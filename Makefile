.PHONY: seal

seal:
	./scripts/latticra-seal-smoke.sh

.PHONY: seal-cli seal-run

seal-cli:
	mkdir -p build
	gcc -Wall -Wextra -O2 -std=c11 -o build/latticra-seal seal/latticra-seal.c

seal-run: seal-cli
	./build/latticra-seal
