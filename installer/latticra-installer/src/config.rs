use serde::{Deserialize, Serialize};
use std::fmt::Write as _;

#[derive(Clone, Copy, Debug, Deserialize, Serialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub enum InstallProfile {
    DeveloperLocal,
    SealReportOnly,
    FedoraValidationVm,
    Custom,
}

impl Default for InstallProfile {
    fn default() -> Self {
        Self::DeveloperLocal
    }
}

impl InstallProfile {
    pub fn label(self) -> &'static str {
        match self {
            Self::DeveloperLocal => "Guided Workbench",
            Self::SealReportOnly => "Seal Report-Only",
            Self::FedoraValidationVm => "Fedora Validation VM",
            Self::Custom => "Custom",
        }
    }

    pub fn detail(self) -> &'static str {
        match self {
            Self::DeveloperLocal => "Safe first-run profile with Lat, LIR, Seal, docs, and helper commands enabled under dry-run authority.",
            Self::SealReportOnly => "Minimal report-only Seal layout for users who only want receipts, reports, and documentation.",
            Self::FedoraValidationVm => "Fedora/Linux validation workspace for VM testing and host-facing evidence capture.",
            Self::Custom => "Manual operator profile. Use after the guided profiles make sense.",
        }
    }

    pub fn all() -> [InstallProfile; 4] {
        [
            Self::DeveloperLocal,
            Self::SealReportOnly,
            Self::FedoraValidationVm,
            Self::Custom,
        ]
    }
}

#[derive(Clone, Copy, Debug, Deserialize, Serialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub enum SealCryptoProfile {
    ReportOnly,
    Blake2bEd25519,
    XChaCha20Poly1305,
    HybridSeal,
    Custom,
}

impl Default for SealCryptoProfile {
    fn default() -> Self {
        Self::Blake2bEd25519
    }
}

impl SealCryptoProfile {
    pub fn label(self) -> &'static str {
        match self {
            Self::ReportOnly => "Report-only / no key authority",
            Self::Blake2bEd25519 => "BLAKE2b + Ed25519",
            Self::XChaCha20Poly1305 => "XChaCha20-Poly1305",
            Self::HybridSeal => "Hybrid Seal profile",
            Self::Custom => "Custom Seal profile",
        }
    }

    pub fn detail(self) -> &'static str {
        match self {
            Self::ReportOnly => "Metadata-only Seal reports. No signing, encryption, key generation, or key storage is requested.",
            Self::Blake2bEd25519 => "Default evidence-oriented profile for hashing and future signature requests without enabling private-key authority.",
            Self::XChaCha20Poly1305 => "Authenticated-encryption profile for future sealed payload experiments. Kept report-only by default here.",
            Self::HybridSeal => "Combined hash, signature, envelope, and AEAD planning profile for advanced Latticra Seal work.",
            Self::Custom => "Manual profile fields are authoritative. Use only when the operator understands the selected algorithms.",
        }
    }

    pub fn all() -> [SealCryptoProfile; 5] {
        [
            Self::ReportOnly,
            Self::Blake2bEd25519,
            Self::XChaCha20Poly1305,
            Self::HybridSeal,
            Self::Custom,
        ]
    }
}

#[derive(Clone, Debug, Deserialize, Serialize)]
#[serde(default)]
pub struct Components {
    pub lat_tooling: bool,
    pub lir_contracts: bool,
    pub seal_report_only: bool,
    pub nadia_offline_ai: bool,
    pub fedora_validation: bool,
    pub docs_and_examples: bool,
    pub developer_cli_helpers: bool,
}

impl Default for Components {
    fn default() -> Self {
        Self {
            lat_tooling: true,
            lir_contracts: true,
            seal_report_only: true,
            nadia_offline_ai: false,
            fedora_validation: false,
            docs_and_examples: true,
            developer_cli_helpers: true,
        }
    }
}

#[derive(Clone, Debug, Deserialize, Serialize)]
#[serde(default)]
pub struct Safety {
    pub dry_run: bool,
    pub allow_host_mutation: bool,
    pub allow_network_effect: bool,
    pub require_component_manifest: bool,
    pub require_artifact_measurements: bool,
    pub require_verification_policy_metadata: bool,
    pub write_operator_receipt: bool,
}

impl Default for Safety {
    fn default() -> Self {
        Self {
            dry_run: true,
            allow_host_mutation: false,
            allow_network_effect: false,
            require_component_manifest: true,
            require_artifact_measurements: true,
            require_verification_policy_metadata: true,
            write_operator_receipt: true,
        }
    }
}

#[derive(Clone, Debug, Deserialize, Serialize)]
#[serde(default)]
pub struct InstallBehavior {
    pub create_prefix_layout: bool,
    pub create_component_markers: bool,
    pub create_cli_shims: bool,
    pub preserve_existing_files: bool,
    pub build_gui_installer: bool,
    pub build_latticra_from_source: bool,
    pub install_payload_tree: bool,
    pub install_desktop_entry: bool,
    pub install_user_bin_wrappers: bool,
}

