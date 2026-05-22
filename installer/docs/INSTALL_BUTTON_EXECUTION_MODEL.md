# Install Button Execution Model

The graphical **Install** button is intentionally real, but guarded.

## Modes

### Dry-install mode

Default.

```text
safety.dry_run = true
```

The button executes the installer engine, emits progress phases, validates configuration, checks the component manifest, generates an install plan, and writes an operator receipt. It does not write into the install prefix.

### Local-prefix install mode

Explicit.

```text
safety.dry_run = false
safety.allow_host_mutation = true
```

The button creates a user-local install layout and writes selected component placeholders, markers, configuration files, and CLI shims. This is still not a production installer. It is a guarded early install path for development validation.

## State machine

```text
Idle
  -> Preparing files
  -> Validating configuration
  -> Loading component manifest
  -> Resolving prefix
  -> Building prefix layout
  -> Materializing selected components
  -> Writing receipt
  -> Complete
```

Failure can occur at any step. A failure should leave the operator with a visible log and, when possible, a receipt.

## Guardrails

The current installer must not:

- request root authority
- mutate system directories
- use the network
- claim production readiness
- silently overwrite existing files when preserve mode is enabled
- enable runtime enforcement from the installer path

## UI behavior

The button label changes based on mode:

- `Run Dry-Install` when dry-run is active
- `Install Latticra` when real local-prefix install is explicitly enabled
- `Installing...` while the engine is running

The progress bar follows emitted `PHASE n/total` messages from the install script.
