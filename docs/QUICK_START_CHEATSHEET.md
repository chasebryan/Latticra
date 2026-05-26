# Latticra Quick Start Cheat Sheet

Audience: users who want the shortest safe path to install, run, update, and remove the current user-local Latticra Panel.

Status: Latticra is still early-stage and evidence-bound. The current installer is user-local. It does not install a root service, change the kernel, change systemd, change SELinux, or use network authority.

## Fast Install

Ubuntu prerequisites:

```sh
sudo apt-get update
sudo apt-get install -y rustc cargo make gcc pkg-config \
  libx11-dev libxcb1-dev libxcursor-dev libxrandr-dev libxi-dev \
  libxkbcommon-dev libgl1-mesa-dev libwayland-dev desktop-file-utils \
  libgtk-3-bin
```

Fedora prerequisites:

```sh
sudo dnf install -y rust cargo make gcc pkgconf-pkg-config \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel mesa-libGL-devel wayland-devel desktop-file-utils gtk3
```

openSUSE prerequisites:

```sh
sudo zypper refresh
sudo zypper install -y rust cargo make gcc pkgconf \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel Mesa-libGL-devel wayland-devel desktop-file-utils \
  gtk3-tools
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

Ubuntu no-effect validation:

```sh
sh scripts/test-ubuntu-build-lane.sh
sh scripts/test-ubuntu-developer-workflow.sh
sh scripts/test-ubuntu-package-notice-inventory.sh
sh scripts/test-ubuntu-doc-payload-license-review-contract.sh
sh scripts/test-ubuntu-third-party-material-review-contract.sh
sh scripts/test-ubuntu-generated-artifact-notice-review-contract.sh
sh scripts/test-ubuntu-notice-file-decision-contract.sh
sh scripts/test-ubuntu-debian-copyright-notice-mapping-contract.sh
sh scripts/test-ubuntu-trademark-notice-boundary-contract.sh
```

openSUSE no-effect validation:

```sh
sh scripts/test-opensuse-developer-workflow.sh
sh scripts/test-opensuse-local-rpm-static-validation.sh
```

openSUSE tool availability validation:

```sh
sh scripts/test-opensuse-rpmlint-osc-availability.sh
sh scripts/test-opensuse-rpmlint-static-spec-lane.sh
sh scripts/test-opensuse-rpmlint-findings-classification.sh
```

## Run

Open the GUI:

```sh
latticra-panel
```

Launch it from a terminal and keep that terminal usable:

```sh
tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-panel.XXXXXX")"
latticra-panel >"$tmpdir/latticra-panel.log" 2>&1 &
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
latticra-panel
```

Use the **Updater** workspace in Latticra Panel. Preview the update first, then apply the guarded user-local update from the current checkout. The installer migrates old Latticra-owned user-local wrappers when it can prove they are legacy Latticra files. Unrelated user files are still preserved or refused.

```sh
latticra updater status
```

This prints the Panel-owned updater policy, including the dry-run/apply commands, guarded apply mode, receipt setting, and disabled network/root/system mutation authority.

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

If LC was installed with a custom `lc.install.command_wrapper`, set `LC_WRAPPER` to that command name; the default is `latticra-lc`.

```sh
LATTICRA_PREFIX="${LATTICRA_PREFIX:-$HOME/.local/share/latticra}"
LC_WRAPPER="${LC_WRAPPER:-latticra-lc}"

rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/$LC_WRAPPER" \
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
LC_WRAPPER="${LC_WRAPPER:-latticra-lc}"

sudo rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

sudo rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/$LC_WRAPPER" \
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
- No production security boundary, root installer, system service, kernel integration, Ubuntu archive/PPA readiness, or network authority is claimed.