impl Default for InstallBehavior {
    fn default() -> Self {
        Self {
            create_prefix_layout: true,
            create_component_markers: true,
            create_cli_shims: true,
            preserve_existing_files: true,
            build_gui_installer: true,
            build_latticra_from_source: true,
            install_payload_tree: true,
            install_desktop_entry: true,
            install_user_bin_wrappers: true,
        }
    }
}

#[derive(Clone, Debug, Deserialize, Serialize)]
#[serde(default)]
pub struct SealConfig {
    pub crypto_profile: SealCryptoProfile,
    pub hash_profile: String,
    pub signature_profile: String,
    pub encryption_profile: String,
    pub envelope_profile: String,
    pub key_storage_profile: String,
    pub report_only: bool,
    pub require_signed_manifest: bool,
    pub write_seal_report: bool,
}

impl Default for SealConfig {
    fn default() -> Self {
        Self {
            crypto_profile: SealCryptoProfile::default(),
            hash_profile: "blake2b-256".to_owned(),
            signature_profile: "ed25519-request-only".to_owned(),
            encryption_profile: "xchacha20-poly1305-planned".to_owned(),
            envelope_profile: "sealed-report-envelope".to_owned(),
            key_storage_profile: "none-report-only".to_owned(),
            report_only: true,
            require_signed_manifest: false,
            write_seal_report: true,
        }
    }
}

impl SealConfig {
    pub fn apply_crypto_profile_defaults(&mut self) {
        match self.crypto_profile {
            SealCryptoProfile::ReportOnly => {
                self.hash_profile = "metadata-digest-only".to_owned();
                self.signature_profile = "none".to_owned();
                self.encryption_profile = "none".to_owned();
                self.envelope_profile = "report-only-envelope".to_owned();
                self.key_storage_profile = "none-report-only".to_owned();
                self.report_only = true;
                self.require_signed_manifest = false;
            }
            SealCryptoProfile::Blake2bEd25519 => {
                self.hash_profile = "blake2b-256".to_owned();
                self.signature_profile = "ed25519-request-only".to_owned();
                self.encryption_profile = "none".to_owned();
                self.envelope_profile = "signed-manifest-ready-envelope".to_owned();
                self.key_storage_profile = "none-report-only".to_owned();
                self.report_only = true;
                self.require_signed_manifest = false;
            }
            SealCryptoProfile::XChaCha20Poly1305 => {
                self.hash_profile = "blake2b-256".to_owned();
                self.signature_profile = "none".to_owned();
                self.encryption_profile = "xchacha20-poly1305-planned".to_owned();
                self.envelope_profile = "sealed-payload-planning-envelope".to_owned();
                self.key_storage_profile = "none-report-only".to_owned();
                self.report_only = true;
                self.require_signed_manifest = false;
            }
            SealCryptoProfile::HybridSeal => {
                self.hash_profile = "blake2b-256".to_owned();
                self.signature_profile = "ed25519-request-only".to_owned();
                self.encryption_profile = "xchacha20-poly1305-planned".to_owned();
                self.envelope_profile = "hybrid-seal-planning-envelope".to_owned();
                self.key_storage_profile = "operator-managed-future".to_owned();
                self.report_only = true;
                self.require_signed_manifest = true;
            }
            SealCryptoProfile::Custom => {}
        }
    }
}

#[derive(Clone, Debug, Deserialize, Serialize)]
#[serde(default)]
pub struct InstallerConfig {
    pub profile: InstallProfile,
    pub install_prefix: String,
    pub components: Components,
    pub safety: Safety,
    pub behavior: InstallBehavior,
    pub seal: SealConfig,
}

impl Default for InstallerConfig {
    fn default() -> Self {
        Self {
            profile: InstallProfile::default(),
            install_prefix: "~/.local/share/latticra".to_owned(),
            components: Components::default(),
            safety: Safety::default(),
            behavior: InstallBehavior::default(),
            seal: SealConfig::default(),
        }
    }
}

