# Using the Experimental Guarded Command Runner (v0.3.0edge+)

When built with `BUILD_PROFILE=effect-enabled`:

```sh
./build-separate/bin/latticra-effect-runner echo hello world
./build-separate/bin/latticra-effect-runner date
./build-separate/bin/latticra-effect-runner uname -a
```

Currently allowed (very small hardcoded list for safety):
- echo
- true
- false
- date
- uname

Anything else will be refused with a clear denial.

This is the first real effect Latticra can perform. It is heavily locked down and exists primarily to prove the architecture works.
