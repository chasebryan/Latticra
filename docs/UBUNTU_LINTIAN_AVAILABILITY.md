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
Promote the Ubuntu package license expression only after documentation licensing and notice obligations are reviewed.
```

That future lane may run `lintian` against the local debian metadata or a locally built artifact and classify expected draft findings separately from unexpected package findings.

## Validation

Run inside Ubuntu:

```sh
sh scripts/test-ubuntu-lintian-availability.sh
```

Expected output:

```text
ubuntu_lintian_availability: ok
```
