from pathlib import Path

ui = Path("installer/latticra-installer/src/ui.rs")
readme = Path("installer/README.md")

checks = [
    (ui, 'const PANEL_BUILD: &str = "gui-workbench";', 'build identity'),
    (ui, 'const SEAL_PNG: &[u8] = include_bytes!("../assets/latticra-panel.png");', 'embedded image'),
    (ui, 'fn ensure_texture(&mut self, ctx: &egui::Context)', 'texture function'),
    (ui, 'fn show_sidebar(&mut self, ui: &mut egui::Ui)', 'sidebar function'),
    (ui, 'fn show_main_workbench(&mut self, ui: &mut egui::Ui)', 'main workbench'),
    (ui, 'fn show_delivery(&mut self, ui: &mut egui::Ui)', 'delivery function'),
    (ui, 'fn show_fluid_install_button(&mut self, ui: &mut egui::Ui)', 'install button'),
    (ui, 'fn show_console_panel(&mut self, ui: &mut egui::Ui)', 'console function'),
    (ui, 'fn show_right_evidence_panel(&mut self, ui: &mut egui::Ui)', 'right evidence'),
    (ui, 'fn blend(a: egui::Color32, b: egui::Color32, t: f32) -> egui::Color32', 'blend helper'),
    (ui, 'WorkspaceTab::Dashboard', 'dashboard tab'),
    (ui, 'WorkspaceTab::Components', 'components tab'),
    (ui, 'WorkspaceTab::Seal', 'seal tab'),
    (ui, 'WorkspaceTab::Authority', 'authority tab'),
    (ui, 'WorkspaceTab::Delivery', 'delivery tab'),
    (ui, 'WorkspaceTab::Evidence', 'evidence tab'),
    (ui, 'WorkspaceTab::Procedure', 'procedure tab'),
    (ui, 'egui::SidePanel::left("left_workbench_nav")', 'left panel'),
    (ui, 'egui::SidePanel::right("right_console")', 'right panel'),
    (ui, 'egui::CentralPanel::default()', 'central panel'),
    (ui, '.default_width(680.0)', 'right width'),
    (ui, '.min_width(500.0)', 'right minimum width'),
    (ui, '.with_inner_size([1600.0, 960.0])', 'window size'),
    (ui, '.with_min_inner_size([1100.0, 720.0])', 'minimum window size'),
    (ui, '.with_maximized(true)', 'maximized launch'),
    (readme, '## Embedded Latticra Console', 'README console section'),
    (readme, '## Safety baseline', 'README safety section'),
]

for path, needle, label in checks:
    content = path.read_text()
    if needle not in content:
        raise SystemExit(f"FAIL: missing {label}: {needle}")
    print(f"PASS: {label}")

print("STATUS: PASS")
print("Latticra Panel UI design checkpoint preserved.")
