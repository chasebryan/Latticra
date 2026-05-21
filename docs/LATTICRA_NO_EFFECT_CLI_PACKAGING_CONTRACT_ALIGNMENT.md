# Latticra No-Effect CLI Packaging Contract Alignment

Status: contract alignment record
Evidence level: 7 packaging alignment, contract only
Scope: future Fedora RPM payload transition for the no-effect `latticra` CLI.

## Purpose

The no-effect CLI status surface now exists as a local guarded C implementation.

This record aligns the future Fedora RPM packaging transition before the package payload is changed.

This is contract/status alignment only.

It does not update `packaging/fedora/latticra.spec`.

It does not add `/usr/bin/latticra` to the RPM payload.

It does not build a new RPM.

It does not install or remove an RPM.

It does not run disposable Fedora VM validation.

It does not claim host install readiness for the CLI payload.

## Alignment header

```text
LATTICRA NO-EFFECT CLI PACKAGING CONTRACT ALIGNMENT
packaging_alignment_version=1
cli_payload_contract_present=1
cli_status_surface_implemented=1
cli_packaging_alignment_present=1
fedora_spec_updated_for_cli=0
rpm_payload_expansion_performed=0
rpm_payload_validated=0
```

## Current validated package boundary

The current evidence-backed Fedora package remains the documentation-only local RPM:

```text
current_validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm
current_validated_payload=/usr/share/doc/latticra/README.md
current_validated_payload_remains_documentation_only=1
current_disposable_vm_rpm_evidence_remains_valid=1
```

The current spec remains a local draft with:

```text
BuildArch: noarch
%doc %{_docdir}/%{name}/README.md
```

This alignment does not change that current package boundary.

## Future RPM payload transition requirements

A future RPM payload-expansion PR may add the CLI only after the local CLI guard remains passing.

The future payload target is:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

The future payload-expansion PR must also update the packaging classification:

```text
future_rpm_contains_compiled_c_binary=1
future_rpm_buildarch_must_not_be_noarch=1
future_spec_must_remove_noarch_claim=1
future_cli_binary_install_mode=0755
future_doc_install_mode=0644
```

Because the CLI is a compiled C executable, a future RPM that includes it must not continue to present the payload as architecture-independent noarch packaging.

## Future spec guard requirements

A future spec-update guard should verify:

```text
src/latticra_cli.c_present=1
cli_local_guard_present=1
cli_local_guard_passes_before_packaging=1
fedora_spec_installs_cli_binary=1
fedora_spec_installs_readme=1
fedora_spec_does_not_install_services=1
fedora_spec_does_not_install_kernel_modules=1
fedora_spec_does_not_install_boot_files=1
fedora_spec_does_not_install_selinux_policy=1
fedora_spec_does_not_enable_services=1
fedora_spec_does_not_run_network_operations=1
```

## Forbidden future payload surfaces for this lane

The no-effect CLI packaging lane must not add:

```text
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
/usr/share/selinux
```

## Future disposable Fedora VM validation requirements

After a future spec-update PR expands the payload, a separate disposable Fedora VM validation transcript must record:

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

Until that transcript exists, the CLI payload must remain unvalidated from a Fedora VM packaging perspective.

## Current readiness classification

```text
cli_payload_contract_present=1
cli_status_surface_implemented=1
cli_packaging_alignment_present=1
fedora_spec_updated_for_cli=0
rpm_payload_expansion_performed=0
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
Update Fedora RPM spec for no-effect CLI payload without claiming VM validation
```

That future lane should compile/install the no-effect CLI into the RPM payload and record that a new disposable Fedora VM validation run is still required before any CLI payload install-readiness claim is made.

## Non-claims

This alignment is not an RPM spec update.

It is not RPM payload expansion.

It is not installation evidence for `/usr/bin/latticra`.

It is not disposable Fedora VM validation of the CLI payload.

It is not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, runtime behavior, Lat execution, LIR execution, service management, kernel integration, SELinux policy integration, update safety, recovery safety, malware prevention, ransomware prevention, sandboxing, or a production installer claim.
