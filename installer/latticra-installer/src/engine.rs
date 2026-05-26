use crate::config::{render_plan, InstallerConfig};
use std::fs;
use std::io::{BufRead, BufReader};
use std::path::{Path, PathBuf};
use std::process::{Command, Stdio};
use std::sync::mpsc::{channel, Receiver, Sender};
use std::thread;

const APPLY_SCRIPT: &str = "latticra-installer-apply.sh";
const UNINSTALL_SCRIPT: &str = "latticra-installer-uninstall.sh";
const SYSTEM_SHELL: &str = "/bin/sh";

#[derive(Clone, Debug)]
pub enum InstallEvent {
    Started,
    Log(String),
    Finished { success: bool, code: Option<i32> },
    Failed(String),
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum RemovalOperation {
    Reset,
    Uninstall,
}

impl RemovalOperation {
    pub fn arg(self) -> &'static str {
        match self {
            Self::Reset => "reset",
            Self::Uninstall => "uninstall",
        }
    }

    pub fn mode_label(self, dry_run: bool) -> String {
        if dry_run {
            format!("dry-{}", self.arg())
        } else {
            format!("local-prefix-{}", self.arg())
        }
    }
}

pub fn launch(config: InstallerConfig) -> Receiver<InstallEvent> {
    let (tx, rx) = channel();
    thread::spawn(move || {
        let _ = tx.send(InstallEvent::Started);
        if let Err(err) = run_engine(config, &tx) {
            let _ = tx.send(InstallEvent::Failed(err));
        }
    });
    rx
}

pub fn launch_removal(
    config: InstallerConfig,
    operation: RemovalOperation,
) -> Receiver<InstallEvent> {
    let (tx, rx) = channel();
    thread::spawn(move || {
        let _ = tx.send(InstallEvent::Started);
        if let Err(err) = run_removal_engine(config, operation, &tx) {
            let _ = tx.send(InstallEvent::Failed(err));
        }
    });
    rx
}

fn run_engine(config: InstallerConfig, tx: &Sender<InstallEvent>) -> Result<(), String> {
    config.can_execute()?;

    let installer_root = find_installer_root().ok_or_else(|| {
        "could not find a validated installer root from the executable path or LATTICRA_INSTALLER_ROOT"
            .to_owned()
    })?;
    let config_path = installer_root.join("latticra-installer-config.toml");
    let plan_path = installer_root.join("latticra-installer-plan.txt");
    let receipt_dir = installer_root.join("latticra-installer-receipts");

    let config_toml = toml::to_string_pretty(&config)
        .map_err(|err| format!("could not serialize installer config: {err}"))?;
    fs::write(&config_path, config_toml)
        .map_err(|err| format!("could not write {}: {err}", config_path.display()))?;
    fs::write(&plan_path, render_plan(&config))
        .map_err(|err| format!("could not write {}: {err}", plan_path.display()))?;

    let script = trusted_installer_script(&installer_root, APPLY_SCRIPT)?;

    let _ = tx.send(InstallEvent::Log(format!(
        "ENGINE: config={}",
        config_path.display()
    )));
    let _ = tx.send(InstallEvent::Log(format!(
        "ENGINE: plan={}",
        plan_path.display()
    )));
    let _ = tx.send(InstallEvent::Log(format!(
        "ENGINE: apply_script={}",
        script.display()
    )));

    let child = Command::new(SYSTEM_SHELL)
        .current_dir(&installer_root)
        .arg(&script)
        .arg("--config")
        .arg(&config_path)
        .arg("--plan")
        .arg(&plan_path)
        .arg("--receipt-dir")
        .arg(&receipt_dir)
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .spawn()
        .map_err(|err| format!("could not launch install engine: {err}"))?;

    stream_child(child, tx)
}

