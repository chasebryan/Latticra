#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

# macOS / Homebrew OpenSSL compatibility for separate clean builds
OPENSSL_CFLAGS=""
OPENSSL_LIBS="-lcrypto"
if [ "$(uname -s)" = "Darwin" ]; then
    if [ -d /opt/homebrew/opt/openssl/include ]; then
        OPENSSL_CFLAGS="-I/opt/homebrew/opt/openssl/include"
        OPENSSL_LIBS="-L/opt/homebrew/opt/openssl/lib -lcrypto"
    elif [ -d /usr/local/opt/openssl/include ]; then
        OPENSSL_CFLAGS="-I/usr/local/opt/openssl/include"
        OPENSSL_LIBS="-L/usr/local/opt/openssl/lib -lcrypto"
    elif [ -d /opt/homebrew/include ]; then
        # fallback for openssl@3 keg-only
        OPENSSL_CFLAGS="-I/opt/homebrew/include"
        OPENSSL_LIBS="-L/opt/homebrew/lib -lcrypto"
    fi
fi

cc $CFLAGS $OPENSSL_CFLAGS -Iinclude src/seal_ed25519_verify.c tests/seal_ed25519_verify_invariants.c $OPENSSL_LIBS -o /tmp/latticra-seal-ed25519-verify-invariants
/tmp/latticra-seal-ed25519-verify-invariants
