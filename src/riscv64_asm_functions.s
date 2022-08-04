//  z_Linux_asm.s:  - microtasking routines specifically
//                    written for Intel platforms running Linux* OS
//
// File origin: https://github.com/llvm-mirror/openmp/blob/master/runtime/src/z_Linux_asm.S
//
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
/*
.macro ALIGN size
    .align 1<<(\size)
.endm

        .data
        .comm .gomp_critical_user_,32,8
        .data
	ALIGN 8
        .global __kmp_unnamed_critical_addr
__kmp_unnamed_critical_addr:
        .8byte .gomp_critical_user_
        .type __kmp_unnamed_critical_addr,@object
        .size __kmp_unnamed_critical_addr,8

    .ident "Intel Corporation"
    .data
    ALIGN 4
*/
//------------------------------------------------------------------------
//
// typedef void (*microtask_t)(int *gtid, int *tid, ...);
//
// int __kmp_invoke_microtask(microtask_t pkfn, int gtid, int tid, int argc,
//                            void *p_argv[]
// #if OMPT_SUPPORT
//                            ,
//                            void **exit_frame_ptr
// #endif
//                            ) {
// #if OMPT_SUPPORT
//   *exit_frame_ptr = OMPT_GET_FRAME_ADDRESS(0);
// #endif
//
//   (*pkfn)(&gtid, &tid, argv[0], ...);
//
//   return 1;
// }
//
// Parameters:
//   a0: pkfn
//   a1: gtid
//   a2: tid
//   a3: argc
//   a4: p_argv
//   a5: exit_frame_ptr
//
// Locals:
//   __gtid: gtid param pushed on stack so can pass &gtid to pkfn
//   __tid: tid param pushed on stack so can pass &tid to pkfn
//
// Temp. registers:
//
//  t0: used to calculate the dynamic stack size / used to hold pkfn address
//  t1: used as temporary for stack placement calculation
//  t2: used as temporary for stack arguments
//  t3: used as temporary for number of remaining pkfn parms
//  t4: used to traverse p_argv array
//
// return: a0 (always 1/TRUE)
//

__gtid = -20
__tid = -24

// -- Begin __kmp_invoke_microtask
// mark_begin;
	.text
	.globl	__kmp_invoke_microtask
	.p2align	1
	.type	__kmp_invoke_microtask,@function
__kmp_invoke_microtask:
	.cfi_startproc

	// First, save ra and fp
	addi	sp, sp, -16
	sd	ra, 8(sp)
	sd	fp, 0(sp)
	addi	fp, sp, 16
	.cfi_def_cfa	fp, 0
	.cfi_offset	ra, -8
	.cfi_offset	fp, -16

	// Compute the dynamic stack size:
	//
	// - We need 8 bytes for storing 'gtid' and 'tid', so we can pass them by
	//   reference
	// - We need 8 bytes for each argument that cannot be passed to the 'pkfn'
	//   function by register. Given that we have 8 of such registers (a[0-7])
	//   and two + 'argc' arguments (consider &gtid and &tid), we need to
	//   reserve max(0, argc - 6)*8 extra bytes
	//
	// The total number of bytes is then max(0, argc - 6)*8 + 8

	// Compute max(0, argc - 6) using the following bithack:
	// max(0, x) = x - (x & (x >> 31)), where x := argc - 6
	// Source: http://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax
	addi	t0, a3, -6
	srai	t1, t0, 31
	and	t1, t0, t1
	sub	t0, t0, t1

	addi	t0, t0, 1

	slli	t0, t0, 3
	sub	sp, sp, t0

	// Align the stack to 16 bytes
	andi	sp, sp, -16

	mv	t0, a0
	mv	t3, a3
	mv	t4, a4

#if OMPT_SUPPORT
	// Save frame pointer into exit_frame
	sd	fp, 0(a5)
#endif

	// Prepare arguments for the pkfn function (first 8 using a0-a7 registers)

	sw	a1, __gtid(fp)
	sw	a2, __tid(fp)

	addi	a0, fp, __gtid
	addi	a1, fp, __tid

	beqz	t3, .L_kmp_3
	ld	a2, 0(t4)

	addi	t3, t3, -1
	beqz	t3, .L_kmp_3
	ld	a3, 8(t4)

	addi	t3, t3, -1
	beqz	t3, .L_kmp_3
	ld	a4, 16(t4)

	addi	t3, t3, -1
	beqz	t3, .L_kmp_3
	ld	a5, 24(t4)

	addi	t3, t3, -1
	beqz	t3, .L_kmp_3
	ld	a6, 32(t4)

	addi	t3, t3, -1
	beqz	t3, .L_kmp_3
	ld	a7, 40(t4)

	// Prepare any additional argument passed through the stack
	addi	t4, t4, 48
	mv	t1, sp
	j .L_kmp_2
.L_kmp_1:
	ld	t2, 0(t4)
	sd	t2, 0(t1)
	addi	t4, t4, 8
	addi	t1, t1, 8
.L_kmp_2:
	addi	t3, t3, -1
	bnez	t3, .L_kmp_1

.L_kmp_3:
	// Call pkfn function
	jalr	t0

	// Restore stack and return

	addi	a0, zero, 1

	addi	sp, fp, -16
	ld	fp, 0(sp)
	ld	ra, 8(sp)
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	__kmp_invoke_microtask, .Lfunc_end0-__kmp_invoke_microtask
	.cfi_endproc

// -- End  __kmp_invoke_microtask

    .data
    .comm .gomp_critical_user_,32,8
    .data
    .align 8
    .global __kmp_unnamed_critical_addr
__kmp_unnamed_critical_addr:
    .8byte .gomp_critical_user_
    .size __kmp_unnamed_critical_addr,8

// -- End  __kmp_invoke_microtask
