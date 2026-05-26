# Documentation Validation Playbook

Status: active documentation validation playbook
Last updated: 2026-05-26 CDT
Scope: documentation-only validation commands, link checks, public-entry checks, estimate checks, subsystem guards, platform guards, and failure handling.

## Purpose

This playbook explains which validation checks to run for documentation-only changes.

Use it with [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), and [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md).

Validation should prove only the documentation claim being made. It should not be used to imply production readiness, security guarantees, installer authority, package approval, runtime authority, or product readiness.

## Validation Levels

| Level | Use when | Minimum checks |
| --- | --- | --- |
| Hygiene | Any documentation file changes. | `git diff --check`, trailing-whitespace check. |
| Local links | New or changed Markdown links. | Local Markdown link sanity check over touched files. |
| Public entry | README, docs hub, map, public site pages, status index, project notes, or strategy docs change. | `sh scripts/test-project-strategy-status-framework.sh`. |
| Estimate mirror | Completion estimates or public estimate tables change. | `sh scripts/test-current-estimate-table-source-alignment.sh`. |
| Seal docs | Seal README, Seal status, Seal public wording, or Seal source records change. | `sh scripts/test-latticra-seal-docs.sh` plus exact Seal guard. |
| Platform docs | Fedora, Ubuntu, openSUSE, Debian, FreeBSD, OpenBSD, macOS, installer, or package posture changes. | Platform workflow guard plus exact platform guard. |
| Subsystem docs | Runtime, Nucleus, Lat, LIR, L-UI, Nadia, boot preview, security, installer, or package source record changes. | Exact guard named by the source or status record. |
| Claim promotion | Public wording becomes stronger. | Stop unless contract, implementation, validation, status, non-claim update, traceability, and public-entry alignment all exist. |

## Minimum Documentation-Only Check

Run this for most documentation-only changes:

```sh
git diff --check
sh scripts/test-project-strategy-status-framework.sh
```

Add a local link check for changed Markdown files when links are added or moved.

## Local Link Check

Use a local Markdown link sanity check on the files you touched:

```sh
perl -MFile::Basename=dirname -e 'my $bad=0; for my $file (@ARGV) { open my $fh, q{<}, $file or die qq{$file: $!\n}; my $base = dirname($file); while (my $line = <$fh>) { while ($line =~ /\[[^\]]+\]\(([^)]+)\)/g) { my $target = $1; next if $target =~ /^(https?:|mailto:|#)/; $target =~ s/#.*\z//; next if $target eq q{}; my $path = $target =~ m{^/} ? $target : qq{$base/$target}; unless (-e $path) { print qq{$file:$.: missing $target\n}; $bad=1; } } } } exit $bad' FILES...
```

This check is intentionally local. It does not prove that a public claim is true; it only catches broken repository links.

## Estimate And Status Checks

Run the estimate source-alignment guard when a change touches:

- public estimate tables;
- overall completion percentage;
- status dashboard estimate text;
- roadmap estimate text;
- `README.md`, `STATUS.md`, or `docs/status/CURRENT_STATUS.md` estimate mirrors.

```sh
sh scripts/test-current-estimate-table-source-alignment.sh
```

If this guard fails because source records and mirrors disagree, do not hand-edit the guard to force a pass. Fix the documented source or mirror drift, or keep the public claim unchanged.

## Platform Checks

Add platform guards when platform or package docs change:

```sh
sh scripts/test-fedora-developer-workflow.sh
sh scripts/test-ubuntu-developer-workflow.sh
sh scripts/test-opensuse-developer-workflow.sh
```

Also run the exact guard named by the platform source record when the change is narrower than the general workflow.

Examples:

```text
Fedora RPM static validation -> run the Fedora static validation guard.
Ubuntu notice/license wording -> run the Ubuntu notice or license guard.
openSUSE rpmlint/osc wording -> run the openSUSE rpmlint or osc guard.
macOS reset/uninstall wording -> run the matching macOS reset/uninstall guard.
```

## Seal Checks

Run the Seal docs guard when any Seal public wording, Seal status row, Seal README, Seal public-entrypoint alignment, or Seal source record changes:

```sh
sh scripts/test-latticra-seal-docs.sh
```

Also run the exact Seal guard named by the changed status or implementation record when applicable.

## Security Checks

Security documentation changes should always preserve security non-claims.

For security wording changes, validate:

1. [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) does not block the wording.
2. [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md) permits the terminology.
3. [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) identifies the source and non-claim boundary.
4. The exact security, threat-model, supply-chain, memory-safety, or runtime-authority guard named by the source record passes.

## Failure Handling

When a documentation validation fails:

1. Read the failing message before editing.
2. Identify whether the failure is link drift, mirror drift, status drift, guard expectation drift, or claim drift.
3. Fix the documentation source or mirror that is wrong.
4. Do not weaken non-claims to make a public summary sound better.
5. Do not edit guard scripts for documentation-only convenience.
6. If the stronger wording lacks evidence, demote the wording and record the blocked claim in the review packet.

## Review Packet Fields

When using [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), put the selected commands in `validation_commands`.

Use `blocked_missing_validation` when a claim would require a guard or evidence record that does not exist yet.

Use `blocked_public_entry_drift` when public pages and source records disagree.

Use `accepted_navigation_only` only when links or route ordering changed without changing claims.

## Boundary

This playbook validates documentation hygiene, traceability, and public-entry consistency.

It does not validate production runtime behavior, installer safety, package publication, platform approval, security guarantees, host protection, network protection, cryptographic authority, or AI-agent execution control.
