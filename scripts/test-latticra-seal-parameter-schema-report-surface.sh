#!/usr/bin/env sh
set -eu

output="$(sh scripts/latticra-seal-parameter-schema-report.sh)"

require_output() {
  pattern="$1"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'seal parameter schema report surface: missing output: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_output 'LATTICRA SEAL PARAMETER SCHEMA'
require_output 'schema_profile=latticra-seal-parameter-schema/0.1'
require_output 'schema_id=unset'
require_output 'schema_version=unset'
require_output 'schema_language=unset'
require_output 'schema_hash=unset'
require_output 'schema_present=0'
require_output 'schema_parsing_supported=0'
require_output 'schema_validation_supported=0'
require_output 'schema_valid=0'
require_output 'max_input_bytes_declared=0'
require_output 'parameter_count_declared=0'
require_output 'required_parameter_count_declared=0'
require_output 'unknown_parameters_allowed=0'
require_output 'parameter_forwarding_allowed=0'
require_output 'input_size_within_limit=0'
require_output 'parameter_names_reported=0'
require_output 'runtime_authority_granted=0'
require_output 'host_read_performed=0'
require_output 'host_write_performed=0'
require_output 'network_performed=0'
require_output 'mode=report-only'
require_output 'decision=report-only'
require_output 'reason=parameter-schema-metadata-only'
require_output 'status=parameter-schema-metadata'

printf 'seal parameter schema report surface: ok\n'
