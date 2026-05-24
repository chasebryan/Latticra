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

pub struct LatticraInstallerApp {
    config: InstallerConfig,
    plan: String,
    status: String,
    logs: Vec<String>,
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
            status: "Ready. Configure the panel, then run a guarded dry-install or local install."
                .to_owned(),
            logs: Vec::new(),
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

    fn save_config(&mut self) {
        self.config.safety.allow_network_effect = false;
        match toml::to_string_pretty(&self.config) {
            Ok(toml) => match fs::write("latticra-installer-config.toml", toml) {
                Ok(_) => self.status = "Saved latticra-installer-config.toml".to_owned(),
                Err(err) => self.status = format!("Could not save config: {err}"),
            },
            Err(err) => self.status = format!("Could not serialize config: {err}"),
        }
    }

    fn write_plan(&mut self) {
        self.config.safety.allow_network_effect = false;
        self.plan = render_plan(&self.config);
        match fs::write("latticra-installer-plan.txt", &self.plan) {
            Ok(_) => self.status = "Wrote latticra-installer-plan.txt".to_owned(),
            Err(err) => self.status = format!("Could not write plan: {err}"),
        }
    }

    fn start_install(&mut self) {
        self.config.safety.allow_network_effect = false;
        match self.config.can_execute() {
            Ok(()) => {
                self.plan = render_plan(&self.config);
                self.logs.clear();
                self.phase_index = 0;
                self.phase_total = 10;
                self.phase_title = "starting".to_owned();
                self.install_state = InstallState::Running;
                self.status = format!("Starting {}...", self.config.execution_mode_label());
                self.rx = Some(engine::launch(self.config.clone()));
            }
            Err(err) => {
                self.install_state = InstallState::Failed;
                self.status = err;
            }
        }
    }

