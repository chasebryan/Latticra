.PHONY: seal latticra-console nadia-context nadia-runtime nadia-plan nadia-mode nadia-ledger nadia-safety nadia-tool nadia-prompt-contract nadia-model-registry nadia-inference-readiness nadia-runtime-invocation nadia-model-load nadia-prompt-receipt nadia-prompt-materialization nadia-awareness-dialogue nadia-prompt-evaluation-handoff nadia-tokenization-boundary nadia-tokenizer-specification nadia-tokenizer-manifest nadia-tokenizer-artifact-inventory nadia-tokenizer-artifact-measurement nadia-tokenizer-artifact-verification nadia-tokenizer-artifact-binding nadia-tokenizer-runtime-attachment nadia-prompt-tokenization

seal:
	./scripts/latticra-seal-smoke.sh

latticra-console:
	sh ./scripts/test-latticra-console-foundation.sh

nadia-context:
	sh ./scripts/nadia-context-pack.sh --repo .

nadia-runtime:
	sh ./scripts/nadia-runtime-profile.sh

nadia-plan:
	sh ./scripts/nadia-prompt-plan.sh

nadia-mode:
	sh ./scripts/nadia-mode-validate.sh

nadia-ledger:
	sh ./scripts/nadia-productivity-ledger.sh

nadia-safety:
	sh ./scripts/nadia-protective-safety-boundary.sh

nadia-tool:
	sh ./scripts/nadia-tool-authority-preflight.sh

nadia-prompt-contract:
	sh ./scripts/nadia-prompt-evaluation-contract.sh

nadia-model-registry:
	sh ./scripts/nadia-local-model-registry-contract.sh

nadia-inference-readiness:
	sh ./scripts/nadia-inference-readiness-contract.sh

nadia-runtime-invocation:
	sh ./scripts/nadia-runtime-invocation-contract.sh

nadia-model-load:
	sh ./scripts/nadia-model-load-contract.sh

nadia-prompt-receipt:
	sh ./scripts/nadia-prompt-receipt-contract.sh

nadia-prompt-materialization:
	sh ./scripts/nadia-prompt-materialization-contract.sh

nadia-awareness-dialogue:
	sh ./scripts/nadia-awareness-dialogue-contract.sh

nadia-prompt-evaluation-handoff:
	sh ./scripts/nadia-prompt-evaluation-handoff-contract.sh

nadia-tokenization-boundary:
	sh ./scripts/nadia-tokenization-boundary-contract.sh

nadia-tokenizer-specification:
	sh ./scripts/nadia-tokenizer-specification-contract.sh

nadia-tokenizer-manifest:
	sh ./scripts/nadia-tokenizer-manifest-contract.sh

nadia-tokenizer-artifact-inventory:
	sh ./scripts/nadia-tokenizer-artifact-inventory-contract.sh

nadia-tokenizer-artifact-measurement:
	sh ./scripts/nadia-tokenizer-artifact-measurement-contract.sh

nadia-tokenizer-artifact-verification:
	sh ./scripts/nadia-tokenizer-artifact-verification-contract.sh

nadia-tokenizer-artifact-binding:
	sh ./scripts/nadia-tokenizer-artifact-binding-contract.sh

nadia-tokenizer-runtime-attachment:
	sh ./scripts/nadia-tokenizer-runtime-attachment-contract.sh

nadia-prompt-tokenization:
	sh ./scripts/nadia-prompt-tokenization-contract.sh

.PHONY: seal-policy-denials

seal-policy-denials:
	bash ./scripts/test-latticra-seal-policy-denials.sh

.PHONY: seal-cli seal-run

seal-cli:
	mkdir -p build
	gcc -Wall -Wextra -O2 -std=c11 -o build/latticra-seal seal/latticra-seal.c -lcrypto

seal-run: seal-cli
	./build/latticra-seal

.PHONY: seal-check seal-manifest seal-report seal-version

seal-check: seal-cli
	./build/latticra-seal check

seal-manifest: seal-cli
	./build/latticra-seal manifest

seal-report: seal-cli
	./build/latticra-seal report

seal-version: seal-cli
	./build/latticra-seal version

.PHONY: seal-hashes

seal-hashes: seal-cli
	./build/latticra-seal hashes

.PHONY: seal-baseline seal-verify

seal-baseline: seal-cli
	./build/latticra-seal baseline

seal-verify: seal-cli
	./build/latticra-seal verify

.PHONY: seal-demo

seal-demo: seal-cli
	./scripts/demo-latticra-seal.sh

.PHONY: seal-docs
seal-docs:
	sh scripts/test-latticra-seal-docs.sh
