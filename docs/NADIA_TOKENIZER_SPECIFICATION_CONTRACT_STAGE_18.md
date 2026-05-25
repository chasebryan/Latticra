# Nadia Tokenizer Specification Contract Stage-18

Status: Stage-18 implementation contract
Date: 2026-05-25
Scope: tokenizer-specification metadata before tokenizer manifest loading, tokenizer file access, tokenizer vocabulary loading, prompt tokenization, prompt evaluation, dialogue generation, token generation, inference, or tool execution.

## Purpose

Stage-18 gives Nadia a tokenizer-specification contract after the tokenization-boundary contract is present.

The contract consumes a Stage-17 tokenization-boundary contract, verifies inherited non-executing tokenizer, prompt, dialogue, runtime, model, tool, and protective-safety posture, and records the requirements a future tokenizer manifest must satisfy. It does not load tokenizer files or tokenize prompts.

## Capability

Stage-18 adds:

```text
nadia_stage_18_tokenizer_specification_contract_present=1
nadia_tokenizer_specification_contract_generator_present=1
tokenizer_specification_contract_command=scripts/nadia-tokenizer-specification-contract.sh
installed_tokenizer_specification_contract_command=latticra-nadia tokenizer-specification
tokenizer_specification_contract_status=contract_only
tokenizer_specification_stage=contract-only
tokenizer_specification_authority=0
tokenizer_specification_allowed=0
tokenizer_specification_performed=0
tokenizer_specification_metadata_present=1
tokenizer_family=model-compatible-tokenizer
tokenizer_format=operator-reviewed-offline-specification
tokenizer_specification_decision=blocked_contract_only
tokenizer_specification_evidence_present=1
tokenizer_source_policy=operator-reviewed-offline
tokenizer_path_recorded=0
tokenizer_manifest_loaded=0
tokenizer_file_measurement_performed=0
requires_tokenization_boundary_contract=1
requires_prompt_evaluation_handoff_contract=1
requires_awareness_dialogue_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_prompt_buffer_boundary=1
requires_protective_safety_boundary=1
requires_operator_review=1
requires_official_source_snapshot=1
requires_future_tokenizer_manifest_contract=1
tokenizer_specification_promotion_allowed=0
```

Stage-18 does not generate dialogue, receive prompt text, read prompt sources, allocate prompt buffers, materialize prompt text, open tokenizer files, read tokenizer files, load tokenizer vocabularies, load tokenizer manifests, tokenize prompts, evaluate prompts, load model weights, invoke a runtime, generate tokens, run inference, execute tools, mutate source, train, distill, download, or use the network.

## Specification Requirements

```text
requires_model_tokenizer_compatibility_review=1
requires_tokenizer_format_review=1
requires_unicode_policy_review=1
requires_normalization_policy_review=1
requires_special_token_policy_review=1
requires_bos_eos_policy_review=1
requires_chat_template_policy_review=1
requires_prompt_template_boundary=1
requires_context_window_policy_review=1
requires_stop_sequence_policy_review=1
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
```

## Tokenizer Denial Boundary

```text
tokenizer_file_open_authority=0
tokenizer_file_read_authority=0
tokenizer_vocab_load_authority=0
tokenizer_vocab_mapping_authority=0
tokenizer_runtime_attach_authority=0
tokenizer_file_opened=0
tokenizer_file_read=0
tokenizer_vocab_loaded=0
tokenizer_vocab_mapped=0
tokenizer_attached_to_runtime=0
tokenizer_bytes_read=0
tokenizer_hash_computed=0
prompt_tokenization_authority=0
prompt_tokenization_allowed=0
prompt_tokenized=0
prompt_tokens_created=0
prompt_evaluation_authority=0
prompt_evaluated=0
```

## Protective Boundary

```text
sexual_user_request_authority=0
sexual_content_generation=0
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
erotic_content_allowed=0
roleplay_allowed=0
survivor_impersonation_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
hate_or_collective_blame_allowed=0
medical_advice_authority=0
legal_advice_authority=0
trauma_counseling_authority=0
crisis_intervention_authority=0
sexual_request_refusal=always
manipulation_resistance=required
```

## Usage

With explicit evidence input:

```sh
sh scripts/nadia-tokenizer-specification-contract.sh \
  --tokenization-boundary /path/to/latest-tokenization-boundary-contract.txt \
  --request-class awareness-education \
  --tokenizer-family model-compatible-tokenizer \
  --tokenizer-format operator-reviewed-offline-specification \
  --output /private/tmp/latticra-nadia-tokenizer-specification
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia tokenizer-specification
```

## Non-Claims

Stage-18 Nadia is not yet a Q&A assistant, dialogue generator, prompt evaluator, tokenizer, tokenizer loader, tokenizer registry, tokenizer manifest loader, model loader, inference runtime, runtime process launcher, token generator, model selector, tool executor, shell runner, network client, source mutator, training system, distillation system, security product, sexual assistant, roleplay surface, adult-content generator, legal adviser, medical adviser, trauma counselor, crisis intervention service, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-tokenizer-specification-contract-stage-18.sh
```

Expected result:

```text
nadia_tokenizer_specification_contract_stage_18: ok
```
