use crate::config::{
    render_plan, Components, InstallBehavior, InstallProfile, InstallerConfig,
    LatticraConsoleConfig, LatticraConsoleProfile, Safety, SealConfig, SealCryptoProfile,
    UpdaterConfig,
};
use crate::engine::{self, InstallEvent, RemovalOperation};
use eframe::egui;
use std::fmt::Write as _;
use std::path::Path;
use std::sync::mpsc::Receiver;
use std::time::Duration;

const PANEL_VERSION: &str = env!("CARGO_PKG_VERSION");
const PANEL_BUILD: &str = "gui-workbench";
const UI_CONFIG_ARTIFACT: &str = "latticra-installer-config.toml";
const UI_PLAN_ARTIFACT: &str = "latticra-installer-plan.txt";
const SEAL_PNG: &[u8] = include_bytes!("../assets/latticra-panel.png");
const COMPACT_LAYOUT_WIDTH: f32 = 1600.0;
const NARROW_LAYOUT_WIDTH: f32 = 960.0;
const LEFT_PANEL_WIDTH: f32 = 180.0;
const LEFT_PANEL_NARROW_WIDTH: f32 = 170.0;
const RIGHT_PANEL_MAX_WIDTH: f32 = 640.0;
const DASHBOARD_SUMMARY_FOUR_COLUMN_WIDTH: f32 = 1100.0;
const DASHBOARD_SUMMARY_TWO_COLUMN_WIDTH: f32 = 620.0;
const CARD_GRID_TWO_COLUMN_WIDTH: f32 = 1180.0;
const CARD_GRID_THREE_COLUMN_WIDTH: f32 = 1320.0;
const CARD_GRID_FOUR_COLUMN_WIDTH: f32 = 1540.0;
const PROFILE_CARD_TWO_COLUMN_WIDTH: f32 = CARD_GRID_TWO_COLUMN_WIDTH;
const RUNNING_CONSOLE_MAX_HEIGHT: f32 = 220.0;
const IDLE_CONSOLE_MAX_HEIGHT: f32 = 520.0;
const CONSOLE_MAX_LINE_CHARS: usize = 1024;
const RUNNING_EVIDENCE_MAX_HEIGHT: f32 = 420.0;
const IDLE_EVIDENCE_MAX_HEIGHT: f32 = 220.0;
const RUNNING_PROGRESS_MAX_WIDTH: f32 = 520.0;
const RUNNING_RECENT_LOG_MAX_HEIGHT: f32 = 180.0;
const RUNNING_MONITOR_WIDE_WIDTH: f32 = 980.0;
const NADIA_PANEL_COMMANDS: &[(&str, &str)] = &[
    ("status", "Stage-48 status and authority summary"),
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
    (
        "prompt-evaluation-result-release-receipt-review",
        "Stage-36 prompt-evaluation result release receipt review contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition",
        "Stage-37 prompt-evaluation result release receipt review disposition contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release",
        "Stage-38 prompt-evaluation result release receipt review disposition release contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt",
        "Stage-39 prompt-evaluation result release receipt review disposition release receipt contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review",
        "Stage-40 prompt-evaluation result release receipt review disposition release receipt review contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition",
        "Stage-41 prompt-evaluation result release receipt review disposition release receipt review disposition contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release",
        "Stage-42 prompt-evaluation result release receipt review disposition release receipt review disposition release contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt",
        "Stage-43 prompt-evaluation result release receipt review disposition release receipt review disposition release receipt contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review",
        "Stage-44 prompt-evaluation result release receipt review disposition release receipt review disposition release receipt review contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition",
        "Stage-45 prompt-evaluation result release receipt review disposition release receipt review disposition release receipt review disposition contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release",
        "Stage-46 prompt-evaluation result release receipt review disposition release receipt review disposition release receipt review disposition release contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt",
        "Stage-47 prompt-evaluation result release receipt review disposition release receipt review disposition release receipt review disposition release receipt contract",
    ),
    (
        "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review",
        "Stage-48 prompt-evaluation result release receipt review disposition release receipt review disposition release receipt review disposition release receipt review contract",
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

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum ProcedureState {
    Done,
    Current,
    Ready,
    Locked,
    Pending,
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
            status: "Ready. Generate a plan, run Dry-Install, then review evidence.".to_owned(),
            logs: Vec::new(),
            console_lines: vec![
                format!("Latticra Panel v{PANEL_VERSION} bounded operator console online."),
                "Authority baseline: root=0 network=0 runtime_enforcement=0.".to_owned(),
                "Type help for panel commands, or use Command shortcuts below.".to_owned(),
                "Start here: plan -> dry-run -> review evidence -> guarded local mode.".to_owned(),
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
        let line = line.into();
        self.console_lines.push(sanitize_console_line(&line));
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
        match ui_plan_artifact(&self.config) {
            Ok((config, plan)) => {
                self.config = config;
                self.plan = plan;
            }
            Err(err) => {
                self.plan = blocked_ui_plan(&err);
            }
        }
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
        match ui_config_toml_artifact(&self.config) {
            Ok((config, toml)) => {
                self.config = config;
                match write_ui_artifact(UI_CONFIG_ARTIFACT, toml.as_bytes()) {
                    Ok(_) => {
                        self.status = "Saved latticra-installer-config.toml".to_owned();
                        self.push_console("saved latticra-installer-config.toml");
                    }
                    Err(err) => self.status = format!("Could not save config: {err}"),
                }
            }
            Err(err) => {
                self.status = format!("Could not save config: {err}");
                self.push_console(format!("blocked config save: {err}"));
            }
        }
    }

    fn write_plan(&mut self) {
        match ui_plan_artifact(&self.config) {
            Ok((config, plan)) => {
                self.config = config;
                self.plan = plan;
                match write_ui_artifact(UI_PLAN_ARTIFACT, self.plan.as_bytes()) {
                    Ok(_) => {
                        self.status = "Wrote latticra-installer-plan.txt".to_owned();
                        self.push_console("wrote latticra-installer-plan.txt");
                    }
                    Err(err) => self.status = format!("Could not write plan: {err}"),
                }
            }
            Err(err) => {
                self.plan = blocked_ui_plan(&err);
                self.status = format!("Could not write plan: {err}");
                self.push_console(format!("blocked plan write: {err}"));
            }
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

    fn panel_can_write_artifacts(&self) -> Result<(), String> {
        sanitized_ui_artifact_config(&self.config).map(|_| ())
    }

    fn console_report_config(&mut self) -> Option<InstallerConfig> {
        match sanitized_ui_artifact_config(&self.config) {
            Ok(config) => {
                self.config = config.clone();
                Some(config)
            }
            Err(err) => {
                self.status = format!("Console command blocked: {err}");
                self.push_console(format!(
                    "blocked: console command requires valid authority fields: {err}"
                ));
                None
            }
        }
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

    fn open_next_surface(&mut self) {
        match self.install_state {
            InstallState::Running | InstallState::Complete | InstallState::Failed => {
                self.active_tab = WorkspaceTab::Evidence;
                self.show_plan_over_log = self.install_state != InstallState::Running;
            }
            InstallState::Idle if self.guarded_local_ack_missing() => {
                self.active_tab = WorkspaceTab::Authority;
            }
            InstallState::Idle if self.logs.is_empty() => {
                self.refresh_plan();
                self.active_tab = WorkspaceTab::Evidence;
                self.show_plan_over_log = true;
            }
            InstallState::Idle if self.config.safety.dry_run => {
                self.active_tab = WorkspaceTab::Evidence;
                self.show_plan_over_log = false;
            }
            InstallState::Idle => {
                self.active_tab = WorkspaceTab::Delivery;
            }
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

        if console_command_requires_authority_floor(parts.as_slice())
            && self.console_report_config().is_none()
        {
            return;
        }

        match parts.as_slice() {
            ["help"] | ["?"] => {
                self.push_console(
                    "panel: help, status, updater status, updater plan, updater dry-run, updater apply, lc commands, lc status, lc install-config, lc session, lc workspace, lc namespace, lc rootfs, lc packages, lc init, lc services, lc service-schema, lc profile hosted|panel|standalone|host|os|custom, plan, save, dry-run, reset, uninstall, clear, nadia status, nadia commands",
                );
                self.push_console(
                    "nadia: use `nadia commands` for the full Stage-1 through Stage-48 command map",
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
                    "standalone_console={}",
                    self.config.lc.install.standalone_console
                ));
                self.push_console("standalone_installable=1");
                self.push_console("standalone_requires_panel=0");
                self.push_console(format!(
                    "standalone_command_wrapper={}",
                    self.config.lc.install.command_wrapper
                ));
                self.push_console("standalone_console_status=metadata-only-standalone-contract");
                self.push_console("standalone_contract_present=1");
                self.push_console(format!(
                    "session_contract_profile={}",
                    self.config.lc.session_contract_profile
                ));
                self.push_console("session_contract_status=metadata-only-contract");
                self.push_console("session_contract_present=1");
                self.push_console(format!(
                    "workspace_contract_profile={}",
                    self.config.lc.workspace_contract_profile
                ));
                self.push_console("workspace_contract_status=metadata-only-contract");
                self.push_console("workspace_contract_present=1");
                self.push_console(format!(
                    "namespace_contract_profile={}",
                    self.config.lc.namespace_contract_profile
                ));
                self.push_console("namespace_contract_status=metadata-only-contract");
                self.push_console("namespace_contract_present=1");
                self.push_console(format!(
                    "rootfs_contract_profile={}",
                    self.config.lc.rootfs_contract_profile
                ));
                self.push_console("rootfs_contract_status=metadata-only-contract");
                self.push_console("rootfs_contract_present=1");
                self.push_console(format!(
                    "packages_contract_profile={}",
                    self.config.lc.packages_contract_profile
                ));
                self.push_console("packages_contract_status=metadata-only-contract");
                self.push_console("packages_contract_present=1");
                self.push_console(format!(
                    "init_contract_profile={}",
                    self.config.lc.init_contract_profile
                ));
                self.push_console("init_contract_status=metadata-only-contract");
                self.push_console("init_contract_present=1");
                self.push_console(format!(
                    "services_contract_profile={}",
                    self.config.lc.services_contract_profile
                ));
                self.push_console("services_contract_status=metadata-only-contract");
                self.push_console("services_contract_present=1");
                self.push_console(format!(
                    "service_schema_contract_profile={}",
                    self.config.lc.service_schema_contract_profile
                ));
                self.push_console("service_schema_contract_status=metadata-only-contract");
                self.push_console("service_schema_contract_present=1");
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
                    "session_contract_profile={}",
                    self.config.lc.session_contract_profile
                ));
                self.push_console("session_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "workspace_contract_profile={}",
                    self.config.lc.workspace_contract_profile
                ));
                self.push_console("workspace_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "namespace_contract_profile={}",
                    self.config.lc.namespace_contract_profile
                ));
                self.push_console("namespace_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "rootfs_contract_profile={}",
                    self.config.lc.rootfs_contract_profile
                ));
                self.push_console("rootfs_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "packages_contract_profile={}",
                    self.config.lc.packages_contract_profile
                ));
                self.push_console("packages_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "init_contract_profile={}",
                    self.config.lc.init_contract_profile
                ));
                self.push_console("init_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "services_contract_profile={}",
                    self.config.lc.services_contract_profile
                ));
                self.push_console("services_contract_status=metadata-only-contract");
                self.push_console(format!(
                    "service_schema_contract_profile={}",
                    self.config.lc.service_schema_contract_profile
                ));
                self.push_console("service_schema_contract_status=metadata-only-contract");
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
                    "receipt_payload_artifact_review_receipt_draft_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_draft_profile
                ));
                self.push_console(
                    "receipt_payload_artifact_review_receipt_draft_status=metadata-only-review-receipt-draft",
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
                    "session_contract_required={}",
                    self.config.lc.require_session_contract
                ));
                self.push_console(format!(
                    "workspace_contract_required={}",
                    self.config.lc.require_workspace_contract
                ));
                self.push_console(format!(
                    "namespace_contract_required={}",
                    self.config.lc.require_namespace_contract
                ));
                self.push_console(format!(
                    "rootfs_contract_required={}",
                    self.config.lc.require_rootfs_contract
                ));
                self.push_console(format!(
                    "packages_contract_required={}",
                    self.config.lc.require_packages_contract
                ));
                self.push_console(format!(
                    "init_contract_required={}",
                    self.config.lc.require_init_contract
                ));
                self.push_console(format!(
                    "services_contract_required={}",
                    self.config.lc.require_services_contract
                ));
                self.push_console(format!(
                    "service_schema_contract_required={}",
                    self.config.lc.require_service_schema_contract
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
                    "standalone_console={}",
                    self.config.lc.install.standalone_console
                ));
                self.push_console("standalone_installable=1");
                self.push_console("standalone_requires_panel=0");
                self.push_console(format!(
                    "standalone_command_wrapper={}",
                    self.config.lc.install.command_wrapper
                ));
                self.push_console("standalone_contract_present=1");
                self.push_console("session_contract_present=1");
                self.push_console("workspace_contract_present=1");
                self.push_console("namespace_contract_present=1");
                self.push_console("rootfs_contract_present=1");
                self.push_console("packages_contract_present=1");
                self.push_console("init_contract_present=1");
                self.push_console("services_contract_present=1");
                self.push_console("service_schema_contract_present=1");
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
            ["lc", "profile", "standalone"] | ["lc", "profile", "standalone_console"] => {
                self.apply_lc_profile(LatticraConsoleProfile::Standalone);
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
                self.push_console("lc.commands=help,status,plan,save,dry-run,reset,uninstall,pwd,cd,lc status,lc commands,lc install-config,lc standalone,lc session,lc workspace,lc namespace,lc rootfs,lc packages,lc init,lc services,lc service-schema,lc profiles,lc receipts,lc receipt-request,lc receipt-payload,lc receipt-artifact,lc receipt-artifact-review,lc receipt-review-receipt,lc receipt-review-draft,lc receipt-materialization-plan,lc signature-request,lc substrate,lc host,lc host-contract,lc host-inventory,lc host-adapter,lc os-contract,lc vm-evidence,lc os");
                self.push_console("registry_authority=metadata-only external_host_processes=0");
            }
            ["lc", "standalone"] | ["console", "standalone"] | ["lc", "standalone-contract"] => {
                self.push_console("lc.standalone=Latticra Console standalone contract");
                self.push_console("standalone_console_profile=lc-standalone-console-v0");
                self.push_console("standalone_console_status=metadata-only-contract");
                self.push_console("standalone_contract_present=1");
                self.push_console(format!(
                    "standalone_console={}",
                    self.config.lc.install.standalone_console
                ));
                self.push_console("standalone_installable=1 standalone_requires_panel=0");
                self.push_console(format!(
                    "standalone_command_wrapper={}",
                    self.config.lc.install.command_wrapper
                ));
                self.push_console("panel_required_for_runtime=0");
                self.push_console("command_surface=lc standalone");
                self.push_console(
                    "shell_execution_allowed=0 host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "session"] | ["console", "session"] | ["lc", "session-contract"] => {
                self.push_console("lc.session=Latticra Console session contract");
                self.push_console(format!(
                    "session_profile={}",
                    self.config.lc.session_contract_profile
                ));
                self.push_console("session_status=metadata-only-contract");
                self.push_console("session_contract_present=1");
                self.push_console("session_kind=operator-base");
                self.push_console(
                    "standalone_compatible=1 panel_embedded_compatible=1 host_embedded_planned=1",
                );
                self.push_console("session_manifest_present=0 session_manifest_write_allowed=0");
                self.push_console("runtime_session_created=0 runtime_process_spawn_allowed=0 runtime_invocation_allowed=0 interactive_shell_allowed=0");
                self.push_console("command_surface=lc session");
                self.push_console(
                    "promotion_gate=lc_session_contract_before_runtime_or_host_embedding",
                );
                self.push_console(
                    "host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "workspace"] | ["console", "workspace"] | ["lc", "workspace-contract"] => {
                self.push_console("lc.workspace=Latticra Console workspace contract");
                self.push_console(format!(
                    "workspace_profile={}",
                    self.config.lc.workspace_contract_profile
                ));
                self.push_console("workspace_status=metadata-only-contract");
                self.push_console("workspace_contract_present=1");
                self.push_console("workspace_kind=operator-root");
                self.push_console("workspace_root=share/latticra/lc/workspace");
                self.push_console("workspace_mount_present=0 workspace_mount_allowed=0");
                self.push_console("host_workspace_bind_allowed=0");
                self.push_console(
                    "workspace_manifest_present=0 workspace_manifest_write_allowed=0",
                );
                self.push_console(
                    "workspace_file_read_allowed=0 workspace_file_write_allowed=0 workspace_mutation_allowed=0",
                );
                self.push_console(
                    "runtime_session_required_before_workspace_runtime=1 session_contract_required=1",
                );
                self.push_console("host_adapter_contract_required=1 os_base_contract_required=1");
                self.push_console("command_surface=lc workspace");
                self.push_console(
                    "promotion_gate=lc_workspace_contract_before_host_mount_or_os_workspace",
                );
                self.push_console(
                    "host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "namespace"] | ["console", "namespace"] | ["lc", "namespace-contract"] => {
                self.push_console("lc.namespace=Latticra Console namespace contract");
                self.push_console(format!(
                    "namespace_profile={}",
                    self.config.lc.namespace_contract_profile
                ));
                self.push_console("namespace_status=metadata-only-contract");
                self.push_console("namespace_contract_present=1");
                self.push_console("namespace_kind=lc-internal-os-namespace");
                self.push_console("namespace_root=share/latticra/lc/namespace");
                self.push_console("namespace_mount_present=0 namespace_mount_allowed=0");
                self.push_console("rootfs_present=0 rootfs_mount_allowed=0");
                self.push_console("path_resolver_present=0 path_resolution_allowed=0");
                self.push_console("host_path_projection_allowed=0");
                self.push_console("workspace_namespace_bind_allowed=0");
                self.push_console(
                    "namespace_file_read_allowed=0 namespace_file_write_allowed=0 namespace_mutation_allowed=0",
                );
                self.push_console(
                    "workspace_contract_required=1 session_contract_required=1 runtime_boundary_required=1",
                );
                self.push_console("command_surface=lc namespace");
                self.push_console(
                    "promotion_gate=lc_namespace_contract_before_rootfs_or_path_projection",
                );
                self.push_console(
                    "host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "rootfs"] | ["console", "rootfs"] | ["lc", "rootfs-contract"] => {
                self.push_console("lc.rootfs=Latticra Console rootfs contract");
                self.push_console(format!(
                    "rootfs_profile={}",
                    self.config.lc.rootfs_contract_profile
                ));
                self.push_console("rootfs_status=metadata-only-contract");
                self.push_console("rootfs_contract_present=1");
                self.push_console("rootfs_kind=lc-internal-root-filesystem");
                self.push_console("rootfs_root=share/latticra/lc/rootfs");
                self.push_console("rootfs_manifest_present=0 rootfs_manifest_write_allowed=0");
                self.push_console(
                    "rootfs_image_present=0 rootfs_image_create_allowed=0 rootfs_image_open_allowed=0",
                );
                self.push_console("rootfs_mount_present=0 rootfs_mount_allowed=0");
                self.push_console(
                    "rootfs_package_manifest_present=0 rootfs_package_install_allowed=0",
                );
                self.push_console(
                    "rootfs_file_read_allowed=0 rootfs_file_write_allowed=0 rootfs_mutation_allowed=0",
                );
                self.push_console(
                    "namespace_contract_required=1 workspace_contract_required=1 session_contract_required=1",
                );
                self.push_console("os_base_contract_required=1 runtime_boundary_required=1");
                self.push_console("command_surface=lc rootfs");
                self.push_console(
                    "promotion_gate=lc_rootfs_contract_before_image_mount_or_package_write",
                );
                self.push_console(
                    "host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "packages"]
            | ["console", "packages"]
            | ["lc", "packages-contract"]
            | ["lc", "package-manifest"] => {
                self.push_console("lc.packages=Latticra Console packages contract");
                self.push_console(format!(
                    "packages_profile={}",
                    self.config.lc.packages_contract_profile
                ));
                self.push_console("packages_status=metadata-only-contract");
                self.push_console("packages_contract_present=1");
                self.push_console("packages_kind=lc-rootfs-package-manifest-envelope");
                self.push_console("packages_root=share/latticra/lc/packages");
                self.push_console("package_manifest_present=0 package_manifest_write_allowed=0");
                self.push_console(
                    "package_catalog_present=0 package_catalog_read_allowed=0 package_catalog_write_allowed=0",
                );
                self.push_console(
                    "package_download_allowed=0 package_install_plan_present=0 package_install_plan_write_allowed=0",
                );
                self.push_console(
                    "package_manager_present=0 package_manager_execution_allowed=0 package_script_execution_allowed=0",
                );
                self.push_console(
                    "rootfs_package_manifest_present=0 rootfs_package_install_allowed=0 rootfs_file_write_allowed=0",
                );
                self.push_console(
                    "rootfs_contract_required=1 namespace_contract_required=1 workspace_contract_required=1",
                );
                self.push_console("os_base_contract_required=1 runtime_boundary_required=1");
                self.push_console("command_surface=lc packages");
                self.push_console(
                    "promotion_gate=lc_packages_contract_before_catalog_install_or_rootfs_write",
                );
                self.push_console(
                    "host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "init"] | ["console", "init"] | ["lc", "init-contract"] => {
                self.push_console("lc.init=Latticra Console init contract");
                self.push_console(format!(
                    "init_profile={}",
                    self.config.lc.init_contract_profile
                ));
                self.push_console("init_status=metadata-only-contract");
                self.push_console("init_contract_present=1");
                self.push_console("init_kind=lc-internal-init-and-service-envelope");
                self.push_console("init_root=share/latticra/lc/init");
                self.push_console("init_manifest_present=0 init_manifest_write_allowed=0");
                self.push_console("pid1_claim_allowed=0");
                self.push_console("init_process_present=0 init_process_launch_allowed=0");
                self.push_console("service_registry_present=0 service_registry_write_allowed=0");
                self.push_console(
                    "service_start_allowed=0 service_stop_allowed=0 service_restart_allowed=0",
                );
                self.push_console("process_supervision_allowed=0");
                self.push_console("startup_order_present=0 startup_order_write_allowed=0");
                self.push_console("services_contract_required=1");
                self.push_console(
                    "rootfs_contract_required=1 packages_contract_required=1 namespace_contract_required=1",
                );
                self.push_console("os_base_contract_required=1 runtime_boundary_required=1");
                self.push_console("command_surface=lc init");
                self.push_console("related_services_command=lc services");
                self.push_console(
                    "promotion_gate=lc_init_contract_before_pid1_service_supervision_or_boot",
                );
                self.push_console(
                    "host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "services"]
            | ["console", "services"]
            | ["lc", "services-contract"]
            | ["lc", "service-registry"] => {
                self.push_console("lc.services=Latticra Console services contract");
                self.push_console(format!(
                    "services_profile={}",
                    self.config.lc.services_contract_profile
                ));
                self.push_console("services_status=metadata-only-contract");
                self.push_console("services_contract_present=1");
                self.push_console("services_kind=lc-service-registry-envelope");
                self.push_console("services_root=share/latticra/lc/services");
                self.push_console("service_registry_present=0 service_registry_read_allowed=0 service_registry_write_allowed=0");
                self.push_console("service_manifest_present=0 service_manifest_write_allowed=0");
                self.push_console(
                    "service_definition_present=0 service_definition_write_allowed=0",
                );
                self.push_console(
                    "service_dependency_graph_present=0 service_dependency_graph_write_allowed=0",
                );
                self.push_console("startup_order_present=0 startup_order_write_allowed=0");
                self.push_console(
                    "service_enable_allowed=0 service_disable_allowed=0 service_start_allowed=0",
                );
                self.push_console(
                    "service_stop_allowed=0 service_restart_allowed=0 service_reload_allowed=0",
                );
                self.push_console("service_health_check_allowed=0 process_supervision_allowed=0");
                self.push_console(
                    "pid1_claim_allowed=0 service_schema_contract_required=1 init_contract_required=1",
                );
                self.push_console(
                    "rootfs_contract_required=1 packages_contract_required=1 namespace_contract_required=1",
                );
                self.push_console("os_base_contract_required=1 runtime_boundary_required=1");
                self.push_console("command_surface=lc services");
                self.push_console("related_service_schema_command=lc service-schema");
                self.push_console("related_init_command=lc init");
                self.push_console(
                    "promotion_gate=lc_services_contract_before_service_registry_or_supervision",
                );
                self.push_console(
                    "host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
            }
            ["lc", "service-schema"]
            | ["console", "service-schema"]
            | ["lc", "service-schema-contract"]
            | ["lc", "service-definition-schema"] => {
                self.push_console("lc.service_schema=Latticra Console service schema contract");
                self.push_console(format!(
                    "service_schema_profile={}",
                    self.config.lc.service_schema_contract_profile
                ));
                self.push_console("service_schema_status=metadata-only-contract");
                self.push_console("service_schema_contract_present=1");
                self.push_console("service_schema_kind=lc-service-definition-schema-envelope");
                self.push_console("service_schema_root=share/latticra/lc/services");
                self.push_console("service_schema_file=definition-schema.toml");
                self.push_console("service_schema_artifact_present=1");
                self.push_console("service_schema_read_allowed=0 service_schema_write_allowed=0");
                self.push_console("service_definition_schema_version=0");
                self.push_console(
                    "service_definition_required_fields=name,kind,scope,authority,dependencies,startup_order",
                );
                self.push_console(
                    "service_definition_optional_fields=description,environment,health,receipts",
                );
                self.push_console(
                    "service_definition_present=0 service_definition_read_allowed=0 service_definition_write_allowed=0",
                );
                self.push_console("service_definition_validation_allowed=0");
                self.push_console("service_dependency_resolution_allowed=0");
                self.push_console("service_authority_binding_allowed=0");
                self.push_console(
                    "service_registry_write_allowed=0 service_manifest_write_allowed=0",
                );
                self.push_console(
                    "service_enable_allowed=0 service_disable_allowed=0 service_start_allowed=0",
                );
                self.push_console(
                    "service_stop_allowed=0 service_restart_allowed=0 service_reload_allowed=0",
                );
                self.push_console("service_health_check_allowed=0 process_supervision_allowed=0");
                self.push_console(
                    "services_contract_required=1 init_contract_required=1 rootfs_contract_required=1 packages_contract_required=1",
                );
                self.push_console(
                    "namespace_contract_required=1 workspace_contract_required=1 session_contract_required=1",
                );
                self.push_console("os_base_contract_required=1 runtime_boundary_required=1");
                self.push_console("receipt_required_before_service_schema_runtime=1");
                self.push_console("command_surface=lc service-schema");
                self.push_console("related_services_command=lc services");
                self.push_console("related_init_command=lc init");
                self.push_console(
                    "promotion_gate=lc_service_schema_contract_before_service_definition_validation",
                );
                self.push_console(
                    "host_process_launch_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 production_os_claim=0",
                );
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
                    "session_contract_required={}",
                    self.config.lc.require_session_contract
                ));
                self.push_console("session_contract_command=lc session");
                self.push_console(format!(
                    "workspace_contract_required={}",
                    self.config.lc.require_workspace_contract
                ));
                self.push_console("workspace_contract_present=1");
                self.push_console("workspace_contract_command=lc workspace");
                self.push_console(format!(
                    "namespace_contract_required={}",
                    self.config.lc.require_namespace_contract
                ));
                self.push_console("namespace_contract_present=1");
                self.push_console("namespace_contract_command=lc namespace");
                self.push_console(format!(
                    "rootfs_contract_required={}",
                    self.config.lc.require_rootfs_contract
                ));
                self.push_console("rootfs_contract_present=1");
                self.push_console("rootfs_contract_command=lc rootfs");
                self.push_console(format!(
                    "packages_contract_required={}",
                    self.config.lc.require_packages_contract
                ));
                self.push_console("packages_contract_present=1");
                self.push_console("packages_contract_command=lc packages");
                self.push_console(format!(
                    "init_contract_required={}",
                    self.config.lc.require_init_contract
                ));
                self.push_console("init_contract_present=1");
                self.push_console("init_contract_command=lc init");
                self.push_console(format!(
                    "services_contract_required={}",
                    self.config.lc.require_services_contract
                ));
                self.push_console("services_contract_present=1");
                self.push_console("services_contract_command=lc services");
                self.push_console(format!(
                    "service_schema_contract_receipt_required={}",
                    self.config.lc.require_service_schema_contract
                ));
                self.push_console("service_schema_contract_present=1");
                self.push_console("service_schema_contract_command=lc service-schema");
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
                    "receipt_payload_artifact_review_receipt_draft_required={}",
                    self.config
                        .lc
                        .require_receipt_payload_artifact_review_receipt_draft
                ));
                self.push_console("receipt_payload_artifact_review_receipt_draft_present=1");
                self.push_console(
                    "receipt_payload_artifact_review_receipt_draft_command=lc receipt-review-draft",
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
                self.push_console("receipt_surfaces=profile,session,workspace,namespace,rootfs,packages,init,services,service-schema,host-contract,host-inventory,host-adapter,runtime-boundary");
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
                self.push_console("requested_surfaces=profile,session,workspace,namespace,rootfs,packages,init,services,service-schema,host-contract,host-inventory,host-adapter,runtime-boundary");
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
                    "review_receipt_draft_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_draft_profile
                ));
                self.push_console(
                    "review_receipt_draft_required=1 review_receipt_draft_contract_present=1",
                );
                self.push_console("review_receipt_draft_command=lc receipt-review-draft");
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
                self.push_console("related_review_receipt_draft_command=lc receipt-review-draft");
                self.push_console("related_review_command=lc receipt-artifact-review");
                self.push_console(
                    "related_materialization_plan_command=lc receipt-materialization-plan",
                );
                self.push_console(
                    "file_write_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0",
                );
            }
            ["lc", "receipt-review-draft"]
            | ["console", "receipt-review-draft"]
            | ["lc", "review-receipt-draft"]
            | ["console", "review-receipt-draft"]
            | ["lc", "artifact-review-receipt-draft"]
            | ["console", "artifact-review-receipt-draft"]
            | ["lc", "payload-artifact-review-receipt-draft"]
            | ["console", "payload-artifact-review-receipt-draft"]
            | ["lc", "receipt-payload-artifact-review-receipt-draft"]
            | ["console", "receipt-payload-artifact-review-receipt-draft"] => {
                self.push_console(
                    "lc.receipt_payload_artifact_review_receipt_draft=Latticra Console receipt payload artifact review receipt draft contract",
                );
                self.push_console(format!(
                    "review_receipt_draft_profile={}",
                    self.config
                        .lc
                        .receipt_payload_artifact_review_receipt_draft_profile
                ));
                self.push_console(
                    "review_receipt_draft_status=metadata-only-draft-contract review_receipt_draft_contract_present=1",
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
                    "draft_review_receipt_required=1 draft_review_receipt_present=0 draft_review_receipt_artifact_present=0",
                );
                self.push_console(
                    "draft_review_receipt_write_allowed=0 draft_review_receipt_signed=0 draft_review_receipt_hash_recorded=0 draft_review_receipt_path_recorded=0",
                );
                self.push_console(
                    "review_receipt_materialization_allowed=0 review_receipt_signing_allowed=0",
                );
                self.push_console("materialization_preconditions_met=0 materialization_allowed=0");
                self.push_console(
                    "payload_artifact_present=0 payload_materialized=0 payload_write_allowed=0",
                );
                self.push_console(
                    "signature_request_binding_allowed=0 signature_request_binding_artifact_present=0",
                );
                self.push_console("receipt_write_allowed=0 receipt_signed=0");
                self.push_console(
                    "promotion_gate=lc_receipt_payload_artifact_review_receipt_draft_before_review_receipt_creation",
                );
                self.push_console("command_surface=lc receipt-review-draft");
                self.push_console("related_review_receipt_command=lc receipt-review-receipt");
                self.push_console("related_review_command=lc receipt-artifact-review");
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
                    "prompt_evaluation_result_release_receipt_review_contract_stage=36-prompt-evaluation-result-release-receipt-review-contract",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_contract_stage=37-prompt-evaluation-result-release-receipt-review-disposition-contract",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_contract_stage=38-prompt-evaluation-result-release-receipt-review-disposition-release-contract",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_contract_stage=39-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-contract",
                );
                self.push_console(
                    "stage=39 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_signed=0 runtime_invoked=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_contract_stage=40-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-contract",
                );
                self.push_console(
                    "stage=40 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_signed=0 runtime_invoked=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_contract_stage=41-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-contract",
                );
                self.push_console(
                    "stage=41 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_decision_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_contract_stage=42-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-contract",
                );
                self.push_console(
                    "stage=42 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_published=0 runtime_invoked=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract_stage=43-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract",
                );
                self.push_console(
                    "stage=43 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_signed=0 runtime_invoked=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract_stage=44-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract",
                );
                self.push_console(
                    "stage=44 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_findings_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_contract_stage=45-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-contract",
                );
                self.push_console(
                    "stage=45 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_findings_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_contract_stage=46-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-contract",
                );
                self.push_console(
                    "stage=46 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_published=0 runtime_invoked=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract_stage=47-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract",
                );
                self.push_console(
                    "stage=47 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_signed=0 runtime_invoked=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract_stage=48-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract",
                );
                self.push_console(
                    "stage=48 prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract; prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_record_created=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_findings_recorded=0 runtime_invoked=0",
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
            ["nadia", "prompt-evaluation-result-release-receipt-review"]
            | ["nadia", "evaluation-result-release-receipt-review"]
            | ["nadia", "prompt-result-release-receipt-review"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review=stage-36-prompt-evaluation-result-release-receipt-review-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_contract_status=contract_only prompt_evaluation_result_release_receipt_review_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_decision_recorded=0 prompt_evaluation_result_release_receipt_review_findings_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition"]
            | ["nadia", "prompt-result-release-receipt-review-disposition"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-contract"] => {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition=stage-37-prompt-evaluation-result-release-receipt-review-disposition-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_findings_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release=stage-38-prompt-evaluation-result-release-receipt-review-disposition-release-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_published=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt=stage-39-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_signed=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_published=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt-review"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt-review"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review=stage-40-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_findings_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt-review-disposition"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition=stage-41-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_findings_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt-review-disposition-release"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release=stage-42-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_published=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt=stage-43-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_signed=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review=stage-44-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_findings_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition=stage-45-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_findings_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release=stage-46-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_published=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt=stage-47-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_signed=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract=1",
                );
            }
            ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review"]
            | ["nadia", "evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review"]
            | ["nadia", "prompt-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review"]
            | ["nadia", "prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract"] =>
            {
                self.push_console(
                    "nadia_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review=stage-48-prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-contract",
                );
                self.push_console(
                    "panel_command=nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review",
                );
                self.push_console("panel_action=metadata-only");
                self.push_console(
                    "installed_cli=latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_contract_status=contract_only prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_record_created=0",
                );
                self.push_console(
                    "prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_decision_recorded=0 prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_findings_recorded=0 runtime_invoked=0",
                );
                self.push_console(
                    "requires_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_contract=1 requires_future_prompt_evaluation_result_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_release_receipt_review_disposition_contract=1",
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
                ui.label(egui::RichText::new("plan, dry-run, evidence, install").color(muted()));
            });
            ui.horizontal_wrapped(|ui| {
                status_chip(ui, "seal", self.config.seal.crypto_profile.label());
                status_chip(ui, "mode", self.config.execution_mode_label());
                status_chip(ui, "active", workspace_tab_key(self.active_tab));
                status_chip(ui, "next", self.next_action_label());
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
                    "guided local install workbench: plan, dry-run, evidence review, guarded install",
                )
                .color(muted()),
            );
        });
        ui.horizontal_wrapped(|ui| {
            status_chip(ui, "mode", self.config.execution_mode_label());
            status_chip(ui, "active", workspace_tab_key(self.active_tab));
            status_chip(ui, "next", self.next_action_label());
            status_chip(ui, "root", "0");
            status_chip(ui, "network", "0");
            status_chip(ui, "runtime", "0");
        });
        ui.add_space(2.0);
    }

    fn show_sidebar(&mut self, ui: &mut egui::Ui, compact: bool) {
        ui.vertical_centered(|ui| {
            if let Some(texture) = &self.seal_texture {
                let image_size = if compact { 72.0 } else { 104.0 };
                let image =
                    egui::Image::new(texture).fit_to_exact_size(egui::vec2(image_size, image_size));
                ui.add(image);
            }
            ui.heading("Latticra Panel");
            ui.label(egui::RichText::new(format!("Panel v{PANEL_VERSION}")).monospace());
            ui.add(
                egui::Label::new(
                    egui::RichText::new("Plan first. Install after evidence.").small(),
                )
                .wrap(),
            );
        });

        ui.add_space(6.0);
        sidebar_status_block(
            ui,
            self.active_tab,
            self.next_action_label(),
            self.install_state,
            self.guarded_local_ack,
        );

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
        ui.horizontal_wrapped(|ui| {
            if compact {
                status_chip(ui, "prod", "0");
                status_chip(ui, "root", "0");
                status_chip(ui, "net", "0");
                status_chip(ui, "rt", "0");
            } else {
                status_chip(ui, "production_installer_ready", "0");
                status_chip(ui, "root_authority", "0");
                status_chip(ui, "network_authority", "0");
                status_chip(ui, "runtime_enforcement_authority", "0");
            }
        });

        ui.separator();
        ui.label(egui::RichText::new("Quick mode").strong());
        let mode_button_width = ui.available_width();
        if ui
            .add_sized(
                [mode_button_width, 34.0],
                egui::Button::new("Use dry-run mode").fill(soft_blue()),
            )
            .clicked()
        {
            self.set_mode_dry();
        }
        let mode_button_width = ui.available_width();
        let local_mode_response = ui
            .add_enabled(
                self.guarded_local_ack,
                egui::Button::new("Use guarded local mode")
                    .min_size(egui::vec2(mode_button_width, 34.0))
                    .fill(soft_green()),
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
        let content_width = ui.available_width();
        egui::ScrollArea::vertical()
            .id_salt("latticra_main_workbench")
            .auto_shrink([false, false])
            .show(ui, |ui| {
                ui.set_width(content_width);
                if compact {
                    self.show_compact_workspace_tabs(ui);
                    ui.add_space(8.0);
                }
                self.show_hero_strip(ui);
                ui.add_space(10.0);
                if self.install_state == InstallState::Running {
                    self.show_install_run_monitor(ui, compact);
                    ui.add_space(10.0);
                }

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

    fn show_compact_workspace_tabs(&mut self, ui: &mut egui::Ui) {
        let card_width = ui.available_width();
        panel_card().show(ui, |ui| {
            ui.set_min_width((card_width - 24.0).max(0.0));
            ui.horizontal_wrapped(|ui| {
                self.compact_tab_button(ui, WorkspaceTab::Dashboard, "Dashboard");
                self.compact_tab_button(ui, WorkspaceTab::Components, "Components");
                self.compact_tab_button(ui, WorkspaceTab::Console, "Console");
                self.compact_tab_button(ui, WorkspaceTab::Seal, "Seal");
                self.compact_tab_button(ui, WorkspaceTab::Authority, "Authority");
                self.compact_tab_button(ui, WorkspaceTab::Delivery, "Delivery");
                self.compact_tab_button(ui, WorkspaceTab::Updater, "Updater");
                self.compact_tab_button(ui, WorkspaceTab::Evidence, "Evidence");
                self.compact_tab_button(ui, WorkspaceTab::Procedure, "Procedure");
            });
        });
    }

    fn compact_tab_button(&mut self, ui: &mut egui::Ui, tab: WorkspaceTab, label: &str) {
        let selected = self.active_tab == tab;
        let accent = workspace_tab_accent(tab);
        let fill = if selected {
            blend(soft_surface(), accent, 0.24)
        } else {
            soft_surface()
        };
        let stroke = if selected {
            egui::Stroke::new(1.0, accent)
        } else {
            egui::Stroke::new(1.0, border())
        };
        let response = ui.add(
            egui::Button::new(egui::RichText::new(label).small().strong().color(ink()))
                .selected(selected)
                .fill(fill)
                .stroke(stroke)
                .corner_radius(egui::CornerRadius::same(6))
                .min_size(egui::vec2(0.0, 30.0)),
        );
        if response.on_hover_text(workspace_tab_note(tab)).clicked() {
            self.active_tab = tab;
        }
    }

    fn show_hero_strip(&mut self, ui: &mut egui::Ui) {
        let card_width = ui.available_width();
        panel_card_with_stroke(teal()).show(ui, |ui| {
            ui.set_min_width((card_width - 24.0).max(0.0));
            let heading_size = if ui.available_width() < 760.0 {
                21.0
            } else {
                23.0
            };
            self.show_hero_copy(ui, heading_size);
            ui.add_space(8.0);
            self.show_hero_authority(ui);
            ui.add_space(8.0);
            self.show_hero_primary_actions(ui);
        });
    }

    fn show_hero_copy(&self, ui: &mut egui::Ui, heading_size: f32) {
        ui.label(
            egui::RichText::new("Guided local workbench")
                .small()
                .strong()
                .color(teal()),
        );
        ui.heading(
            egui::RichText::new("Plan first. Dry-run second. Install after evidence.")
                .size(heading_size)
                .color(ink()),
        );
        ui.add(
            egui::Label::new(
                "Latticra Panel prepares a user-local install, shows exactly what will happen, and keeps root, network, and runtime enforcement authority off in this lane.",
            )
            .wrap(),
        );
        ui.add(
            egui::Label::new(
                egui::RichText::new(self.config.profile.detail())
                    .small()
                    .color(muted()),
            )
            .wrap(),
        );
        ui.add_space(6.0);
        if ui.available_width() < 900.0 {
            ui.horizontal_wrapped(|ui| {
                status_chip(ui, "version", PANEL_VERSION);
                status_chip(ui, "mode", self.config.execution_mode_label());
                status_chip(ui, "next", self.next_action_label());
                if self.install_state == InstallState::Running {
                    status_chip(ui, "phase", &self.phase_title);
                }
            });
            ui.horizontal_wrapped(|ui| {
                status_chip(ui, "profile", self.config.profile.label());
                status_chip(ui, "seal", self.config.seal.crypto_profile.label());
            });
        } else {
            ui.horizontal_wrapped(|ui| {
                status_chip(ui, "version", PANEL_VERSION);
                status_chip(ui, "profile", self.config.profile.label());
                status_chip(ui, "mode", self.config.execution_mode_label());
                status_chip(ui, "seal", self.config.seal.crypto_profile.label());
                status_chip(ui, "next", self.next_action_label());
                if self.install_state == InstallState::Running {
                    status_chip(ui, "phase", &self.phase_title);
                }
            });
        }
    }

    fn show_hero_primary_actions(&mut self, ui: &mut egui::Ui) {
        let running = self.install_state == InstallState::Running;
        let install_blocker = self.install_blocker(running);
        let plan_blocker = self.panel_can_write_artifacts().err();
        let can_write_plan = plan_blocker.is_none();
        let can_execute = install_blocker.is_none();
        let run_label = if running {
            "Engine running"
        } else if self.config.safety.dry_run {
            "Run Dry-Install"
        } else {
            "Install guarded prefix"
        };

        ui.horizontal_wrapped(|ui| {
            let plan_response = ui
                .add_enabled(
                    can_write_plan,
                    egui::Button::new("Generate plan")
                        .fill(soft_blue())
                        .stroke(egui::Stroke::new(1.0, blue())),
                )
                .on_disabled_hover_text(plan_blocker.as_deref().unwrap_or("Plan ready"));
            if plan_response.clicked() {
                self.write_plan();
                self.active_tab = WorkspaceTab::Evidence;
                self.show_plan_over_log = true;
            }

            let run_response = ui
                .add_enabled(
                    can_execute,
                    egui::Button::new(run_label)
                        .fill(if self.config.safety.dry_run {
                            soft_blue()
                        } else {
                            soft_green()
                        })
                        .stroke(egui::Stroke::new(
                            1.0,
                            if self.config.safety.dry_run {
                                blue()
                            } else {
                                green()
                            },
                        )),
                )
                .on_disabled_hover_text(install_blocker.as_deref().unwrap_or("Run ready"));
            if run_response.clicked() {
                self.start_install();
            }

            if ui.button("Review evidence").clicked() {
                self.active_tab = WorkspaceTab::Evidence;
            }
            if ui.button("Open procedure").clicked() {
                self.active_tab = WorkspaceTab::Procedure;
            }
        });
    }

    fn show_hero_authority(&self, ui: &mut egui::Ui) {
        ui.horizontal_wrapped(|ui| {
            ui.label(
                egui::RichText::new("Authority floor")
                    .small()
                    .strong()
                    .color(amber()),
            );
            status_chip(ui, "prod", "0");
            status_chip(ui, "root", "0");
            status_chip(ui, "network", "0");
            status_chip(ui, "runtime", "0");
        });
    }

    fn show_dashboard(&mut self, ui: &mut egui::Ui) {
        ui.heading("Choose a starting lane");
        ui.add(
            egui::Label::new(
                "Pick the closest preset, then use the buttons above or the command deck below. The safe path is always plan, Dry-Install, evidence review, then guarded local writes.",
            )
            .wrap(),
        );
        ui.add_space(8.0);
        self.show_dashboard_summary(ui);
        ui.add_space(12.0);

        let profiles = InstallProfile::all();
        if ui.available_width() < PROFILE_CARD_TWO_COLUMN_WIDTH {
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
        if ui.available_width() < CARD_GRID_THREE_COLUMN_WIDTH {
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
            ui.heading(egui::RichText::new(profile.label()).size(18.0).color(ink()));
            ui.horizontal_wrapped(|ui| {
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
        ui.add_space(8.0);

        panel_card().show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(
                    egui::RichText::new("Component selection")
                        .size(18.0)
                        .color(ink()),
                );
                status_chip(
                    ui,
                    "selected",
                    &format!(
                        "{}/{}",
                        selected_component_count(&self.config.components),
                        8
                    ),
                );
                status_chip(ui, "profile", self.config.profile.label());
                status_chip(
                    ui,
                    "validation",
                    if self.config.components.fedora_validation {
                        "1"
                    } else {
                        "0"
                    },
                );
                status_chip(
                    ui,
                    "nadia",
                    if self.config.components.nadia_offline_ai {
                        "1"
                    } else {
                        "0"
                    },
                );
            });
            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                if ui.button("Guided preset").clicked() {
                    self.apply_profile(InstallProfile::DeveloperLocal);
                    self.active_tab = WorkspaceTab::Components;
                }
                if ui.button("Seal preset").clicked() {
                    self.apply_profile(InstallProfile::SealReportOnly);
                    self.active_tab = WorkspaceTab::Components;
                }
                if ui.button("Fedora VM preset").clicked() {
                    self.apply_profile(InstallProfile::FedoraValidationVm);
                    self.active_tab = WorkspaceTab::Components;
                }
                if ui.button("LC standalone preset").clicked() {
                    self.apply_profile(InstallProfile::LcStandalone);
                    self.active_tab = WorkspaceTab::Components;
                }
            });
        });
        ui.add_space(10.0);

        let mut components_changed = false;
        if ui.available_width() < CARD_GRID_TWO_COLUMN_WIDTH {
            components_changed |= component_card(
                ui,
                &mut self.config.components.latticra_console,
                "Latticra Console (LC)",
                "operator base",
                "Configurable Panel-installable operator base for substrate, host, and future OS-console workflows.",
                teal(),
            );
            components_changed |= component_card(
                ui,
                &mut self.config.components.lat_tooling,
                "Lat language tooling",
                "language",
                "Language and contract declaration tooling surface.",
                blue(),
            );
            components_changed |= component_card(
                ui,
                &mut self.config.components.lir_contracts,
                "LIR contracts",
                "contracts",
                "Intermediate representation contracts and validation materials.",
                blue(),
            );
            components_changed |= component_card(
                ui,
                &mut self.config.components.seal_report_only,
                "Latticra Seal report-only subsystem",
                "seal",
                "Tool-boundary and trust-boundary reporting without runtime enforcement claims.",
                green(),
            );
            components_changed |= component_card(
                ui,
                &mut self.config.components.nadia_offline_ai,
                "Nadia offline AI foundation",
                "optional",
                "Metadata-only offline AI foundation records contracts and Console surfaces. It does not run inference, load models, execute tools, or use network authority.",
                amber(),
            );
            components_changed |= component_card(
                ui,
                &mut self.config.components.fedora_validation,
                "Fedora validation files",
                "validation",
                "Fedora/Linux validation workspace, notes, and generated reports.",
                amber(),
            );
            components_changed |= component_card(
                ui,
                &mut self.config.components.docs_and_examples,
                "Documentation and examples",
                "docs",
                "User-facing project notes and local examples.",
                teal(),
            );
            components_changed |= component_card(
                ui,
                &mut self.config.components.developer_cli_helpers,
                "Developer CLI helpers",
                "helpers",
                "Convenience wrappers for local exploration.",
                teal(),
            );
        } else {
            ui.columns(2, |columns| {
                components_changed |= component_card(
                    &mut columns[0],
                    &mut self.config.components.latticra_console,
                    "Latticra Console (LC)",
                    "operator base",
                    "Configurable Panel-installable operator base for substrate, host, and future OS-console workflows.",
                    teal(),
                );
                components_changed |= component_card(
                    &mut columns[1],
                    &mut self.config.components.seal_report_only,
                    "Latticra Seal report-only subsystem",
                    "seal",
                    "Tool-boundary and trust-boundary reporting without runtime enforcement claims.",
                    green(),
                );
            });
            ui.columns(2, |columns| {
                components_changed |= component_card(
                    &mut columns[0],
                    &mut self.config.components.lat_tooling,
                    "Lat language tooling",
                    "language",
                    "Language and contract declaration tooling surface.",
                    blue(),
                );
                components_changed |= component_card(
                    &mut columns[1],
                    &mut self.config.components.lir_contracts,
                    "LIR contracts",
                    "contracts",
                    "Intermediate representation contracts and validation materials.",
                    blue(),
                );
            });
            ui.columns(2, |columns| {
                components_changed |= component_card(
                    &mut columns[0],
                    &mut self.config.components.docs_and_examples,
                    "Documentation and examples",
                    "docs",
                    "User-facing project notes and local examples.",
                    teal(),
                );
                components_changed |= component_card(
                    &mut columns[1],
                    &mut self.config.components.developer_cli_helpers,
                    "Developer CLI helpers",
                    "helpers",
                    "Convenience wrappers for local exploration.",
                    teal(),
                );
            });
            ui.columns(2, |columns| {
                components_changed |= component_card(
                    &mut columns[0],
                    &mut self.config.components.nadia_offline_ai,
                    "Nadia offline AI foundation",
                    "optional",
                    "Metadata-only offline AI foundation records contracts and Console surfaces. It does not run inference, load models, execute tools, or use network authority.",
                    amber(),
                );
                components_changed |= component_card(
                    &mut columns[1],
                    &mut self.config.components.fedora_validation,
                    "Fedora validation files",
                    "validation",
                    "Fedora/Linux validation workspace, notes, and generated reports.",
                    amber(),
                );
            });
        }

        if components_changed {
            self.config.profile = InstallProfile::Custom;
            self.refresh_plan();
            self.status = "Component selection marked as Custom.".to_owned();
            self.push_console("components -> custom");
        }
    }

    fn show_console_config(&mut self, ui: &mut egui::Ui) {
        ui.heading("Latticra Console profile");
        ui.label("Choose how LC metadata and wrappers are installed. Current LC surfaces stay panel-aware, local-prefix scoped, and no-effect.");
        ui.add_space(8.0);

        panel_card().show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("LC posture").size(18.0).color(ink()));
                status_chip(ui, "profile", self.config.lc.profile.label());
                status_chip(
                    ui,
                    "installed",
                    if self.config.components.latticra_console {
                        "1"
                    } else {
                        "0"
                    },
                );
                status_chip(
                    ui,
                    "contracts",
                    &format!("{}/{}", selected_lc_contract_count(&self.config.lc), 26),
                );
                status_chip(
                    ui,
                    "report_only",
                    if self.config.lc.report_only { "1" } else { "0" },
                );
                status_chip(ui, "external_host", "0");
            });
            ui.add(
                egui::Label::new(
                    egui::RichText::new(self.config.lc.profile.detail())
                        .small()
                        .color(muted()),
                )
                .wrap(),
            );
            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                if ui.button("Open LC plan").clicked() {
                    self.refresh_plan();
                    self.active_tab = WorkspaceTab::Evidence;
                    self.show_plan_over_log = true;
                }
                if ui.button("Review components").clicked() {
                    self.active_tab = WorkspaceTab::Components;
                }
                if ui.button("Review Authority").clicked() {
                    self.active_tab = WorkspaceTab::Authority;
                }
            });
        });

        ui.add_space(10.0);
        let lc_profiles = LatticraConsoleProfile::all();
        if ui.available_width() < CARD_GRID_TWO_COLUMN_WIDTH {
            for profile in lc_profiles {
                lc_profile_button(ui, self, profile, lc_profile_note(profile));
            }
        } else {
            for row in lc_profiles.chunks(2) {
                ui.columns(2, |columns| {
                    for (column, profile) in row.iter().copied().enumerate() {
                        lc_profile_button(
                            &mut columns[column],
                            self,
                            profile,
                            lc_profile_note(profile),
                        );
                    }
                });
            }
        }

        ui.add_space(8.0);
        panel_card_with_stroke(teal()).show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(
                    egui::RichText::new("LC install configuration")
                        .size(18.0)
                        .color(ink()),
                );
                colored_status_chip(ui, "external_host", "disabled", amber());
                status_chip(ui, "wrapper", &self.config.lc.install.command_wrapper);
            });
            ui.add_space(4.0);
            let _ = behavior_toggle_row(
                ui,
                &mut self.config.components.latticra_console,
                "Install Latticra Console",
                "LC is installed as a standalone and Panel-embedded operator console metadata surface.",
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
            let _ = behavior_toggle_row(
                ui,
                &mut self.config.lc.install.standalone_console,
                "Standalone console",
                "Install LC as a direct user-local console wrapper that does not require Panel at runtime.",
            );
            let _ = behavior_toggle_row(
                ui,
                &mut self.config.lc.install.panel_embedded_console,
                "Panel embedded console",
                "LC remains available inside Latticra Panel.",
            );
            let _ = behavior_toggle_row(
                ui,
                &mut self.config.lc.install.write_config_file,
                "Write LC config file",
                "Install LC configuration metadata into the local prefix.",
            );
            let _ = behavior_toggle_row(
                ui,
                &mut self.config.lc.install.write_profile_presets,
                "Write profile presets",
                "Install hosted, standalone, Panel, host-planning, and OS-planning profile metadata.",
            );
            let _ = behavior_toggle_row(
                ui,
                &mut self.config.lc.install.write_command_registry,
                "Write command registry",
                "Install the LC command registry used by help, boundary, and commands.",
            );
            let _ = behavior_toggle_row(
                ui,
                &mut self.config.lc.install.write_contract_files,
                "Write contract files",
                "Install LC metadata contracts without granting execution authority.",
            );
            let _ = behavior_toggle_row(
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
        });

        ui.add_space(8.0);
        egui::CollapsingHeader::new("Advanced LC substrate and contract profiles")
            .default_open(false)
            .show(ui, |ui| {
                panel_card().show(ui, |ui| {
                    ui.horizontal_wrapped(|ui| {
                        ui.heading(
                            egui::RichText::new("Profile fields")
                                .size(18.0)
                                .color(ink()),
                        );
                        status_chip(ui, "bridge", &self.config.lc.panel_bridge);
                        status_chip(ui, "host", &self.config.lc.host_embedding_profile);
                    });
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
                        "Session contract",
                        &mut self.config.lc.session_contract_profile,
                    );
                    labeled_text_field(
                        ui,
                        "Workspace contract",
                        &mut self.config.lc.workspace_contract_profile,
                    );
                    labeled_text_field(
                        ui,
                        "Namespace contract",
                        &mut self.config.lc.namespace_contract_profile,
                    );
                    labeled_text_field(
                        ui,
                        "Rootfs contract",
                        &mut self.config.lc.rootfs_contract_profile,
                    );
                    labeled_text_field(
                        ui,
                        "Packages contract",
                        &mut self.config.lc.packages_contract_profile,
                    );
                    labeled_text_field(
                        ui,
                        "Init contract",
                        &mut self.config.lc.init_contract_profile,
                    );
                    labeled_text_field(
                        ui,
                        "Services contract",
                        &mut self.config.lc.services_contract_profile,
                    );
                    labeled_text_field(
                        ui,
                        "Service schema",
                        &mut self.config.lc.service_schema_contract_profile,
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
                        "Review draft",
                        &mut self
                            .config
                            .lc
                            .receipt_payload_artifact_review_receipt_draft_profile,
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
                });
            });

        ui.add_space(8.0);
        egui::CollapsingHeader::new("Advanced LC authority and receipt gates")
            .default_open(false)
            .show(ui, |ui| {
                panel_card().show(ui, |ui| {
                    ui.horizontal_wrapped(|ui| {
                        ui.heading(
                            egui::RichText::new("Contract gates").size(18.0).color(ink()),
                        );
                        status_chip(
                            ui,
                            "enabled",
                            &format!("{}/{}", selected_lc_contract_count(&self.config.lc), 26),
                        );
                        status_chip(ui, "runtime", "0");
                    });
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.report_only,
                        "LC remains report-only",
                        "Current LC profiles emit configuration and evidence only.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_host_embedding_contract,
                        "Require host-embedding contract",
                        "LC host embedding cannot advance until this contract is present and reviewed.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_read_only_host_inventory_contract,
                        "Require read-only host inventory contract",
                        "Future host adapters must prove inventory evidence without broad host authority.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_profile_receipt,
                        "Require profile receipt",
                        "LC profile selection must become receipt evidence before future promotion.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_host_contract_receipt,
                        "Require host-contract receipt",
                        "The host-embedding contract must be receipted before any host adapter path.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_host_inventory_receipt,
                        "Require host-inventory receipt",
                        "Read-only inventory contract metadata must be receipted before host embedding work.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_host_adapter_contract,
                        "Require host-adapter contract",
                        "Future Host embedding must prove the adapter contract before any adapter can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_session_contract,
                        "Require session contract",
                        "LC sessions must prove this metadata envelope before any runtime session, shell, or host adapter can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_workspace_contract,
                        "Require workspace contract",
                        "LC workspaces must prove this metadata envelope before any workspace mount, manifest write, or OS-base workspace can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_namespace_contract,
                        "Require namespace contract",
                        "LC namespaces must prove this metadata envelope before any rootfs, mount, or host path projection can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_rootfs_contract,
                        "Require rootfs contract",
                        "LC rootfs planning must prove this metadata envelope before any image, mount, package write, or boot-adjacent work can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_packages_contract,
                        "Require packages contract",
                        "LC package planning must prove this metadata envelope before any catalog read, download, package manager execution, or rootfs package write can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_init_contract,
                        "Require init contract",
                        "LC init planning must prove this metadata envelope before any PID 1 claim, service start, or process supervision can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_services_contract,
                        "Require services contract",
                        "LC service planning must prove this metadata envelope before any service registry write, enable, start, reload, or supervision can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_service_schema_contract,
                        "Require service schema",
                        "LC service definitions must prove this schema contract before validation, dependency resolution, or service control can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_receipt_request_contract,
                        "Require receipt-request contract",
                        "Future LC receipt signing must prove the request contract before any signature can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_receipt_payload_schema,
                        "Require receipt payload schema",
                        "Future LC receipt signing must prove the payload shape before any signature request can bind.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_receipt_payload_artifact_draft,
                        "Require receipt artifact draft",
                        "Future LC receipt signing must prove the no-write payload artifact draft before materialization.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_receipt_payload_artifact_review,
                        "Require artifact review gate",
                        "Future LC receipt payload materialization must prove the draft review gate before any payload artifact can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self
                            .config
                            .lc
                            .require_receipt_payload_artifact_review_receipt,
                        "Require review receipt",
                        "Future LC receipt payload materialization must prove review receipt evidence before any payload artifact can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self
                            .config
                            .lc
                            .require_receipt_payload_artifact_review_receipt_draft,
                        "Require review draft",
                        "Future LC receipt payload materialization must prove review receipt draft metadata before any payload artifact can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self
                            .config
                            .lc
                            .require_receipt_payload_materialization_plan,
                        "Require materialization plan",
                        "Future LC receipt payload writes must prove the materialization plan before any payload artifact can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_signature_request_binding,
                        "Require signature-request binding",
                        "Future LC receipt signing must prove the binding contract before any Seal signature request artifact can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_os_base_contract,
                        "Require OS-base contract",
                        "Future OS-base work must prove this contract before any boot-adjacent planning advances.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_vm_evidence_contract,
                        "Require VM evidence contract",
                        "Future OS-base work must prove VM evidence metadata before any boot-adjacent implementation.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_runtime_boundary_binding,
                        "Require Runtime Boundary binding",
                        "LC command surfaces must remain classified before future execution authority can exist.",
                    );
                    let _ = behavior_toggle_row(
                        ui,
                        &mut self.config.lc.require_seal_capability_labels,
                        "Require Seal capability labels",
                        "LC commands keep explicit Seal labels while granting no cryptographic or runtime authority.",
                    );
                });
            });
    }

    fn show_seal_config(&mut self, ui: &mut egui::Ui) {
        ui.heading("Latticra Seal cryptographic profile");
        ui.label("Choose the Seal reporting and future-crypto posture. This panel records metadata and reports; it does not generate keys, sign payloads, or encrypt files.");
        ui.add_space(8.0);

        panel_card().show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("Seal posture").size(18.0).color(ink()));
                status_chip(ui, "profile", self.config.seal.crypto_profile.label());
                status_chip(
                    ui,
                    "capabilities",
                    &format!(
                        "{}/{}",
                        selected_seal_capability_count(&self.config.seal),
                        3,
                    ),
                );
                status_chip(ui, "hash", &self.config.seal.hash_profile);
                status_chip(
                    ui,
                    "report_only",
                    if self.config.seal.report_only {
                        "1"
                    } else {
                        "0"
                    },
                );
                status_chip(
                    ui,
                    "signed_manifest",
                    if self.config.seal.require_signed_manifest {
                        "1"
                    } else {
                        "0"
                    },
                );
            });
            ui.add(
                egui::Label::new(
                    egui::RichText::new(self.config.seal.crypto_profile.detail())
                        .small()
                        .color(muted()),
                )
                .wrap(),
            );
            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                if ui.button("Open Seal evidence").clicked() {
                    self.refresh_plan();
                    self.active_tab = WorkspaceTab::Evidence;
                    self.show_plan_over_log = true;
                }
                if ui.button("Reapply profile defaults").clicked() {
                    self.config.seal.apply_crypto_profile_defaults();
                    self.refresh_plan();
                    self.status = "Reapplied Seal profile defaults.".to_owned();
                    self.push_console("seal.profile_defaults -> reapplied");
                }
            });
        });

        ui.add_space(10.0);
        let seal_profiles = SealCryptoProfile::all();
        if ui.available_width() < CARD_GRID_TWO_COLUMN_WIDTH {
            for profile in seal_profiles {
                seal_profile_button(ui, self, profile, seal_profile_note(profile));
            }
        } else {
            for row in seal_profiles.chunks(2) {
                ui.columns(2, |columns| {
                    for (column, profile) in row.iter().copied().enumerate() {
                        seal_profile_button(
                            &mut columns[column],
                            self,
                            profile,
                            seal_profile_note(profile),
                        );
                    }
                });
            }
        }

        ui.add_space(8.0);
        let mut seal_changed = false;
        panel_card_with_stroke(if self.config.seal.report_only {
            teal()
        } else {
            amber()
        })
        .show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("Seal parameters").size(18.0).color(ink()));
                colored_status_chip(
                    ui,
                    "keys",
                    if self.config.seal.report_only {
                        "no-authority"
                    } else {
                        "review"
                    },
                    if self.config.seal.report_only {
                        teal()
                    } else {
                        amber()
                    },
                );
            });
            ui.add_space(4.0);
            if ui.available_width() < 740.0 {
                seal_changed |= seal_text_field(ui, "Hash", &mut self.config.seal.hash_profile);
                seal_changed |=
                    seal_text_field(ui, "Signature", &mut self.config.seal.signature_profile);
                seal_changed |=
                    seal_text_field(ui, "Encryption", &mut self.config.seal.encryption_profile);
                seal_changed |=
                    seal_text_field(ui, "Envelope", &mut self.config.seal.envelope_profile);
                seal_changed |= seal_text_field(
                    ui,
                    "Key storage",
                    &mut self.config.seal.key_storage_profile,
                );
            } else {
                ui.columns(2, |columns| {
                    seal_changed |= seal_text_field(
                        &mut columns[0],
                        "Hash",
                        &mut self.config.seal.hash_profile,
                    );
                    seal_changed |= seal_text_field(
                        &mut columns[1],
                        "Signature",
                        &mut self.config.seal.signature_profile,
                    );
                });
                ui.columns(2, |columns| {
                    seal_changed |= seal_text_field(
                        &mut columns[0],
                        "Encryption",
                        &mut self.config.seal.encryption_profile,
                    );
                    seal_changed |= seal_text_field(
                        &mut columns[1],
                        "Envelope",
                        &mut self.config.seal.envelope_profile,
                    );
                });
                seal_changed |= seal_text_field(
                    ui,
                    "Key storage",
                    &mut self.config.seal.key_storage_profile,
                );
            }

            ui.separator();
            seal_changed |= seal_toggle_row(
                ui,
                &mut self.config.seal.report_only,
                "Seal remains report-only",
                "No signing, encryption, key generation, or key storage occurs from this panel lane.",
            );
            seal_changed |= seal_toggle_row(
                ui,
                &mut self.config.seal.require_signed_manifest,
                "Require signed manifest metadata",
                "Requires signed-manifest metadata in plans/receipts when using advanced profiles.",
            );
            seal_changed |= seal_toggle_row(
                ui,
                &mut self.config.seal.write_seal_report,
                "Write Seal report",
                "Include Latticra Seal report metadata in generated local evidence.",
            );
        });

        if seal_changed {
            if self.config.seal.crypto_profile != SealCryptoProfile::Custom {
                self.push_console("seal.crypto_profile -> Custom");
            }
            self.config.seal.crypto_profile = SealCryptoProfile::Custom;
            self.refresh_plan();
            self.status = "Seal parameters marked as Custom.".to_owned();
        }
    }

    fn show_authority(&mut self, ui: &mut egui::Ui) {
        ui.heading("Safety and evidence gates");
        ui.label("Latticra Panel makes authority visible before anything effectful can happen.");
        ui.add_space(8.0);

        panel_card().show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(
                    egui::RichText::new("Authority matrix")
                        .size(18.0)
                        .color(ink()),
                );
                status_chip(
                    ui,
                    "evidence_gates",
                    &format!("{}/{}", selected_safety_gate_count(&self.config.safety), 4),
                );
                status_chip(ui, "mode", self.config.execution_mode_label());
                status_chip(
                    ui,
                    "local_ack",
                    if self.guarded_local_ack { "1" } else { "0" },
                );
                status_chip(ui, "root", "0");
                status_chip(ui, "network", "0");
                status_chip(ui, "runtime", "0");
            });
            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                if ui.button("Open procedure").clicked() {
                    self.active_tab = WorkspaceTab::Procedure;
                }
                if ui.button("Open evidence").clicked() {
                    self.active_tab = WorkspaceTab::Evidence;
                }
                if ui.button("Open delivery").clicked() {
                    self.active_tab = WorkspaceTab::Delivery;
                }
            });
        });

        ui.add_space(10.0);
        self.show_mode_gate(ui);
        self.config.safety.allow_network_effect = false;

        ui.add_space(10.0);
        let mut authority_changed = false;
        if ui.available_width() < CARD_GRID_THREE_COLUMN_WIDTH {
            authority_locked_card(
                ui,
                "Network authority",
                "future disabled",
                "Network fetch and outbound effects remain outside this Panel lane.",
                amber(),
            );
            authority_changed |= safety_gate_card(
                ui,
                &mut self.config.safety.require_component_manifest,
                "Require component manifest",
                "inventory",
                "Refuse to proceed when component inventory evidence is missing.",
                teal(),
            );
            authority_changed |= safety_gate_card(
                ui,
                &mut self.config.safety.require_artifact_measurements,
                "Require artifact measurements",
                "measurement",
                "Keep generated measurement evidence in the receipt chain.",
                blue(),
            );
            authority_changed |= safety_gate_card(
                ui,
                &mut self.config.safety.require_verification_policy_metadata,
                "Require verification policy metadata",
                "policy",
                "Preserve policy/evidence metadata expectations.",
                green(),
            );
            authority_changed |= safety_gate_card(
                ui,
                &mut self.config.safety.write_operator_receipt,
                "Write operator-visible receipt",
                "receipt",
                "Create a visible receipt for the configured run.",
                teal(),
            );
        } else {
            ui.columns(3, |columns| {
                authority_locked_card(
                    &mut columns[0],
                    "Network authority",
                    "future disabled",
                    "Network fetch and outbound effects remain outside this Panel lane.",
                    amber(),
                );
                authority_changed |= safety_gate_card(
                    &mut columns[1],
                    &mut self.config.safety.require_component_manifest,
                    "Require component manifest",
                    "inventory",
                    "Refuse to proceed when component inventory evidence is missing.",
                    teal(),
                );
                authority_changed |= safety_gate_card(
                    &mut columns[2],
                    &mut self.config.safety.require_artifact_measurements,
                    "Require artifact measurements",
                    "measurement",
                    "Keep generated measurement evidence in the receipt chain.",
                    blue(),
                );
            });
            ui.columns(2, |columns| {
                authority_changed |= safety_gate_card(
                    &mut columns[0],
                    &mut self.config.safety.require_verification_policy_metadata,
                    "Require verification policy metadata",
                    "policy",
                    "Preserve policy/evidence metadata expectations.",
                    green(),
                );
                authority_changed |= safety_gate_card(
                    &mut columns[1],
                    &mut self.config.safety.write_operator_receipt,
                    "Write operator-visible receipt",
                    "receipt",
                    "Create a visible receipt for the configured run.",
                    teal(),
                );
            });
        }

        if authority_changed {
            if self.config.profile != InstallProfile::Custom {
                self.push_console("authority -> custom");
            }
            self.config.profile = InstallProfile::Custom;
            self.refresh_plan();
            self.status = "Authority gates marked as Custom.".to_owned();
        }
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
        ui.label("Control the local prefix, wrappers, desktop entry, and build outputs before any write is allowed.");
        ui.add_space(8.0);

        let mut delivery_changed = false;
        panel_card().show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(
                    egui::RichText::new("Delivery footprint")
                        .size(18.0)
                        .color(ink()),
                );
                status_chip(ui, "prefix", prefix_lane_label(&self.config.install_prefix));
                status_chip(
                    ui,
                    "options",
                    &format!("{}/{}", selected_behavior_count(&self.config.behavior), 9),
                );
                status_chip(ui, "mode", self.config.execution_mode_label());
                status_chip(
                    ui,
                    "preserve",
                    if self.config.behavior.preserve_existing_files {
                        "1"
                    } else {
                        "0"
                    },
                );
            });
            ui.add_space(6.0);
            if ui.available_width() < 620.0 {
                ui.label(egui::RichText::new("Install prefix").strong().color(ink()));
                delivery_changed |= ui
                    .add(
                        egui::TextEdit::singleline(&mut self.config.install_prefix)
                            .desired_width(ui.available_width())
                            .margin(egui::Margin::symmetric(8, 6)),
                    )
                    .changed();
                if ui.button("Reset default prefix").clicked() {
                    self.reset_install_prefix();
                    delivery_changed = true;
                }
            } else {
                ui.horizontal(|ui| {
                    ui.set_min_width(120.0);
                    ui.label(egui::RichText::new("Install prefix").strong().color(ink()));
                    delivery_changed |= ui
                        .add(
                            egui::TextEdit::singleline(&mut self.config.install_prefix)
                                .desired_width((ui.available_width() - 164.0).max(180.0))
                                .margin(egui::Margin::symmetric(8, 6)),
                        )
                        .changed();
                    if ui.button("Reset default prefix").clicked() {
                        self.reset_install_prefix();
                        delivery_changed = true;
                    }
                });
            }
            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                if ui.button("Open components").clicked() {
                    self.active_tab = WorkspaceTab::Components;
                }
                if ui.button("Open plan").clicked() {
                    self.refresh_plan();
                    self.active_tab = WorkspaceTab::Evidence;
                    self.show_plan_over_log = true;
                }
                if ui.button("Review gates").clicked() {
                    self.active_tab = WorkspaceTab::Authority;
                }
            });
        });

        if let Err(err) = self.panel_can_execute() {
            ui.add_space(8.0);
            warning_note(ui, "Delivery gate", &err);
        }

        ui.add_space(10.0);
        if ui.available_width() < CARD_GRID_THREE_COLUMN_WIDTH {
            delivery_changed |= delivery_layout_card(ui, &mut self.config.behavior);
            delivery_changed |= delivery_payload_card(ui, &mut self.config.behavior);
            delivery_changed |= delivery_build_card(ui, &mut self.config.behavior);
        } else {
            ui.columns(3, |columns| {
                delivery_changed |=
                    delivery_layout_card(&mut columns[0], &mut self.config.behavior);
                delivery_changed |=
                    delivery_payload_card(&mut columns[1], &mut self.config.behavior);
                delivery_changed |= delivery_build_card(&mut columns[2], &mut self.config.behavior);
            });
        }

        if delivery_changed {
            if self.config.profile != InstallProfile::Custom {
                self.push_console("delivery -> custom");
            }
            self.config.profile = InstallProfile::Custom;
            self.refresh_plan();
            self.status = "Delivery settings marked as Custom.".to_owned();
        }
    }

    fn show_updater(&mut self, ui: &mut egui::Ui) {
        ui.heading("Panel updater");
        ui.label("Preview updates from the reviewed local checkout, then apply only after a successful dry-run and guarded-write acknowledgement.");
        ui.add_space(8.0);

        let apply_blocker =
            if self.config.updater.require_dry_run_before_apply && !self.last_update_dry_run_ok {
                Some("Updater apply is locked until Preview update completes successfully.")
            } else if !self.guarded_local_ack {
                Some(self.guarded_local_ack_message())
            } else {
                None
            };
        let mut updater_changed = false;

        panel_card().show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("Update lane").size(18.0).color(ink()));
                status_chip(ui, "source", &self.config.updater.source_strategy);
                status_chip(ui, "channel", &self.config.updater.update_channel);
                status_chip(
                    ui,
                    "policies",
                    &format!(
                        "{}/{}",
                        selected_updater_policy_count(&self.config.updater),
                        3
                    ),
                );
                status_chip(
                    ui,
                    "preview",
                    if self.last_update_dry_run_ok {
                        "complete"
                    } else {
                        "needed"
                    },
                );
                status_chip(
                    ui,
                    "apply",
                    if apply_blocker.is_some() {
                        "locked"
                    } else {
                        "ready"
                    },
                );
                status_chip(ui, "network", "0");
                status_chip(ui, "root", "0");
            });
            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                if ui.button("Preview update").clicked() {
                    self.start_update_dry_run();
                }
                if ui.button("Open update plan").clicked() {
                    self.refresh_plan();
                    self.show_plan_over_log = true;
                    self.active_tab = WorkspaceTab::Evidence;
                }
                if ui.button("Review Authority").clicked() {
                    self.active_tab = WorkspaceTab::Authority;
                }
            });
        });

        ui.add_space(10.0);
        panel_card_with_stroke(blue()).show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("Source posture").size(18.0).color(ink()));
                colored_status_chip(ui, "fetch", "disabled", amber());
                status_chip(ui, "checkout", "reviewed-local");
            });
            ui.add(
                egui::Label::new(
                    egui::RichText::new(
                        "Updater apply reuses the local installer engine against the reviewed checkout. Pull/fetch authority stays out of this Panel lane.",
                    )
                    .small()
                    .color(muted()),
                )
                .wrap(),
            );
            ui.add_space(6.0);
            if ui.available_width() < 620.0 {
                updater_changed |= updater_text_field(
                    ui,
                    "Source strategy",
                    &mut self.config.updater.source_strategy,
                );
                updater_changed |= updater_text_field(
                    ui,
                    "Channel",
                    &mut self.config.updater.update_channel,
                );
            } else {
                ui.columns(2, |columns| {
                    updater_changed |= updater_text_field(
                        &mut columns[0],
                        "Source strategy",
                        &mut self.config.updater.source_strategy,
                    );
                    updater_changed |= updater_text_field(
                        &mut columns[1],
                        "Channel",
                        &mut self.config.updater.update_channel,
                    );
                });
            }
        });

        self.config.updater.allow_network_fetch = false;
        ui.add_space(10.0);
        if ui.available_width() < CARD_GRID_TWO_COLUMN_WIDTH {
            authority_locked_card(
                ui,
                "Network fetch (future; disabled)",
                "fetch=0",
                "Updater fetch/pull authority remains outside this Panel lane.",
                amber(),
            );
            updater_changed |= updater_policy_card(
                ui,
                &mut self.config.updater.require_dry_run_before_apply,
                "Require updater dry-run before apply",
                "preview",
                "A successful updater dry-run in this Panel session is required before guarded apply.",
                teal(),
            );
            updater_changed |= updater_policy_card(
                ui,
                &mut self.config.updater.reuse_installer_engine,
                "Reuse guarded installer engine",
                "engine",
                "Update apply is a guarded local-prefix reinstall over Latticra-managed files.",
                blue(),
            );
            updater_changed |= updater_policy_card(
                ui,
                &mut self.config.updater.write_update_receipt,
                "Write updater receipt metadata",
                "receipt",
                "Generated plans and receipts include the updater policy fields.",
                green(),
            );
        } else if ui.available_width() >= CARD_GRID_FOUR_COLUMN_WIDTH {
            ui.columns(4, |columns| {
                authority_locked_card(
                    &mut columns[0],
                    "Network fetch (future; disabled)",
                    "fetch=0",
                    "Updater fetch/pull authority remains outside this Panel lane.",
                    amber(),
                );
                updater_changed |= updater_policy_card(
                    &mut columns[1],
                    &mut self.config.updater.require_dry_run_before_apply,
                    "Require updater dry-run before apply",
                    "preview",
                    "A successful updater dry-run in this Panel session is required before guarded apply.",
                    teal(),
                );
                updater_changed |= updater_policy_card(
                    &mut columns[2],
                    &mut self.config.updater.reuse_installer_engine,
                    "Reuse guarded installer engine",
                    "engine",
                    "Update apply is a guarded local-prefix reinstall over Latticra-managed files.",
                    blue(),
                );
                updater_changed |= updater_policy_card(
                    &mut columns[3],
                    &mut self.config.updater.write_update_receipt,
                    "Write updater receipt metadata",
                    "receipt",
                    "Generated plans and receipts include the updater policy fields.",
                    green(),
                );
            });
        } else {
            ui.columns(2, |columns| {
                authority_locked_card(
                    &mut columns[0],
                    "Network fetch (future; disabled)",
                    "fetch=0",
                    "Updater fetch/pull authority remains outside this Panel lane.",
                    amber(),
                );
                updater_changed |= updater_policy_card(
                    &mut columns[1],
                    &mut self.config.updater.require_dry_run_before_apply,
                    "Require updater dry-run before apply",
                    "preview",
                    "A successful updater dry-run in this Panel session is required before guarded apply.",
                    teal(),
                );
            });
            ui.columns(2, |columns| {
                updater_changed |= updater_policy_card(
                    &mut columns[0],
                    &mut self.config.updater.reuse_installer_engine,
                    "Reuse guarded installer engine",
                    "engine",
                    "Update apply is a guarded local-prefix reinstall over Latticra-managed files.",
                    blue(),
                );
                updater_changed |= updater_policy_card(
                    &mut columns[1],
                    &mut self.config.updater.write_update_receipt,
                    "Write updater receipt metadata",
                    "receipt",
                    "Generated plans and receipts include the updater policy fields.",
                    green(),
                );
            });
        }

        ui.add_space(10.0);
        panel_card_with_stroke(if apply_blocker.is_some() {
            amber()
        } else {
            green()
        })
        .show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(
                    egui::RichText::new("Guarded updater actions")
                        .size(18.0)
                        .color(ink()),
                );
                status_chip(
                    ui,
                    "dry_run_ok",
                    if self.last_update_dry_run_ok {
                        "1"
                    } else {
                        "0"
                    },
                );
                status_chip(
                    ui,
                    "local_ack",
                    if self.guarded_local_ack { "1" } else { "0" },
                );
            });
            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                if ui.button("Preview update").clicked() {
                    self.start_update_dry_run();
                }
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
        });

        if updater_changed {
            if self.config.profile != InstallProfile::Custom {
                self.push_console("updater -> custom");
            }
            self.config.profile = InstallProfile::Custom;
            self.refresh_plan();
            self.status = "Updater settings marked as Custom.".to_owned();
        }

        let apply_blocker =
            if self.config.updater.require_dry_run_before_apply && !self.last_update_dry_run_ok {
                Some("Preview update must complete successfully in this Panel session.")
            } else if !self.guarded_local_ack {
                Some(self.guarded_local_ack_message())
            } else {
                None
            };
        if let Some(reason) = apply_blocker {
            warning_note(ui, "Updater apply locked", reason);
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

        let tiles = [
            (
                "Panel version",
                PANEL_VERSION,
                "current GUI foundation",
                teal(),
            ),
            (
                "Authority",
                mode_value,
                "root=0 network=0 runtime=0",
                blue(),
            ),
            (
                "Evidence",
                evidence_value,
                "plan and engine log stay visible",
                amber(),
            ),
            ("Updater", updater_value, "dry-run gates apply", green()),
        ];

        let available_width = ui.available_width();
        if available_width >= DASHBOARD_SUMMARY_FOUR_COLUMN_WIDTH {
            ui.columns(4, |columns| {
                for (column, (label, value, note, accent)) in tiles.iter().enumerate() {
                    summary_tile(&mut columns[column], label, value, note, *accent);
                }
            });
        } else if available_width >= DASHBOARD_SUMMARY_TWO_COLUMN_WIDTH {
            for row in tiles.chunks(2) {
                ui.columns(row.len(), |columns| {
                    for (column, (label, value, note, accent)) in row.iter().enumerate() {
                        summary_tile(&mut columns[column], label, value, note, *accent);
                    }
                });
                ui.add_space(6.0);
            }
        } else {
            for (label, value, note, accent) in tiles {
                summary_tile(ui, label, value, note, accent);
                ui.add_space(6.0);
            }
        }
    }

    fn show_evidence(&mut self, ui: &mut egui::Ui) {
        ui.heading("Plan, receipts, and evidence");
        ui.horizontal_wrapped(|ui| {
            status_chip(
                ui,
                "view",
                if self.show_plan_over_log {
                    "plan"
                } else {
                    "log"
                },
            );
            status_chip(ui, "plan_lines", &line_count(&self.plan).to_string());
            status_chip(ui, "log_lines", &self.logs.len().to_string());
            status_chip(ui, "phase", &self.phase_title);
        });
        ui.add_space(6.0);
        ui.horizontal_wrapped(|ui| {
            let plan_button = egui::Button::new("Plan preview")
                .selected(self.show_plan_over_log)
                .fill(if self.show_plan_over_log {
                    soft_blue()
                } else {
                    soft_surface()
                });
            if ui.add(plan_button).clicked() {
                self.show_plan_over_log = true;
            }

            let log_button = egui::Button::new("Engine log")
                .selected(!self.show_plan_over_log)
                .fill(if !self.show_plan_over_log {
                    soft_blue()
                } else {
                    soft_surface()
                });
            if ui.add(log_button).clicked() {
                self.show_plan_over_log = false;
            }

            if ui.button("Refresh plan").clicked() {
                self.refresh_plan();
            }
        });
        ui.add_space(8.0);

        let max_height = ui.available_height().max(320.0);
        if self.show_plan_over_log {
            show_record_text(
                ui,
                "latticra_evidence_plan_record",
                &self.plan,
                "plan=empty",
                max_height,
                false,
            );
        } else {
            show_record_lines(
                ui,
                "latticra_evidence_log_record",
                &self.logs,
                "engine_log=waiting",
                max_height,
                true,
            );
        }
    }

    fn show_install_run_monitor(&mut self, ui: &mut egui::Ui, compact: bool) {
        panel_card_with_stroke(blue()).show(ui, |ui| {
            if !compact && ui.available_width() >= RUNNING_MONITOR_WIDE_WIDTH {
                ui.columns(2, |columns| {
                    columns[0].vertical(|ui| {
                        self.show_install_run_summary(ui);
                        ui.add_space(6.0);
                        self.show_bounded_install_progress(ui, RUNNING_PROGRESS_MAX_WIDTH);
                        ui.add_space(6.0);
                        self.show_install_run_monitor_actions(ui);
                    });
                    columns[1].vertical(|ui| {
                        self.show_recent_engine_output(ui, 8, RUNNING_RECENT_LOG_MAX_HEIGHT);
                    });
                });
                return;
            }

            ui.vertical(|ui| {
                self.show_install_run_summary(ui);
                ui.add_space(6.0);
                let max_width = if compact {
                    ui.available_width()
                } else {
                    RUNNING_PROGRESS_MAX_WIDTH
                };
                self.show_bounded_install_progress(ui, max_width);
                ui.add_space(6.0);
                self.show_recent_engine_output(ui, 5, RUNNING_RECENT_LOG_MAX_HEIGHT);
                ui.add_space(6.0);
                self.show_install_run_monitor_actions(ui);
            });
        });
    }

    fn show_bounded_install_progress(&self, ui: &mut egui::Ui, max_width: f32) {
        let width = ui.available_width().min(max_width).max(180.0);
        ui.add_sized(
            [width, 16.0],
            egui::ProgressBar::new(self.progress()).show_percentage(),
        );
    }

    fn show_install_run_summary(&self, ui: &mut egui::Ui) {
        ui.horizontal_wrapped(|ui| {
            ui.label(
                egui::RichText::new(format!("Running {}", self.operation_label()))
                    .strong()
                    .color(ink()),
            );
            status_chip(ui, "phase", &self.phase_title);
            status_chip(ui, "root", "0");
            status_chip(ui, "network", "0");
        });
        ui.add(egui::Label::new(&self.status).wrap());
    }

    fn show_install_run_monitor_actions(&mut self, ui: &mut egui::Ui) {
        ui.horizontal_wrapped(|ui| {
            if ui.button("Engine log").clicked() {
                self.active_tab = WorkspaceTab::Evidence;
                self.show_plan_over_log = false;
            }
            if ui.button("Plan").clicked() {
                self.active_tab = WorkspaceTab::Evidence;
                self.show_plan_over_log = true;
            }
        });
    }

    fn show_recent_engine_output(&self, ui: &mut egui::Ui, max_lines: usize, max_height: f32) {
        ui.label(
            egui::RichText::new("Recent engine output")
                .small()
                .strong()
                .color(teal()),
        );
        egui::Frame::NONE
            .fill(egui::Color32::from_rgb(6, 10, 18))
            .stroke(egui::Stroke::new(1.0, egui::Color32::from_rgb(45, 90, 130)))
            .inner_margin(egui::Margin::same(8))
            .show(ui, |ui| {
                egui::ScrollArea::both()
                    .id_salt("latticra_recent_engine_output")
                    .max_height(max_height)
                    .stick_to_bottom(true)
                    .auto_shrink([false, false])
                    .show(ui, |ui| self.show_engine_log_lines(ui, max_lines));
            });
    }

    fn show_engine_log_lines(&self, ui: &mut egui::Ui, max_lines: usize) {
        if self.logs.is_empty() {
            ui.add(
                egui::Label::new(
                    egui::RichText::new("engine_log=waiting")
                        .monospace()
                        .small()
                        .color(muted()),
                )
                .wrap(),
            );
            return;
        }

        let start = self.logs.len().saturating_sub(max_lines);
        for (offset, line) in self.logs[start..].iter().enumerate() {
            record_line(ui, start + offset + 1, line, record_line_color(line));
        }
    }

    fn show_procedure(&mut self, ui: &mut egui::Ui) {
        ui.heading("Recommended procedure");
        ui.label("A safe Latticra first run is evidence-first, then install-second.");
        ui.add_space(8.0);
        ui.horizontal_wrapped(|ui| {
            status_chip(ui, "next", self.next_action_label());
            status_chip(ui, "mode", self.config.execution_mode_label());
            status_chip(
                ui,
                "evidence",
                if self.logs.is_empty() {
                    "waiting"
                } else {
                    "available"
                },
            );
            status_chip(
                ui,
                "local_ack",
                if self.guarded_local_ack { "1" } else { "0" },
            );
        });
        ui.add_space(8.0);

        let running = self.install_state == InstallState::Running;
        let has_evidence = !self.logs.is_empty();
        let local_mode_ready = !self.config.safety.dry_run && self.guarded_local_ack;
        let local_mode_locked = !self.config.safety.dry_run && !self.guarded_local_ack;

        procedure_row(
            ui,
            "01",
            "Choose Guided Workbench",
            "Start from a complete but dry configuration.",
            ProcedureState::Done,
        );
        procedure_row(
            ui,
            "02",
            "Inspect components",
            "Confirm Lat, LIR, Seal, docs, helpers, and Fedora validation intent.",
            ProcedureState::Ready,
        );
        procedure_row(
            ui,
            "03",
            "Configure Seal",
            "Pick a report-only, signature-planning, AEAD-planning, or hybrid Seal profile.",
            ProcedureState::Ready,
        );
        procedure_row(
            ui,
            "04",
            "Generate plan",
            "Write and inspect latticra-installer-plan.txt.",
            if has_evidence {
                ProcedureState::Done
            } else {
                ProcedureState::Current
            },
        );
        procedure_row(
            ui,
            "05",
            "Run Dry-Install",
            "Validate the engine and create a receipt without host mutation.",
            if running {
                ProcedureState::Current
            } else if has_evidence {
                ProcedureState::Done
            } else {
                ProcedureState::Ready
            },
        );
        procedure_row(
            ui,
            "06",
            "Review evidence",
            "Read console output, plan, logs, and receipt paths.",
            if running || has_evidence {
                ProcedureState::Current
            } else {
                ProcedureState::Pending
            },
        );
        procedure_row(
            ui,
            "07",
            "Enable local install",
            "Only then enable guarded local-prefix writes.",
            if local_mode_ready {
                ProcedureState::Done
            } else if local_mode_locked {
                ProcedureState::Locked
            } else {
                ProcedureState::Pending
            },
        );
        procedure_row(
            ui,
            "08",
            "Use the Panel updater for reinstall updates",
            "Preview the update first, then apply the guarded local-prefix reinstall from the current checkout.",
            if self.last_update_dry_run_ok {
                ProcedureState::Ready
            } else {
                ProcedureState::Pending
            },
        );
        procedure_row(
            ui,
            "09",
            "Reset or uninstall when specifications change",
            "Use reset before reinstalling from new specs, or uninstall to remove the managed local install.",
            if has_evidence {
                ProcedureState::Ready
            } else {
                ProcedureState::Pending
            },
        );

        ui.add_space(8.0);
        ui.horizontal_wrapped(|ui| {
            if ui.button("Open next surface").clicked() {
                self.open_next_surface();
            }
            if ui.button("Review Authority").clicked() {
                self.active_tab = WorkspaceTab::Authority;
            }
            if ui.button("Review Evidence").clicked() {
                self.active_tab = WorkspaceTab::Evidence;
            }
        });
    }

    fn show_action_buttons(&mut self, ui: &mut egui::Ui) {
        self.show_run_readiness_panel(ui);
        ui.add_space(8.0);

        panel_card_with_stroke(if self.install_state == InstallState::Running {
            blue()
        } else if self.config.safety.dry_run {
            teal()
        } else {
            green()
        })
        .show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("Command deck").size(18.0).color(ink()));
                status_chip(ui, "mode", self.config.execution_mode_label());
                status_chip(ui, "next", self.next_action_label());
            });
            ui.add_space(6.0);
            let artifact_blocker = self.panel_can_write_artifacts().err();
            let can_write_artifacts = artifact_blocker.is_none();
            ui.horizontal_wrapped(|ui| {
                let save_response =
                    ui.add_enabled(can_write_artifacts, egui::Button::new("Save configuration"));
                if save_response.clicked() {
                    self.save_config();
                }
                let plan_response =
                    ui.add_enabled(can_write_artifacts, egui::Button::new("Generate plan"));
                if plan_response.clicked() {
                    self.write_plan();
                    self.active_tab = WorkspaceTab::Evidence;
                    self.show_plan_over_log = true;
                }
                if ui.button("Open evidence").clicked() {
                    self.active_tab = WorkspaceTab::Evidence;
                }
                if ui.button("Open next surface").clicked() {
                    self.open_next_surface();
                }
            });
            if let Some(reason) = artifact_blocker.as_deref() {
                warning_note(ui, "Artifact writes locked", reason);
            }

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
        });
    }

    fn show_run_readiness_panel(&mut self, ui: &mut egui::Ui) {
        let running = self.install_state == InstallState::Running;
        let install_blocker = self.install_blocker(running);
        let removal_blocker = self.removal_blocker(running);
        let evidence_label = if self.logs.is_empty() {
            "waiting"
        } else if self.install_state == InstallState::Failed {
            "needs-review"
        } else {
            "available"
        };
        let install_label = if running {
            "running"
        } else if install_blocker.is_some() {
            "blocked"
        } else {
            "ready"
        };
        let removal_label = if running {
            "running"
        } else if removal_blocker.is_some() {
            "blocked"
        } else {
            "ready"
        };
        let write_gate_label = if self.config.safety.dry_run {
            "dry-run"
        } else if self.guarded_local_ack {
            "acknowledged"
        } else {
            "locked"
        };

        panel_card().show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("Run readiness").size(18.0).color(ink()));
                status_chip(ui, "install", install_label);
                status_chip(ui, "reset", removal_label);
                status_chip(ui, "writes", write_gate_label);
                status_chip(ui, "evidence", evidence_label);
            });
            ui.add(
                egui::Label::new(
                    egui::RichText::new(format!("Status: {}", self.status))
                        .small()
                        .color(muted()),
                )
                .wrap(),
            );
            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                if ui.button("Review gates").clicked() {
                    self.active_tab = WorkspaceTab::Authority;
                }
                if ui.button("Review delivery").clicked() {
                    self.active_tab = WorkspaceTab::Delivery;
                }
                if ui.button("Review evidence").clicked() {
                    self.active_tab = WorkspaceTab::Evidence;
                }
            });
        });
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
        let pulse = if running {
            ((time * 3.0).sin() + 1.0) * 0.5
        } else {
            0.0
        };
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

        let button_width = ui.available_width().clamp(180.0, 340.0);
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
        let button_width = ui.available_width().clamp(180.0, 340.0);
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
                colored_status_chip(
                    ui,
                    "state",
                    install_state_label(self.install_state),
                    console_state_color(self.install_state),
                );
                status_chip(ui, "lines", &self.console_lines.len().to_string());
                status_chip(ui, "authority", "panel-only");
                status_chip(ui, "root", "0");
                status_chip(ui, "network", "0");
            });
            ui.add(
                egui::Label::new(
                    egui::RichText::new(format!("cwd={}", self.terminal_cwd))
                        .monospace()
                        .small()
                        .color(muted()),
                )
                .wrap(),
            );
            ui.add(
                egui::Label::new(
                    egui::RichText::new(
                        "Panel commands and local navigation only. External host process launch is denied.",
                    )
                    .small()
                    .color(muted()),
                )
                .wrap(),
            );
            ui.add_space(6.0);

            let console_height = if self.install_state == InstallState::Running {
                RUNNING_CONSOLE_MAX_HEIGHT
            } else {
                IDLE_CONSOLE_MAX_HEIGHT
            };
            show_console_record_lines(
                ui,
                "latticra_embedded_console",
                &self.terminal_cwd,
                &self.console_lines,
                console_height,
                true,
            );

            ui.add_space(6.0);
            ui.horizontal_wrapped(|ui| {
                colored_status_chip(ui, "input", "allowlist", teal());
                status_chip(ui, "external_host", "0");
            });
            ui.add_space(4.0);
            ui.horizontal(|ui| {
                ui.label(egui::RichText::new("$").monospace().color(teal()));
                let input_width = (ui.available_width() - 64.0).max(120.0);
                let response = ui.add(
                    egui::TextEdit::singleline(&mut self.console_input)
                        .font(egui::TextStyle::Monospace)
                        .desired_width(input_width)
                        .hint_text("panel command"),
                );
                let enter_pressed =
                    response.lost_focus() && ui.input(|input| input.key_pressed(egui::Key::Enter));
                if enter_pressed {
                    self.run_console_command();
                }
                if ui
                    .add(
                        egui::Button::new("Run")
                            .fill(soft_blue())
                            .stroke(egui::Stroke::new(1.0, blue())),
                    )
                    .clicked()
                {
                    self.run_console_command();
                }
            });

            if self.install_state != InstallState::Running {
                ui.add_space(6.0);
                egui::CollapsingHeader::new("Command shortcuts")
                    .default_open(false)
                    .show(ui, |ui| {
                        console_shortcut_group(
                            ui,
                            self,
                            "core",
                            blue(),
                            &["help", "status", "pwd", "plan", "save", "clear"],
                        );
                        console_shortcut_group(
                            ui,
                            self,
                            "run",
                            green(),
                            &["dry-run", "reset", "uninstall"],
                        );
                        console_shortcut_group(
                            ui,
                            self,
                            "mode",
                            teal(),
                            &[
                                "mode dry",
                                "mode local",
                                "profile guided",
                                "profile seal",
                                "profile fedora",
                            ],
                        );
                        console_shortcut_group(
                            ui,
                            self,
                            "updater",
                            amber(),
                            &[
                                "updater",
                                "updater plan",
                                "updater dry-run",
                                "updater apply",
                            ],
                        );
                        console_shortcut_group(
                            ui,
                            self,
                            "lc",
                            teal(),
                            &[
                                "lc status",
                                "lc commands",
                                "lc install-config",
                                "lc profiles",
                                "lc standalone",
                            ],
                        );
                        console_shortcut_group(
                            ui,
                            self,
                            "nadia",
                            blue(),
                            &[
                                "nadia status",
                                "nadia commands",
                                "nadia context",
                                "nadia readiness",
                            ],
                        );
                    });
            }
        });
    }

    fn show_compact_auxiliary(&mut self, ui: &mut egui::Ui) {
        ui.add_space(12.0);
        ui.separator();
        egui::CollapsingHeader::new("Live evidence")
            .default_open(false)
            .show(ui, |ui| self.show_right_evidence_panel(ui));
        egui::CollapsingHeader::new("Panel Console")
            .default_open(false)
            .show(ui, |ui| self.show_console_panel(ui));
    }

    fn show_right_evidence_panel(&mut self, ui: &mut egui::Ui) {
        panel_card().show(ui, |ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("Live evidence").color(ink()));
                status_chip(
                    ui,
                    "view",
                    if self.show_plan_over_log {
                        "plan"
                    } else {
                        "log"
                    },
                );
                status_chip(ui, "log_lines", &self.logs.len().to_string());
            });
            ui.horizontal_wrapped(|ui| {
                if ui
                    .add(
                        egui::Button::new("Plan")
                            .selected(self.show_plan_over_log)
                            .fill(if self.show_plan_over_log {
                                soft_blue()
                            } else {
                                soft_surface()
                            }),
                    )
                    .clicked()
                {
                    self.show_plan_over_log = true;
                }
                if ui
                    .add(
                        egui::Button::new("Log")
                            .selected(!self.show_plan_over_log)
                            .fill(if !self.show_plan_over_log {
                                soft_blue()
                            } else {
                                soft_surface()
                            }),
                    )
                    .clicked()
                {
                    self.show_plan_over_log = false;
                }
            });
            if self.install_state == InstallState::Running {
                ui.add(egui::ProgressBar::new(self.progress()).show_percentage());
                ui.add(
                    egui::Label::new(
                        egui::RichText::new(format!("{}: {}", self.phase_title, self.status))
                            .small()
                            .color(muted()),
                    )
                    .wrap(),
                );
            }

            let evidence_height = if self.install_state == InstallState::Running {
                RUNNING_EVIDENCE_MAX_HEIGHT
            } else {
                IDLE_EVIDENCE_MAX_HEIGHT
            };
            if self.show_plan_over_log {
                show_record_text(
                    ui,
                    "latticra_right_evidence_plan",
                    &self.plan,
                    "plan=empty",
                    evidence_height,
                    false,
                );
            } else {
                show_record_lines(
                    ui,
                    "latticra_right_evidence_log",
                    &self.logs,
                    "engine_log=waiting",
                    evidence_height,
                    true,
                );
            }
        });
    }

    fn show_status_bar(&mut self, ui: &mut egui::Ui) {
        ui.horizontal_wrapped(|ui| {
            ui.monospace(
                egui::RichText::new(format!("Latticra Panel v{PANEL_VERSION}")).color(ink()),
            );
            colored_status_chip(
                ui,
                "state",
                install_state_label(self.install_state),
                console_state_color(self.install_state),
            );
            status_chip(ui, "active", workspace_tab_key(self.active_tab));
            status_chip(ui, "profile", self.config.profile.label());
            status_chip(ui, "seal", self.config.seal.crypto_profile.label());
            status_chip(ui, "mode", self.config.execution_mode_label());
            status_chip(ui, "next", self.next_action_label());
            if self.install_state == InstallState::Running {
                ui.add_sized(
                    [160.0, 14.0],
                    egui::ProgressBar::new(self.progress()).show_percentage(),
                );
            }
            ui.add(egui::Label::new(&self.status).truncate());
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
        let compact = should_use_compact_workspace(screen_width, fedora_desktop_runtime());
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

        if !compact {
            egui::Panel::left("left_workbench_nav")
                .resizable(false)
                .exact_size(if narrow {
                    LEFT_PANEL_NARROW_WIDTH
                } else {
                    LEFT_PANEL_WIDTH
                })
                .show_inside(root_ui, |ui| {
                    let nav_width = ui.available_width();
                    egui::ScrollArea::vertical()
                        .id_salt("left_workbench_nav_scroll")
                        .auto_shrink([false, false])
                        .show(ui, |ui| {
                            ui.set_width(nav_width);
                            self.show_sidebar(ui, compact);
                        });
                });
        }

        if !compact {
            egui::Panel::right("right_console")
                .resizable(true)
                .default_size(560.0)
                .min_size(360.0)
                .max_size(RIGHT_PANEL_MAX_WIDTH)
                .show_inside(root_ui, |ui| {
                    egui::ScrollArea::vertical()
                        .id_salt("right_console_scroll")
                        .auto_shrink([false, false])
                        .show(ui, |ui| {
                            if self.install_state == InstallState::Running {
                                self.show_right_evidence_panel(ui);
                                ui.add_space(10.0);
                                self.show_console_panel(ui);
                            } else {
                                self.show_console_panel(ui);
                                ui.add_space(10.0);
                                self.show_right_evidence_panel(ui);
                            }
                        });
                });
        }

        egui::CentralPanel::default().show_inside(root_ui, |ui| {
            self.show_main_workbench(ui, compact);
        });
    }
}

fn write_ui_artifact(filename: &str, contents: &[u8]) -> Result<(), String> {
    let current_dir = std::env::current_dir().map_err(|err| {
        format!("could not resolve current directory for installer artifact: {err}")
    })?;
    write_ui_artifact_at(&current_dir, filename, contents)
}

fn enforce_ui_artifact_authority_floor(config: &mut InstallerConfig) {
    config.safety.allow_network_effect = false;
    config.updater.allow_network_fetch = false;
    config.lc.install.allow_external_host_commands = false;
}

fn sanitized_ui_artifact_config(config: &InstallerConfig) -> Result<InstallerConfig, String> {
    let mut config = config.clone();
    enforce_ui_artifact_authority_floor(&mut config);
    config.can_write_artifacts()?;

    Ok(config)
}

fn ui_config_toml_artifact(config: &InstallerConfig) -> Result<(InstallerConfig, String), String> {
    let config = sanitized_ui_artifact_config(config)?;
    let toml = toml::to_string_pretty(&config)
        .map_err(|err| format!("could not serialize config: {err}"))?;

    Ok((config, toml))
}

fn ui_plan_artifact(config: &InstallerConfig) -> Result<(InstallerConfig, String), String> {
    let config = sanitized_ui_artifact_config(config)?;
    let plan = render_plan(&config);

    Ok((config, plan))
}

fn blocked_ui_plan(error: &str) -> String {
    format!("LATTICRA PANEL INSTALL PLAN\n\nvalidation_status=blocked\nvalidation_error={error}\n")
}

fn sanitize_console_line(line: &str) -> String {
    let redacted = engine::redact_log_line(line);
    let mut sanitized = String::new();
    let mut truncated = false;

    for (index, ch) in redacted.chars().enumerate() {
        if index >= CONSOLE_MAX_LINE_CHARS {
            truncated = true;
            break;
        }

        match ch {
            '\n' => sanitized.push_str("\\n"),
            '\r' => sanitized.push_str("\\r"),
            '\t' => sanitized.push_str("\\t"),
            ch if ch.is_control() => {
                let code = ch as u32;
                if code <= 0xFF {
                    let _ = write!(&mut sanitized, "\\x{code:02X}");
                } else {
                    let _ = write!(&mut sanitized, "\\u{{{code:X}}}");
                }
            }
            ch => sanitized.push(ch),
        }
    }

    if truncated {
        sanitized.push_str("...[truncated]");
    }

    sanitized
}

fn console_command_requires_authority_floor(parts: &[&str]) -> bool {
    !matches!(
        parts,
        [] | ["help"]
            | ["?"]
            | ["clear"]
            | ["pwd"]
            | ["cd"]
            | ["cd", _]
            | ["mode", "dry"]
            | ["mode", "local"]
            | ["lc", "commands"]
            | ["console", "commands"]
            | ["lc", "profiles"]
            | ["console", "profiles"]
            | ["nadia", "commands"]
            | ["nadia", "help"]
            | ["nadia", "?"]
            | ["profile", ..]
            | ["seal", "profile", ..]
            | ["lc", "profile", ..]
            | ["console", "profile", ..]
    )
}

fn write_ui_artifact_at(root: &Path, filename: &str, contents: &[u8]) -> Result<(), String> {
    let relative = Path::new(filename);
    if relative.file_name().and_then(|name| name.to_str()) != Some(filename) {
        return Err(format!(
            "refusing nested installer UI artifact path: {filename}"
        ));
    }

    let artifact_path = root.join(relative);
    engine::write_installer_artifact(&artifact_path, contents)
}

fn apply_panel_theme(ctx: &egui::Context) {
    ctx.set_theme(egui::Theme::Dark);
    let mut style = (*ctx.global_style()).clone();
    style.spacing.item_spacing = egui::vec2(8.0, 8.0);
    style.spacing.button_padding = egui::vec2(10.0, 7.0);
    style.spacing.interact_size = egui::vec2(40.0, 32.0);
    style.spacing.window_margin = egui::Margin::same(10);
    style
        .text_styles
        .insert(egui::TextStyle::Heading, egui::FontId::proportional(24.0));
    style
        .text_styles
        .insert(egui::TextStyle::Body, egui::FontId::proportional(15.5));
    style
        .text_styles
        .insert(egui::TextStyle::Button, egui::FontId::proportional(15.0));
    style
        .text_styles
        .insert(egui::TextStyle::Small, egui::FontId::proportional(13.0));
    style
        .text_styles
        .insert(egui::TextStyle::Monospace, egui::FontId::monospace(13.5));

    let mut visuals = egui::Visuals::dark();
    visuals.panel_fill = egui::Color32::from_rgb(12, 17, 21);
    visuals.window_fill = egui::Color32::from_rgb(18, 24, 28);
    visuals.window_stroke = egui::Stroke::new(1.0, border());
    visuals.window_corner_radius = egui::CornerRadius::same(8);
    visuals.menu_corner_radius = egui::CornerRadius::same(8);
    visuals.faint_bg_color = egui::Color32::from_rgb(21, 28, 32);
    visuals.extreme_bg_color = egui::Color32::from_rgb(8, 12, 15);
    visuals.code_bg_color = egui::Color32::from_rgb(20, 27, 32);
    visuals.hyperlink_color = blue();
    visuals.warn_fg_color = amber();
    visuals.error_fg_color = red();
    visuals.selection.bg_fill = egui::Color32::from_rgb(34, 83, 78);
    visuals.selection.stroke = egui::Stroke::new(1.0, teal());
    visuals.widgets.noninteractive.bg_fill = egui::Color32::from_rgb(18, 24, 28);
    visuals.widgets.noninteractive.weak_bg_fill = soft_surface();
    visuals.widgets.noninteractive.bg_stroke = egui::Stroke::new(1.0, border());
    visuals.widgets.noninteractive.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.widgets.inactive.bg_fill = egui::Color32::from_rgb(25, 34, 38);
    visuals.widgets.inactive.weak_bg_fill = soft_surface();
    visuals.widgets.inactive.bg_stroke = egui::Stroke::new(1.0, border());
    visuals.widgets.inactive.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.widgets.hovered.bg_fill = egui::Color32::from_rgb(31, 51, 49);
    visuals.widgets.hovered.weak_bg_fill = egui::Color32::from_rgb(35, 60, 56);
    visuals.widgets.hovered.bg_stroke = egui::Stroke::new(1.0, teal());
    visuals.widgets.hovered.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.widgets.active.bg_fill = egui::Color32::from_rgb(40, 78, 73);
    visuals.widgets.active.weak_bg_fill = egui::Color32::from_rgb(40, 78, 73);
    visuals.widgets.active.bg_stroke = egui::Stroke::new(1.0, teal());
    visuals.widgets.active.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.widgets.open.bg_fill = egui::Color32::from_rgb(28, 38, 42);
    visuals.widgets.open.weak_bg_fill = egui::Color32::from_rgb(28, 38, 42);
    visuals.widgets.open.bg_stroke = egui::Stroke::new(1.0, border_strong());
    visuals.widgets.open.fg_stroke = egui::Stroke::new(1.0, ink());
    visuals.override_text_color = Some(ink());
    visuals.weak_text_color = Some(muted());
    visuals.button_frame = true;
    visuals.interact_cursor = Some(egui::CursorIcon::PointingHand);

    style.visuals = visuals;
    ctx.set_global_style(style);
}

fn should_use_compact_workspace(screen_width: f32, fedora_desktop: bool) -> bool {
    screen_width < COMPACT_LAYOUT_WIDTH || fedora_desktop
}

fn fedora_desktop_runtime() -> bool {
    cfg!(target_os = "linux") && os_release_is_fedora("/etc/os-release")
}

fn os_release_is_fedora(path: &str) -> bool {
    std::fs::read_to_string(path)
        .map(|content| os_release_content_is_fedora(&content))
        .unwrap_or(false)
}

fn os_release_content_is_fedora(content: &str) -> bool {
    content.lines().any(|line| {
        let Some((key, value)) = line.split_once('=') else {
            return false;
        };
        if key != "ID" && key != "ID_LIKE" {
            return false;
        }

        let value = value.trim().trim_matches('"').trim_matches('\'');
        value.split_whitespace().any(|part| part == "fedora")
    })
}

fn panel_card() -> egui::Frame {
    panel_card_with_stroke(border())
}

fn panel_card_with_stroke(stroke_color: egui::Color32) -> egui::Frame {
    egui::Frame::NONE
        .fill(egui::Color32::from_rgb(18, 24, 28))
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
        .fill(egui::Color32::from_rgb(48, 35, 18))
        .stroke(egui::Stroke::new(
            1.0,
            egui::Color32::from_rgb(160, 112, 40),
        ))
        .corner_radius(egui::CornerRadius::same(8))
        .inner_margin(egui::Margin::same(10))
        .show(ui, |ui| {
            ui.label(egui::RichText::new(title).strong().color(amber()));
            ui.add(egui::Label::new(egui::RichText::new(body).small().color(ink())).wrap());
        });
}

fn show_record_text(
    ui: &mut egui::Ui,
    id_salt: &'static str,
    text: &str,
    empty_line: &str,
    max_height: f32,
    stick_to_bottom: bool,
) {
    let lines: Vec<&str> = text.lines().collect();
    record_frame().show(ui, |ui| {
        egui::ScrollArea::both()
            .id_salt(id_salt)
            .max_height(max_height)
            .stick_to_bottom(stick_to_bottom)
            .auto_shrink([false, false])
            .show(ui, |ui| {
                if lines.is_empty() {
                    record_line(ui, 1, empty_line, muted());
                    return;
                }

                for (index, line) in lines.iter().enumerate() {
                    record_line(ui, index + 1, line, record_line_color(line));
                }
            });
    });
}

fn show_record_lines(
    ui: &mut egui::Ui,
    id_salt: &'static str,
    lines: &[String],
    empty_line: &str,
    max_height: f32,
    stick_to_bottom: bool,
) {
    record_frame().show(ui, |ui| {
        egui::ScrollArea::both()
            .id_salt(id_salt)
            .max_height(max_height)
            .stick_to_bottom(stick_to_bottom)
            .auto_shrink([false, false])
            .show(ui, |ui| {
                if lines.is_empty() {
                    record_line(ui, 1, empty_line, muted());
                    return;
                }

                for (index, line) in lines.iter().enumerate() {
                    record_line(ui, index + 1, line, record_line_color(line));
                }
            });
    });
}

fn show_console_record_lines(
    ui: &mut egui::Ui,
    id_salt: &'static str,
    cwd: &str,
    lines: &[String],
    max_height: f32,
    stick_to_bottom: bool,
) {
    record_frame().show(ui, |ui| {
        egui::ScrollArea::both()
            .id_salt(id_salt)
            .max_height(max_height)
            .stick_to_bottom(stick_to_bottom)
            .auto_shrink([false, false])
            .show(ui, |ui| {
                record_line(ui, 1, &format!("prompt={cwd} shell=panel-console"), muted());

                if lines.is_empty() {
                    record_line(ui, 2, "console ready", muted());
                    return;
                }

                for (index, line) in lines.iter().enumerate() {
                    record_line(ui, index + 2, line, console_line_color(line));
                }
            });
    });
}

fn record_frame() -> egui::Frame {
    egui::Frame::NONE
        .fill(egui::Color32::from_rgb(6, 10, 18))
        .stroke(egui::Stroke::new(1.0, egui::Color32::from_rgb(45, 90, 130)))
        .corner_radius(egui::CornerRadius::same(8))
        .inner_margin(egui::Margin::same(8))
}

fn record_line(ui: &mut egui::Ui, number: usize, line: &str, color: egui::Color32) {
    ui.horizontal(|ui| {
        ui.add_sized(
            [34.0, 18.0],
            egui::Label::new(
                egui::RichText::new(format!("{number:>3}"))
                    .monospace()
                    .small()
                    .color(egui::Color32::from_rgb(92, 123, 142)),
            ),
        );
        ui.add(
            egui::Label::new(egui::RichText::new(line).monospace().small().color(color)).extend(),
        );
    });
}

fn record_line_color(line: &str) -> egui::Color32 {
    let lower = line.to_ascii_lowercase();
    if lower.contains("engine_failure")
        || lower.contains("blocked")
        || lower.contains("error")
        || lower.contains("failed")
    {
        return egui::Color32::from_rgb(255, 166, 142);
    }

    if lower.starts_with("phase ") || lower.contains("completed successfully") {
        return egui::Color32::from_rgb(155, 217, 255);
    }

    if lower.contains("authority=0")
        || lower.contains("network=0")
        || lower.contains("root=0")
        || lower.contains("allowed=0")
    {
        return egui::Color32::from_rgb(143, 232, 210);
    }

    if lower.contains("receipt") || lower.contains("evidence") || lower.contains("plan") {
        return egui::Color32::from_rgb(246, 206, 139);
    }

    egui::Color32::from_rgb(190, 220, 232)
}

fn console_line_color(line: &str) -> egui::Color32 {
    let lower = line.to_ascii_lowercase();
    if lower.contains("denied")
        || lower.contains("blocked")
        || lower.contains("failed")
        || lower.contains("error")
        || lower.contains("engine_failure")
    {
        return egui::Color32::from_rgb(255, 166, 142);
    }

    if lower.contains("authority=0")
        || lower.contains("network=0")
        || lower.contains("root=0")
        || lower.contains("allowed=0")
        || lower.contains("external_host")
        || lower.contains("host_process_launch_allowed=0")
    {
        return egui::Color32::from_rgb(143, 232, 210);
    }

    if lower.contains("receipt")
        || lower.contains("evidence")
        || lower.contains("plan")
        || lower.contains("contract")
    {
        return egui::Color32::from_rgb(246, 206, 139);
    }

    if lower.contains("profile")
        || lower.contains("mode=")
        || lower.contains("status")
        || lower.contains("saved")
        || lower.contains("updated")
    {
        return egui::Color32::from_rgb(155, 217, 255);
    }

    if lower.contains(" $ ") || lower.starts_with("panel_command=") {
        return egui::Color32::from_rgb(160, 230, 255);
    }

    egui::Color32::from_rgb(190, 220, 232)
}

fn install_state_label(state: InstallState) -> &'static str {
    match state {
        InstallState::Idle => "idle",
        InstallState::Running => "running",
        InstallState::Complete => "complete",
        InstallState::Failed => "failed",
    }
}

