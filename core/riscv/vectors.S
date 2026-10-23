/*
 * Copyright (c) 2026 Driftless Software Pvt. Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
*/
# rvunix Kernel
# Path: core/riscv/vectors.S
# Copyright (c) 2026 Driftless Software. All rights reserved.
# Property of Driftless Software.
#
# NOTICE: This software is governed by a license agreement. 
# Redistribution, modification, or use of this file, in whole or in part,
# is strictly restricted to the terms specified in the 'LICENSE' file 
# located at the root directory of this project repository.
#
# Description:
# S-mode trap handler, trap initialization
#
# Author: Daniil Dunaeff (dan7)

.section .text
.global trap_vector
.extern rv64_exception

# Trap vector (kernel mode)
trap_vector: # no arguments; modified: t0, t1, sepc
_trap_vector_stackframe_create:
    addi sp, sp, -280 # preserve space for stackframe
    sd x0,  0(sp) # store x0-x31 registers in stackframe
    sd x1,  8(sp)
    sd x2,  16(sp)
    sd x3,  24(sp)
    sd x4,  32(sp)
    sd x5,  40(sp)
    sd x6,  48(sp)
    sd x7,  56(sp)
    sd x8,  64(sp)
    sd x9,  72(sp)
    sd x10, 80(sp)
    sd x11, 88(sp)
    sd x12, 96(sp)
    sd x13, 104(sp)
    sd x14, 112(sp)
    sd x15, 120(sp)
    sd x16, 128(sp)
    sd x17, 136(sp)
    sd x18, 144(sp)
    sd x19, 152(sp)
    sd x20, 160(sp)
    sd x21, 168(sp)
    sd x22, 176(sp)
    sd x23, 184(sp)
    sd x24, 192(sp)
    sd x25, 200(sp)
    sd x26, 208(sp)
    sd x27, 216(sp)
    sd x28, 224(sp)
    sd x29, 232(sp)
    sd x30, 240(sp)
    sd x31, 248(sp)

    csrr t0, scause
    sd t0,  256(sp) # store suprevisor exception program counter
    csrr t0, sstatus
    sd t0,  264(sp) # store supervisor status
    csrr t0, sepc
    sd t0,  272(sp) # store supervisor cause

    addi t0, sp, 280 # calculate original stack pointer
    sd t0, 16(sp) # store calculated original stack pointer

    mv a0, sp # pass stackframe address as argument
    call rv64_exception # call primary trap handler

_trap_vector_stackframe_restore:
    # do not restore supervisor atp when returning to supervisor
    ld t0,  272(sp)
    csrw sepc, t0 # restore supervisor exception program counter
    ld t0,  264(sp)
    csrw sstatus, t0 # restore supervisor status
    ld t0,  256(sp)
    csrw scause, t0 # restore supervisor cause

    ld x31, 248(sp) # restore x1-x31 registers from stackframe
    ld x30, 240(sp)
    ld x29, 232(sp)
    ld x28, 224(sp)
    ld x27, 216(sp)
    ld x26, 208(sp)
    ld x25, 200(sp)
    ld x24, 192(sp)
    ld x23, 184(sp)
    ld x22, 176(sp)
    ld x21, 168(sp)
    ld x20, 160(sp)
    ld x19, 152(sp)
    ld x18, 144(sp)
    ld x17, 136(sp)
    ld x16, 128(sp)
    ld x15, 120(sp)
    ld x14, 112(sp)
    ld x13, 104(sp)
    ld x12, 96(sp)
    ld x11, 88(sp)
    ld x10, 80(sp)
    ld x9,  72(sp)
    ld x8,  64(sp)
    ld x7,  56(sp)
    ld x6,  48(sp)
    ld x5,  40(sp)
    ld x4,  32(sp)
    ld x3,  24(sp)
    # restore stack pointer last
    ld x1,  8(sp)
    # do not restore x0 because it's always zero

    ld x2,  16(sp) # now we can restore stack pointer

    sret # return from trap vector