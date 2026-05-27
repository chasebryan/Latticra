#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'secret material guard: %s\n' "$1" >&2
  exit 1
}

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-secret-material.XXXXXX")"
cleanup() {
  rm -rf "$tmp_dir"
}
trap cleanup EXIT INT HUP TERM

filename_hits="$tmp_dir/filename-hits.txt"
content_hits="$tmp_dir/content-hits.txt"
: >"$filename_hits"
: >"$content_hits"

source_files() {
  find . \
    -path './.git' -prune -o \
    -path './reports' -prune -o \
    -name target -type d -prune -o \
    -name build -type d -prune -o \
    -name dist -type d -prune -o \
    -name node_modules -type d -prune -o \
    -name .venv -type d -prune -o \
    -name '.venv-*' -type d -prune -o \
    -name venv -type d -prune -o \
    -name __pycache__ -type d -prune -o \
    -name .pytest_cache -type d -prune -o \
    -name .mypy_cache -type d -prune -o \
    -type f -print
}

is_allowed_secret_template_name() {
  case "$1" in
    .env.example|.env.sample|.env.template|*.env.example|*.env.sample|*.env.template|*.example.pem|*.sample.pem|*.template.pem)
      return 0
      ;;
  esac
  return 1
}

is_sensitive_secret_name() {
  case "$1" in
    .env|.env.*|.envrc|*.env|*.env.*|.npmrc|.pypirc|.netrc|credentials|credentials.json|service-account*.json|id_rsa|id_ed25519|*.pem|*.key|*.p12|*.pfx|*.jks|*.keystore|*.ovpn|kubeconfig|*.kubeconfig)
      return 0
      ;;
  esac
  return 1
}

source_files |
  while IFS= read -r path; do
    name="${path##*/}"
    if is_sensitive_secret_name "$name" && ! is_allowed_secret_template_name "$name"; then
      printf '%s\n' "$path" >>"$filename_hits"
    fi
  done

if [ -s "$filename_hits" ]; then
  sed -n '1,40p' "$filename_hits" >&2
  fail "possible committed secret-bearing filenames found"
fi

secret_content_pattern='-----BEGIN (RSA |DSA |EC |OPENSSH |PGP )?PRIVATE KEY-----|(^|[^A-Za-z0-9_-])(AKIA|ASIA)[0-9A-Z]{16}([^A-Za-z0-9_-]|$)|(^|[^A-Za-z0-9_-])github_pat_[A-Za-z0-9_]{20,}([^A-Za-z0-9_-]|$)|(^|[^A-Za-z0-9_-])gh[pousr]_[A-Za-z0-9_]{20,}([^A-Za-z0-9_-]|$)|(^|[^A-Za-z0-9_-])glpat-[A-Za-z0-9_-]{20,}([^A-Za-z0-9_-]|$)|(^|[^A-Za-z0-9_-])sk-[A-Za-z0-9_-]{20,}([^A-Za-z0-9_-]|$)|(^|[^A-Za-z0-9_-])xox[baprs]-[A-Za-z0-9-]{10,}([^A-Za-z0-9_-]|$)|(^|[^A-Za-z0-9_-])AIza[0-9A-Za-z_-]{35}([^A-Za-z0-9_-]|$)|(^|[^A-Za-z0-9_-])eyJ[A-Za-z0-9_-]{10,}[.][A-Za-z0-9_-]{10,}[.][A-Za-z0-9_-]{10,}([^A-Za-z0-9_-]|$)|(OPENAI_API_KEY|AWS_SECRET_ACCESS_KEY|GITHUB_TOKEN|GH_TOKEN)[[:space:]]*=[[:space:]]*[A-Za-z0-9_./+=:-]{8,}'

source_files |
  while IFS= read -r path; do
    if LC_ALL=C grep -Iq . "$path" 2>/dev/null; then
      matches="$(LC_ALL=C grep -nE -- "$secret_content_pattern" "$path" 2>/dev/null || :)"
      if [ -n "$matches" ]; then
        printf '%s\n' "$matches" | sed "s|^|$path:|" >>"$content_hits"
      fi
    fi
  done

if [ -s "$content_hits" ]; then
  sed -n '1,40p' "$content_hits" >&2
  fail "possible committed secret or private-key content markers found"
fi

printf 'secret_material_guard: ok\n'
