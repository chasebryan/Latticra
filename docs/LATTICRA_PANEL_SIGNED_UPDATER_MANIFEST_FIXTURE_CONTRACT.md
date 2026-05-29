# Latticra Panel Signed Updater Manifest Fixture Contract

Status: local no-effect signed updater manifest fixture contract
Date: 2026-05-26 CDT
Scope: local fixture contract for future signed updater manifest work behind the Latticra Panel updater.

## Purpose

This slice adds a committed local manifest fixture for the Panel signed updater lane.

The fixture gives the closed delivery gate a concrete manifest-shaped record to review without making it trusted signed update evidence, enabling network fetch, verifying artifacts, staging updates, writing receipts, or applying updates.

```text
signed_updater_manifest_fixture_contract_present=1
signed_updater_manifest_fixture_present=1
manifest_fixture_effect=none
manifest_fixture_trusted_for_apply=0
trusted_signed_manifest_present=0
signed_update_apply_allowed=0
```

## Fixture

The fixture lives at:

```text
fixtures/latticra-panel/signed-updater-manifest.fixture.toml
```

It records the current local-checkout updater shape:

```text
update_id=panel-local-checkout-fixture
update_channel=lab
source_strategy=current-source-checkout
apply_mode=guarded-local-prefix-reinstall
target_component=latticra-panel
target_version=fixture-only
```

## Command

```sh
sh scripts/latticra-panel-signed-updater-manifest-fixture-contract.sh
```

The command writes only a deterministic report to stdout.

## Trust Boundary

The fixture is explicitly not trusted for apply:

```text
signed_updater_delivery_gate_state=closed
signed_manifest_present=0
trusted_signed_manifest_present=0
manifest_signature_verified=0
artifact_hash_verified=0
artifact_signature_verified=0
rollback_plan_present=0
operator_confirmation_observed=0
update_receipt_written=0
signed_update_apply_allowed=0
```

The authority boundary remains closed:

```text
network_fetch_authority=0
network_fetch_attempted=0
remote_update_repository_trust=0
updater_network_fetch_enabled=0
staged_update_performed=0
signed_update_apply_performed=0
host_mutation_performed=0
root_authority=0
system_mutation_authority=0
production_update_ready=0
```

## Validation

This contract is guarded by:

```sh
sh scripts/test-latticra-panel-signed-updater-manifest-fixture-contract.sh
```

Expected output:

```text
latticra_panel_signed_updater_manifest_fixture_contract: ok
```

## Next Recommended Lane

```text
Add Panel signed-updater state transition denial disposition closeout audit review disposition review closeout without enabling transition execution or update apply.
```

## Non-Claims

This contract is not signed update evidence, network update evidence, update-server evidence, trusted repository evidence, artifact-verification evidence, rollback evidence, receipt evidence, production update readiness, production installer readiness, root installer readiness, kernel integration, systemd integration, SELinux integration, runtime enforcement, malware prevention, ransomware prevention, sandboxing, or a production security-product claim.
