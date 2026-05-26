#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

present() {
  if [ -e "$1" ]; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

contains() {
  pattern="$1"
  file="$2"
  if [ -f "$file" ] && grep -Fq -- "$pattern" "$file"; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

notice_present="$(present NOTICE)"
cli_spdx_present="$(contains 'SPDX-License-Identifier: AGPL-3.0-or-later' src/latticra_cli.c)"
debian_copyright_present="$(present packaging/ubuntu/debian/copyright)"
debian_tbd_present="$(contains 'LicenseRef-Latticra-TBD' packaging/ubuntu/debian/copyright)"

cat <<REPORT
UBUNTU PACKAGE NOTICE INVENTORY
inventory_status=ok
inventory_mode=no-effect
package_scope=local-deb-draft
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
binary_payload_source_present=$(present src/latticra_cli.c)
binary_payload_spdx_present=$cli_spdx_present
binary_payload_spdx=AGPL-3.0-or-later
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
doc_payload_source_present=$(present README.md)
doc_payload_license_reviewed=0
doc_payload_license_unresolved=1
root_license_file=LICENSE
root_license_present=$(present LICENSE)
root_license_current=Apache-2.0
notice_file_present=$notice_present
notice_file_decision_recorded=0
third_party_material_inventory_recorded=1
third_party_material_inventory_reviewed=0
third_party_material_missing_entries=0
generated_artifact_notice_reviewed=0
trademark_policy_present=$(present TRADEMARK_POLICY.md)
trademark_notice_boundary_recorded=1
debian_copyright_file=packaging/ubuntu/debian/copyright
debian_copyright_present=$debian_copyright_present
debian_copyright_license_ref_tbd=$debian_tbd_present
debian_copyright_notice_mapping_reviewed=0
packaging_license_expression_updated=0
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
host_mutation=0
network=0
package_build_performed=0
package_publish_performed=0
REPORT
