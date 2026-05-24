use crate::config::{render_plan, InstallProfile, InstallerConfig};
use crate::engine::{self, InstallEvent};
use std::fs;
use std::io::{self, Write};
use std::sync::mpsc::Receiver;

pub fn run() -> Result<(), String> {
    TerminalPanel::default().run()
}

struct TerminalPanel {
    config: InstallerConfig,
    plan: String,
    status: String,
}

impl Default for TerminalPanel {
    fn default() -> Self {
        let config = InstallerConfig::default();
        let plan = render_plan(&config);
        Self {
            config,
            plan,
            status: "Ready. Configure the panel, then run a guarded dry-install or local install."
                .to_owned(),
        }
    }
}

impl TerminalPanel {
    fn run(&mut self) -> Result<(), String> {
        loop {
            self.config.safety.allow_network_effect = false;
            self.plan = render_plan(&self.config);
            self.show_dashboard();

            match prompt("Select action")?.as_str() {
                "" => {}
                "1" => self.choose_profile()?,
                "2" => self.edit_install_prefix()?,
                "3" => self.toggle_components()?,
                "4" => self.toggle_safety_and_evidence()?,
                "5" => self.toggle_behavior_and_programs()?,
                "6" => self.save_config()?,
                "7" => self.write_plan()?,
                "8" => self.preview_plan()?,
                "9" => self.run_install()?,
                "0" | "q" | "quit" | "exit" => return Ok(()),
                other => {
                    self.status = format!("Unknown action: {other}");
                }
            }
        }
    }

    fn show_dashboard(&self) {
        print!("\x1B[2J\x1B[H");
        println!("Latticra Terminal Configuration Panel");
        println!("=====================================");
        println!();
        println!("profile={}", self.config.profile.label());
        println!("mode={}", self.config.execution_mode_label());
        println!("install_prefix={}", self.config.install_prefix);
        println!();
        println!("Authority baseline");
        println!("  production_installer_ready=0");
        println!("  root_authority=0");
        println!("  network_authority=0");
        println!("  runtime_enforcement_authority=0");
        println!();
        println!("Components");
        print_flag("Lat language tooling", self.config.components.lat_tooling);
        print_flag("LIR contracts", self.config.components.lir_contracts);
        print_flag(
            "Latticra Seal report-only subsystem",
            self.config.components.seal_report_only,
        );
        print_flag("Fedora validation files", self.config.components.fedora_validation);
        print_flag(
            "Documentation and examples",
            self.config.components.docs_and_examples,
        );
        print_flag(
            "Developer CLI helpers",
            self.config.components.developer_cli_helpers,
        );
        println!();
        println!("Safety and evidence");
        print_flag("Dry-run only", self.config.safety.dry_run);
        print_flag(
            "Allow guarded local-prefix writes",
            self.config.safety.allow_host_mutation,
        );
        print_flag("Network effect (future; disabled)", false);
        print_flag(
            "Require component manifest",
            self.config.safety.require_component_manifest,
        );
        print_flag(
            "Require artifact measurements",
            self.config.safety.require_artifact_measurements,
        );
        print_flag(
            "Require verification policy metadata",
            self.config.safety.require_verification_policy_metadata,
        );
        print_flag(
            "Write operator-visible receipt",
            self.config.safety.write_operator_receipt,
        );
        println!();
        println!("Behavior and program delivery");
        print_flag(
            "Create prefix layout",
            self.config.behavior.create_prefix_layout,
        );
        print_flag(
            "Create component markers",
            self.config.behavior.create_component_markers,
        );
        print_flag("Create CLI shims", self.config.behavior.create_cli_shims);
        print_flag(
            "Preserve existing files",
            self.config.behavior.preserve_existing_files,
        );
        print_flag(
            "Build Latticra Panel binary",
            self.config.behavior.build_gui_installer,
        );
        print_flag(
            "Build Latticra from source when available",
            self.config.behavior.build_latticra_from_source,
        );
        print_flag(
            "Install payload tree",
            self.config.behavior.install_payload_tree,
        );
        print_flag(
            "Install desktop entry",
            self.config.behavior.install_desktop_entry,
        );
        print_flag(
            "Install user bin wrappers",
            self.config.behavior.install_user_bin_wrappers,
        );
        println!();
        println!("Actions");
        println!("  1) Change install profile");
        println!("  2) Edit install prefix");
        println!("  3) Toggle components");
        println!("  4) Toggle safety and evidence");
        println!("  5) Toggle behavior and program delivery");
        println!("  6) Save configuration");
        println!("  7) Generate plan");
        println!("  8) Preview plan");
        if self.config.safety.dry_run {
            println!("  9) Run Dry-Install");
        } else {
            println!("  9) Install guarded local prefix");
        }
        println!("  0) Exit");
        println!();
        println!("Status: {}", self.status);
        if let Err(err) = self.config.can_execute() {
            println!("Blocked: {err}");
        }
        println!();
    }

