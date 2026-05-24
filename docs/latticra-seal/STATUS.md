# Latticra Seal Status

Status: early evidence-bound verification layer  
Scope: local report-only verification, manifest/hash baseline, policy regression, and Panel integration planning.

## Current classification

Latticra Seal is currently a bounded local evidence subsystem.

It may describe local state, generate reports, compare hash baselines, and participate in policy-denial tests.

It must not be described as a production enforcement layer.

## Current evidence

Known current evidence includes:

- `latticra-seal` command wrapper installed in the local user path
- local Fedora Workstation report generation
- report-only mode
- installed component marker for `latticra-seal`
- hash lock material in `latticra.seal.lock`
- policy regression workflow through GitHub Actions
- policy-denial testing through `make seal-policy-denials`

## Current authority limits

```text
network_authority=0
runtime_enforcement_authority=0
root_authority=0
kernel_modification_performed=0
systemd_modification_performed=0
selinux_modification_performed=0
production_security_product=0
```

## Current readiness

```text
local_report_generation=1
manifest_hash_baseline=1
policy_regression_lane=1
panel_bridge_planning=1
runtime_enforcement=0
network_operation=0
root_installation=0
kernel_enforcement=0
production_readiness=0
```

## Correct public wording

Latticra Seal is an early verification and reporting layer inside Latticra. It focuses on local evidence, policy boundaries, manifest/hash baselines, and report-only system state inspection.

## Incorrect public wording

Do not say that Latticra Seal protects production systems, prevents malware, prevents ransomware, enforces runtime isolation, modifies the kernel, installs system services, or provides certified host security.
