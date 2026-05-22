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

impl InstallProfile {
    pub fn label(self) -> &'static str {
        match self {
            Self::DeveloperLocal => "Developer Local",
            Self::SealReportOnly => "Seal Report-Only",
            Self::FedoraValidationVm => "Fedora Validation VM",
            Self::Custom => "Custom",
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

#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct Components {
    pub lat_tooling: bool,
    pub lir_contracts: bool,
    pub seal_report_only: bool,
    pub fedora_validation: bool,
    pub docs_and_examples: bool,
    pub developer_cli_helpers: bool,
}

#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct Safety {
    pub dry_run: bool,
    pub allow_host_mutation: bool,
    pub allow_network_effect: bool,
    pub require_component_manifest: bool,
    pub require_artifact_measurements: bool,
    pub require_verification_policy_metadata: bool,
    pub write_operator_receipt: bool,
}

#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct InstallBehavior {
    pub create_prefix_layout: bool,
    pub create_component_markers: bool,
    pub create_cli_shims: bool,
    pub preserve_existing_files: bool,
}

#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct InstallerConfig {
    pub profile: InstallProfile,
    pub install_prefix: String,
    pub components: Components,
    pub safety: Safety,
    pub behavior: InstallBehavior,
}

impl Default for InstallerConfig {
    fn default() -> Self {
        Self {
            profile: InstallProfile::SealReportOnly,
            install_prefix: "~/.local/share/latticra".to_owned(),
            components: Components {
                lat_tooling: false,
                lir_contracts: true,
                seal_report_only: true,
                fedora_validation: false,
                docs_and_examples: true,
                developer_cli_helpers: true,
            },
            safety: Safety {
                dry_run: true,
                allow_host_mutation: false,
                allow_network_effect: false,
                require_component_manifest: true,
                require_artifact_measurements: true,
                require_verification_policy_metadata: true,
                write_operator_receipt: true,
            },
            behavior: InstallBehavior {
                create_prefix_layout: true,
                create_component_markers: true,
                create_cli_shims: true,
                preserve_existing_files: true,
            },
        }
    }
}

impl InstallerConfig {
    pub fn apply_profile_defaults(&mut self) {
        match self.profile {
            InstallProfile::DeveloperLocal => {
                self.install_prefix = "~/.local/share/latticra".to_owned();
                self.components = Components {
                    lat_tooling: true,
                    lir_contracts: true,
                    seal_report_only: true,
                    fedora_validation: false,
                    docs_and_examples: true,
                    developer_cli_helpers: true,
                };
                self.safety.dry_run = true;
                self.safety.allow_host_mutation = false;
                self.safety.allow_network_effect = false;
            }
            InstallProfile::SealReportOnly => {
                self.install_prefix = "~/.local/share/latticra".to_owned();
                self.components = Components {
                    lat_tooling: false,
                    lir_contracts: true,
                    seal_report_only: true,
                    fedora_validation: false,
                    docs_and_examples: true,
                    developer_cli_helpers: true,
                };
                self.safety.dry_run = true;
                self.safety.allow_host_mutation = false;
                self.safety.allow_network_effect = false;
            }
            InstallProfile::FedoraValidationVm => {
                self.install_prefix = "~/.local/share/latticra-validation".to_owned();
                self.components = Components {
                    lat_tooling: true,
                    lir_contracts: true,
                    seal_report_only: true,
                    fedora_validation: true,
                    docs_and_examples: true,
                    developer_cli_helpers: true,
                };
                self.safety.dry_run = true;
                self.safety.allow_host_mutation = false;
                self.safety.allow_network_effect = false;
            }
            InstallProfile::Custom => {}
        }

        self.behavior = InstallBehavior {
            create_prefix_layout: true,
            create_component_markers: true,
            create_cli_shims: true,
            preserve_existing_files: true,
        };
    }

    pub fn execution_mode_label(&self) -> &'static str {
        if self.safety.dry_run {
            "dry-install"
        } else {
            "local-prefix-install"
        }
    }

    pub fn can_execute(&self) -> Result<(), String> {
        if self.safety.dry_run {
            return Ok(());
        }

        if !self.safety.allow_host_mutation {
            return Err("Real install requires allow_host_mutation=true. Keep dry-run enabled or explicitly authorize a guarded local-prefix install.".to_owned());
        }

        if self.safety.allow_network_effect {
            return Err("Network authority is not implemented in this installer. Disable allow_network_effect.".to_owned());
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
    let _ = writeln!(out);
    let _ = writeln!(out, "[next_action]");
    if config.safety.dry_run {
        let _ = writeln!(out, "result=execute-dry-install");
        let _ = writeln!(
            out,
            "message=Press Run Dry-Install to validate and write a dry-install receipt."
        );
    } else if config.safety.allow_host_mutation {
        let _ = writeln!(out, "result=execute-local-prefix-install");
        let _ = writeln!(
            out,
            "message=Press Install to write the guarded user-local prefix layout."
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