    fn choose_profile(&mut self) -> Result<(), String> {
        println!();
        println!("Install profiles");
        for (index, profile) in InstallProfile::all().iter().enumerate() {
            println!("  {}) {}", index + 1, profile.label());
        }
        println!("  0) Back");

        let choice = prompt("Select profile")?;
        if choice == "0" || choice.is_empty() {
            self.status = "Profile unchanged.".to_owned();
            return Ok(());
        }

        let index = choice
            .parse::<usize>()
            .map_err(|_| format!("Invalid profile selection: {choice}"))?;
        let profiles = InstallProfile::all();
        let profile = profiles
            .get(index.saturating_sub(1))
            .ok_or_else(|| format!("Invalid profile selection: {choice}"))?;

        self.config.profile = *profile;
        self.config.apply_profile_defaults();
        self.status = format!("Applied {} profile defaults.", self.config.profile.label());
        Ok(())
    }

    fn edit_install_prefix(&mut self) -> Result<(), String> {
        println!();
        println!("Current install prefix: {}", self.config.install_prefix);
        let prefix = prompt("New install prefix, or Enter to keep current")?;
        if prefix.is_empty() {
            self.status = "Install prefix unchanged.".to_owned();
        } else {
            self.config.install_prefix = prefix;
            self.status = "Install prefix updated.".to_owned();
        }
        Ok(())
    }

    fn toggle_components(&mut self) -> Result<(), String> {
        loop {
            println!();
            println!("Components");
            print_toggle(1, "Lat language tooling", self.config.components.lat_tooling);
            print_toggle(2, "LIR contracts", self.config.components.lir_contracts);
            print_toggle(
                3,
                "Latticra Seal report-only subsystem",
                self.config.components.seal_report_only,
            );
            print_toggle(
                4,
                "Fedora validation files",
                self.config.components.fedora_validation,
            );
            print_toggle(
                5,
                "Documentation and examples",
                self.config.components.docs_and_examples,
            );
            print_toggle(
                6,
                "Developer CLI helpers",
                self.config.components.developer_cli_helpers,
            );
            println!("  0) Back");

            match prompt("Toggle component")?.as_str() {
                "" | "0" => {
                    self.status = "Component selection updated.".to_owned();
                    return Ok(());
                }
                "1" => self.config.components.lat_tooling = !self.config.components.lat_tooling,
                "2" => self.config.components.lir_contracts = !self.config.components.lir_contracts,
                "3" => {
                    self.config.components.seal_report_only =
                        !self.config.components.seal_report_only;
                }
                "4" => {
                    self.config.components.fedora_validation =
                        !self.config.components.fedora_validation;
                }
                "5" => {
                    self.config.components.docs_and_examples =
                        !self.config.components.docs_and_examples;
                }
                "6" => {
                    self.config.components.developer_cli_helpers =
                        !self.config.components.developer_cli_helpers;
                }
                other => println!("Unknown component: {other}"),
            }
        }
    }