fn console_state_color(state: InstallState) -> egui::Color32 {
    match state {
        InstallState::Idle => teal(),
        InstallState::Running => blue(),
        InstallState::Complete => green(),
        InstallState::Failed => red(),
    }
}

fn console_shortcut_group(
    ui: &mut egui::Ui,
    app: &mut LatticraInstallerApp,
    label: &str,
    accent: egui::Color32,
    commands: &[&str],
) {
    ui.horizontal_wrapped(|ui| {
        colored_status_chip(ui, "group", label, accent);
        for command in commands {
            let response = ui.add(
                egui::Button::new(
                    egui::RichText::new(*command)
                        .monospace()
                        .small()
                        .color(ink()),
                )
                .fill(blend(soft_surface(), accent, 0.08))
                .stroke(egui::Stroke::new(1.0, blend(border(), accent, 0.45)))
                .corner_radius(egui::CornerRadius::same(6))
                .min_size(egui::vec2(0.0, 26.0)),
            );
            if response.clicked() {
                app.console_input = (*command).to_owned();
                app.run_console_command();
            }
        }
    });
    ui.add_space(4.0);
}

fn line_count(text: &str) -> usize {
    text.lines().count()
}

fn ink() -> egui::Color32 {
    egui::Color32::from_rgb(229, 236, 234)
}