impl InstallerConfig {
    pub fn apply_profile_defaults(&mut self) {
        match self.profile {
            InstallProfile::DeveloperLocal => {
                self.install_prefix = "~/.local/share/latticra".to_owned();
                self.components = Components::default();
                self.safety.dry_run = true;
                self.safety.allow_host_mutation = false;
                self.safety.allow_network_effect = false;
                self.seal = SealConfig::default();
            }
            InstallProfile::SealReportOnly => {
                self.install_prefix = "~/.local/share/latticra".to_owned();
                self.components = Components {
                    lat_tooling: false,
                    lir_contracts: true,
                    seal_report_only: true,
                    nadia_offline_ai: false,
                    fedora_validation: false,
                    docs_and_examples: true,
                    developer_cli_helpers: true,
                };
                self.safety.dry_run = true;
                self.safety.allow_host_mutation = false;
                self.safety.allow_network_effect = false;
                self.seal.crypto_profile = SealCryptoProfile::ReportOnly;
                self.seal.apply_crypto_profile_defaults();
            }
            InstallProfile::FedoraValidationVm => {
                self.install_prefix = "~/.local/share/latticra-validation".to_owned();
                self.components = Components {
                    lat_tooling: true,
                    lir_contracts: true,
                    seal_report_only: true,
                    nadia_offline_ai: false,
                    fedora_validation: true,
                    docs_and_examples: true,
                    developer_cli_helpers: true,
                };
                self.safety.dry_run = true;
                self.safety.allow_host_mutation = false;
                self.safety.allow_network_effect = false;
                self.seal.crypto_profile = SealCryptoProfile::Blake2bEd25519;
                self.seal.apply_crypto_profile_defaults();
            }
            InstallProfile::Custom => {}
        }

        self.behavior = InstallBehavior::default();
    }

    pub fn execution_mode_label(&self) -> &'static str {
        if self.safety.dry_run {
            "dry-install"
        } else {
            "local-prefix-install"
        }
    }

    pub fn reset_mode_label(&self) -> &'static str {
        if self.safety.dry_run {
            "dry-reset"
        } else {
            "local-prefix-reset"
        }
    }

    pub fn can_execute(&self) -> Result<(), String> {
        if self.safety.dry_run {
            return Ok(());
        }

        if !self.safety.allow_host_mutation {
            return Err(
                "Real install requires allow_host_mutation=true. Keep dry-run enabled or explicitly authorize a guarded local-prefix install.".to_owned(),
            );
        }

        if self.safety.allow_network_effect {
            return Err(
                "Network authority is not implemented in this installer. Disable allow_network_effect."
                    .to_owned(),
            );
        }

        Ok(())
    }

    pub fn can_reset(&self) -> Result<(), String> {
        if self.safety.allow_network_effect {
            return Err(
                "Network authority is not implemented in this installer. Disable allow_network_effect."
                    .to_owned(),
            );
        }

        if self.safety.dry_run {
            return Ok(());
        }

        if !self.safety.allow_host_mutation {
            return Err(
                "Real reset requires allow_host_mutation=true. Keep dry-run enabled to preview reset or explicitly authorize guarded local-prefix writes.".to_owned(),
            );
        }

        Ok(())
    }
}

