# Fedora VM CLI Payload README Alignment Status

Status: README/status alignment
Date: 2026-05-26
Scope: root README wording after accepted disposable Fedora VM CLI payload validation evidence was recorded.

## Summary

The root README now records the narrow Fedora CLI payload posture supported by the accepted disposable VM evidence:

```text
fedora_vm_cli_payload_validation_status=evidence-recorded
disposable_vm_cli_validation_transcript_present=1
disposable_vm_cli_validation_completed=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

This wording is limited to the no-effect CLI payload validated in a disposable Fedora VM.

It does not claim production readiness, Fedora approval, Fedora distribution readiness, immutable Fedora readiness, daily-driver safety, security capability, update safety, recovery safety, sandboxing, malware prevention, ransomware prevention, or OS-replacement readiness.

## Evidence linked

The README links to:

```text
docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md
docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_README_ALIGNMENT_STATUS.md
packaging/fedora/latticra.spec
```

## README wording boundaries

The README must preserve these boundaries:

```text
validated path is disposable Fedora VM only
validated payload includes /usr/bin/latticra
validated payload includes /usr/share/doc/latticra/README.md
validated CLI mode is no-effect
validated runtime_behavior is disabled
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

The README must not claim:

```text
production ready
Fedora approved
Fedora distribution ready
daily-driver safe
immutable Fedora ready
security product
update safety
recovery safety
sandboxing
malware prevention
ransomware prevention
bootable OS replacement
kernel runtime ready
```

## Guard validation

This README alignment is guarded by:

```sh
sh scripts/test-fedora-vm-cli-payload-readme-alignment.sh
```

Expected output:

```text
fedora_vm_cli_payload_readme_alignment: ok
```

## Next recommended lane

```text
Plan the next Fedora CLI payload validation lane without widening README or announcement claims beyond disposable Fedora VM evidence
```

## Non-claims

This status record is not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, update safety, recovery safety, malware prevention, ransomware prevention, sandboxing, or a production installer claim.