fn run_removal_engine(
    config: InstallerConfig,
    operation: RemovalOperation,
    tx: &Sender<InstallEvent>,
) -> Result<(), String> {
    config.can_reset()?;

    let installer_root = find_installer_root().ok_or_else(|| {
        "could not find a validated installer root from the executable path or LATTICRA_INSTALLER_ROOT"
            .to_owned()
    })?;
    let script = trusted_installer_script(&installer_root, UNINSTALL_SCRIPT)?;

    let _ = tx.send(InstallEvent::Log(format!(
        "ENGINE: removal_script={}",
        script.display()
    )));
    let _ = tx.send(InstallEvent::Log(format!(
        "ENGINE: removal_mode={}",
        operation.mode_label(config.safety.dry_run)
    )));
    let _ = tx.send(InstallEvent::Log(format!(
        "ENGINE: removal_prefix={}",
        config.install_prefix
    )));

    let mut command = Command::new(SYSTEM_SHELL);
    command
        .current_dir(&installer_root)
        .arg(&script)
        .arg("--prefix")
        .arg(&config.install_prefix)
        .arg("--operation")
        .arg(operation.arg());

    if config.safety.dry_run {
        command.arg("--dry-run");
    }

    let child = command
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .spawn()
        .map_err(|err| format!("could not launch reset engine: {err}"))?;

    stream_child(child, tx)
}

fn stream_child(mut child: std::process::Child, tx: &Sender<InstallEvent>) -> Result<(), String> {
    let stdout_handle = child.stdout.take().map(|stdout| {
        let tx = tx.clone();
        thread::spawn(move || {
            let reader = BufReader::new(stdout);
            for line in reader.lines() {
                match line {
                    Ok(line) => {
                        let _ = tx.send(InstallEvent::Log(line));
                    }
                    Err(err) => {
                        let _ = tx.send(InstallEvent::Log(format!(
                            "ENGINE: stdout read error: {err}"
                        )));
                    }
                }
            }
        })
    });

    let stderr_handle = child.stderr.take().map(|stderr| {
        let tx = tx.clone();
        thread::spawn(move || {
            let reader = BufReader::new(stderr);
            for line in reader.lines() {
                match line {
                    Ok(line) => {
                        let _ = tx.send(InstallEvent::Log(format!("stderr: {line}")));
                    }
                    Err(err) => {
                        let _ = tx.send(InstallEvent::Log(format!(
                            "ENGINE: stderr read error: {err}"
                        )));
                    }
                }
            }
        })
    });

    let status = child
        .wait()
        .map_err(|err| format!("install engine wait failed: {err}"))?;

    if let Some(handle) = stdout_handle {
        let _ = handle.join();
    }
    if let Some(handle) = stderr_handle {
        let _ = handle.join();
    }

    let _ = tx.send(InstallEvent::Finished {
        success: status.success(),
        code: status.code(),
    });

    Ok(())
}

fn find_installer_root() -> Option<PathBuf> {
    installer_root_candidates()
        .into_iter()
        .filter_map(|candidate| validate_installer_root(&candidate))
        .next()
}

fn installer_root_candidates() -> Vec<PathBuf> {
    let mut candidates = Vec::new();

    if let Ok(root) = std::env::var("LATTICRA_INSTALLER_ROOT") {
        candidates.push(PathBuf::from(root));
    }

    if let Ok(exe) = std::env::current_exe() {
        if let Some(dir) = exe.parent() {
            for ancestor in dir.ancestors().take(8) {
                candidates.push(ancestor.to_path_buf());
                candidates.push(ancestor.join("installer"));
            }
        }
    }

    candidates
}

fn validate_installer_root(candidate: &Path) -> Option<PathBuf> {
    let root = fs::canonicalize(candidate).ok()?;
    if !root.is_dir() {
        return None;
    }

    let scripts_dir = root.join("scripts");
    let manifests_dir = root.join("manifests");
    let manifest = manifests_dir.join("components.toml");

    if !regular_non_symlink_dir(&scripts_dir) || !regular_non_symlink_dir(&manifests_dir) {
        return None;
    }
    if !regular_non_symlink_file(&manifest) {
        return None;
    }
    if trusted_installer_script(&root, APPLY_SCRIPT).is_err() {
        return None;
    }
    if trusted_installer_script(&root, UNINSTALL_SCRIPT).is_err() {
        return None;
    }

    Some(root)
}

