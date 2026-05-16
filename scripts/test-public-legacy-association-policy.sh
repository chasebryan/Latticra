#!/usr/bin/env sh
set -eu

public_docs="
README.md
SECURITY.md
docs/FOUNDATION_INDEX.md
docs/REAL_SYSTEM_CONTRACT.md
docs/PRECURSOR_PROMOTION_RULE.md
docs/NON_CLAIMS.md
docs/ARCHITECTURE_SEED.md
docs/NAMING_SYSTEM.md
docs/FEATURE_TRANSLATION_LEDGER.md
docs/LANGUAGE_NAMING_POLICY.md
docs/LANGUAGE_STRATEGY.md
docs/SUPERVISOR_ARCHITECTURE.md
docs/EFFECT_GATES.md
docs/UI_TERMINAL_LANGUAGE.md
docs/SERVER_INTERACTION_MODEL.md
docs/SELF_UPDATE_MODEL.md
docs/HOST_ARCHITECTURE_TARGETS.md
docs/ROADMAP.md
docs/LICENSE_POLICY.md
"

for file in $public_docs; do
  if [ ! -f "$file" ]; then
    printf 'public legacy association policy: missing public doc: %s\n' "$file" >&2
    exit 1
  fi

  if grep -Eq 'Phase1|Base1|Fyr|PHASE1_IMPORT_RULE|Phase-derived|Base1-derived|Fyr-derived|Phase-native' "$file"; then
    printf 'public legacy association policy: legacy project association found in %s\n' "$file" >&2
    exit 1
  fi

done

printf 'public_legacy_association_policy: ok\n'
