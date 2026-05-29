#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

sh scripts/test-fedora-local-rpm-static-validation.sh

printf 'fedora_spec_static: ok\n'
