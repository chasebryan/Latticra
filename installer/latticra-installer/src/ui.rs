use crate::config::{render_plan, InstallProfile, InstallerConfig, SealCryptoProfile};
use crate::engine::{self, InstallEvent};
use eframe::egui;
use std::fs;
use std::sync::mpsc::Receiver;
use std::time::Duration;

const PANEL_VERSION: &str = env!("CARGO_PKG_VERSION");
const PANEL_BUILD: &str = "gui-workbench";
const SEAL_PNG: &[u8] = include_bytes!("../assets/latticra-panel.png");
const COMPACT_LAYOUT_WIDTH: f32 = 1400.0;
const NARROW_LAYOUT_WIDTH: f32 = 900.0;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum InstallState {
    Idle,
    Running,
    Complete,
    Failed,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum WorkspaceTab {
    Dashboard,
    Components,
    Seal,
    Authority,
    Delivery,
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
                "Panel commands: help, status, plan, save, dry-run, reset, profile seal, profile fedora."
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

    fn refresh_plan(&mut self) {
        self.config.safety.allow_network_effect = false;
        self.plan = render_plan(&self.config);
    }

    fn apply_profile(&mut self, profile: InstallProfile) {
        self.config.profile = profile;
        self.config.apply_profile_defaults();
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

    fn set_mode_dry(&mut self) {
        self.config.safety.dry_run = true;
        self.config.safety.allow_host_mutation = false;
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
        self.config.safety.allow_network_effect = false;
        match self.config.can_execute() {
            Ok(()) => {
                self.refresh_plan();
                self.logs.clear();
                self.phase_index = 0;
                self.phase_total = 10;
                self.phase_title = "starting".to_owned();
                self.install_state = InstallState::Running;
                self.status = format!("Starting {}...", self.config.execution_mode_label());
                self.push_console(format!("launching {}", self.config.execution_mode_label()));
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

    fn start_reset(&mut self) {
        self.config.safety.allow_network_effect = false;
        match self.config.can_reset() {
            Ok(()) => {
                self.logs.clear();
                self.phase_index = 0;
                self.phase_total = 5;
                self.phase_title = "starting reset".to_owned();
                self.install_state = InstallState::Running;
                self.status = format!("Starting {}...", self.config.reset_mode_label());
                self.push_console(format!("launching {}", self.config.reset_mode_label()));
                self.rx = Some(engine::launch_reset(self.config.clone()));
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
                        self.status = "Engine completed successfully.".to_owned();
                        self.push_console("engine: completed successfully");
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
                    "panel: help, status, plan, save, dry-run, reset, clear, nadia status, nadia context, nadia runtime, nadia plan, nadia mode, nadia ledger, nadia safety, nadia tool, nadia prompt-contract, nadia model-registry, nadia inference-readiness, nadia runtime-invocation, nadia model-load, nadia prompt-receipt, nadia prompt-materialization, nadia awareness-dialogue, nadia prompt-evaluation-handoff, nadia tokenization-boundary",
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
                    "nadia_offline_ai={}",
                    self.config.components.nadia_offline_ai
                ));
                self.push_console(format!("install_prefix={}", self.config.install_prefix));
                self.push_console(
                    "root_authority=0 network_authority=0 runtime_enforcement_authority=0",
                );
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
                    "stage=17 tokenization-boundary-contract; prompt_tokenized=0 prompt_evaluated=0",
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
            ["save"] => self.save_config(),
            ["dry-run"] | ["run"] => self.start_install(),
            ["reset"] | ["reset-local"] | ["uninstall"] => self.start_reset(),
            ["clear"] => self.console_lines.clear(),
            ["mode", "dry"] => self.set_mode_dry(),
            ["mode", "local"] => self.set_mode_local(),
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
            "allowed panel commands: help, status, plan, save, dry-run, reset, clear",
        );
        self.push_console("allowed navigation commands: pwd, cd <path>");
    }

    fn show_header(&mut self, ui: &mut egui::Ui, compact: bool) {
        if compact {
            ui.horizontal_wrapped(|ui| {
                ui.heading(egui::RichText::new("Latticra Panel").size(20.0));
                ui.label(egui::RichText::new(format!("v{PANEL_VERSION}")).monospace());
                ui.separator();
                ui.label("first-run workbench");
            });
            ui.horizontal_wrapped(|ui| {
                ui.monospace(format!("seal={}", self.config.seal.crypto_profile.label()));
                ui.monospace(format!("mode={}", self.config.execution_mode_label()));
                ui.monospace("root=0 network=0 runtime=0");
            });
            return;
        }

        ui.horizontal_wrapped(|ui| {
            ui.heading(egui::RichText::new("Latticra Panel").size(22.0));
            ui.label(egui::RichText::new(format!("v{PANEL_VERSION}")).monospace());
            ui.separator();
            ui.label("workbench for first-run configuration, validation, receipts, terminal access, and Seal profiles");
            ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                ui.monospace(format!("seal={}", self.config.seal.crypto_profile.label()));
                ui.monospace(format!("mode={}", self.config.execution_mode_label()));
                ui.monospace("root=0 network=0 runtime=0");
            });
        });
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
        if ui.button("Dry-run mode").clicked() {
            self.set_mode_dry();
        }
        if ui.button("Guarded local mode").clicked() {
            self.set_mode_local();
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
            .id_source("latticra_main_workbench")
            .auto_shrink([false, false])
            .show(ui, |ui| {
                self.show_hero_strip(ui);
                ui.add_space(10.0);

                match self.active_tab {
                    WorkspaceTab::Dashboard => self.show_dashboard(ui),
                    WorkspaceTab::Components => self.show_components(ui),
                    WorkspaceTab::Seal => self.show_seal_config(ui),
                    WorkspaceTab::Authority => self.show_authority(ui),
                    WorkspaceTab::Delivery => self.show_delivery(ui),
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
        ui.group(|ui| {
            if stack {
                ui.vertical(|ui| {
                    ui.heading("Guided Workbench");
                    ui.label(self.config.profile.detail());
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
                    status_chip(ui, "ready", "0");
                    status_chip(ui, "root", "0");
                    status_chip(ui, "network", "0");
                    status_chip(ui, "runtime", "0");
                });
                return;
            }

            ui.horizontal_top(|ui| {
                ui.vertical(|ui| {
                    ui.heading("Guided Workbench");
                    ui.label(self.config.profile.detail());
                    ui.add_space(6.0);
                    ui.horizontal_wrapped(|ui| {
                        status_chip(ui, "version", PANEL_VERSION);
                        status_chip(ui, "profile", self.config.profile.label());
                        status_chip(ui, "mode", self.config.execution_mode_label());
                        status_chip(ui, "seal", self.config.seal.crypto_profile.label());
                    });
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
        ui.label("The workbench starts with safe, useful defaults. Generate a plan and run a dry-install receipt before enabling any local writes.");
        ui.add_space(8.0);

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
        ui.group(|ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading(profile.label());
                if self.config.profile == profile {
                    ui.colored_label(egui::Color32::from_rgb(120, 220, 255), "selected");
                } else {
                    ui.label(badge);
                }
            });
            ui.label(description);
            if ui.button(format!("Use {}", profile.label())).clicked() {
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
            "Stage-17 tokenization-boundary contract with metadata-only Console surfaces.",
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
        checkbox_note(
            ui,
            &mut self.config.safety.dry_run,
            "Dry-run only",
            "Validation and receipts only. This is the recommended first-run mode.",
        );
        checkbox_note(
            ui,
            &mut self.config.safety.allow_host_mutation,
            "Allow guarded local-prefix writes",
            "Required only for an actual user-local install. Still no root/system mutation.",
        );
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
            .id_source("latticra_evidence_panel")
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
            "Reset when specifications change",
            "Use the guarded reset path to remove the managed prefix, wrappers, desktop entry, and icons before reinstalling.",
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

        if let Err(err) = self.config.can_execute() {
            ui.colored_label(egui::Color32::from_rgb(255, 160, 130), err);
        }
        if let Err(err) = self.config.can_reset() {
            ui.colored_label(egui::Color32::from_rgb(255, 190, 130), err);
        }
    }

    fn show_fluid_install_button(&mut self, ui: &mut egui::Ui) {
        let running = self.install_state == InstallState::Running;
        let can_execute = self.config.can_execute().is_ok() && !running;
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

        let response = ui.add_enabled(can_execute, button);
        if response.clicked() {
            self.start_install();
        }
    }

    fn show_reset_button(&mut self, ui: &mut egui::Ui) {
        let running = self.install_state == InstallState::Running;
        let can_reset = self.config.can_reset().is_ok() && !running;
        let label = if self.config.safety.dry_run {
            "Preview local reset"
        } else {
            "Reset installed local prefix"
        };

        let button_width = ui.available_width().min(340.0).max(180.0);
        let text_size = if button_width < 280.0 { 14.0 } else { 16.0 };
        let button = egui::Button::new(egui::RichText::new(label).size(text_size).strong())
            .min_size(egui::vec2(button_width, 44.0))
            .fill(egui::Color32::from_rgb(96, 70, 38))
            .stroke(egui::Stroke::new(
                1.0,
                egui::Color32::from_rgb(230, 185, 120),
            ));

        let response = ui.add_enabled(can_reset, button);
        if response.clicked() {
            self.start_reset();
        }
    }

    fn reset_install_prefix(&mut self) {
        self.config.install_prefix = match self.config.profile {
            InstallProfile::FedoraValidationVm => "~/.local/share/latticra-validation".to_owned(),
            _ => "~/.local/share/latticra".to_owned(),
        };
    }

    fn show_console_panel(&mut self, ui: &mut egui::Ui) {
        ui.group(|ui| {
            ui.horizontal_wrapped(|ui| {
                ui.heading("Host Quick Terminal");
                ui.small(format!("cwd={}", self.terminal_cwd));
            });
            ui.small("Panel commands and local navigation only. No external host process is launched by the console.");
            ui.add_space(6.0);

            egui::Frame::none()
                .fill(egui::Color32::from_rgb(6, 10, 18))
                .stroke(egui::Stroke::new(1.0, egui::Color32::from_rgb(45, 90, 130)))
                .inner_margin(egui::Margin::same(8.0))
                .show(ui, |ui| {
                    egui::ScrollArea::vertical()
                        .id_source("latticra_embedded_console")
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
                    "pwd",
                    "plan",
                    "dry-run",
                    "reset",
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
                .id_source("latticra_right_evidence")
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
            ui.monospace(format!("Latticra Panel v{PANEL_VERSION}"));
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
    fn update(&mut self, ctx: &egui::Context, _: &mut eframe::Frame) {
        self.ensure_texture(ctx);
        self.drain_events();
        let screen_width = ctx.screen_rect().width();
        let compact = screen_width < COMPACT_LAYOUT_WIDTH;
        let narrow = screen_width < NARROW_LAYOUT_WIDTH;

        if self.install_state == InstallState::Running {
            ctx.request_repaint_after(Duration::from_millis(33));
        }

        egui::TopBottomPanel::top("top_header").show(ctx, |ui| {
            self.show_header(ui, compact);
        });

        egui::TopBottomPanel::bottom("bottom_status").show(ctx, |ui| {
            self.show_status_bar(ui);
        });

        egui::SidePanel::left("left_workbench_nav")
            .resizable(true)
            .default_width(if narrow { 170.0 } else { 230.0 })
            .min_width(if narrow { 150.0 } else { 180.0 })
            .show(ctx, |ui| {
                egui::ScrollArea::vertical()
                    .id_source("left_workbench_nav_scroll")
                    .auto_shrink([false, false])
                    .show(ui, |ui| self.show_sidebar(ui, compact));
            });

        if !compact {
            egui::SidePanel::right("right_console")
                .resizable(true)
                .default_width(560.0)
                .min_width(360.0)
                .show(ctx, |ui| {
                    egui::ScrollArea::vertical()
                        .id_source("right_console_scroll")
                        .auto_shrink([false, false])
                        .show(ui, |ui| {
                            self.show_console_panel(ui);
                            ui.add_space(10.0);
                            self.show_right_evidence_panel(ui);
                        });
                });
        }

        egui::CentralPanel::default().show(ctx, |ui| {
            self.show_main_workbench(ui, compact);
        });
    }
}

fn nav_button(ui: &mut egui::Ui, active: &mut WorkspaceTab, tab: WorkspaceTab, label: &str) {
    let selected = *active == tab;
    if ui.selectable_label(selected, label).clicked() {
        *active = tab;
    }
}

fn status_chip(ui: &mut egui::Ui, key: &str, value: &str) {
    ui.label(
        egui::RichText::new(format!("{key}={value}"))
            .monospace()
            .color(egui::Color32::from_rgb(160, 220, 255)),
    );
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

fn workbench_card(ui: &mut egui::Ui, title: &str, body: &str) {
    ui.group(|ui| {
        ui.heading(title);
        ui.label(body);
    });
}

fn seal_profile_button(
    ui: &mut egui::Ui,
    app: &mut LatticraInstallerApp,
    profile: SealCryptoProfile,
    note: &str,
) {
    ui.group(|ui| {
        ui.heading(profile.label());
        ui.label(note);
        ui.small(profile.detail());
        if app.config.seal.crypto_profile == profile {
            ui.colored_label(egui::Color32::from_rgb(120, 220, 255), "selected");
        } else if ui.button("Use profile").clicked() {
            app.apply_seal_crypto_profile(profile);
        }
    });
}

fn procedure_row(ui: &mut egui::Ui, number: &str, title: &str, body: &str) {
    ui.group(|ui| {
        ui.horizontal_top(|ui| {
            ui.label(
                egui::RichText::new(number)
                    .strong()
                    .color(egui::Color32::from_rgb(120, 220, 255)),
            );
            ui.vertical(|ui| {
                ui.label(egui::RichText::new(title).strong());
                ui.label(body);
            });
        });
    });
}

fn checkbox_note(ui: &mut egui::Ui, value: &mut bool, label: &str, note: &str) {
    ui.checkbox(value, label);
    ui.small(note);
    ui.add_space(4.0);
}

fn labeled_text_field(ui: &mut egui::Ui, label: &str, value: &mut String) {
    if ui.available_width() < 520.0 {
        ui.label(label);
        ui.text_edit_singleline(value);
        return;
    }

    ui.horizontal(|ui| {
        ui.set_min_width(110.0);
        ui.label(label);
        ui.text_edit_singleline(value);
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
