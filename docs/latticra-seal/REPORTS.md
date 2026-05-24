# Latticra Seal Reports

Latticra Seal reports are evidence records.

A report should be readable by a human and stable enough for future tooling.

## Report goals

A Seal report should answer:

- what was checked
- when it was checked
- where it was checked
- what mode was used
- what passed
- what failed
- what changed
- what authority was not used

## Required report fields

Recommended fields:

```text
timestamp_utc=
mode=
prefix=
kernel=
os=
network_authority=
runtime_enforcement_authority=
root_authority=
manifest_present=
lock_present=
hashes_checked=
hashes_changed=
warnings=
failures=
status=
```

## Report modes

### report-only

The default safe mode.

Report-only mode may inspect and describe local state, but should not enforce runtime behavior or mutate system state.

### verification

Verification mode compares current state against declared expectations.

Verification may fail when files are missing, changed, malformed, or outside policy.

### future enforcement

Future enforcement must not be claimed until implemented and tested.

## PASS meaning

PASS means the checked evidence matched the declared local expectations for that command.

PASS does not mean the host is secure.

## FAIL meaning

FAIL means the checked evidence did not match expectations, policy denied the state, or Seal could not safely complete the check.

FAIL should include a reason.
