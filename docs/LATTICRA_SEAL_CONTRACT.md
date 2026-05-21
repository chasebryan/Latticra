# Latticra Seal Contract

Status: Latticra Seal contract
Scope: cryptographic evidence and capability substrate definition before signing implementation, encryption implementation, key management, post-quantum implementation, TPM integration, Linux integrity integration, Fedora integration, artifact measurement, runtime enforcement, network behavior, host mutation, kernel behavior, certification, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal contract.

Latticra Seal is the cryptographic evidence and capability substrate direction for Latticra. Its purpose is to bind contracts, state transitions, authority decisions, artifact identities, reports, and future operational gates to verifiable evidence before they are allowed to become runtime behavior.

This document does not implement cryptographic enforcement.

## Relationship to current Latticra posture

Latticra is contract-first, report-oriented, denied-by-default, and explicit about non-claims.

Latticra Seal depends on the existing project posture:

```text
docs/REAL_SYSTEM_CONTRACT.md
docs/EVIDENCE_LADDER.md
docs/EFFECT_GATES.md
docs/RUNTIME_BOUNDARY_CONTRACT.md
docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_REPORT_INTEGRATION.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
docs/CPP_AUTHORITY_IMPLEMENTATION_REVIEW.md
docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
docs/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_REFINEMENT.md
docs/LAT_PIPELINE_IMPLEMENTATION.md
docs/LIR_SHAPE_IMPLEMENTATION.md
```

Those files remain the source of truth for the current no-effect, metadata-only, authority, runtime-boundary, Nucleus, Lat, and LIR behavior.

Latticra Seal adds a cryptographic evidence direction. It does not bypass existing gates.

## Direction checkpoint

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
Latticra Seal is the evidence boundary.
```

Latticra Seal must preserve this relationship:

```text
Lat / Latticra Language: declares contracts, authority requests, and intended effects
LIR: carries validated metadata and evidence labels
C substrate: owns bounded records and ABI-compatible report surfaces
Constrained C++ authority layer: validates authority policy and produces denied-by-default decisions
Nucleus: coordinates only after contracts, authority, and gates are satisfied
Latticra Seal: binds reports, contracts, artifacts, and authority envelopes to evidence
Runtime boundary: remains disabled until explicit cryptographic and authority gates exist
```

## Core rule

```text
No contract without identity.
No authority without a capability.
No effect without a signed gate.
No promotion without verifiable evidence.
```

This rule is directional. It is not yet implemented runtime behavior.

## Current Seal posture

Current Latticra Seal behavior includes no implemented cryptographic enforcement.

Current allowed work:

```text
contract definition
implementation planning
report-field design
capability-envelope design
evidence-record design
primitive-policy planning
status/index alignment
guard-script validation
```

Current forbidden claims:

```text
signing implemented
encryption implemented
key generation implemented
key storage implemented
capability enforcement implemented
artifact measurement implemented
sealed objects implemented
post-quantum implementation completed
TPM-backed identity implemented
Linux integrity enforcement implemented
Fedora approval or distribution readiness
runtime enforcement
production hardening
certification
```

## Seal layers

Latticra Seal is divided into explicit layers.

```text
Seal contract layer
  Defines vocabulary, evidence boundaries, non-claims, and promotion rules.

Seal report layer
  Emits deterministic no-effect status records about what Seal supports.

Seal evidence layer
  Defines evidence records for contracts, reports, artifacts, state transitions, and authority decisions.

Seal capability layer
  Defines narrow, inspectable, future signed capability envelopes.

Seal signature layer
  Future layer for signing manifests, reports, releases, gates, and authority decisions.

Seal object layer
  Future layer for sealed/encrypted objects.

Seal integrity bridge
  Future layer for Linux/Fedora integrity evidence, package evidence, and measured host-facing validation.
