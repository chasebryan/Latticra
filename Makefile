.PHONY: seal

seal:
	./scripts/latticra-seal-smoke.sh

.PHONY: seal-policy-denials

seal-policy-denials:
	bash ./scripts/test-latticra-seal-policy-denials.sh

.PHONY: seal-cli seal-run

seal-cli:
	mkdir -p build
	@OPENSSL_CFLAGS=""; \
	OPENSSL_LIBS="-lcrypto"; \
	if [ "$$(uname -s)" = "Darwin" ]; then \
		if [ -d /opt/homebrew/opt/openssl/include ]; then \
			OPENSSL_CFLAGS="-I/opt/homebrew/opt/openssl/include"; \
			OPENSSL_LIBS="-L/opt/homebrew/opt/openssl/lib -lcrypto"; \
		elif [ -d /usr/local/opt/openssl/include ]; then \
			OPENSSL_CFLAGS="-I/usr/local/opt/openssl/include"; \
			OPENSSL_LIBS="-L/usr/local/opt/openssl/lib -lcrypto"; \
		elif [ -d /opt/homebrew/include ]; then \
			OPENSSL_CFLAGS="-I/opt/homebrew/include"; \
			OPENSSL_LIBS="-L/opt/homebrew/lib -lcrypto"; \
		fi; \
	fi; \
	gcc -Wall -Wextra -O2 -std=c11 $$OPENSSL_CFLAGS -o build/latticra-seal seal/latticra-seal.c $$OPENSSL_LIBS

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

# --- Separate clean build structure (out-of-tree, isolated from installer/target/) ---
.PHONY: build-separate build-separate-cli build-separate-seal build-separate-tests build-separate-clean

build-separate:
	sh scripts/build-separate.sh all

build-separate-cli:
	sh scripts/build-separate.sh cli

build-separate-seal:
	sh scripts/build-separate.sh seal

build-separate-tests:
	sh scripts/build-separate.sh tests

build-separate-clean:
	sh scripts/build-separate.sh clean

.PHONY: build-separate-smoke
build-separate-smoke:
	sh scripts/build-separate.sh smoke

.PHONY: build-separate-validate
build-separate-validate:
	sh scripts/build-separate.sh validate

.PHONY: build-separate-full-validate
build-separate-full-validate:
	sh scripts/build-separate.sh full-validate