    fn toggle_safety_and_evidence(&mut self) -> Result<(), String> {
        loop {
            self.config.safety.allow_network_effect = false;
            println!();
            println!("Safety and evidence");
            print_toggle(1, "Dry-run only", self.config.safety.dry_run);
            print_toggle(
                2,
                "Allow guarded local-prefix writes",
                self.config.safety.allow_host_mutation,
            );
            print_toggle(3, "Network effect (future; disabled)", false);
            print_toggle(
                4,
                "Require component manifest",
                self.config.safety.require_component_manifest,
            );
            print_toggle(
                5,
                "Require artifact measurements",
                self.config.safety.require_artifact_measurements,
            );
            print_toggle(
                6,
                "Require verification policy metadata",
                self.config.safety.require_verification_policy_metadata,
            );
            print_toggle(
                7,
                "Write operator-visible receipt",
                self.config.safety.write_operator_receipt,
            );
            println!("  0) Back");

            match prompt("Toggle safety/evidence control")?.as_str() {
                "" | "0" => {
                    self.status = "Safety and evidence settings updated.".to_owned();
                    return Ok(());
                }
                "1" => self.config.safety.dry_run = !self.config.safety.dry_run,
                "2" => {
                    self.config.safety.allow_host_mutation =
                        !self.config.safety.allow_host_mutation;
                }
                "3" => {
                    self.config.safety.allow_network_effect = false;
                    println!("Network authority is intentionally disabled in this installer.");
                }
                "4" => {
                    self.config.safety.require_component_manifest =
                        !self.config.safety.require_component_manifest;
                }
                "5" => {
                    self.config.safety.require_artifact_measurements =
                        !self.config.safety.require_artifact_measurements;
                }
                "6" => {
                    self.config.safety.require_verification_policy_metadata =
                        !self.config.safety.require_verification_policy_metadata;
                }
                "7" => {
                    self.config.safety.write_operator_receipt =
                        !self.config.safety.write_operator_receipt;
                }
                other => println!("Unknown safety/evidence control: {other}"),
            }
        }
    }

    fn toggle_behavior_and_programs(&mut self) -> Result<(), String> {
        loop {
            println!();
            println!("Behavior and program delivery");
            print_toggle(
                1,
                "Create prefix layout",
                self.config.behavior.create_prefix_layout,
            );
            print_toggle(
                2,
                "Create component markers",
                self.config.behavior.create_component_markers,
            );
            print_toggle(3, "Create CLI shims", self.config.behavior.create_cli_shims);
            print_toggle(
                4,
                "Preserve existing files",
                self.config.behavior.preserve_existing_files,
            );
            print_toggle(
                5,
                "Build Latticra Panel binary",
                self.config.behavior.build_gui_installer,
            );
            print_toggle(
                6,
                "Build Latticra from source when available",
                self.config.behavior.build_latticra_from_source,
            );
            print_toggle(
                7,
                "Install payload tree",
                self.config.behavior.install_payload_tree,
            );
            print_toggle(
                8,
                "Install desktop entry",
                self.config.behavior.install_desktop_entry,
            );
            print_toggle(
                9,
                "Install user bin wrappers",
                self.config.behavior.install_user_bin_wrappers,
            );
            println!("  0) Back");

            match prompt("Toggle behavior/program control")?.as_str() {
                "" | "0" => {
                    self.status = "Behavior and program delivery settings updated.".to_owned();
                    return Ok(());
                }
                "1" => {
                    self.config.behavior.create_prefix_layout =
                        !self.config.behavior.create_prefix_layout;
                }
                "2" => {
                    self.config.behavior.create_component_markers =
                        !self.config.behavior.create_component_markers;
                }
                "3" => {
                    self.config.behavior.create_cli_shims =
                        !self.config.behavior.create_cli_shims;
                }
                "4" => {
                    self.config.behavior.preserve_existing_files =
                        !self.config.behavior.preserve_existing_files;
                }
                "5" => {
                    self.config.behavior.build_gui_installer =
                        !self.config.behavior.build_gui_installer;
                }
                "6" => {
                    self.config.behavior.build_latticra_from_source =
                        !self.config.behavior.build_latticra_from_source;
                }
                "7" => {
                    self.config.behavior.install_payload_tree =
                        !self.config.behavior.install_payload_tree;
                }
                "8" => {
                    self.config.behavior.install_desktop_entry =
                        !self.config.behavior.install_desktop_entry;
                }
                "9" => {
                    self.config.behavior.install_user_bin_wrappers =
                        !self.config.behavior.install_user_bin_wrappers;
                }
                other => println!("Unknown behavior/program control: {other}"),
            }
        }
    }

