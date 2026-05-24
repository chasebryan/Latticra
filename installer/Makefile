.RECIPEPREFIX := >
.PHONY: help gui panel terminal tui build-gui build-panel dry-run local-example install-local verify-local uninstall-local fmt tree clean refresh-desktop

INSTALLER_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
GUI_DIR := $(INSTALLER_DIR)latticra-installer
SCRIPT_DIR := $(INSTALLER_DIR)scripts
CONFIG_DIR := $(INSTALLER_DIR)configs
PLAN := $(INSTALLER_DIR)latticra-installer-plan.txt
RECEIPTS := $(INSTALLER_DIR)latticra-installer-receipts

help:
>@printf "%s\n" \
>  "Latticra Panel commands:" \
>  "  make -C installer gui             Run Latticra Panel GUI from source" \
>  "  make -C installer panel           Same as gui" \
>  "  make -C installer terminal        Run terminal configuration panel from source" \
>  "  make -C installer tui             Same as terminal" \
>  "  make -C installer build-gui       Build Latticra Panel release binary" \
>  "  make -C installer build-panel     Same as build-gui" \
>  "  make -C installer dry-run         Run guarded dry-install through the real engine" \
>  "  make -C installer local-example   Run actual guarded user-local install" \
>  "  make -C installer install-local   Same as local-example" \
>  "  make -C installer verify-local    Verify the local install" \
>  "  make -C installer uninstall-local Remove managed local install" \
>  "  make -C installer refresh-desktop Refresh user-local desktop metadata" \
>  "  make -C installer fmt             Format Rust panel code" \
>  "  make -C installer tree            Show installer tree" \
>  "  make -C installer clean           Remove generated local installer receipts/plans"

gui panel:
>cd "$(GUI_DIR)" && LATTICRA_INSTALLER_ROOT="$(INSTALLER_DIR)" cargo run

terminal tui:
>cd "$(GUI_DIR)" && LATTICRA_INSTALLER_ROOT="$(INSTALLER_DIR)" cargo run -- --terminal

build-gui build-panel:
>cd "$(GUI_DIR)" && cargo build --release

dry-run:
>sh "$(SCRIPT_DIR)/latticra-installer-apply.sh" \
>  --config "$(CONFIG_DIR)/default.installer.toml" \
>  --plan "$(PLAN)" \
>  --receipt-dir "$(RECEIPTS)"

local-example install-local:
>sh "$(SCRIPT_DIR)/latticra-installer-apply.sh" \
>  --config "$(CONFIG_DIR)/local-prefix-example.installer.toml" \
>  --plan "$(PLAN)" \
>  --receipt-dir "$(RECEIPTS)"

verify-local:
>sh "$(SCRIPT_DIR)/latticra-installer-verify.sh" \
>  --prefix "$(HOME)/.local/share/latticra"

uninstall-local:
>sh "$(SCRIPT_DIR)/latticra-installer-uninstall.sh" \
>  --prefix "$(HOME)/.local/share/latticra"

refresh-desktop:
>@if command -v update-desktop-database >/dev/null 2>&1; then update-desktop-database "$(HOME)/.local/share/applications" >/dev/null 2>&1 || true; fi
>@if command -v gtk-update-icon-cache >/dev/null 2>&1; then gtk-update-icon-cache -q "$(HOME)/.local/share/icons/hicolor" >/dev/null 2>&1 || true; fi
>@printf "%s\n" "Refreshed user-local desktop metadata."

fmt:
>cd "$(GUI_DIR)" && cargo fmt

tree:
>cat "$(INSTALLER_DIR)TREE.txt"

clean:
>rm -rf "$(RECEIPTS)" "$(PLAN)"
