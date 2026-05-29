# Nadia Awareness Dialogue Contract Stage-15

Status: Stage-15 implementation contract
Date: 2026-05-25
Scope: future Q&A dialogue scope for Nadia Initiative awareness topics before prompt evaluation, dialogue generation, token generation, inference, or tool execution.

## Purpose

Stage-15 gives Nadia an awareness-dialogue contract for future Q&A about the work Nadia Initiative actively raises awareness about.

The contract consumes a Stage-14 prompt-materialization contract, verifies inherited non-executing prompt, runtime, model, tool, and protective-safety posture, and records the awareness topic register and dialogue safety rules that must exist before any future prompt-evaluation handoff.

## Capability

Stage-15 adds:

```text
nadia_stage_15_awareness_dialogue_contract_present=1
nadia_awareness_dialogue_contract_generator_present=1
awareness_dialogue_contract_command=scripts/nadia-awareness-dialogue-contract.sh
installed_awareness_dialogue_contract_command=latticra-nadia awareness-dialogue
future_qa_dialogue_capability_planned=1
awareness_dialogue_contract_status=contract_only
awareness_dialogue_stage=contract-only
awareness_dialogue_authority=0
awareness_dialogue_allowed=0
dialogue_generation_authority=0
dialogue_generation_allowed=0
qa_dialogue_generated=0
dialogue_turns_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0
dialogue_scope=official-nadia-initiative-awareness-work
dialogue_format=question-and-answer
q_and_a_format_required=1
survivor_centered_dialogue_required=1
respectful_tone_required=1
plain_language_required=1
source_attribution_required=1
official_source_grounding_required=1
source_snapshot_policy=operator-reviewed-offline
active_topic_update_authority=0
live_web_lookup_authority=0
dialogue_decision=blocked_contract_only
requires_official_source_snapshot=1
awareness_dialogue_promotion_allowed=0
```

Stage-15 does not generate dialogue, receive prompt text, read prompt sources, allocate prompt buffers, materialize prompt text, tokenize prompts, evaluate prompts, load model weights, invoke a runtime, generate tokens, run inference, execute tools, mutate source, train, distill, download, or use the network.

## Awareness Topic Register

Nadia's future Q&A scope is limited to official Nadia Initiative awareness work and must remain non-graphic, respectful, and survivor-centered:

```text
topic_yazidi_genocide_awareness=1
topic_survivor_voice_and_dignity=1
topic_conflict_related_sexual_violence_awareness_non_graphic=1
topic_genocide_prevention=1
topic_justice_and_accountability=1
topic_women_peace_justice_security=1
topic_sinjar_reconstruction=1
topic_security_and_safe_return=1
topic_education_restoration=1
topic_healthcare_and_mental_health=1
topic_livelihoods_and_food_security=1
topic_wash_clean_water_sanitation_hygiene=1
topic_womens_empowerment=1
topic_legal_rights_and_reparations_awareness=1
topic_cultural_preservation_and_memorialization=1
topic_community_driven_survivor_centric_development=1
topic_responsible_support_and_digital_activism=1
```

## Protective Dialogue Rules

```text
sexual_user_request_authority=0
sexual_content_generation=0
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
erotic_content_allowed=0
roleplay_allowed=0
survivor_impersonation_allowed=0
survivor_identifying_speculation_allowed=0
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

## Official Source Register

Future dialogue must be grounded in operator-reviewed offline snapshots from official Nadia Initiative sources:

```text
source_nadia_initiative_home=https://www.nadiasinitiative.org/home
source_nadia_initiative_about=https://www.nadiasinitiative.org/nadias-initiative
source_nadia_initiative_approach=https://www.nadiasinitiative.org/our-approach
source_nadia_initiative_advocacy=https://www.nadiasinitiative.org/advocacy
source_nadia_initiative_womens_empowerment=https://www.nadiasinitiative.org/womens-empowerment
source_snapshot_generated=0
source_snapshot_loaded=0
source_fetch_performed=0
```

Stage-15 does not give Nadia live browsing authority.

## Usage

With explicit evidence input:

```sh
sh scripts/nadia-awareness-dialogue-contract.sh \
  --prompt-materialization /path/to/latest-prompt-materialization-contract.txt \
  --request-class awareness-education \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-awareness-dialogue.XXXXXX")"
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia awareness-dialogue
```

## Non-Claims

Stage-15 Nadia is not yet a Q&A assistant, dialogue generator, prompt evaluator, model loader, inference runtime, runtime process launcher, token generator, model selector, tool executor, shell runner, network client, source mutator, training system, distillation system, security product, sexual assistant, roleplay surface, adult-content generator, legal adviser, medical adviser, trauma counselor, crisis intervention service, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-awareness-dialogue-contract-stage-15.sh
```

Expected result:

```text
nadia_awareness_dialogue_contract_stage_15: ok
```
