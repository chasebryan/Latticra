# Supply Chain Security Baseline

Status: supply-chain security baseline
Scope: repository workflows, quality guards, local guard scripts, package fixture archives, installer/package lanes, and public security non-claims.

## Purpose

This baseline records the current repository supply-chain posture for Latticra.

It focuses on repository-controlled automation and local fixture generation. It does not claim production release security, artifact signing, deployment security, registry trust, dependency freshness, vulnerability remediation, or package approval.

This document does not grant release, deployment, network, package-manager, secret, OIDC, write-token, or source-mutation authority.

## Current Baseline

```text
workflow_triggers_limited_to_push_and_pull_request=1
out_of_band_workflow_triggers_require_dedicated_review=1
deployment_environment_use_requires_dedicated_review=1
github_expression_interpolation_requires_dedicated_review=1
external_actions_must_be_commit_pinned=1
checkout_persist_credentials_false_required=1
workflow_token_permissions_read_only=1
workflow_secrets_disallowed_without_dedicated_review=1
implicit_github_token_surfaces_disallowed_without_dedicated_review=1
remote_pipe_to_shell_disallowed=1
package_manager_commands_allowlisted=1
source_archive_fixture_requires_reviewed_symlink_guard=1
reproducible_source_archive_metadata_required=1
```

## Workflow Rules

GitHub workflows remain on the narrow reviewed automation path:

```text
allowed_trigger_push=1
allowed_trigger_pull_request=1
schedule_trigger_allowed=0
workflow_run_trigger_allowed=0
workflow_call_trigger_allowed=0
workflow_dispatch_trigger_allowed=0
repository_dispatch_trigger_allowed=0
deployment_environment_allowed=0
github_expression_interpolation_allowed=0
write_token_permission_allowed=0
broad_token_permission_allowed=0
pull_request_target_allowed=0
repository_secret_consumption_allowed=0
implicit_github_token_consumption_allowed=0
```

External GitHub Actions must be pinned to approved 40-character commit SHAs. Checkout steps must set `persist-credentials: false`.

## Script Rules

Repository shell guards must keep fail-fast behavior, avoid `eval`, avoid remote pipe-to-shell patterns, avoid unsafe broad mutation commands, and register cleanup traps for temporary work directories.

Package-manager commands are only allowed in reviewed bootstrap workflows. Any new package-manager lane must receive a dedicated review guard before it joins the quality aggregate.

## Source Archive Rules

Source archive fixtures must be temporary and local. They must exclude VCS metadata, RPM work directories, RPM artifacts, and nested source archives.

Archive creation must refuse symlink entries and normalize tar metadata for deterministic fixture output. Source archive fixtures remain evidence for shape and boundary only; they do not publish packages, run RPM builds, install Latticra, or claim distribution approval.

## Validation

This baseline is guarded by:

```sh
sh scripts/test-supply-chain-security-baseline.sh
sh scripts/test-quality-safety-guards.sh
sh scripts/test-fedora-source-archive-fixture-lane.sh
```

The repository quality aggregate must include `quality-security-standards` so the baseline runs with the main local quality gate.

## Non-Claims

This baseline does not claim complete supply-chain security, dependency vulnerability coverage, reproducible release builds, signed release enforcement, deployment protection, package-manager trust, registry trust, maintainer account protection, or production readiness.
