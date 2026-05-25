#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS -Iinclude src/seal_signature_request.c tests/seal_signature_request_invariants.c -o /tmp/latticra-seal-signature-request-invariants
/tmp/latticra-seal-signature-request-invariants
