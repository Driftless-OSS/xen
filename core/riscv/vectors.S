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

.global trap_vector
.align 4

.extern rv64_exception

trap_vector:
    csrw sscratch, a0
    la a0, trapframe

trapframe_create:
    sd x0,  0(a0)         # zero (always 0, but filled for structure matching)
    sd x1,  8(a0)         # ra
    sd x2,  16(a0)        # sp
    sd x3,  24(a0)        # gp
    sd x4,  32(a0)        # tp
    sd x5,  40(a0)        # t0
    sd x6,  48(a0)        # t1
    sd x7,  56(a0)        # t2
    sd x8,  64(a0)        # s0/fp
    sd x9,  72(a0)        # s1
    sd x11, 88(a0)        # a1
    sd x12, 96(a0)        # a2
    sd x13, 104(a0)       # a3
    sd x14, 112(a0)       # a4
    sd x15, 120(a0)       # a5
    sd x16, 128(a0)       # a6
    sd x17, 136(a0)       # a7
    sd x18, 144(a0)       # s2
    sd x19, 152(a0)       # s3
    sd x20, 160(a0)       # s4
    sd x21, 168(a0)       # s5
    sd x22, 176(a0)       # s6
    sd x23, 184(a0)       # s7
    sd x24, 192(a0)       # s8
    sd x25, 200(a0)       # s9
    sd x26, 208(a0)       # s10
    sd x27, 216(a0)       # s11
    sd x28, 224(a0)       # t3
    sd x29, 232(a0)       # t4
    sd x30, 240(a0)       # t5
    sd x31, 248(a0)       # t6

    csrr t0, scause
    sd t0, 256(a0)
    csrr t0, sstatus
    sd t0, 264(a0)
    csrr t0, sepc
    sd t0, 272(a0)

    mv t0, a0
    csrr a0, sscratch
    csrw sscratch, t0
    sd x10, 80(a0)        # a0
    mv a0, t0    

    call rv64_exception

    csrr a0, sscratch

    ld t0, 256(a0)
    csrw scause, t0
    ld t0, 264(a0)
    csrw sstatus, t0
    ld t0, 272(a0)
    csrw sepc, t0

    ld x31, 248(a0)       # t6
    ld x30, 240(a0)       # t5
    ld x29, 232(a0)       # t4
    ld x28, 224(a0)       # t3
    ld x27, 216(a0)       # s11
    ld x26, 208(a0)       # s10
    ld x25, 200(a0)       # s9
    ld x24, 192(a0)       # s8
    ld x23, 184(a0)       # s7
    ld x22, 176(a0)       # s6
    ld x21, 168(a0)       # s5
    ld x20, 160(a0)       # s4
    ld x19, 152(a0)       # s3
    ld x18, 144(a0)       # s2
    ld x17, 136(a0)       # a7
    ld x16, 128(a0)       # a6
    ld x15, 120(a0)       # a5
    ld x14, 112(a0)       # a4
    ld x13, 104(a0)       # a3
    ld x12, 96(a0)        # a2
    ld x11, 88(a0)        # a1
    ld x9,  72(a0)        # s1
    ld x8,  64(a0)        # s0/fp
    ld x7,  56(a0)        # t2
    ld x6,  48(a0)        # t1
    ld x5,  40(a0)        # t0
    ld x4,  32(a0)        # tp
    ld x3,  24(a0)        # gp
    ld x1,  8(a0)         # ra

    ld x10, 80(a0)        # a0

    sret

.section .bss

trapframe:
    .fill 280, 1, 0