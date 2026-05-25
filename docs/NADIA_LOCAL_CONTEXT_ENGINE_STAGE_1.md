# Nadia Local Context Engine Stage-1

Status: Stage-1 implementation contract
Date: 2026-05-25
Scope: no-network local context-pack generation for Nadia.

## Purpose

Stage-1 gives Nadia a deterministic local context engine before any model runtime exists.

The context engine creates auditable context packs from local Latticra project files so future offline inference can begin from explicit, measured, inspectable source material instead of hidden memory or network retrieval.

## Capability

Stage-1 adds:

```text
nadia_stage_1_local_context_engine_present=1
nadia_context_pack_generator_present=1
context_pack_command=scripts/nadia-context-pack.sh
installed_context_pack_command=latticra-nadia context-pack
local_file_read_for_indexing=operator_invoked
local_context_pack_write=operator_selected_output
network_authority=0
model_runtime_present=0
model_weights_installed=0
tool_execution_authority=0
source_mutation_authority=0
training_performed=0
```

The context engine records file paths, file classes, line counts, byte counts, and local measurements. It does not summarize with AI, embed text, call a model, use the network, or mutate source.

## Inputs

The default context-pack roots are:

```text
README.md
STATUS.md
SECURITY.md
CONTRIBUTING.md
docs/
include/
src/
tests/
scripts/
installer/
seal/
```

Generated build outputs, local receipts, and existing Nadia context-pack outputs are excluded.

## Outputs

The context-pack generator writes:

```text
nadia-context-pack-<timestamp>.txt
nadia-context-file-index-<timestamp>.tsv
latest-context-pack.txt
latest-file-index.tsv
```

The pack includes:

```text
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=1-local-context-engine
network_authority=0
model_runtime_present=0
model_weights_installed=0
tool_execution_authority=0
source_mutation_authority=0
human_dignity_principle=1
community_awareness_posture=1
```

## Usage

From the repository:

```sh
sh scripts/nadia-context-pack.sh --repo . --output /private/tmp/latticra-nadia-context
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia context-pack
```

The installed command writes under the user-local Nadia context-pack directory.

## Non-Claims

Stage-1 Nadia is not an inference runtime, autonomous coding agent, embedding service, training system, source mutator, network retriever, security product, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-local-context-engine-stage-1.sh
```

Expected result:

```text
nadia_local_context_engine_stage_1: ok
```
