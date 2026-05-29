#!/usr/bin/env sh
set -eu

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)

sh "$ROOT/latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh"
