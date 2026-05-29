# Kernel Runtime Entry Syscall Return View Seed

Status: controlled runtime-entry syscall-return-view metadata seed
Scope: report-only bridge from runtime-entry syscall-dispatch-view metadata to declared syscall-return metadata.

This slice connects runtime-entry syscall-dispatch-view metadata to deterministic syscall-return-view metadata.

It remains no-effect and denied-by-default.

## Files

```text
include/latticra/kernel_runtime_entry_syscall_return_view.h
src/kernel_runtime_entry_syscall_return_view.c
tests/kernel_runtime_entry_syscall_return_view.c
tools/kernel_runtime_entry_syscall_return_view_report.c
scripts/test-kernel-runtime-entry-syscall-return-view.sh
scripts/test-kernel-runtime-entry-syscall-return-view-report-runner.sh
.github/workflows/kernel-runtime-entry-syscall-return-view.yml
docs/KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_SEED.md
```

## Report Fields

The report exposes the chained runtime-entry path:

```text
syscall_return_view_status=runtime-entry-syscall-return-view-seed-ready
runtime_entry_syscall_dispatch_view_status=runtime-entry-syscall-dispatch-view-seed-ready
runtime_entry_syscall_gate_view_status=runtime-entry-syscall-gate-view-seed-ready
runtime_entry_privilege_level_view_status=runtime-entry-privilege-level-view-seed-ready
```

It also keeps return authority explicitly denied:

```text
runtime_entry_syscall_return_view_allowed=0
runtime_entry_syscall_dispatch_view_allowed=0
runtime_entry_syscall_gate_view_allowed=0
runtime_entry_allowed=0
syscall_dispatch_allowed=0
syscall_handler_allowed=0
syscall_return_allowed=0
syscall_result_copy_allowed=0
interrupt_return_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
no_effect=1
```

## Metadata Shape

The first declared syscall-return-view record is the kernel report process metadata:

```text
syscall_return_view[0].process_label=kernel-report-process-metadata
syscall_return_view[0].syscall_return_view_class=kernel-report-runtime-entry-syscall-return-view
syscall_return_view[0].syscall_number=512
syscall_return_view[0].handler_slot=0
syscall_return_view[0].dispatch_slot=1024
syscall_return_view[0].return_slot=2048
syscall_return_view[0].result_register_slot=10
syscall_return_view[0].errno_slot=11
syscall_return_view[0].argument_count=6
```

Those fields are declaration metadata only. They do not copy syscall results,
return to user mode, enter an interrupt return path, perform a context switch,
or execute syscall handlers.

## Boundary

This slice adds a deterministic metadata point after runtime-entry syscall
dispatch declaration while preserving the denial of syscall returns, result
copying, handler entry, interrupt returns, privilege transitions, runtime entry,
hardware effects, and host effects.

## Validation

```sh
sh scripts/test-kernel-runtime-entry-syscall-return-view.sh
sh scripts/test-kernel-runtime-entry-syscall-return-view-report-runner.sh
```

Expected output:

```text
kernel_runtime_entry_syscall_return_view: ok
kernel_runtime_entry_syscall_return_view_report_runner: ok
```
