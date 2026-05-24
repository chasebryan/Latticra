.PHONY: seal

seal:
	./scripts/latticra-seal-smoke.sh

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