    fn drain_events(&mut self) {
        let mut clear_rx = false;

        if let Some(rx) = &self.rx {
            while let Ok(event) = rx.try_recv() {
                match event {
                    InstallEvent::Started => {
                        self.install_state = InstallState::Running;
                        self.status = "Install engine started.".to_owned();
                    }
                    InstallEvent::Log(line) => {
                        if let Some((index, total, title)) = parse_phase_line(&line) {
                            self.phase_index = index;
                            self.phase_total = total.max(1);
                            self.phase_title = title.clone();
                            self.status = format!("{title}...");
                        }
                        self.logs.push(line);
                        if self.logs.len() > 350 {
                            let drain_count = self.logs.len() - 350;
                            self.logs.drain(0..drain_count);
                        }
                    }
                    InstallEvent::Finished { success, code } => {
                        clear_rx = true;
                        self.phase_index = self.phase_total;
                        if success {
                            self.install_state = InstallState::Complete;
                            self.status = "Install engine completed successfully.".to_owned();
                        } else {
                            self.install_state = InstallState::Failed;
                            self.status = format!(
                                "Install engine exited unsuccessfully{}.",
                                code.map(|code| format!(" with code {code}"))
                                    .unwrap_or_default()
                            );
                        }
                    }
                    InstallEvent::Failed(err) => {
                        clear_rx = true;
                        self.install_state = InstallState::Failed;
                        self.status = err.clone();
                        self.logs.push(format!("ENGINE_FAILURE: {err}"));
                    }
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

    fn show_profile_and_components(&mut self, ui: &mut egui::Ui) {
        ui.heading("Configuration");

        let old_profile = self.config.profile;
        egui::ComboBox::from_label("Install profile")
            .selected_text(self.config.profile.label())
            .show_ui(ui, |ui| {
                for profile in InstallProfile::all() {
                    ui.selectable_value(&mut self.config.profile, profile, profile.label());
                }
            });

        if self.config.profile != old_profile {
            self.config.apply_profile_defaults();
        }

        ui.horizontal(|ui| {
            ui.label("Install prefix");
            ui.text_edit_singleline(&mut self.config.install_prefix);
        });

        ui.separator();
        ui.heading("Components");
        ui.checkbox(
            &mut self.config.components.lat_tooling,
            "Lat language tooling",
        );
        ui.checkbox(&mut self.config.components.lir_contracts, "LIR contracts");
        ui.checkbox(
            &mut self.config.components.seal_report_only,
            "Latticra Seal report-only subsystem",
        );
        ui.checkbox(
            &mut self.config.components.fedora_validation,
            "Fedora validation files",
        );
        ui.checkbox(
            &mut self.config.components.docs_and_examples,
            "Documentation and examples",
        );
        ui.checkbox(
            &mut self.config.components.developer_cli_helpers,
            "Developer CLI helpers",
        );
    }

    fn show_safety_and_behavior(&mut self, ui: &mut egui::Ui) {
        ui.heading("Safety and evidence");
        ui.checkbox(&mut self.config.safety.dry_run, "Dry-run only");
        ui.checkbox(
            &mut self.config.safety.allow_host_mutation,
            "Allow guarded local-prefix writes",
        );
        self.config.safety.allow_network_effect = false;
        ui.add_enabled(
            false,
            egui::Checkbox::new(
                &mut self.config.safety.allow_network_effect,
                "Network effect (future; disabled)",
            ),
        );
        ui.checkbox(
            &mut self.config.safety.require_component_manifest,
            "Require component manifest",
        );
        ui.checkbox(
            &mut self.config.safety.require_artifact_measurements,
            "Require artifact measurements",
        );
        ui.checkbox(
            &mut self.config.safety.require_verification_policy_metadata,
            "Require verification policy metadata",
        );
        ui.checkbox(
            &mut self.config.safety.write_operator_receipt,
            "Write operator-visible receipt",
        );

        ui.separator();
        ui.heading("Install behavior");
        ui.checkbox(
            &mut self.config.behavior.create_prefix_layout,
            "Create prefix layout",
        );
        ui.checkbox(
            &mut self.config.behavior.create_component_markers,
            "Create component markers",
        );
        ui.checkbox(
            &mut self.config.behavior.create_cli_shims,
            "Create CLI shims",
        );
        ui.checkbox(
            &mut self.config.behavior.preserve_existing_files,
            "Preserve existing files",
        );

        ui.separator();
        ui.heading("Program delivery");
        ui.checkbox(
            &mut self.config.behavior.build_gui_installer,
            "Build Latticra Panel binary",
        );
        ui.checkbox(
            &mut self.config.behavior.build_latticra_from_source,
            "Build Latticra from source when available",
        );
        ui.checkbox(
            &mut self.config.behavior.install_payload_tree,
            "Install payload tree",
        );
        ui.checkbox(
            &mut self.config.behavior.install_desktop_entry,
            "Install desktop entry",
        );
        ui.checkbox(
            &mut self.config.behavior.install_user_bin_wrappers,
            "Install user bin wrappers",
        );
    }

    fn show_action_buttons(&mut self, ui: &mut egui::Ui) {
        ui.horizontal(|ui| {
            if ui.button("Save configuration").clicked() {
                self.save_config();
            }

            if ui.button("Generate plan").clicked() {
                self.write_plan();
            }
        });

        ui.add_space(10.0);
        self.show_fluid_install_button(ui);

        if let Err(err) = self.config.can_execute() {
            ui.colored_label(egui::Color32::from_rgb(255, 160, 130), err);
        }

        ui.label(&self.status);

        if self.install_state == InstallState::Running {
            ui.add_space(4.0);
            ui.label(format!(
                "Phase {}/{}: {}",
                self.phase_index, self.phase_total, self.phase_title
            ));
            ui.add(egui::ProgressBar::new(self.progress()).show_percentage());
        } else if self.install_state == InstallState::Complete {
            ui.add_space(4.0);
            ui.add(egui::ProgressBar::new(1.0).show_percentage());
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
            "Install"
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
            .min_size(egui::vec2(280.0, 54.0))
            .fill(fill)
            .stroke(stroke);

        let response = ui.add_enabled(can_execute, button);
        if response.clicked() {
            self.start_install();
        }
    }

    fn show_hero(&mut self, ui: &mut egui::Ui) {
        if let Some(texture) = &self.seal_texture {
            let image = egui::Image::new(texture).fit_to_exact_size(egui::vec2(270.0, 270.0));
            ui.add(image);
        }

        ui.add_space(8.0);
        ui.group(|ui| {
            ui.heading("Authority baseline");
            ui.monospace("production_installer_ready=0");
            ui.monospace("root_authority=0");
            ui.monospace("network_authority=0");
            ui.monospace("runtime_enforcement_authority=0");
        });

        ui.add_space(8.0);
        ui.group(|ui| {
            ui.heading("Current mode");
            ui.monospace(self.config.execution_mode_label());
            if self.config.safety.dry_run {
                ui.label("The install button will execute validation and write a receipt only.");
            } else {
                ui.label("The install button will write a guarded user-local prefix layout.");
            }
        });
    }

    fn show_log_panel(&mut self, ui: &mut egui::Ui) {
        ui.heading("Install log");
        egui::ScrollArea::vertical()
            .id_source("latticra_install_log_scroll")
            .max_height(180.0)
            .stick_to_bottom(true)
            .show(ui, |ui| {
                if self.logs.is_empty() {
                    ui.monospace("No install run yet.");
                } else {
                    for line in &self.logs {
                        ui.monospace(line);
                    }
                }
            });
    }

    fn show_plan_panel(&mut self, ui: &mut egui::Ui) {
        self.config.safety.allow_network_effect = false;
        self.plan = render_plan(&self.config);
        ui.heading("Install plan preview");
        egui::ScrollArea::vertical()
            .id_source("latticra_install_plan_scroll")
            .max_height(240.0)
            .show(ui, |ui| {
                ui.monospace(&self.plan);
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
            ui.vertical_centered(|ui| {
                ui.label(egui::RichText::new("Install and manage Latticra components.").size(13.0));
            });
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            ui.add_space(8.0);

            ui.horizontal(|ui| {
                ui.vertical(|ui| {
                    self.show_hero(ui);
                });

                ui.add_space(18.0);

                ui.vertical(|ui| {
                    self.show_profile_and_components(ui);
                    ui.separator();
                    self.show_safety_and_behavior(ui);
                    ui.separator();
                    self.show_action_buttons(ui);
                });
            });

            ui.separator();
            self.show_log_panel(ui);
            ui.separator();
            self.show_plan_panel(ui);
        });
    }
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
            .with_inner_size([1040.0, 820.0])
            .with_min_inner_size([920.0, 700.0])
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