fn muted() -> egui::Color32 {
    egui::Color32::from_rgb(158, 174, 180)
}

fn border() -> egui::Color32 {
    egui::Color32::from_rgb(55, 73, 82)
}

fn border_strong() -> egui::Color32 {
    egui::Color32::from_rgb(84, 108, 118)
}

fn soft_surface() -> egui::Color32 {
    egui::Color32::from_rgb(24, 32, 36)
}

fn soft_blue() -> egui::Color32 {
    egui::Color32::from_rgb(24, 48, 70)
}

fn soft_green() -> egui::Color32 {
    egui::Color32::from_rgb(24, 58, 49)
}

fn blue() -> egui::Color32 {
    egui::Color32::from_rgb(96, 165, 250)
}

fn teal() -> egui::Color32 {
    egui::Color32::from_rgb(45, 212, 191)
}

fn green() -> egui::Color32 {
    egui::Color32::from_rgb(91, 201, 126)
}

fn amber() -> egui::Color32 {
    egui::Color32::from_rgb(245, 158, 11)
}

fn red() -> egui::Color32 {
    egui::Color32::from_rgb(248, 113, 113)
}

fn workspace_tab_key(tab: WorkspaceTab) -> &'static str {
    match tab {
        WorkspaceTab::Dashboard => "dashboard",
        WorkspaceTab::Components => "components",
        WorkspaceTab::Console => "lc",
        WorkspaceTab::Seal => "seal",
        WorkspaceTab::Authority => "authority",
        WorkspaceTab::Delivery => "delivery",
        WorkspaceTab::Updater => "updater",
        WorkspaceTab::Evidence => "evidence",
        WorkspaceTab::Procedure => "procedure",
    }
}

