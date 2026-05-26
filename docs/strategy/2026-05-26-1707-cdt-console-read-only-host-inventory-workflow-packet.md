# Latticra Console Read-Only Host Inventory Workflow Packet

Status: planning workflow packet
Created: 2026-05-26 17:07 CDT
Decision: select a contract-only Console host-inventory evaluator workflow
Promotion decision: no Console, host-inventory, host-adapter, product-readiness, runtime, security, or OS-base promotion recommended
Scope: planning packet for a future evaluator workflow around Latticra Console read-only host inventory.

## Purpose

This packet opens the next planning lane recommended by the overall strategy priority map.

It defines how a future evaluator should review Latticra Console host-inventory posture while the project remains inside metadata-only, read-only, no-effect boundaries.

## Source records

This packet follows:

```text
docs/strategy/2026-05-26-1702-cdt-overall-strategy-priority-map.md
docs/LATTICRA_CONSOLE_FOUNDATION.md
docs/status/LATTICRA_CONSOLE_FOUNDATION_STATUS.md
STATUS.md
docs/status/CURRENT_STATUS.md
README.md
```

## Current Console posture

Current source posture:

```text
console_name=Latticra Console
short_name=LC
component_key=latticra_console
standalone_installable=1
standalone_requires_panel=0
standalone_command_wrapper=latticra-lc
host_inventory_contract_profile=lc-host-inventory-v0
host_adapter_contract_profile=lc-host-adapter-v0
runtime_boundary_bound=1
seal_capability_labels_bound=1
command_registry_no_effect=1
```

Current host-inventory posture:

```text
contract_profile=lc-host-inventory-v0
contract_status=metadata-only
required_before_host_embedding=1
host_adapter_present=0
inventory_schema_status=planned
inventory_performed=0
inventory_artifact_present=0
inventory_receipt_required=1
operator_consent_required=1
runtime_boundary_required=1
seal_capability_labels_required=1
promotion_gate=host_inventory_contract_receipt_before_host_adapter
```

Current authority floor:

```text
host_probe_allowed=0
host_process_launch_allowed=0
host_file_read_allowed=0
host_file_write_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
```

## Workflow selection

Selected workflow:

```text
contract_only_console_host_inventory_evaluator_workflow
```

Rejected workflow:

```text
live_host_inventory_capture
```

Reason:

```text
the current Console host-inventory lane is intentionally metadata-only;
the useful evaluator workflow is to verify the contract, denial posture,
future-gate language, and non-claims before any host observation is allowed
```

## Intended evaluator question

The workflow should answer:

```text
Can an evaluator understand that Latticra Console has a planned host-inventory
contract surface while also understanding that no host inventory, host probing,
host process launch, file reading, file writing, host mutation, network use,
runtime enforcement, boot behavior, or product readiness is currently claimed?
```

## Planned evaluator path

The future workflow should be organized as:

1. Start at the current public Latticra status and estimate posture.
2. Find the Console foundation and Console status records.
3. Confirm `lc host-inventory` is described as an inspectable contract command.
4. Confirm the planned future inventory scope is narrow and reviewable.
5. Confirm excluded scope blocks secrets, private files, network scanning, process launch, kernel change, and system mutation.
6. Confirm current host-inventory fields report `inventory_performed=0`.
7. Confirm host probing, host process launch, file read, file write, host mutation, network, runtime enforcement, and boot authority remain denied.
8. Confirm host-adapter promotion remains blocked by contract receipt and inventory gates.
9. Confirm receipt paths remain metadata-only and unsigned.
10. Stop before evidence capture, command execution, implementation, estimate updates, or public-entrypoint changes.

## Future evidence surfaces

If a separate evidence-capture request is made later, the likely surfaces are:

```text
docs/LATTICRA_CONSOLE_FOUNDATION.md
docs/status/LATTICRA_CONSOLE_FOUNDATION_STATUS.md
latticra_console_report host-inventory
latticra-lc host-inventory
latticra_console_report host-adapter
latticra-lc host-adapter
latticra_console_report receipt-request
latticra-lc receipt-request
```

This packet does not run or validate those commands.

## Review gates

Before any future host-inventory posture can move beyond this workflow, require:

```text
acceptance_checklist=required
evidence_bundle_template=required
non_claim_review=required
public_entrypoint_review=required
estimate_impact_review=required
completion_checkpoint=required
```

Before any future live inventory is allowed, additionally require:

```text
operator_consent_model=required
inventory_schema=required
field_allowlist=required
field_denial_tests=required
fixture_host_profiles=required
receipt_materialization_review=required
host_adapter_denial_review=required
runtime_boundary_review=required
security_non_claim_review=required
```

## Package plan

The planning package should add, in order:

```text
workflow packet
acceptance checklist
evidence bundle template
non-claim review template
public-entrypoint review template
estimate-impact review template
completion checkpoint
```

Current package status:

```text
workflow_packet_created=1
acceptance_checklist_created=1
evidence_bundle_template_created=1
non_claim_review_template_created=1
public_entrypoint_review_template_created=0
estimate_impact_review_template_created=0
completion_checkpoint_created=0
```

## Recommended next planning move

Recommended next planning move:

```text
create the Console read-only host inventory public-entrypoint review template
```

Reason:

```text
the workflow, acceptance criteria, evidence bundle shape, and non-claim review
shape are now selected; the next useful planning artifact is the review form
for deciding whether future evidence can be referenced from public entry points
without changing product, runtime, host, security, or estimate posture
```

## Do not start yet

Do not start the following from this packet:

```text
launch_console
run_latticra_lc
run_latticra_console_report
run_host_inventory
probe_host
read_host_files
write_host_files
scan_network
launch_host_process
create_inventory_artifact
write_receipt
request_signature
enable_host_adapter
change_estimates
update_public_entrypoints
promote_product_readiness
```

## Non-claims

This packet does not run Console, launch Panel, launch a shell, launch a host process, inspect a host, probe a host, read host files, write host files, scan a network, mutate a host, create an inventory artifact, create a receipt, request a signature, sign a receipt, enable a host adapter, enforce runtime policy, boot hardware, validate product readiness, update estimates, update public entry points, harden security, prevent malware, prevent ransomware, provide sandboxing, provide operating-system behavior, or provide production support.

It records workflow planning only.
