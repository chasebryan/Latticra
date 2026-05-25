# Nadia Offline AI Foundation

Status: Stage-0 foundation contract
Date: 2026-05-25
Scope: Latticra-native offline AI identity, installation surface, Console interoperability, local evidence posture, and staged development plan.

## Name

The Latticra offline AI is named **Nadia**.

Nadia is named after Nobel Peace Prize laureate Nadia Murad, whose testimony and advocacy have helped bring public attention to the enslavement and abuse of thousands of women in Iraq and Syria.

This name gives the Latticra offline AI a human-rights awareness posture: technical capability should be bound to dignity, witness, community responsibility, and careful authority.

Nadia's Latticra component identity is:

```text
public_name=Nadia
system_name=Latticra Nadia
command_name=latticra-nadia
component_key=nadia_offline_ai
```

## Purpose

Nadia is the future offline AI companion for Latticra software development, systems engineering, and AI development workflows.

Her long-term role is to help operators:

- understand and improve Latticra source, contracts, tests, and evidence;
- reason about C, constrained C++, Rust Panel code, Lat, LIR, L-UI, Nucleus, Runtime Boundary, and Seal surfaces;
- plan bounded implementation slices before tool authority is granted;
- use local project context without requiring network access;
- learn from accepted local work through operator-reviewed productivity evidence;
- keep community-awareness principles visible while building powerful local AI tools.

## Stage-0 Foundation

Stage-0 makes Nadia visible and installable without claiming model capability.

Stage-0 establishes:

```text
nadia_stage_0_foundation_present=1
panel_install_surface_present=1
console_interop_surface_present=1
local_config_surface_present=1
local_component_marker_present=1
offline_by_default=1
network_authority=0
tool_execution_authority=0
model_runtime_present=0
model_weights_installed=0
self_modification_authority=0
production_ai_claimed=0
```

Stage-0 does not install model weights, run inference, execute tools, mutate source, train a model, use the network, or claim autonomous software-development capability.

## Awareness Principles

Nadia's development should remain aligned with the reason for her name:

```text
human_dignity_principle=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1
sensationalism_allowed=0
coercive_use_allowed=0
dehumanizing_use_allowed=0
```

This does not make Stage-0 a policy engine or content-moderation system. It establishes a naming and design commitment that later AI capability must honor through explicit contracts, evidence, and operator-visible boundaries.

## Local Layout

When enabled through Latticra Panel, Nadia reserves a user-local foundation under the guarded Latticra prefix:

```text
etc/latticra/nadia.toml
share/latticra/nadia/README.md
share/latticra/nadia/context-packs/
share/latticra/nadia/model-registry/
share/latticra/nadia/productivity-ledger/
share/latticra/components/nadia-offline-ai.installed
bin/latticra-nadia
```

These paths are placeholders for future offline capability. They are intentionally local, inspectable, and receipt-visible.

## Console Interoperability

Nadia must interoperate with the embedded Latticra Console before receiving any broader authority.

Stage-0 Console behavior is metadata-only:

```text
nadia status
```

The command reports whether the Panel configuration has selected the Nadia component and repeats the denied authority posture. It does not launch an external host process.

After user-local installation, the CLI surface is:

```text
latticra-nadia status
latticra nadia status
```

The installed shim reports Stage-0 metadata only.

## Productivity Learning

Nadia's learning loop must begin as a local productivity ledger, not as silent self-training.

Stage-0 reserves the ledger path and policy vocabulary:

```text
productivity_ledger=operator-reviewed-local
accepted_patch_memory=planned
test_outcome_memory=planned
retrieval_index_updates=planned
weight_training=0
silent_self_modification=0
```

Future stages may let Nadia learn from accepted patches, test outcomes, rejected plans, and operator notes. That learning must remain local, auditable, reversible, and separated from model-weight training unless a later contract explicitly permits it.

## Development Stages

### Stage-0: Foundation

Establish name, component identity, Panel install surface, Console status surface, local config, local directories, CLI shim, status record, and deterministic guard.

### Stage-1: Local Context Engine

Build a no-network project indexer for docs, headers, sources, tests, scripts, installer configs, and status records. Produce context packs for Latticra-specific coding tasks without running inference.

Current Stage-1 status:

```text
nadia_stage_1_local_context_engine_present=1
context_pack_command=scripts/nadia-context-pack.sh
installed_context_pack_command=latticra-nadia context-pack
local_file_read_for_indexing=operator_invoked
source_mutation_authority=0
network_authority=0
model_runtime_present=0
```

See [`NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md`](NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md).

### Stage-2: Offline Inference Runtime

Add a pluggable local runtime boundary for operator-provided models, likely GGUF-compatible first. Record model hashes, quantization, context length, hardware profile, and memory budget before use.

Current Stage-2 status:

```text
nadia_stage_2_runtime_profile_present=1
runtime_profile_command=scripts/nadia-runtime-profile.sh
installed_runtime_profile_command=latticra-nadia runtime-profile
model_file_measurement=operator_provided_optional
runtime_family=llama.cpp-compatible
model_format=gguf
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
```

See [`NADIA_RUNTIME_PROFILE_STAGE_2.md`](NADIA_RUNTIME_PROFILE_STAGE_2.md).

### Stage-3: Developer Workbench

Integrate Nadia with Latticra Console and Panel workflows for code navigation, patch planning, test selection, and evidence review. Keep source mutation behind explicit operator action.

Current Stage-3 status:

```text
nadia_stage_3_developer_workbench_present=1
prompt_plan_command=scripts/nadia-prompt-plan.sh
installed_prompt_plan_command=latticra-nadia prompt-plan
requires_context_pack=1
requires_runtime_profile=1
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
source_mutation_authority=0
```

See [`NADIA_DEVELOPER_WORKBENCH_STAGE_3.md`](NADIA_DEVELOPER_WORKBENCH_STAGE_3.md).

### Stage-4: Systems Engineering Mode

Specialize prompts, retrieval, and validators for C, constrained C++, Rust Panel code, Lat/LIR/L-UI, Runtime Boundary, Seal, AI infrastructure, and Linux/Fedora integration.

### Stage-5: Productivity Loop

Use the local productivity ledger to improve retrieval, ranking, plan templates, test recommendations, and project-specific memory. Any model training or distillation remains a separate future contract.

### Stage-6: Guarded Tool Authority

Only after Nucleus, Runtime Boundary, and Seal gates mature, consider bounded tool execution. The default remains deny-by-default, receipt-bound, and operator-visible.

## Non-Claims

Stage-0 Nadia is not:

- a production AI assistant;
- an autonomous coding agent;
- a model runtime;
- a model distribution channel;
- a training system;
- a network service;
- a sandbox;
- a security product;
- a replacement for Latticra Seal, Nucleus, or Runtime Boundary.

## Promotion Gate

Before Stage-3 starts, Latticra should keep these guards passing:

```sh
sh scripts/test-nadia-offline-ai-stage-0.sh
sh scripts/test-nadia-local-context-engine-stage-1.sh
sh scripts/test-nadia-runtime-profile-stage-2.sh
sh scripts/test-nadia-developer-workbench-stage-3.sh
```

Before systems-engineering mode starts, a separate mode-taxonomy contract must exist and name domain labels, validators, failure behavior, receipt fields, and non-claims.