pub fn render_plan(config: &InstallerConfig) -> String {
    let mut out = String::new();

    let _ = writeln!(out, "LATTICRA PANEL INSTALL PLAN");
    let _ = writeln!(out);
    let _ = writeln!(out, "profile={}", config.profile.label());
    let _ = writeln!(out, "mode={}", config.execution_mode_label());
    let _ = writeln!(out, "install_prefix={}", config.install_prefix);
    let _ = writeln!(out);
    let _ = writeln!(out, "[authority]");
    let _ = writeln!(out, "production_installer_ready=0");
    let _ = writeln!(
        out,
        "host_install_authority={}",
        u8::from(!config.safety.dry_run && config.safety.allow_host_mutation)
    );
    let _ = writeln!(
        out,
        "network_authority={}",
        u8::from(!config.safety.dry_run && config.safety.allow_network_effect)
    );
    let _ = writeln!(out, "runtime_enforcement_authority=0");
    let _ = writeln!(out);
    let _ = writeln!(out, "[components]");
    let _ = writeln!(out, "lat_tooling={}", config.components.lat_tooling);
    let _ = writeln!(out, "lir_contracts={}", config.components.lir_contracts);
    let _ = writeln!(
        out,
        "seal_report_only={}",
        config.components.seal_report_only
    );
    let _ = writeln!(
        out,
        "nadia_offline_ai={}",
        config.components.nadia_offline_ai
    );
    let _ = writeln!(
        out,
        "fedora_validation={}",
        config.components.fedora_validation
    );
    let _ = writeln!(
        out,
        "docs_and_examples={}",
        config.components.docs_and_examples
    );
    let _ = writeln!(
        out,
        "developer_cli_helpers={}",
        config.components.developer_cli_helpers
    );
    let _ = writeln!(out);
    let _ = writeln!(out, "[nadia]");
    let _ = writeln!(out, "system_name=Latticra Nadia Witness Foundation");
    let _ = writeln!(out, "public_name=Nadia");
    let _ = writeln!(out, "interactive_name=Nadia");
    let _ = writeln!(out, "implementation_name=Nadia Witness Foundation");
    let _ = writeln!(out, "documentation_code_name=Nadia Witness Foundation");
    let _ = writeln!(out, "stage=17-tokenization-boundary-contract");
    let _ = writeln!(
        out,
        "component_selected={}",
        config.components.nadia_offline_ai
    );
    let _ = writeln!(out, "context_engine_stage=1-local-context-engine");
    let _ = writeln!(out, "context_pack_command=scripts/nadia-context-pack.sh");
    let _ = writeln!(
        out,
        "installed_context_pack_command=latticra-nadia context-pack"
    );
    let _ = writeln!(out, "local_file_read_for_indexing=operator_invoked");
    let _ = writeln!(out, "runtime_profile_stage=2-runtime-profile-boundary");
    let _ = writeln!(
        out,
        "runtime_profile_command=scripts/nadia-runtime-profile.sh"
    );
    let _ = writeln!(
        out,
        "installed_runtime_profile_command=latticra-nadia runtime-profile"
    );
    let _ = writeln!(out, "runtime_family=llama.cpp-compatible");
    let _ = writeln!(out, "model_format=gguf");
    let _ = writeln!(
        out,
        "developer_workbench_stage=3-developer-workbench-planning"
    );
    let _ = writeln!(out, "prompt_plan_command=scripts/nadia-prompt-plan.sh");
    let _ = writeln!(
        out,
        "installed_prompt_plan_command=latticra-nadia prompt-plan"
    );
    let _ = writeln!(
        out,
        "systems_engineering_mode_stage=4-systems-engineering-mode-validation"
    );
    let _ = writeln!(
        out,
        "mode_validation_command=scripts/nadia-mode-validate.sh"
    );
    let _ = writeln!(
        out,
        "installed_mode_validation_command=latticra-nadia mode-validate"
    );
    let _ = writeln!(out, "mode_taxonomy_present=1");
    let _ = writeln!(out, "productivity_loop_stage=5-productivity-ledger-loop");
    let _ = writeln!(
        out,
        "productivity_ledger_command=scripts/nadia-productivity-ledger.sh"
    );
    let _ = writeln!(
        out,
        "installed_productivity_ledger_command=latticra-nadia productivity-ledger"
    );
    let _ = writeln!(out, "learning_scope=operator-reviewed-local-productivity");
    let _ = writeln!(out, "ledger_append_only=1");
    let _ = writeln!(out, "protective_safety_stage=6-protective-safety-boundary");
    let _ = writeln!(
        out,
        "protective_safety_command=scripts/nadia-protective-safety-boundary.sh"
    );
    let _ = writeln!(
        out,
        "installed_protective_safety_command=latticra-nadia protective-safety"
    );
    let _ = writeln!(out, "absolute_protective_boundary=1");
    let _ = writeln!(out, "sexual_user_request_authority=0");
    let _ = writeln!(out, "sexual_content_generation=0");
    let _ = writeln!(out, "sexual_roleplay_authority=0");
    let _ = writeln!(out, "sexualized_namesake_or_survivor_content=0");
    let _ = writeln!(out, "sexual_request_refusal=always");
    let _ = writeln!(out, "user_override_authority=0");
    let _ = writeln!(out, "prompt_injection_override_authority=0");
    let _ = writeln!(out, "manipulation_resistance=required");
    let _ = writeln!(out, "policy_bypass_authority=0");
    let _ = writeln!(out, "namesake_cause_awareness=1");
    let _ = writeln!(
        out,
        "tool_authority_stage=7-guarded-tool-authority-preflight"
    );
    let _ = writeln!(
        out,
        "tool_authority_preflight_command=scripts/nadia-tool-authority-preflight.sh"
    );
    let _ = writeln!(
        out,
        "installed_tool_authority_preflight_command=latticra-nadia tool-preflight"
    );
    let _ = writeln!(out, "preflight_decision=report_only_no_execution");
    let _ = writeln!(out, "tool_execution_performed=0");
    let _ = writeln!(out, "tool_selection_authority=0");
    let _ = writeln!(out, "shell_execution_authority=0");
    let _ = writeln!(out, "network_tool_authority=0");
    let _ = writeln!(out, "destructive_action_authority=0");
    let _ = writeln!(out, "credential_access_authority=0");
    let _ = writeln!(out, "requires_operator_approval=1");
    let _ = writeln!(out, "requires_nucleus_gate=1");
    let _ = writeln!(out, "requires_runtime_boundary_gate=1");
    let _ = writeln!(out, "requires_seal_receipt=1");
    let _ = writeln!(out, "requires_protective_safety_boundary=1");
    let _ = writeln!(out, "authority_transition_allowed=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_contract_stage=8-prompt-evaluation-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_contract_command=scripts/nadia-prompt-evaluation-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_contract_command=latticra-nadia prompt-contract"
    );
    let _ = writeln!(out, "prompt_contract_status=contract_only");
    let _ = writeln!(out, "prompt_evaluation_stage=contract-only");
    let _ = writeln!(out, "prompt_materialized=0");
    let _ = writeln!(out, "prompt_text_materialized=0");
    let _ = writeln!(out, "prompt_evaluation_authority=0");
    let _ = writeln!(out, "prompt_receipt_required=1");
    let _ = writeln!(out, "refusal_policy_required=1");
    let _ = writeln!(out, "protective_safety_required=1");
    let _ = writeln!(out, "tool_preflight_required=1");
    let _ = writeln!(out, "runtime_profile_required=1");
    let _ = writeln!(out, "model_registry_review_required=1");
    let _ = writeln!(out, "operator_review_required=1");
    let _ = writeln!(out, "contract_promotion_allowed=0");
    let _ = writeln!(
        out,
        "local_model_registry_contract_stage=9-local-model-registry-contract"
    );
    let _ = writeln!(
        out,
        "model_registry_contract_command=scripts/nadia-local-model-registry-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_model_registry_contract_command=latticra-nadia model-registry"
    );
    let _ = writeln!(out, "local_model_registry_stage=contract-only");
    let _ = writeln!(out, "registry_contract_status=metadata_only");
    let _ = writeln!(out, "model_registry_authority=0");
    let _ = writeln!(out, "requires_prompt_contract=1");
    let _ = writeln!(out, "candidate_review_status=operator_review_required");
    let _ = writeln!(out, "candidate_usable_for_inference=0");
    let _ = writeln!(out, "candidate_selected_for_runtime=0");
    let _ = writeln!(out, "model_selection_authority=0");
    let _ = writeln!(out, "model_install_authority=0");
    let _ = writeln!(out, "model_download_authority=0");
    let _ = writeln!(out, "model_copy_authority=0");
    let _ = writeln!(out, "model_load_authority=0");
    let _ = writeln!(out, "model_benchmark_authority=0");
    let _ = writeln!(out, "model_weight_inspection_authority=0");
    let _ = writeln!(out, "registry_promotion_allowed=0");
    let _ = writeln!(
        out,
        "inference_readiness_contract_stage=10-inference-readiness-contract"
    );
    let _ = writeln!(
        out,
        "inference_readiness_contract_command=scripts/nadia-inference-readiness-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_inference_readiness_contract_command=latticra-nadia inference-readiness"
    );
    let _ = writeln!(out, "inference_readiness_stage=contract-only");
    let _ = writeln!(out, "inference_readiness_contract_status=contract_only");
    let _ = writeln!(out, "inference_readiness_authority=0");
    let _ = writeln!(out, "inference_ready=0");
    let _ = writeln!(out, "readiness_decision=blocked_contract_only");
    let _ = writeln!(out, "readiness_evidence_present=1");
    let _ = writeln!(out, "requires_model_registry_contract=1");
    let _ = writeln!(out, "requires_future_runtime_invocation_contract=1");
    let _ = writeln!(out, "readiness_promotion_allowed=0");
    let _ = writeln!(out, "runtime_invocation_authority=0");
    let _ = writeln!(out, "token_generation_authority=0");
    let _ = writeln!(out, "model_session_authority=0");
    let _ = writeln!(
        out,
        "runtime_invocation_contract_stage=11-runtime-invocation-contract"
    );
    let _ = writeln!(
        out,
        "runtime_invocation_contract_command=scripts/nadia-runtime-invocation-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_runtime_invocation_contract_command=latticra-nadia runtime-invocation"
    );
    let _ = writeln!(out, "runtime_invocation_stage=contract-only");
    let _ = writeln!(out, "runtime_invocation_contract_status=contract_only");
    let _ = writeln!(out, "runtime_invocation_allowed=0");
    let _ = writeln!(out, "invocation_decision=blocked_contract_only");
    let _ = writeln!(out, "invocation_evidence_present=1");
    let _ = writeln!(out, "requires_inference_readiness_contract=1");
    let _ = writeln!(out, "requires_future_model_load_contract=1");
    let _ = writeln!(out, "invocation_promotion_allowed=0");
    let _ = writeln!(out, "runtime_process_spawn_authority=0");
    let _ = writeln!(out, "runtime_binary_execution_authority=0");
    let _ = writeln!(out, "runtime_session_authority=0");
    let _ = writeln!(out, "runtime_process_spawned=0");
    let _ = writeln!(out, "runtime_binary_executed=0");
    let _ = writeln!(out, "runtime_session_created=0");
    let _ = writeln!(out, "token_generation_performed=0");
    let _ = writeln!(out, "model_load_contract_stage=12-model-load-contract");
    let _ = writeln!(
        out,
        "model_load_contract_command=scripts/nadia-model-load-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_model_load_contract_command=latticra-nadia model-load"
    );
    let _ = writeln!(out, "model_load_stage=contract-only");
    let _ = writeln!(out, "model_load_contract_status=contract_only");
    let _ = writeln!(out, "model_load_authority=0");
    let _ = writeln!(out, "model_load_allowed=0");
    let _ = writeln!(out, "model_loaded=0");
    let _ = writeln!(out, "load_decision=blocked_contract_only");
    let _ = writeln!(out, "load_evidence_present=1");
    let _ = writeln!(out, "requires_runtime_invocation_contract=1");
    let _ = writeln!(out, "requires_model_weight_measurement_contract=1");
    let _ = writeln!(out, "requires_future_prompt_receipt_contract=1");
    let _ = writeln!(out, "load_promotion_allowed=0");
    let _ = writeln!(out, "model_file_open_authority=0");
    let _ = writeln!(out, "model_weight_read_authority=0");
    let _ = writeln!(out, "model_weight_mapping_authority=0");
    let _ = writeln!(out, "model_weight_verification_authority=0");
    let _ = writeln!(out, "runtime_model_attach_authority=0");
    let _ = writeln!(out, "model_file_opened=0");
    let _ = writeln!(out, "model_file_descriptor_opened=0");
    let _ = writeln!(out, "model_memory_map_created=0");
    let _ = writeln!(out, "model_weights_mapped=0");
    let _ = writeln!(out, "model_weights_attached=0");
    let _ = writeln!(out, "model_weight_measurement_performed=0");
    let _ = writeln!(out, "model_weight_verification_performed=0");
    let _ = writeln!(out, "model_load_performed=0");
    let _ = writeln!(
        out,
        "prompt_receipt_contract_stage=13-prompt-receipt-contract"
    );
    let _ = writeln!(
        out,
        "prompt_receipt_contract_command=scripts/nadia-prompt-receipt-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_receipt_contract_command=latticra-nadia prompt-receipt"
    );
    let _ = writeln!(out, "prompt_receipt_stage=contract-only");
    let _ = writeln!(out, "prompt_receipt_contract_status=contract_only");
    let _ = writeln!(out, "prompt_receipt_authority=0");
    let _ = writeln!(out, "prompt_receipt_allowed=0");
    let _ = writeln!(out, "prompt_received=0");
    let _ = writeln!(out, "receipt_decision=blocked_contract_only");
    let _ = writeln!(out, "receipt_evidence_present=1");
    let _ = writeln!(out, "requires_model_load_contract=1");
    let _ = writeln!(out, "requires_prompt_source_boundary=1");
    let _ = writeln!(out, "requires_future_prompt_materialization_contract=1");
    let _ = writeln!(out, "prompt_receipt_promotion_allowed=0");
    let _ = writeln!(out, "prompt_source_open_authority=0");
    let _ = writeln!(out, "prompt_source_read_authority=0");
    let _ = writeln!(out, "prompt_text_materialization_authority=0");
    let _ = writeln!(out, "prompt_content_storage_authority=0");
    let _ = writeln!(out, "prompt_hash_authority=0");
    let _ = writeln!(out, "prompt_classification_authority=0");
    let _ = writeln!(out, "prompt_source_opened=0");
    let _ = writeln!(out, "prompt_source_read=0");
    let _ = writeln!(out, "prompt_bytes_read=0");
    let _ = writeln!(out, "prompt_text_received=0");
    let _ = writeln!(out, "prompt_text_materialized=0");
    let _ = writeln!(out, "prompt_content_stored=0");
    let _ = writeln!(out, "prompt_hash_computed=0");
    let _ = writeln!(out, "prompt_classified=0");
    let _ = writeln!(
        out,
        "prompt_materialization_contract_stage=14-prompt-materialization-contract"
    );
    let _ = writeln!(
        out,
        "prompt_materialization_contract_command=scripts/nadia-prompt-materialization-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_materialization_contract_command=latticra-nadia prompt-materialization"
    );
    let _ = writeln!(out, "prompt_materialization_stage=contract-only");
    let _ = writeln!(out, "prompt_materialization_contract_status=contract_only");
    let _ = writeln!(out, "prompt_materialization_authority=0");
    let _ = writeln!(out, "prompt_materialization_allowed=0");
    let _ = writeln!(out, "prompt_materialized=0");
    let _ = writeln!(out, "materialization_decision=blocked_contract_only");
    let _ = writeln!(out, "materialization_evidence_present=1");
    let _ = writeln!(out, "requires_prompt_receipt_contract=1");
    let _ = writeln!(out, "requires_prompt_buffer_boundary=1");
    let _ = writeln!(out, "requires_future_prompt_evaluation_handoff_contract=1");
    let _ = writeln!(out, "prompt_materialization_promotion_allowed=0");
    let _ = writeln!(out, "prompt_buffer_allocation_authority=0");
    let _ = writeln!(out, "prompt_buffer_write_authority=0");
    let _ = writeln!(out, "prompt_tokenization_authority=0");
    let _ = writeln!(out, "prompt_materialization_performed=0");
    let _ = writeln!(out, "prompt_buffer_allocated=0");
    let _ = writeln!(out, "prompt_buffer_written=0");
    let _ = writeln!(out, "prompt_bytes_materialized=0");
    let _ = writeln!(out, "prompt_tokens_created=0");
    let _ = writeln!(out, "prompt_tokenized=0");
    let _ = writeln!(
        out,
        "awareness_dialogue_contract_stage=15-awareness-dialogue-contract"
    );
    let _ = writeln!(
        out,
        "awareness_dialogue_contract_command=scripts/nadia-awareness-dialogue-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_awareness_dialogue_contract_command=latticra-nadia awareness-dialogue"
    );
    let _ = writeln!(out, "future_qa_dialogue_capability_planned=1");
    let _ = writeln!(out, "awareness_dialogue_stage=contract-only");
    let _ = writeln!(out, "awareness_dialogue_contract_status=contract_only");
    let _ = writeln!(out, "awareness_dialogue_authority=0");
    let _ = writeln!(out, "awareness_dialogue_allowed=0");
    let _ = writeln!(out, "dialogue_generation_authority=0");
    let _ = writeln!(out, "dialogue_generation_allowed=0");
    let _ = writeln!(out, "qa_dialogue_generated=0");
    let _ = writeln!(
        out,
        "dialogue_scope=official-nadia-initiative-awareness-work"
    );
    let _ = writeln!(out, "dialogue_format=question-and-answer");
    let _ = writeln!(out, "q_and_a_format_required=1");
    let _ = writeln!(out, "survivor_centered_dialogue_required=1");
    let _ = writeln!(out, "official_source_grounding_required=1");
    let _ = writeln!(out, "live_web_lookup_authority=0");
    let _ = writeln!(out, "topic_yazidi_genocide_awareness=1");
    let _ = writeln!(out, "topic_survivor_voice_and_dignity=1");
    let _ = writeln!(
        out,
        "topic_conflict_related_sexual_violence_awareness_non_graphic=1"
    );
    let _ = writeln!(out, "topic_genocide_prevention=1");
    let _ = writeln!(out, "topic_justice_and_accountability=1");
    let _ = writeln!(out, "topic_sinjar_reconstruction=1");
    let _ = writeln!(out, "topic_womens_empowerment=1");
    let _ = writeln!(out, "sexualized_dialogue_generation=0");
    let _ = writeln!(out, "graphic_sexual_detail_allowed=0");
    let _ = writeln!(out, "victim_blaming_allowed=0");
    let _ = writeln!(out, "genocide_denial_allowed=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_handoff_contract_stage=16-prompt-evaluation-handoff-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_handoff_contract_command=scripts/nadia-prompt-evaluation-handoff-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_handoff_contract_command=latticra-nadia prompt-evaluation-handoff"
    );
    let _ = writeln!(out, "prompt_evaluation_handoff_stage=contract-only");
    let _ = writeln!(
        out,
        "prompt_evaluation_handoff_contract_status=contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_handoff_authority=0");
    let _ = writeln!(out, "prompt_evaluation_handoff_allowed=0");
    let _ = writeln!(out, "prompt_evaluation_handoff_performed=0");
    let _ = writeln!(out, "evaluation_handoff_decision=blocked_contract_only");
    let _ = writeln!(out, "requires_awareness_dialogue_contract=1");
    let _ = writeln!(out, "requires_future_tokenization_contract=1");
    let _ = writeln!(out, "prompt_evaluation_handoff_promotion_allowed=0");
    let _ = writeln!(
        out,
        "tokenization_boundary_contract_stage=17-tokenization-boundary-contract"
    );
    let _ = writeln!(
        out,
        "tokenization_boundary_contract_command=scripts/nadia-tokenization-boundary-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_tokenization_boundary_contract_command=latticra-nadia tokenization-boundary"
    );
    let _ = writeln!(out, "tokenization_boundary_stage=contract-only");
    let _ = writeln!(out, "tokenization_boundary_contract_status=contract_only");
    let _ = writeln!(out, "tokenization_boundary_authority=0");
    let _ = writeln!(out, "tokenization_boundary_allowed=0");
    let _ = writeln!(out, "tokenization_boundary_performed=0");
    let _ = writeln!(out, "prompt_tokenization_allowed=0");
    let _ = writeln!(out, "prompt_tokenized=0");
    let _ = writeln!(out, "prompt_tokens_created=0");
    let _ = writeln!(out, "tokenizer_file_opened=0");
    let _ = writeln!(out, "tokenizer_vocab_loaded=0");
    let _ = writeln!(out, "tokenization_decision=blocked_contract_only");
    let _ = writeln!(out, "requires_prompt_evaluation_handoff_contract=1");
    let _ = writeln!(out, "requires_future_tokenizer_specification_contract=1");
    let _ = writeln!(out, "tokenization_boundary_promotion_allowed=0");
    let _ = writeln!(out, "requires_context_pack=1");
    let _ = writeln!(out, "requires_runtime_profile=1");
    let _ = writeln!(out, "human_dignity_principle=1");
    let _ = writeln!(out, "survivor_witness_respect=1");
    let _ = writeln!(out, "community_awareness_posture=1");
    let _ = writeln!(out, "harm_aware_development=1");
    let _ = writeln!(out, "model_runtime_present=0");
    let _ = writeln!(out, "model_runtime_invoked=0");
    let _ = writeln!(out, "inference_performed=0");
    let _ = writeln!(out, "inference_authority=0");
    let _ = writeln!(out, "runtime_invoked=0");
    let _ = writeln!(out, "prompt_evaluated=0");
    let _ = writeln!(out, "model_weights_installed=0");
    let _ = writeln!(out, "model_weights_loaded=0");
    let _ = writeln!(out, "model_weights_copied=0");
    let _ = writeln!(out, "model_weights_downloaded=0");
    let _ = writeln!(out, "model_weights_inspected=0");
    let _ = writeln!(out, "tool_execution_authority=0");
    let _ = writeln!(out, "source_mutation_authority=0");
    let _ = writeln!(out);
    let _ = writeln!(out, "[seal]");
    let _ = writeln!(out, "crypto_profile={}", config.seal.crypto_profile.label());
    let _ = writeln!(out, "hash_profile={}", config.seal.hash_profile);
    let _ = writeln!(out, "signature_profile={}", config.seal.signature_profile);
    let _ = writeln!(out, "encryption_profile={}", config.seal.encryption_profile);
    let _ = writeln!(out, "envelope_profile={}", config.seal.envelope_profile);
    let _ = writeln!(
        out,
        "key_storage_profile={}",
        config.seal.key_storage_profile
    );
    let _ = writeln!(out, "report_only={}", config.seal.report_only);
    let _ = writeln!(
        out,
        "require_signed_manifest={}",
        config.seal.require_signed_manifest
    );
    let _ = writeln!(out, "write_seal_report={}", config.seal.write_seal_report);
    let _ = writeln!(out);
    let _ = writeln!(out, "[safety]");
    let _ = writeln!(out, "dry_run={}", config.safety.dry_run);
    let _ = writeln!(
        out,
        "would_mutate_host={}",
        u8::from(!config.safety.dry_run && config.safety.allow_host_mutation)
    );
    let _ = writeln!(
        out,
        "would_use_network={}",
        u8::from(!config.safety.dry_run && config.safety.allow_network_effect)
    );
    let _ = writeln!(
        out,
        "require_component_manifest={}",
        config.safety.require_component_manifest
    );
    let _ = writeln!(
        out,
        "require_artifact_measurements={}",
        config.safety.require_artifact_measurements
    );
    let _ = writeln!(
        out,
        "require_verification_policy_metadata={}",
        config.safety.require_verification_policy_metadata
    );
    let _ = writeln!(
        out,
        "write_operator_receipt={}",
        config.safety.write_operator_receipt
    );
    let _ = writeln!(out);
    let _ = writeln!(out, "[behavior]");
    let _ = writeln!(
        out,
        "create_prefix_layout={}",
        config.behavior.create_prefix_layout
    );
    let _ = writeln!(
        out,
        "create_component_markers={}",
        config.behavior.create_component_markers
    );
    let _ = writeln!(out, "create_cli_shims={}", config.behavior.create_cli_shims);
    let _ = writeln!(
        out,
        "preserve_existing_files={}",
        config.behavior.preserve_existing_files
    );
    let _ = writeln!(
        out,
        "build_gui_installer={}",
        config.behavior.build_gui_installer
    );
    let _ = writeln!(
        out,
        "build_latticra_from_source={}",
        config.behavior.build_latticra_from_source
    );
    let _ = writeln!(
        out,
        "install_payload_tree={}",
        config.behavior.install_payload_tree
    );
    let _ = writeln!(
        out,
        "install_desktop_entry={}",
        config.behavior.install_desktop_entry
    );
    let _ = writeln!(
        out,
        "install_user_bin_wrappers={}",
        config.behavior.install_user_bin_wrappers
    );
    let _ = writeln!(out);
    let _ = writeln!(out, "[next_action]");
    if config.safety.dry_run {
        let _ = writeln!(out, "result=execute-dry-install");
        let _ = writeln!(
            out,
            "message=Run Dry-Install to validate and write a dry-install receipt."
        );
    } else if config.safety.allow_host_mutation {
        let _ = writeln!(out, "result=execute-local-prefix-install");
        let _ = writeln!(
            out,
            "message=Run Install to write the guarded user-local prefix layout."
        );
    } else {
        let _ = writeln!(out, "result=blocked");
        let _ = writeln!(
            out,
            "message=Real install is blocked until allow_host_mutation is enabled."
        );
    }

    out
}
