# Ubuntu lintian Availability Lane

Status: active tool availability lane
Scope: verify that lintian is available in an Ubuntu Linux environment.

## Purpose

This lane prepares the next packaging validation step without linting or building the Latticra package draft yet.

The current goal is only to prove that `lintian` can be installed and invoked inside the Ubuntu compatibility environment.

## Files

```text
docs/UBUNTU_LINTIAN_AVAILABILITY.md
scripts/test-ubuntu-lintian-availability.sh
.github/workflows/ubuntu-lintian-availability.yml
docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md
```

## Checks

This lane checks:

```text
Ubuntu environment marker exists
apt-get is available
lintian installs
lintian command is available
lintian version command can run
local deb static validation lane remains green
```

## Boundary

This lane does not lint the Latticra deb draft yet.

It does not run `dpkg-buildpackage`, `debuild`, `sbuild`, or `pbuilder`.

It does not create package artifacts.

It does not submit Latticra to Ubuntu, create a PPA, or claim Ubuntu archive readiness.

## Next Slice

Recommended next slice:

```text
Review the Ubuntu lintian static metadata contract after package license promotion is unblocked.
Keep lintian execution, lintian finding classification, build transcript evidence, and deb artifact creation blocked until package notice and license prerequisites are reviewed.
```

That future lane may run `lintian` against the local debian metadata or a locally built artifact and classify expected draft findings separately from unexpected package findings. The current static metadata contract records the evidence shape without running lintian.

## Validation

Run inside Ubuntu:

```sh
sh scripts/test-ubuntu-lintian-availability.sh
```

Expected output:

```text
ubuntu_lintian_availability: ok
```
