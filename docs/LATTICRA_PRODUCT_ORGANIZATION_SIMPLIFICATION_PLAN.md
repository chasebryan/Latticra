# Latticra Product Organization Simplification Plan

Status: guarded product routing and simplification plan
Date: 2026-06-19 CDT
Scope: organization decision for the next Latticra product phase before simplified installer implementation, Netplane adapter expansion, or repository restructuring.

## Purpose

This record simplifies Latticra by naming the product routes a reader should use first and by choosing the next implementation lane. It does not move source files, rename active directories, import sibling repositories, or grant new runtime authority.

The immediate decision is to add a routing layer before any physical reorganization. Latticra already has many guarded records, status mirrors, scripts, and workflows that are intentionally string-coupled. Moving them now would create avoidable validation risk. The better simplification step is to make the public product shape obvious, then let later implementation work follow that shape.

## Boundary Checkpoint

```text
latticra_product_organization_simplification_present=1
product_organization_simplification_guard_present=1
decision_id=latticra-product-organization-simplification
decision_version=1
edge_checkpoint=v0.3.0edge
product_route_layer_present=1
physical_reorganization_performed=0
active_repo_relocation_performed=0
source_import_performed=0
artifact_copy_performed=0
sibling_repo_mutation_performed=0
network_performed=0
runtime_authority_granted=0
production_readiness_claim=0
cybersecurity_certification_claim=0
set_and_forget_security_claim=0
central_hub_role=Latticra Core plus Netplane routing
simplified_user_route=Latticra Guard
integration_route=Latticra Netplane
research_route=Latticra Research
separate_channel=WARLOCK-INDEX
next_recommended_lane=latticra-guard-simplified-installer-intake
ready_for_next_when=guarded-routing-present-and-quality-status-green
```

## Product Routes

| Route | Meaning | First implementation posture |
| --- | --- | --- |
| Latticra Guard | Simplified user-facing edition for install, baseline status, update, reset, and evidence visibility | Plan an installer/app intake before claiming protection or production readiness |
| Latticra Core | Evidence substrate, Seal/Q-Seal, Nucleus, runtime boundary, reports, receipts, installer, docs, and guards | Keep as the canonical architecture and validation source |
| Latticra Netplane | Adapter and provenance plane for Kaiju, l2, l3, L4, fyr, Rainbow, and later adjacent systems | Accept static evidence and receipt schemas before runtime bridges |
| Latticra Research | Proof objects, substrate models, Higgs challenge, simulation-bound reality hypotheses, and visual theorem lanes | Keep source-tracked, falsifiable, and non-claiming |
| WARLOCK-INDEX | Separate corpus and channel | Keep separate from Latticra import, build, and runtime authority |

## Simplification Decisions

1. The first public route should answer what a user installs before it exposes the full research and substrate corpus.
2. Latticra Guard is the name for the simplified user edition, but this record does not create that app or installer.
3. Latticra Guard may target baseline setup, visible status, update checks, reset/uninstall, receipts, and clear denied states.
4. Latticra Guard must not be described as certified cybersecurity, guaranteed protection, autonomous remediation, or set-and-forget security.
5. Latticra Core remains the source of truth for evidence, policy, receipts, runtime boundary contracts, installer surfaces, and status mirrors.
6. Latticra Netplane is the only entry route for Kaiju, l2, l3, L4, fyr, Rainbow, or similar sibling projects until a later explicit review gate changes that boundary.
7. Kaiju and later sibling projects should enter as static adapter evidence, receipt schemas, manifests, or reviewed adapters before any source import, artifact copy, command execution, network behavior, or runtime bridge.
8. Nadia remains a separate offline AI lane and is not part of Latticra Guard v1 by default.
9. The existing guarded file layout should stay in place for now. Simplification should happen through reader routes, status maps, and implementation lanes before physical moves.
10. WARLOCK-INDEX stays its own channel and should not be pulled into Latticra as source, generated site output, or runtime dependency.

## First-Screen Public Order

The public reader order should be:

```text
1. What do I install?
2. What does it do locally?
3. What evidence can I inspect?
4. What does it not claim?
5. Where do I go for Core, Netplane, or Research details?
```

For now, the root README adds this route without changing package behavior. The next implementation lane should define the smallest Latticra Guard installer intake that can tell a user what would be installed, what local authority is requested, what receipts are written, how status is shown, how updates are checked, and how reset/uninstall is performed.

## Ready For Next

This simplification stop point is ready for the next lane when:

```text
root_readme_product_routes_present=1
docs_hub_product_route_present=1
status_mirrors_reference_plan=1
make_target_present=1
focused_guard_present=1
quality_status_includes_guard=1
quality_safety_guard_tracks_target=1
next_recommended_lane=latticra-guard-simplified-installer-intake
```

## Validation

This plan is guarded by:

```sh
sh scripts/test-latticra-product-organization-simplification.sh
```

Expected output:

```text
latticra_product_organization_simplification: ok
```

## Non-Claims

This record is not a product release, installer implementation, source move, repository import, sibling repository mutation, Kaiju integration, l2 integration, l3 integration, L4 integration, fyr integration, Rainbow integration, Nadia integration, WARLOCK-INDEX import, command execution, file mutation outside this repository, network behavior, runtime authority, production readiness, cybersecurity certification, guaranteed protection, autonomous remediation, or set-and-forget security claim.
