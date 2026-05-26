.PHONY: help gui panel build-gui build-panel dry-run lc-standalone-dry-run standalone-dry-run lc-standalone-local standalone-local local-example install-local verify-local verify-lc-standalone verify-standalone uninstall-local reset-local uninstall-dry-run reset-dry-run fmt tree clean refresh-desktop

INSTALLER_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
GUI_DIR := $(INSTALLER_DIR)latticra-installer
SCRIPT_DIR := $(INSTALLER_DIR)scripts
CONFIG_DIR := $(INSTALLER_DIR)configs
PLAN := $(INSTALLER_DIR)latticra-installer-plan.txt
RECEIPTS := $(INSTALLER_DIR)latticra-installer-receipts

help:
	@printf "%s\n" \
	  "Latticra Panel commands:" \
	  "  make -C installer gui             Run Latticra Panel from source" \
	  "  make -C installer panel           Same as gui" \
	  "  make -C installer build-gui       Build Latticra Panel release binary" \
	  "  make -C installer build-panel     Same as build-gui" \
	  "  make -C installer dry-run         Run guarded dry-install through the real engine" \
	  "  make -C installer lc-standalone-dry-run Preview standalone LC install" \
	  "  make -C installer lc-standalone-local   Run guarded standalone LC local install" \
	  "  make -C installer local-example   Run actual guarded user-local install" \
	  "  make -C installer install-local   Same as local-example" \
	  "  make -C installer verify-local    Verify the local install" \
	  "  make -C installer verify-lc-standalone Verify standalone LC local install" \
	  "  make -C installer reset-local     Reset managed local install for reinstall" \
	  "  make -C installer uninstall-local Uninstall managed local install" \
	  "  make -C installer reset-dry-run   Preview managed local reset" \
	  "  make -C installer uninstall-dry-run Preview managed local uninstall" \
	  "  make -C installer refresh-desktop Refresh user-local desktop metadata" \
	  "  make -C installer fmt             Format Rust panel code" \
	  "  make -C installer tree            Show installer tree" \
	  "  make -C installer clean           Remove generated local installer receipts/plans"

gui panel:
	cd "$(GUI_DIR)" && LATTICRA_INSTALLER_ROOT="$(INSTALLER_DIR)" cargo run --locked

build-gui build-panel:
	cd "$(GUI_DIR)" && cargo build --release --locked

dry-run:
	sh "$(SCRIPT_DIR)/latticra-installer-apply.sh" \
	  --config "$(CONFIG_DIR)/default.installer.toml" \
	  --plan "$(PLAN)" \
	  --receipt-dir "$(RECEIPTS)"

lc-standalone-dry-run standalone-dry-run:
	sh "$(SCRIPT_DIR)/latticra-installer-apply.sh" \
	  --config "$(CONFIG_DIR)/lc-standalone.installer.toml" \
	  --plan "$(PLAN)" \
	  --receipt-dir "$(RECEIPTS)"

lc-standalone-local standalone-local:
	sh "$(SCRIPT_DIR)/latticra-installer-apply.sh" \
	  --config "$(CONFIG_DIR)/lc-standalone-local.installer.toml" \
	  --plan "$(PLAN)" \
	  --receipt-dir "$(RECEIPTS)"

local-example install-local:
	sh "$(SCRIPT_DIR)/latticra-installer-apply.sh" \
	  --config "$(CONFIG_DIR)/local-prefix-example.installer.toml" \
	  --plan "$(PLAN)" \
	  --receipt-dir "$(RECEIPTS)"

verify-local:
	sh "$(SCRIPT_DIR)/latticra-installer-verify.sh" \
	  --prefix "$(HOME)/.local/share/latticra"

verify-lc-standalone verify-standalone:
	sh "$(SCRIPT_DIR)/latticra-installer-verify-lc-standalone.sh" \
	  --prefix "$(HOME)/.local/share/latticra"

uninstall-local:
	sh "$(SCRIPT_DIR)/latticra-installer-uninstall.sh" \
	  --prefix "$(HOME)/.local/share/latticra" \
	  --receipt-dir "$(RECEIPTS)" \
	  --operation uninstall

reset-local:
	sh "$(SCRIPT_DIR)/latticra-installer-uninstall.sh" \
	  --prefix "$(HOME)/.local/share/latticra" \
	  --receipt-dir "$(RECEIPTS)" \
	  --operation reset

uninstall-dry-run:
	sh "$(SCRIPT_DIR)/latticra-installer-uninstall.sh" \
	  --prefix "$(HOME)/.local/share/latticra" \
	  --receipt-dir "$(RECEIPTS)" \
	  --operation uninstall \
	  --dry-run

reset-dry-run:
	sh "$(SCRIPT_DIR)/latticra-installer-uninstall.sh" \
	  --prefix "$(HOME)/.local/share/latticra" \
	  --receipt-dir "$(RECEIPTS)" \
	  --operation reset \
	  --dry-run

refresh-desktop:
	@if command -v update-desktop-database >/dev/null 2>&1; then update-desktop-database "$(HOME)/.local/share/applications" >/dev/null 2>&1 || true; fi
	@if command -v gtk-update-icon-cache >/dev/null 2>&1; then gtk-update-icon-cache -q "$(HOME)/.local/share/icons/hicolor" >/dev/null 2>&1 || true; fi
	@printf "%s\n" "Refreshed user-local desktop metadata."

fmt:
	cd "$(GUI_DIR)" && cargo fmt

tree:
	cat "$(INSTALLER_DIR)TREE.txt"

clean:
	rm -rf "$(RECEIPTS)" "$(PLAN)"
