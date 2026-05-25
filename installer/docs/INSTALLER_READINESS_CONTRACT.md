# Installer Readiness Contract

The Latticra installer is allowed to exist before it is production-ready, but it must be honest about its authority and maturity.

## Current authority

```text
production_installer_ready=0
root_authority=0
network_authority=0
runtime_enforcement_authority=0
```

## Current allowed behavior

- Generate configuration.
- Generate an install plan.
- Execute a dry-install.
- Write local operator receipts.
- Create a guarded user-local prefix when explicitly authorized.
- Create component markers and placeholder developer shims for validation.
- Reset or uninstall a guarded user-local prefix by removing managed wrappers, desktop metadata, known Panel icons, and the managed prefix.

## Current forbidden behavior

- Do not request root.
- Do not write into `/usr`, `/bin`, `/sbin`, `/etc`, `/System`, or other system directories.
- Do not fetch dependencies from the network.
- Do not silently overwrite files when preserve mode is enabled.
- Do not claim the host is protected by Latticra Seal enforcement.
- Do not claim production installer readiness.

## Promotion requirements

Before this installer can become a production installer, the repo needs documented evidence for:

- component manifest integrity
- artifact hashing
- rollback
- upgrade
- uninstall
- failed-install recovery
- Fedora/Linux target validation
- Latticra Seal report generation
- package-manager-safe integration strategy
