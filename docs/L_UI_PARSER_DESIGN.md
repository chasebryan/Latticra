# Latticra L-UI Parser Design Contract

Status: parser design contract
Scope: parser behavior, no-effect constraints, error categories, fixture expectations, and non-claims before parser implementation.

## Purpose

This document defines the design contract for a future L-UI parser.

The parser should be introduced only after the L-UI grammar draft and fixtures are stable enough to justify implementation.

This document does not implement a parser.

## Current boundary

The current project state includes:

```text
L-UI source grammar draft
.lui fixture
static fixture guard script
static C report fixture
```

The current project state does not include:

```text
L-UI parser
renderer engine
interactive UI
command execution
Nucleus execution
live movement
server interaction
update behavior
hardware behavior
boot behavior
recovery behavior
```

## Parser role

A future L-UI parser should read `.lui` source and produce a no-effect parse result.

Input:

```text
source bytes
source length
optional source name
```

Output:

```text
parse status
error category
error location
normalized fixture summary
no-effect proof flags
```

## Parser must not

The parser must not:

- execute commands;
- render UI;
- call Nucleus execution;
- mutate state;
- perform live movement;
- perform recovery behavior;
- perform update behavior;
- interact with servers;
- access networking;
- access hardware;
- change boot state;
- perform host effects;
- perform external effects;
- allocate hidden persistent state;
- silently accept unknown effect declarations.

## Allowed parser behavior

A future parser may:

- scan source;
- tokenize source;
- validate required clauses;
- validate allowed rails;
- validate allowed bindings;
- validate string literals;
- validate `effect none`;
- validate `boundary preview_only`;
- return deterministic errors;
- return a normalized no-effect summary.

## Error categories

Initial parser error categories should include:

```text
ok
null_argument
empty_source
unsupported_version
missing_card
missing_purpose
missing_effect
unsupported_effect
missing_boundary
unsupported_boundary
missing_rail
unknown_rail
unknown_binding_prefix
missing_required_binding
unterminated_string
unbalanced_brace
forbidden_behavior_marker
source_too_large
internal_error
```

## Source size rule

A future parser should define a maximum source size.

Initial proposed limit:

```text
64 KiB
```

The parser must reject oversized source rather than reallocating without bounds.

## Required fixture behavior

The first parser target should accept:

```text
examples/l-ui/nucleus-preview-card.lui
```

The parser must confirm:

- version is `lui 0.1`;
- card name is `NucleusPreview`;
- purpose exists;
- effect is `none`;
- boundary is `preview_only`;
- required rails exist;
- required bindings exist;
- forbidden behavior markers are absent.

## Required rails

The first parser target must recognize:

```text
top
state
trace
safety
gates
effects
policy
execution
bottom
```

## Required binding prefixes

Initial allowed binding prefixes:

```text
state.
preview.
```

No other prefix should be accepted until documented.

## Effect validation

Only this effect declaration is valid for the first parser target:

```text
effect none
```

Examples that must be rejected:

```text
effect read
effect local_mutation
effect host_mutation
effect network
effect hardware
effect boot
effect recovery
effect external
```

## Boundary validation

Only this boundary is valid for the first parser target:

```text
boundary preview_only
```

Any other boundary should be rejected until documented.

## Forbidden markers

Parser and fixture guards should reject markers that imply behavior outside static report layout:

```text
execute
host_mutation
network
hardware
boot
recovery
self_update
server call
server_interaction {
```

Future syntax may refine this list, but the first parser must be conservative.

## Parse result shape

A future parse result may use a C structure similar to:

```text
status
error
line
column
card_name
rail_count
field_count
effect
boundary
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
```

Required no-effect flags:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Test plan for future parser implementation

Future parser tests should verify:

- valid fixture parses successfully;
- unsupported version is rejected;
- missing card is rejected;
- missing purpose is rejected;
- missing effect is rejected;
- unsupported effect is rejected;
- missing boundary is rejected;
- unsupported boundary is rejected;
- missing required rail is rejected;
- missing required binding is rejected;
- unknown binding prefix is rejected;
- forbidden behavior marker is rejected;
- oversized source is rejected;
- parser returns no-effect flags for valid fixtures.

## Implementation gate

Parser code should not be added until:

1. this design contract is merged;
2. fixture guardrails pass;
3. parser error categories are reviewed;
4. parse result shape is approved;
5. no-effect invariants are explicit in tests.

## Current validation command

This design contract is guarded by:

```sh
sh scripts/test-l-ui-parser-design.sh
```

The guard is static. It does not parse L-UI.

## Non-claims

This document does not implement L-UI parsing, rendering, command execution, Nucleus execution, live movement, origin mutation, recovery execution, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
