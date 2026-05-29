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

### Local-prefix reset and uninstall modes

The reset and uninstall actions use the same authority posture as local-prefix install. In dry-run mode they preview removal and write a receipt. With guarded local-prefix writes enabled, they remove managed command wrappers, managed desktop entries, known Panel icons, and the selected guarded prefix.

Reset and uninstall intentionally share removal mechanics. Reset means "remove the managed local install so I can reinstall from new specifications." Uninstall means "remove the managed local install and stop using it."

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

Reset and uninstall use a shorter state sequence:

```text
Idle
  -> Resolving guarded prefix
  -> Removing managed wrappers
  -> Removing desktop metadata
  -> Removing managed prefix
  -> Writing reset receipt
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
- `Install guarded local prefix` when real local-prefix install is explicitly enabled
- `Installing...` while the engine is running

The reset action is separate:

- `Preview local reset` when dry-run is active
- `Reset installed local prefix` when guarded local-prefix writes are explicitly enabled

The uninstall action is also separate:

- `Preview uninstall` when dry-run is active
- `Uninstall managed local install` when guarded local-prefix writes are explicitly enabled

The progress bar follows emitted `PHASE n/total` messages from the install script.
