use crate::config::{render_plan, InstallerConfig};
use std::fs::{self, OpenOptions};
use std::io::{BufRead, BufReader, Write};
#[cfg(unix)]
use std::os::unix::fs::OpenOptionsExt;
use std::path::{Path, PathBuf};
use std::process::{Command, Stdio};
use std::sync::mpsc::{channel, Receiver, Sender};
use std::thread;

const APPLY_SCRIPT: &str = "latticra-installer-apply.sh";
const UNINSTALL_SCRIPT: &str = "latticra-installer-uninstall.sh";
const SYSTEM_SHELL: &str = "/bin/sh";
const REDACTED_LOG_VALUE: &str = "[redacted]";
const PRIVATE_KEY_MARKER_REDACTION: &str = "[redacted-private-key-marker]";
const SENSITIVE_ASSIGNMENT_KEYS: &[&str] = &[
    "AWS_ACCESS_KEY_ID",
    "AWS_SECRET_ACCESS_KEY",
    "AWS_SESSION_TOKEN",
    "GITHUB_TOKEN",
    "GH_TOKEN",
    "OPENAI_API_KEY",
    "PASSWORD",
    "PRIVATE_KEY",
    "SECRET",
    "TOKEN",
];

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
    write_installer_artifact(&config_path, config_toml.as_bytes())?;
    write_installer_artifact(&plan_path, render_plan(&config).as_bytes())?;

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
                        let _ = tx.send(InstallEvent::Log(redact_log_line(&line)));
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
                        let _ = tx.send(InstallEvent::Log(format!(
                            "stderr: {}",
                            redact_log_line(&line)
                        )));
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

fn redact_log_line(line: &str) -> String {
    if line.contains("-----BEGIN ") && line.contains("PRIVATE KEY-----") {
        return PRIVATE_KEY_MARKER_REDACTION.to_owned();
    }

    let mut redacted = line.to_owned();
    for key in SENSITIVE_ASSIGNMENT_KEYS {
        redacted = redact_sensitive_assignment(&redacted, key);
    }

    for (prefix, min_len) in [
        ("github_pat_", 31usize),
        ("ghp_", 24usize),
        ("gho_", 24usize),
        ("ghu_", 24usize),
        ("ghs_", 24usize),
        ("ghr_", 24usize),
        ("glpat-", 26usize),
        ("sk-", 23usize),
        ("xoxb-", 15usize),
        ("xoxa-", 15usize),
        ("xoxp-", 15usize),
        ("xoxr-", 15usize),
        ("xoxs-", 15usize),
        ("AKIA", 20usize),
        ("ASIA", 20usize),
        ("AIza", 39usize),
    ] {
        redacted = redact_prefixed_token(&redacted, prefix, min_len);
    }

    redacted
}

fn redact_sensitive_assignment(line: &str, key: &str) -> String {
    let mut redacted = line.to_owned();
    let key_lower = key.to_ascii_lowercase();
    let mut search_start = 0usize;

    loop {
        if search_start >= redacted.len() {
            break;
        }

        let haystack = redacted[search_start..].to_ascii_lowercase();
        let Some(relative_start) = haystack.find(&key_lower) else {
            break;
        };
        let key_start = search_start + relative_start;
        let key_end = key_start + key.len();

        if !has_token_boundary(&redacted, key_start, key_end) {
            search_start = key_end;
            continue;
        }

        let bytes = redacted.as_bytes();
        let mut cursor = key_end;
        while cursor < bytes.len() && matches!(bytes[cursor], b' ' | b'\t') {
            cursor += 1;
        }
        if cursor >= bytes.len() || bytes[cursor] != b'=' {
            search_start = key_end;
            continue;
        }
        cursor += 1;
        while cursor < bytes.len() && matches!(bytes[cursor], b' ' | b'\t') {
            cursor += 1;
        }

        let value_start = cursor;
        while cursor < redacted.len() {
            let Some(ch) = redacted[cursor..].chars().next() else {
                break;
            };
            if ch.is_whitespace() {
                break;
            }
            cursor += ch.len_utf8();
        }

        if value_start == cursor {
            search_start = cursor;
            continue;
        }

        redacted.replace_range(value_start..cursor, REDACTED_LOG_VALUE);
        search_start = value_start + REDACTED_LOG_VALUE.len();
    }

    redacted
}

