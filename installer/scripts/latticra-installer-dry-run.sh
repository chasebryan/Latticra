#!/usr/bin/env sh
set -eu
SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
INSTALLER_DIR=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
exec sh "$SCRIPT_DIR/latticra-installer-apply.sh" \
  --config "$INSTALLER_DIR/configs/default.installer.toml" \
  --plan "$INSTALLER_DIR/latticra-installer-plan.txt" \
  --receipt-dir "$INSTALLER_DIR/latticra-installer-receipts"
