# Documentation Command Example Standard

Status: active documentation command-example standard
Last updated: 2026-05-28 CDT
Scope: Markdown command snippets, public HTML command snippets, quick-start commands, validation commands, installer commands, package commands, platform prerequisite commands, reset/uninstall commands, update commands, and any runnable example shown to readers.

## Purpose

This standard defines how Latticra documentation should present runnable commands.

Commands are product documentation. A command block can imply authority, safety, support, readiness, package approval, install scope, or host effects even when the surrounding prose is careful. This standard keeps command examples bounded, inspectable, and paired with the context a reader needs before running them.

Use it with [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md), [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md), [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md), [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md), [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), and [`NON_CLAIMS.md`](NON_CLAIMS.md).

This standard does not make commands safe. It makes their documented scope and limits visible.

## Command Example Rule

Every runnable command example should make these clear before or near the command:

```text
where to run it
what it reads or writes
whether it is no-effect, dry-run, guarded user-local, local-only, or effectful
what evidence or output the reader should expect
how to stop, reset, uninstall, or clean up if the command writes user-local state
which stronger claims remain blocked
```

If the documentation cannot state those things, keep the command out of public quick-start or public site surfaces until the missing context exists.

## Command Classes

| Command class | Required nearby context | Must not imply |
| --- | --- | --- |
| Read-only inspection | Current directory, expected output shape, and source record. | Validation, readiness, or success beyond inspection. |
| No-effect validation | Guard name, source record, expected pass/fail meaning, and non-claim boundary. | Production safety, package approval, security guarantee, or broad readiness. |
| Build command | Build scope, output location, prerequisites, and whether artifacts are local-only. | Release artifact, supported install, package approval, or distribution readiness. |
| User-local install | User-local paths, preview route, verification route, reset/uninstall route, and no root/service/kernel/network authority unless proven. | Root install, daily-driver support, unattended host mutation, or production installer readiness. |
| Update command | Source checkout boundary, preview route, verification route, rollback or reset route, and network/update authority boundary. | Trusted remote update delivery, production self-update, signed update apply authority, or automatic host mutation. |
| Reset or uninstall | Preview route when available, managed paths, preserved paths, refusal boundaries, and evidence or receipt location. | Deletion safety guarantee or permission to remove unmanaged user files. |
| Platform prerequisite | Platform name, package manager scope, why elevated privileges are used, and local-only project boundary. | Official package support, distribution approval, production installability, or vendor endorsement. |
| Package validation | Package lane, local-only or disposable environment boundary, exact guard, and blocked publication claim. | Archive readiness, official package status, or production package quality. |
| Security or crypto validation | Source baseline, exact guard, no production-protection wording, and blocked security claims. | Malware prevention, ransomware prevention, hardened sandboxing, certification, compliance, or production crypto authority. |

## Required Context Blocks

Use short prose, not heavy ceremony. The reader should see the command boundary before deciding to run it.

Good context patterns:

```text
Run from the repository root.
This is a no-effect validation command.
This writes only user-local Latticra-managed paths.
Preview first, then apply only if the preview matches the expected managed paths.
This does not prove package approval or production readiness.
```

Avoid context-free command blocks when the command:

- installs packages;
- writes files;
- starts a GUI;
- changes PATH;
- launches a background process;
- resets or removes user-local paths;
- uses `sudo`;
- fetches from the network;
- validates platform, installer, package, security, runtime, crypto, or AI posture.

## `sudo` And Network Rules

Use `sudo` only when the command is a platform prerequisite or a clearly documented cleanup path.

When `sudo` appears, the surrounding text must say why elevated privileges may be needed and what the command affects.

Network-fetching commands, package-manager refresh commands, clone commands, and update commands must not imply trusted update delivery, official package status, or production installability.

## Expected Output

When a command is a validation or guard command, state the success signal when practical.

Prefer:

```text
Expected success signal: the guard exits 0 and prints its `ok` line.
```

Avoid:

```text
This proves it works.
```

If output varies by platform, say which platform the example targets.

## Cleanup And Reset

Any command that writes user-local Latticra state should be near at least one cleanup route:

- uninstall;
- reset;
- receipt location;
- managed path list;
- refusal boundary for unmanaged files;
- source record for reset or uninstall behavior.

For public quick-start paths, cleanup should be reachable without forcing the reader into the full foundation index.

## Review Triggers

Use this standard when a change touches:

- [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md);
- `start.html`, `examples.html`, `validation.html`, `installer.html`, `packaging.html`, or other public HTML command snippets;
- platform prerequisite commands;
- install, update, reset, uninstall, or cleanup commands;
- guard or validation command lists;
- package build or package validation commands;
- security, runtime, crypto, or AI validation commands.

Use [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) when the command example changes public claim posture, effect boundaries, validation meaning, cleanup expectations, or platform posture.

## Boundary

This standard governs documentation for command examples only.

It does not change command behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.
