# Latticra Netplane Central Hub Intake

Status: no-effect Netplane central-hub intake
Date: 2026-06-19 CDT
Scope: first integration intake for Kaiju, l2, l3, L4, Fyr, Rainbow, and Latticra Netplane as Latticra-adjacent lanes while WARLOCK-INDEX remains separate.

## Purpose

This record defines Latticra Netplane as the central routing and provenance plane for sibling systems that should feed Latticra without silently importing source, copying artifacts, executing effects, opening network authority, or promoting runtime authority.

The intake is grounded in local checkout and live GitHub observations made on 2026-06-19 CDT. It records:

- Kaiju as the first binary-analysis and package-evidence adapter lane.
- l2 as the focused Latticra substrate prototype lane.
- l3 as the Ada-first high-assurance substrate direction.
- L4 as the existing internal blinded-holdout execution-gate lane, not a separate observed checkout.
- Fyr as a public source lane whose local checkout must be refreshed because the current local `~/Documents/fyr` path points at Rainbow.
- Rainbow as the locally present language-bootstrap lane.
- Latticra Netplane as the new internal central-hub lane.
- WARLOCK-INDEX as a separate channel outside this intake.

## Boundary Checkpoint

```text
latticra_netplane_central_hub_intake_present=1
netplane_intake_id=latticra-netplane-central-hub-intake
netplane_intake_version=1
edge_checkpoint=v0.3.0edge
manifest_reference=fixtures/netplane/latticra-netplane-central-hub-manifest.json
netplane_inventory_tool=tools/latticra_netplane_inventory.py
central_hub_declared=1
netplane_defined=1
active_lane_count=7
required_lane_count=7
required_lanes_present=1
kaiju_lane_present=1
l2_lane_present=1
l3_lane_present=1
l4_lane_present=1
fyr_lane_present=1
rainbow_lane_present=1
warlock_index_separate_channel=1
fyr_local_provenance_refresh_required=1
rainbow_local_checkout_present=1
deny_by_default=1
source_import_performed=0
artifact_copy_performed=0
mixed_build_promotion_accepted=0
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
network_performed=0
runtime_authority_granted=0
production_readiness_claim=0
```

## Observed Active Lanes

| Lane | Source | Current intake decision |
| --- | --- | --- |
| Kaiju | `chasebryan/kaiju`, local `~/Documents/kaiju` at `93995843381d` | Static adapter evidence intake required before any source import |
| l2 | `veilriven-design/l2`, local `~/Documents/l2` at `e592e0fa0c1e` | Substrate-boundary review required before any bridge |
| l3 | `chasebryan/l3`, local `~/Documents/l3` at `1e502f07abf6` | License and assurance review required before any source copy |
| L4 | internal Latticra lane | Already guarded as `docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_L4_BLINDED_HOLDOUT_EXECUTION_GATE.md` |
| Fyr | `chasebryan/fyr` | Local provenance refresh required before review |
| Rainbow | `chasebryan/rainbow`, local `~/Documents/fyr` at `1c63e02b58e5` | Language-surface review required before any import |
| Netplane | internal Latticra lane | Central-hub intake defined by this record |

## Required Follow-On Review Fields

Every future sibling-system intake must expose these fields before code, artifacts, build outputs, or runtime behavior can be accepted:

```text
lane_id
source_owner
source_repository
source_default_branch
source_revision
source_dirty_state
license_posture
local_checkout
local_checkout_provenance
import_scope
adapter_scope
artifact_inventory_reference
capability_boundary_reference
effect_contract_reference
runtime_authority_decision
network_authority_decision
non_claims
review_decision
```

Initial defaults remain conservative:

```text
import_scope=not-imported|static-review-only
adapter_scope=not-accepted
runtime_authority_decision=not-granted
network_authority_decision=not-granted
review_decision=requires-future-gate
```

## Kaiju First-Lane Meaning

Kaiju is the first practical lane because it already produces binary, package, project, network-evidence, and workbench surfaces that can become Latticra evidence inputs. The next lane should define a static Kaiju adapter evidence intake that reads Kaiju-produced files or package metadata as evidence records.

That follow-on lane must not run privileged capture, scan live interfaces, import Kaiju source, accept a plugin runtime, promote a mixed build, or claim reverse-engineering completeness.

## Netplane Meaning

Netplane is the Latticra-owned routing surface for sibling system provenance and integration intent. At this checkpoint it is a manifest plus receipt emitter only. It is not network behavior.

The fixture manifest is:

```text
fixtures/netplane/latticra-netplane-central-hub-manifest.json
```

The receipt tool is:

```sh
python3 tools/latticra_netplane_inventory.py
```

Expected receipt fields include `source_import_performed=0`, `network_performed=0`, and `runtime_authority_granted=0`.

## Separate Channel

WARLOCK-INDEX remains a separate channel:

```text
warlock_index_separate_channel=1
warlock_index_imported_into_latticra_netplane=0
```

WARLOCK-INDEX may reference or be referenced by Latticra in public routing, but it is not part of this central-hub import lane.

## Next Recommended Lane

```text
Kaiju static adapter evidence intake.
```

That lane should define the exact Kaiju evidence files, package metadata, digest fields, license boundary, denied live-capture behavior, and no-effect validation before any deeper Latticra integration.

## Validation

This intake is guarded by:

```sh
sh scripts/test-latticra-netplane-central-hub-intake.sh
```

Expected output:

```text
latticra_netplane_central_hub_intake: ok
```

## Non-Claims

This record is not source import, artifact import, code vendoring, adapter acceptance, mixed-build promotion, command execution, file mutation, privileged capture, port scanning, live network behavior, runtime authority, production readiness, distribution readiness, or a claim that Kaiju, l2, l3, Fyr, Rainbow, or any deferred repository is complete or integrated.
