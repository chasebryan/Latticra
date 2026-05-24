use crate::config::{render_plan, InstallProfile, InstallerConfig};
use crate::engine::{self, InstallEvent};
use eframe::egui;
use std::fs;
use std::sync::mpsc::Receiver;
use std::time::Duration;

const SEAL_PNG: &[u8] = include_bytes!("../assets/latticra-panel.png");

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum InstallState {
    Idle,
    Running,
    Complete,
    Failed,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum WorkspaceTab {
    Guided,
    Components,
    Safety,
    Delivery,
    Evidence,
}

pub struct LatticraInstallerApp {
    config: InstallerConfig,
    plan: String,
    status: String,
    logs: Vec<String>,
    console_lines: Vec<String>,
    console_input: String,
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
        Self {
            config,
            plan,
            status: "Ready. Guided Workbench is selected with dry-run authority.".to_owned(),
            logs: Vec::new(),
            console_lines: vec![
                "Latticra Panel console online.".to_owned(),
                "Authority baseline: root=0 network=0 runtime_enforcement=0.".to_owned(),
                "Try: help, status, plan, save, dry-run, profile fedora, profile seal.".to_owned(),
            ],
            console_input: String::new(),
            show_plan_over_log: true,
            active_tab: WorkspaceTab::Guided,
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
        if self.console_lines.len() > 260 {
            let drain_count = self.console_lines.len() - 260;
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
                    self.status = "Install engine started.".to_owned();
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
                        self.status = "Install engine completed successfully.".to_owned();
                        self.push_console("engine: completed successfully");
                    } else {
                        self.install_state = InstallState::Failed;
                        self.status = format!(
                            "Install engine exited unsuccessfully{}.",
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

        self.push_console(format!("latticra-panel $ {command}"));
        let normalized = command.to_ascii_lowercase();
        let parts: Vec<&str> = normalized.split_whitespace().collect();

        match parts.as_slice() {
            ["help"] | ["?"] => {
                self.push_console("commands: help, status, plan, save, dry-run, clear");
                self.push_console("profiles: profile guided | profile seal | profile fedora | profile custom");
                self.push_console("modes: mode dry | mode local");
            }
            ["status"] => {
                self.push_console(format!("profile={}", self.config.profile.label()));
                self.push_console(format!("mode={}", self.config.execution_mode_label()));
                self.push_console(format!("install_prefix={}", self.config.install_prefix));
                self.push_console("root_authority=0 network_authority=0 runtime_enforcement_authority=0");
            }
            ["plan"] => {
                self.refresh_plan();
                self.show_plan_over_log = true;
                self.active_tab = WorkspaceTab::Evidence;
                self.push_console("plan refreshed in evidence panel");
            }
            ["save"] => self.save_config(),
            ["dry-run"] | ["run"] => self.start_install(),
            ["clear"] => self.console_lines.clear(),
            ["mode", "dry"] => {
                self.config.safety.dry_run = true;
                self.config.safety.allow_host_mutation = false;
                self.refresh_plan();
                self.push_console("mode -> dry-install");
            }
            ["mode", "local"] => {
                self.config.safety.dry_run = false;
                self.config.safety.allow_host_mutation = true;
                self.refresh_plan();
                self.push_console("mode -> guarded local-prefix install");
            }
            ["profile", "guided"] | ["profile", "workbench"] => {
                self.apply_profile(InstallProfile::DeveloperLocal)
            }
            ["profile", "seal"] => self.apply_profile(InstallProfile::SealReportOnly),
            ["profile", "fedora"] | ["profile", "vm"] => {
                self.apply_profile(InstallProfile::FedoraValidationVm)
            }
            ["profile", "custom"] => self.apply_profile(InstallProfile::Custom),
            _ => self.push_console("unknown command. try: help"),
        }
    }

    fn show_header(&mut self, ui: &mut egui::Ui) {
        ui.horizontal(|ui| {
            ui.heading(egui::RichText::new("Latticra Panel").size(24.0));
            ui.separator();
            ui.label("first-run configuration, validation, receipts, and operator control");
            ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                ui.monospace(format!("mode={}", self.config.execution_mode_label()));
                ui.monospace("root=0 network=0 runtime=0");
            });
        });
    }

    fn show_main_workbench(&mut self, ui: &mut egui::Ui) {
        self.refresh_plan();
        egui::ScrollArea::vertical()
            .id_source("latticra_main_workbench")
            .show(ui, |ui| {
                self.show_hero_strip(ui);
                ui.add_space(10.0);
                self.show_workspace_tabs(ui);
                ui.separator();

                match self.active_tab {
                    WorkspaceTab::Guided => self.show_guided_setup(ui),
                    WorkspaceTab::Components => self.show_components(ui),
                    WorkspaceTab::Safety => self.show_safety(ui),
                    WorkspaceTab::Delivery => self.show_delivery(ui),
                    WorkspaceTab::Evidence => self.show_evidence(ui),
                }

                ui.separator();
                self.show_action_buttons(ui);
            });
    }

    fn show_hero_strip(&mut self, ui: &mut egui::Ui) {
        ui.horizontal_top(|ui| {
            if let Some(texture) = &self.seal_texture {
                let image = egui::Image::new(texture).fit_to_exact_size(egui::vec2(132.0, 132.0));
                ui.add(image);
            }

            ui.add_space(12.0);
            ui.vertical(|ui| {
                ui.heading("Guided Workbench");
                ui.label(self.config.profile.detail());
                ui.add_space(6.0);
                ui.horizontal_wrapped(|ui| {
                    status_chip(ui, "production_installer_ready", "0");
                    status_chip(ui, "root_authority", "0");
                    status_chip(ui, "network_authority", "0");
                    status_chip(ui, "runtime_enforcement_authority", "0");
                });
                ui.add_space(8.0);
                if self.install_state == InstallState::Running {
                    ui.label(format!(
                        "Phase {}/{}: {}",
                        self.phase_index, self.phase_total, self.phase_title
                    ));
                    ui.add(egui::ProgressBar::new(self.progress()).show_percentage());
                } else {
                    ui.label(&self.status);
                }
            });
        });
    }

    fn show_workspace_tabs(&mut self, ui: &mut egui::Ui) {
        ui.horizontal_wrapped(|ui| {
            ui.selectable_value(&mut self.active_tab, WorkspaceTab::Guided, "Guided setup");
            ui.selectable_value(&mut self.active_tab, WorkspaceTab::Components, "Components");
            ui.selectable_value(&mut self.active_tab, WorkspaceTab::Safety, "Safety + evidence");
            ui.selectable_value(&mut self.active_tab, WorkspaceTab::Delivery, "Program delivery");
            ui.selectable_value(&mut self.active_tab, WorkspaceTab::Evidence, "Plan + receipts");
        });
    }

    fn show_guided_setup(&mut self, ui: &mut egui::Ui) {
        ui.heading("Choose a starting lane");
        ui.label("These are opinionated Latticra-safe defaults. The average user should start with Guided Workbench, generate a plan, then run a dry-install receipt before enabling any local writes.");
        ui.add_space(8.0);

        ui.columns(2, |columns| {
            self.profile_card(&mut columns[0], InstallProfile::DeveloperLocal, "Best first impression", "Full project surface, dry-run only, with Lat/LIR/Seal/docs/helpers ready for inspection.");
            self.profile_card(&mut columns[1], InstallProfile::SealReportOnly, "Minimal safe lane", "Report-only Seal and documentation lane for receipts and evidence without extra project payload.");
        });
        ui.add_space(6.0);
        ui.columns(2, |columns| {
            self.profile_card(&mut columns[0], InstallProfile::FedoraValidationVm, "Fedora validation", "VM-oriented Fedora/Linux validation workspace and evidence path.");
            self.profile_card(&mut columns[1], InstallProfile::Custom, "Manual operator", "Direct control for advanced users after the defaults are understood.");
        });

        ui.add_space(12.0);
        ui.group(|ui| {
            ui.heading("Recommended first-run procedure");
            numbered_step(ui, "1", "Keep dry-run enabled and inspect the generated plan.");
            numbered_step(ui, "2", "Run Dry-Install to validate configuration and write an operator receipt.");
            numbered_step(ui, "3", "Review the console output and plan/receipt evidence.");
            numbered_step(ui, "4", "Only then enable guarded local-prefix writes for a real user-local install.");
        });
    }

    fn profile_card(
        &mut self,
        ui: &mut egui::Ui,
        profile: InstallProfile,
        badge: &str,
        description: &str,
    ) {
        ui.group(|ui| {
            ui.horizontal(|ui| {
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
        checkbox_note(ui, &mut self.config.components.lat_tooling, "Lat language tooling", "Language and contract declaration tooling surface.");
        checkbox_note(ui, &mut self.config.components.lir_contracts, "LIR contracts", "Intermediate representation contracts and validation materials.");
        checkbox_note(ui, &mut self.config.components.seal_report_only, "Latticra Seal report-only subsystem", "Tool-boundary and trust-boundary reporting without runtime enforcement claims.");
        checkbox_note(ui, &mut self.config.components.fedora_validation, "Fedora validation files", "Fedora/Linux validation workspace, notes, and generated reports.");
        checkbox_note(ui, &mut self.config.components.docs_and_examples, "Documentation and examples", "User-facing project notes and local examples.");
        checkbox_note(ui, &mut self.config.components.developer_cli_helpers, "Developer CLI helpers", "Convenience wrappers for local exploration.");
    }

    fn show_safety(&mut self, ui: &mut egui::Ui) {
        ui.heading("Safety and evidence gates");
        ui.label("The panel should make authority visible before anything effectful can happen.");
        ui.add_space(6.0);
        checkbox_note(ui, &mut self.config.safety.dry_run, "Dry-run only", "Validation and receipts only. This is the recommended first-run mode.");
        checkbox_note(ui, &mut self.config.safety.allow_host_mutation, "Allow guarded local-prefix writes", "Required only for an actual user-local install. Still no root/system mutation.");
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
        checkbox_note(ui, &mut self.config.safety.require_component_manifest, "Require component manifest", "Refuse to proceed when component inventory evidence is missing.");
        checkbox_note(ui, &mut self.config.safety.require_artifact_measurements, "Require artifact measurements", "Keep generated measurement evidence in the receipt chain.");
        checkbox_note(ui, &mut self.config.safety.require_verification_policy_metadata, "Require verification policy metadata", "Preserve policy/evidence metadata expectations.");
        checkbox_note(ui, &mut self.config.safety.write_operator_receipt, "Write operator-visible receipt", "Create a visible receipt for the configured run.");
    }

    fn show_delivery(&mut self, ui: &mut egui::Ui) {
        ui.heading("Program delivery");
        ui.label("Control how the user-local payload, wrappers, desktop entry, and build outputs are prepared.");
        ui.add_space(6.0);
        ui.horizontal(|ui| {
            ui.label("Install prefix");
            ui.text_edit_singleline(&mut self.config.install_prefix);
            if ui.button("Reset").clicked() {
                self.config.install_prefix = match self.config.profile {
                    InstallProfile::FedoraValidationVm => "~/.local/share/latticra-validation".to_owned(),
                    _ => "~/.local/share/latticra".to_owned(),
                };
            }
        });
        ui.separator();
        checkbox_note(ui, &mut self.config.behavior.create_prefix_layout, "Create prefix layout", "Prepare the user-local directory structure.");
        checkbox_note(ui, &mut self.config.behavior.create_component_markers, "Create component markers", "Write installed component marker files.");
        checkbox_note(ui, &mut self.config.behavior.create_cli_shims, "Create CLI shims", "Prepare command shims inside the user-local prefix.");
        checkbox_note(ui, &mut self.config.behavior.preserve_existing_files, "Preserve existing files", "Refuse to overwrite unmanaged files.");
        ui.separator();
        checkbox_note(ui, &mut self.config.behavior.build_gui_installer, "Build Latticra Panel binary", "Build the panel itself when Cargo is available.");
        checkbox_note(ui, &mut self.config.behavior.build_latticra_from_source, "Build Latticra from source when available", "Use supported root build systems when present.");
        checkbox_note(ui, &mut self.config.behavior.install_payload_tree, "Install payload tree", "Copy project payload material into the local prefix.");
        checkbox_note(ui, &mut self.config.behavior.install_desktop_entry, "Install desktop entry", "Expose Latticra Panel in the user app grid.");
        checkbox_note(ui, &mut self.config.behavior.install_user_bin_wrappers, "Install user bin wrappers", "Install user-local wrappers for latticra, lat, seal, and panel commands.");
    }

    fn show_evidence(&mut self, ui: &mut egui::Ui) {
        ui.heading("Plan, receipts, and evidence");
        ui.horizontal(|ui| {
            if ui.selectable_label(self.show_plan_over_log, "Plan preview").clicked() {
                self.show_plan_over_log = true;
            }
            if ui.selectable_label(!self.show_plan_over_log, "Engine log").clicked() {
                self.show_plan_over_log = false;
            }
            if ui.button("Refresh plan").clicked() {
                self.refresh_plan();
            }
        });

        egui::ScrollArea::vertical()
            .id_source("latticra_evidence_panel")
            .max_height(360.0)
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
            if ui.button("Open evidence view").clicked() {
                self.active_tab = WorkspaceTab::Evidence;
            }
        });

        ui.add_space(10.0);
        self.show_fluid_install_button(ui);

        if let Err(err) = self.config.can_execute() {
            ui.colored_label(egui::Color32::from_rgb(255, 160, 130), err);
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

        let button = egui::Button::new(egui::RichText::new(label).size(20.0).strong())
            .min_size(egui::vec2(340.0, 58.0))
            .fill(fill)
            .stroke(stroke);

        let response = ui.add_enabled(can_execute, button);
        if response.clicked() {
            self.start_install();
            self.active_tab = WorkspaceTab::Evidence;
            self.show_plan_over_log = false;
        }
    }

    fn show_console_panel(&mut self, ui: &mut egui::Ui) {
        ui.group(|ui| {
            ui.horizontal(|ui| {
                ui.heading("Latticra Console");
                ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                    ui.small("embedded operator console");
                });
            });
            ui.small("Fedora-style control console. This is panel-aware, not an unrestricted shell.");
            ui.add_space(6.0);

            egui::Frame::none()
                .fill(egui::Color32::from_rgb(6, 10, 18))
                .stroke(egui::Stroke::new(1.0, egui::Color32::from_rgb(45, 90, 130)))
                .inner_margin(egui::Margin::same(8.0))
                .show(ui, |ui| {
                    egui::ScrollArea::vertical()
                        .id_source("latticra_embedded_console")
                        .max_height(310.0)
                        .stick_to_bottom(true)
                        .show(ui, |ui| {
                            ui.monospace("latticra@panel:~");
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
                        let response = ui.add(
                            egui::TextEdit::singleline(&mut self.console_input)
                                .font(egui::TextStyle::Monospace)
                                .hint_text("help | status | plan | save | dry-run"),
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
                if ui.button("help").clicked() {
                    self.console_input = "help".to_owned();
                    self.run_console_command();
                }
                if ui.button("status").clicked() {
                    self.console_input = "status".to_owned();
                    self.run_console_command();
                }
                if ui.button("plan").clicked() {
                    self.console_input = "plan".to_owned();
                    self.run_console_command();
                }
                if ui.button("dry-run").clicked() {
                    self.console_input = "dry-run".to_owned();
                    self.run_console_command();
                }
                if ui.button("clear").clicked() {
                    self.console_lines.clear();
                }
            });
        });
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
                .max_height(260.0)
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
}

impl eframe::App for LatticraInstallerApp {
    fn update(&mut self, ctx: &egui::Context, _: &mut eframe::Frame) {
        self.ensure_texture(ctx);
        self.drain_events();

        if self.install_state == InstallState::Running {
            ctx.request_repaint_after(Duration::from_millis(33));
        }

        egui::TopBottomPanel::top("top").show(ctx, |ui| {
            self.show_header(ui);
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            ui.add_space(8.0);
            let total_width = ui.available_width();
            let wide = total_width >= 1180.0;

            if wide {
                let console_width = (total_width * 0.36).clamp(520.0, 720.0);
                let left_width = (total_width - console_width - 18.0).max(560.0);
                ui.horizontal_top(|ui| {
                    ui.vertical(|ui| {
                        ui.set_width(left_width);
                        self.show_main_workbench(ui);
                    });
                    ui.add_space(12.0);
                    ui.vertical(|ui| {
                        ui.set_width(console_width);
                        self.show_console_panel(ui);
                        ui.add_space(10.0);
                        self.show_right_evidence_panel(ui);
                    });
                });
            } else {
                self.show_console_panel(ui);
                ui.separator();
                self.show_main_workbench(ui);
            }
        });
    }
}

fn status_chip(ui: &mut egui::Ui, key: &str, value: &str) {
    ui.label(
        egui::RichText::new(format!("{key}={value}"))
            .monospace()
            .color(egui::Color32::from_rgb(160, 220, 255)),
    );
}

fn numbered_step(ui: &mut egui::Ui, number: &str, text: &str) {
    ui.horizontal(|ui| {
        ui.label(
            egui::RichText::new(number)
                .strong()
                .color(egui::Color32::from_rgb(120, 220, 255)),
        );
        ui.label(text);
    });
}

fn checkbox_note(ui: &mut egui::Ui, value: &mut bool, label: &str, note: &str) {
    ui.checkbox(value, label);
    ui.small(note);
    ui.add_space(4.0);
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
            .with_inner_size([1440.0, 960.0])
            .with_min_inner_size([1040.0, 720.0])
            .with_maximized(true)
            .with_resizable(true)
            .with_title("Latticra Panel")
            .with_app_id("latticra-panel"),
        ..Default::default()
    };

    eframe::run_native(
        "Latticra Panel",
        options,
        Box::new(|_| Ok(Box::<LatticraInstallerApp>::default())),
    )
}
