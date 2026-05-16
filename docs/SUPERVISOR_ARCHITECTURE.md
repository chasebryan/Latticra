# Nucleus Supervisor Architecture

Status: initial supervisor architecture
Scope: Latticra supervisor, orchestration responsibilities, state ownership, gates, and non-claims.

## Purpose

Nucleus is the planned Latticra supervisor and orchestration core.

It should be designed from the beginning as a disciplined system supervisor, not as an experimental shell and not as a simulation loop.

## Responsibilities

Nucleus owns or coordinates:

- state lattice identity;
- transition requests;
- policy evaluation;
- effect gates;
- task orchestration;
- update staging;
- rollback visibility;
- server interaction gates;
- operator-visible reports;
- evidence records;
- language boundaries for Lat-family documents.

## Initial boundaries

Nucleus does not initially provide:

- hardware boot control;
- disk modification;
- recovery action;
- silent self-update behavior;
- kernel behavior;
- hypervisor behavior;
- security-boundary guarantees;
- general third-party code isolation;
- system integrity guarantees.

## Core components

```text
Nucleus
  State Lattice
  Policy Engine
  Effect Gate
  Task Engine
  Update Engine
  Server Gateway
  Report Engine
  Lat Boundary
  Evidence Recorder
```

### State Lattice

The State Lattice stores explicit state cells, paths, routes, axes, traces, breadcrumbs, and effect labels.

Early state must be read-only and fixture-backed.

### Policy Engine

The Policy Engine answers:

```text
Is this request allowed?
Why or why not?
What evidence level is required?
What gate is required?
What effect is possible?
```

### Effect Gate

The Effect Gate controls whether a request may produce no effect, a read effect, a local mutation, a host mutation, a network effect, a hardware effect, a boot effect, a recovery effect, or an external effect.

### Task Engine

The Task Engine handles only approved tasks.

Early implementation should support only dry-run and preview tasks.

### Update Engine

The Update Engine handles signed staged updates, channels, verification, rollback slots, and post-update validation.

It must never perform silent updates.

### Server Gateway

The Server Gateway handles optional and signed server interaction.

It must keep local operation possible unless a deployment profile explicitly requires server connectivity.

### Report Engine

The Report Engine produces operator-visible state, effect, risk, health, lock, update, and evidence reports.

### Lat Boundary

The Lat Boundary controls how Lat, L-UI, and future Lat-Orch documents are parsed, validated, and handled.

Early Lat behavior should be assertion/report only.

### Evidence Recorder

The Evidence Recorder captures validation level, source, target, effect, result, failure behavior, and promotion status.

## Request lifecycle

```text
operator request
  -> parse
  -> classify
  -> policy check
  -> effect gate
  -> preview/report
  -> explicit confirmation if required
  -> carry out only if allowed
  -> record evidence
  -> report result
```

## Effect-first design

Every Nucleus request must carry an effect label.

If the effect cannot be classified, the request is denied.

## Failure-first design

Every mutating or external action must define:

- failure result;
- rollback or recovery boundary;
- operator-visible reason;
- evidence record;
- post-action validation.

## Initial Nucleus milestone

The first Nucleus milestone is not a full supervisor.

It is:

```text
state lattice fixture
policy classification
no-effect report
invariant tests
```

## Non-claims

This document does not claim Nucleus is implemented.

It defines the intended supervisor architecture before implementation begins.
