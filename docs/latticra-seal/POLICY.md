# Latticra Seal Policy

Latticra Seal policy exists to define what Seal is allowed to inspect, verify, report, deny, or pass.

The policy layer should be conservative by default.

## Policy goals

Seal policy should:

- make allowed scope explicit
- reject unsupported authority
- deny unsafe assumptions
- produce readable denial reasons
- support regression testing
- keep Latticra evidence-bound

## Fail-closed principle

When policy input is malformed, incomplete, unsupported, or contradictory, Seal should fail closed.

Failing closed means:

```text
do not silently pass
do not guess intent
do not grant authority
do not claim enforcement
emit a clear denial reason
```

## Denial examples

Policy should deny:

- unknown authority modes
- network authority requests
- runtime enforcement claims
- root installation claims
- paths outside declared scope
- malformed manifests
- missing required metadata
- unsupported cryptographic claims

## Policy regression

The policy regression lane should prove that unsafe or unsupported states are denied.

The native v0.1 CLI does not enforce large-binary denial. If
`[policy].deny_large_binaries` is present, it must be `false`; if
`[policy].max_file_size_mb` is present, it must be `25`. Non-default,
duplicate, or malformed large-binary policy declarations must fail closed
before native hash-list promotion.

The native CLI reads filename deny patterns from
`[policy.deny_filenames].patterns` and content marker parts from
`[policy.deny_contents].pattern_parts` in `latticra.seal`. Missing, duplicate,
or malformed deny policy arrays must fail closed. Missing or doubled comma
separators are malformed. Quoted array tokens must not use backslash escapes
or raw control bytes. Nested content marker parts must be non-empty. Filename
deny patterns must not include path separators, control characters,
backslashes, bare `*`, or multiple wildcards.

The native CLI reads required file paths from
`[policy.required_files].paths` in `latticra.seal`. Missing, duplicate, or
malformed required-file arrays must fail closed. Required-file paths must stay
relative to the project root and must not include `.` or `..` segments,
wildcards, control characters, backslashes, backslash escapes, absolute paths,
or directory paths.

The native CLI also reads `[paths].include` and `[paths].exclude` from
`latticra.seal` before policy and digest scans. Unsupported path scopes must
fail closed. Exclude patterns must stay relative to the project root and must
not include `.` or `..` path segments, control characters, backslashes,
backslash escapes, absolute paths, or multiple wildcards.

Expected local command:

```sh
make seal-policy-denials
```

Expected CI lane:

```text
Latticra Seal Policy
```

## Correct policy wording

Seal policy verifies whether local evidence matches declared expectations.

## Incorrect policy wording

Seal policy does not currently enforce runtime behavior, block malware, isolate processes, protect the kernel, or provide production host security.
