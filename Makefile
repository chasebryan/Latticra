.PHONY: seal latticra-console nadia-context nadia-runtime nadia-plan nadia-mode nadia-ledger nadia-safety nadia-tool nadia-prompt-contract nadia-model-registry nadia-inference-readiness nadia-runtime-invocation nadia-model-load nadia-prompt-receipt nadia-prompt-materialization nadia-awareness-dialogue nadia-prompt-evaluation-handoff nadia-tokenization-boundary nadia-tokenizer-specification nadia-tokenizer-manifest nadia-tokenizer-artifact-inventory nadia-tokenizer-artifact-measurement nadia-tokenizer-artifact-verification nadia-tokenizer-artifact-binding nadia-tokenizer-runtime-attachment nadia-prompt-tokenization nadia-prompt-token-sequence nadia-context-window-assembly nadia-prompt-evaluation-input nadia-prompt-evaluation-runtime-handoff nadia-prompt-evaluation-invocation nadia-prompt-evaluation-result nadia-prompt-evaluation-result-review nadia-prompt-evaluation-result-disposition nadia-prompt-evaluation-result-release nadia-prompt-evaluation-result-release-receipt nadia-prompt-evaluation-result-release-receipt-review nadia-prompt-evaluation-result-release-receipt-review-disposition nadia-prompt-evaluation-result-release-receipt-review-disposition-release

.PHONY: quality quality-worktree quality-safety-guards quality-defensive-threat-model quality-security-standards quality-rust-installer quality-panel-installer quality-installer-readiness quality-nadia quality-c-foundation boot-compatibility boot-preview-preflight boot-evidence-template boot-qemu-argv-template boot-artifact-template boot-artifact-validate macos-reset-uninstall-live-denial-transcript macos-reset-uninstall-live-runner-interface macos-reset-uninstall-live-runner-noop-prototype macos-reset-uninstall-live-runner-denied-dispatch-transcript macos-reset-uninstall-live-runner-denied-dispatch-review nadia-commands high-assurance-security-baseline

quality: quality-worktree quality-safety-guards quality-defensive-threat-model quality-security-standards seal-policy-denials quality-rust-installer quality-panel-installer quality-installer-readiness quality-nadia quality-c-foundation

quality-worktree:
	git diff --check

quality-safety-guards:
	tmp="$$(mktemp -d "$${TMPDIR:-/tmp}/latticra-quality-safety-guards.XXXXXX")"; \
	trap 'rm -rf "$$tmp"' EXIT INT HUP TERM; \
	cp ./scripts/test-quality-safety-guards.sh "$$tmp/test-quality-safety-guards.sh"; \
	LATTICRA_ROOT="$$(pwd)" sh "$$tmp/test-quality-safety-guards.sh"

quality-defensive-threat-model:
	sh ./scripts/test-defensive-threat-model-contract.sh
	sh ./scripts/test-defensive-threat-model-implementation-plan.sh
	sh ./scripts/test-defensive-threat-model-validation.sh

quality-security-standards:
	sh ./scripts/test-defensive-threat-model-validation-refinement.sh
	sh ./scripts/test-high-assurance-security-baseline.sh

quality-rust-installer:
	cargo fmt --manifest-path installer/latticra-installer/Cargo.toml -- --check
	cargo check --locked --manifest-path installer/latticra-installer/Cargo.toml

quality-panel-installer:
	python3 scripts/check_latticra_panel_ui_design.py
	sh ./scripts/test-latticra-panel-lc-install-config.sh
	sh ./scripts/test-latticra-panel-local-install-lc-install-config.sh
	sh ./scripts/test-latticra-panel-local-install-evidence-status.sh
	sh ./scripts/test-latticra-panel-local-install-public-entrypoint-alignment.sh
	sh ./scripts/test-latticra-panel-local-uninstall-reset.sh
	sh ./scripts/test-latticra-panel-updater.sh

quality-installer-readiness:
	sh ./scripts/test-production-installer-readiness-contract.sh
	sh ./scripts/test-local-installer-artifact-manifest-contract.sh
	sh ./scripts/test-local-artifact-manifest-fixture.sh
	sh ./scripts/test-seabios-grub-compatibility-contract.sh
	sh ./scripts/test-seabios-grub-boot-preview-evidence-contract.sh
	sh ./scripts/test-seabios-grub-boot-preview-preflight.sh
	sh ./scripts/test-seabios-grub-boot-preview-evidence-template.sh
	sh ./scripts/test-seabios-grub-boot-preview-qemu-argv-template.sh
	sh ./scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-template.sh
	sh ./scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-validate.sh

quality-nadia:
	sh ./scripts/test-nadia-command-surface.sh
	sh ./scripts/test-nadia-prompt-evaluation-result-review-contract-stage-32.sh
	sh ./scripts/test-nadia-prompt-evaluation-result-disposition-contract-stage-33.sh
	sh ./scripts/test-nadia-prompt-evaluation-result-release-contract-stage-34.sh
	sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-contract-stage-35.sh
	sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-review-contract-stage-36.sh
	sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-stage-37.sh
	sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-stage-38.sh

