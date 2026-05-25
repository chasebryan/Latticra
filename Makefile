.PHONY: seal nadia-context nadia-runtime nadia-plan nadia-mode nadia-ledger nadia-safety nadia-tool

seal:
	./scripts/latticra-seal-smoke.sh

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
