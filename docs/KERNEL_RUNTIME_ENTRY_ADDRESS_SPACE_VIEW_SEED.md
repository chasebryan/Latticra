# Kernel Runtime Entry Address Space View Seed

Status: controlled runtime-entry address-space-view metadata seed
Scope: report-only bridge from runtime-entry stack-view metadata to declared address-space-view metadata.

This slice connects runtime-entry stack-view metadata to deterministic address-space-view metadata.
It does not capture address spaces, switch address spaces, walk page tables, write page tables,
flush TLBs, update MMU state, capture stacks, switch stacks, save registers, restore registers,
switch CPU context, enter runtime execution, mutate a run queue, read time, update accounting,
dispatch scheduler work, or touch hardware.

## Files

```text
include/latticra/kernel_runtime_entry_address_space_view.h
src/kernel_runtime_entry_address_space_view.c
tests/kernel_runtime_entry_address_space_view.c
tools/kernel_runtime_entry_address_space_view_report.c
scripts/test-kernel-runtime-entry-address-space-view.sh
scripts/test-kernel-runtime-entry-address-space-view-report-runner.sh
.github/workflows/kernel-runtime-entry-address-space-view.yml
```

## Evidence

The seed report emits a deterministic, no-effect boundary:

```text
address_space_view_status=runtime-entry-address-space-view-seed-ready
policy_status=report-only
runtime_entry_stack_view_status=runtime-entry-stack-view-seed-ready
runtime_entry_register_view_status=runtime-entry-register-view-seed-ready
runtime_entry_frame_status=runtime-entry-frame-seed-ready
runtime_entry_admission_status=runtime-entry-admission-seed-ready
scheduler_run_entry_status=scheduler-run-entry-seed-ready
address_space_view_count=4
runtime_entry_address_space_view_allowed=0
runtime_entry_stack_view_allowed=0
runtime_entry_register_view_allowed=0
runtime_entry_frame_allowed=0
runtime_entry_admission_allowed=0
runtime_entry_allowed=0
context_switch_allowed=0
stack_switch_allowed=0
address_space_switch_allowed=0
page_table_write_allowed=0
tlb_flush_allowed=0
mmu_update_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

The first declared address-space-view record is the kernel report process metadata:

```text
address_space_view[0].process_label=kernel-report-process-metadata
address_space_view[0].address_space_view_class=kernel-report-runtime-entry-address-space-view
address_space_view[0].address_space_view_token=0
address_space_view[0].stack_view_token=0
address_space_view[0].register_view_token=0
address_space_view[0].frame_token=0
address_space_view[0].address_space_view_rank=1
address_space_view[0].address_space_slot_count=4
address_space_view[0].address_space_window_bytes=1048576
address_space_view[0].address_space_root_declared=1
address_space_view[0].user_range_declared=1
address_space_view[0].kernel_range_declared=1
address_space_view[0].guard_region_declared=1
address_space_view[0].address_space_view_planned=0
address_space_view[0].address_space_capture_planned=0
address_space_view[0].address_space_switch_planned=0
address_space_view[0].page_table_walk_planned=0
address_space_view[0].page_table_write_allowed=0
address_space_view[0].tlb_flush_allowed=0
address_space_view[0].mmu_update_allowed=0
address_space_view[0].no_effect=1
```

The seed keeps the runtime boundary explicit: the lifecycle can name the next
metadata point after runtime-entry stack-view declaration while preserving
the denial of address-space capture, address-space switching, page-table writes,
TLB flushes, MMU updates, stack switching, register save/restore, context switching,
runtime entry, scheduler execution, and hardware effects.

## Validation

```text
sh scripts/test-kernel-runtime-entry-address-space-view.sh
sh scripts/test-kernel-runtime-entry-address-space-view-report-runner.sh
```