quality-c-foundation:
	sh ./scripts/test-latticra-console-foundation.sh
	sh ./scripts/test-cpp-authority-layer.sh
	sh ./scripts/test-kernel-timer-source.sh
	sh ./scripts/test-kernel-timer-source-report-runner.sh
	sh ./scripts/test-kernel-scheduler-tick.sh
	sh ./scripts/test-kernel-scheduler-tick-report-runner.sh
	sh ./scripts/test-kernel-run-queue.sh
	sh ./scripts/test-kernel-run-queue-report-runner.sh
	sh ./scripts/test-kernel-context-switch.sh
	sh ./scripts/test-kernel-context-switch-report-runner.sh

boot-compatibility:
	sh ./scripts/test-seabios-grub-compatibility-contract.sh
	sh ./scripts/test-seabios-grub-boot-preview-evidence-contract.sh
	sh ./scripts/test-seabios-grub-boot-preview-preflight.sh
	sh ./scripts/test-seabios-grub-boot-preview-evidence-template.sh
	sh ./scripts/test-seabios-grub-boot-preview-qemu-argv-template.sh
	sh ./scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-template.sh
	sh ./scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-validate.sh

boot-preview-preflight:
	sh ./scripts/seabios-grub-boot-preview-preflight.sh

boot-evidence-template:
	sh ./scripts/seabios-grub-boot-preview-evidence-template.sh

boot-qemu-argv-template:
	sh ./scripts/seabios-grub-boot-preview-qemu-argv-template.sh

boot-artifact-template:
	sh ./scripts/seabios-grub-boot-preview-boot-artifact-manifest-template.sh

boot-artifact-validate:
	sh ./scripts/seabios-grub-boot-preview-boot-artifact-manifest-validate.sh

macos-reset-uninstall-live-denial-transcript:
	sh ./scripts/test-macos-reset-uninstall-live-denial-transcript-contract.sh

macos-reset-uninstall-live-runner-interface:
	sh ./scripts/test-macos-reset-uninstall-live-runner-interface-contract.sh

macos-reset-uninstall-live-runner-noop-prototype:
	sh ./scripts/test-macos-reset-uninstall-live-runner-noop-prototype-contract.sh

macos-reset-uninstall-live-runner-denied-dispatch-transcript:
	sh ./scripts/test-macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh

macos-reset-uninstall-live-runner-denied-dispatch-review:
	sh ./scripts/test-macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh

nadia-commands:
	sh ./scripts/test-nadia-command-surface.sh

high-assurance-security-baseline:
	sh ./scripts/test-high-assurance-security-baseline.sh

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

nadia-prompt-token-sequence:
	sh ./scripts/nadia-prompt-token-sequence-contract.sh

nadia-context-window-assembly:
	sh ./scripts/nadia-context-window-assembly-contract.sh

nadia-prompt-evaluation-input:
	sh ./scripts/nadia-prompt-evaluation-input-contract.sh

nadia-prompt-evaluation-runtime-handoff:
	sh ./scripts/nadia-prompt-evaluation-runtime-handoff-contract.sh

nadia-prompt-evaluation-invocation:
	sh ./scripts/nadia-prompt-evaluation-invocation-contract.sh

nadia-prompt-evaluation-result:
	sh ./scripts/nadia-prompt-evaluation-result-contract.sh

nadia-prompt-evaluation-result-review:
	sh ./scripts/nadia-prompt-evaluation-result-review-contract.sh

nadia-prompt-evaluation-result-disposition:
	sh ./scripts/nadia-prompt-evaluation-result-disposition-contract.sh

nadia-prompt-evaluation-result-release:
	sh ./scripts/nadia-prompt-evaluation-result-release-contract.sh

nadia-prompt-evaluation-result-release-receipt:
	sh ./scripts/nadia-prompt-evaluation-result-release-receipt-contract.sh

nadia-prompt-evaluation-result-release-receipt-review:
	sh ./scripts/nadia-prompt-evaluation-result-release-receipt-review-contract.sh

nadia-prompt-evaluation-result-release-receipt-review-disposition:
	sh ./scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract.sh

nadia-prompt-evaluation-result-release-receipt-review-disposition-release:
	sh ./scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract.sh

.PHONY: seal-policy-denials

seal-policy-denials:
	bash ./scripts/test-latticra-seal-policy-denials.sh

.PHONY: seal-cli seal-run

PKG_CONFIG ?= pkg-config
SEAL_CFLAGS ?= -Wall -Wextra -O2 -std=c11
SEAL_OPENSSL_CFLAGS ?= $(shell $(PKG_CONFIG) --cflags openssl 2>/dev/null)
SEAL_OPENSSL_LIBS ?= $(shell $(PKG_CONFIG) --libs openssl 2>/dev/null)
ifeq ($(strip $(SEAL_OPENSSL_LIBS)),)
SEAL_OPENSSL_LIBS := -lcrypto
endif

seal-cli:
	mkdir -p build
	$(CC) $(SEAL_CFLAGS) $(SEAL_OPENSSL_CFLAGS) -o build/latticra-seal seal/latticra-seal.c $(SEAL_OPENSSL_LIBS)

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
