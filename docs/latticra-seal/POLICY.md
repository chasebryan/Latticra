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