fn workspace_tab_note(tab: WorkspaceTab) -> &'static str {
    match tab {
        WorkspaceTab::Dashboard => "Starting lanes and summary posture.",
        WorkspaceTab::Components => "Project pieces included in the local prefix.",
        WorkspaceTab::Console => "Latticra Console install and contract options.",
        WorkspaceTab::Seal => "Seal report, signature, and payload posture.",
        WorkspaceTab::Authority => "Local-write acknowledgements and evidence gates.",
        WorkspaceTab::Delivery => "Prefix layout, wrappers, payload, and build behavior.",
        WorkspaceTab::Updater => "Preview and apply guarded local reinstall updates.",
        WorkspaceTab::Evidence => "Plan, logs, receipts, and engine output.",
        WorkspaceTab::Procedure => "Evidence-first sequence for a safe first run.",
    }
}

fn workspace_tab_accent(tab: WorkspaceTab) -> egui::Color32 {
    match tab {
        WorkspaceTab::Dashboard => teal(),
        WorkspaceTab::Components => blue(),
        WorkspaceTab::Console => green(),
        WorkspaceTab::Seal => teal(),
        WorkspaceTab::Authority => amber(),
        WorkspaceTab::Delivery => green(),
        WorkspaceTab::Updater => amber(),
        WorkspaceTab::Evidence => blue(),
        WorkspaceTab::Procedure => teal(),
    }
}

