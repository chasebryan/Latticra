use crate::config::{
    render_plan, InstallProfile, InstallerConfig, LatticraConsoleProfile, SealCryptoProfile,
};
use crate::engine::{self, InstallEvent, RemovalOperation};
use eframe::egui;
use std::fs;
use std::sync::mpsc::Receiver;
use std::time::Duration;

const PANEL_VERSION: &str = env!("CARGO_PKG_VERSION");
const PANEL_BUILD: &str = "gui-workbench";
const SEAL_PNG: &[u8] = include_bytes!("../assets/latticra-panel.png");
const COMPACT_LAYOUT_WIDTH: f32 = 1400.0;
const NARROW_LAYOUT_WIDTH: f32 = 900.0;
const NADIA_PANEL_COMMANDS: &[(&str, &str)] = &[
    ("status", "Stage-35 status and authority summary"),
    ("context", "Stage-1 local context-pack metadata"),
    ("runtime", "Stage-2 runtime-profile metadata"),
    ("plan", "Stage-3 prompt-plan workbench metadata"),
    ("mode", "Stage-4 systems-engineering mode validation"),
    ("ledger", "Stage-5 productivity ledger metadata"),
    ("safety", "Stage-6 protective-safety boundary"),
    ("tool", "Stage-7 guarded tool-authority preflight"),
    ("prompt-contract", "Stage-8 prompt-evaluation contract"),
    ("model-registry", "Stage-9 local model-registry contract"),
    (
        "inference-readiness",
        "Stage-10 inference-readiness contract",
    ),
    ("runtime-invocation", "Stage-11 runtime-invocation contract"),
    ("model-load", "Stage-12 model-load contract"),
    ("prompt-receipt", "Stage-13 prompt-receipt contract"),
    (
        "prompt-materialization",
        "Stage-14 prompt-materialization contract",
    ),
    ("awareness-dialogue", "Stage-15 awareness-dialogue contract"),
    (
        "prompt-evaluation-handoff",
        "Stage-16 prompt-evaluation handoff contract",
    ),
    (
        "tokenization-boundary",
        "Stage-17 tokenization-boundary contract",
    ),
    (
        "tokenizer-specification",
        "Stage-18 tokenizer-specification contract",
    ),
    ("tokenizer-manifest", "Stage-19 tokenizer-manifest contract"),
    (
        "tokenizer-artifact-inventory",
        "Stage-20 tokenizer-artifact-inventory contract",
    ),
    (
        "tokenizer-artifact-measurement",
        "Stage-21 tokenizer-artifact-measurement contract",
    ),
    (
        "tokenizer-artifact-verification",
        "Stage-22 tokenizer-artifact-verification contract",
    ),
    (
        "tokenizer-artifact-binding",
        "Stage-23 tokenizer-artifact-binding contract",
    ),
    (
        "tokenizer-runtime-attachment",
        "Stage-24 tokenizer-runtime-attachment contract",
    ),
    (
        "prompt-tokenization",
        "Stage-25 prompt-tokenization contract",
    ),
    (
        "prompt-token-sequence",
        "Stage-26 prompt-token-sequence contract",
    ),
    (
        "context-window-assembly",
        "Stage-27 context-window-assembly contract",
    ),
    (
        "prompt-evaluation-input",
        "Stage-28 prompt-evaluation-input contract",
    ),
    (
        "prompt-evaluation-runtime-handoff",
        "Stage-29 prompt-evaluation runtime handoff contract",
    ),
    (
        "prompt-evaluation-invocation",
        "Stage-30 prompt-evaluation invocation contract",
    ),
    (
        "prompt-evaluation-result",
        "Stage-31 prompt-evaluation result contract",
    ),
    (
        "prompt-evaluation-result-review",
        "Stage-32 prompt-evaluation result review contract",
    ),
    (
        "prompt-evaluation-result-disposition",
        "Stage-33 prompt-evaluation result disposition contract",
    ),
    (
        "prompt-evaluation-result-release",
        "Stage-34 prompt-evaluation result release contract",
    ),
    (
        "prompt-evaluation-result-release-receipt",
        "Stage-35 prompt-evaluation result release receipt contract",
    ),
];

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum InstallState {
    Idle,
    Running,
    Complete,
    Failed,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum OperationIntent {
    Install,
    UpdateDryRun,
    UpdateApply,
    Removal,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum WorkspaceTab {
    Dashboard,
    Components,
    Console,
    Seal,
    Authority,
    Delivery,
    Updater,
    Evidence,
    Procedure,
}

pub struct LatticraInstallerApp {
    config: InstallerConfig,
    plan: String,
    status: String,
    logs: Vec<String>,
    console_lines: Vec<String>,
    console_input: String,
    terminal_cwd: String,
    show_plan_over_log: bool,
    active_tab: WorkspaceTab,
    seal_texture: Option<egui::TextureHandle>,
    rx: Option<Receiver<InstallEvent>>,
    install_state: InstallState,
    active_operation: OperationIntent,
    last_update_dry_run_ok: bool,
    guarded_local_ack: bool,
    phase_index: usize,
    phase_total: usize,
    phase_title: String,
}

impl Default for LatticraInstallerApp {
    fn default() -> Self {
        let config = InstallerConfig::default();
        let plan = render_plan(&config);
        let terminal_cwd = std::env::current_dir()
            .map(|path| path.display().to_string())
            .unwrap_or_else(|_| ".".to_owned());
        Self {
            config,
            plan,
            status: "Ready. Guided Workbench opens in dry-run authority.".to_owned(),
            logs: Vec::new(),
            console_lines: vec![
                format!("Latticra Panel v{PANEL_VERSION} bounded operator console online."),
                "Authority baseline: root=0 network=0 runtime_enforcement=0.".to_owned(),
                "Panel commands: help, status, lc commands, lc status, lc install-config, plan, save, dry-run, reset, uninstall, profile seal, profile fedora, nadia commands."
                    .to_owned(),
                "Navigation commands: pwd, cd <dir>. External host commands are denied.".to_owned(),
            ],
            console_input: String::new(),
            terminal_cwd,
            show_plan_over_log: true,
            active_tab: WorkspaceTab::Dashboard,
            seal_texture: None,
            rx: None,
            install_state: InstallState::Idle,
            active_operation: OperationIntent::Install,
            last_update_dry_run_ok: false,
            guarded_local_ack: false,
            phase_index: 0,
            phase_total: 10,
            phase_title: "idle".to_owned(),
        }
    }
}

impl LatticraInstallerApp {
    fn ensure_texture(&mut self, ctx: &egui::Context) {
        if self.seal_texture.is_some() {
            return;
        }

        match image::load_from_memory(SEAL_PNG) {
            Ok(image) => {
                let image = image.to_rgba8();
                let size = [image.width() as usize, image.height() as usize];
                let pixels = image.into_raw();
                let color_image = egui::ColorImage::from_rgba_unmultiplied(size, &pixels);

                self.seal_texture = Some(ctx.load_texture(
                    "latticra-seal",
                    color_image,
                    egui::TextureOptions::LINEAR,
                ));
            }
            Err(err) => {
                self.status = format!("Could not decode embedded Latticra Seal image: {err}");
            }
        }
    }

    fn push_console(&mut self, line: impl Into<String>) {
        self.console_lines.push(line.into());
        if self.console_lines.len() > 360 {
            let drain_count = self.console_lines.len() - 360;
            self.console_lines.drain(0..drain_count);
        }
    }

    fn push_nadia_commands(&mut self) {
        self.push_console("NADIA COMMAND SURFACE");
        self.push_console("panel_command=nadia commands");
        self.push_console("installed_wrapper=latticra-nadia commands");
        self.push_console(format!(
            "component_selected={}",
            self.config.components.nadia_offline_ai
        ));
        for &(command, detail) in NADIA_PANEL_COMMANDS {
            self.push_console(format!("command=nadia {command} detail={detail}"));
        }
        self.push_console(
            "network_authority=0 tool_execution_authority=0 runtime_invocation_authority=0 source_mutation_authority=0",
        );
        self.push_console(
            "prompt_evaluation_authority=0 inference_authority=0 model_load_authority=0",
        );
    }

    fn refresh_plan(&mut self) {
        self.config.safety.allow_network_effect = false;
        self.plan = render_plan(&self.config);
    }

    fn apply_profile(&mut self, profile: InstallProfile) {
        self.config.profile = profile;
        self.config.apply_profile_defaults();
        self.guarded_local_ack = false;
        self.refresh_plan();
        self.status = format!("Applied {} defaults.", self.config.profile.label());
        self.push_console(format!("profile -> {}", self.config.profile.label()));
    }

    fn apply_seal_crypto_profile(&mut self, profile: SealCryptoProfile) {
        self.config.seal.crypto_profile = profile;
        self.config.seal.apply_crypto_profile_defaults();
        self.refresh_plan();
        self.status = format!(
            "Seal crypto profile set to {}.",
            self.config.seal.crypto_profile.label()
        );
        self.push_console(format!(
            "seal.crypto_profile -> {}",
            self.config.seal.crypto_profile.label()
        ));
    }

    fn apply_lc_profile(&mut self, profile: LatticraConsoleProfile) {
        self.config.lc.profile = profile;
        self.config.lc.apply_profile_defaults();
        self.refresh_plan();
        self.status = format!("LC profile set to {}.", self.config.lc.profile.label());
        self.push_console(format!("lc.profile -> {}", self.config.lc.profile.label()));
    }

    fn set_mode_dry(&mut self) {
        self.config.safety.dry_run = true;
        self.config.safety.allow_host_mutation = false;
        self.guarded_local_ack = false;
        self.refresh_plan();
        self.status = "Mode set to dry-install. Host writes are disabled.".to_owned();
        self.push_console("mode -> dry-install");
    }

    fn set_mode_local(&mut self) {
        self.config.safety.dry_run = false;
        self.config.safety.allow_host_mutation = true;
        self.refresh_plan();
        self.status = "Mode set to guarded local-prefix install.".to_owned();
        self.push_console("mode -> guarded local-prefix install");
    }

    fn request_guarded_local_mode(&mut self) {
        if !self.guarded_local_ack {
            self.active_tab = WorkspaceTab::Authority;
            self.status =
                "Guarded local mode is locked until the Authority acknowledgement is checked."
                    .to_owned();
            self.push_console(
                "blocked: guarded local mode requires Authority acknowledgement first",
            );
            return;
        }

        self.set_mode_local();
    }

    fn save_config(&mut self) {
        self.config.safety.allow_network_effect = false;
        match toml::to_string_pretty(&self.config) {
            Ok(toml) => match fs::write("latticra-installer-config.toml", toml) {
                Ok(_) => {
                    self.status = "Saved latticra-installer-config.toml".to_owned();
                    self.push_console("saved latticra-installer-config.toml");
                }
                Err(err) => self.status = format!("Could not save config: {err}"),
            },
            Err(err) => self.status = format!("Could not serialize config: {err}"),
        }
    }

    fn write_plan(&mut self) {
        self.refresh_plan();
        match fs::write("latticra-installer-plan.txt", &self.plan) {
            Ok(_) => {
                self.status = "Wrote latticra-installer-plan.txt".to_owned();
                self.push_console("wrote latticra-installer-plan.txt");
            }
            Err(err) => self.status = format!("Could not write plan: {err}"),
        }
    }

    fn start_install(&mut self) {
        self.start_install_with_intent(OperationIntent::Install);
    }

    fn start_install_with_intent(&mut self, intent: OperationIntent) {
        self.config.safety.allow_network_effect = false;
        self.config.updater.allow_network_fetch = false;
        match self.panel_can_execute() {
            Ok(()) => {
                self.refresh_plan();
                self.logs.clear();
                self.phase_index = 0;
                self.phase_total = 10;
                self.phase_title = "starting".to_owned();
                self.active_operation = intent;
                self.install_state = InstallState::Running;
                let label = self.operation_label();
                self.status = format!("Starting {label}...");
                self.push_console(format!("launching {label}"));
                self.rx = Some(engine::launch(self.config.clone()));
                self.active_tab = WorkspaceTab::Evidence;
                self.show_plan_over_log = false;
            }
            Err(err) => {
                self.install_state = InstallState::Failed;
                self.status = err.clone();
                self.push_console(format!("blocked: {err}"));
            }
        }
    }

    fn start_update_dry_run(&mut self) {
        if !self.config.updater.reuse_installer_engine {
            self.install_state = InstallState::Failed;
            self.status = "Updater currently requires reuse_installer_engine=true.".to_owned();
            self.push_console("blocked: updater requires guarded installer engine reuse");
            self.active_tab = WorkspaceTab::Updater;
            return;
        }

        self.config.safety.dry_run = true;
        self.config.safety.allow_host_mutation = false;
        self.config.safety.allow_network_effect = false;
        self.config.updater.allow_network_fetch = false;
        self.last_update_dry_run_ok = false;
        self.refresh_plan();
        self.status = "Starting updater dry-run from the current checkout.".to_owned();
        self.push_console("updater: dry-run preview requested");
        self.start_install_with_intent(OperationIntent::UpdateDryRun);
    }

    fn start_update_apply(&mut self) {
        if !self.config.updater.reuse_installer_engine {
            self.install_state = InstallState::Failed;
            self.status = "Updater currently requires reuse_installer_engine=true.".to_owned();
            self.push_console("blocked: updater requires guarded installer engine reuse");
            self.active_tab = WorkspaceTab::Updater;
            return;
        }

        if !self.guarded_local_ack {
            self.install_state = InstallState::Failed;
            self.status =
                "Updater apply requires the guarded local-write acknowledgement first.".to_owned();
            self.push_console(
                "blocked: updater apply requires guarded local-write acknowledgement",
            );
            self.active_tab = WorkspaceTab::Authority;
            return;
        }

        if self.config.updater.require_dry_run_before_apply && !self.last_update_dry_run_ok {
            self.install_state = InstallState::Failed;
            self.status =
                "Updater apply requires a successful updater dry-run in this Panel session."
                    .to_owned();
            self.push_console("blocked: updater apply requires successful updater dry-run first");
            self.active_tab = WorkspaceTab::Updater;
            return;
        }

        self.config.safety.dry_run = false;
        self.config.safety.allow_host_mutation = true;
        self.config.safety.allow_network_effect = false;
        self.config.updater.allow_network_fetch = false;
        self.refresh_plan();
        self.status = "Starting guarded updater apply from the current checkout.".to_owned();
        self.push_console("updater: guarded local-prefix apply requested");
        self.start_install_with_intent(OperationIntent::UpdateApply);
    }

    fn start_removal(&mut self, operation: RemovalOperation) {
        self.config.safety.allow_network_effect = false;
        self.config.updater.allow_network_fetch = false;
        match self.panel_can_reset() {
            Ok(()) => {
                self.logs.clear();
                self.phase_index = 0;
                self.phase_total = 5;
                self.phase_title = format!("starting {}", operation.arg());
                self.active_operation = OperationIntent::Removal;
                self.install_state = InstallState::Running;
                let mode_label = operation.mode_label(self.config.safety.dry_run);
                self.status = format!("Starting {mode_label}...");
                self.push_console(format!("launching {mode_label}"));
                self.rx = Some(engine::launch_removal(self.config.clone(), operation));
                self.active_tab = WorkspaceTab::Evidence;
                self.show_plan_over_log = false;
            }
            Err(err) => {
                self.install_state = InstallState::Failed;
                self.status = err.clone();
                self.push_console(format!("blocked: {err}"));
            }
        }
    }

    fn start_reset(&mut self) {
        self.start_removal(RemovalOperation::Reset);
    }

    fn start_uninstall(&mut self) {
        self.start_removal(RemovalOperation::Uninstall);
    }

    fn drain_events(&mut self) {
        let mut events = Vec::new();
        let mut clear_rx = false;

        if let Some(rx) = &self.rx {
            while let Ok(event) = rx.try_recv() {
                events.push(event);
            }
        }

        for event in events {
            match event {
                InstallEvent::Started => {
                    self.install_state = InstallState::Running;
                    self.status = "Engine started.".to_owned();
                    self.push_console("engine: started");
                }
                InstallEvent::Log(line) => {
                    if let Some((index, total, title)) = parse_phase_line(&line) {
                        self.phase_index = index;
                        self.phase_total = total.max(1);
                        self.phase_title = title.clone();
                        self.status = format!("{title}...");
                    }
                    self.logs.push(line.clone());
                    self.push_console(line);
                    if self.logs.len() > 500 {
                        let drain_count = self.logs.len() - 500;
                        self.logs.drain(0..drain_count);
                    }
                }
                InstallEvent::Finished { success, code } => {
                    clear_rx = true;
                    self.phase_index = self.phase_total;
                    if success {
                        self.install_state = InstallState::Complete;
                        if self.active_operation == OperationIntent::UpdateDryRun {
                            self.last_update_dry_run_ok = true;
                        }
                        let label = self.operation_label();
                        self.status = format!("{label} completed successfully.");
                        self.push_console(format!("engine: {label} completed successfully"));
                    } else {
                        self.install_state = InstallState::Failed;
                        self.status = format!(
                            "Engine exited unsuccessfully{}.",
                            code.map(|code| format!(" with code {code}"))
                                .unwrap_or_default()
                        );
                        self.push_console(format!("engine: {}", self.status));
                    }
                }
                InstallEvent::Failed(err) => {
                    clear_rx = true;
                    self.install_state = InstallState::Failed;
                    self.status = err.clone();
                    self.logs.push(format!("ENGINE_FAILURE: {err}"));
                    self.push_console(format!("ENGINE_FAILURE: {err}"));
                }
            }
        }

        if clear_rx {
            self.rx = None;
        }
    }

    fn progress(&self) -> f32 {
        if self.phase_total == 0 {
            return 0.0;
        }
        (self.phase_index as f32 / self.phase_total as f32).clamp(0.0, 1.0)
    }

    fn operation_label(&self) -> &'static str {
        match self.active_operation {
            OperationIntent::Install => self.config.execution_mode_label(),
            OperationIntent::UpdateDryRun => "updater dry-run",
            OperationIntent::UpdateApply => "guarded updater apply",
            OperationIntent::Removal => "removal engine",
        }
    }

    fn guarded_local_ack_missing(&self) -> bool {
        !self.config.safety.dry_run
            && self.config.safety.allow_host_mutation
            && !self.guarded_local_ack
    }

    fn guarded_local_ack_message(&self) -> &'static str {
        "Guarded local writes require the Authority acknowledgement."
    }

    fn panel_can_execute(&self) -> Result<(), String> {
        self.config.can_execute()?;
        if self.guarded_local_ack_missing() {
            return Err(self.guarded_local_ack_message().to_owned());
        }

        Ok(())
    }

    fn panel_can_reset(&self) -> Result<(), String> {
        self.config.can_reset()?;
        if self.guarded_local_ack_missing() {
            return Err(self.guarded_local_ack_message().to_owned());
        }

        Ok(())
    }

    fn install_blocker(&self, running: bool) -> Option<String> {
        if running {
            return Some(
                "Engine is already running. Watch the evidence panel for progress.".to_owned(),
            );
        }

        self.panel_can_execute().err()
    }

    fn removal_blocker(&self, running: bool) -> Option<String> {
        if running {
            return Some(
                "Engine is already running. Wait for the current operation to finish.".to_owned(),
            );
        }

        self.panel_can_reset().err()
    }

    fn next_action_label(&self) -> &'static str {
        match self.install_state {
            InstallState::Running => "watch evidence",
            InstallState::Complete if self.config.safety.dry_run => "review receipt",
            InstallState::Complete => "verify install",
            InstallState::Failed => "fix blocker",
            InstallState::Idle if self.guarded_local_ack_missing() => "acknowledge local writes",
            InstallState::Idle if self.logs.is_empty() => "generate plan",
            InstallState::Idle if self.config.safety.dry_run => "run dry-install",
            InstallState::Idle => "install guarded prefix",
        }
    }

    fn run_console_command(&mut self) {
        let command = self.console_input.trim().to_owned();
        self.console_input.clear();

        if command.is_empty() {
            return;
        }

        self.push_console(format!("{} $ {command}", self.terminal_cwd));
        let original_parts: Vec<&str> = command.split_whitespace().collect();
        let normalized = command.to_ascii_lowercase();
        let parts: Vec<&str> = normalized.split_whitespace().collect();

        match parts.as_slice() {
            ["help"] | ["?"] => {
                self.push_console(
                    "panel: help, status, updater status, updater plan, updater dry-run, updater apply, lc commands, lc status, lc install-config, lc profile hosted|panel|host|os|custom, plan, save, dry-run, reset, uninstall, clear, nadia status, nadia commands",
                );
                self.push_console(
                    "nadia: use `nadia commands` for the full Stage-1 through Stage-35 command map",
                );
                self.push_console("panel: profile guided|seal|fedora|custom, seal profile report|sign|aead|hybrid|custom");
                self.push_console("navigation: pwd, cd <path>; external host commands are denied");
            }
            ["status"] => {
                self.push_console(format!("version={PANEL_VERSION} build={PANEL_BUILD}"));
                self.push_console(format!("profile={}", self.config.profile.label()));
                self.push_console(format!("mode={}", self.config.execution_mode_label()));
                self.push_console(format!(
                    "seal_crypto={}",
                    self.config.seal.crypto_profile.label()
                ));
                self.push_console(format!(
                    "latticra_console={}",
                    self.config.components.latticra_console
                ));
                self.push_console(format!("lc_profile={}", self.config.lc.profile.key()));
                self.push_console(format!(
                    "lc_profile_label={}",
                    self.config.lc.profile.label()
                ));
                self.push_console(format!(
                    "nadia_offline_ai={}",
                    self.config.components.nadia_offline_ai
                ));
                self.push_console(format!("install_prefix={}", self.config.install_prefix));
                self.push_console(format!(
                    "updater_source={}",
                    self.config.updater.source_strategy
                ));
                self.push_console(format!(
                    "updater_channel={}",
                    self.config.updater.update_channel
                ));
                self.push_console(
                    "root_authority=0 network_authority=0 runtime_enforcement_authority=0",
                );
            }
            ["updater"] | ["update"] | ["updater", "status"] | ["update", "status"] => {
                self.push_console("updater.panel_owned=1");
                self.push_console(format!(
                    "updater.source_strategy={}",
                    self.config.updater.source_strategy
                ));
                self.push_console(format!(
                    "updater.update_channel={}",
                    self.config.updater.update_channel
                ));
                self.push_console(format!(
                    "updater.require_dry_run_before_apply={}",
                    self.config.updater.require_dry_run_before_apply
                ));
                self.push_console(format!(
                    "updater.last_dry_run_ok={}",
                    self.last_update_dry_run_ok
                ));
                self.push_console(format!(
                    "updater.reuse_installer_engine={}",
                    self.config.updater.reuse_installer_engine
                ));
                self.push_console(format!(
                    "updater.write_update_receipt={}",
                    self.config.updater.write_update_receipt
                ));
                self.push_console(
                    "updater.network_authority=0 root_authority=0 system_mutation_authority=0",
                );
            }
            ["lc"] | ["lc", "status"] | ["console"] | ["console", "status"] => {
                self.push_console("console_name=Latticra Console");
                self.push_console("short_name=LC");
                self.push_console("component_key=latticra_console");
                self.push_console(format!(
                    "component_selected={}",
                    self.config.components.latticra_console
                ));
                self.push_console(format!("profile={}", self.config.lc.profile.key()));
                self.push_console(format!("profile_label={}", self.config.lc.profile.label()));
                self.push_console(format!(
                    "configurable=1 panel_installable=1 panel_console_bridge={}",
                    self.config.lc.panel_bridge
                ));
                self.push_console(format!(
                    "install_profile={}",
                    self.config.lc.install.install_profile
                ));
                self.push_console(format!(
                    "install_mode={}",
                    self.config.lc.install.install_mode
                ));
                self.push_console(format!(
                    "install_config_path={}",
                    self.config.lc.install.config_path
                ));
                self.push_console(format!(
                    "install_share_path={}",
                    self.config.lc.install.share_path
                ));
                self.push_console(format!(
                    "install_command_wrapper={}",
                    self.config.lc.install.command_wrapper
                ));
                self.push_console(format!(
                    "command_registry_profile={}",
                    self.config.lc.command_registry_profile
                ));
                self.push_console(format!(
                    "substrate_bridge_profile={}",
                    self.config.lc.substrate_bridge_profile
                ));
                self.push_console(format!(
                    "host_embedding_profile={}",
                    self.config.lc.host_embedding_profile
                ));
                self.push_console(format!(
                    "host_embedding_contract_profile={}",
                    self.config.lc.host_embedding_contract_profile
                ));
                self.push_console("host_embedding_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "host_inventory_contract_profile={}",
                    self.config.lc.host_inventory_contract_profile
                ));
                self.push_console("host_inventory_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "host_adapter_contract_profile={}",
                    self.config.lc.host_adapter_contract_profile
                ));
                self.push_console("host_adapter_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "receipt_request_contract_profile={}",
                    self.config.lc.receipt_request_contract_profile
                ));
                self.push_console("receipt_request_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "receipt_payload_schema_profile={}",
                    self.config.lc.receipt_payload_schema_profile
                ));
                self.push_console("receipt_payload_schema_status=metadata-only-schema");
                self.push_console(format!(
                    "receipt_payload_artifact_draft_profile={}",
                    self.config.lc.receipt_payload_artifact_draft_profile
                ));
                self.push_console("receipt_payload_artifact_draft_status=metadata-only-draft");
                self.push_console(format!(
                    "receipt_payload_artifact_review_profile={}",
                    self.config.lc.receipt_payload_artifact_review_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_status=metadata-only-review-gate",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_receipt_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_receipt_status=metadata-only-receipt-contract",
                );
                self.push_console(format!(
                    "receipt_payload_materialization_plan_profile={}",
                    self.config.lc.receipt_payload_materialization_plan_profile
                ));
                self.push_console("receipt_payload_materialization_plan_status=metadata-only-plan");
                self.push_console(
                    "draft_review_receipt_present=0 materialization_preconditions_met=0 materialization_allowed=0",
                );
                self.push_console(format!(
                    "signature_request_binding_profile={}",
                    self.config.lc.signature_request_binding_profile
                ));
                self.push_console("signature_request_binding_status=metadata-only-contract");
                self.push_console(format!(
                    "receipt_contract_profile={}",
                    self.config.lc.receipt_contract_profile
                ));
                self.push_console("receipt_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "os_base_contract_profile={}",
                    self.config.lc.os_base_contract_profile
                ));
                self.push_console("os_base_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "vm_evidence_contract_profile={}",
                    self.config.lc.vm_evidence_contract_profile
                ));
                self.push_console("vm_evidence_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "os_base_profile={}",
                    self.config.lc.os_base_profile
                ));
                self.push_console(format!("report_only={}", self.config.lc.report_only));
                self.push_console(format!(
                    "host_embedding_contract_required={}",
                    self.config.lc.require_host_embedding_contract
                ));
                self.push_console(format!(
                    "read_only_host_inventory_contract_required={}",
                    self.config.lc.require_read_only_host_inventory_contract
                ));
                self.push_console(format!(
                    "profile_receipt_required={}",
                    self.config.lc.require_profile_receipt
                ));
                self.push_console(format!(
                    "host_contract_receipt_required={}",
                    self.config.lc.require_host_contract_receipt
                ));
                self.push_console(format!(
                    "host_inventory_receipt_required={}",
                    self.config.lc.require_host_inventory_receipt
                ));
                self.push_console(format!(
                    "host_adapter_contract_required={}",
                    self.config.lc.require_host_adapter_contract
                ));
                self.push_console(format!(
                    "receipt_request_contract_required={}",
                    self.config.lc.require_receipt_request_contract
                ));
                self.push_console(format!(
                    "receipt_payload_schema_required={}",
                    self.config.lc.require_receipt_payload_schema
                ));
                self.push_console(format!(
                    "receipt_payload_artifact_draft_required={}",
                    self.config.lc.require_receipt_payload_artifact_draft
                ));
                self.push_console(format!(
                    "receipt_payload_artifact_review_required={}",
                    self.config.lc.require_receipt_payload_artifact_review
                ));
                self.push_console(format!(
                    "receipt_payload_materialization_plan_required={}",
                    self.config.lc.require_receipt_payload_materialization_plan
                ));
                self.push_console(format!(
                    "signature_request_binding_required={}",
                    self.config.lc.require_signature_request_binding
                ));
                self.push_console(format!(
                    "os_base_contract_required={}",
                    self.config.lc.require_os_base_contract
                ));
                self.push_console(format!(
                    "vm_evidence_contract_required={}",
                    self.config.lc.require_vm_evidence_contract
                ));
                self.push_console(format!(
                    "runtime_boundary_binding_required={}",
                    self.config.lc.require_runtime_boundary_binding
                ));
                self.push_console(format!(
                    "seal_capability_labels_required={}",
                    self.config.lc.require_seal_capability_labels
                ));
                self.push_console(
                    "execution_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "install"]
            | ["lc", "install-config"]
            | ["console", "install"]
            | ["console", "install-config"] => {
                self.push_console("lc.install_config=Latticra Console install configuration");
                self.push_console(format!(
                    "component_selected={}",
                    self.config.components.latticra_console
                ));
                self.push_console(format!(
                    "install_profile={}",
                    self.config.lc.install.install_profile
                ));
                self.push_console(format!(
                    "install_mode={}",
                    self.config.lc.install.install_mode
                ));
                self.push_console(format!(
                    "config_path={}",
                    self.config.lc.install.config_path
                ));
                self.push_console(format!("share_path={}", self.config.lc.install.share_path));
                self.push_console(format!(
                    "command_wrapper={}",
                    self.config.lc.install.command_wrapper
                ));
                self.push_console(format!(
                    "panel_embedded_console={}",
                    self.config.lc.install.panel_embedded_console
                ));
                self.push_console(format!(
                    "write_config_file={}",
                    self.config.lc.install.write_config_file
                ));
                self.push_console(format!(
                    "write_profile_presets={}",
                    self.config.lc.install.write_profile_presets
                ));
                self.push_console(format!(
                    "write_command_registry={}",
                    self.config.lc.install.write_command_registry
                ));
                self.push_console(format!(
                    "write_contract_files={}",
                    self.config.lc.install.write_contract_files
                ));
                self.push_console(format!(
                    "install_user_wrapper={}",
                    self.config.lc.install.install_user_wrapper
                ));
                self.push_console("allow_external_host_commands=false");
                self.push_console(
                    "execution_allowed=0 host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "profiles"] | ["console", "profiles"] => {
                for profile in LatticraConsoleProfile::all() {
                    self.push_console(format!("{}: {}", profile.key(), profile.detail()));
                }
            }
            ["lc", "profile", "hosted"] | ["lc", "profile", "hosted_reference"] => {
                self.apply_lc_profile(LatticraConsoleProfile::HostedReference);
            }
            ["lc", "profile", "panel"] | ["lc", "profile", "panel_embedded"] => {
                self.apply_lc_profile(LatticraConsoleProfile::PanelEmbedded);
            }
            ["lc", "profile", "host"] | ["lc", "profile", "host_embedded_planning"] => {
                self.apply_lc_profile(LatticraConsoleProfile::HostEmbeddedPlanning);
            }
            ["lc", "profile", "os"] | ["lc", "profile", "os_base_planning"] => {
                self.apply_lc_profile(LatticraConsoleProfile::OsBasePlanning);
            }
            ["lc", "profile", "custom"] => {
                self.apply_lc_profile(LatticraConsoleProfile::Custom);
            }
            ["lc", "commands"] | ["console", "commands"] => {
                self.push_console("lc.commands=help,status,plan,save,dry-run,reset,uninstall,pwd,cd,lc status,lc commands,lc install-config,lc profiles,lc receipts,lc receipt-request,lc receipt-payload,lc receipt-artifact,lc receipt-artifact-review,lc receipt-review-receipt,lc receipt-materialization-plan,lc signature-request,lc substrate,lc host,lc host-contract,lc host-inventory,lc host-adapter,lc os-contract,lc vm-evidence,lc os");
                self.push_console("registry_authority=metadata-only external_host_processes=0");
            }
            ["lc", "receipts"]
            | ["console", "receipts"]
            | ["lc", "receipt-contract"]
            | ["console", "receipt-contract"] => {
                self.push_console("lc.receipt_contract=Latticra Console receipt contract");
                self.push_console(format!(
                    "receipt_profile={}",
                    self.config.lc.receipt_contract_profile
                ));
                self.push_console("receipt_contract_status=metadata-only");
                self.push_console(format!(
                    "profile_receipt_required={}",
                    self.config.lc.require_profile_receipt
                ));
                self.push_console(format!(
                    "host_contract_receipt_required={}",
                    self.config.lc.require_host_contract_receipt
                ));
                self.push_console(format!(
                    "host_inventory_receipt_required={}",
                    self.config.lc.require_host_inventory_receipt
                ));
                self.push_console(format!(
                    "host_adapter_contract_required={}",
                    self.config.lc.require_host_adapter_contract
                ));
                self.push_console(format!(
                    "receipt_request_contract_required={}",
                    self.config.lc.require_receipt_request_contract
                ));
                self.push_console(format!(
                    "receipt_payload_schema_required={}",
                    self.config.lc.require_receipt_payload_schema
                ));
                self.push_console("receipt_payload_schema_command=lc receipt-payload");
                self.push_console(format!(
                    "receipt_payload_artifact_draft_required={}",
                    self.config.lc.require_receipt_payload_artifact_draft
                ));
                self.push_console("receipt_payload_artifact_draft_command=lc receipt-artifact");
                self.push_console(format!(
                    "receipt_payload_artifact_review_required={}",
                    self.config.lc.require_receipt_payload_artifact_review
                ));
                self.push_console("receipt_payload_artifact_review_present=1");
                self.push_console("draft_review_receipt_present=0");
                self.push_console(
                    "receipt_payload_artifact_review_command=lc receipt-artifact-review",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_receipt_required={}",
                    self.config
                        .lc
                        .require_receipt_payload_artifact_review_receipt
                ));
                self.push_console("receipt_payload_artifact_review_receipt_present=1");
                self.push_console(
                    "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt",
                );
                self.push_console(format!(
                    "receipt_payload_materialization_plan_required={}",
                    self.config.lc.require_receipt_payload_materialization_plan
                ));
                self.push_console("receipt_payload_materialization_plan_present=1");
                self.push_console(
                    "receipt_payload_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console(format!(
                    "signature_request_binding_required={}",
                    self.config.lc.require_signature_request_binding
                ));
                self.push_console("signature_request_binding_command=lc signature-request");
                self.push_console(
                    "receipt_request_command=lc receipt-request seal_signature_request_present=0",
                );
                self.push_console(
                    "seal_signature_present=0 seal_signing_authority_present=0 receipt_signed=0",
                );
                self.push_console(
                    "file_write_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "receipt-request"]
            | ["console", "receipt-request"]
            | ["lc", "seal-receipt-request"]
            | ["console", "seal-receipt-request"] => {
                self.push_console(
                    "lc.receipt_request_contract=Latticra Console Seal receipt request contract",
                );
                self.push_console(format!(
                    "request_profile={}",
                    self.config.lc.receipt_request_contract_profile
                ));
                self.push_console(format!(
                    "request_contract_required={}",
                    self.config.lc.require_receipt_request_contract
                ));
                self.push_console(format!(
                    "receipt_contract_profile={}",
                    self.config.lc.receipt_contract_profile
                ));
                self.push_console(format!(
                    "receipt_payload_schema_profile={}",
                    self.config.lc.receipt_payload_schema_profile
                ));
                self.push_console("receipt_payload_schema_required=1");
                self.push_console(format!(
                    "receipt_payload_artifact_draft_profile={}",
                    self.config.lc.receipt_payload_artifact_draft_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_draft_required=1 receipt_payload_artifact_draft_present=1",
                );
                self.push_console("receipt_payload_artifact_draft_command=lc receipt-artifact");
                self.push_console(format!(
                    "receipt_payload_artifact_review_profile={}",
                    self.config.lc.receipt_payload_artifact_review_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_required=1 receipt_payload_artifact_review_present=1",
                );
                self.push_console(
                    "receipt_payload_artifact_review_command=lc receipt-artifact-review",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_receipt_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_receipt_required=1 receipt_payload_artifact_review_receipt_present=1",
                );
                self.push_console(
                    "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt",
                );
                self.push_console(format!(
                    "receipt_payload_materialization_plan_profile={}",
                    self.config.lc.receipt_payload_materialization_plan_profile
                ));
                self.push_console(
                    "receipt_payload_materialization_plan_required=1 receipt_payload_materialization_plan_present=1",
                );
                self.push_console(
                    "receipt_payload_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console(
                    "draft_review_receipt_present=0 materialization_preconditions_met=0 materialization_allowed=0",
                );
                self.push_console("payload_artifact_present=0 payload_materialized=0");
                self.push_console(format!(
                    "signature_request_binding_profile={}",
                    self.config.lc.signature_request_binding_profile
                ));
                self.push_console("signature_request_binding_required=1 signature_request_binding_artifact_present=0");
                self.push_console("signature_request_profile=latticra-seal-signature-request/0.1");
                self.push_console("requested_receipt_profile=latticra-seal-verified-receipt/0.1");
                self.push_console("requested_capability=verified-receipt-report");
                self.push_console("seal_signature_request_ready=0 seal_signature_request_present=0 seal_signing_authority_present=0");
                self.push_console("seal_signer_handoff_allowed=0 seal_signing_operation_allowed=0 receipt_write_allowed=0 receipt_signed=0");
                self.push_console(
                    "file_write_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "receipt-payload"]
            | ["console", "receipt-payload"]
            | ["lc", "receipt-payload-schema"]
            | ["console", "receipt-payload-schema"]
            | ["lc", "payload-schema"]
            | ["console", "payload-schema"] => {
                self.push_console(
                    "lc.receipt_payload_schema=Latticra Console receipt payload schema",
                );
                self.push_console(format!(
                    "schema_profile={}",
                    self.config.lc.receipt_payload_schema_profile
                ));
                self.push_console(format!(
                    "schema_required={}",
                    self.config.lc.require_receipt_payload_schema
                ));
                self.push_console(format!(
                    "receipt_request_profile={}",
                    self.config.lc.receipt_request_contract_profile
                ));
                self.push_console(format!(
                    "receipt_contract_profile={}",
                    self.config.lc.receipt_contract_profile
                ));
                self.push_console("payload_fields=console_id,profile,command_registry,host_contract,host_inventory,host_adapter,runtime_boundary,seal_capability_labels,authority_denials");
                self.push_console(
                    "payload_artifact_present=0 payload_hash_computed=0 payload_path_recorded=0",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_draft_profile={}",
                    self.config.lc.receipt_payload_artifact_draft_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_draft_present=1 receipt_payload_artifact_draft_command=lc receipt-artifact",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_profile={}",
                    self.config.lc.receipt_payload_artifact_review_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_present=1 receipt_payload_artifact_review_command=lc receipt-artifact-review",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_receipt_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_receipt_present=1 receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt",
                );
                self.push_console(format!(
                    "receipt_payload_materialization_plan_profile={}",
                    self.config.lc.receipt_payload_materialization_plan_profile
                ));
                self.push_console(
                    "receipt_payload_materialization_plan_present=1 receipt_payload_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console("materialization_preconditions_met=0 materialization_allowed=0");
                self.push_console(
                    "signature_request_binding_present=0 signature_request_binding_allowed=0",
                );
                self.push_console(
                    "signature_request_binding_contract_present=1 signature_request_binding_command=lc signature-request",
                );
                self.push_console("seal_signature_request_ready=0 seal_signature_request_present=0 receipt_write_allowed=0 receipt_signed=0");
                self.push_console(
                    "file_write_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "receipt-artifact"]
            | ["console", "receipt-artifact"]
            | ["lc", "receipt-payload-artifact"]
            | ["console", "receipt-payload-artifact"]
            | ["lc", "payload-artifact"]
            | ["console", "payload-artifact"]
            | ["lc", "receipt-artifact-draft"]
            | ["console", "receipt-artifact-draft"] => {
                self.push_console(
                    "lc.receipt_payload_artifact_draft=Latticra Console receipt payload artifact draft",
                );
                self.push_console(format!(
                    "draft_profile={}",
                    self.config.lc.receipt_payload_artifact_draft_profile
                ));
                self.push_console("draft_status=metadata-only draft_contract_present=1");
                self.push_console(format!(
                    "receipt_payload_artifact_review_profile={}",
                    self.config.lc.receipt_payload_artifact_review_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_present=1 receipt_payload_artifact_review_command=lc receipt-artifact-review",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_receipt_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_receipt_present=1 receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt",
                );
                self.push_console(format!(
                    "receipt_payload_materialization_plan_profile={}",
                    self.config.lc.receipt_payload_materialization_plan_profile
                ));
                self.push_console(
                    "receipt_payload_materialization_plan_present=1 receipt_payload_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console("draft_review_required=1 draft_review_present=0");
                self.push_console("draft_review_receipt_required=1 draft_review_receipt_present=0");
                self.push_console(
                    "draft_review_approval_recorded=0 materialization_preconditions_met=0 materialization_allowed=0",
                );
                self.push_console(format!(
                    "receipt_request_profile={}",
                    self.config.lc.receipt_request_contract_profile
                ));
                self.push_console(format!(
                    "receipt_payload_schema_profile={}",
                    self.config.lc.receipt_payload_schema_profile
                ));
                self.push_console(format!(
                    "signature_request_binding_profile={}",
                    self.config.lc.signature_request_binding_profile
                ));
                self.push_console("canonicalization_profile=lc-receipt-payload-canonical-text-v0");
                self.push_console("artifact_fields=console_id,profile,command_registry,host_contract,host_inventory,host_adapter,runtime_boundary,seal_capability_labels,authority_denials");
                self.push_console(
                    "receipt_payload_artifact_draft_present=1 payload_artifact_present=0 payload_materialized=0",
                );
                self.push_console(
                    "payload_write_allowed=0 payload_hash_computed=0 payload_hash_recorded=0 payload_path_recorded=0",
                );
                self.push_console(
                    "signature_request_binding_artifact_present=0 signature_request_binding_allowed=0",
                );
                self.push_console(
                    "seal_signature_request_ready=0 seal_signature_request_present=0 seal_signing_authority_present=0",
                );
                self.push_console(
                    "receipt_write_allowed=0 receipt_signed=0 command_surface=lc receipt-artifact",
                );
                self.push_console("related_review_command=lc receipt-artifact-review");
                self.push_console(
                    "related_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console(
                    "file_write_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "receipt-artifact-review"]
            | ["console", "receipt-artifact-review"]
            | ["lc", "receipt-review"]
            | ["console", "receipt-review"]
            | ["lc", "artifact-review"]
            | ["console", "artifact-review"]
            | ["lc", "payload-artifact-review"]
            | ["console", "payload-artifact-review"] => {
                self.push_console(
                    "lc.receipt_payload_artifact_review_gate=Latticra Console receipt payload artifact review gate",
                );
                self.push_console(format!(
                    "review_profile={}",
                    self.config.lc.receipt_payload_artifact_review_profile
                ));
                self.push_console("review_status=metadata-only review_gate_present=1");
                self.push_console(format!(
                    "receipt_payload_artifact_draft_profile={}",
                    self.config.lc.receipt_payload_artifact_draft_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_draft_present=1 receipt_payload_artifact_draft_command=lc receipt-artifact",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_receipt_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_receipt_required=1 receipt_payload_artifact_review_receipt_present=1",
                );
                self.push_console(
                    "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt",
                );
                self.push_console(format!(
                    "receipt_payload_materialization_plan_profile={}",
                    self.config.lc.receipt_payload_materialization_plan_profile
                ));
                self.push_console(
                    "receipt_payload_materialization_plan_present=1 receipt_payload_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console("draft_review_required=1 draft_review_present=0");
                self.push_console("draft_review_receipt_required=1 draft_review_receipt_present=0");
                self.push_console(
                    "draft_review_approval_recorded=0 draft_reviewer_identity_recorded=0 draft_review_timestamp_recorded=0",
                );
                self.push_console(
                    "materialization_plan_required=1 materialization_preconditions_met=0",
                );
                self.push_console(
                    "materialization_allowed=0 payload_artifact_present=0 payload_materialized=0 payload_write_allowed=0",
                );
                self.push_console(
                    "payload_hash_computed=0 payload_hash_recorded=0 payload_path_recorded=0",
                );
                self.push_console(
                    "signature_request_binding_allowed=0 signature_request_binding_artifact_present=0",
                );
                self.push_console(
                    "seal_signature_request_ready=0 seal_signature_request_present=0 seal_signing_authority_present=0",
                );
                self.push_console("receipt_write_allowed=0 receipt_signed=0");
                self.push_console(
                    "promotion_gate=lc_receipt_payload_artifact_review_before_materialization",
                );
                self.push_console("command_surface=lc receipt-artifact-review");
                self.push_console(
                    "related_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console(
                    "file_write_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "receipt-review-receipt"]
            | ["console", "receipt-review-receipt"]
            | ["lc", "artifact-review-receipt"]
            | ["console", "artifact-review-receipt"]
            | ["lc", "payload-artifact-review-receipt"]
            | ["console", "payload-artifact-review-receipt"]
            | ["lc", "receipt-payload-artifact-review-receipt"]
            | ["console", "receipt-payload-artifact-review-receipt"] => {
                self.push_console(
                    "lc.receipt_payload_artifact_review_receipt=Latticra Console receipt payload artifact review receipt contract",
                );
                self.push_console(format!(
                    "review_receipt_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_profile
                ));
                self.push_console(
                    "review_receipt_status=metadata-only-contract review_receipt_contract_present=1",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_profile={}",
                    self.config.lc.receipt_payload_artifact_review_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_required=1 receipt_payload_artifact_review_present=1",
                );
                self.push_console(
                    "receipt_payload_artifact_review_command=lc receipt-artifact-review",
                );
                self.push_console(format!(
                    "receipt_payload_materialization_plan_profile={}",
                    self.config.lc.receipt_payload_materialization_plan_profile
                ));
                self.push_console(
                    "receipt_payload_materialization_plan_required=1 receipt_payload_materialization_plan_present=1",
                );
                self.push_console(
                    "receipt_payload_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console(
                    "draft_review_required=1 draft_review_present=0 draft_review_receipt_required=1 draft_review_receipt_present=0",
                );
                self.push_console(
                    "draft_review_receipt_artifact_present=0 draft_review_receipt_write_allowed=0 draft_review_receipt_signed=0",
                );
                self.push_console(
                    "draft_review_receipt_hash_recorded=0 draft_review_receipt_path_recorded=0",
                );
                self.push_console(
                    "draft_review_approval_recorded=0 draft_reviewer_identity_recorded=0 draft_review_timestamp_recorded=0",
                );
                self.push_console("materialization_preconditions_met=0 materialization_allowed=0");
                self.push_console(
                    "payload_artifact_present=0 payload_materialized=0 payload_write_allowed=0",
                );
                self.push_console(
                    "signature_request_binding_allowed=0 signature_request_binding_artifact_present=0",
                );
                self.push_console(
                    "seal_signature_request_ready=0 seal_signature_request_present=0 seal_signing_authority_present=0",
                );
                self.push_console("receipt_write_allowed=0 receipt_signed=0");
                self.push_console(
                    "promotion_gate=lc_receipt_payload_artifact_review_receipt_before_materialization_preconditions",
                );
                self.push_console("command_surface=lc receipt-review-receipt");
                self.push_console("related_review_command=lc receipt-artifact-review");
                self.push_console(
                    "related_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console(
                    "file_write_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "receipt-materialization-plan"]
            | ["console", "receipt-materialization-plan"]
            | ["lc", "materialization-plan"]
            | ["console", "materialization-plan"]
            | ["lc", "payload-materialization-plan"]
            | ["console", "payload-materialization-plan"]
            | ["lc", "receipt-payload-materialization-plan"]
            | ["console", "receipt-payload-materialization-plan"] => {
                self.push_console(
                    "lc.receipt_payload_materialization_plan=Latticra Console receipt payload materialization plan",
                );
                self.push_console(format!(
                    "materialization_plan_profile={}",
                    self.config.lc.receipt_payload_materialization_plan_profile
                ));
                self.push_console(
                    "materialization_plan_status=metadata-only materialization_plan_present=1",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_profile={}",
                    self.config.lc.receipt_payload_artifact_review_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_required=1 receipt_payload_artifact_review_present=1",
                );
                self.push_console(
                    "receipt_payload_artifact_review_command=lc receipt-artifact-review",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_receipt_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_receipt_required=1 receipt_payload_artifact_review_receipt_present=1",
                );
                self.push_console(
                    "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt",
                );
                self.push_console(
                    "draft_review_receipt_required=1 draft_review_receipt_present=0 draft_review_approval_recorded=0",
                );
                self.push_console(
                    "materialization_preconditions_met=0 materialization_allowed=0 materialization_execution_planned=0",
                );
                self.push_console(
                    "payload_artifact_present=0 payload_materialized=0 payload_write_allowed=0 payload_file_open_allowed=0",
                );
                self.push_console(
                    "payload_hash_computed=0 payload_hash_recorded=0 payload_path_recorded=0",
                );
                self.push_console(
                    "signature_request_binding_allowed=0 signature_request_binding_artifact_present=0",
                );
                self.push_console(
                    "seal_signature_request_ready=0 seal_signature_request_present=0 seal_signing_authority_present=0",
                );
                self.push_console("receipt_write_allowed=0 receipt_signed=0");
                self.push_console(
                    "promotion_gate=lc_receipt_payload_materialization_plan_after_review_receipt",
                );
                self.push_console("command_surface=lc receipt-materialization-plan");
                self.push_console("related_review_command=lc receipt-artifact-review");
                self.push_console(
                    "file_write_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "signature-request"]
            | ["console", "signature-request"]
            | ["lc", "receipt-signature-request"]
            | ["console", "receipt-signature-request"]
            | ["lc", "signature-request-binding"]
            | ["console", "signature-request-binding"] => {
                self.push_console(
                    "lc.signature_request_binding=Latticra Console signature request binding contract",
                );
                self.push_console(format!(
                    "binding_profile={}",
                    self.config.lc.signature_request_binding_profile
                ));
                self.push_console(format!(
                    "binding_required={}",
                    self.config.lc.require_signature_request_binding
                ));
                self.push_console(format!(
                    "receipt_payload_schema_profile={}",
                    self.config.lc.receipt_payload_schema_profile
                ));
                self.push_console(format!(
                    "receipt_payload_artifact_draft_profile={}",
                    self.config.lc.receipt_payload_artifact_draft_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_draft_present=1 receipt_payload_artifact_draft_command=lc receipt-artifact",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_profile={}",
                    self.config.lc.receipt_payload_artifact_review_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_present=1 receipt_payload_artifact_review_command=lc receipt-artifact-review",
                );
                self.push_console(format!(
                    "receipt_payload_artifact_review_receipt_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_receipt_required=1 receipt_payload_artifact_review_receipt_present=1",
                );
                self.push_console(
                    "receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt",
                );
                self.push_console(format!(
                    "receipt_payload_materialization_plan_profile={}",
                    self.config.lc.receipt_payload_materialization_plan_profile
                ));
                self.push_console(
                    "receipt_payload_materialization_plan_required=1 receipt_payload_materialization_plan_present=1",
                );
                self.push_console(
                    "receipt_payload_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console(
                    "draft_review_receipt_present=0 materialization_preconditions_met=0 materialization_allowed=0",
                );
                self.push_console("payload_artifact_present=0");
                self.push_console("signature_request_profile=latticra-seal-signature-request/0.1");
                self.push_console(
                    "signing_authorization_profile=latticra-seal-signing-authorization/0.1",
                );
                self.push_console("requested_signature=Ed25519-development requested_signing_authorization=metadata-only");
                self.push_console(
                    "signature_request_binding_artifact_present=0 signature_request_binding_allowed=0",
                );
                self.push_console("seal_signature_request_ready=0 seal_signature_request_present=0 seal_signing_authority_present=0");
                self.push_console("seal_signer_handoff_allowed=0 seal_signing_operation_allowed=0 receipt_write_allowed=0 receipt_signed=0");
                self.push_console(
                    "file_write_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "substrate"] | ["console", "substrate"] => {
                self.push_console("lc.substrate_bridge=Latticra substrate metadata bridge");
                self.push_console(
                    "linked_surfaces=Lat,LIR,Nucleus,Runtime Boundary,Seal,Panel,Nadia",
                );
                self.push_console("effect_boundary=no-effect runtime_enforcement_authority=0");
            }
            ["lc", "host"] | ["console", "host"] => {
                self.push_console(format!(
                    "lc.host_embedding={}",
                    self.config.lc.host_embedding_profile
                ));
                self.push_console(format!(
                    "host_adapter_contract={}",
                    self.config.lc.host_adapter_contract_profile
                ));
                self.push_console("host_embedded_now=0 host_mutation_allowed=0 file_io_allowed=0");
                self.push_console("future_host_role=embed-within-host-after-gates");
            }
            ["lc", "host-contract"]
            | ["console", "host-contract"]
            | ["lc", "host", "contract"]
            | ["console", "host", "contract"] => {
                self.push_console(
                    "lc.host_embedding_contract=Latticra Console host embedding contract",
                );
                self.push_console(format!(
                    "contract_profile={}",
                    self.config.lc.host_embedding_contract_profile
                ));
                self.push_console(format!(
                    "contract_required={}",
                    self.config.lc.require_host_embedding_contract
                ));
                self.push_console("contract_status=metadata-only host_embedded_now=0");
                self.push_console("host_process_launch_allowed=0 host_file_read_allowed=0 host_file_write_allowed=0");
                self.push_console(
                    "host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "host-inventory"]
            | ["console", "host-inventory"]
            | ["lc", "host", "inventory"]
            | ["console", "host", "inventory"] => {
                self.push_console(
                    "lc.host_inventory_contract=Latticra Console read-only host inventory contract",
                );
                self.push_console(format!(
                    "contract_profile={}",
                    self.config.lc.host_inventory_contract_profile
                ));
                self.push_console(format!(
                    "contract_required={}",
                    self.config.lc.require_read_only_host_inventory_contract
                ));
                self.push_console("contract_status=metadata-only inventory_performed=0");
                self.push_console(
                    "host_probe_allowed=0 host_file_read_allowed=0 host_file_write_allowed=0",
                );
                self.push_console("host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0");
            }
            ["lc", "host-adapter"]
            | ["console", "host-adapter"]
            | ["lc", "host", "adapter"]
            | ["console", "host", "adapter"]
            | ["lc", "adapter-contract"]
            | ["console", "adapter-contract"] => {
                self.push_console(
                    "lc.host_adapter_contract=Latticra Console host adapter contract",
                );
                self.push_console(format!(
                    "contract_profile={}",
                    self.config.lc.host_adapter_contract_profile
                ));
                self.push_console(format!(
                    "contract_required={}",
                    self.config.lc.require_host_adapter_contract
                ));
                self.push_console("contract_status=metadata-only host_adapter_enabled=0");
                self.push_console("host_adapter_present=0 host_adapter_loaded=0 adapter_api_status=planned adapter_abi_status=planned");
                self.push_console(
                    "host_embedding_contract_receipt_required=1 host_inventory_contract_receipt_required=1",
                );
                self.push_console(
                    "host_process_launch_allowed=0 host_probe_allowed=0 host_file_read_allowed=0 host_file_write_allowed=0",
                );
                self.push_console(
                    "host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "os-contract"]
            | ["console", "os-contract"]
            | ["lc", "os", "contract"]
            | ["console", "os", "contract"]
            | ["lc", "base-contract"]
            | ["console", "base-contract"] => {
                self.push_console("lc.os_base_contract=Latticra Console OS-base planning contract");
                self.push_console(format!(
                    "contract_profile={}",
                    self.config.lc.os_base_contract_profile
                ));
                self.push_console(format!(
                    "contract_required={}",
                    self.config.lc.require_os_base_contract
                ));
                self.push_console("contract_status=metadata-only os_base_enabled=0");
                self.push_console(
                    "boot_authority_present=0 kernel_change_allowed=0 hardware_access_allowed=0",
                );
                self.push_console(
                    "bootloader_write_allowed=0 partition_mutation_allowed=0 driver_load_allowed=0 service_install_allowed=0",
                );
                self.push_console(
                    "vm_evidence_contract_required=1 vm_evidence_required=1 receipt_required_before_os_base=1 promotion_gate=os_base_contract_receipt_and_vm_evidence",
                );
                self.push_console(
                    "host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "vm-evidence"]
            | ["console", "vm-evidence"]
            | ["lc", "vm", "evidence"]
            | ["console", "vm", "evidence"]
            | ["lc", "vm-contract"]
            | ["console", "vm-contract"] => {
                self.push_console("lc.vm_evidence_contract=Latticra Console VM evidence contract");
                self.push_console(format!(
                    "contract_profile={}",
                    self.config.lc.vm_evidence_contract_profile
                ));
                self.push_console(format!(
                    "contract_required={}",
                    self.config.lc.require_vm_evidence_contract
                ));
                self.push_console("contract_status=metadata-only vm_evidence_capture_enabled=0");
                self.push_console(
                    "vm_launcher_present=0 vm_launch_allowed=0 hypervisor_access_allowed=0",
                );
                self.push_console(
                    "disk_image_open_allowed=0 disk_image_write_allowed=0 snapshot_capture_allowed=0",
                );
                self.push_console(
                    "guest_agent_allowed=0 guest_network_allowed=0 host_probe_allowed=0",
                );
                self.push_console(
                    "promotion_gate=vm_evidence_contract_before_boot_adjacency receipt_required_before_vm_evidence=1",
                );
                self.push_console(
                    "host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "os"] | ["console", "os"] | ["lc", "base"] | ["console", "base"] => {
                self.push_console(format!(
                    "lc.os_base_status={}",
                    self.config.lc.os_base_profile
                ));
                self.push_console(format!(
                    "os_base_contract={}",
                    self.config.lc.os_base_contract_profile
                ));
                self.push_console(format!(
                    "vm_evidence_contract={}",
                    self.config.lc.vm_evidence_contract_profile
                ));
                self.push_console("future_os_base_claim=planned_not_claimed");
                self.push_console(
                    "boot_allowed=0 kernel_enforcement_authority=0 production_os_claim=0",
                );
            }
            ["nadia", "commands"] | ["nadia", "help"] | ["nadia", "?"] => {
                self.push_nadia_commands();
            }
            ["nadia"] | ["nadia", "status"] => {
                self.push_console("name=Nadia");
                self.push_console("system_name=Latticra Nadia Witness Foundation");
                self.push_console("public_name=Nadia");
                self.push_console("interactive_name=Nadia");
                self.push_console("implementation_name=Nadia Witness Foundation");
                self.push_console("documentation_code_name=Nadia Witness Foundation");
                self.push_console(format!(
                    "component_selected={}",
                    self.config.components.nadia_offline_ai
                ));
                self.push_console("human_dignity_principle=1 community_awareness_posture=1");
                self.push_console("context_engine_stage=1-local-context-engine");
                self.push_console("runtime_profile_stage=2-runtime-profile-boundary");
                self.push_console("developer_workbench_stage=3-developer-workbench-planning");
                self.push_console(
                    "systems_engineering_mode_stage=4-systems-engineering-mode-validation",
                );
                self.push_console("productivity_loop_stage=5-productivity-ledger-loop");
                self.push_console("protective_safety_stage=6-protective-safety-boundary");
                self.push_console("tool_authority_stage=7-guarded-tool-authority-preflight");
                self.push_console("prompt_evaluation_contract_stage=8-prompt-evaluation-contract");
                self.push_console(
                    "local_model_registry_contract_stage=9-local-model-registry-contract",
                );
                self.push_console(
                    "inference_readiness_contract_stage=10-inference-readiness-contract",
                );
                self.push_console(
                    "runtime_invocation_contract_stage=11-runtime-invocation-contract",
                );
                self.push_console("model_load_contract_stage=12-model-load-contract");
                self.push_console("prompt_receipt_contract_stage=13-prompt-receipt-contract");
                self.push_console(
                    "prompt_materialization_contract_stage=14-prompt-materialization-contract",
                );
                self.push_console(
                    "awareness_dialogue_contract_stage=15-awareness-dialogue-contract",
                );
                self.push_console(
                    "prompt_evaluation_handoff_contract_stage=16-prompt-evaluation-handoff-contract",
                );
                self.push_console(
                    "tokenization_boundary_contract_stage=17-tokenization-boundary-contract",
                );
                self.push_console(
                    "tokenizer_specification_contract_stage=18-tokenizer-specification-contract",
                );
                self.push_console(
                    "tokenizer_manifest_contract_stage=19-tokenizer-manifest-contract",
                );
                self.push_console(
                    "tokenizer_artifact_inventory_contract_stage=20-tokenizer-artifact-inventory-contract",
                );
                self.push_console(
                    "tokenizer_artifact_measurement_contract_stage=21-tokenizer-artifact-measurement-contract",
                );
                self.push_console(
                    "tokenizer_artifact_verification_contract_stage=22-tokenizer-artifact-verification-contract",
                );
                self.push_console(
                    "tokenizer_artifact_binding_contract_stage=23-tokenizer-artifact-binding-contract",
                );
                self.push_console(
                    "tokenizer_runtime_attachment_contract_stage=24-tokenizer-runtime-attachment-contract",
                );
                self.push_console(
                    "prompt_tokenization_contract_stage=25-prompt-tokenization-contract",
                );
                self.push_console(
                    "prompt_token_sequence_contract_stage=26-prompt-token-sequence-contract",
                );
                self.push_console(
                    "context_window_assembly_contract_stage=27-context-window-assembly-contract",
                );
                self.push_console(
                    "prompt_evaluation_input_contract_stage=28-prompt-evaluation-input-contract",
                );
                self.push_console(
                    "prompt_evaluation_runtime_handoff_contract_stage=29-prompt-evaluation-runtime-handoff-contract",
                );
                self.push_console(
                    "prompt_evaluation_invocation_contract_stage=30-prompt-evaluation-invocation-contract",
                );
                self.push_console(
                    "prompt_evaluation_result_contract_stage=31-prompt-evaluation-result-contract",
                );
                self.push_console(
                    "prompt_evaluation_result_review_contract_stage=32-prompt-evaluation-result-review-contract",
                );
                self.push_console(
                    "prompt_evaluation_result_disposition_contract_stage=33-prompt-evaluation-result-disposition-contract",
                );
                self.push_console(
                    "prompt_evaluation_result_release_contract_stage=34-prompt-evaluation-result-release-contract",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_contract_stage=35-prompt-evaluation-result-release-receipt-contract",
                );
                self.push_console(
                    "stage=35 prompt-evaluation-result-release-receipt-contract; prompt_evaluation_result_release_receipt_record_created=0 prompt_evaluation_result_release_receipt_signed=0 runtime_invoked=0",
                );
                self.push_console(
                    "network_authority=0 tool_execution_authority=0 self_modification_authority=0",
                );
            }
            ["nadia", "context"] | ["nadia", "context-pack"] => {
                self.push_console("nadia_context_engine=stage-1-local-context-pack");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia context-pack");
                self.push_console(
                    "network_authority=0 model_runtime_present=0 source_mutation_authority=0",
                );
            }
            ["nadia", "runtime"] | ["nadia", "runtime-profile"] => {
                self.push_console("nadia_runtime_profile=stage-2-runtime-profile-boundary");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia runtime-profile");
                self.push_console("runtime_family=llama.cpp-compatible model_format=gguf");
                self.push_console(
                    "model_runtime_invoked=0 inference_performed=0 prompt_evaluated=0",
                );
            }
            ["nadia", "runtime-invocation"]
            | ["nadia", "invocation"]
            | ["nadia", "runtime-contract"] => {
                self.push_console("nadia_runtime_invocation=stage-11-runtime-invocation-contract");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia runtime-invocation");
                self.push_console(
                    "runtime_invocation_contract_status=contract_only runtime_invocation_allowed=0",
                );
                self.push_console(
                    "runtime_process_spawn_authority=0 runtime_session_authority=0 token_generation_authority=0",
                );
                self.push_console(
                    "runtime_process_spawned=0 runtime_session_created=0 inference_performed=0",
                );
            }
            ["nadia", "model-load"] | ["nadia", "load"] | ["nadia", "model-load-contract"] => {
                self.push_console("nadia_model_load=stage-12-model-load-contract");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia model-load");
                self.push_console("model_load_contract_status=contract_only model_loaded=0");
                self.push_console(
                    "model_file_open_authority=0 model_weight_mapping_authority=0 model_load_authority=0",
                );
                self.push_console(
                    "model_file_opened=0 model_weights_mapped=0 model_weights_loaded=0",
                );
            }
            ["nadia", "prompt-receipt"]
            | ["nadia", "receipt"]
            | ["nadia", "prompt-receipt-contract"] => {
                self.push_console("nadia_prompt_receipt=stage-13-prompt-receipt-contract");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-receipt");
                self.push_console("prompt_receipt_contract_status=contract_only prompt_received=0");
                self.push_console(
                    "prompt_source_open_authority=0 prompt_source_read_authority=0 prompt_text_materialization_authority=0",
                );
                self.push_console(
                    "prompt_text_received=0 prompt_text_materialized=0 prompt_evaluated=0",
                );
            }
            ["nadia", "prompt-materialization"]
            | ["nadia", "materialization"]
            | ["nadia", "prompt-materialization-contract"] => {
                self.push_console(
                    "nadia_prompt_materialization=stage-14-prompt-materialization-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-materialization");
                self.push_console(
                    "prompt_materialization_contract_status=contract_only prompt_materialized=0",
                );
                self.push_console(
                    "prompt_buffer_allocation_authority=0 prompt_buffer_write_authority=0 prompt_tokenization_authority=0",
                );
                self.push_console(
                    "prompt_buffer_allocated=0 prompt_tokenized=0 inference_performed=0",
                );
            }
            ["nadia", "awareness-dialogue"] | ["nadia", "awareness"] | ["nadia", "dialogue"] => {
                self.push_console("nadia_awareness_dialogue=stage-15-awareness-dialogue-contract");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia awareness-dialogue");
                self.push_console(
                    "awareness_dialogue_contract_status=contract_only qa_dialogue_generated=0",
                );
                self.push_console(
                    "dialogue_scope=official-nadia-initiative-awareness-work q_and_a_format_required=1",
                );
                self.push_console(
                    "sexualized_dialogue_generation=0 graphic_sexual_detail_allowed=0 inference_performed=0",
                );
            }
            ["nadia", "prompt-evaluation-handoff"]
            | ["nadia", "evaluation-handoff"]
            | ["nadia", "prompt-eval-handoff"] => {
                self.push_console(
                    "nadia_prompt_evaluation_handoff=stage-16-prompt-evaluation-handoff-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-evaluation-handoff");
                self.push_console(
                    "prompt_evaluation_handoff_contract_status=contract_only prompt_evaluated=0",
                );
                self.push_console(
                    "requires_awareness_dialogue_contract=1 requires_future_tokenization_contract=1",
                );
                self.push_console(
                    "qa_dialogue_generated=0 token_generation_performed=0 inference_performed=0",
                );
            }
            ["nadia", "tokenization-boundary"]
            | ["nadia", "tokenization"]
            | ["nadia", "tokenization-contract"] => {
                self.push_console(
                    "nadia_tokenization_boundary=stage-17-tokenization-boundary-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia tokenization-boundary");
                self.push_console(
                    "tokenization_boundary_contract_status=contract_only prompt_tokenized=0",
                );
                self.push_console(
                    "tokenizer_file_opened=0 tokenizer_vocab_loaded=0 prompt_evaluated=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_handoff_contract=1 requires_future_tokenizer_specification_contract=1",
                );
            }
            ["nadia", "tokenizer-specification"]
            | ["nadia", "tokenizer-spec"]
            | ["nadia", "tokenizer-spec-contract"] => {
                self.push_console(
                    "nadia_tokenizer_specification=stage-18-tokenizer-specification-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia tokenizer-specification");
                self.push_console(
                    "tokenizer_specification_contract_status=contract_only tokenizer_manifest_loaded=0",
                );
                self.push_console(
                    "tokenizer_file_opened=0 tokenizer_vocab_loaded=0 prompt_tokenized=0",
                );
                self.push_console(
                    "requires_tokenization_boundary_contract=1 requires_future_tokenizer_manifest_contract=1",
                );
            }
            ["nadia", "tokenizer-manifest"]
            | ["nadia", "manifest"]
            | ["nadia", "tokenizer-manifest-contract"] => {
                self.push_console("nadia_tokenizer_manifest=stage-19-tokenizer-manifest-contract");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia tokenizer-manifest");
                self.push_console(
                    "tokenizer_manifest_contract_status=contract_only tokenizer_manifest_loaded=0",
                );
                self.push_console(
                    "tokenizer_manifest_opened=0 tokenizer_manifest_parsed=0 tokenizer_file_opened=0",
                );
                self.push_console(
                    "prompt_tokenized=0 requires_tokenizer_specification_contract=1 requires_future_tokenizer_artifact_inventory_contract=1",
                );
            }
            ["nadia", "tokenizer-artifact-inventory"]
            | ["nadia", "tokenizer-artifacts"]
            | ["nadia", "tokenizer-inventory"] => {
                self.push_console(
                    "nadia_tokenizer_artifact_inventory=stage-20-tokenizer-artifact-inventory-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia tokenizer-artifact-inventory");
                self.push_console(
                    "tokenizer_artifact_inventory_contract_status=contract_only tokenizer_artifact_path_resolved=0",
                );
                self.push_console(
                    "tokenizer_artifact_file_opened=0 tokenizer_artifact_hash_computed=0 tokenizer_manifest_loaded=0",
                );
                self.push_console(
                    "prompt_tokenized=0 requires_tokenizer_manifest_contract=1 requires_future_tokenizer_artifact_measurement_contract=1",
                );
            }
            ["nadia", "tokenizer-artifact-measurement"]
            | ["nadia", "tokenizer-measurement"]
            | ["nadia", "artifact-measurement"] => {
                self.push_console(
                    "nadia_tokenizer_artifact_measurement=stage-21-tokenizer-artifact-measurement-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia tokenizer-artifact-measurement");
                self.push_console(
                    "tokenizer_artifact_measurement_contract_status=contract_only tokenizer_artifact_measurement_performed=0",
                );
                self.push_console(
                    "tokenizer_artifact_file_opened=0 tokenizer_artifact_hash_computed=0 tokenizer_artifact_measurement_hash_computed=0",
                );
                self.push_console(
                    "prompt_tokenized=0 requires_tokenizer_artifact_inventory_contract=1 requires_future_tokenizer_artifact_verification_contract=1",
                );
            }
            ["nadia", "tokenizer-artifact-verification"]
            | ["nadia", "tokenizer-verification"]
            | ["nadia", "artifact-verification"] => {
                self.push_console(
                    "nadia_tokenizer_artifact_verification=stage-22-tokenizer-artifact-verification-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia tokenizer-artifact-verification");
                self.push_console(
                    "tokenizer_artifact_verification_contract_status=contract_only tokenizer_artifact_verification_performed=0",
                );
                self.push_console(
                    "tokenizer_artifact_verification_comparison_performed=0 tokenizer_artifact_file_opened=0 tokenizer_artifact_hash_computed=0",
                );
                self.push_console(
                    "prompt_tokenized=0 requires_tokenizer_artifact_measurement_contract=1 requires_future_tokenizer_artifact_binding_contract=1",
                );
            }
            ["nadia", "tokenizer-artifact-binding"]
            | ["nadia", "tokenizer-binding"]
            | ["nadia", "artifact-binding"] => {
                self.push_console(
                    "nadia_tokenizer_artifact_binding=stage-23-tokenizer-artifact-binding-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia tokenizer-artifact-binding");
                self.push_console(
                    "tokenizer_artifact_binding_contract_status=contract_only tokenizer_artifact_binding_performed=0",
                );
                self.push_console(
                    "tokenizer_artifact_binding_bound=0 tokenizer_artifact_file_opened=0 tokenizer_artifact_binding_hash_computed=0",
                );
                self.push_console(
                    "prompt_tokenized=0 tokenizer_attached_to_runtime=0 requires_tokenizer_artifact_verification_contract=1 requires_future_tokenizer_runtime_attachment_contract=1",
                );
            }
            ["nadia", "tokenizer-runtime-attachment"]
            | ["nadia", "runtime-attachment"]
            | ["nadia", "tokenizer-attachment"] => {
                self.push_console(
                    "nadia_tokenizer_runtime_attachment=stage-24-tokenizer-runtime-attachment-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia tokenizer-runtime-attachment");
                self.push_console(
                    "tokenizer_runtime_attachment_contract_status=contract_only tokenizer_runtime_attachment_performed=0",
                );
                self.push_console(
                    "tokenizer_attached_to_runtime=0 runtime_invoked=0 runtime_session_created=0",
                );
                self.push_console(
                    "prompt_tokenized=0 requires_tokenizer_artifact_binding_contract=1 requires_future_prompt_tokenization_contract=1",
                );
            }
            ["nadia", "prompt-tokenization"]
            | ["nadia", "prompt-tokenization-contract"]
            | ["nadia", "prompt-tokenizer"] => {
                self.push_console(
                    "nadia_prompt_tokenization=stage-25-prompt-tokenization-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-tokenization");
                self.push_console(
                    "prompt_tokenization_contract_status=contract_only prompt_tokenization_performed=0",
                );
                self.push_console("prompt_tokens_created=0 prompt_tokenized=0 runtime_invoked=0");
                self.push_console(
                    "requires_tokenizer_runtime_attachment_contract=1 requires_future_prompt_token_sequence_contract=1",
                );
            }
            ["nadia", "prompt-token-sequence"]
            | ["nadia", "token-sequence"]
            | ["nadia", "prompt-sequence"]
            | ["nadia", "prompt-token-sequence-contract"] => {
                self.push_console(
                    "nadia_prompt_token_sequence=stage-26-prompt-token-sequence-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-token-sequence");
                self.push_console(
                    "prompt_token_sequence_contract_status=contract_only prompt_token_sequence_recorded=0",
                );
                self.push_console(
                    "prompt_token_ids_recorded=0 context_window_assembled=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_tokenization_contract=1 requires_future_context_window_assembly_contract=1",
                );
            }
            ["nadia", "context-window-assembly"]
            | ["nadia", "context-window"]
            | ["nadia", "context-assembly"]
            | ["nadia", "context-window-assembly-contract"] => {
                self.push_console(
                    "nadia_context_window_assembly=stage-27-context-window-assembly-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia context-window-assembly");
                self.push_console(
                    "context_window_assembly_contract_status=contract_only context_window_assembly_performed=0",
                );
                self.push_console(
                    "context_window_assembled=0 prompt_evaluation_input_created=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_token_sequence_contract=1 requires_future_prompt_evaluation_input_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-input"]
            | ["nadia", "evaluation-input"]
            | ["nadia", "prompt-input"]
            | ["nadia", "prompt-evaluation-input-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_input=stage-28-prompt-evaluation-input-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-evaluation-input");
                self.push_console(
                    "prompt_evaluation_input_contract_status=contract_only prompt_evaluation_input_created=0",
                );
                self.push_console(
                    "prompt_evaluation_input_materialized=0 prompt_evaluation_input_validated=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_context_window_assembly_contract=1 requires_future_prompt_evaluation_runtime_handoff_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-runtime-handoff"]
            | ["nadia", "runtime-handoff"]
            | ["nadia", "evaluation-runtime-handoff"]
            | ["nadia", "prompt-evaluation-runtime-handoff-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_runtime_handoff=stage-29-prompt-evaluation-runtime-handoff-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-evaluation-runtime-handoff");
                self.push_console(
                    "prompt_evaluation_runtime_handoff_contract_status=contract_only prompt_evaluation_runtime_handoff_performed=0",
                );
                self.push_console("runtime_handoff_created=0 runtime_invoked=0 prompt_evaluated=0");
                self.push_console(
                    "requires_prompt_evaluation_input_contract=1 requires_future_prompt_evaluation_invocation_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-invocation"]
            | ["nadia", "evaluation-invocation"]
            | ["nadia", "prompt-invocation"]
            | ["nadia", "prompt-evaluation-invocation-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_invocation=stage-30-prompt-evaluation-invocation-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-evaluation-invocation");
                self.push_console(
                    "prompt_evaluation_invocation_contract_status=contract_only prompt_evaluation_invocation_performed=0",
                );
                self.push_console(
                    "prompt_evaluation_invocation_request_created=0 runtime_invoked=0 prompt_evaluated=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_runtime_handoff_contract=1 requires_future_prompt_evaluation_result_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result"]
            | ["nadia", "evaluation-result"]
            | ["nadia", "prompt-result"]
            | ["nadia", "prompt-evaluation-result-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_result=stage-31-prompt-evaluation-result-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-evaluation-result");
                self.push_console(
                    "prompt_evaluation_result_contract_status=contract_only prompt_evaluation_result_recorded=0",
                );
                self.push_console(
                    "prompt_evaluation_result_record_created=0 prompt_evaluation_result_model_output_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_invocation_contract=1 requires_future_prompt_evaluation_result_review_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-review"]
            | ["nadia", "evaluation-result-review"]
            | ["nadia", "prompt-result-review"]
            | ["nadia", "prompt-evaluation-result-review-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_result_review=stage-32-prompt-evaluation-result-review-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-evaluation-result-review");
                self.push_console(
                    "prompt_evaluation_result_review_contract_status=contract_only prompt_evaluation_result_review_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_review_decision_recorded=0 prompt_evaluation_result_model_output_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_contract=1 requires_future_prompt_evaluation_result_disposition_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-disposition"]
            | ["nadia", "evaluation-result-disposition"]
            | ["nadia", "prompt-result-disposition"]
            | ["nadia", "prompt-evaluation-result-disposition-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_result_disposition=stage-33-prompt-evaluation-result-disposition-contract",
                );
                self.push_console("panel_command=nadia prompt-evaluation-result-disposition");
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-disposition",
                );
                self.push_console(
                    "prompt_evaluation_result_disposition_contract_status=contract_only prompt_evaluation_result_disposition_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_disposition_decision_recorded=0 prompt_evaluation_result_release_record_created=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_review_contract=1 requires_future_prompt_evaluation_result_release_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release"]
            | ["nadia", "evaluation-result-release"]
            | ["nadia", "prompt-result-release"]
            | ["nadia", "prompt-evaluation-result-release-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_result_release=stage-34-prompt-evaluation-result-release-contract",
                );
                self.push_console("panel_command=nadia prompt-evaluation-result-release");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-evaluation-result-release");
                self.push_console(
                    "prompt_evaluation_result_release_contract_status=contract_only prompt_evaluation_result_release_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_decision_recorded=0 prompt_evaluation_result_release_receipt_created=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_disposition_contract=1 requires_future_prompt_evaluation_result_release_receipt_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt"]
            | ["nadia", "evaluation-result-release-receipt"]
            | ["nadia", "prompt-result-release-receipt"]
            | ["nadia", "prompt-evaluation-result-release-receipt-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt=stage-35-prompt-evaluation-result-release-receipt-contract",
                );
                self.push_console("panel_command=nadia prompt-evaluation-result-release-receipt");
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_contract_status=contract_only prompt_evaluation_result_release_receipt_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_signed=0 prompt_evaluation_result_release_receipt_published=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_contract=1",
                );
            }
            ["nadia", "inference-readiness"]
            | ["nadia", "readiness"]
            | ["nadia", "inference-contract"] => {
                self.push_console(
                    "nadia_inference_readiness=stage-10-inference-readiness-contract",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia inference-readiness");
                self.push_console(
                    "inference_readiness_contract_status=contract_only inference_ready=0",
                );
                self.push_console(
                    "runtime_invocation_authority=0 token_generation_authority=0 model_session_authority=0",
                );
                self.push_console(
                    "model_runtime_invoked=0 inference_performed=0 prompt_evaluated=0",
                );
            }
            ["nadia", "plan"] | ["nadia", "prompt-plan"] => {
                self.push_console("panel_command=nadia plan");
                self.push_console("nadia_developer_workbench=stage-3-prompt-plan");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-plan");
                self.push_console("requires_context_pack=1 requires_runtime_profile=1");
                self.push_console(
                    "prompt_evaluated=0 inference_performed=0 source_mutation_authority=0",
                );
            }
            ["nadia", "mode"] | ["nadia", "mode-validate"] => {
                self.push_console(
                    "nadia_systems_engineering_mode=stage-4-systems-engineering-mode-validation",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia mode-validate");
                self.push_console(
                    "allowed_modes=systems-engineering|ai-development|c-substrate|cpp-authority|rust-panel|lat-lir-l-ui|seal-boundary|runtime-boundary|fedora-validation|awareness-safety",
                );
                self.push_console(
                    "prompt_evaluated=0 inference_performed=0 source_mutation_authority=0",
                );
            }
            ["nadia", "ledger"] | ["nadia", "productivity"] | ["nadia", "productivity-ledger"] => {
                self.push_console("panel_command=nadia ledger");
                self.push_console("nadia_productivity_loop=stage-5-productivity-ledger-loop");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia productivity-ledger");
                self.push_console(
                    "learning_scope=operator-reviewed-local-productivity ledger_append_only=1",
                );
                self.push_console(
                    "training_performed=0 distillation_performed=0 source_mutation_authority=0",
                );
            }
            ["nadia", "safety"] | ["nadia", "protective-safety"] => {
                self.push_console("panel_command=nadia safety");
                self.push_console("nadia_protective_safety=stage-6-protective-safety-boundary");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia protective-safety");
                self.push_console(
                    "absolute_protective_boundary=1 sexual_content_generation=0 sexual_request_refusal=always",
                );
                self.push_console(
                    "manipulation_resistance=required prompt_injection_override_authority=0 policy_bypass_authority=0",
                );
            }
            ["nadia", "tool"] | ["nadia", "tool-preflight"] | ["nadia", "tool-authority"] => {
                self.push_console("nadia_tool_authority=stage-7-guarded-tool-authority-preflight");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia tool-preflight");
                self.push_console(
                    "preflight_decision=report_only_no_execution tool_execution_authority=0 tool_execution_performed=0",
                );
                self.push_console(
                    "requires_protective_safety_boundary=1 authority_transition_allowed=0",
                );
            }
            ["nadia", "prompt-contract"] | ["nadia", "prompt-evaluation-contract"] => {
                self.push_console("nadia_prompt_evaluation=stage-8-prompt-evaluation-contract");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia prompt-contract");
                self.push_console(
                    "prompt_evaluation_stage=contract-only prompt_evaluation_authority=0 prompt_materialized=0",
                );
                self.push_console(
                    "prompt_evaluated=0 inference_performed=0 tool_execution_authority=0",
                );
            }
            ["nadia", "model-registry"] | ["nadia", "registry"] | ["nadia", "model-contract"] => {
                self.push_console("nadia_model_registry=stage-9-local-model-registry-contract");
                self.push_console("panel_action=metadata-only");
                self.push_console("installed_cli=latticra-nadia model-registry");
                self.push_console(
                    "registry_contract_status=metadata_only model_registry_authority=0",
                );
                self.push_console(
                    "model_selection_authority=0 model_install_authority=0 model_load_authority=0",
                );
                self.push_console(
                    "model_runtime_invoked=0 inference_performed=0 prompt_evaluated=0",
                );
            }
            ["plan"] => {
                self.refresh_plan();
                self.show_plan_over_log = true;
                self.active_tab = WorkspaceTab::Evidence;
                self.push_console("plan refreshed in evidence panel");
            }
            ["updater", "plan"] | ["update", "plan"] => {
                self.refresh_plan();
                self.show_plan_over_log = true;
                self.active_tab = WorkspaceTab::Updater;
                self.push_console("updater: plan refreshed in Panel updater");
            }
            ["updater", "dry-run"]
            | ["update", "dry-run"]
            | ["updater", "preview"]
            | ["update", "preview"] => self.start_update_dry_run(),
            ["updater", "apply"] | ["update", "apply"] => self.start_update_apply(),
            ["save"] => self.save_config(),
            ["dry-run"] | ["run"] => self.start_install(),
            ["reset"] | ["reset-local"] => self.start_reset(),
            ["uninstall"] | ["uninstall-local"] => self.start_uninstall(),
            ["clear"] => self.console_lines.clear(),
            ["mode", "dry"] => self.set_mode_dry(),
            ["mode", "local"] => self.request_guarded_local_mode(),
            ["profile", "guided"] | ["profile", "workbench"] => {
                self.apply_profile(InstallProfile::DeveloperLocal)
            }
            ["profile", "seal"] => self.apply_profile(InstallProfile::SealReportOnly),
            ["profile", "fedora"] | ["profile", "vm"] => {
                self.apply_profile(InstallProfile::FedoraValidationVm)
            }
            ["profile", "custom"] => self.apply_profile(InstallProfile::Custom),
            ["seal", "profile", "report"] | ["seal", "profile", "report-only"] => {
                self.apply_seal_crypto_profile(SealCryptoProfile::ReportOnly)
            }
            ["seal", "profile", "sign"] | ["seal", "profile", "ed25519"] => {
                self.apply_seal_crypto_profile(SealCryptoProfile::Blake2bEd25519)
            }
            ["seal", "profile", "aead"] | ["seal", "profile", "xchacha"] => {
                self.apply_seal_crypto_profile(SealCryptoProfile::XChaCha20Poly1305)
            }
            ["seal", "profile", "hybrid"] => {
                self.apply_seal_crypto_profile(SealCryptoProfile::HybridSeal)
            }
            ["seal", "profile", "custom"] => {
                self.apply_seal_crypto_profile(SealCryptoProfile::Custom)
            }
            ["pwd"] => self.push_console(self.terminal_cwd.clone()),
            ["cd"] => self.change_terminal_dir("."),
            ["cd", _] => {
                if let Some(path) = original_parts.get(1) {
                    self.change_terminal_dir(path);
                } else {
                    self.change_terminal_dir(".");
                }
            }
            _ => self.deny_console_command(&command),
        }
    }

    fn change_terminal_dir(&mut self, path: &str) {
        let base = std::path::PathBuf::from(&self.terminal_cwd);
        let candidate = if path == "~" {
            std::env::var_os("HOME")
                .map(std::path::PathBuf::from)
                .unwrap_or(base)
        } else {
            let path_buf = std::path::PathBuf::from(path);
            if path_buf.is_absolute() {
                path_buf
            } else {
                base.join(path_buf)
            }
        };

        match candidate.canonicalize() {
            Ok(resolved) if resolved.is_dir() => {
                self.terminal_cwd = resolved.display().to_string();
                self.push_console(format!("cwd -> {}", self.terminal_cwd));
            }
            Ok(resolved) => self.push_console(format!("not a directory: {}", resolved.display())),
            Err(err) => self.push_console(format!("cd failed: {err}")),
        }
    }

    fn deny_console_command(&mut self, command: &str) {
        self.push_console(format!(
            "blocked: command outside panel allowlist: {command}"
        ));
        self.push_console(
            "allowed panel commands: help, status, plan, save, dry-run, reset, uninstall, clear",
        );
        self.push_console("allowed navigation commands: pwd, cd <path>");
    }

    fn show_header(&mut self, ui: &mut egui::Ui, compact: bool) {
        ui.add_space(2.0);
        if compact {
            ui.horizontal_wrapped(|ui| {
                ui.heading(
                    egui::RichText::new("Latticra Panel")
                        .size(20.0)
                        .color(ink()),
                );
                status_chip(ui, "version", PANEL_VERSION);
                ui.separator();
                ui.label(egui::RichText::new("first-run workbench").color(muted()));
            });
            ui.horizontal_wrapped(|ui| {
                status_chip(ui, "seal", self.config.seal.crypto_profile.label());
                status_chip(ui, "mode", self.config.execution_mode_label());
                status_chip(ui, "root", "0");
                status_chip(ui, "network", "0");
                status_chip(ui, "runtime", "0");
            });
            return;
        }

        ui.horizontal_wrapped(|ui| {
            ui.heading(
                egui::RichText::new("Latticra Panel")
                    .size(22.0)
                    .color(ink()),
            );
            status_chip(ui, "version", PANEL_VERSION);
            ui.separator();
            ui.label(
                egui::RichText::new(
                    "first-run configuration, validation, receipts, console, and Seal profiles",
                )
                .color(muted()),
            );
            ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                status_chip(ui, "runtime", "0");
                status_chip(ui, "network", "0");
                status_chip(ui, "root", "0");
                status_chip(ui, "mode", self.config.execution_mode_label());
            });
        });
        ui.add_space(2.0);
    }

    fn show_sidebar(&mut self, ui: &mut egui::Ui, compact: bool) {
        ui.vertical_centered(|ui| {
            if let Some(texture) = &self.seal_texture {
                let image_size = if compact { 84.0 } else { 132.0 };
                let image =
                    egui::Image::new(texture).fit_to_exact_size(egui::vec2(image_size, image_size));
                ui.add(image);
            }
            ui.heading("Latticra");
            ui.label(egui::RichText::new(format!("Panel v{PANEL_VERSION}")).monospace());
        });

        ui.separator();
        ui.label(egui::RichText::new("Workspace").strong());
        nav_button(
            ui,
            &mut self.active_tab,
            WorkspaceTab::Dashboard,
            "Dashboard",
        );
        nav_button(
            ui,
            &mut self.active_tab,
            WorkspaceTab::Components,
            "Components",
        );
        nav_button(
            ui,
            &mut self.active_tab,
            WorkspaceTab::Console,
            "Latticra Console",
        );
        nav_button(
            ui,
            &mut self.active_tab,
            WorkspaceTab::Seal,
            "Latticra Seal",
        );
        nav_button(
            ui,
            &mut self.active_tab,
            WorkspaceTab::Authority,
            "Authority gates",
        );
        nav_button(ui, &mut self.active_tab, WorkspaceTab::Delivery, "Delivery");
        nav_button(ui, &mut self.active_tab, WorkspaceTab::Updater, "Updater");
        nav_button(ui, &mut self.active_tab, WorkspaceTab::Evidence, "Evidence");
        nav_button(
            ui,
            &mut self.active_tab,
            WorkspaceTab::Procedure,
            "Procedure",
        );

        ui.separator();
        ui.label(egui::RichText::new("Authority baseline").strong());
        if compact {
            ui.monospace("prod_ready=0");
        } else {
            ui.monospace("production_installer_ready=0");
        }
        ui.monospace("root_authority=0");
        ui.monospace("network_authority=0");
        if compact {
            ui.monospace("runtime_auth=0");
        } else {
            ui.monospace("runtime_enforcement_authority=0");
        }

        ui.separator();
        ui.label(egui::RichText::new("Quick mode").strong());
        if ui
            .add_sized(
                [ui.available_width(), 30.0],
                egui::Button::new("Dry-run mode").fill(soft_blue()),
            )
            .clicked()
        {
            self.set_mode_dry();
        }
        let local_mode_response = ui
            .add_enabled(
                self.guarded_local_ack,
                egui::Button::new("Guarded local mode").fill(soft_green()),
            )
            .on_disabled_hover_text(self.guarded_local_ack_message());
        if local_mode_response.clicked() {
            self.request_guarded_local_mode();
        }
        if !self.guarded_local_ack {
            ui.small("Guarded local mode is unlocked in Authority gates.");
        }

        ui.separator();
        ui.label(egui::RichText::new("Status").strong());
        ui.label(&self.status);
        if self.install_state == InstallState::Running {
            ui.add(egui::ProgressBar::new(self.progress()).show_percentage());
        }
    }

    fn show_main_workbench(&mut self, ui: &mut egui::Ui, compact: bool) {
        self.refresh_plan();
        egui::ScrollArea::vertical()
            .id_salt("latticra_main_workbench")
            .auto_shrink([false, false])
            .show(ui, |ui| {
                self.show_hero_strip(ui);
                ui.add_space(10.0);

                match self.active_tab {
                    WorkspaceTab::Dashboard => self.show_dashboard(ui),
                    WorkspaceTab::Components => self.show_components(ui),
                    WorkspaceTab::Console => self.show_console_config(ui),
                    WorkspaceTab::Seal => self.show_seal_config(ui),
                    WorkspaceTab::Authority => self.show_authority(ui),
                    WorkspaceTab::Delivery => self.show_delivery(ui),
                    WorkspaceTab::Updater => self.show_updater(ui),
                    WorkspaceTab::Evidence => self.show_evidence(ui),
                    WorkspaceTab::Procedure => self.show_procedure(ui),
                }

                ui.separator();
                self.show_action_buttons(ui);
                if compact {
                    self.show_compact_auxiliary(ui);
                }
                ui.add_space(16.0);
            });
    }

    fn show_hero_strip(&mut self, ui: &mut egui::Ui) {
        let stack = ui.available_width() < 760.0;
        panel_card().show(ui, |ui| {
            if stack {
                ui.vertical(|ui| {
                    ui.label(
                        egui::RichText::new("Current lane")
                            .small()
                            .strong()
                            .color(teal()),
                    );
                    ui.heading(
                        egui::RichText::new("Guided Workbench")
                            .size(24.0)
                            .color(ink()),
                    );
                    ui.add(egui::Label::new(self.config.profile.detail()).wrap());
                    ui.add_space(6.0);
                    ui.horizontal_wrapped(|ui| {
                        status_chip(ui, "version", PANEL_VERSION);
                        status_chip(ui, "profile", self.config.profile.label());
                        status_chip(ui, "mode", self.config.execution_mode_label());
                        status_chip(ui, "seal", self.config.seal.crypto_profile.label());
                    });
                });
                ui.add_space(6.0);
                ui.horizontal_wrapped(|ui| {
                    status_chip(ui, "next", self.next_action_label());
                    status_chip(ui, "root", "0");
                    status_chip(ui, "network", "0");
                    status_chip(ui, "runtime", "0");
                });
                if self.install_state == InstallState::Running {
                    ui.add_space(8.0);
                    ui.add(egui::ProgressBar::new(self.progress()).show_percentage());
                    ui.small(format!("Current phase: {}", self.phase_title));
                }
                return;
            }

            ui.horizontal_top(|ui| {
                ui.vertical(|ui| {
                    ui.label(
                        egui::RichText::new("Current lane")
                            .small()
                            .strong()
                            .color(teal()),
                    );
                    ui.heading(
                        egui::RichText::new("Guided Workbench")
                            .size(26.0)
                            .color(ink()),
                    );
                    ui.add(egui::Label::new(self.config.profile.detail()).wrap());
                    ui.add_space(6.0);
                    ui.horizontal_wrapped(|ui| {
                        status_chip(ui, "version", PANEL_VERSION);
                        status_chip(ui, "profile", self.config.profile.label());
                        status_chip(ui, "mode", self.config.execution_mode_label());
                        status_chip(ui, "seal", self.config.seal.crypto_profile.label());
                    });
                    ui.add_space(8.0);
                    ui.horizontal_wrapped(|ui| {
                        status_chip(ui, "next", self.next_action_label());
                        status_chip(ui, "phase", &self.phase_title);
                    });
                    if self.install_state == InstallState::Running {
                        ui.add(egui::ProgressBar::new(self.progress()).show_percentage());
                    }
                });
                ui.with_layout(egui::Layout::right_to_left(egui::Align::TOP), |ui| {
                    ui.vertical(|ui| {
                        status_chip(ui, "production_installer_ready", "0");
                        status_chip(ui, "root_authority", "0");
                        status_chip(ui, "network_authority", "0");
                        status_chip(ui, "runtime_enforcement_authority", "0");
                    });
                });
            });
        });
    }

    fn show_dashboard(&mut self, ui: &mut egui::Ui) {
        ui.heading("Choose a starting lane");
        ui.add(
            egui::Label::new(
                "The workbench starts with safe, useful defaults. Generate a plan and run a dry-install receipt before enabling any local writes.",
            )
            .wrap(),
        );
        ui.add_space(8.0);
        self.show_dashboard_summary(ui);
        ui.add_space(12.0);

        let profiles = InstallProfile::all();
        if ui.available_width() < 720.0 {
            for profile in profiles {
                let (badge, description) = profile_card_text(profile);
                self.profile_card(ui, profile, badge, description);
            }
        } else {
            for row in profiles.chunks(2) {
                ui.columns(2, |columns| {
                    for (column, profile) in row.iter().copied().enumerate() {
                        let (badge, description) = profile_card_text(profile);
                        self.profile_card(&mut columns[column], profile, badge, description);
                    }
                });
                ui.add_space(6.0);
            }
        }

        ui.add_space(12.0);
        if ui.available_width() < 860.0 {
            workbench_card(
                ui,
                "1. Plan",
                "Generate and inspect the exact installer plan before any run.",
            );
            workbench_card(
                ui,
                "2. Receipt",
                "Run Dry-Install to validate and write an operator receipt.",
            );
            workbench_card(
                ui,
                "3. Install",
                "Enable guarded local writes only after evidence looks correct.",
            );
        } else {
            ui.columns(3, |columns| {
                workbench_card(
                    &mut columns[0],
                    "1. Plan",
                    "Generate and inspect the exact installer plan before any run.",
                );
                workbench_card(
                    &mut columns[1],
                    "2. Receipt",
                    "Run Dry-Install to validate and write an operator receipt.",
                );
                workbench_card(
                    &mut columns[2],
                    "3. Install",
                    "Enable guarded local writes only after evidence looks correct.",
                );
            });
        }
    }

    fn profile_card(
        &mut self,
        ui: &mut egui::Ui,
        profile: InstallProfile,
        badge: &str,
        description: &str,
    ) {
        let selected = self.config.profile == profile;
        let stroke = if selected { teal() } else { border() };
        panel_card_with_stroke(stroke).show(ui, |ui| {
            ui.set_min_height(136.0);
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new(profile.label()).size(18.0).color(ink()));
                if selected {
                    status_chip(ui, "selected", "1");
                } else {
                    status_chip(ui, "lane", badge);
                }
            });
            ui.add(egui::Label::new(description).wrap());
            ui.add_space(8.0);
            let button_label = if selected {
                "Current profile".to_owned()
            } else {
                format!("Use {}", profile.label())
            };
            let button = egui::Button::new(button_label)
                .fill(if selected { soft_green() } else { soft_blue() })
                .stroke(egui::Stroke::new(
                    1.0,
                    if selected { teal() } else { border() },
                ));
            if ui
                .add_enabled(!selected, button)
                .on_hover_text(profile.detail())
                .clicked()
            {
                self.apply_profile(profile);
            }
        });
    }

    fn show_components(&mut self, ui: &mut egui::Ui) {
        ui.heading("Project components");
        ui.label("Choose what the panel prepares under the user-local Latticra prefix.");
        ui.add_space(6.0);
        checkbox_note(
            ui,
            &mut self.config.components.latticra_console,
            "Latticra Console (LC)",
            "Configurable Panel-installable operator base for substrate, host, and future OS-console workflows.",
        );
        checkbox_note(
            ui,
            &mut self.config.components.lat_tooling,
            "Lat language tooling",
            "Language and contract declaration tooling surface.",
        );
        checkbox_note(
            ui,
            &mut self.config.components.lir_contracts,
            "LIR contracts",
            "Intermediate representation contracts and validation materials.",
        );
        checkbox_note(
            ui,
            &mut self.config.components.seal_report_only,
            "Latticra Seal report-only subsystem",
            "Tool-boundary and trust-boundary reporting without runtime enforcement claims.",
        );
        checkbox_note(
            ui,
            &mut self.config.components.nadia_offline_ai,
            "Nadia offline AI foundation",
            "Stage-35 prompt-evaluation-result-release-receipt contract with metadata-only Console surfaces.",
        );
        checkbox_note(
            ui,
            &mut self.config.components.fedora_validation,
            "Fedora validation files",
            "Fedora/Linux validation workspace, notes, and generated reports.",
        );
        checkbox_note(
            ui,
            &mut self.config.components.docs_and_examples,
            "Documentation and examples",
            "User-facing project notes and local examples.",
        );
        checkbox_note(
            ui,
            &mut self.config.components.developer_cli_helpers,
            "Developer CLI helpers",
            "Convenience wrappers for local exploration.",
        );
    }

    fn show_console_config(&mut self, ui: &mut egui::Ui) {
        ui.heading("Latticra Console profile");
        ui.label("Configure the LC installation profile, substrate bridge, and future host/OS-base posture while keeping the current authority boundary no-effect.");
        ui.add_space(8.0);

        let old_profile = self.config.lc.profile;
        egui::ComboBox::from_label("LC profile")
            .selected_text(self.config.lc.profile.label())
            .show_ui(ui, |ui| {
                for profile in LatticraConsoleProfile::all() {
                    ui.selectable_value(&mut self.config.lc.profile, profile, profile.label());
                }
            });
        if self.config.lc.profile != old_profile {
            self.config.lc.apply_profile_defaults();
            self.refresh_plan();
        }
        ui.label(self.config.lc.profile.detail());

        ui.separator();
        if ui.available_width() < 760.0 {
            lc_profile_button(
                ui,
                self,
                LatticraConsoleProfile::HostedReference,
                "Reference metadata lane",
            );
            lc_profile_button(
                ui,
                self,
                LatticraConsoleProfile::PanelEmbedded,
                "Default Panel-installed lane",
            );
            lc_profile_button(
                ui,
                self,
                LatticraConsoleProfile::HostEmbeddedPlanning,
                "Future host-embedding lane",
            );
            lc_profile_button(
                ui,
                self,
                LatticraConsoleProfile::OsBasePlanning,
                "Future OS-base lane",
            );
        } else {
            ui.columns(2, |columns| {
                lc_profile_button(
                    &mut columns[0],
                    self,
                    LatticraConsoleProfile::HostedReference,
                    "Reference metadata lane",
                );
                lc_profile_button(
                    &mut columns[1],
                    self,
                    LatticraConsoleProfile::PanelEmbedded,
                    "Default Panel-installed lane",
                );
            });
            ui.columns(2, |columns| {
                lc_profile_button(
                    &mut columns[0],
                    self,
                    LatticraConsoleProfile::HostEmbeddedPlanning,
                    "Future host-embedding lane",
                );
                lc_profile_button(
                    &mut columns[1],
                    self,
                    LatticraConsoleProfile::OsBasePlanning,
                    "Future OS-base lane",
                );
            });
        }

        ui.separator();
        ui.heading("LC install configuration");
        checkbox_note(
            ui,
            &mut self.config.components.latticra_console,
            "Install Latticra Console",
            "LC is installed as the Panel-owned operator console and metadata surface.",
        );
        labeled_text_field(
            ui,
            "Install profile",
            &mut self.config.lc.install.install_profile,
        );
        labeled_text_field(ui, "Install mode", &mut self.config.lc.install.install_mode);
        labeled_text_field(ui, "Config path", &mut self.config.lc.install.config_path);
        labeled_text_field(ui, "Share path", &mut self.config.lc.install.share_path);
        labeled_text_field(
            ui,
            "Command wrapper",
            &mut self.config.lc.install.command_wrapper,
        );
        checkbox_note(
            ui,
            &mut self.config.lc.install.panel_embedded_console,
            "Panel embedded console",
            "LC remains available inside Latticra Panel.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.install.write_config_file,
            "Write LC config file",
            "Install LC configuration metadata into the local prefix.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.install.write_profile_presets,
            "Write profile presets",
            "Install hosted, Panel, host-planning, and OS-planning profile metadata.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.install.write_command_registry,
            "Write command registry",
            "Install the LC command registry used by help, boundary, and commands.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.install.write_contract_files,
            "Write contract files",
            "Install LC metadata contracts without granting execution authority.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.install.install_user_wrapper,
            "Install user wrapper",
            "Install the latticra-lc wrapper when user command wrappers are enabled.",
        );
        let mut external_host_commands = false;
        ui.add_enabled(
            false,
            egui::Checkbox::new(
                &mut external_host_commands,
                "External host commands (future; disabled)",
            ),
        )
        .on_hover_text("LC install configuration cannot grant host process launch authority.");
        self.config.lc.install.allow_external_host_commands = false;

        ui.separator();
        ui.heading("LC substrate and embedding fields");
        labeled_text_field(
            ui,
            "Command registry",
            &mut self.config.lc.command_registry_profile,
        );
        labeled_text_field(
            ui,
            "Substrate bridge",
            &mut self.config.lc.substrate_bridge_profile,
        );
        labeled_text_field(
            ui,
            "Host embedding",
            &mut self.config.lc.host_embedding_profile,
        );
        labeled_text_field(
            ui,
            "Host contract",
            &mut self.config.lc.host_embedding_contract_profile,
        );
        labeled_text_field(
            ui,
            "Host inventory",
            &mut self.config.lc.host_inventory_contract_profile,
        );
        labeled_text_field(
            ui,
            "Host adapter",
            &mut self.config.lc.host_adapter_contract_profile,
        );
        labeled_text_field(
            ui,
            "Receipt request",
            &mut self.config.lc.receipt_request_contract_profile,
        );
        labeled_text_field(
            ui,
            "Receipt payload",
            &mut self.config.lc.receipt_payload_schema_profile,
        );
        labeled_text_field(
            ui,
            "Receipt artifact",
            &mut self.config.lc.receipt_payload_artifact_draft_profile,
        );
        labeled_text_field(
            ui,
            "Artifact review",
            &mut self.config.lc.receipt_payload_artifact_review_profile,
        );
        labeled_text_field(
            ui,
            "Review receipt",
            &mut self
                .config
                .lc
                .receipt_payload_artifact_review_receipt_profile,
        );
        labeled_text_field(
            ui,
            "Materialization plan",
            &mut self.config.lc.receipt_payload_materialization_plan_profile,
        );
        labeled_text_field(
            ui,
            "Signature request",
            &mut self.config.lc.signature_request_binding_profile,
        );
        labeled_text_field(
            ui,
            "Receipt contract",
            &mut self.config.lc.receipt_contract_profile,
        );
        labeled_text_field(
            ui,
            "OS contract",
            &mut self.config.lc.os_base_contract_profile,
        );
        labeled_text_field(
            ui,
            "VM evidence",
            &mut self.config.lc.vm_evidence_contract_profile,
        );
        labeled_text_field(ui, "OS base", &mut self.config.lc.os_base_profile);
        labeled_text_field(ui, "Panel bridge", &mut self.config.lc.panel_bridge);
        checkbox_note(
            ui,
            &mut self.config.lc.report_only,
            "LC remains report-only",
            "Current LC profiles emit configuration and evidence only.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_host_embedding_contract,
            "Require host-embedding contract",
            "LC host embedding cannot advance until this contract is present and reviewed.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_read_only_host_inventory_contract,
            "Require read-only host inventory contract",
            "Future host adapters must prove inventory evidence without broad host authority.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_profile_receipt,
            "Require profile receipt",
            "LC profile selection must become receipt evidence before future promotion.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_host_contract_receipt,
            "Require host-contract receipt",
            "The host-embedding contract must be receipted before any host adapter path.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_host_inventory_receipt,
            "Require host-inventory receipt",
            "Read-only inventory contract metadata must be receipted before host embedding work.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_host_adapter_contract,
            "Require host-adapter contract",
            "Future Host embedding must prove the adapter contract before any adapter can exist.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_receipt_request_contract,
            "Require receipt-request contract",
            "Future LC receipt signing must prove the request contract before any signature can exist.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_receipt_payload_schema,
            "Require receipt payload schema",
            "Future LC receipt signing must prove the payload shape before any signature request can bind.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_receipt_payload_artifact_draft,
            "Require receipt artifact draft",
            "Future LC receipt signing must prove the no-write payload artifact draft before materialization.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_receipt_payload_artifact_review,
            "Require artifact review gate",
            "Future LC receipt payload materialization must prove the draft review gate before any payload artifact can exist.",
        );
        checkbox_note(
            ui,
            &mut self
                .config
                .lc
                .require_receipt_payload_artifact_review_receipt,
            "Require review receipt",
            "Future LC receipt payload materialization must prove review receipt evidence before any payload artifact can exist.",
        );
        checkbox_note(
            ui,
            &mut self
                .config
                .lc
                .require_receipt_payload_materialization_plan,
            "Require materialization plan",
            "Future LC receipt payload writes must prove the materialization plan before any payload artifact can exist.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_signature_request_binding,
            "Require signature-request binding",
            "Future LC receipt signing must prove the binding contract before any Seal signature request artifact can exist.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_os_base_contract,
            "Require OS-base contract",
            "Future OS-base work must prove this contract before any boot-adjacent planning advances.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_vm_evidence_contract,
            "Require VM evidence contract",
            "Future OS-base work must prove VM evidence metadata before any boot-adjacent implementation.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_runtime_boundary_binding,
            "Require Runtime Boundary binding",
            "LC command surfaces must remain classified before future execution authority can exist.",
        );
        checkbox_note(
            ui,
            &mut self.config.lc.require_seal_capability_labels,
            "Require Seal capability labels",
            "LC commands keep explicit Seal labels while granting no cryptographic or runtime authority.",
        );
    }

    fn show_seal_config(&mut self, ui: &mut egui::Ui) {
        ui.heading("Latticra Seal cryptographic profile");
        ui.label("Choose the Seal crypto posture for reports, manifests, envelopes, and future sealed payload planning. The installer still remains report-only and no-effect unless explicit future authority is implemented.");
        ui.add_space(8.0);

        let old_profile = self.config.seal.crypto_profile;
        egui::ComboBox::from_label("Seal crypto profile")
            .selected_text(self.config.seal.crypto_profile.label())
            .show_ui(ui, |ui| {
                for profile in SealCryptoProfile::all() {
                    ui.selectable_value(
                        &mut self.config.seal.crypto_profile,
                        profile,
                        profile.label(),
                    );
                }
            });
        if self.config.seal.crypto_profile != old_profile {
            self.config.seal.apply_crypto_profile_defaults();
            self.refresh_plan();
        }
        ui.label(self.config.seal.crypto_profile.detail());

        ui.separator();
        if ui.available_width() < 760.0 {
            seal_profile_button(
                ui,
                self,
                SealCryptoProfile::ReportOnly,
                "Zero-key report lane",
            );
            seal_profile_button(
                ui,
                self,
                SealCryptoProfile::Blake2bEd25519,
                "Default evidence/signature planning lane",
            );
            seal_profile_button(
                ui,
                self,
                SealCryptoProfile::XChaCha20Poly1305,
                "AEAD sealed-payload planning lane",
            );
            seal_profile_button(
                ui,
                self,
                SealCryptoProfile::HybridSeal,
                "Advanced hybrid planning lane",
            );
        } else {
            ui.columns(2, |columns| {
                seal_profile_button(
                    &mut columns[0],
                    self,
                    SealCryptoProfile::ReportOnly,
                    "Zero-key report lane",
                );
                seal_profile_button(
                    &mut columns[1],
                    self,
                    SealCryptoProfile::Blake2bEd25519,
                    "Default evidence/signature planning lane",
                );
            });
            ui.columns(2, |columns| {
                seal_profile_button(
                    &mut columns[0],
                    self,
                    SealCryptoProfile::XChaCha20Poly1305,
                    "AEAD sealed-payload planning lane",
                );
                seal_profile_button(
                    &mut columns[1],
                    self,
                    SealCryptoProfile::HybridSeal,
                    "Advanced hybrid planning lane",
                );
            });
        }

        ui.separator();
        ui.heading("Seal parameters");
        labeled_text_field(ui, "Hash", &mut self.config.seal.hash_profile);
        labeled_text_field(ui, "Signature", &mut self.config.seal.signature_profile);
        labeled_text_field(ui, "Encryption", &mut self.config.seal.encryption_profile);
        labeled_text_field(ui, "Envelope", &mut self.config.seal.envelope_profile);
        labeled_text_field(ui, "Key storage", &mut self.config.seal.key_storage_profile);
        checkbox_note(
            ui,
            &mut self.config.seal.report_only,
            "Seal remains report-only",
            "No signing, encryption, key generation, or key storage occurs from this panel lane.",
        );
        checkbox_note(
            ui,
            &mut self.config.seal.require_signed_manifest,
            "Require signed manifest metadata",
            "Requires signed-manifest metadata in plans/receipts when using advanced profiles.",
        );
        checkbox_note(
            ui,
            &mut self.config.seal.write_seal_report,
            "Write Seal report",
            "Include Latticra Seal report metadata in generated local evidence.",
        );
    }

    fn show_authority(&mut self, ui: &mut egui::Ui) {
        ui.heading("Safety and evidence gates");
        ui.label("Latticra Panel makes authority visible before anything effectful can happen.");
        ui.add_space(6.0);
        self.show_mode_gate(ui);
        self.config.safety.allow_network_effect = false;
        ui.add_enabled(
            false,
            egui::Checkbox::new(
                &mut self.config.safety.allow_network_effect,
                "Network effect (future; disabled)",
            ),
        );
        ui.small("Network authority remains disabled in this installer lane.");
        ui.separator();
        checkbox_note(
            ui,
            &mut self.config.safety.require_component_manifest,
            "Require component manifest",
            "Refuse to proceed when component inventory evidence is missing.",
        );
        checkbox_note(
            ui,
            &mut self.config.safety.require_artifact_measurements,
            "Require artifact measurements",
            "Keep generated measurement evidence in the receipt chain.",
        );
        checkbox_note(
            ui,
            &mut self.config.safety.require_verification_policy_metadata,
            "Require verification policy metadata",
            "Preserve policy/evidence metadata expectations.",
        );
        checkbox_note(
            ui,
            &mut self.config.safety.write_operator_receipt,
            "Write operator-visible receipt",
            "Create a visible receipt for the configured run.",
        );
    }

    fn show_mode_gate(&mut self, ui: &mut egui::Ui) {
        let mode_stroke = if self.config.safety.dry_run {
            blue()
        } else if self.guarded_local_ack {
            green()
        } else {
            amber()
        };

        panel_card_with_stroke(mode_stroke).show(ui, |ui| {
            ui.heading(egui::RichText::new("Run mode").size(18.0).color(ink()));
            ui.add(
                egui::Label::new(
                    "Dry-run is the default. Guarded local mode can write only to the configured user-local prefix and stays blocked until acknowledged here.",
                )
                .wrap(),
            );
            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                status_chip(ui, "mode", self.config.execution_mode_label());
                status_chip(
                    ui,
                    "local_write_ack",
                    if self.guarded_local_ack { "1" } else { "0" },
                );
                status_chip(ui, "root", "0");
                status_chip(ui, "network", "0");
            });
            ui.add_space(8.0);

            let ack_changed = ui
                .checkbox(
                    &mut self.guarded_local_ack,
                    egui::RichText::new(
                        "I understand guarded local mode can write to the configured user-local prefix.",
                    )
                    .strong(),
                )
                .changed();
            if ack_changed && !self.guarded_local_ack && !self.config.safety.dry_run {
                self.set_mode_dry();
                self.status =
                    "Guarded local mode returned to dry-run because acknowledgement was cleared."
                        .to_owned();
                self.push_console("mode -> dry-install; guarded local acknowledgement cleared");
            }

            ui.horizontal_wrapped(|ui| {
                if ui
                    .add(
                        egui::Button::new("Use dry-run mode")
                            .fill(soft_blue())
                            .stroke(egui::Stroke::new(1.0, blue())),
                    )
                    .clicked()
                {
                    self.set_mode_dry();
                }

                let local_response = ui
                    .add_enabled(
                        self.guarded_local_ack,
                        egui::Button::new("Use guarded local mode")
                            .fill(soft_green())
                            .stroke(egui::Stroke::new(1.0, green())),
                    )
                    .on_disabled_hover_text(self.guarded_local_ack_message());
                if local_response.clicked() {
                    self.set_mode_local();
                }
            });

            if self.guarded_local_ack_missing() {
                warning_note(ui, "Guarded mode locked", self.guarded_local_ack_message());
            } else if self.config.safety.dry_run {
                ui.small("Current action path: plan, dry-install, and receipt generation.");
            } else {
                ui.small("Current action path: guarded writes to the configured user-local prefix.");
            }
        });
    }

    fn show_delivery(&mut self, ui: &mut egui::Ui) {
        ui.heading("Program delivery");
        ui.label("Control how the user-local payload, wrappers, desktop entry, and build outputs are prepared.");
        ui.add_space(6.0);
        if ui.available_width() < 620.0 {
            ui.label("Install prefix");
            ui.text_edit_singleline(&mut self.config.install_prefix);
            if ui.button("Reset").clicked() {
                self.reset_install_prefix();
            }
        } else {
            ui.horizontal(|ui| {
                ui.label("Install prefix");
                ui.text_edit_singleline(&mut self.config.install_prefix);
                if ui.button("Reset").clicked() {
                    self.reset_install_prefix();
                }
            });
        }
        ui.separator();
        checkbox_note(
            ui,
            &mut self.config.behavior.create_prefix_layout,
            "Create prefix layout",
            "Prepare the user-local directory structure.",
        );
        checkbox_note(
            ui,
            &mut self.config.behavior.create_component_markers,
            "Create component markers",
            "Write installed component marker files.",
        );
        checkbox_note(
            ui,
            &mut self.config.behavior.create_cli_shims,
            "Create CLI shims",
            "Prepare command shims inside the user-local prefix.",
        );
        checkbox_note(
            ui,
            &mut self.config.behavior.preserve_existing_files,
            "Preserve existing files",
            "Refuse to overwrite unmanaged files.",
        );
        ui.separator();
        checkbox_note(
            ui,
            &mut self.config.behavior.build_gui_installer,
            "Build Latticra Panel binary",
            "Build the panel itself when Cargo is available.",
        );
        checkbox_note(
            ui,
            &mut self.config.behavior.build_latticra_from_source,
            "Build Latticra from source when available",
            "Use supported root build systems when present.",
        );
        checkbox_note(
            ui,
            &mut self.config.behavior.install_payload_tree,
            "Install payload tree",
            "Copy project payload material into the local prefix.",
        );
        checkbox_note(
            ui,
            &mut self.config.behavior.install_desktop_entry,
            "Install desktop entry",
            "Expose Latticra Panel in the user app grid.",
        );
        checkbox_note(
            ui,
            &mut self.config.behavior.install_user_bin_wrappers,
            "Install user bin wrappers",
            "Install user-local wrappers for latticra, lat, seal, and panel commands.",
        );
    }

    fn show_updater(&mut self, ui: &mut egui::Ui) {
        ui.heading("Panel updater");
        ui.label("Update the managed user-local install from the reviewed source checkout through the same guarded installer engine.");
        ui.add_space(6.0);

        ui.horizontal_wrapped(|ui| {
            status_chip(ui, "source", &self.config.updater.source_strategy);
            status_chip(ui, "channel", &self.config.updater.update_channel);
            status_chip(
                ui,
                "dry_run_ok",
                if self.last_update_dry_run_ok {
                    "1"
                } else {
                    "0"
                },
            );
            status_chip(ui, "network", "0");
            status_chip(ui, "root", "0");
        });

        ui.separator();
        if ui.available_width() < 620.0 {
            labeled_text_field(
                ui,
                "Source strategy",
                &mut self.config.updater.source_strategy,
            );
            labeled_text_field(ui, "Channel", &mut self.config.updater.update_channel);
        } else {
            ui.columns(2, |columns| {
                labeled_text_field(
                    &mut columns[0],
                    "Source strategy",
                    &mut self.config.updater.source_strategy,
                );
                labeled_text_field(
                    &mut columns[1],
                    "Channel",
                    &mut self.config.updater.update_channel,
                );
            });
        }

        ui.add_space(4.0);
        self.config.updater.allow_network_fetch = false;
        ui.add_enabled(
            false,
            egui::Checkbox::new(
                &mut self.config.updater.allow_network_fetch,
                "Network fetch (future; disabled)",
            ),
        );
        ui.small("Updater fetch/pull authority remains outside this Panel lane.");
        checkbox_note(
            ui,
            &mut self.config.updater.require_dry_run_before_apply,
            "Require updater dry-run before apply",
            "A successful updater dry-run in this Panel session is required before guarded apply.",
        );
        checkbox_note(
            ui,
            &mut self.config.updater.reuse_installer_engine,
            "Reuse guarded installer engine",
            "Update apply is a guarded local-prefix reinstall over Latticra-managed files.",
        );
        checkbox_note(
            ui,
            &mut self.config.updater.write_update_receipt,
            "Write updater receipt metadata",
            "Generated plans and receipts include the updater policy fields.",
        );

        ui.separator();
        ui.horizontal_wrapped(|ui| {
            if ui.button("Preview update").clicked() {
                self.start_update_dry_run();
            }
            let apply_blocker = if self.config.updater.require_dry_run_before_apply
                && !self.last_update_dry_run_ok
            {
                Some("Updater apply is locked until Preview update completes successfully.")
            } else if !self.guarded_local_ack {
                Some(self.guarded_local_ack_message())
            } else {
                None
            };
            let apply_response = if let Some(reason) = apply_blocker {
                ui.add_enabled(false, egui::Button::new("Apply guarded update"))
                    .on_disabled_hover_text(reason)
            } else {
                ui.add(egui::Button::new("Apply guarded update"))
            };
            if apply_response.clicked() {
                self.start_update_apply();
            }
            if ui.button("Open update plan").clicked() {
                self.refresh_plan();
                self.show_plan_over_log = true;
                self.active_tab = WorkspaceTab::Evidence;
            }
        });

        if self.config.updater.require_dry_run_before_apply && !self.last_update_dry_run_ok {
            warning_note(
                ui,
                "Updater apply locked",
                "Preview update must complete successfully in this Panel session.",
            );
        } else if !self.guarded_local_ack {
            warning_note(ui, "Updater apply locked", self.guarded_local_ack_message());
        }
    }

    fn show_dashboard_summary(&mut self, ui: &mut egui::Ui) {
        let mode_value = if self.config.safety.dry_run {
            "dry-run"
        } else {
            "guarded local"
        };
        let evidence_value = if self.logs.is_empty() {
            "not run"
        } else if self.install_state == InstallState::Complete {
            "complete"
        } else if self.install_state == InstallState::Failed {
            "blocked"
        } else {
            "available"
        };
        let updater_value = if self.last_update_dry_run_ok {
            "ready"
        } else {
            "locked"
        };

        if ui.available_width() < 760.0 {
            summary_tile(
                ui,
                "Panel version",
                PANEL_VERSION,
                "current GUI foundation",
                teal(),
            );
            summary_tile(
                ui,
                "Authority",
                mode_value,
                "root=0 network=0 runtime=0",
                blue(),
            );
            summary_tile(
                ui,
                "Evidence",
                evidence_value,
                "plan and engine log stay visible",
                amber(),
            );
            summary_tile(ui, "Updater", updater_value, "dry-run gates apply", green());
            return;
        }

        ui.columns(4, |columns| {
            summary_tile(
                &mut columns[0],
                "Panel version",
                PANEL_VERSION,
                "current GUI foundation",
                teal(),
            );
            summary_tile(
                &mut columns[1],
                "Authority",
                mode_value,
                "root=0 network=0 runtime=0",
                blue(),
            );
            summary_tile(
                &mut columns[2],
                "Evidence",
                evidence_value,
                "plan and engine log stay visible",
                amber(),
            );
            summary_tile(
                &mut columns[3],
                "Updater",
                updater_value,
                "dry-run gates apply",
                green(),
            );
        });
    }

    fn show_evidence(&mut self, ui: &mut egui::Ui) {
        ui.heading("Plan, receipts, and evidence");
        ui.horizontal(|ui| {
            if ui
                .selectable_label(self.show_plan_over_log, "Plan preview")
                .clicked()
            {
                self.show_plan_over_log = true;
            }
            if ui
                .selectable_label(!self.show_plan_over_log, "Engine log")
                .clicked()
            {
                self.show_plan_over_log = false;
            }
            if ui.button("Refresh plan").clicked() {
                self.refresh_plan();
            }
        });

        egui::ScrollArea::vertical()
            .id_salt("latticra_evidence_panel")
            .max_height(ui.available_height().max(260.0))
            .stick_to_bottom(!self.show_plan_over_log)
            .show(ui, |ui| {
                if self.show_plan_over_log {
                    ui.monospace(&self.plan);
                } else if self.logs.is_empty() {
                    ui.monospace("No engine run yet.");
                } else {
                    for line in &self.logs {
                        ui.monospace(line);
                    }
                }
            });
    }

    fn show_procedure(&mut self, ui: &mut egui::Ui) {
        ui.heading("Recommended procedure");
        ui.label("A safe Latticra first run is evidence-first, then install-second.");
        ui.add_space(8.0);
        procedure_row(
            ui,
            "01",
            "Choose Guided Workbench",
            "Start from a complete but dry configuration.",
        );
        procedure_row(
            ui,
            "02",
            "Inspect components",
            "Confirm Lat, LIR, Seal, docs, helpers, and Fedora validation intent.",
        );
        procedure_row(
            ui,
            "03",
            "Configure Seal",
            "Pick a report-only, signature-planning, AEAD-planning, or hybrid Seal profile.",
        );
        procedure_row(
            ui,
            "04",
            "Generate plan",
            "Write and inspect latticra-installer-plan.txt.",
        );
        procedure_row(
            ui,
            "05",
            "Run Dry-Install",
            "Validate the engine and create a receipt without host mutation.",
        );
        procedure_row(
            ui,
            "06",
            "Review evidence",
            "Read console output, plan, logs, and receipt paths.",
        );
        procedure_row(
            ui,
            "07",
            "Enable local install",
            "Only then enable guarded local-prefix writes.",
        );
        procedure_row(
            ui,
            "08",
            "Use the Panel updater for reinstall updates",
            "Preview the update first, then apply the guarded local-prefix reinstall from the current checkout.",
        );
        procedure_row(
            ui,
            "09",
            "Reset or uninstall when specifications change",
            "Use reset before reinstalling from new specs, or uninstall to remove the managed local install.",
        );
    }

    fn show_action_buttons(&mut self, ui: &mut egui::Ui) {
        ui.horizontal_wrapped(|ui| {
            if ui.button("Save configuration").clicked() {
                self.save_config();
            }
            if ui.button("Generate plan").clicked() {
                self.write_plan();
                self.active_tab = WorkspaceTab::Evidence;
                self.show_plan_over_log = true;
            }
            if ui.button("Open evidence").clicked() {
                self.active_tab = WorkspaceTab::Evidence;
            }
        });

        ui.add_space(10.0);
        self.show_fluid_install_button(ui);
        ui.add_space(8.0);
        self.show_reset_button(ui);
        ui.add_space(6.0);
        self.show_uninstall_button(ui);

        if let Err(err) = self.panel_can_execute() {
            ui.colored_label(egui::Color32::from_rgb(255, 160, 130), err);
        }
        if let Err(err) = self.panel_can_reset() {
            ui.colored_label(egui::Color32::from_rgb(255, 190, 130), err);
        }
    }

    fn show_fluid_install_button(&mut self, ui: &mut egui::Ui) {
        let running = self.install_state == InstallState::Running;
        let blocker = self.install_blocker(running);
        let can_execute = blocker.is_none();
        let label = if running {
            "Installing..."
        } else if self.config.safety.dry_run {
            "Run Dry-Install"
        } else {
            "Install guarded local prefix"
        };

        let time = ui.input(|input| input.time) as f32;
        let pulse = ((time * 3.0).sin() + 1.0) * 0.5;
        let fill = if running {
            blend(
                egui::Color32::from_rgb(20, 88, 210),
                egui::Color32::from_rgb(70, 180, 255),
                pulse,
            )
        } else if self.config.safety.dry_run {
            egui::Color32::from_rgb(22, 88, 185)
        } else {
            egui::Color32::from_rgb(28, 130, 95)
        };

        let stroke = egui::Stroke::new(
            1.0 + pulse,
            blend(
                egui::Color32::from_rgb(160, 220, 255),
                egui::Color32::from_rgb(210, 245, 255),
                pulse,
            ),
        );

        let button_width = ui.available_width().min(340.0).max(180.0);
        let text_size = if button_width < 280.0 { 16.0 } else { 20.0 };
        let button = egui::Button::new(egui::RichText::new(label).size(text_size).strong())
            .min_size(egui::vec2(button_width, 58.0))
            .fill(fill)
            .stroke(stroke);

        let response = if let Some(reason) = blocker.as_deref() {
            ui.add_enabled(can_execute, button)
                .on_disabled_hover_text(reason)
        } else {
            ui.add_enabled(can_execute, button)
        };
        if let Some(reason) = blocker.as_deref() {
            warning_note(ui, "Install locked", reason);
        }
        if response.clicked() {
            self.start_install();
        }
    }

    fn show_reset_button(&mut self, ui: &mut egui::Ui) {
        let label = if self.config.safety.dry_run {
            "Preview local reset"
        } else {
            "Reset installed local prefix"
        };

        self.show_removal_button(ui, label, RemovalOperation::Reset);
    }

    fn show_uninstall_button(&mut self, ui: &mut egui::Ui) {
        let label = if self.config.safety.dry_run {
            "Preview uninstall"
        } else {
            "Uninstall managed local install"
        };

        self.show_removal_button(ui, label, RemovalOperation::Uninstall);
    }

    fn show_removal_button(&mut self, ui: &mut egui::Ui, label: &str, operation: RemovalOperation) {
        let running = self.install_state == InstallState::Running;
        let blocker = self.removal_blocker(running);
        let can_remove = blocker.is_none();
        let button_width = ui.available_width().min(340.0).max(180.0);
        let text_size = if button_width < 280.0 { 14.0 } else { 16.0 };
        let button = egui::Button::new(egui::RichText::new(label).size(text_size).strong())
            .min_size(egui::vec2(button_width, 44.0))
            .fill(egui::Color32::from_rgb(96, 70, 38))
            .stroke(egui::Stroke::new(
                1.0,
                egui::Color32::from_rgb(230, 185, 120),
            ));

        let response = if let Some(reason) = blocker.as_deref() {
            ui.add_enabled(can_remove, button)
                .on_disabled_hover_text(reason)
        } else {
            ui.add_enabled(can_remove, button)
        };
        if response.clicked() {
            self.start_removal(operation);
        }
    }

    fn reset_install_prefix(&mut self) {
        self.config.install_prefix = match self.config.profile {
            InstallProfile::FedoraValidationVm => "~/.local/share/latticra-validation".to_owned(),
            _ => "~/.local/share/latticra".to_owned(),
        };
    }

    fn show_console_panel(&mut self, ui: &mut egui::Ui) {
        panel_card().show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("Panel Console").color(ink()));
                ui.small(format!("cwd={}", self.terminal_cwd));
            });
            ui.small("Panel commands and local navigation only. No external host process is launched by the console.");
            ui.add_space(6.0);

            egui::Frame::NONE
                .fill(egui::Color32::from_rgb(6, 10, 18))
                .stroke(egui::Stroke::new(1.0, egui::Color32::from_rgb(45, 90, 130)))
                .inner_margin(egui::Margin::same(8))
                .show(ui, |ui| {
                    egui::ScrollArea::vertical()
                        .id_salt("latticra_embedded_console")
                        .max_height(520.0)
                        .stick_to_bottom(true)
                        .show(ui, |ui| {
                            ui.monospace("host@latticra-panel:~");
                            for line in &self.console_lines {
                                ui.label(
                                    egui::RichText::new(line)
                                        .monospace()
                                        .color(egui::Color32::from_rgb(160, 230, 255)),
                                );
                            }
                        });

                    ui.separator();
                    ui.horizontal(|ui| {
                        ui.label(egui::RichText::new("$").monospace());
                        let input_width = (ui.available_width() - 48.0).max(120.0);
                        let response = ui.add(
                            egui::TextEdit::singleline(&mut self.console_input)
                                .font(egui::TextStyle::Monospace)
                                .desired_width(input_width)
                                .hint_text("panel command"),
                        );
                        let enter_pressed = response.lost_focus()
                            && ui.input(|input| input.key_pressed(egui::Key::Enter));
                        if enter_pressed {
                            self.run_console_command();
                        }
                        if ui.button("Run").clicked() {
                            self.run_console_command();
                        }
                    });
                });

            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                for command in [
                    "help",
                    "status",
                    "updater",
                    "updater dry-run",
                    "pwd",
                    "plan",
                    "dry-run",
                    "reset",
                    "uninstall",
                    "mode dry",
                    "mode local",
                    "clear",
                ] {
                    if ui.button(command).clicked() {
                        self.console_input = command.to_owned();
                        self.run_console_command();
                    }
                }
            });
        });
    }

    fn show_compact_auxiliary(&mut self, ui: &mut egui::Ui) {
        ui.add_space(12.0);
        ui.separator();
        egui::CollapsingHeader::new("Live evidence")
            .default_open(false)
            .show(ui, |ui| self.show_right_evidence_panel(ui));
        egui::CollapsingHeader::new("Host Quick Terminal")
            .default_open(false)
            .show(ui, |ui| self.show_console_panel(ui));
    }

    fn show_right_evidence_panel(&mut self, ui: &mut egui::Ui) {
        ui.group(|ui| {
            ui.horizontal(|ui| {
                ui.heading("Live evidence");
                ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                    if ui.button("plan/log").clicked() {
                        self.show_plan_over_log = !self.show_plan_over_log;
                    }
                });
            });

            egui::ScrollArea::vertical()
                .id_salt("latticra_right_evidence")
                .max_height(220.0)
                .stick_to_bottom(!self.show_plan_over_log)
                .show(ui, |ui| {
                    if self.show_plan_over_log {
                        ui.monospace(&self.plan);
                    } else if self.logs.is_empty() {
                        ui.monospace("No engine log yet.");
                    } else {
                        for line in &self.logs {
                            ui.monospace(line);
                        }
                    }
                });
        });
    }

    fn show_status_bar(&mut self, ui: &mut egui::Ui) {
        ui.horizontal_wrapped(|ui| {
            ui.monospace(
                egui::RichText::new(format!("Latticra Panel v{PANEL_VERSION}")).color(ink()),
            );
            ui.separator();
            ui.monospace(format!("profile={}", self.config.profile.label()));
            ui.separator();
            ui.monospace(format!("seal={}", self.config.seal.crypto_profile.label()));
            ui.separator();
            ui.monospace(format!("mode={}", self.config.execution_mode_label()));
            ui.separator();
            ui.label(&self.status);
        });
    }
}

impl eframe::App for LatticraInstallerApp {
    fn ui(&mut self, root_ui: &mut egui::Ui, _: &mut eframe::Frame) {
        let ctx = root_ui.ctx().clone();
        apply_panel_theme(&ctx);
        self.ensure_texture(&ctx);
        self.drain_events();
        let screen_width = ctx.content_rect().width();
        let compact = screen_width < COMPACT_LAYOUT_WIDTH;
        let narrow = screen_width < NARROW_LAYOUT_WIDTH;

        if self.install_state == InstallState::Running {
            ctx.request_repaint_after(Duration::from_millis(33));
        }

        egui::Panel::top("top_header").show_inside(root_ui, |ui| {
            self.show_header(ui, compact);
        });

        egui::Panel::bottom("bottom_status").show_inside(root_ui, |ui| {
            self.show_status_bar(ui);
        });

        egui::Panel::left("left_workbench_nav")
            .resizable(true)
            .default_size(if narrow { 170.0 } else { 230.0 })
            .min_size(if narrow { 150.0 } else { 180.0 })
            .show_inside(root_ui, |ui| {
                egui::ScrollArea::vertical()
                    .id_salt("left_workbench_nav_scroll")
                    .auto_shrink([false, false])
                    .show(ui, |ui| self.show_sidebar(ui, compact));
            });

        if !compact {
            egui::Panel::right("right_console")
                .resizable(true)
                .default_size(560.0)
                .min_size(360.0)
                .show_inside(root_ui, |ui| {
                    egui::ScrollArea::vertical()
                        .id_salt("right_console_scroll")
                        .auto_shrink([false, false])
                        .show(ui, |ui| {
                            self.show_console_panel(ui);
                            ui.add_space(10.0);
                            self.show_right_evidence_panel(ui);
                        });
                });
        }

        egui::CentralPanel::default().show_inside(root_ui, |ui| {
            self.show_main_workbench(ui, compact);
        });
    }
}

fn apply_panel_theme(ctx: &egui::Context) {
    let mut style = (*ctx.global_style()).clone();
    style.spacing.item_spacing = egui::vec2(8.0, 8.0);
    style.spacing.button_padding = egui::vec2(10.0, 7.0);
    style.spacing.interact_size = egui::vec2(40.0, 32.0);
    style.spacing.window_margin = egui::Margin::same(10);

    let mut visuals = egui::Visuals::light();
    visuals.panel_fill = egui::Color32::from_rgb(244, 247, 246);
    visuals.window_fill = egui::Color32::from_rgb(255, 255, 255);
    visuals.window_stroke = egui::Stroke::new(1.0, border());
    visuals.window_corner_radius = egui::CornerRadius::same(8);
    visuals.menu_corner_radius = egui::CornerRadius::same(8);
    visuals.faint_bg_color = egui::Color32::from_rgb(239, 245, 244);
    visuals.extreme_bg_color = egui::Color32::from_rgb(230, 238, 238);
    visuals.code_bg_color = egui::Color32::from_rgb(232, 239, 240);
    visuals.hyperlink_color = blue();
    visuals.warn_fg_color = amber();
    visuals.error_fg_color = red();
    visuals.selection.bg_fill = egui::Color32::from_rgb(205, 231, 226);
    visuals.selection.stroke = egui::Stroke::new(1.0, teal());
    visuals.widgets.noninteractive.bg_fill = egui::Color32::from_rgb(250, 252, 251);
    visuals.widgets.noninteractive.weak_bg_fill = soft_surface();
    visuals.widgets.noninteractive.bg_stroke = egui::Stroke::new(1.0, border());
    visuals.widgets.noninteractive.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.widgets.inactive.bg_fill = egui::Color32::from_rgb(247, 250, 249);
    visuals.widgets.inactive.weak_bg_fill = soft_surface();
    visuals.widgets.inactive.bg_stroke = egui::Stroke::new(1.0, border());
    visuals.widgets.inactive.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.widgets.hovered.bg_fill = egui::Color32::from_rgb(230, 244, 242);
    visuals.widgets.hovered.weak_bg_fill = egui::Color32::from_rgb(222, 239, 237);
    visuals.widgets.hovered.bg_stroke = egui::Stroke::new(1.0, teal());
    visuals.widgets.hovered.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.widgets.active.bg_fill = egui::Color32::from_rgb(208, 232, 228);
    visuals.widgets.active.weak_bg_fill = egui::Color32::from_rgb(208, 232, 228);
    visuals.widgets.active.bg_stroke = egui::Stroke::new(1.0, teal());
    visuals.widgets.active.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.widgets.open.bg_fill = egui::Color32::from_rgb(236, 242, 241);
    visuals.widgets.open.weak_bg_fill = egui::Color32::from_rgb(236, 242, 241);
    visuals.widgets.open.bg_stroke = egui::Stroke::new(1.0, border_strong());
    visuals.widgets.open.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.override_text_color = Some(ink());
    visuals.weak_text_color = Some(muted());
    visuals.button_frame = true;
    visuals.interact_cursor = Some(egui::CursorIcon::PointingHand);

    style.visuals = visuals;
    ctx.set_global_style(style);
}

fn panel_card() -> egui::Frame {
    panel_card_with_stroke(border())
}

fn panel_card_with_stroke(stroke_color: egui::Color32) -> egui::Frame {
    egui::Frame::NONE
        .fill(egui::Color32::from_rgb(255, 255, 255))
        .stroke(egui::Stroke::new(1.0, stroke_color))
        .corner_radius(egui::CornerRadius::same(8))
        .inner_margin(egui::Margin::same(12))
}

fn summary_tile(ui: &mut egui::Ui, label: &str, value: &str, note: &str, accent: egui::Color32) {
    panel_card_with_stroke(accent).show(ui, |ui| {
        ui.set_min_height(108.0);
        ui.label(egui::RichText::new(label).small().strong().color(accent));
        ui.heading(egui::RichText::new(value).size(20.0).color(ink()));
        ui.add(egui::Label::new(egui::RichText::new(note).small().color(muted())).wrap());
    });
}

fn warning_note(ui: &mut egui::Ui, title: &str, body: &str) {
    egui::Frame::NONE
        .fill(egui::Color32::from_rgb(255, 248, 235))
        .stroke(egui::Stroke::new(
            1.0,
            egui::Color32::from_rgb(226, 175, 88),
        ))
        .corner_radius(egui::CornerRadius::same(8))
        .inner_margin(egui::Margin::same(10))
        .show(ui, |ui| {
            ui.label(egui::RichText::new(title).strong().color(amber()));
            ui.add(egui::Label::new(egui::RichText::new(body).small().color(ink())).wrap());
        });
}

fn ink() -> egui::Color32 {
    egui::Color32::from_rgb(23, 32, 42)
}

fn muted() -> egui::Color32 {
    egui::Color32::from_rgb(82, 97, 111)
}

fn border() -> egui::Color32 {
    egui::Color32::from_rgb(213, 222, 226)
}

fn border_strong() -> egui::Color32 {
    egui::Color32::from_rgb(172, 184, 194)
}

fn soft_surface() -> egui::Color32 {
    egui::Color32::from_rgb(241, 246, 245)
}

fn soft_blue() -> egui::Color32 {
    egui::Color32::from_rgb(225, 237, 251)
}

fn soft_green() -> egui::Color32 {
    egui::Color32::from_rgb(222, 241, 233)
}

fn blue() -> egui::Color32 {
    egui::Color32::from_rgb(29, 78, 216)
}

fn teal() -> egui::Color32 {
    egui::Color32::from_rgb(15, 118, 110)
}

fn green() -> egui::Color32 {
    egui::Color32::from_rgb(31, 122, 77)
}

fn amber() -> egui::Color32 {
    egui::Color32::from_rgb(180, 83, 9)
}

fn red() -> egui::Color32 {
    egui::Color32::from_rgb(185, 28, 28)
}

fn nav_button(ui: &mut egui::Ui, active: &mut WorkspaceTab, tab: WorkspaceTab, label: &str) {
    let selected = *active == tab;
    let fill = if selected {
        soft_blue()
    } else {
        egui::Color32::TRANSPARENT
    };
    let stroke = if selected {
        egui::Stroke::new(1.0, blue())
    } else {
        egui::Stroke::new(1.0, egui::Color32::TRANSPARENT)
    };
    let button = egui::Button::new(egui::RichText::new(label).strong())
        .selected(selected)
        .fill(fill)
        .stroke(stroke)
        .corner_radius(egui::CornerRadius::same(6));
    if ui
        .add_sized([ui.available_width(), 32.0], button)
        .on_hover_text(label)
        .clicked()
    {
        *active = tab;
    }
}

fn status_chip(ui: &mut egui::Ui, key: &str, value: &str) {
    egui::Frame::NONE
        .fill(soft_surface())
        .stroke(egui::Stroke::new(1.0, border()))
        .corner_radius(egui::CornerRadius::same(6))
        .inner_margin(egui::Margin::symmetric(8, 4))
        .show(ui, |ui| {
            ui.label(
                egui::RichText::new(format!("{key}={value}"))
                    .monospace()
                    .small()
                    .color(ink()),
            );
        });
}

fn profile_card_text(profile: InstallProfile) -> (&'static str, &'static str) {
    match profile {
        InstallProfile::DeveloperLocal => (
            "Best first impression",
            "Full project surface with Lat, LIR, Seal, docs, helpers, and dry-run authority.",
        ),
        InstallProfile::SealReportOnly => (
            "Minimal safe lane",
            "Report-only Seal and documentation lane for receipts and evidence.",
        ),
        InstallProfile::FedoraValidationVm => (
            "Fedora validation",
            "VM-oriented Fedora/Linux validation workspace and evidence path.",
        ),
        InstallProfile::Custom => (
            "Manual operator",
            "Advanced manual control after the guided defaults are understood.",
        ),
    }
}

fn lc_profile_button(
    ui: &mut egui::Ui,
    app: &mut LatticraInstallerApp,
    profile: LatticraConsoleProfile,
    note: &str,
) {
    let selected = app.config.lc.profile == profile;
    panel_card_with_stroke(if selected { teal() } else { border() }).show(ui, |ui| {
        ui.heading(egui::RichText::new(profile.label()).size(17.0).color(ink()));
        ui.add(egui::Label::new(note).wrap());
        ui.add(
            egui::Label::new(egui::RichText::new(profile.detail()).small().color(muted())).wrap(),
        );
        if app.config.lc.profile == profile {
            status_chip(ui, "selected", "1");
        } else if ui
            .add(egui::Button::new("Use profile").fill(soft_blue()))
            .clicked()
        {
            app.apply_lc_profile(profile);
        }
    });
}

fn workbench_card(ui: &mut egui::Ui, title: &str, body: &str) {
    panel_card().show(ui, |ui| {
        ui.set_min_height(96.0);
        ui.heading(egui::RichText::new(title).size(17.0).color(ink()));
        ui.add(egui::Label::new(body).wrap());
    });
}

fn seal_profile_button(
    ui: &mut egui::Ui,
    app: &mut LatticraInstallerApp,
    profile: SealCryptoProfile,
    note: &str,
) {
    let selected = app.config.seal.crypto_profile == profile;
    panel_card_with_stroke(if selected { teal() } else { border() }).show(ui, |ui| {
        ui.heading(egui::RichText::new(profile.label()).size(17.0).color(ink()));
        ui.add(egui::Label::new(note).wrap());
        ui.add(
            egui::Label::new(egui::RichText::new(profile.detail()).small().color(muted())).wrap(),
        );
        if app.config.seal.crypto_profile == profile {
            status_chip(ui, "selected", "1");
        } else if ui
            .add(egui::Button::new("Use profile").fill(soft_blue()))
            .clicked()
        {
            app.apply_seal_crypto_profile(profile);
        }
    });
}

fn procedure_row(ui: &mut egui::Ui, number: &str, title: &str, body: &str) {
    panel_card().show(ui, |ui| {
        ui.horizontal_top(|ui| {
            status_chip(ui, "step", number);
            ui.vertical(|ui| {
                ui.label(egui::RichText::new(title).strong().color(ink()));
                ui.add(egui::Label::new(body).wrap());
            });
        });
    });
}

fn checkbox_note(ui: &mut egui::Ui, value: &mut bool, label: &str, note: &str) {
    panel_card().show(ui, |ui| {
        ui.checkbox(value, egui::RichText::new(label).strong());
        ui.add(egui::Label::new(egui::RichText::new(note).small().color(muted())).wrap());
    });
    ui.add_space(4.0);
}

fn labeled_text_field(ui: &mut egui::Ui, label: &str, value: &mut String) {
    if ui.available_width() < 520.0 {
        ui.label(egui::RichText::new(label).strong().color(ink()));
        ui.add(
            egui::TextEdit::singleline(value)
                .desired_width(ui.available_width())
                .margin(egui::Margin::symmetric(8, 6)),
        );
        return;
    }

    ui.horizontal(|ui| {
        ui.set_min_width(150.0);
        ui.label(egui::RichText::new(label).strong().color(ink()));
        ui.add(
            egui::TextEdit::singleline(value)
                .desired_width(ui.available_width())
                .margin(egui::Margin::symmetric(8, 6)),
        );
    });
}

fn parse_phase_line(line: &str) -> Option<(usize, usize, String)> {
    let rest = line.strip_prefix("PHASE ")?;
    let (fraction, title) = rest.split_once(':')?;
    let (index, total) = fraction.trim().split_once('/')?;
    Some((
        index.trim().parse().ok()?,
        total.trim().parse().ok()?,
        title.trim().to_owned(),
    ))
}

fn blend(a: egui::Color32, b: egui::Color32, t: f32) -> egui::Color32 {
    let t = t.clamp(0.0, 1.0);
    let mix = |x: u8, y: u8| -> u8 { (x as f32 + (y as f32 - x as f32) * t).round() as u8 };
    egui::Color32::from_rgb(mix(a.r(), b.r()), mix(a.g(), b.g()), mix(a.b(), b.b()))
}

pub fn run() -> eframe::Result<()> {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default()
            .with_inner_size([1280.0, 820.0])
            .with_min_inner_size([760.0, 560.0])
            .with_maximized(true)
            .with_resizable(true)
            .with_title(format!("Latticra Panel v{PANEL_VERSION}"))
            .with_app_id("latticra-panel"),
        ..Default::default()
    };

    eframe::run_native(
        &format!("Latticra Panel v{PANEL_VERSION}"),
        options,
        Box::new(|_| Ok(Box::<LatticraInstallerApp>::default())),
    )
}
