# Latticra Panel

Graphical and terminal installer/control panel for Latticra, Lat, LIR, and Latticra Seal.

## Prerequisites

Fedora:

```sh
sudo dnf install -y rust cargo make gcc pkgconf-pkg-config \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel mesa-libGL-devel wayland-devel desktop-file-utils gtk3
```

User-local command path:

```sh
export PATH="$HOME/.local/bin:$PATH"
```

## Run the GUI from source

```sh
make -C installer gui
```

## Run the terminal panel from source

```sh
make -C installer terminal
```

Equivalent direct command:

```sh
cd installer/latticra-installer
LATTICRA_INSTALLER_ROOT="$PWD/.." cargo run -- --terminal
```

## Dry-run

```sh
make -C installer dry-run
```

## Install locally

```sh
make -C installer local-example
```

## Verify

```sh
make -C installer verify-local
```

## Open after install

```sh
latticra-panel
```

For the terminal configuration panel:

```sh
latticra-panel --terminal
```

Or from the desktop app grid, open **Latticra Panel**.

## Installed paths

```text
~/.local/bin/latticra
~/.local/bin/lat
~/.local/bin/latticra-seal
~/.local/bin/latticra-panel
~/.local/share/applications/latticra-panel.desktop
~/.local/share/icons/hicolor/256x256/apps/latticra-panel.png
~/.local/share/latticra
```

## Uninstall managed local install

```sh
make -C installer uninstall-local
```

## Safety baseline

```text
no root
no kernel mutation
no systemd mutation
no SELinux mutation
no network authority
user-local prefix only
```
