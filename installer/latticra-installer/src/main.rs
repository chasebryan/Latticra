mod config;
mod engine;
mod tui;
mod ui;

fn main() {
    let mut args = std::env::args().skip(1);
    let terminal_mode = args.any(|arg| {
        matches!(
            arg.as_str(),
            "--terminal" | "--tui" | "--config-terminal" | "terminal" | "tui"
        )
    });

    if terminal_mode {
        if let Err(err) = tui::run() {
            eprintln!("latticra terminal panel error: {err}");
            std::process::exit(1);
        }
        return;
    }

    if let Err(err) = ui::run() {
        eprintln!("latticra panel error: {err}");
        std::process::exit(1);
    }
}