fn sidebar_status_block(
    ui: &mut egui::Ui,
    active_tab: WorkspaceTab,
    next_action: &str,
    install_state: InstallState,
    guarded_local_ack: bool,
) {
    egui::Frame::NONE
        .fill(soft_surface())
        .stroke(egui::Stroke::new(1.0, border()))
        .corner_radius(egui::CornerRadius::same(8))
        .inner_margin(egui::Margin::same(8))
        .show(ui, |ui| {
            ui.label(
                egui::RichText::new("Workbench state")
                    .small()
                    .strong()
                    .color(teal()),
            );
            colored_status_chip(
                ui,
                "state",
                install_state_label(install_state),
                console_state_color(install_state),
            );
            colored_status_chip(
                ui,
                "active",
                workspace_tab_key(active_tab),
                workspace_tab_accent(active_tab),
            );
            status_chip(ui, "next", next_action);
            status_chip(ui, "ack", if guarded_local_ack { "1" } else { "0" });
        });
}

fn nav_button(ui: &mut egui::Ui, active: &mut WorkspaceTab, tab: WorkspaceTab, label: &str) {
    let selected = *active == tab;
    let accent = workspace_tab_accent(tab);
    let fill = if selected {
        blend(soft_surface(), accent, 0.22)
    } else {
        egui::Color32::TRANSPARENT
    };
    let stroke = if selected {
        egui::Stroke::new(1.0, accent)
    } else {
        egui::Stroke::new(1.0, egui::Color32::TRANSPARENT)
    };
    let button = egui::Button::new(egui::RichText::new(label).strong().color(ink()))
        .selected(selected)
        .fill(fill)
        .stroke(stroke)
        .corner_radius(egui::CornerRadius::same(6));
    if ui
        .add_sized([ui.available_width(), 34.0], button)
        .on_hover_text(workspace_tab_note(tab))
        .clicked()
    {
        *active = tab;
    }

    if selected {
        ui.horizontal_wrapped(|ui| {
            colored_status_chip(ui, "active", workspace_tab_key(tab), accent);
        });
        ui.add(
            egui::Label::new(
                egui::RichText::new(workspace_tab_note(tab))
                    .small()
                    .color(muted()),
            )
            .wrap(),
        );
        ui.add_space(3.0);
    }
}

