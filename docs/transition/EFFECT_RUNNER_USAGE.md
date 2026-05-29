# Using the Experimental Guarded Command Runner (v0.3.0edge+)

## Easiest way on macOS (recommended for demos)

```sh
# One command for a focused, impressive demo
make build-separate-demo-quick
# or
BUILD_PROFILE=effect-enabled make build-separate-demo
```

This will:
- Build the effect runner
- Create a safe default allowlist
- Exercise real guarded command execution
- Generate Dashboard + Q-Seal report

## Manual build + run

```sh
BUILD_PROFILE=effect-enabled make build-separate-effect-runner
```

Then run:

```sh
export LATTICRA_EFFECT_ALLOWLIST="effect-allowlist.txt"
./build-separate/bin/latticra-effect-runner echo "hello from the effect layer"
./build-separate/bin/latticra-effect-runner date
```

The root `effect-allowlist.txt` (checked into the repo) contains a safe default set.

## How the allowlist works

- `LATTICRA_EFFECT_ALLOWLIST` env var (colon-separated commands, or path to a file)
- Falls back to `effect-allowlist.txt` in current directory

This is the first real effectful capability in Latticra. Use it to show that the system can now actually execute (guarded) commands while producing evidence.
