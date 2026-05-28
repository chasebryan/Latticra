# Kernel Runtime Entry Idle Return Observation View Seed

Status: controlled runtime-entry idle-return-observation-view metadata seed
Scope: report-only bridge from runtime-entry process-return-observation-view metadata to declared idle-return observation metadata.

This slice connects runtime-entry process-return-observation-view metadata to deterministic idle-return-observation-view metadata.

It remains no-effect and denied-by-default.

## Files

```text
include/latticra/kernel_runtime_entry_idle_return_observation_view.h
src/kernel_runtime_entry_idle_return_observation_view.c
tests/kernel_runtime_entry_idle_return_observation_view.c
tools/kernel_runtime_entry_idle_return_observation_view_report.c
scripts/test-kernel-runtime-entry-idle-return-observation-view.sh
scripts/test-kernel-runtime-entry-idle-return-observation-view-report-runner.sh
.github/workflows/kernel-runtime-entry-idle-return-observation-view.yml
docs/KERNEL_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_SEED.md
```

## Report Fields

The report exposes the chained runtime-entry path:

```text
idle_return_observation_view_status=runtime-entry-idle-return-observation-view-seed-ready
runtime_entry_process_return_observation_view_status=runtime-entry-process-return-observation-view-seed-ready
runtime_entry_scheduler_return_observation_view_status=runtime-entry-scheduler-return-observation-view-seed-ready
runtime_entry_post_resume_observation_view_status=runtime-entry-post-resume-observation-view-seed-ready
runtime_entry_user_mode_resume_view_status=runtime-entry-user-mode-resume-view-seed-ready
runtime_entry_syscall_exit_view_status=runtime-entry-syscall-exit-view-seed-ready
runtime_entry_syscall_return_view_status=runtime-entry-syscall-return-view-seed-ready
```

It also keeps idle-return observation authority explicitly denied:

```text
runtime_entry_idle_return_observation_view_allowed=0
runtime_entry_process_return_observation_view_allowed=0
runtime_entry_scheduler_return_observation_view_allowed=0
runtime_entry_post_resume_observation_view_allowed=0
runtime_entry_allowed=0
scheduler_return_observation_allowed=0
process_return_observation_allowed=0
process_return_allowed=0
idle_return_observation_allowed=0
idle_return_allowed=0
idle_state_read_allowed=0
process_state_read_allowed=0
scheduler_execution_allowed=0
scheduler_dispatch_allowed=0
context_switch_allowed=0
run_queue_mutation_allowed=0
process_wake_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
no_effect=1
```

## Metadata Shape

The first declared idle-return-observation-view record is the kernel report process metadata:

```text
idle_return_observation_view[0].process_label=kernel-report-process-metadata
idle_return_observation_view[0].idle_return_observation_view_class=kernel-report-runtime-entry-idle-return-observation-view
idle_return_observation_view[0].idle_return_observation_view_token=0
idle_return_observation_view[0].process_return_observation_view_token=0
idle_return_observation_view[0].scheduler_return_observation_view_token=0
idle_return_observation_view[0].scheduler_return_slot=6144
idle_return_observation_view[0].process_return_slot=7168
idle_return_observation_view[0].idle_return_slot=8192
idle_return_observation_view[0].idle_return_epoch_slot=22
idle_return_observation_view[0].idle_return_reason_slot=23
idle_return_observation_view[0].idle_state_slot=24
```

Those fields are declaration metadata only. They do not return to an idle
loop or process, read live idle or process state, wake a process, dispatch
work, perform a context switch, mutate a run queue, run scheduler execution,
or touch hardware or host state.

## Boundary

This slice adds a deterministic metadata point after runtime-entry
process-return observation while preserving the denial of idle-return
observation, idle returns, idle state reads, process-return observation,
process returns, process state reads, process wakes, scheduler execution,
scheduler dispatch, context switching, run queue mutation, runtime entry,
hardware effects, and host effects.

## Validation

```sh
sh scripts/test-kernel-runtime-entry-idle-return-observation-view.sh
sh scripts/test-kernel-runtime-entry-idle-return-observation-view-report-runner.sh
```

Expected output:

```text
kernel_runtime_entry_idle_return_observation_view: ok
kernel_runtime_entry_idle_return_observation_view_report_runner: ok
```
