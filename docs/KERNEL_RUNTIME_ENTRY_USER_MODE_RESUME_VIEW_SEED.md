# Kernel Runtime Entry User Mode Resume View Seed

Status: controlled runtime-entry user-mode-resume-view metadata seed
Scope: report-only bridge from runtime-entry syscall-exit-view metadata to declared user-mode-resume metadata.

This slice connects runtime-entry syscall-exit-view metadata to deterministic user-mode-resume-view metadata.

It remains no-effect and denied-by-default.

## Files

```text
include/latticra/kernel_runtime_entry_user_mode_resume_view.h
src/kernel_runtime_entry_user_mode_resume_view.c
tests/kernel_runtime_entry_user_mode_resume_view.c
tools/kernel_runtime_entry_user_mode_resume_view_report.c
scripts/test-kernel-runtime-entry-user-mode-resume-view.sh
scripts/test-kernel-runtime-entry-user-mode-resume-view-report-runner.sh
.github/workflows/kernel-runtime-entry-user-mode-resume-view.yml
docs/KERNEL_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_SEED.md
```

## Report Fields

The report exposes the chained runtime-entry path:

```text
user_mode_resume_view_status=runtime-entry-user-mode-resume-view-seed-ready
runtime_entry_syscall_exit_view_status=runtime-entry-syscall-exit-view-seed-ready
runtime_entry_syscall_return_view_status=runtime-entry-syscall-return-view-seed-ready
runtime_entry_syscall_dispatch_view_status=runtime-entry-syscall-dispatch-view-seed-ready
runtime_entry_syscall_gate_view_status=runtime-entry-syscall-gate-view-seed-ready
runtime_entry_privilege_level_view_status=runtime-entry-privilege-level-view-seed-ready
```

It also keeps resume authority explicitly denied:

```text
runtime_entry_user_mode_resume_view_allowed=0
runtime_entry_syscall_exit_view_allowed=0
runtime_entry_syscall_return_view_allowed=0
runtime_entry_syscall_dispatch_view_allowed=0
runtime_entry_syscall_gate_view_allowed=0
runtime_entry_allowed=0
syscall_exit_allowed=0
syscall_exit_commit_allowed=0
user_mode_resume_allowed=0
user_instruction_resume_allowed=0
resume_frame_commit_allowed=0
interrupt_return_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
no_effect=1
```

## Metadata Shape

The first declared user-mode-resume-view record is the kernel report process metadata:

```text
user_mode_resume_view[0].process_label=kernel-report-process-metadata
user_mode_resume_view[0].user_mode_resume_view_class=kernel-report-runtime-entry-user-mode-resume-view
user_mode_resume_view[0].syscall_number=512
user_mode_resume_view[0].handler_slot=0
user_mode_resume_view[0].dispatch_slot=1024
user_mode_resume_view[0].return_slot=2048
user_mode_resume_view[0].exit_slot=3072
user_mode_resume_view[0].resume_slot=4096
user_mode_resume_view[0].instruction_pointer_slot=13
user_mode_resume_view[0].stack_pointer_slot=14
user_mode_resume_view[0].argument_count=6
```

Those fields are declaration metadata only. They do not resume user-mode
execution, advance an instruction pointer, commit a resume frame, return from
interrupt state, perform a context switch, or execute syscall handlers.

## Boundary

This slice adds a deterministic metadata point after runtime-entry syscall exit
declaration while preserving the denial of user-mode resume, user instruction
resume, resume frame commits, syscall exits, interrupt returns, privilege
transitions, runtime entry, hardware effects, and host effects.

## Validation

```sh
sh scripts/test-kernel-runtime-entry-user-mode-resume-view.sh
sh scripts/test-kernel-runtime-entry-user-mode-resume-view-report-runner.sh
```

Expected output:

```text
kernel_runtime_entry_user_mode_resume_view: ok
kernel_runtime_entry_user_mode_resume_view_report_runner: ok
```
