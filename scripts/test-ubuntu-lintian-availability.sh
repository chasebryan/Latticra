#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu lintian availability: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu lintian availability: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

apt_install() {
  if [ "$(id -u)" -eq 0 ]; then
    apt-get update
    env DEBIAN_FRONTEND=noninteractive apt-get install -y "$@"
  elif command -v sudo >/dev/null 2>&1; then
    sudo apt-get update
    sudo env DEBIAN_FRONTEND=noninteractive apt-get install -y "$@"
  else
    printf 'ubuntu lintian availability: apt install requires root or sudo\n' >&2
    exit 1
  fi
}

require_file docs/UBUNTU_LINTIAN_AVAILABILITY.md
require_file docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
require_file scripts/test-ubuntu-local-deb-static-validation.sh
require_file packaging/ubuntu/debian/control

require_contains 'Status: active tool availability lane' docs/UBUNTU_LINTIAN_AVAILABILITY.md
require_contains 'lintian installs' docs/UBUNTU_LINTIAN_AVAILABILITY.md
require_contains 'does not lint the Latticra deb draft yet' docs/UBUNTU_LINTIAN_AVAILABILITY.md
require_contains 'does not run `dpkg-buildpackage`, `debuild`, `sbuild`, or `pbuilder`' docs/UBUNTU_LINTIAN_AVAILABILITY.md
require_contains 'does not create package artifacts' docs/UBUNTU_LINTIAN_AVAILABILITY.md
require_contains 'Add Ubuntu lintian static debian metadata lane after license expression review' docs/UBUNTU_LINTIAN_AVAILABILITY.md
require_contains 'ubuntu_lintian_availability: ok' docs/UBUNTU_LINTIAN_AVAILABILITY.md

if [ ! -r /etc/os-release ] || ! grep -Eq '^(ID=ubuntu|ID_LIKE=.*ubuntu)' /etc/os-release; then
  printf 'ubuntu lintian availability: expected Ubuntu environment\n' >&2
  exit 1
fi

command -v apt-get >/dev/null 2>&1

apt_install lintian
command -v lintian >/dev/null 2>&1
lintian --version >/dev/null 2>&1

sh scripts/test-ubuntu-local-deb-static-validation.sh

printf 'ubuntu_lintian_availability: ok\n'
