#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

fail() {
  printf 'latticra prevention surface consistency: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_field() {
  field="$1"
  file="$2"
  grep -Fqx -- "$field" "$file" || fail "missing field in $file: $field"
}

require_absent_field() {
  field="$1"
  file="$2"
  if grep -Fqx -- "$field" "$file"; then
    fail "unexpected field in $file: $field"
  fi
}

require_file src/latticra_cli.c

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-prevention-surface.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

bin="$tmpdir/latticra"
research="$tmpdir/research.out"
boundary="$tmpdir/boundary.out"
evidence="$tmpdir/evidence.out"
gate="$tmpdir/gate.out"
fixtures="$tmpdir/fixtures.out"
method="$tmpdir/method.out"

cc $CFLAGS src/latticra_cli.c -o "$bin"

"$bin" --prevention-research >"$research"
"$bin" --prevention-boundary >"$boundary"
"$bin" --prevention-evidence >"$evidence"
"$bin" --prevention-gate >"$gate"
"$bin" --prevention-fixtures >"$fixtures"

require_field 'prevention_method_count=16' "$research"
require_field 'boundary_count=8' "$boundary"
require_field 'fixture_set_count=16' "$fixtures"
require_field 'evidence_scope=application-owned-controls' "$evidence"
require_field 'LATTICRA PREVENTION GATE REPORT' "$gate"
require_field 'gate_scope=application-release-decision-support' "$gate"

for method_id in \
  sql sql-identifier nosql ldap xpath os-command program-argument xss ssrf path xml deserialization template log secret failure
do
  case "$method_id" in
    sql-identifier)
      research_field='method_sql_identifier=closed-allowlist-map'
      fixture_field='fixture_sql_identifier=unknown-name-and-reserved-word-rejection'
      ;;
    os-command)
      research_field='method_os_command=avoid-shell-use-fixed-argv'
      fixture_field='fixture_os_command=separator-and-option-smuggling-rejection'
      ;;
    program-argument)
      research_field='method_program_argument=option-allowlist-and-end-of-options-marker'
      fixture_field='fixture_program_argument=end-of-options-boundary'
      ;;
    *)
      method_key="$(printf '%s' "$method_id" | tr '-' '_')"
      research_field="method_${method_key}="
      fixture_field="fixture_${method_key}="
      ;;
  esac

  if ! grep -Fq -- "$research_field" "$research"; then
    fail "research report missing method field for $method_id"
  fi
  if ! grep -Fq -- "$fixture_field" "$fixtures"; then
    fail "fixture report missing fixture field for $method_id"
  fi

  "$bin" --prevention-method "$method_id" >"$method"
  require_field 'LATTICRA PREVENTION METHOD' "$method"
  require_field "method_id=$method_id" "$method"
  require_field 'host_mutation=0' "$method"
  require_field 'network=0' "$method"
  require_field 'host_scan=0' "$method"
  require_field 'production_protection_claim=0' "$method"
  require_field 'operator_visible_evidence_required=1' "$method"
done

require_field 'boundary_database=sql,sql-identifier,nosql,ldap,xpath' "$boundary"
require_field 'boundary_process=os-command,program-argument' "$boundary"
require_field 'boundary_browser=xss' "$boundary"
require_field 'boundary_server_fetch=ssrf' "$boundary"
require_field 'boundary_filesystem=path' "$boundary"
require_field 'boundary_parser=xml,deserialization,template' "$boundary"
require_field 'boundary_observability=log,secret' "$boundary"
require_field 'boundary_policy=failure' "$boundary"

require_field 'gate_unmapped_boundary_blocks_release=1' "$evidence"
require_field 'gate_missing_method_blocks_release=1' "$evidence"
require_field 'gate_missing_negative_fixture_blocks_release=1' "$evidence"
require_field 'gate_missing_safe_api_trace_blocks_release=1' "$evidence"
require_field 'gate_missing_owner_review_blocks_release=1' "$evidence"
require_field 'gate_missing_repeatability_blocks_release=1' "$evidence"
require_field 'gate_secret_capture_blocks_release=1' "$evidence"
require_field 'gate_production_claim_without_runtime_evidence_blocks_release=1' "$evidence"

require_field 'gate_default=block-until-evidence-complete' "$gate"
require_field 'gate_boundary_inventory_required=1' "$gate"
require_field 'gate_method_matrix_required=1' "$gate"
require_field 'gate_fixture_coverage_required=1' "$gate"
require_field 'gate_safe_api_trace_required=1' "$gate"
require_field 'gate_owner_review_required=1' "$gate"
require_field 'gate_repeatable_result_required=1' "$gate"
require_field 'gate_secret_redaction_required=1' "$gate"
require_field 'gate_fail_closed_result_required=1' "$gate"
require_field 'gate_new_boundary_review_required=1' "$gate"
require_field 'gate_runtime_evidence_required_for_protection_claim=1' "$gate"
require_field 'release_without_complete_evidence_allowed=0' "$gate"
require_field 'production_claim_without_runtime_evidence_allowed=0' "$gate"
require_field 'decision_authority=application-owner' "$gate"

require_field 'fixture_payload_strings_in_report=0' "$fixtures"
require_field 'fixture_safe_harness_required=1' "$fixtures"
require_field 'fixture_ci_gate_required=1' "$fixtures"
require_field 'fixture_regression_on_new_boundary_required=1' "$fixtures"

for output in "$research" "$boundary" "$evidence" "$gate" "$fixtures"; do
  require_field 'host_mutation=0' "$output"
  require_field 'network=0' "$output"
  require_field 'host_scan=0' "$output"
  require_field 'production_protection_claim=0' "$output"
done

require_absent_field 'production_protection_claim=1' "$research"
require_absent_field 'production_protection_claim=1' "$boundary"
require_absent_field 'production_protection_claim=1' "$evidence"
require_absent_field 'production_protection_claim=1' "$gate"
require_absent_field 'production_protection_claim=1' "$fixtures"

printf 'latticra_prevention_surface_consistency: ok\n'