    fn save_config(&mut self) -> Result<(), String> {
        self.config.safety.allow_network_effect = false;
        let config_toml = toml::to_string_pretty(&self.config)
            .map_err(|err| format!("could not serialize installer config: {err}"))?;
        fs::write("latticra-installer-config.toml", config_toml)
            .map_err(|err| format!("could not write latticra-installer-config.toml: {err}"))?;
        self.status = "Saved latticra-installer-config.toml".to_owned();
        Ok(())
    }

    fn write_plan(&mut self) -> Result<(), String> {
        self.plan = render_plan(&self.config);
        fs::write("latticra-installer-plan.txt", &self.plan)
            .map_err(|err| format!("could not write latticra-installer-plan.txt: {err}"))?;
        self.status = "Wrote latticra-installer-plan.txt".to_owned();
        Ok(())
    }

    fn preview_plan(&mut self) -> Result<(), String> {
        self.plan = render_plan(&self.config);
        println!();
        println!("{}", self.plan);
        wait_for_enter("Press Enter to return to the terminal panel")?;
        self.status = "Plan preview refreshed.".to_owned();
        Ok(())
    }

    fn run_install(&mut self) -> Result<(), String> {
        self.config.can_execute()?;
        let action = if self.config.safety.dry_run {
            "Run guarded dry-install"
        } else {
            "Run guarded local-prefix install"
        };

        if !confirm(&format!("{action} now?"))? {
            self.status = "Install run cancelled.".to_owned();
            return Ok(());
        }

        println!();
        println!("Starting {}...", self.config.execution_mode_label());
        self.plan = render_plan(&self.config);
        let rx = engine::launch(self.config.clone());
        self.stream_install_events(rx)?;
        wait_for_enter("Press Enter to return to the terminal panel")?;
        Ok(())
    }

    fn stream_install_events(&mut self, rx: Receiver<InstallEvent>) -> Result<(), String> {
        loop {
            match rx.recv() {
                Ok(InstallEvent::Started) => {
                    println!("ENGINE: started");
                }
                Ok(InstallEvent::Log(line)) => {
                    if line.starts_with("PHASE ") {
                        self.status = line.clone();
                    }
                    println!("{line}");
                }
                Ok(InstallEvent::Finished { success, code }) => {
                    if success {
                        self.status = "Install engine completed successfully.".to_owned();
                        println!("ENGINE: completed successfully");
                    } else {
                        self.status = format!(
                            "Install engine exited unsuccessfully{}.",
                            code.map(|code| format!(" with code {code}"))
                                .unwrap_or_default()
                        );
                        println!("ENGINE: {}", self.status);
                    }
                    return Ok(());
                }
                Ok(InstallEvent::Failed(err)) => {
                    self.status = err.clone();
                    println!("ENGINE_FAILURE: {err}");
                    return Ok(());
                }
                Err(err) => {
                    self.status = format!("Install event stream closed unexpectedly: {err}");
                    return Ok(());
                }
            }
        }
    }
}

fn prompt(label: &str) -> Result<String, String> {
    print!("{label}: ");
    io::stdout()
        .flush()
        .map_err(|err| format!("could not flush stdout: {err}"))?;

    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .map_err(|err| format!("could not read terminal input: {err}"))?;
    Ok(input.trim().to_owned())
}

fn wait_for_enter(label: &str) -> Result<(), String> {
    let _ = prompt(label)?;
    Ok(())
}

fn confirm(label: &str) -> Result<bool, String> {
    let answer = prompt(&format!("{label} [y/N]"))?;
    Ok(matches!(answer.as_str(), "y" | "Y" | "yes" | "YES" | "Yes"))
}

fn print_flag(label: &str, value: bool) {
    println!("  [{}] {label}", flag(value));
}

fn print_toggle(index: usize, label: &str, value: bool) {
    println!("  {index}) [{}] {label}", flag(value));
}

fn flag(value: bool) -> char {
    if value {
        'x'
    } else {
        ' '
    }
}
