#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse local rpm static validation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse local rpm static validation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse local rpm static validation: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent_section() {
  section="$1"
  file="$2"
  if grep -Eq "^[[:space:]]*${section}([[:space:]]|$)" "$file"; then
    printf 'opensuse local rpm static validation: unexpected section in %s: %s\n' "$file" "$section" >&2
    exit 1
  fi
}

require_file docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_file docs/OPENSUSE_READINESS_PLAN.md
require_file docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_file docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_file docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/opensuse/README.md
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes
require_file scripts/test-latticra-no-effect-cli-status-surface.sh
require_file src/latticra_cli.c

require_contains 'Status: active static validation lane' docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'static checks for the local-only openSUSE RPM packaging draft' docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'does not run `rpmbuild`, `osc build`, `rpmlint`, `spec-cleaner`, or `zypper install`' docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'no Open Build Service publication claim is made' docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md' docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md' docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'Add openSUSE rpmlint findings classification report' docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_contains 'opensuse_local_rpm_static_validation: ok' docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md

require_contains 'Status: local-only packaging draft' packaging/opensuse/README.md
require_contains 'not an official openSUSE package' packaging/opensuse/README.md
require_contains 'not SUSE endorsement evidence' packaging/opensuse/README.md
require_contains 'not Open Build Service publication evidence' packaging/opensuse/README.md
require_contains 'opensuse_rpmlint_osc_availability_lane_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpmlint_static_spec_lane_present=1' packaging/opensuse/README.md
require_contains 'rpm_artifact_created=0' packaging/opensuse/README.md
require_contains 'osc_build_run=0' packaging/opensuse/README.md
require_contains 'accepted_rpmlint_transcript_present=0' packaging/opensuse/README.md
require_contains 'rpmlint_package_readiness_claimed=0' packaging/opensuse/README.md
require_contains 'opensuse_obs_publication_claimed=0' packaging/opensuse/README.md
require_contains 'opensuse_official_package_claimed=0' packaging/opensuse/README.md
require_contains 'suse_endorsement_claimed=0' packaging/opensuse/README.md

require_contains 'LOCAL-ONLY openSUSE DRAFT' packaging/opensuse/latticra.spec
require_contains 'Name:           latticra' packaging/opensuse/latticra.spec
require_contains 'Version:        0.0.0' packaging/opensuse/latticra.spec
require_contains 'Release:        0.local' packaging/opensuse/latticra.spec
require_contains 'Summary:        Contract-first systems architecture and language project' packaging/opensuse/latticra.spec
require_contains 'License:        LicenseRef-Latticra-TBD' packaging/opensuse/latticra.spec
require_contains 'URL:            https://github.com/Bryforge/Latticra' packaging/opensuse/latticra.spec
require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/opensuse/latticra.spec
require_contains 'BuildRequires:  gcc' packaging/opensuse/latticra.spec
require_contains 'BuildRequires:  make' packaging/opensuse/latticra.spec
require_contains '%description' packaging/opensuse/latticra.spec
require_contains '%prep' packaging/opensuse/latticra.spec
require_contains '%build' packaging/opensuse/latticra.spec
require_contains '%install' packaging/opensuse/latticra.spec
require_contains '%files' packaging/opensuse/latticra.spec
require_contains '%changelog' packaging/opensuse/latticra.spec
require_contains 'sh scripts/test-state-lattice.sh' packaging/opensuse/latticra.spec
require_contains 'sh scripts/test-system-bootstrap.sh' packaging/opensuse/latticra.spec
require_contains 'sh scripts/test-kernel.sh' packaging/opensuse/latticra.spec
require_contains 'sh scripts/test-kernel-lifecycle.sh' packaging/opensuse/latticra.spec
require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' packaging/opensuse/latticra.spec
require_contains 'cc %{optflags} -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra' packaging/opensuse/latticra.spec
require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' packaging/opensuse/latticra.spec
require_contains 'install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md' packaging/opensuse/latticra.spec
require_contains '%{_bindir}/latticra' packaging/opensuse/latticra.spec
require_contains '%doc %{_docdir}/%{name}/README.md' packaging/opensuse/latticra.spec

require_contains 'Add local-only openSUSE RPM packaging draft' packaging/opensuse/latticra.changes
require_contains 'Open Build Service publication' packaging/opensuse/latticra.changes
require_contains 'official package' packaging/opensuse/latticra.changes
require_contains 'SUSE endorsement' packaging/opensuse/latticra.changes

require_contains 'LATTICRA STATUS REPORT' src/latticra_cli.c
require_contains 'mode=no-effect' src/latticra_cli.c
require_contains 'runtime_behavior=disabled' src/latticra_cli.c

require_absent 'BuildArch:      noarch' packaging/opensuse/latticra.spec
require_absent_section '%pre' packaging/opensuse/latticra.spec
require_absent_section '%post' packaging/opensuse/latticra.spec
require_absent_section '%preun' packaging/opensuse/latticra.spec
require_absent_section '%postun' packaging/opensuse/latticra.spec
require_absent '.service' packaging/opensuse/latticra.spec
require_absent 'systemctl' packaging/opensuse/latticra.spec
require_absent '/usr/lib/systemd/system' packaging/opensuse/latticra.spec
require_absent '/usr/lib/modules' packaging/opensuse/latticra.spec
require_absent '/boot/latticra' packaging/opensuse/latticra.spec
require_absent '/usr/share/selinux' packaging/opensuse/latticra.spec
require_absent '/etc/latticra' packaging/opensuse/latticra.spec

printf 'opensuse_local_rpm_static_validation: ok\n'