fn redact_prefixed_token(line: &str, prefix: &str, min_len: usize) -> String {
    let mut redacted = line.to_owned();
    let mut search_start = 0usize;

    loop {
        if search_start >= redacted.len() {
            break;
        }

        let Some(relative_start) = redacted[search_start..].find(prefix) else {
            break;
        };
        let token_start = search_start + relative_start;
        if !is_left_token_boundary(&redacted, token_start) {
            search_start = token_start + prefix.len();
            continue;
        }

        let bytes = redacted.as_bytes();
        let mut token_end = token_start + prefix.len();
        while token_end < bytes.len() && is_token_byte(bytes[token_end]) {
            token_end += 1;
        }

        if token_end - token_start < min_len || !is_right_token_boundary(&redacted, token_end) {
            search_start = token_start + prefix.len();
            continue;
        }

        redacted.replace_range(token_start..token_end, REDACTED_LOG_VALUE);
        search_start = token_start + REDACTED_LOG_VALUE.len();
    }

    redacted
}

fn has_token_boundary(value: &str, start: usize, end: usize) -> bool {
    is_left_token_boundary(value, start) && is_right_token_boundary(value, end)
}

fn is_left_token_boundary(value: &str, start: usize) -> bool {
    if start == 0 {
        return true;
    }
    !is_token_byte(value.as_bytes()[start - 1])
}

fn is_right_token_boundary(value: &str, end: usize) -> bool {
    if end >= value.len() {
        return true;
    }
    !is_token_byte(value.as_bytes()[end])
}

