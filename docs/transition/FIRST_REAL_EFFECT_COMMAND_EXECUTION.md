# First Real Effect: Guarded Command Execution

**Status:** Design in progress (post v0.3.0edge)
**Priority:** Highest for making Latticra actually useful

## Rationale

The single most useful narrow effect Latticra can provide early is **safe, contract-bound, fully evidenced command execution**.

This directly serves:
- AI agent tool use (with strong boundaries)
- Automated operations with audit trails
- "Run this only if these conditions are met" workflows
- Complementing host systems without replacing them

## Scope for v0.4-era First Implementation

**In scope:**
- Execute commands only from an explicitly declared allowlist (or exact command + args)
- Capture full evidence: command, args, env (redacted), cwd, uid, start/end time, stdout/stderr (bounded), exit code, resource usage summary
- Integrate with existing Seal (for cryptographic approval where required) + Nucleus + Runtime Boundary
- Support both "preview/report only" and "actually execute" modes via the Effect Gate
- Operator confirmation hooks for high-impact commands
- Rollback/undo hooks where practical (future)

**Out of scope for first cut:**
- Arbitrary shell interpretation (no `sh -c` with untrusted input)
- Network-bound commands by default (can be explicitly allowed under contract)
- Privileged execution (starts as user-level only)
- Long-running services (focus on discrete commands first)

## Integration Points

- `nucleus_task` will gain a new request kind: `LATTICRA_NUCLEUS_TASK_COMMAND_EXECUTION`
- Effect class: `LATTICRA_NUCLEUS_TASK_EFFECT_LOCAL_MUTATION` or a new specific one
- New effect type in the Effect Dispatcher
- Evidence written through the existing evidence layer (with optional Q-Seal signing later)

## Security / Boundary Posture

- Denied by default
- Explicit allowlist required in the contract
- Full pre-execution validation via existing Lat/LIR + boundary systems
- All execution goes through the Effect Gate
- Evidence is mandatory and structured

## Success Criteria for First Cut

A user (or automated system) can:
1. Declare a contract allowing specific commands with arguments
2. Have the contract validated and approved (or auto-approved under policy)
3. Execute one of the allowed commands through Latticra
4. Receive rich, tamper-evident evidence of what was attempted and what actually happened
5. The system refuses anything not explicitly contracted

This would be the first time Latticra crosses from "describes what should happen" to "makes something happen safely."

## Next Steps (Immediate)

1. Extend nucleus task types and effect enums (if needed)
2. Design the Command Execution Contract schema
3. Implement the guarded executor (initially very conservative)
4. Wire it into the Effect Dispatcher
5. Add platform support for building effect-enabled command executor
6. Create test contracts and evidence examples
