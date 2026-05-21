# Latticra No-Effect CLI Packaging Contract Alignment

Status: packaging/spec alignment record
Evidence level: 7 packaging alignment, local guard only
Scope: Fedora RPM spec transition for the no-effect `latticra` CLI payload.

## Purpose

The no-effect CLI status surface now exists as a local guarded C implementation.

This record aligns the Fedora RPM spec transition that adds the no-effect CLI payload to the local RPM draft.

This is packaging/spec alignment only.

It updates `packaging/fedora/latticra.spec` for the CLI payload.

It does not build a new RPM in CI.

It does not install or remove an RPM.

It does not run disposable Fedora VM validation.

It does not claim host install readiness for the CLI payload.

## Alignment header

```text
LATTICRA NO-EFFECT CLI PACKAGING CONTRACT ALIGNMENT
packaging_alignment_version=2
cli_payload_contract_present=1
cli_status_surface_implemented=1
cli_packaging_alignment_present=1
fedora_spec_updated_for_cli=1
rpm_payload_expansion_performed=1
rpm_payload_validated=0
```

## Historical validated package boundary

The current evidence-backed Fedora validation record still applies only to the earlier documentation-only local RPM:

```text
validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm
validated_payload=/usr/share/doc/latticra/README.md
validated_payload_remains_documentation_only=1
historical_disposable_vm_rpm_evidence_remains_limited=1
```

That historical evidence does not validate the new CLI payload.

## Current spec payload target

The local Fedora spec now targets this payload shape:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

Because the CLI is a compiled C executable, the spec no longer declares:

```text
BuildArch: noarch
```

The spec transition records:

```text
rpm_contains_compiled_c_binary=1
buildarch_noarch_removed=1
cli_binary_install_mode=0755
doc_install_mode=0644
```

## Required spec properties

The spec must verify the local CLI guard before compiling/installing the binary:

```text
sh scripts/test-latticra-no-effect-cli-status-surface.sh
cc %{optflags} -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra
install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra
install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md
%{_bindir}/latticra
%doc %{_docdir}/%{name}/README.md
```

## Forbidden payload surfaces for this lane

The no-effect CLI packaging lane must not add:

```text
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
/usr/share/selinux
```

The spec must also avoid service activation, package-manager actions, network actions, boot changes, kernel-module installation, and SELinux policy installation.

## Future disposable Fedora VM validation requirements

After this spec-update lane, a separate disposable Fedora VM validation transcript must record:

```text
expanded_payload_validation_transcript_present=1
cli_binary_present_after_install=1
cli_status_command_recorded=1
cli_version_command_recorded=1
cli_report_command_recorded=1
cli_status_output_matches_contract=1
cli_no_root_required=1
cli_no_host_mutation_observed=1
cli_no_network_observed=1
rpm_verify_completed=1
removal_validation_performed=1
cli_removed_after_rpm_removal=1
post_removal_cli_absence_verified=1
```

Until that transcript exists, the CLI payload remains unvalidated from a disposable Fedora VM packaging perspective.

## Current readiness classification

```text
cli_payload_contract_present=1
cli_status_surface_implemented=1
cli_packaging_alignment_present=1
fedora_spec_updated_for_cli=1
rpm_payload_expansion_performed=1
rpm_payload_validated=0
disposable_vm_cli_validation_completed=0
host_install_ready_for_cli_payload=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Validation

```sh
sh scripts/test-latticra-no-effect-cli-packaging-contract-alignment.sh
```

Expected output:

```text
latticra_no_effect_cli_packaging_contract_alignment: ok
```

## Next recommended lane

```text
Add disposable Fedora VM CLI payload validation transcript contract
```

That future lane should define the evidence contract for a real disposable Fedora VM RPM validation run against the expanded `/usr/bin/latticra` payload.

## Non-claims

This alignment is not a completed RPM build transcript.

It is not installation evidence for `/usr/bin/latticra`.

It is not disposable Fedora VM validation of the CLI payload.

It is not host install readiness for the CLI payload.

It is not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, runtime behavior, Lat execution, LIR execution, service management, kernel integration, SELinux policy integration, update safety, recovery safety, malware prevention, ransomware prevention, sandboxing, or a production installer claim.
