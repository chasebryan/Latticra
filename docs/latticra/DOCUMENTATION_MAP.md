# Latticra Documentation Map

Status: active documentation map
Last updated: 2026-05-26 CDT
Scope: reader routes, foundation documents, C/C++ direction, security profile, ABI boundaries, platform lanes, subsystem handbooks, and validation posture.

## Purpose

This map records how the Latticra documentation set is meant to fit together.

For the public front door, start with [`../../README.md`](../../README.md). For the deeper documentation route, use [`../README.md`](../README.md). For the exhaustive architecture and operations index, use [`../FOUNDATION_INDEX.md`](../FOUNDATION_INDEX.md). This file explains the relationship between those layers and the older C/C++ foundation package that originally lived here.

## Documentation Layers

| Layer | Purpose | Primary entry |
| --- | --- | --- |
| Documentation hub | Deeper route through the whole documentation set | [`../README.md`](../README.md) |
| Public project overview | Product identity, current status, quick start, and non-claims | [`../../README.md`](../../README.md) |
| Live status | Current public posture, estimates, status records, announcements | [`../../STATUS.md`](../../STATUS.md), [`../status/CURRENT_STATUS.md`](../status/CURRENT_STATUS.md), [`../status/README.md`](../status/README.md) |
| Foundation index | Full project operations, architecture, implementation, and guard index | [`../FOUNDATION_INDEX.md`](../FOUNDATION_INDEX.md) |
| System handbook | Project-level book for the durable Latticra story | [`../latticra-system-substrate/README.md`](../latticra-system-substrate/README.md) |
| Seal subsystem | Focused trust-boundary and report-only Seal docs | [`../latticra-seal/README.md`](../latticra-seal/README.md) |
| Installer docs | Panel installer authority, configuration, receipts, and evidence | [`../../installer/docs/README.md`](../../installer/docs/README.md) |
| Project notes | Short direction and queue notes | [`../project_notes/README.md`](../project_notes/README.md) |

## C/C++ Foundation Package

The C/C++ foundation direction remains active and is intentionally evidence-bound:

- C is the narrow platform substrate.
- Restricted C++ is the governed authority layer.
- Latticra is the contract language above the implementation substrate.

This does not claim that C/C++ is automatically safe. It defines the project posture required to use C/C++ responsibly inside a security-conscious systems project.

| Document | Purpose |
| --- | --- |
| [`../architecture/LATTICRA_LANGUAGE_FOUNDATION.md`](../architecture/LATTICRA_LANGUAGE_FOUNDATION.md) | Defines the architectural language layering and project posture. |
| [`../security/C_CPP_SECURITY_PROFILE.md`](../security/C_CPP_SECURITY_PROFILE.md) | Defines the restricted C/C++ profile for trusted code. |
| [`../security/C_ABI_BOUNDARY_POLICY.md`](../security/C_ABI_BOUNDARY_POLICY.md) | Defines how C ABI boundaries are exposed, controlled, and reviewed. |
| [`../roadmap/LATTICRA_C_CPP_FOUNDATION_ROADMAP.md`](../roadmap/LATTICRA_C_CPP_FOUNDATION_ROADMAP.md) | Defines staged work required to make this direction real. |
| [`../C_CPP_FOUNDATION_DIRECTION.md`](../C_CPP_FOUNDATION_DIRECTION.md) | Records the active C is the metal, C++ is the disciplined structure, Latticra is the contract direction. |
| [`../CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md`](../CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md) | Defines the guarded C++ authority-layer contract before broad authority is allowed. |

## Platform and Product Lanes

| Lane | Entry points | Current posture |
| --- | --- | --- |
| Panel installer | [`../../installer/README.md`](../../installer/README.md), [`../../installer/docs/README.md`](../../installer/docs/README.md) | User-local, dry-run-first, no root, no network authority. |
| macOS installer lane | [`../MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md`](../MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md), [`../MACOS_COMMIT_GATE_CONTRACT.md`](../MACOS_COMMIT_GATE_CONTRACT.md) | No-effect probes and dry-run planning; no `.app` write or signing claim. |
| Fedora | [`../FEDORA_DEVELOPER_WORKFLOW.md`](../FEDORA_DEVELOPER_WORKFLOW.md), [`../../packaging/fedora/README.md`](../../packaging/fedora/README.md) | Local-only package and validation lanes; no Fedora approval. |
| Ubuntu | [`../UBUNTU_DEVELOPER_WORKFLOW.md`](../UBUNTU_DEVELOPER_WORKFLOW.md), [`../../packaging/ubuntu/README.md`](../../packaging/ubuntu/README.md) | Local-only deb draft and static checks; no archive or PPA readiness. |
| openSUSE | [`../OPENSUSE_DEVELOPER_WORKFLOW.md`](../OPENSUSE_DEVELOPER_WORKFLOW.md), [`../../packaging/opensuse/README.md`](../../packaging/opensuse/README.md) | Local-only RPM maintenance draft; no OBS publication or official package claim. |

## Summary

Latticra is not rejecting memory safety. Latticra is rejecting uncontrolled authority and replacing it with explicit security architecture, narrow unsafe boundaries, hard build discipline, and validation before promotion.

Core statement:

> C is the metal. C++ is the disciplined structure. Latticra is the contract.

## External Guidance Used For Alignment

These sources are used as security-alignment references, not as project endorsements:

- NSA/CISA, "Memory Safe Languages: Reducing Vulnerabilities in Modern Software Development"  
  https://media.defense.gov/2025/Jun/23/2003742198/-1/-1/0/CSI_MEMORY_SAFE_LANGUAGES_REDUCING_VULNERABILITIES_IN_MODERN_SOFTWARE_DEVELOPMENT.PDF
- NSA press release for the NSA/CISA memory-safe languages CSI  
  https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4223298/nsa-and-cisa-release-csi-highlighting-importance-of-memory-safe-languages-in-so/
- SEI CERT C and C++ Coding Standards  
  https://www.sei.cmu.edu/library/sei-cert-c-and-c-coding-standards/
- SEI CERT C++ Coding Standard  
  https://cmu-sei.github.io/secure-coding-standards/sei-cert-cpp-coding-standard/
- C++ Core Guidelines  
  https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

## Promotion Rule

No future claim about Latticra security, runtime authority, host protection, package readiness, boot readiness, or production maturity should be promoted unless the relevant code, tests, documentation, and review evidence support it.