fn status_chip(ui: &mut egui::Ui, key: &str, value: &str) {
    let key_label = chip_key_label(key);
    let (key_width, value_width) =
        chip_widths_for_available(&key_label, value, ui.available_width());
    let response = egui::Frame::NONE
        .fill(soft_surface())
        .stroke(egui::Stroke::new(1.0, border()))
        .corner_radius(egui::CornerRadius::same(6))
        .inner_margin(egui::Margin::symmetric(8, 5))
        .show(ui, |ui| {
            ui.horizontal(|ui| {
                ui.add_sized(
                    [key_width, 18.0],
                    egui::Label::new(
                        egui::RichText::new(&key_label)
                            .small()
                            .strong()
                            .color(muted()),
                    )
                    .truncate(),
                );
                ui.add_sized(
                    [value_width, 18.0],
                    egui::Label::new(egui::RichText::new(value).small().strong().color(ink()))
                        .truncate(),
                );
            });
        })
        .response;
    response.on_hover_text(format!("{}: {}", key.replace('_', " "), value));
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
        InstallProfile::LcStandalone => (
            "Console only",
            "Standalone LC wrapper, profiles, registry, and contracts without Panel runtime dependency.",
        ),
        InstallProfile::Custom => (
            "Manual operator",
            "Advanced manual control after the guided defaults are understood.",
        ),
    }
}

