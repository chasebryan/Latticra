/* SPDX-License-Identifier: AGPL-3.0-or-later */

.section .multiboot
.align 8
header_start:
  .long 0xe85250d6
  .long 0
  .long header_end - header_start
  .long -(0xe85250d6 + 0 + (header_end - header_start))
  .short 0
  .short 0
  .long 8
header_end:

.section .bss
.align 16
stack_bottom:
  .skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
  movl $stack_top, %esp
  pushl %ebx
  pushl %eax
  call kernel_main
1:
  cli
  hlt
  jmp 1b
.size _start, . - _start
