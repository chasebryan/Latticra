from pathlib import Path

ui = Path("installer/latticra-installer/src/ui.rs")
readme = Path("installer/README.md")
cargo_toml = Path("installer/latticra-installer/Cargo.toml")
components_manifest = Path("installer/manifests/components.toml")

checks = [
    (cargo_toml, 'version = "1.0.0"', 'Panel v1.0.0 package version'),
    (components_manifest, 'version = "1.0.0"', 'Panel v1.0.0 component manifest'),
    (ui, 'const PANEL_BUILD: &str = "gui-workbench";', 'build identity'),
    (ui, 'const SEAL_PNG: &[u8] = include_bytes!("../assets/latticra-panel.png");', 'embedded image'),
    (ui, 'fn ensure_texture(&mut self, ctx: &egui::Context)', 'texture function'),
    (ui, 'fn show_sidebar(&mut self, ui: &mut egui::Ui, compact: bool)', 'sidebar function'),
    (ui, 'fn show_main_workbench(&mut self, ui: &mut egui::Ui, compact: bool)', 'main workbench'),
    (ui, 'fn show_delivery(&mut self, ui: &mut egui::Ui)', 'delivery function'),
    (ui, 'fn show_fluid_install_button(&mut self, ui: &mut egui::Ui)', 'install button'),
    (ui, 'fn show_console_panel(&mut self, ui: &mut egui::Ui)', 'console function'),
    (ui, 'fn show_right_evidence_panel(&mut self, ui: &mut egui::Ui)', 'right evidence'),
    (ui, 'fn show_install_run_monitor(&mut self, ui: &mut egui::Ui, compact: bool)', 'install run monitor'),
    (ui, 'const COMPACT_LAYOUT_WIDTH: f32 = 1600.0;', 'less crowded responsive rail threshold'),
    (ui, 'fn show_hero_primary_actions(&mut self, ui: &mut egui::Ui)', 'first-screen primary actions'),
    (ui, 'Plan first. Dry-run second. Install after evidence.', 'first-screen purpose copy'),
    (ui, 'fn chip_value_width(value: &str) -> f32', 'bounded readable status chips'),
    (ui, 'fn show_bounded_install_progress(&self, ui: &mut egui::Ui, max_width: f32)', 'bounded install progress'),
    (ui, 'fn show_recent_engine_output(&self, ui: &mut egui::Ui, max_lines: usize, max_height: f32)', 'recent engine output surface'),
    (ui, 'fn show_engine_log_lines(&self, ui: &mut egui::Ui, max_lines: usize)', 'shared engine log renderer'),
    (ui, 'RUNNING_EVIDENCE_MAX_HEIGHT', 'running evidence priority'),
    (ui, 'RUNNING_CONSOLE_MAX_HEIGHT', 'running console restraint'),
    (ui, 'RUNNING_PROGRESS_MAX_WIDTH', 'running progress restraint'),
    (ui, 'RUNNING_RECENT_LOG_MAX_HEIGHT', 'running recent log restraint'),
    (ui, 'RUNNING_MONITOR_WIDE_WIDTH', 'running monitor wide layout'),
    (ui, 'self.show_plan_over_log = false;', 'engine log focus'),
    (ui, 'if self.install_state != InstallState::Running', 'running console quick-command restraint'),
    (ui, 'egui::ScrollArea::both()', 'non-wrapping engine log scroll'),
    (ui, 'fn blend(a: egui::Color32, b: egui::Color32, t: f32) -> egui::Color32', 'blend helper'),
    (ui, 'WorkspaceTab::Dashboard', 'dashboard tab'),
    (ui, 'WorkspaceTab::Components', 'components tab'),
    (ui, 'WorkspaceTab::Seal', 'seal tab'),
    (ui, 'WorkspaceTab::Authority', 'authority tab'),
    (ui, 'WorkspaceTab::Delivery', 'delivery tab'),
    (ui, 'WorkspaceTab::Updater', 'updater tab'),
    (ui, 'fn show_updater(&mut self, ui: &mut egui::Ui)', 'updater function'),
    (ui, 'LC install configuration', 'LC install configuration section'),
    (ui, 'lc install-config', 'LC install-config command'),
    (ui, 'WorkspaceTab::Evidence', 'evidence tab'),
    (ui, 'WorkspaceTab::Procedure', 'procedure tab'),
    (ui, 'egui::Panel::left("left_workbench_nav")', 'left panel'),
    (ui, 'egui::Panel::right("right_console")', 'right panel'),
    (ui, 'egui::CentralPanel::default()', 'central panel'),
    (ui, '.default_size(560.0)', 'right width'),
    (ui, '.min_size(360.0)', 'right minimum width'),
    (ui, '.with_inner_size([1280.0, 820.0])', 'window size'),
    (ui, '.with_min_inner_size([760.0, 560.0])', 'minimum window size'),
    (ui, '.with_maximized(true)', 'maximized launch'),
    (ui, 'fn deny_console_command(&mut self, command: &str)', 'console boundary function'),
    (ui, 'Panel commands and local navigation only.', 'console boundary label'),
    (ui, 'command outside panel allowlist', 'console blocked-message surface'),
    (readme, '## Embedded Latticra Console', 'README console section'),
    (readme, '## Safety baseline', 'README safety section'),
]

for path, needle, label in checks:
    content = path.read_text()
    if needle not in content:
        raise SystemExit(f"FAIL: missing {label}: {needle}")
    print(f"PASS: {label}")

ui_content = ui.read_text()
if 'self.push_console(line);' in ui_content:
    raise SystemExit("FAIL: engine log lines must remain in live evidence instead of mirroring into the console")
print("PASS: engine logs stay in live evidence")

print("STATUS: PASS")
print("Latticra Panel UI design checkpoint preserved.")