fn selected_component_count(components: &Components) -> usize {
    [
        components.latticra_console,
        components.lat_tooling,
        components.lir_contracts,
        components.seal_report_only,
        components.nadia_offline_ai,
        components.fedora_validation,
        components.docs_and_examples,
        components.developer_cli_helpers,
    ]
    .into_iter()
    .filter(|selected| *selected)
    .count()
}

fn component_card(
    ui: &mut egui::Ui,
    selected: &mut bool,
    title: &str,
    tag: &str,
    body: &str,
    accent: egui::Color32,
) -> bool {
    let stroke = if *selected { accent } else { border() };
    let mut changed = false;
    panel_card_with_stroke(stroke).show(ui, |ui| {
        ui.set_min_height(118.0);
        ui.horizontal_wrapped(|ui| {
            changed |= ui
                .checkbox(selected, egui::RichText::new(title).strong().color(ink()))
                .changed();
        });
        ui.horizontal_wrapped(|ui| {
            colored_status_chip(
                ui,
                "component",
                if *selected { "selected" } else { "off" },
                if *selected { accent } else { border_strong() },
            );
            status_chip(ui, "lane", tag);
        });
        ui.add(egui::Label::new(egui::RichText::new(body).small().color(muted())).wrap());
    });
    ui.add_space(6.0);
    changed
}

fn selected_behavior_count(behavior: &InstallBehavior) -> usize {
    [
        behavior.create_prefix_layout,
        behavior.create_component_markers,
        behavior.create_cli_shims,
        behavior.preserve_existing_files,
        behavior.build_gui_installer,
        behavior.build_latticra_from_source,
        behavior.install_payload_tree,
        behavior.install_desktop_entry,
        behavior.install_user_bin_wrappers,
    ]
    .into_iter()
    .filter(|selected| *selected)
    .count()
}

fn prefix_lane_label(prefix: &str) -> &'static str {
    if prefix.contains("latticra-validation") {
        "validation"
    } else if prefix.contains("latticra") {
        "standard"
    } else {
        "custom"
    }
}

fn delivery_layout_card(ui: &mut egui::Ui, behavior: &mut InstallBehavior) -> bool {
    let mut changed = false;
    panel_card_with_stroke(teal()).show(ui, |ui| {
        ui.heading(egui::RichText::new("Layout").size(17.0).color(ink()));
        ui.horizontal_wrapped(|ui| {
            colored_status_chip(ui, "group", "prefix", teal());
        });
        ui.add(
            egui::Label::new(
                egui::RichText::new("Directory structure, markers, and overwrite posture.")
                    .small()
                    .color(muted()),
            )
            .wrap(),
        );
        ui.separator();
        changed |= behavior_toggle_row(
            ui,
            &mut behavior.create_prefix_layout,
            "Create prefix layout",
            "Prepare the user-local directory structure.",
        );
        changed |= behavior_toggle_row(
            ui,
            &mut behavior.create_component_markers,
            "Create component markers",
            "Write installed component marker files.",
        );
        changed |= behavior_toggle_row(
            ui,
            &mut behavior.preserve_existing_files,
            "Preserve existing files",
            "Refuse to overwrite unmanaged files.",
        );
    });
    ui.add_space(6.0);
    changed
}

fn delivery_payload_card(ui: &mut egui::Ui, behavior: &mut InstallBehavior) -> bool {
    let mut changed = false;
    panel_card_with_stroke(blue()).show(ui, |ui| {
        ui.heading(egui::RichText::new("Payload").size(17.0).color(ink()));
        ui.horizontal_wrapped(|ui| {
            colored_status_chip(ui, "group", "wrappers", blue());
        });
        ui.add(
            egui::Label::new(
                egui::RichText::new("Project material, shims, and user-local commands.")
                    .small()
                    .color(muted()),
            )
            .wrap(),
        );
        ui.separator();
        changed |= behavior_toggle_row(
            ui,
            &mut behavior.install_payload_tree,
            "Install payload tree",
            "Copy project payload material into the local prefix.",
        );
        changed |= behavior_toggle_row(
            ui,
            &mut behavior.create_cli_shims,
            "Create CLI shims",
            "Prepare command shims inside the user-local prefix.",
        );
        changed |= behavior_toggle_row(
            ui,
            &mut behavior.install_user_bin_wrappers,
            "Install user bin wrappers",
            "Install user-local wrappers for latticra, lat, seal, and panel commands.",
        );
    });
    ui.add_space(6.0);
    changed
}

fn delivery_build_card(ui: &mut egui::Ui, behavior: &mut InstallBehavior) -> bool {
    let mut changed = false;
    panel_card_with_stroke(green()).show(ui, |ui| {
        ui.heading(egui::RichText::new("Build").size(17.0).color(ink()));
        ui.horizontal_wrapped(|ui| {
            colored_status_chip(ui, "group", "exposure", green());
        });
        ui.add(
            egui::Label::new(
                egui::RichText::new("Panel binary, source build, and desktop entry behavior.")
                    .small()
                    .color(muted()),
            )
            .wrap(),
        );
        ui.separator();
        changed |= behavior_toggle_row(
            ui,
            &mut behavior.build_gui_installer,
            "Build Latticra Panel binary",
            "Build the panel itself when Cargo is available.",
        );
        changed |= behavior_toggle_row(
            ui,
            &mut behavior.build_latticra_from_source,
            "Build Latticra from source when available",
            "Use supported root build systems when present.",
        );
        changed |= behavior_toggle_row(
            ui,
            &mut behavior.install_desktop_entry,
            "Install desktop entry",
            "Expose Latticra Panel in the user app grid.",
        );
    });
    ui.add_space(6.0);
    changed
}

fn selected_safety_gate_count(safety: &Safety) -> usize {
    [
        safety.require_component_manifest,
        safety.require_artifact_measurements,
        safety.require_verification_policy_metadata,
        safety.write_operator_receipt,
    ]
    .into_iter()
    .filter(|selected| *selected)
    .count()
}

fn authority_locked_card(
    ui: &mut egui::Ui,
    title: &str,
    tag: &str,
    body: &str,
    accent: egui::Color32,
) {
    panel_card_with_stroke(accent).show(ui, |ui| {
        ui.set_min_height(126.0);
        ui.heading(egui::RichText::new(title).size(17.0).color(ink()));
        ui.horizontal_wrapped(|ui| {
            colored_status_chip(ui, "authority", "0", accent);
            status_chip(ui, "lane", tag);
        });
        ui.add(egui::Label::new(egui::RichText::new(body).small().color(muted())).wrap());
    });
    ui.add_space(6.0);
}

fn safety_gate_card(
    ui: &mut egui::Ui,
    enabled: &mut bool,
    title: &str,
    tag: &str,
    body: &str,
    accent: egui::Color32,
) -> bool {
    let mut changed = false;
    panel_card_with_stroke(if *enabled { accent } else { border() }).show(ui, |ui| {
        ui.set_min_height(126.0);
        ui.horizontal_wrapped(|ui| {
            changed |= ui
                .checkbox(enabled, egui::RichText::new(title).strong().color(ink()))
                .changed();
        });
        ui.horizontal_wrapped(|ui| {
            colored_status_chip(
                ui,
                "gate",
                if *enabled { "required" } else { "off" },
                if *enabled { accent } else { border_strong() },
            );
            status_chip(ui, "evidence", tag);
        });
        ui.add(egui::Label::new(egui::RichText::new(body).small().color(muted())).wrap());
    });
    ui.add_space(6.0);
    changed
}

fn selected_updater_policy_count(updater: &UpdaterConfig) -> usize {
    [
        updater.require_dry_run_before_apply,
        updater.reuse_installer_engine,
        updater.write_update_receipt,
    ]
    .into_iter()
    .filter(|selected| *selected)
    .count()
}

fn updater_text_field(ui: &mut egui::Ui, label: &str, value: &mut String) -> bool {
    let mut changed = false;
    ui.vertical(|ui| {
        ui.label(egui::RichText::new(label).strong().color(ink()));
        changed |= ui
            .add(
                egui::TextEdit::singleline(value)
                    .desired_width(ui.available_width())
                    .margin(egui::Margin::symmetric(8, 6)),
            )
            .changed();
    });
    ui.add_space(6.0);
    changed
}

fn updater_policy_card(
    ui: &mut egui::Ui,
    enabled: &mut bool,
    title: &str,
    tag: &str,
    body: &str,
    accent: egui::Color32,
) -> bool {
    let mut changed = false;
    panel_card_with_stroke(if *enabled { accent } else { border() }).show(ui, |ui| {
        ui.set_min_height(132.0);
        ui.horizontal_wrapped(|ui| {
            changed |= ui
                .checkbox(enabled, egui::RichText::new(title).strong().color(ink()))
                .changed();
        });
        ui.horizontal_wrapped(|ui| {
            colored_status_chip(
                ui,
                "policy",
                if *enabled { "on" } else { "off" },
                if *enabled { accent } else { border_strong() },
            );
            status_chip(ui, "gate", tag);
        });
        ui.add(egui::Label::new(egui::RichText::new(body).small().color(muted())).wrap());
    });
    ui.add_space(6.0);
    changed
}

fn selected_seal_capability_count(seal: &SealConfig) -> usize {
    [
        seal.report_only,
        seal.require_signed_manifest,
        seal.write_seal_report,
    ]
    .into_iter()
    .filter(|selected| *selected)
    .count()
}

fn seal_capability_label(profile: SealCryptoProfile) -> &'static str {
    match profile {
        SealCryptoProfile::ReportOnly => "report",
        SealCryptoProfile::Blake2bEd25519 => "signing-plan",
        SealCryptoProfile::XChaCha20Poly1305 => "sealed-plan",
        SealCryptoProfile::HybridSeal => "hybrid-plan",
        SealCryptoProfile::Custom => "custom",
    }
}