```

Each layer must have its own implementation plan before code is added.

## Primitive policy

Latticra Seal does not invent cryptographic primitives.

Initial policy:

```text
new cipher design: forbidden
custom cryptographic primitive design: forbidden
standard primitive use: allowed only after exact implementation plan
primitive claims: forbidden until tests and evidence exist
post-quantum claims: forbidden until implementation and validation exist
```

Planned primitive families may include:

```text
SHA-256 / SHA-384 for official artifact and record digests
Ed25519 for future development signing
ML-KEM for future post-quantum key establishment profiles
ML-DSA for future post-quantum signature profiles
SLH-DSA for future conservative/offline signature profiles
HPKE for future object sealing
TLS 1.3 or Noise-style channels for future authenticated transport
TPM2-backed sealed identity for future machine-bound evidence
Linux integrity mechanisms for future host-facing evidence bridges
```

These are planning targets only. This contract does not implement or certify them.

## Effect boundary

First Latticra Seal effect posture:

```text
contract writing allowed: yes
implementation planning allowed: yes
static report design allowed: yes
static guard validation allowed: yes
host file reads allowed: no
host file writes allowed: no
network access allowed: no
key generation allowed: no
private key storage allowed: no
signature generation allowed: no
encryption allowed: no
artifact hashing allowed: not until exact measurement plan and tests exist
runtime authority allowed: no
capability enforcement allowed: no
kernel interaction allowed: no
```

Future artifact measurement must be explicitly classified as read-only evidence work before it is implemented.

## Evidence record shape

Future evidence records should be bounded and deterministic.

Initial planned fields:

```text
record_version
record_kind
subject_kind
subject_label
contract_id
contract_digest
artifact_label
artifact_digest
state_before_label
state_after_label
requested_effect
allowed_effect_scope
authority_state
capability_id
signature_state
sealed_state
runtime_boundary_state
evidence_level
non_claims
```

The first report implementation may include these fields as labels without computing cryptographic values.

## Capability envelope shape

Future capability envelopes should be narrow, explicit, inspectable, and expiring.

Initial planned fields:

```text
capability_version
issuer_id
subject_id
action
object_scope
effect_scope
authority_state
valid_from
valid_until
revocation_state
signature_state
```

An unsigned capability envelope is metadata only. It grants no authority.

A signed capability envelope grants no authority unless a later runtime-boundary implementation explicitly recognizes and enforces it.

## Failure behavior

Latticra Seal must fail closed.

Initial failure rules:

```text
unknown record kind -> deny / report invalid
unknown effect -> deny / report invalid
unknown authority -> deny / report invalid
missing capability -> deny / report missing
unsigned future gate -> deny / report unsigned
invalid digest -> deny / report invalid
unsupported primitive -> deny / report unsupported
runtime request -> deny / report future-gated
```

## Promotion gates

Latticra Seal may only advance through evidence-backed stages.

```text
contract -> implementation plan -> no-effect report -> fixture evidence -> read-only artifact measurement -> signed manifest -> capability envelope -> sealed object -> Linux/Fedora integrity bridge -> runtime authority gate
```

Skipping stages is forbidden.

## First implementation target

The first implementation target is report-only.

It should add no signing, no encryption, no key generation, no artifact reading, no network access, no runtime authority, and no host mutation.

The first report should be able to state:

```text
seal_profile
contract_present
implementation_plan_present
report_only_supported
artifact_measurement_supported
signature_supported
capability_enforcement_supported
sealed_objects_supported
effect_performed
host_read_performed
host_mutation_performed
network_performed
runtime_authority_granted
status
non_claims
```

## Non-claims

Latticra Seal does not currently provide:

```text
cryptographic enforcement
secure boot
measured boot
file integrity enforcement
package-signature enforcement
runtime authorization
capability enforcement
key management
encryption at rest
encrypted transport
post-quantum security
TPM-backed identity
Linux integrity integration
Fedora approval
production hardening
certification
```

## Validation path

This contract is validated by a static guard script that verifies the contract, implementation plan, status record, and non-claim posture remain present.

The guard does not prove cryptographic security. It only prevents the first Seal foundation from being represented as implemented enforcement.
