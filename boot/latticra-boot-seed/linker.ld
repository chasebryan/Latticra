/* SPDX-License-Identifier: AGPL-3.0-or-later */

ENTRY(_start)

SECTIONS
{
  . = 1M;

  .multiboot : { KEEP(*(.multiboot)) }
  .text : { *(.text*) }
  .rodata : { *(.rodata*) }
  .data : { *(.data*) }
  .bss : { *(COMMON) *(.bss*) }
}
