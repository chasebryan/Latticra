#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-seal-panel-dashboard-view-model.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_panel_dashboard_view_model.c \
  tests/seal_panel_dashboard_view_model_surface.c \
  -o "$tmpdir/latticra-seal-panel-dashboard-view-model"

"$tmpdir/latticra-seal-panel-dashboard-view-model"
