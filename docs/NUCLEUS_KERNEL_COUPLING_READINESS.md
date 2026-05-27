# Nucleus Kernel Coupling Readiness

Status: controlled nucleus-first OS-readiness metadata gate
Scope: report-only coupling from the nucleus task plan to kernel subsystem and runtime-entry register-view evidence.

This slice makes the nucleus the first checkpoint for kernel coupling. It accepts
only an already-allowed no-effect nucleus task plan, a no-effect kernel subsystem
registry, and a no-effect runtime-entry register-view seed. When all three are
present and clean, it emits `os_readiness_status=os-metadata-ready`.

The API supports both reviewed-evidence intake and a default evaluator. The
default evaluator assembles the standard no-effect nucleus task plan, kernel
subsystem registry, and runtime-entry register-view seed before running the same
coupling gate.

This is not bootable OS readiness. It does not boot, enter runtime, dispatch
scheduler work, mutate a run queue, save registers, restore registers, switch
stacks, switch address spaces, write files, open the network, touch devices, or
grant host authority.

## Files

```text
include/latticra/nucleus_kernel_coupling.h
src/nucleus_kernel_coupling.c
tests/nucleus_kernel_coupling.c
tools/nucleus_kernel_coupling_report.c
scripts/test-nucleus-kernel-coupling.sh
scripts/test-nucleus-kernel-coupling-report-runner.sh
docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
```

## Entrypoints

```text
latticra_nucleus_kernel_coupling_default_nucleus_plan
latticra_nucleus_kernel_coupling_evaluate
latticra_nucleus_kernel_coupling_evaluate_default
latticra_nucleus_kernel_coupling_report
```

## Ready Evidence

The ready path requires:

```text
nucleus_plan_status=allow-no-effect-sequence
kernel_registry_status=registry-ready
kernel_status=initialized-report-only
runtime_register_view_status=runtime-entry-register-view-seed-ready
runtime_entry_frame_status=runtime-entry-frame-seed-ready
scheduler_run_entry_status=scheduler-run-entry-seed-ready
task_count=1
accepted_task_count=1
blocked_task_count=0
subsystem_count=9
register_view_count=4
prerequisites_satisfied=1
no_effect_chain_ok=1
```

The ready report also keeps all OS-effect flags denied:

```text
report_only=1
execution_allowed=0
mutation_allowed=0
network_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
boot_allowed=0
runtime_entry_allowed=0
scheduler_run_entry_allowed=0
context_switch_allowed=0
register_save_allowed=0
register_restore_allowed=0
host_effect_allowed=0
```

## Blocked Evidence

The gate blocks when any prerequisite is missing or when any prerequisite stops
being no-effect:

```text
reason=nucleus-plan-missing
reason=nucleus-plan-blocked
reason=kernel-registry-missing
reason=kernel-registry-blocked
reason=runtime-register-view-missing
reason=runtime-register-view-blocked
```

The blocked path remains report-only and does not grant the denied authority.

## Validation

```text
sh scripts/test-nucleus-kernel-coupling.sh
sh scripts/test-nucleus-kernel-coupling-report-runner.sh
```
