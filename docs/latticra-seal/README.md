# Latticra Seal Documentation

> **Documentation update:** The former standalone Latticra Seal handbook has been superseded as the main project book by **The Latticra System Substrate: An Effect at Modern Security**.
>
> - [System Substrate documentation landing page](../latticra-system-substrate/)
> - [System Substrate PDF](../latticra-system-substrate/the-latticra-system-substrate.pdf)
> - [System Substrate DOCX](../latticra-system-substrate/the-latticra-system-substrate.docx)
>
> The file `latticra-seal-handbook.pdf` is retained as a compatibility path, but it now points to the System Substrate PDF content.


Latticra Seal is the verification, reporting, and policy-boundary layer inside the Latticra ecosystem.

It is designed to help Latticra describe, inspect, and verify local project/system state through bounded evidence such as manifests, hashes, receipts, policy checks, status reports, and no-effect runtime-boundary metadata.

Latticra Seal is not a separate production security product. It is not currently a malware prevention system, ransomware prevention system, sandbox, kernel enforcement layer, root installer, network authority, or runtime enforcement authority.

## Current role

Latticra Seal currently serves as:

- a local integrity and evidence surface
- a report-only verification lane
- a policy regression target
- a manifest/hash baseline mechanism
- a bridge between Latticra CLI, Latticra Panel, and future runtime-boundary work

## Documentation map

| Document | Purpose |
|---|---|
| `STATUS.md` | Current readiness and evidence status |
| `ARCHITECTURE.md` | Internal structure and subsystem model |
| `USAGE.md` | User-facing command guide |
| `POLICY.md` | Policy-denial and fail-closed behavior |
| `REPORTS.md` | Report format and interpretation |
| `BOUNDARIES.md` | Non-claims and authority limits |
| `ROADMAP.md` | Future implementation path |
| `PRODUCT.md` | Security-product spine, modes, product surfaces, and earned-capability path |

## Canonical boundary

Seal documentation must remain evidence-bound.

Do not claim:

- production security readiness
- runtime enforcement
- network authority
- root authority
- kernel integration
- SELinux integration
- systemd enforcement
- Fedora approval
- malware or ransomware prevention
- broad host protection

until those claims are implemented, tested, and documented with reproducible evidence.
