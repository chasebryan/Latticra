# Using the Experimental Guarded Command Runner (v0.3.0edge+)

Build with effect-enabled profile first:
```sh
BUILD_PROFILE=effect-enabled make build-separate-platform-effect
# or
BUILD_PROFILE=effect-enabled make build-separate-effect-runner
```

## Basic Usage

```sh
./build-separate/bin/latticra-effect-runner echo "hello from guarded execution"
./build-separate/bin/latticra-effect-runner date
./build-separate/bin/latticra-effect-runner uname -a
```

## Extending the Allowlist (for safe experimentation)

Set the environment variable (colon-separated):

```sh
export LATTICRA_EFFECT_ALLOWLIST="echo:date:uname:ls:pwd:whoami"
./build-separate/bin/latticra-effect-runner ls -la
```

Or create a file `effect-allowlist.txt` in the current directory (one command per line) and the runner will read it.

Currently the runner only supports simple commands + args. No shell interpretation, pipes, or redirection for safety.

This is the first real effect Latticra can perform. Everything is still heavily locked down and designed to produce rich evidence.
