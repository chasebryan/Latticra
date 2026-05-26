# Latticra Quick Start Cheat Sheet

Audience: users who want the shortest safe path to install, run, update, and remove the current user-local Latticra Panel.

Status: Latticra is still early-stage and evidence-bound. The current installer is user-local. It does not install a root service, change the kernel, change systemd, change SELinux, or use network authority.

## Fast Install

Fedora prerequisites:

```sh
sudo dnf install -y rust cargo make gcc pkgconf-pkg-config \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel mesa-libGL-devel wayland-devel desktop-file-utils gtk3
```

Clone and enter the repo:

```sh
git clone https://github.com/Bryforge/Latticra.git
cd Latticra
```

Keep the user-local command path available:

```sh
export PATH="$HOME/.local/bin:$PATH"
```

Preview first:

```sh
make -C installer dry-run
```

Install and verify:

```sh
make -C installer local-example
make -C installer verify-local
```

## Run

Open the GUI:

```sh
latticra-panel
```

Launch it from a terminal and keep that terminal usable:

```sh
latticra-panel >/tmp/latticra-panel.log 2>&1 &
```

Useful commands:

```sh
latticra status
latticra path
latticra seal report
latticra lc status
```

## Update

From the source checkout:

```sh
git pull
make -C installer dry-run
make -C installer local-example
make -C installer verify-local
```

The installer migrates old Latticra-owned user-local wrappers when it can prove they are legacy Latticra files. Unrelated user files are still preserved or refused.

## Normal Reset Or Uninstall

Preview removal:

```sh
make -C installer uninstall-dry-run
make -C installer reset-dry-run
```

Remove the managed local install:

```sh
make -C installer uninstall-local
```

Or, from an installed wrapper:

```sh
latticra uninstall
```

Use reset when you plan to reinstall from new specs:

```sh
latticra reset
```

## Clean Full User-Local Uninstall

Use this only when normal uninstall/reset cannot clean up an old or broken user-local install.

These commands are intentionally exact. Do not replace them with broad paths such as `~/.local`, `/usr`, `/`, or unreviewed wildcards.

```sh
LATTICRA_PREFIX="${LATTICRA_PREFIX:-$HOME/.local/share/latticra}"

rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/latticra-lc" \
  "$HOME/.local/bin/lat" \
  "$HOME/.local/bin/latticra-seal" \
  "$HOME/.local/bin/latticra-nadia" \
  "$HOME/.local/bin/latticra-panel" \
  "$HOME/.local/bin/latticra-installer" \
  "$HOME/.local/share/applications/latticra-panel.desktop" \
  "$HOME/.local/share/applications/latticra-installer.desktop" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-panel.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-installer.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-seal.png"
```

If those paths are root-owned because an earlier command was run with `sudo`, repeat the same exact cleanup with `sudo`:

```sh
LATTICRA_PREFIX="${LATTICRA_PREFIX:-$HOME/.local/share/latticra}"

sudo rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

sudo rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/latticra-lc" \
  "$HOME/.local/bin/lat" \
  "$HOME/.local/bin/latticra-seal" \
  "$HOME/.local/bin/latticra-nadia" \
  "$HOME/.local/bin/latticra-panel" \
  "$HOME/.local/bin/latticra-installer" \
  "$HOME/.local/share/applications/latticra-panel.desktop" \
  "$HOME/.local/share/applications/latticra-installer.desktop" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-panel.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-installer.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-seal.png"
```

Refresh the shell command cache after cleanup:

```sh
hash -r 2>/dev/null || true
```

## Important Limits

- Current install scope is user-local under `~/.local`.
- Dry-run first, then install.
- Latticra currently remains early-stage and evidence-bound.
- No production security boundary, root installer, system service, kernel integration, or network authority is claimed.
