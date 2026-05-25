use crate::config::{render_plan, InstallerConfig};
use std::fs;
use std::io::{BufRead, BufReader};
use std::path::PathBuf;
use std::process::{Command, Stdio};
use std::sync::mpsc::{channel, Receiver, Sender};
use std::thread;

#[derive(Clone, Debug)]
pub enum InstallEvent {
    Started,
    Log(String),
    Finished { success: bool, code: Option<i32> },
    Failed(String),
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

pub fn launch_reset(config: InstallerConfig) -> Receiver<InstallEvent> {
    let (tx, rx) = channel();
    thread::spawn(move || {
        let _ = tx.send(InstallEvent::Started);
        if let Err(err) = run_reset_engine(config, &tx) {
            let _ = tx.send(InstallEvent::Failed(err));
        }
    });
    rx
}

fn run_engine(config: InstallerConfig, tx: &Sender<InstallEvent>) -> Result<(), String> {
    config.can_execute()?;

    let cwd = std::env::current_dir().map_err(|err| format!("could not read cwd: {err}"))?;
    let installer_root = find_installer_root().unwrap_or_else(|| cwd.clone());
    let config_path = installer_root.join("latticra-installer-config.toml");
    let plan_path = installer_root.join("latticra-installer-plan.txt");
    let receipt_dir = installer_root.join("latticra-installer-receipts");

    let config_toml = toml::to_string_pretty(&config)
        .map_err(|err| format!("could not serialize installer config: {err}"))?;
    fs::write(&config_path, config_toml)
        .map_err(|err| format!("could not write {}: {err}", config_path.display()))?;
    fs::write(&plan_path, render_plan(&config))
        .map_err(|err| format!("could not write {}: {err}", plan_path.display()))?;

    let script = find_apply_script().ok_or_else(|| {
        "could not find scripts/latticra-installer-apply.sh from current working directory or executable path".to_owned()
    })?;

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

    let child = Command::new("sh")
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

fn run_reset_engine(config: InstallerConfig, tx: &Sender<InstallEvent>) -> Result<(), String> {
    config.can_reset()?;

    let script = find_uninstall_script().ok_or_else(|| {
        "could not find scripts/latticra-installer-uninstall.sh from current working directory or executable path".to_owned()
    })?;

    let _ = tx.send(InstallEvent::Log(format!(
        "ENGINE: reset_script={}",
        script.display()
    )));
    let _ = tx.send(InstallEvent::Log(format!(
        "ENGINE: reset_mode={}",
        config.reset_mode_label()
    )));
    let _ = tx.send(InstallEvent::Log(format!(
        "ENGINE: reset_prefix={}",
        config.install_prefix
    )));

    let mut command = Command::new("sh");
    command
        .arg(&script)
        .arg("--prefix")
        .arg(&config.install_prefix);

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
    if let Ok(root) = std::env::var("LATTICRA_INSTALLER_ROOT") {
        let path = PathBuf::from(root);
        if path.is_dir() {
            return Some(path);
        }
    }

    if let Ok(cwd) = std::env::current_dir() {
        if cwd.join("scripts/latticra-installer-apply.sh").is_file() {
            return Some(cwd);
        }
        if let Some(parent) = cwd.parent() {
            if parent.join("scripts/latticra-installer-apply.sh").is_file() {
                return Some(parent.to_path_buf());
            }
        }
    }

    None
}

fn find_apply_script() -> Option<PathBuf> {
    let mut candidates = Vec::new();

    if let Some(root) = find_installer_root() {
        candidates.push(root.join("scripts/latticra-installer-apply.sh"));
    }

    if let Ok(cwd) = std::env::current_dir() {
        candidates.push(cwd.join("../scripts/latticra-installer-apply.sh"));
        candidates.push(cwd.join("scripts/latticra-installer-apply.sh"));
        candidates.push(cwd.join("installer/scripts/latticra-installer-apply.sh"));
    }

    if let Ok(exe) = std::env::current_exe() {
        if let Some(dir) = exe.parent() {
            candidates.push(dir.join("../../../scripts/latticra-installer-apply.sh"));
            candidates.push(dir.join("../../scripts/latticra-installer-apply.sh"));
            candidates.push(dir.join("../scripts/latticra-installer-apply.sh"));
        }
    }

    candidates.into_iter().find(|path| path.is_file())
}

fn find_uninstall_script() -> Option<PathBuf> {
    let mut candidates = Vec::new();

    if let Some(root) = find_installer_root() {
        candidates.push(root.join("scripts/latticra-installer-uninstall.sh"));
    }

    if let Ok(cwd) = std::env::current_dir() {
        candidates.push(cwd.join("../scripts/latticra-installer-uninstall.sh"));
        candidates.push(cwd.join("scripts/latticra-installer-uninstall.sh"));
        candidates.push(cwd.join("installer/scripts/latticra-installer-uninstall.sh"));
    }

    if let Ok(exe) = std::env::current_exe() {
        if let Some(dir) = exe.parent() {
            candidates.push(dir.join("../../../scripts/latticra-installer-uninstall.sh"));
            candidates.push(dir.join("../../scripts/latticra-installer-uninstall.sh"));
            candidates.push(dir.join("../scripts/latticra-installer-uninstall.sh"));
        }
    }

    candidates.into_iter().find(|path| path.is_file())
}