fn is_token_byte(byte: u8) -> bool {
    byte.is_ascii_alphanumeric() || matches!(byte, b'_' | b'-')
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

pub(crate) fn write_installer_artifact(path: &Path, contents: &[u8]) -> Result<(), String> {
    let parent = path
        .parent()
        .ok_or_else(|| format!("installer artifact path has no parent: {}", path.display()))?;

    if !regular_non_symlink_dir(parent) {
        return Err(format!(
            "installer artifact parent is missing or symlinked: {}",
            parent.display()
        ));
    }

    match fs::symlink_metadata(path) {
        Ok(metadata) => {
            let file_type = metadata.file_type();
            if file_type.is_symlink() {
                return Err(format!(
                    "refusing to overwrite symlink installer artifact: {}",
                    path.display()
                ));
            }
            if !file_type.is_file() {
                return Err(format!(
                    "refusing to overwrite non-file installer artifact: {}",
                    path.display()
                ));
            }
        }
        Err(err) if err.kind() == std::io::ErrorKind::NotFound => {}
        Err(err) => {
            return Err(format!(
                "could not inspect installer artifact {}: {err}",
                path.display()
            ));
        }
    }

    let file_name = path
        .file_name()
        .ok_or_else(|| {
            format!(
                "installer artifact path has no file name: {}",
                path.display()
            )
        })?
        .to_string_lossy();
    let process_id = std::process::id();
    let mut last_exists = None;

    for attempt in 0..16u8 {
        let tmp_path = parent.join(format!(".{file_name}.tmp-{process_id}-{attempt}"));
        let mut options = OpenOptions::new();
        options.write(true).create_new(true);
        #[cfg(unix)]
        options.mode(0o600);

        match options.open(&tmp_path) {
            Ok(mut file) => {
                if let Err(err) = file.write_all(contents) {
                    return Err(format!(
                        "could not write temporary installer artifact {}; preserved for inspection: {err}",
                        tmp_path.display()
                    ));
                }
                if let Err(err) = file.flush() {
                    return Err(format!(
                        "could not flush temporary installer artifact {}; preserved for inspection: {err}",
                        tmp_path.display()
                    ));
                }
                drop(file);
                if let Err(err) = fs::rename(&tmp_path, path) {
                    return Err(format!(
                        "could not publish installer artifact {}; temporary artifact preserved at {}: {err}",
                        path.display(),
                        tmp_path.display()
                    ));
                }
                return Ok(());
            }
            Err(err) if err.kind() == std::io::ErrorKind::AlreadyExists => {
                last_exists = Some(err);
            }
            Err(err) => {
                return Err(format!(
                    "could not create temporary installer artifact for {}: {err}",
                    path.display()
                ));
            }
        }
    }

    Err(format!(
        "could not create temporary installer artifact for {} after retries: {}",
        path.display(),
        last_exists
            .map(|err| err.to_string())
            .unwrap_or_else(|| "temporary name collision".to_owned())
    ))
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
    fn redact_log_line_masks_sensitive_assignments() {
        let openai_key_line = format!(
            "{}{}{}{} status=debug",
            "OPENAI", "_API_KEY=", "sk-proj-", "secret12345678901234567890"
        );
        let aws_secret_line = format!(
            "prefix {}{} = abcdefgh1234567890 suffix",
            "AWS_SECRET", "_ACCESS_KEY"
        );

        assert_eq!(
            redact_log_line(&openai_key_line),
            format!("{}{}[redacted] status=debug", "OPENAI", "_API_KEY=")
        );
        assert_eq!(
            redact_log_line(&aws_secret_line),
            "prefix AWS_SECRET_ACCESS_KEY = [redacted] suffix"
        );
        assert_eq!(
            redact_log_line("PASSWORD=caf\u{e9} done"),
            "PASSWORD=[redacted] done"
        );
    }

    #[test]
    fn redact_log_line_masks_private_key_markers_and_tokens() {
        let private_key_marker = ["-----BEGIN ", "OPENSSH PRIVATE KEY-----"].concat();
        let openai_token_line = format!(
            "token {}{} done",
            "sk-proj-", "abcdefghijklmnopqrstuvwxyz1234567890"
        );
        let github_token = format!(
            "{}{}",
            "github_pat_", "abcdefghijklmnopqrstuvwxyz1234567890"
        );

        assert_eq!(
            redact_log_line(&private_key_marker),
            "[redacted-private-key-marker]"
        );
        assert_eq!(redact_log_line(&openai_token_line), "token [redacted] done");
        assert_eq!(redact_log_line(&github_token), "[redacted]");
    }

    #[test]
    fn redact_log_line_preserves_non_secret_terms() {
        assert_eq!(
            redact_log_line("prompt_tokenization_boundary=metadata-only"),
            "prompt_tokenization_boundary=metadata-only"
        );
        assert_eq!(
            redact_log_line("task-nucleus-report-only-execution"),
            "task-nucleus-report-only-execution"
        );
        assert_eq!(
            redact_log_line("status=ok note=cafe-ready"),
            "status=ok note=cafe-ready"
        );
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

    #[test]
    fn write_installer_artifact_replaces_regular_file() {
        let root = unique_temp_root("artifact-regular");
        fs::create_dir_all(&root).expect("create artifact fixture");
        let artifact = root.join("latticra-installer-plan.txt");

        write_installer_artifact(&artifact, b"first\n").expect("write first artifact");
        write_installer_artifact(&artifact, b"second\n").expect("replace artifact");

        let contents = fs::read_to_string(&artifact).expect("read artifact");
        assert_eq!(contents, "second\n");
        #[cfg(unix)]
        {
            use std::os::unix::fs::PermissionsExt;
            let mode = fs::metadata(&artifact)
                .expect("artifact metadata")
                .permissions()
                .mode()
                & 0o777;
            assert_eq!(mode, 0o600);
        }

        fs::remove_dir_all(root).expect("cleanup fixture");
    }

    #[cfg(unix)]
    #[test]
    fn write_installer_artifact_rejects_symlink_target() {
        let root = unique_temp_root("artifact-symlink");
        fs::create_dir_all(&root).expect("create artifact fixture");
        let victim = root.join("victim.txt");
        let artifact = root.join("latticra-installer-config.toml");

        fs::write(&victim, "do-not-overwrite\n").expect("write victim");
        std::os::unix::fs::symlink(&victim, &artifact).expect("create artifact symlink");

        assert!(write_installer_artifact(&artifact, b"replacement\n").is_err());
        assert_eq!(
            fs::read_to_string(&victim).expect("read victim"),
            "do-not-overwrite\n"
        );

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