fn trusted_installer_script(installer_root: &Path, script_name: &str) -> Result<PathBuf, String> {
    if script_name.contains('/') || script_name.contains('\\') {
        return Err(format!(
            "installer script name is not trusted: {script_name}"
        ));
    }

    let root = fs::canonicalize(installer_root)
        .map_err(|err| format!("could not canonicalize installer root: {err}"))?;
    let scripts_dir = root.join("scripts");
    let script = scripts_dir.join(script_name);

    if !regular_non_symlink_dir(&scripts_dir) {
        return Err(format!(
            "installer scripts directory is missing or symlinked: {}",
            scripts_dir.display()
        ));
    }
    if !regular_non_symlink_file(&script) {
        return Err(format!(
            "installer script is missing or symlinked: {}",
            script.display()
        ));
    }

    let script_real = fs::canonicalize(&script)
        .map_err(|err| format!("could not canonicalize installer script: {err}"))?;
    if !script_real.starts_with(&scripts_dir) {
        return Err(format!(
            "installer script escaped trusted root: {}",
            script_real.display()
        ));
    }

    Ok(script_real)
}

fn regular_non_symlink_dir(path: &Path) -> bool {
    fs::symlink_metadata(path)
        .map(|metadata| metadata.file_type().is_dir())
        .unwrap_or(false)
}

fn regular_non_symlink_file(path: &Path) -> bool {
    fs::symlink_metadata(path)
        .map(|metadata| metadata.file_type().is_file())
        .unwrap_or(false)
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::time::{SystemTime, UNIX_EPOCH};

    fn unique_temp_root(label: &str) -> PathBuf {
        let nanos = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .expect("system clock before unix epoch")
            .as_nanos();
        std::env::temp_dir().join(format!(
            "latticra-panel-engine-{label}-{}-{nanos}",
            std::process::id()
        ))
    }

    fn write_fixture(path: &Path, content: &str) {
        fs::write(path, content).expect("write fixture");
    }

    fn installer_fixture(label: &str) -> PathBuf {
        let root = unique_temp_root(label);
        fs::create_dir_all(root.join("scripts")).expect("create scripts fixture");
        fs::create_dir_all(root.join("manifests")).expect("create manifests fixture");
        write_fixture(&root.join("manifests/components.toml"), "# fixture\n");
        write_fixture(
            &root.join("scripts").join(APPLY_SCRIPT),
            "#!/bin/sh\nexit 0\n",
        );
        write_fixture(
            &root.join("scripts").join(UNINSTALL_SCRIPT),
            "#!/bin/sh\nexit 0\n",
        );
        root
    }

    #[test]
    fn trusted_installer_script_accepts_regular_script_under_root() {
        let root = installer_fixture("regular");
        let script = trusted_installer_script(&root, APPLY_SCRIPT).expect("trusted script");

        assert!(script.ends_with(Path::new("scripts").join(APPLY_SCRIPT)));

        fs::remove_dir_all(root).expect("cleanup fixture");
    }

    #[test]
    fn trusted_installer_script_rejects_script_name_traversal() {
        let root = installer_fixture("traversal");

        assert!(trusted_installer_script(&root, "../latticra-installer-apply.sh").is_err());

        fs::remove_dir_all(root).expect("cleanup fixture");
    }

    #[cfg(unix)]
    #[test]
    fn validate_installer_root_rejects_symlinked_script() {
        let root = installer_fixture("symlink");
        let apply = root.join("scripts").join(APPLY_SCRIPT);

        fs::remove_file(&apply).expect("remove regular apply fixture");
        std::os::unix::fs::symlink("/bin/sh", &apply).expect("create script symlink");

        assert!(validate_installer_root(&root).is_none());

        fs::remove_dir_all(root).expect("cleanup fixture");
    }
}