fn seal_profile_note(profile: SealCryptoProfile) -> &'static str {
    match profile {
        SealCryptoProfile::ReportOnly => "Zero-key report lane",
        SealCryptoProfile::Blake2bEd25519 => "Default evidence/signature planning lane",
        SealCryptoProfile::XChaCha20Poly1305 => "AEAD sealed-payload planning lane",
        SealCryptoProfile::HybridSeal => "Advanced hybrid planning lane",
        SealCryptoProfile::Custom => "Manual parameter lane",
    }
}

fn seal_text_field(ui: &mut egui::Ui, label: &str, value: &mut String) -> bool {
    let mut changed = false;
    ui.vertical(|ui| {
        ui.label(egui::RichText::new(label).strong().color(ink()));
        changed |= ui
            .add(
                egui::TextEdit::singleline(value)
                    .desired_width(ui.available_width())
                    .margin(egui::Margin::symmetric(8, 6)),
            )
            .changed();
    });
    ui.add_space(6.0);
    changed
}

fn seal_toggle_row(ui: &mut egui::Ui, value: &mut bool, label: &str, note: &str) -> bool {
    let mut changed = false;
    ui.horizontal_wrapped(|ui| {
        changed |= ui
            .checkbox(value, egui::RichText::new(label).strong().color(ink()))
            .changed();
        colored_status_chip(
            ui,
            "enabled",
            if *value { "1" } else { "0" },
            if *value { teal() } else { border_strong() },
        );
    });
    ui.add(egui::Label::new(egui::RichText::new(note).small().color(muted())).wrap());
    ui.add_space(6.0);
    changed
}

fn behavior_toggle_row(ui: &mut egui::Ui, value: &mut bool, label: &str, note: &str) -> bool {
    let mut changed = false;
    ui.horizontal_wrapped(|ui| {
        changed |= ui
            .checkbox(value, egui::RichText::new(label).strong().color(ink()))
            .changed();
        colored_status_chip(
            ui,
            "enabled",
            if *value { "1" } else { "0" },
            if *value { teal() } else { border_strong() },
        );
    });
    ui.add(egui::Label::new(egui::RichText::new(note).small().color(muted())).wrap());
    ui.add_space(6.0);
    changed
}

fn selected_lc_contract_count(lc: &LatticraConsoleConfig) -> usize {
    [
        lc.report_only,
        lc.require_host_embedding_contract,
        lc.require_read_only_host_inventory_contract,
        lc.require_profile_receipt,
        lc.require_host_contract_receipt,
        lc.require_host_inventory_receipt,
        lc.require_host_adapter_contract,
        lc.require_session_contract,
        lc.require_workspace_contract,
        lc.require_namespace_contract,
        lc.require_rootfs_contract,
        lc.require_packages_contract,
        lc.require_init_contract,
        lc.require_services_contract,
        lc.require_service_schema_contract,
        lc.require_receipt_request_contract,
        lc.require_receipt_payload_schema,
        lc.require_receipt_payload_artifact_draft,
        lc.require_receipt_payload_artifact_review,
        lc.require_receipt_payload_artifact_review_receipt,
        lc.require_receipt_payload_artifact_review_receipt_draft,
        lc.require_receipt_payload_materialization_plan,
        lc.require_signature_request_binding,
        lc.require_os_base_contract,
        lc.require_vm_evidence_contract,
        lc.require_runtime_boundary_binding,
        lc.require_seal_capability_labels,
    ]
    .into_iter()
    .filter(|selected| *selected)
    .count()
}

fn lc_profile_note(profile: LatticraConsoleProfile) -> &'static str {
    match profile {
        LatticraConsoleProfile::HostedReference => "Reference metadata lane",
        LatticraConsoleProfile::PanelEmbedded => "Default Panel-installed lane",
        LatticraConsoleProfile::Standalone => "Standalone console wrapper lane",
        LatticraConsoleProfile::HostEmbeddedPlanning => "Future host-embedding lane",
        LatticraConsoleProfile::OsBasePlanning => "Future OS-base lane",
        LatticraConsoleProfile::Custom => "Manual LC parameter lane",
    }
}

fn lc_profile_accent(profile: LatticraConsoleProfile) -> egui::Color32 {
    match profile {
        LatticraConsoleProfile::HostedReference => teal(),
        LatticraConsoleProfile::PanelEmbedded => blue(),
        LatticraConsoleProfile::Standalone => green(),
        LatticraConsoleProfile::HostEmbeddedPlanning => amber(),
        LatticraConsoleProfile::OsBasePlanning => amber(),
        LatticraConsoleProfile::Custom => border_strong(),
    }
}

fn lc_profile_button(
    ui: &mut egui::Ui,
    app: &mut LatticraInstallerApp,
    profile: LatticraConsoleProfile,
    note: &str,
) {
    let selected = app.config.lc.profile == profile;
    let accent = lc_profile_accent(profile);
    panel_card_with_stroke(if selected { accent } else { border() }).show(ui, |ui| {
        ui.set_min_height(132.0);
        ui.heading(egui::RichText::new(profile.label()).size(17.0).color(ink()));
        ui.horizontal_wrapped(|ui| {
            status_chip(ui, "lane", profile.key());
            if selected {
                colored_status_chip(ui, "selected", "1", accent);
            }
        });
        ui.add(egui::Label::new(note).wrap());
        ui.add(
            egui::Label::new(egui::RichText::new(profile.detail()).small().color(muted())).wrap(),
        );
        ui.add_space(6.0);
        if selected {
            ui.add_enabled(
                false,
                egui::Button::new("Current profile").fill(soft_green()),
            );
        } else if ui
            .add(
                egui::Button::new("Use profile")
                    .fill(soft_blue())
                    .stroke(egui::Stroke::new(1.0, accent)),
            )
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
    let accent = match profile {
        SealCryptoProfile::ReportOnly => teal(),
        SealCryptoProfile::Blake2bEd25519 => blue(),
        SealCryptoProfile::XChaCha20Poly1305 => green(),
        SealCryptoProfile::HybridSeal => amber(),
        SealCryptoProfile::Custom => border_strong(),
    };
    panel_card_with_stroke(if selected { accent } else { border() }).show(ui, |ui| {
        ui.set_min_height(138.0);
        ui.heading(egui::RichText::new(profile.label()).size(17.0).color(ink()));
        ui.horizontal_wrapped(|ui| {
            colored_status_chip(ui, "lane", seal_capability_label(profile), accent);
            if selected {
                status_chip(ui, "selected", "1");
            }
        });
        ui.add(egui::Label::new(note).wrap());
        ui.add(
            egui::Label::new(egui::RichText::new(profile.detail()).small().color(muted())).wrap(),
        );
        ui.add_space(6.0);
        if selected {
            ui.add_enabled(
                false,
                egui::Button::new("Current profile").fill(soft_green()),
            );
        } else if ui
            .add(
                egui::Button::new("Use profile")
                    .fill(soft_blue())
                    .stroke(egui::Stroke::new(1.0, accent)),
            )
            .clicked()
        {
            app.apply_seal_crypto_profile(profile);
        }
    });
}

fn procedure_row(ui: &mut egui::Ui, number: &str, title: &str, body: &str, state: ProcedureState) {
    panel_card_with_stroke(procedure_state_color(state)).show(ui, |ui| {
        ui.horizontal_top(|ui| {
            status_chip(ui, "step", number);
            colored_status_chip(
                ui,
                "state",
                procedure_state_label(state),
                procedure_state_color(state),
            );
            ui.vertical(|ui| {
                ui.label(egui::RichText::new(title).strong().color(ink()));
                ui.add(egui::Label::new(egui::RichText::new(body).color(muted())).wrap());
            });
        });
    });
    ui.add_space(4.0);
}

fn procedure_state_label(state: ProcedureState) -> &'static str {
    match state {
        ProcedureState::Done => "done",
        ProcedureState::Current => "current",
        ProcedureState::Ready => "ready",
        ProcedureState::Locked => "locked",
        ProcedureState::Pending => "pending",
    }
}

fn procedure_state_color(state: ProcedureState) -> egui::Color32 {
    match state {
        ProcedureState::Done => green(),
        ProcedureState::Current => blue(),
        ProcedureState::Ready => teal(),
        ProcedureState::Locked => amber(),
        ProcedureState::Pending => border_strong(),
    }
}

fn colored_status_chip(ui: &mut egui::Ui, key: &str, value: &str, color: egui::Color32) {
    let key_label = chip_key_label(key);
    let (key_width, value_width) =
        chip_widths_for_available(&key_label, value, ui.available_width());
    let response = egui::Frame::NONE
        .fill(blend(soft_surface(), color, 0.16))
        .stroke(egui::Stroke::new(1.0, color))
        .corner_radius(egui::CornerRadius::same(6))
        .inner_margin(egui::Margin::symmetric(8, 5))
        .show(ui, |ui| {
            ui.horizontal(|ui| {
                ui.add_sized(
                    [key_width, 18.0],
                    egui::Label::new(
                        egui::RichText::new(&key_label)
                            .small()
                            .strong()
                            .color(color),
                    )
                    .truncate(),
                );
                ui.add_sized(
                    [value_width, 18.0],
                    egui::Label::new(egui::RichText::new(value).small().strong().color(ink()))
                        .truncate(),
                );
            });
        })
        .response;
    response.on_hover_text(format!("{}: {}", key.replace('_', " "), value));
}

fn chip_key_label(key: &str) -> String {
    match key {
        "component" => "comp".to_owned(),
        "components" => "parts".to_owned(),
        "local_ack" | "local_write_ack" => "ack".to_owned(),
        "external_host" => "host".to_owned(),
        "production_installer_ready" => "prod".to_owned(),
        "runtime_enforcement_authority" => "runtime".to_owned(),
        "root_authority" => "root".to_owned(),
        "network_authority" => "network".to_owned(),
        "report_only" => "report".to_owned(),
        "signed_manifest" => "manifest".to_owned(),
        "evidence_gates" => "gates".to_owned(),
        "dry_run_ok" => "dry run".to_owned(),
        _ => key.replace('_', " "),
    }
}

fn chip_key_width(key: &str) -> f32 {
    let width = 8.0 + key.chars().count() as f32 * 7.0;
    width.clamp(34.0, 104.0)
}

fn chip_value_width(value: &str) -> f32 {
    let width = 12.0 + value.chars().count() as f32 * 7.0;
    width.clamp(32.0, 136.0)
}

fn chip_widths_for_available(key: &str, value: &str, available_width: f32) -> (f32, f32) {
    let mut key_width = chip_key_width(key);
    let mut value_width = chip_value_width(value);
    let max_inner = (available_width - 30.0).max(62.0);
    let total_width = key_width + value_width;

    if total_width > max_inner {
        let mut excess = total_width - max_inner;
        let value_shrink = excess.min((value_width - 38.0).max(0.0));
        value_width -= value_shrink;
        excess -= value_shrink;

        let key_shrink = excess.min((key_width - 28.0).max(0.0));
        key_width -= key_shrink;
    }

    (key_width, value_width)
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
        Box::new(|cc| {
            apply_panel_theme(&cc.egui_ctx);
            Ok(Box::<LatticraInstallerApp>::default())
        }),
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::fs;
    use std::time::{SystemTime, UNIX_EPOCH};

    fn unique_temp_root(label: &str) -> std::path::PathBuf {
        let nanos = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .expect("system clock before unix epoch")
            .as_nanos();
        std::env::temp_dir().join(format!(
            "latticra-panel-ui-{label}-{}-{nanos}",
            std::process::id()
        ))
    }

    #[test]
    fn ui_config_artifact_rejects_invalid_authority_slug() {
        let mut config = InstallerConfig::default();
        config.lc.session_contract_profile = "../escape".to_owned();

        let error = ui_config_toml_artifact(&config).unwrap_err();
        assert!(error.contains("LC session contract profile"));
    }

    #[test]
    fn ui_plan_artifact_rejects_invalid_authority_slug() {
        let mut config = InstallerConfig::default();
        config.updater.update_channel = "local checkout".to_owned();

        let error = ui_plan_artifact(&config).unwrap_err();
        assert!(error.contains("Updater update channel"));
    }

    #[test]
    fn ui_artifact_config_forces_network_authority_off() {
        let mut config = InstallerConfig::default();
        config.safety.allow_network_effect = true;
        config.updater.allow_network_fetch = true;
        config.lc.install.allow_external_host_commands = true;

        let sanitized = sanitized_ui_artifact_config(&config).expect("sanitize UI artifact config");
        assert!(!sanitized.safety.allow_network_effect);
        assert!(!sanitized.updater.allow_network_fetch);
        assert!(!sanitized.lc.install.allow_external_host_commands);
    }

    #[test]
    fn compact_workspace_keeps_macos_width_rule_when_not_fedora() {
        assert!(should_use_compact_workspace(
            COMPACT_LAYOUT_WIDTH - 1.0,
            false
        ));
        assert!(!should_use_compact_workspace(
            COMPACT_LAYOUT_WIDTH + 240.0,
            false
        ));
    }

    #[test]
    fn compact_workspace_is_forced_for_fedora() {
        assert!(should_use_compact_workspace(
            COMPACT_LAYOUT_WIDTH + 240.0,
            true
        ));
    }

    #[test]
    fn os_release_detects_fedora_id() {
        assert!(os_release_content_is_fedora(
            "NAME=\"Fedora Linux\"\nID=fedora\nVERSION_ID=42\n"
        ));
        assert!(os_release_content_is_fedora(
            "NAME=\"Fedora Remix\"\nID=custom\nID_LIKE=\"rhel fedora\"\n"
        ));
        assert!(!os_release_content_is_fedora(
            "NAME=\"Ubuntu\"\nID=ubuntu\nID_LIKE=debian\n"
        ));
    }

    #[test]
    fn blocked_ui_plan_omits_invalid_authority_value() {
        let mut config = InstallerConfig::default();
        config.lc.session_contract_profile = "../escape".to_owned();

        let error = ui_plan_artifact(&config).unwrap_err();
        let plan = blocked_ui_plan(&error);
        assert!(plan.contains("validation_status=blocked"));
        assert!(!plan.contains("../escape"));
    }

    #[test]
    fn console_config_report_blocks_invalid_authority_without_reflection() {
        let mut app = LatticraInstallerApp::default();
        app.config.lc.session_contract_profile = "../escape".to_owned();
        app.console_input = "lc status".to_owned();

        app.run_console_command();

        let console = app.console_lines.join("\n");
        assert!(console.contains("blocked: console command requires valid authority fields"));
        assert!(console.contains("LC session contract profile"));
        assert!(!console.contains("../escape"));
    }

    #[test]
    fn console_updater_report_blocks_invalid_authority_without_reflection() {
        let mut app = LatticraInstallerApp::default();
        app.config.updater.update_channel = "local checkout".to_owned();
        app.console_input = "updater status".to_owned();

        app.run_console_command();

        let console = app.console_lines.join("\n");
        assert!(console.contains("blocked: console command requires valid authority fields"));
        assert!(console.contains("Updater update channel"));
        assert!(!console.contains("local checkout"));
    }

    #[test]
    fn console_profile_command_can_repair_invalid_authority() {
        let mut app = LatticraInstallerApp::default();
        app.config.lc.session_contract_profile = "../escape".to_owned();
        app.console_input = "lc profile panel".to_owned();

        app.run_console_command();

        let console = app.console_lines.join("\n");
        assert!(console.contains("lc.profile ->"));
        assert!(!console.contains("blocked: console command requires valid authority fields"));
        assert_ne!(app.config.lc.session_contract_profile, "../escape");
    }

    #[test]
    fn console_command_discovery_works_with_invalid_authority() {
        let mut app = LatticraInstallerApp::default();
        app.config.lc.session_contract_profile = "../escape".to_owned();
        app.console_input = "lc profiles".to_owned();

        app.run_console_command();

        let console = app.console_lines.join("\n");
        assert!(console.contains("panel_embedded"));
        assert!(!console.contains("blocked: console command requires valid authority fields"));
        assert!(!console.contains("../escape"));
    }

    #[test]
    fn console_line_sanitizer_escapes_control_characters() {
        let line = sanitize_console_line("ok\nbad\r\x1B[2J\tend\0");

        assert_eq!(line, "ok\\nbad\\r\\x1B[2J\\tend\\x00");
    }

    #[test]
    fn console_line_sanitizer_redacts_secret_assignments() {
        let line = sanitize_console_line(&format!(
            "{}{}{}{} done",
            "OPENAI", "_API_KEY=", "sk-proj-", "secret12345678901234567890"
        ));
        let expected = format!("{}{}[redacted] done", "OPENAI", "_API_KEY=");

        assert_eq!(line, expected);
    }

    #[test]
    fn console_line_sanitizer_truncates_oversized_lines() {
        let oversized = "a".repeat(CONSOLE_MAX_LINE_CHARS + 16);
        let line = sanitize_console_line(&oversized);

        assert!(line.ends_with("...[truncated]"));
        assert!(line.len() < oversized.len());
    }

    #[test]
    fn console_command_echo_escapes_multiline_secret_input() {
        let mut app = LatticraInstallerApp::default();
        app.console_input = format!(
            "unknown\n{}{}{}{}",
            "OPENAI", "_API_KEY=", "sk-proj-", "secret12345678901234567890"
        );

        app.run_console_command();

        assert!(app.console_lines.iter().all(|line| !line.contains('\n')));
        assert!(app.console_lines.iter().any(|line| line.contains("\\n")));
        assert!(!app
            .console_lines
            .iter()
            .any(|line| line.contains("sk-proj-secret")));
        assert!(app
            .console_lines
            .iter()
            .any(|line| line.contains(&format!("{}{}[redacted]", "OPENAI", "_API_KEY="))));
    }

    #[test]
    fn write_ui_artifact_at_replaces_regular_file() {
        let root = unique_temp_root("artifact-regular");
        fs::create_dir_all(&root).expect("create ui artifact fixture");
        let artifact = root.join(UI_PLAN_ARTIFACT);

        write_ui_artifact_at(&root, UI_PLAN_ARTIFACT, b"first\n").expect("write first artifact");
        write_ui_artifact_at(&root, UI_PLAN_ARTIFACT, b"second\n").expect("replace artifact");

        assert_eq!(
            fs::read_to_string(&artifact).expect("read ui artifact"),
            "second\n"
        );

        fs::remove_dir_all(root).expect("cleanup fixture");
    }

    #[cfg(unix)]
    #[test]
    fn write_ui_artifact_at_rejects_symlink_target() {
        let root = unique_temp_root("artifact-symlink");
        fs::create_dir_all(&root).expect("create ui artifact fixture");
        let victim = root.join("victim.txt");
        let artifact = root.join(UI_CONFIG_ARTIFACT);

        fs::write(&victim, "do-not-overwrite\n").expect("write victim");
        std::os::unix::fs::symlink(&victim, &artifact).expect("create artifact symlink");

        assert!(write_ui_artifact_at(&root, UI_CONFIG_ARTIFACT, b"replacement\n").is_err());
        assert_eq!(
            fs::read_to_string(&victim).expect("read victim"),
            "do-not-overwrite\n"
        );

        fs::remove_dir_all(root).expect("cleanup fixture");
    }

    #[test]
    fn write_ui_artifact_at_rejects_nested_path() {
        let root = unique_temp_root("artifact-nested");
        fs::create_dir_all(&root).expect("create ui artifact fixture");

        assert!(write_ui_artifact_at(&root, "../latticra-installer-plan.txt", b"plan\n").is_err());
        assert!(
            write_ui_artifact_at(&root, "nested/latticra-installer-plan.txt", b"plan\n").is_err()
        );

        fs::remove_dir_all(root).expect("cleanup fixture");
    }
}
