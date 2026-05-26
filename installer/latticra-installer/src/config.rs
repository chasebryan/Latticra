use serde::{Deserialize, Serialize};
use std::fmt::Write as _;
use std::path::{Component, Path, PathBuf};

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

#[derive(Clone, Copy, Debug, Deserialize, Serialize, PartialEq, Eq)]
#[serde(rename_all = "snake_case")]
pub enum LatticraConsoleProfile {
    HostedReference,
    PanelEmbedded,
    HostEmbeddedPlanning,
    OsBasePlanning,
    Custom,
}

impl Default for LatticraConsoleProfile {
    fn default() -> Self {
        Self::PanelEmbedded
    }
}

impl LatticraConsoleProfile {
    pub fn key(self) -> &'static str {
        match self {
            Self::HostedReference => "hosted_reference",
            Self::PanelEmbedded => "panel_embedded",
            Self::HostEmbeddedPlanning => "host_embedded_planning",
            Self::OsBasePlanning => "os_base_planning",
            Self::Custom => "custom",
        }
    }

    pub fn label(self) -> &'static str {
        match self {
            Self::HostedReference => "Hosted Reference",
            Self::PanelEmbedded => "Panel Embedded",
            Self::HostEmbeddedPlanning => "Host-Embedded Planning",
            Self::OsBasePlanning => "OS-Base Planning",
            Self::Custom => "Custom LC",
        }
    }

    pub fn detail(self) -> &'static str {
        match self {
            Self::HostedReference => "Reference LC metadata installed beside the Panel without claiming embedded host behavior.",
            Self::PanelEmbedded => "Default Panel-installed LC profile for operator console workflows and substrate inspection.",
            Self::HostEmbeddedPlanning => "Planning profile for future host embedding while retaining zero host mutation authority.",
            Self::OsBasePlanning => "Planning profile for the eventual LC OS-base lane without boot, kernel, or runtime enforcement authority.",
            Self::Custom => "Manual LC profile fields are authoritative while the authority floor remains no-effect.",
        }
    }

    pub fn all() -> [LatticraConsoleProfile; 5] {
        [
            Self::HostedReference,
            Self::PanelEmbedded,
            Self::HostEmbeddedPlanning,
            Self::OsBasePlanning,
            Self::Custom,
        ]
    }
}

