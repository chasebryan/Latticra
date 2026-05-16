# Latticra Documentation Map

Status: Draft  
Scope: Language foundation, C/C++ direction, security profile, ABI boundaries, and validation roadmap.

## Purpose

This documentation package records the current Latticra implementation direction before further engineering work continues.

The direction is intentionally evidence-bound:

- C is the narrow platform substrate.
- Restricted C++ is the governed authority layer.
- Latticra is the contract language above the implementation substrate.

This does not claim that C/C++ is automatically safe. It defines the project posture required to use C/C++ responsibly inside a security-conscious systems project.

## Documents

| Document | Purpose |
|---|---|
| `docs/architecture/LATTICRA_LANGUAGE_FOUNDATION.md` | Defines the architectural language layering and project posture. |
| `docs/security/C_CPP_SECURITY_PROFILE.md` | Defines the restricted C/C++ profile for trusted code. |
| `docs/security/C_ABI_BOUNDARY_POLICY.md` | Defines how C ABI boundaries are exposed, controlled, and reviewed. |
| `docs/roadmap/LATTICRA_C_CPP_FOUNDATION_ROADMAP.md` | Defines staged work required to make this direction real. |

## Summary

Latticra is not rejecting memory safety. Latticra is rejecting uncontrolled ecosystem dependency and replacing it with explicit security architecture, narrow unsafe boundaries, hard build discipline, and validation before promotion.

Core statement:

> C is the metal. C++ is the disciplined structure. Latticra is the contract.

## External guidance used for alignment

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

## Promotion rule

No future claim about Latticra security should be promoted unless the relevant code, tests, documentation, and review evidence support it.