#[derive(Clone, Debug, Deserialize, Serialize)]
#[serde(default)]
pub struct Components {
    pub latticra_console: bool,
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
            latticra_console: true,
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
pub struct LatticraConsoleInstallConfig {
    pub install_profile: String,
    pub install_mode: String,
    pub config_path: String,
    pub share_path: String,
    pub command_wrapper: String,
    pub panel_embedded_console: bool,
    pub write_config_file: bool,
    pub write_profile_presets: bool,
    pub write_command_registry: bool,
    pub write_contract_files: bool,
    pub install_user_wrapper: bool,
    pub allow_external_host_commands: bool,
}

impl Default for LatticraConsoleInstallConfig {
    fn default() -> Self {
        Self {
            install_profile: "lc-panel-install-v0".to_owned(),
            install_mode: "metadata-only-console-foundation".to_owned(),
            config_path: "etc/latticra/lc.toml".to_owned(),
            share_path: "share/latticra/lc".to_owned(),
            command_wrapper: "latticra-lc".to_owned(),
            panel_embedded_console: true,
            write_config_file: true,
            write_profile_presets: true,
            write_command_registry: true,
            write_contract_files: true,
            install_user_wrapper: true,
            allow_external_host_commands: false,
        }
    }
}

impl LatticraConsoleInstallConfig {
    pub fn validate(&self) -> Result<(), String> {
        validate_nonempty_field("LC install profile", &self.install_profile)?;
        validate_nonempty_field("LC install mode", &self.install_mode)?;
        validate_relative_install_path("LC config path", &self.config_path)?;
        validate_relative_install_path("LC share path", &self.share_path)?;
        validate_command_wrapper(&self.command_wrapper)?;

        if self.allow_external_host_commands {
            return Err(
                "LC install configuration cannot enable external host commands from the Panel."
                    .to_owned(),
            );
        }

        Ok(())
    }
}

#[derive(Clone, Debug, Deserialize, Serialize)]
#[serde(default)]
pub struct LatticraConsoleConfig {
    pub profile: LatticraConsoleProfile,
    pub install: LatticraConsoleInstallConfig,
    pub command_registry_profile: String,
    pub substrate_bridge_profile: String,
    pub host_embedding_profile: String,
    pub host_embedding_contract_profile: String,
    pub host_inventory_contract_profile: String,
    pub host_adapter_contract_profile: String,
    pub receipt_request_contract_profile: String,
    pub receipt_payload_schema_profile: String,
    pub receipt_payload_artifact_draft_profile: String,
    pub receipt_payload_artifact_review_profile: String,
    pub receipt_payload_artifact_review_receipt_profile: String,
    pub receipt_payload_artifact_review_receipt_draft_profile: String,
    pub receipt_payload_materialization_plan_profile: String,
    pub signature_request_binding_profile: String,
    pub receipt_contract_profile: String,
    pub os_base_contract_profile: String,
    pub vm_evidence_contract_profile: String,
    pub os_base_profile: String,
    pub panel_bridge: String,
    pub report_only: bool,
    pub require_host_embedding_contract: bool,
    pub require_read_only_host_inventory_contract: bool,
    pub require_profile_receipt: bool,
    pub require_host_contract_receipt: bool,
    pub require_host_inventory_receipt: bool,
    pub require_host_adapter_contract: bool,
    pub require_receipt_request_contract: bool,
    pub require_receipt_payload_schema: bool,
    pub require_receipt_payload_artifact_draft: bool,
    pub require_receipt_payload_artifact_review: bool,
    pub require_receipt_payload_artifact_review_receipt: bool,
    pub require_receipt_payload_artifact_review_receipt_draft: bool,
    pub require_receipt_payload_materialization_plan: bool,
    pub require_signature_request_binding: bool,
    pub require_os_base_contract: bool,
    pub require_vm_evidence_contract: bool,
    pub require_runtime_boundary_binding: bool,
    pub require_seal_capability_labels: bool,
}

impl Default for LatticraConsoleConfig {
    fn default() -> Self {
        let mut config = Self {
            profile: LatticraConsoleProfile::default(),
            install: LatticraConsoleInstallConfig::default(),
            command_registry_profile: "c-static-table".to_owned(),
            substrate_bridge_profile: "metadata-bound".to_owned(),
            host_embedding_profile: "panel-contained".to_owned(),
            host_embedding_contract_profile: "lc-host-embedding-v0".to_owned(),
            host_inventory_contract_profile: "lc-host-inventory-v0".to_owned(),
            host_adapter_contract_profile: "lc-host-adapter-v0".to_owned(),
            receipt_request_contract_profile: "lc-receipt-request-v0".to_owned(),
            receipt_payload_schema_profile: "lc-receipt-payload-schema-v0".to_owned(),
            receipt_payload_artifact_draft_profile: "lc-receipt-payload-artifact-draft-v0"
                .to_owned(),
            receipt_payload_artifact_review_profile: "lc-receipt-payload-artifact-review-v0"
                .to_owned(),
            receipt_payload_artifact_review_receipt_profile:
                "lc-receipt-payload-artifact-review-receipt-v0".to_owned(),
            receipt_payload_artifact_review_receipt_draft_profile:
                "lc-receipt-payload-artifact-review-receipt-draft-v0".to_owned(),
            receipt_payload_materialization_plan_profile:
                "lc-receipt-payload-materialization-plan-v0".to_owned(),
            signature_request_binding_profile: "lc-signature-request-binding-v0".to_owned(),
            receipt_contract_profile: "lc-receipts-v0".to_owned(),
            os_base_contract_profile: "lc-os-base-v0".to_owned(),
            vm_evidence_contract_profile: "lc-vm-evidence-v0".to_owned(),
            os_base_profile: "planned-no-boot-authority".to_owned(),
            panel_bridge: "panel-aware".to_owned(),
            report_only: true,
            require_host_embedding_contract: true,
            require_read_only_host_inventory_contract: true,
            require_profile_receipt: true,
            require_host_contract_receipt: true,
            require_host_inventory_receipt: true,
            require_host_adapter_contract: true,
            require_receipt_request_contract: true,
            require_receipt_payload_schema: true,
            require_receipt_payload_artifact_draft: true,
            require_receipt_payload_artifact_review: true,
            require_receipt_payload_artifact_review_receipt: true,
            require_receipt_payload_artifact_review_receipt_draft: true,
            require_receipt_payload_materialization_plan: true,
            require_signature_request_binding: true,
            require_os_base_contract: true,
            require_vm_evidence_contract: true,
            require_runtime_boundary_binding: true,
            require_seal_capability_labels: true,
        };
        config.apply_profile_defaults();
        config
    }
}

impl LatticraConsoleConfig {
    pub fn apply_profile_defaults(&mut self) {
        match self.profile {
            LatticraConsoleProfile::HostedReference => {
                self.panel_bridge = "hosted-reference".to_owned();
                self.host_embedding_profile = "not-embedded".to_owned();
                self.os_base_profile = "planned-no-boot-authority".to_owned();
            }
            LatticraConsoleProfile::PanelEmbedded => {
                self.panel_bridge = "panel-aware".to_owned();
                self.host_embedding_profile = "panel-contained".to_owned();
                self.os_base_profile = "planned-no-boot-authority".to_owned();
            }
            LatticraConsoleProfile::HostEmbeddedPlanning => {
                self.panel_bridge = "panel-aware".to_owned();
                self.host_embedding_profile = "host-embedded-planning".to_owned();
                self.os_base_profile = "planned-no-boot-authority".to_owned();
            }
            LatticraConsoleProfile::OsBasePlanning => {
                self.panel_bridge = "panel-aware".to_owned();
                self.host_embedding_profile = "host-embedded-planning".to_owned();
                self.os_base_profile = "os-base-planning-no-boot-authority".to_owned();
            }
            LatticraConsoleProfile::Custom => {}
        }

        self.command_registry_profile = "c-static-table".to_owned();
        self.substrate_bridge_profile = "metadata-bound".to_owned();
        self.host_embedding_contract_profile = "lc-host-embedding-v0".to_owned();
        self.host_inventory_contract_profile = "lc-host-inventory-v0".to_owned();
        self.host_adapter_contract_profile = "lc-host-adapter-v0".to_owned();
        self.receipt_request_contract_profile = "lc-receipt-request-v0".to_owned();
        self.receipt_payload_schema_profile = "lc-receipt-payload-schema-v0".to_owned();
        self.receipt_payload_artifact_draft_profile =
            "lc-receipt-payload-artifact-draft-v0".to_owned();
        self.receipt_payload_artifact_review_profile =
            "lc-receipt-payload-artifact-review-v0".to_owned();
        self.receipt_payload_artifact_review_receipt_profile =
            "lc-receipt-payload-artifact-review-receipt-v0".to_owned();
        self.receipt_payload_artifact_review_receipt_draft_profile =
            "lc-receipt-payload-artifact-review-receipt-draft-v0".to_owned();
        self.receipt_payload_materialization_plan_profile =
            "lc-receipt-payload-materialization-plan-v0".to_owned();
        self.signature_request_binding_profile = "lc-signature-request-binding-v0".to_owned();
        self.receipt_contract_profile = "lc-receipts-v0".to_owned();
        self.os_base_contract_profile = "lc-os-base-v0".to_owned();
        self.vm_evidence_contract_profile = "lc-vm-evidence-v0".to_owned();
        self.report_only = true;
        self.require_host_embedding_contract = true;
        self.require_read_only_host_inventory_contract = true;
        self.require_profile_receipt = true;
        self.require_host_contract_receipt = true;
        self.require_host_inventory_receipt = true;
        self.require_host_adapter_contract = true;
        self.require_receipt_request_contract = true;
        self.require_receipt_payload_schema = true;
        self.require_receipt_payload_artifact_draft = true;
        self.require_receipt_payload_artifact_review = true;
        self.require_receipt_payload_artifact_review_receipt = true;
        self.require_receipt_payload_artifact_review_receipt_draft = true;
        self.require_receipt_payload_materialization_plan = true;
        self.require_signature_request_binding = true;
        self.require_os_base_contract = true;
        self.require_vm_evidence_contract = true;
        self.require_runtime_boundary_binding = true;
        self.require_seal_capability_labels = true;
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
pub struct UpdaterConfig {
    pub source_strategy: String,
    pub update_channel: String,
    pub allow_network_fetch: bool,
    pub require_dry_run_before_apply: bool,
    pub reuse_installer_engine: bool,
    pub write_update_receipt: bool,
}

impl Default for UpdaterConfig {
    fn default() -> Self {
        Self {
            source_strategy: "current-source-checkout".to_owned(),
            update_channel: "local-checkout".to_owned(),
            allow_network_fetch: false,
            require_dry_run_before_apply: true,
            reuse_installer_engine: true,
            write_update_receipt: true,
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
    pub lc: LatticraConsoleConfig,
    pub safety: Safety,
    pub behavior: InstallBehavior,
    pub updater: UpdaterConfig,
    pub seal: SealConfig,
}

impl Default for InstallerConfig {
    fn default() -> Self {
        Self {
            profile: InstallProfile::default(),
            install_prefix: "~/.local/share/latticra".to_owned(),
            components: Components::default(),
            lc: LatticraConsoleConfig::default(),
            safety: Safety::default(),
            behavior: InstallBehavior::default(),
            updater: UpdaterConfig::default(),
            seal: SealConfig::default(),
        }
    }
}

fn expand_install_prefix(raw_prefix: &str, home: &Path) -> PathBuf {
    if raw_prefix == "~" {
        return home.to_path_buf();
    }

    if let Some(rest) = raw_prefix.strip_prefix("~/") {
        return home.join(rest);
    }

    PathBuf::from(raw_prefix)
}

fn path_has_parent_reference(path: &Path) -> bool {
    path.components()
        .any(|component| matches!(component, Component::ParentDir))
}

fn validate_nonempty_field(label: &str, value: &str) -> Result<(), String> {
    if value.trim().is_empty() {
        return Err(format!("{label} must not be empty."));
    }

    Ok(())
}

fn validate_relative_install_path(label: &str, raw_path: &str) -> Result<(), String> {
    validate_nonempty_field(label, raw_path)?;

    let path = Path::new(raw_path);
    if path.is_absolute() {
        return Err(format!(
            "{label} must be a relative path under the install prefix."
        ));
    }

    if path_has_parent_reference(path) {
        return Err(format!(
            "{label} must not contain parent-directory traversal."
        ));
    }

    Ok(())
}

fn validate_command_wrapper(command: &str) -> Result<(), String> {
    validate_nonempty_field("LC command wrapper", command)?;

    if command.contains('/')
        || command.split_whitespace().count() != 1
        || !command
            .chars()
            .all(|ch| ch.is_ascii_alphanumeric() || matches!(ch, '.' | '_' | '-'))
    {
        return Err(
            "LC command wrapper must be a single command name. Use only letters, numbers, '.', '_', or '-'."
                .to_owned(),
        );
    }

    Ok(())
}

fn validate_user_local_install_prefix(raw_prefix: &str) -> Result<(), String> {
    if raw_prefix.trim().is_empty() {
        return Err("Install prefix must not be empty.".to_owned());
    }

    let home = std::env::var("HOME")
        .map(PathBuf::from)
        .map_err(|_| "HOME must be set before validating the install prefix.".to_owned())?;
    let prefix = expand_install_prefix(raw_prefix, &home);

    if !prefix.is_absolute() {
        return Err("Install prefix must resolve to an absolute path.".to_owned());
    }

    if path_has_parent_reference(&prefix) {
        return Err("Install prefix must not contain parent-directory traversal.".to_owned());
    }

    if std::fs::symlink_metadata(&prefix)
        .map(|metadata| metadata.file_type().is_symlink())
        .unwrap_or(false)
    {
        return Err("Install prefix must not be a symlink.".to_owned());
    }

    let latticra_prefix = home.join(".local/share/latticra");
    let validation_prefix = home.join(".local/share/latticra-validation");
    if prefix == latticra_prefix
        || prefix.starts_with(&latticra_prefix)
        || prefix == validation_prefix
        || prefix.starts_with(&validation_prefix)
    {
        return Ok(());
    }

    Err(format!(
        "Installer only allows user-local prefixes under {}/.local/share/latticra*.",
        home.display()
    ))
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
                self.lc = LatticraConsoleConfig::default();
                self.seal = SealConfig::default();
            }
            InstallProfile::SealReportOnly => {
                self.install_prefix = "~/.local/share/latticra".to_owned();
                self.components = Components {
                    latticra_console: true,
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
                self.lc = LatticraConsoleConfig::default();
                self.seal.crypto_profile = SealCryptoProfile::ReportOnly;
                self.seal.apply_crypto_profile_defaults();
            }
            InstallProfile::FedoraValidationVm => {
                self.install_prefix = "~/.local/share/latticra-validation".to_owned();
                self.components = Components {
                    latticra_console: true,
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
                self.lc = LatticraConsoleConfig::default();
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

    pub fn can_execute(&self) -> Result<(), String> {
        validate_user_local_install_prefix(&self.install_prefix)?;
        self.lc.install.validate()?;

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

        if self.updater.allow_network_fetch {
            return Err(
                "Updater network fetch is not implemented in this installer. Use a reviewed local checkout and keep allow_network_fetch=false."
                    .to_owned(),
            );
        }

        Ok(())
    }

    pub fn can_reset(&self) -> Result<(), String> {
        validate_user_local_install_prefix(&self.install_prefix)?;
        self.lc.install.validate()?;

        if self.safety.allow_network_effect {
            return Err(
                "Network authority is not implemented in this installer. Disable allow_network_effect."
                    .to_owned(),
            );
        }

        if self.updater.allow_network_fetch {
            return Err(
                "Updater network fetch is not implemented in this installer. Use a reviewed local checkout and keep allow_network_fetch=false."
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
    let _ = writeln!(out, "[updater]");
    let _ = writeln!(out, "panel_owned=1");
    let _ = writeln!(out, "source_strategy={}", config.updater.source_strategy);
    let _ = writeln!(out, "update_channel={}", config.updater.update_channel);
    let _ = writeln!(
        out,
        "allow_network_fetch={}",
        config.updater.allow_network_fetch
    );
    let _ = writeln!(
        out,
        "require_dry_run_before_apply={}",
        config.updater.require_dry_run_before_apply
    );
    let _ = writeln!(
        out,
        "reuse_installer_engine={}",
        config.updater.reuse_installer_engine
    );
    let _ = writeln!(
        out,
        "write_update_receipt={}",
        config.updater.write_update_receipt
    );
    let _ = writeln!(out, "network_authority=0");
    let _ = writeln!(out, "root_authority=0");
    let _ = writeln!(out, "system_mutation_authority=0");
    let _ = writeln!(out, "update_apply_mode=guarded-local-prefix-reinstall");
    let _ = writeln!(out);
    let _ = writeln!(out, "[components]");
    let _ = writeln!(
        out,
        "latticra_console={}",
        config.components.latticra_console
    );
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
    let _ = writeln!(out, "[lc]");
    let _ = writeln!(out, "component_key=latticra_console");
    let _ = writeln!(out, "console_name=Latticra Console");
    let _ = writeln!(out, "short_name=LC");
    let _ = writeln!(
        out,
        "component_selected={}",
        config.components.latticra_console
    );
    let _ = writeln!(out, "configurable=1");
    let _ = writeln!(out, "panel_installable=1");
    let _ = writeln!(out, "install_profile={}", config.lc.install.install_profile);
    let _ = writeln!(out, "install_mode={}", config.lc.install.install_mode);
    let _ = writeln!(out, "install_config_path={}", config.lc.install.config_path);
    let _ = writeln!(out, "install_share_path={}", config.lc.install.share_path);
    let _ = writeln!(
        out,
        "install_command_wrapper={}",
        config.lc.install.command_wrapper
    );
    let _ = writeln!(
        out,
        "panel_embedded_console={}",
        config.lc.install.panel_embedded_console
    );
    let _ = writeln!(
        out,
        "write_config_file={}",
        config.lc.install.write_config_file
    );
    let _ = writeln!(
        out,
        "write_profile_presets={}",
        config.lc.install.write_profile_presets
    );
    let _ = writeln!(
        out,
        "write_command_registry={}",
        config.lc.install.write_command_registry
    );
    let _ = writeln!(
        out,
        "write_contract_files={}",
        config.lc.install.write_contract_files
    );
    let _ = writeln!(
        out,
        "install_user_wrapper={}",
        config.lc.install.install_user_wrapper
    );
    let _ = writeln!(
        out,
        "allow_external_host_commands={}",
        config.lc.install.allow_external_host_commands
    );
    let _ = writeln!(out, "profile={}", config.lc.profile.key());
    let _ = writeln!(out, "profile_label={}", config.lc.profile.label());
    let _ = writeln!(out, "panel_console_bridge={}", config.lc.panel_bridge);
    let _ = writeln!(
        out,
        "command_registry_profile={}",
        config.lc.command_registry_profile
    );
    let _ = writeln!(
        out,
        "substrate_bridge_profile={}",
        config.lc.substrate_bridge_profile
    );
    let _ = writeln!(
        out,
        "host_embedding_profile={}",
        config.lc.host_embedding_profile
    );
    let _ = writeln!(
        out,
        "host_embedding_contract_profile={}",
        config.lc.host_embedding_contract_profile
    );
    let _ = writeln!(
        out,
        "host_inventory_contract_profile={}",
        config.lc.host_inventory_contract_profile
    );
    let _ = writeln!(
        out,
        "host_adapter_contract_profile={}",
        config.lc.host_adapter_contract_profile
    );
    let _ = writeln!(
        out,
        "receipt_request_contract_profile={}",
        config.lc.receipt_request_contract_profile
    );
    let _ = writeln!(
        out,
        "receipt_payload_schema_profile={}",
        config.lc.receipt_payload_schema_profile
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_draft_profile={}",
        config.lc.receipt_payload_artifact_draft_profile
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_review_profile={}",
        config.lc.receipt_payload_artifact_review_profile
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_review_receipt_profile={}",
        config.lc.receipt_payload_artifact_review_receipt_profile
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_review_receipt_draft_profile={}",
        config
            .lc
            .receipt_payload_artifact_review_receipt_draft_profile
    );
    let _ = writeln!(
        out,
        "receipt_payload_materialization_plan_profile={}",
        config.lc.receipt_payload_materialization_plan_profile
    );
    let _ = writeln!(
        out,
        "signature_request_binding_profile={}",
        config.lc.signature_request_binding_profile
    );
    let _ = writeln!(
        out,
        "receipt_contract_profile={}",
        config.lc.receipt_contract_profile
    );
    let _ = writeln!(
        out,
        "os_base_contract_profile={}",
        config.lc.os_base_contract_profile
    );
    let _ = writeln!(
        out,
        "vm_evidence_contract_profile={}",
        config.lc.vm_evidence_contract_profile
    );
    let _ = writeln!(out, "os_base_profile={}", config.lc.os_base_profile);
    let _ = writeln!(out, "report_only={}", config.lc.report_only);
    let _ = writeln!(
        out,
        "host_embedding_contract_required={}",
        config.lc.require_host_embedding_contract
    );
    let _ = writeln!(
        out,
        "read_only_host_inventory_contract_required={}",
        config.lc.require_read_only_host_inventory_contract
    );
    let _ = writeln!(
        out,
        "profile_receipt_required={}",
        config.lc.require_profile_receipt
    );
    let _ = writeln!(
        out,
        "host_contract_receipt_required={}",
        config.lc.require_host_contract_receipt
    );
    let _ = writeln!(
        out,
        "host_inventory_receipt_required={}",
        config.lc.require_host_inventory_receipt
    );
    let _ = writeln!(
        out,
        "host_adapter_contract_required={}",
        config.lc.require_host_adapter_contract
    );
    let _ = writeln!(
        out,
        "receipt_request_contract_required={}",
        config.lc.require_receipt_request_contract
    );
    let _ = writeln!(
        out,
        "receipt_payload_schema_required={}",
        config.lc.require_receipt_payload_schema
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_draft_required={}",
        config.lc.require_receipt_payload_artifact_draft
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_review_required={}",
        config.lc.require_receipt_payload_artifact_review
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_review_receipt_required={}",
        config.lc.require_receipt_payload_artifact_review_receipt
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_review_receipt_draft_required={}",
        config
            .lc
            .require_receipt_payload_artifact_review_receipt_draft
    );
    let _ = writeln!(
        out,
        "receipt_payload_materialization_plan_required={}",
        config.lc.require_receipt_payload_materialization_plan
    );
    let _ = writeln!(
        out,
        "signature_request_binding_required={}",
        config.lc.require_signature_request_binding
    );
    let _ = writeln!(
        out,
        "os_base_contract_required={}",
        config.lc.require_os_base_contract
    );
    let _ = writeln!(
        out,
        "vm_evidence_contract_required={}",
        config.lc.require_vm_evidence_contract
    );
    let _ = writeln!(
        out,
        "runtime_boundary_binding_required={}",
        config.lc.require_runtime_boundary_binding
    );
    let _ = writeln!(
        out,
        "seal_capability_labels_required={}",
        config.lc.require_seal_capability_labels
    );
    let _ = writeln!(out, "command_registry_status=seed-registry");
    let _ = writeln!(
        out,
        "substrate_bridge_status={}",
        config.lc.substrate_bridge_profile
    );
    let _ = writeln!(
        out,
        "host_embedding_status={}",
        config.lc.host_embedding_profile
    );
    let _ = writeln!(out, "host_embedding_contract_status=metadata-only-contract");
    let _ = writeln!(out, "host_inventory_contract_status=metadata-only-contract");
    let _ = writeln!(out, "host_adapter_contract_status=metadata-only-contract");
    let _ = writeln!(
        out,
        "receipt_request_contract_status=metadata-only-contract"
    );
    let _ = writeln!(out, "receipt_payload_schema_status=metadata-only-schema");
    let _ = writeln!(
        out,
        "receipt_payload_artifact_draft_status=metadata-only-draft"
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_review_status=metadata-only-review-gate"
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_review_receipt_status=metadata-only-receipt-contract"
    );
    let _ = writeln!(
        out,
        "receipt_payload_artifact_review_receipt_draft_status=metadata-only-review-receipt-draft"
    );
    let _ = writeln!(
        out,
        "receipt_payload_materialization_plan_status=metadata-only-plan"
    );
    let _ = writeln!(out, "materialization_preconditions_met=0");
    let _ = writeln!(out, "draft_review_receipt_present=0");
    let _ = writeln!(out, "draft_review_receipt_artifact_present=0");
    let _ = writeln!(out, "materialization_allowed=0");
    let _ = writeln!(out, "payload_artifact_present=0");
    let _ = writeln!(out, "payload_materialized=0");
    let _ = writeln!(out, "payload_write_allowed=0");
    let _ = writeln!(
        out,
        "signature_request_binding_status=metadata-only-contract"
    );
    let _ = writeln!(out, "receipt_contract_status=metadata-only-contract");
    let _ = writeln!(out, "seal_signature_request_ready=0");
    let _ = writeln!(out, "seal_signature_request_present=0");
    let _ = writeln!(out, "os_base_contract_status=metadata-only-contract");
    let _ = writeln!(out, "vm_evidence_contract_status=metadata-only-contract");
    let _ = writeln!(out, "seal_signature_present=0");
    let _ = writeln!(out, "receipt_signed=0");
    let _ = writeln!(out, "os_base_status={}", config.lc.os_base_profile);
    let _ = writeln!(out, "operator_shell_present=1");
    let _ = writeln!(out, "execution_allowed=0");
    let _ = writeln!(out, "host_mutation_allowed=0");
    let _ = writeln!(out, "network_allowed=0");
    let _ = writeln!(out, "runtime_enforcement_allowed=0");
    let _ = writeln!(out, "boot_allowed=0");
    let _ = writeln!(out, "os_base_enabled=0");
    let _ = writeln!(out, "production_os_claim=0");
    let _ = writeln!(out);
    let _ = writeln!(out, "[nadia]");
    let _ = writeln!(out, "system_name=Latticra Nadia Witness Foundation");
    let _ = writeln!(out, "public_name=Nadia");
    let _ = writeln!(out, "interactive_name=Nadia");
    let _ = writeln!(out, "implementation_name=Nadia Witness Foundation");
    let _ = writeln!(out, "documentation_code_name=Nadia Witness Foundation");
    let _ = writeln!(
        out,
        "stage=36-prompt-evaluation-result-release-receipt-review-contract"
    );
    let _ = writeln!(
        out,
        "previous_stage=35-prompt-evaluation-result-release-receipt-contract"
    );
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
    let _ = writeln!(
        out,
        "tokenizer_specification_contract_stage=18-tokenizer-specification-contract"
    );
    let _ = writeln!(
        out,
        "tokenizer_specification_contract_command=scripts/nadia-tokenizer-specification-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_tokenizer_specification_contract_command=latticra-nadia tokenizer-specification"
    );
    let _ = writeln!(out, "tokenizer_specification_stage=contract-only");
    let _ = writeln!(out, "tokenizer_specification_contract_status=contract_only");
    let _ = writeln!(out, "tokenizer_specification_authority=0");
    let _ = writeln!(out, "tokenizer_specification_allowed=0");
    let _ = writeln!(out, "tokenizer_specification_performed=0");
    let _ = writeln!(out, "tokenizer_specification_metadata_present=1");
    let _ = writeln!(out, "tokenizer_family=model-compatible-tokenizer");
    let _ = writeln!(
        out,
        "tokenizer_format=operator-reviewed-offline-specification"
    );
    let _ = writeln!(
        out,
        "tokenizer_specification_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "tokenizer_path_recorded=0");
    let _ = writeln!(out, "tokenizer_manifest_loaded=0");
    let _ = writeln!(out, "requires_tokenization_boundary_contract=1");
    let _ = writeln!(out, "requires_future_tokenizer_manifest_contract=1");
    let _ = writeln!(out, "tokenizer_specification_promotion_allowed=0");
    let _ = writeln!(
        out,
        "tokenizer_manifest_contract_stage=19-tokenizer-manifest-contract"
    );
    let _ = writeln!(
        out,
        "tokenizer_manifest_contract_command=scripts/nadia-tokenizer-manifest-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_tokenizer_manifest_contract_command=latticra-nadia tokenizer-manifest"
    );
    let _ = writeln!(out, "tokenizer_manifest_stage=contract-only");
    let _ = writeln!(out, "tokenizer_manifest_contract_status=contract_only");
    let _ = writeln!(out, "tokenizer_manifest_authority=0");
    let _ = writeln!(out, "tokenizer_manifest_allowed=0");
    let _ = writeln!(out, "tokenizer_manifest_performed=0");
    let _ = writeln!(out, "tokenizer_manifest_metadata_present=1");
    let _ = writeln!(
        out,
        "tokenizer_manifest_family=operator-reviewed-tokenizer-manifest"
    );
    let _ = writeln!(
        out,
        "tokenizer_manifest_format=contract-only-offline-manifest"
    );
    let _ = writeln!(out, "tokenizer_manifest_decision=blocked_contract_only");
    let _ = writeln!(out, "tokenizer_manifest_path_recorded=0");
    let _ = writeln!(out, "tokenizer_manifest_schema_planned=1");
    let _ = writeln!(out, "tokenizer_manifest_opened=0");
    let _ = writeln!(out, "tokenizer_manifest_read=0");
    let _ = writeln!(out, "tokenizer_manifest_parsed=0");
    let _ = writeln!(out, "tokenizer_manifest_validated=0");
    let _ = writeln!(out, "tokenizer_manifest_loaded=0");
    let _ = writeln!(out, "requires_tokenizer_specification_contract=1");
    let _ = writeln!(
        out,
        "requires_future_tokenizer_artifact_inventory_contract=1"
    );
    let _ = writeln!(out, "tokenizer_manifest_promotion_allowed=0");
    let _ = writeln!(
        out,
        "tokenizer_artifact_inventory_contract_stage=20-tokenizer-artifact-inventory-contract"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_inventory_contract_command=scripts/nadia-tokenizer-artifact-inventory-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_tokenizer_artifact_inventory_contract_command=latticra-nadia tokenizer-artifact-inventory"
    );
    let _ = writeln!(out, "tokenizer_artifact_inventory_stage=contract-only");
    let _ = writeln!(
        out,
        "tokenizer_artifact_inventory_contract_status=contract_only"
    );
    let _ = writeln!(out, "tokenizer_artifact_inventory_authority=0");
    let _ = writeln!(out, "tokenizer_artifact_inventory_allowed=0");
    let _ = writeln!(out, "tokenizer_artifact_inventory_performed=0");
    let _ = writeln!(out, "tokenizer_artifact_inventory_metadata_present=1");
    let _ = writeln!(
        out,
        "tokenizer_artifact_inventory_family=operator-reviewed-tokenizer-artifact-inventory"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_inventory_format=contract-only-offline-inventory"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_inventory_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "tokenizer_artifact_inventory_path_recorded=0");
    let _ = writeln!(out, "tokenizer_artifact_inventory_schema_planned=1");
    let _ = writeln!(out, "tokenizer_artifact_inventory_entry_count=0");
    let _ = writeln!(out, "tokenizer_artifact_inventory_file_count=0");
    let _ = writeln!(out, "tokenizer_artifact_path_resolved=0");
    let _ = writeln!(out, "tokenizer_artifact_scan_performed=0");
    let _ = writeln!(out, "tokenizer_artifact_stat_performed=0");
    let _ = writeln!(out, "tokenizer_artifact_file_opened=0");
    let _ = writeln!(out, "tokenizer_artifact_file_read=0");
    let _ = writeln!(out, "tokenizer_artifact_hash_computed=0");
    let _ = writeln!(out, "tokenizer_artifact_measurement_performed=0");
    let _ = writeln!(out, "requires_tokenizer_manifest_contract=1");
    let _ = writeln!(
        out,
        "requires_future_tokenizer_artifact_measurement_contract=1"
    );
    let _ = writeln!(out, "tokenizer_artifact_inventory_promotion_allowed=0");
    let _ = writeln!(
        out,
        "tokenizer_artifact_measurement_contract_stage=21-tokenizer-artifact-measurement-contract"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_measurement_contract_command=scripts/nadia-tokenizer-artifact-measurement-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_tokenizer_artifact_measurement_contract_command=latticra-nadia tokenizer-artifact-measurement"
    );
    let _ = writeln!(out, "tokenizer_artifact_measurement_stage=contract-only");
    let _ = writeln!(
        out,
        "tokenizer_artifact_measurement_contract_status=contract_only"
    );
    let _ = writeln!(out, "tokenizer_artifact_measurement_authority=0");
    let _ = writeln!(out, "tokenizer_artifact_measurement_allowed=0");
    let _ = writeln!(out, "tokenizer_artifact_measurement_performed=0");
    let _ = writeln!(out, "tokenizer_artifact_measurement_metadata_present=1");
    let _ = writeln!(
        out,
        "tokenizer_artifact_measurement_family=operator-reviewed-tokenizer-artifact-measurement"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_measurement_format=contract-only-offline-measurement"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_measurement_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "tokenizer_artifact_measurement_plan_recorded=1");
    let _ = writeln!(out, "tokenizer_artifact_measurement_result_recorded=0");
    let _ = writeln!(out, "tokenizer_artifact_measurement_digest_recorded=0");
    let _ = writeln!(out, "tokenizer_artifact_measurement_size_recorded=0");
    let _ = writeln!(out, "tokenizer_artifact_measurement_hash_computed=0");
    let _ = writeln!(out, "requires_tokenizer_artifact_inventory_contract=1");
    let _ = writeln!(
        out,
        "requires_future_tokenizer_artifact_verification_contract=1"
    );
    let _ = writeln!(out, "tokenizer_artifact_measurement_promotion_allowed=0");
    let _ = writeln!(
        out,
        "tokenizer_artifact_verification_contract_stage=22-tokenizer-artifact-verification-contract"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_verification_contract_command=scripts/nadia-tokenizer-artifact-verification-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_tokenizer_artifact_verification_contract_command=latticra-nadia tokenizer-artifact-verification"
    );
    let _ = writeln!(out, "tokenizer_artifact_verification_stage=contract-only");
    let _ = writeln!(
        out,
        "tokenizer_artifact_verification_contract_status=contract_only"
    );
    let _ = writeln!(out, "tokenizer_artifact_verification_authority=0");
    let _ = writeln!(out, "tokenizer_artifact_verification_allowed=0");
    let _ = writeln!(out, "tokenizer_artifact_verification_performed=0");
    let _ = writeln!(out, "tokenizer_artifact_verification_metadata_present=1");
    let _ = writeln!(
        out,
        "tokenizer_artifact_verification_family=operator-reviewed-tokenizer-artifact-verification"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_verification_format=contract-only-offline-verification"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_verification_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "tokenizer_artifact_verification_plan_recorded=1");
    let _ = writeln!(
        out,
        "tokenizer_artifact_verification_comparison_performed=0"
    );
    let _ = writeln!(out, "tokenizer_artifact_verification_result_recorded=0");
    let _ = writeln!(
        out,
        "tokenizer_artifact_verification_digest_match_recorded=0"
    );
    let _ = writeln!(out, "tokenizer_artifact_verification_size_match_recorded=0");
    let _ = writeln!(out, "tokenizer_artifact_verification_hash_computed=0");
    let _ = writeln!(out, "requires_tokenizer_artifact_measurement_contract=1");
    let _ = writeln!(out, "requires_future_tokenizer_artifact_binding_contract=1");
    let _ = writeln!(out, "tokenizer_artifact_verification_promotion_allowed=0");
    let _ = writeln!(
        out,
        "tokenizer_artifact_binding_contract_stage=23-tokenizer-artifact-binding-contract"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_binding_contract_command=scripts/nadia-tokenizer-artifact-binding-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_tokenizer_artifact_binding_contract_command=latticra-nadia tokenizer-artifact-binding"
    );
    let _ = writeln!(out, "tokenizer_artifact_binding_stage=contract-only");
    let _ = writeln!(
        out,
        "tokenizer_artifact_binding_contract_status=contract_only"
    );
    let _ = writeln!(out, "tokenizer_artifact_binding_authority=0");
    let _ = writeln!(out, "tokenizer_artifact_binding_allowed=0");
    let _ = writeln!(out, "tokenizer_artifact_binding_performed=0");
    let _ = writeln!(out, "tokenizer_artifact_binding_metadata_present=1");
    let _ = writeln!(
        out,
        "tokenizer_artifact_binding_family=operator-reviewed-tokenizer-artifact-binding"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_binding_format=contract-only-offline-binding"
    );
    let _ = writeln!(
        out,
        "tokenizer_artifact_binding_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "tokenizer_artifact_binding_plan_recorded=1");
    let _ = writeln!(out, "tokenizer_artifact_binding_result_recorded=0");
    let _ = writeln!(out, "tokenizer_artifact_binding_record_created=0");
    let _ = writeln!(out, "tokenizer_artifact_binding_hash_computed=0");
    let _ = writeln!(out, "tokenizer_artifact_binding_bound=0");
    let _ = writeln!(
        out,
        "tokenizer_artifact_binding_runtime_attachment_performed=0"
    );
    let _ = writeln!(out, "tokenizer_artifact_bound_to_manifest=0");
    let _ = writeln!(out, "tokenizer_artifact_bound_to_tokenizer=0");
    let _ = writeln!(out, "tokenizer_attached_to_runtime=0");
    let _ = writeln!(out, "requires_tokenizer_artifact_verification_contract=1");
    let _ = writeln!(
        out,
        "requires_future_tokenizer_runtime_attachment_contract=1"
    );
    let _ = writeln!(out, "tokenizer_artifact_binding_promotion_allowed=0");
    let _ = writeln!(
        out,
        "tokenizer_runtime_attachment_contract_stage=24-tokenizer-runtime-attachment-contract"
    );
    let _ = writeln!(
        out,
        "tokenizer_runtime_attachment_contract_command=scripts/nadia-tokenizer-runtime-attachment-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_tokenizer_runtime_attachment_contract_command=latticra-nadia tokenizer-runtime-attachment"
    );
    let _ = writeln!(out, "tokenizer_runtime_attachment_stage=contract-only");
    let _ = writeln!(
        out,
        "tokenizer_runtime_attachment_contract_status=contract_only"
    );
    let _ = writeln!(out, "tokenizer_runtime_attachment_authority=0");
    let _ = writeln!(out, "tokenizer_runtime_attachment_allowed=0");
    let _ = writeln!(out, "tokenizer_runtime_attachment_performed=0");
    let _ = writeln!(out, "tokenizer_runtime_attachment_metadata_present=1");
    let _ = writeln!(
        out,
        "tokenizer_runtime_attachment_family=operator-reviewed-tokenizer-runtime-attachment"
    );
    let _ = writeln!(
        out,
        "tokenizer_runtime_attachment_format=contract-only-offline-attachment"
    );
    let _ = writeln!(
        out,
        "tokenizer_runtime_attachment_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "tokenizer_runtime_attachment_plan_recorded=1");
    let _ = writeln!(out, "tokenizer_runtime_attachment_result_recorded=0");
    let _ = writeln!(out, "tokenizer_runtime_attachment_record_created=0");
    let _ = writeln!(out, "tokenizer_runtime_attachment_attached=0");
    let _ = writeln!(out, "tokenizer_runtime_attachment_runtime_invoked=0");
    let _ = writeln!(out, "tokenizer_runtime_attachment_session_created=0");
    let _ = writeln!(out, "runtime_session_created=0");
    let _ = writeln!(out, "runtime_invoked=0");
    let _ = writeln!(out, "requires_tokenizer_artifact_binding_contract=1");
    let _ = writeln!(out, "requires_future_prompt_tokenization_contract=1");
    let _ = writeln!(out, "tokenizer_runtime_attachment_promotion_allowed=0");
    let _ = writeln!(
        out,
        "prompt_tokenization_contract_stage=25-prompt-tokenization-contract"
    );
    let _ = writeln!(
        out,
        "prompt_tokenization_contract_command=scripts/nadia-prompt-tokenization-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_tokenization_contract_command=latticra-nadia prompt-tokenization"
    );
    let _ = writeln!(out, "prompt_tokenization_stage=contract-only");
    let _ = writeln!(out, "prompt_tokenization_contract_status=contract_only");
    let _ = writeln!(out, "prompt_tokenization_authority=0");
    let _ = writeln!(out, "prompt_tokenization_allowed=0");
    let _ = writeln!(out, "prompt_tokenization_performed=0");
    let _ = writeln!(out, "prompt_tokenization_metadata_present=1");
    let _ = writeln!(
        out,
        "prompt_tokenization_family=operator-reviewed-prompt-tokenization"
    );
    let _ = writeln!(
        out,
        "prompt_tokenization_format=contract-only-offline-tokenization"
    );
    let _ = writeln!(out, "prompt_tokenization_decision=blocked_contract_only");
    let _ = writeln!(out, "prompt_tokenization_plan_recorded=1");
    let _ = writeln!(out, "prompt_tokenization_result_recorded=0");
    let _ = writeln!(out, "prompt_tokenization_token_count_recorded=0");
    let _ = writeln!(out, "prompt_tokenization_token_sequence_recorded=0");
    let _ = writeln!(out, "prompt_tokenization_runtime_invoked=0");
    let _ = writeln!(out, "prompt_tokens_created=0");
    let _ = writeln!(out, "prompt_token_count_recorded=0");
    let _ = writeln!(out, "prompt_token_sequence_recorded=0");
    let _ = writeln!(out, "prompt_token_buffer_created=0");
    let _ = writeln!(out, "prompt_tokenized=0");
    let _ = writeln!(out, "requires_tokenizer_runtime_attachment_contract=1");
    let _ = writeln!(out, "requires_future_prompt_token_sequence_contract=1");
    let _ = writeln!(out, "prompt_tokenization_promotion_allowed=0");
    let _ = writeln!(
        out,
        "prompt_token_sequence_contract_stage=26-prompt-token-sequence-contract"
    );
    let _ = writeln!(
        out,
        "prompt_token_sequence_contract_command=scripts/nadia-prompt-token-sequence-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_token_sequence_contract_command=latticra-nadia prompt-token-sequence"
    );
    let _ = writeln!(out, "prompt_token_sequence_stage=contract-only");
    let _ = writeln!(out, "prompt_token_sequence_contract_status=contract_only");
    let _ = writeln!(out, "prompt_token_sequence_authority=0");
    let _ = writeln!(out, "prompt_token_sequence_allowed=0");
    let _ = writeln!(out, "prompt_token_sequence_recorded=0");
    let _ = writeln!(out, "prompt_token_sequence_metadata_present=1");
    let _ = writeln!(
        out,
        "prompt_token_sequence_family=operator-reviewed-prompt-token-sequence"
    );
    let _ = writeln!(
        out,
        "prompt_token_sequence_format=contract-only-offline-sequence"
    );
    let _ = writeln!(out, "prompt_token_sequence_decision=blocked_contract_only");
    let _ = writeln!(out, "prompt_token_sequence_plan_recorded=1");
    let _ = writeln!(out, "prompt_token_sequence_result_recorded=0");
    let _ = writeln!(out, "prompt_token_sequence_count_recorded=0");
    let _ = writeln!(out, "prompt_token_sequence_order_recorded=0");
    let _ = writeln!(out, "prompt_token_sequence_runtime_invoked=0");
    let _ = writeln!(out, "prompt_token_ids_recorded=0");
    let _ = writeln!(out, "prompt_attention_mask_created=0");
    let _ = writeln!(out, "context_window_assembled=0");
    let _ = writeln!(out, "requires_prompt_tokenization_contract=1");
    let _ = writeln!(out, "requires_future_context_window_assembly_contract=1");
    let _ = writeln!(out, "prompt_token_sequence_promotion_allowed=0");
    let _ = writeln!(
        out,
        "context_window_assembly_contract_stage=27-context-window-assembly-contract"
    );
    let _ = writeln!(
        out,
        "context_window_assembly_contract_command=scripts/nadia-context-window-assembly-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_context_window_assembly_contract_command=latticra-nadia context-window-assembly"
    );
    let _ = writeln!(out, "context_window_assembly_stage=contract-only");
    let _ = writeln!(out, "context_window_assembly_contract_status=contract_only");
    let _ = writeln!(out, "context_window_assembly_authority=0");
    let _ = writeln!(out, "context_window_assembly_allowed=0");
    let _ = writeln!(out, "context_window_assembly_performed=0");
    let _ = writeln!(out, "context_window_assembly_metadata_present=1");
    let _ = writeln!(
        out,
        "context_window_family=operator-reviewed-context-window-assembly"
    );
    let _ = writeln!(
        out,
        "context_window_format=contract-only-offline-context-window"
    );
    let _ = writeln!(
        out,
        "context_window_assembly_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "context_window_assembly_plan_recorded=1");
    let _ = writeln!(out, "context_window_assembly_result_recorded=0");
    let _ = writeln!(out, "context_window_assembly_runtime_invoked=0");
    let _ = writeln!(out, "context_window_token_budget_recorded=0");
    let _ = writeln!(out, "context_window_truncation_applied=0");
    let _ = writeln!(out, "context_window_serialized=0");
    let _ = writeln!(out, "requires_prompt_token_sequence_contract=1");
    let _ = writeln!(out, "requires_future_prompt_evaluation_input_contract=1");
    let _ = writeln!(out, "prompt_evaluation_input_created=0");
    let _ = writeln!(out, "context_window_assembly_promotion_allowed=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_input_contract_stage=28-prompt-evaluation-input-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_input_contract_command=scripts/nadia-prompt-evaluation-input-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_input_contract_command=latticra-nadia prompt-evaluation-input"
    );
    let _ = writeln!(out, "prompt_evaluation_input_stage=contract-only");
    let _ = writeln!(out, "prompt_evaluation_input_contract_status=contract_only");
    let _ = writeln!(out, "prompt_evaluation_input_authority=0");
    let _ = writeln!(out, "prompt_evaluation_input_allowed=0");
    let _ = writeln!(out, "prompt_evaluation_input_created=0");
    let _ = writeln!(out, "prompt_evaluation_input_metadata_present=1");
    let _ = writeln!(
        out,
        "prompt_evaluation_input_family=operator-reviewed-prompt-evaluation-input"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_input_format=contract-only-offline-evaluation-input"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_input_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_input_plan_recorded=1");
    let _ = writeln!(out, "prompt_evaluation_input_result_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_input_runtime_invoked=0");
    let _ = writeln!(out, "prompt_evaluation_input_materialized=0");
    let _ = writeln!(out, "prompt_evaluation_input_validated=0");
    let _ = writeln!(out, "prompt_evaluation_input_serialized=0");
    let _ = writeln!(out, "prompt_evaluation_input_written=0");
    let _ = writeln!(out, "requires_context_window_assembly_contract=1");
    let _ = writeln!(
        out,
        "requires_future_prompt_evaluation_runtime_handoff_contract=1"
    );
    let _ = writeln!(out, "prompt_evaluation_input_promotion_allowed=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_runtime_handoff_contract_stage=29-prompt-evaluation-runtime-handoff-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_runtime_handoff_contract_command=scripts/nadia-prompt-evaluation-runtime-handoff-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_runtime_handoff_contract_command=latticra-nadia prompt-evaluation-runtime-handoff"
    );
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_stage=contract-only");
    let _ = writeln!(
        out,
        "prompt_evaluation_runtime_handoff_contract_status=contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_authority=0");
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_allowed=0");
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_performed=0");
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_metadata_present=1");
    let _ = writeln!(
        out,
        "prompt_evaluation_runtime_handoff_family=operator-reviewed-prompt-evaluation-runtime-handoff"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_runtime_handoff_format=contract-only-offline-runtime-handoff"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_runtime_handoff_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_plan_recorded=1");
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_result_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_runtime_invoked=0");
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_request_created=0");
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_request_submitted=0");
    let _ = writeln!(out, "runtime_handoff_created=0");
    let _ = writeln!(out, "runtime_invocation_requested=0");
    let _ = writeln!(out, "requires_prompt_evaluation_input_contract=1");
    let _ = writeln!(
        out,
        "requires_future_prompt_evaluation_invocation_contract=1"
    );
    let _ = writeln!(out, "prompt_evaluation_runtime_handoff_promotion_allowed=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_invocation_contract_stage=30-prompt-evaluation-invocation-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_invocation_contract_command=scripts/nadia-prompt-evaluation-invocation-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_invocation_contract_command=latticra-nadia prompt-evaluation-invocation"
    );
    let _ = writeln!(out, "prompt_evaluation_invocation_stage=contract-only");
    let _ = writeln!(
        out,
        "prompt_evaluation_invocation_contract_status=contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_invocation_authority=0");
    let _ = writeln!(out, "prompt_evaluation_invocation_allowed=0");
    let _ = writeln!(out, "prompt_evaluation_invocation_performed=0");
    let _ = writeln!(out, "prompt_evaluation_invocation_metadata_present=1");
    let _ = writeln!(
        out,
        "prompt_evaluation_invocation_family=operator-reviewed-prompt-evaluation-invocation"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_invocation_format=contract-only-offline-evaluation-invocation"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_invocation_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_invocation_plan_recorded=1");
    let _ = writeln!(out, "prompt_evaluation_invocation_result_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_invocation_runtime_invoked=0");
    let _ = writeln!(out, "prompt_evaluation_invocation_request_created=0");
    let _ = writeln!(out, "prompt_evaluation_invocation_request_submitted=0");
    let _ = writeln!(out, "prompt_evaluation_invocation_request_scheduled=0");
    let _ = writeln!(out, "prompt_evaluation_invocation_request_queued=0");
    let _ = writeln!(out, "requires_prompt_evaluation_runtime_handoff_contract=1");
    let _ = writeln!(out, "requires_future_prompt_evaluation_result_contract=1");
    let _ = writeln!(out, "prompt_evaluation_invocation_promotion_allowed=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_contract_stage=31-prompt-evaluation-result-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_contract_command=scripts/nadia-prompt-evaluation-result-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_result_contract_command=latticra-nadia prompt-evaluation-result"
    );
    let _ = writeln!(out, "prompt_evaluation_result_stage=contract-only");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_contract_status=contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_result_authority=0");
    let _ = writeln!(out, "prompt_evaluation_result_allowed=0");
    let _ = writeln!(out, "prompt_evaluation_result_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_created=0");
    let _ = writeln!(out, "prompt_evaluation_result_performed=0");
    let _ = writeln!(out, "prompt_evaluation_result_metadata_present=1");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_family=operator-reviewed-prompt-evaluation-result"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_format=contract-only-offline-evaluation-result"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_result_plan_recorded=1");
    let _ = writeln!(out, "prompt_evaluation_result_result_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_runtime_invoked=0");
    let _ = writeln!(out, "prompt_evaluation_result_record_created=0");
    let _ = writeln!(out, "prompt_evaluation_result_model_output_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_output_text_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_score_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_token_logprobs_recorded=0");
    let _ = writeln!(out, "answer_text_generated=0");
    let _ = writeln!(out, "requires_prompt_evaluation_invocation_contract=1");
    let _ = writeln!(
        out,
        "requires_future_prompt_evaluation_result_review_contract=1"
    );
    let _ = writeln!(out, "prompt_evaluation_result_promotion_allowed=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_review_contract_stage=32-prompt-evaluation-result-review-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_review_contract_command=scripts/nadia-prompt-evaluation-result-review-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_result_review_contract_command=latticra-nadia prompt-evaluation-result-review"
    );
    let _ = writeln!(out, "prompt_evaluation_result_review_stage=contract-only");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_review_contract_status=contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_result_review_authority=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_allowed=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_created=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_performed=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_metadata_present=1");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_review_family=operator-reviewed-prompt-evaluation-result-review"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_review_format=contract-only-offline-evaluation-result-review"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_review_decision=blocked_contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_result_review_plan_recorded=1");
    let _ = writeln!(out, "prompt_evaluation_result_review_result_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_runtime_invoked=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_record_created=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_decision_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_approval_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_rejection_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_review_findings_recorded=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_disposition_contract_stage=33-prompt-evaluation-result-disposition-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_disposition_contract_command=scripts/nadia-prompt-evaluation-result-disposition-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_result_disposition_contract_command=latticra-nadia prompt-evaluation-result-disposition"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_disposition_contract_status=contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_result_disposition_record_created=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_disposition_decision_recorded=0"
    );
    let _ = writeln!(out, "prompt_evaluation_result_release_record_created=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_contract_stage=34-prompt-evaluation-result-release-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_contract_command=scripts/nadia-prompt-evaluation-result-release-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_result_release_contract_command=latticra-nadia prompt-evaluation-result-release"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_contract_status=contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_result_release_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_release_record_created=0");
    let _ = writeln!(out, "prompt_evaluation_result_release_decision_recorded=0");
    let _ = writeln!(out, "prompt_evaluation_result_release_published=0");
    let _ = writeln!(out, "prompt_evaluation_result_release_packaged=0");
    let _ = writeln!(out, "prompt_evaluation_result_release_receipt_created=0");
    let _ = writeln!(
        out,
        "requires_prompt_evaluation_result_disposition_contract=1"
    );
    let _ = writeln!(
        out,
        "requires_future_prompt_evaluation_result_release_receipt_contract=1"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_contract_stage=35-prompt-evaluation-result-release-receipt-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_contract_command=scripts/nadia-prompt-evaluation-result-release-receipt-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_result_release_receipt_contract_command=latticra-nadia prompt-evaluation-result-release-receipt"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_contract_status=contract_only"
    );
    let _ = writeln!(out, "prompt_evaluation_result_release_receipt_recorded=0");
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_record_created=0"
    );
    let _ = writeln!(out, "prompt_evaluation_result_release_receipt_signed=0");
    let _ = writeln!(out, "prompt_evaluation_result_release_receipt_published=0");
    let _ = writeln!(out, "requires_prompt_evaluation_result_release_contract=1");
    let _ = writeln!(
        out,
        "requires_future_prompt_evaluation_result_release_receipt_review_contract=1"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_review_contract_stage=36-prompt-evaluation-result-release-receipt-review-contract"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_review_contract_command=scripts/nadia-prompt-evaluation-result-release-receipt-review-contract.sh"
    );
    let _ = writeln!(
        out,
        "installed_prompt_evaluation_result_release_receipt_review_contract_command=latticra-nadia prompt-evaluation-result-release-receipt-review"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_review_contract_status=contract_only"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_review_recorded=0"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_review_record_created=0"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_review_decision_recorded=0"
    );
    let _ = writeln!(
        out,
        "prompt_evaluation_result_release_receipt_review_findings_recorded=0"
    );
    let _ = writeln!(
        out,
        "requires_future_prompt_evaluation_result_release_receipt_review_disposition_contract=1"
    );
    let _ = writeln!(out, "requires_prompt_evaluation_result_contract=1");
    let _ = writeln!(
        out,
        "requires_future_prompt_evaluation_result_disposition_contract=1"
    );
    let _ = writeln!(out, "prompt_evaluation_result_review_promotion_allowed=0");
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
