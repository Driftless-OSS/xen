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
.global enter_usermode
.align 4

.extern page_table_installed
.extern kernel_page_table
.extern interrupt_exception_handler

trap_vector:
    csrrw sp, sscratch, sp
    bnez sp, from_usermode

    csrrw sp, sscratch, sp

    addi sp, sp, -280

    sd x5,  40(sp)
    sd x6,  48(sp)
    sd x7,  56(sp)

    addi t0, sp, 280
    sd t0,  16(sp)
    
    li t0, 0
    j stackframe_create

from_usermode:
    csrr t1, satp
    mv t0, t1
    beqz t1, enter_interrupt
    la t1, kernel_page_table
    srli t1, t1, 12
    li t2, 8
    slli t2, t2, 60
    or t1, t1, t2
    csrw satp, t1
    sfence.vma zero, zero

enter_interrupt:
    addi sp, sp, -280
    sd x5,  40(sp)
    sd x6,  48(sp)
    sd x7,  56(sp)
    csrrw x5, sscratch, zero
    sd x5,  16(sp)
    ld x5,  40(sp)
    sd t0,  272(sp)
    li t0, 1

stackframe_create:
    sd x0,  0(sp)         # zero (always 0, but filled for structure matching)
    sd x1,  8(sp)         # ra
    sd x3,  24(sp)        # gp
    sd x4,  32(sp)        # tp
    sd x8,  64(sp)        # s0/fp
    sd x9,  72(sp)        # s1
    sd x10, 80(sp)        # a0
    sd x11, 88(sp)        # a1
    sd x12, 96(sp)        # a2
    sd x13, 104(sp)       # a3
    sd x14, 112(sp)       # a4
    sd x15, 120(sp)       # a5
    sd x16, 128(sp)       # a6
    sd x17, 136(sp)       # a7
    sd x18, 144(sp)       # s2
    sd x19, 152(sp)       # s3
    sd x20, 160(sp)       # s4
    sd x21, 168(sp)       # s5
    sd x22, 176(sp)       # s6
    sd x23, 184(sp)       # s7
    sd x24, 192(sp)       # s8
    sd x25, 200(sp)       # s9
    sd x26, 208(sp)       # s10
    sd x27, 216(sp)       # s11
    sd x28, 224(sp)       # t3
    sd x29, 232(sp)       # t4
    sd x30, 240(sp)       # t5
    sd x31, 248(sp)       # t6

    csrr t1, sstatus
    sd t1, 256(sp)
    csrr t2, sepc
    sd t2, 264(sp)

    mv a0, t0
    mv a1, sp
    call rv64_exception

    ld t1, 256(sp)
    csrw sstatus, t1
    ld t2, 264(sp)
    csrw sepc, t2

    li t1, 0x100
    and t0, t1, t1
    bnez t0, to_kernel_mode

to_user_mode:
    addi t0, sp, 280
    csrw sscratch, t0
    
    ld t0,  272(sp)
    csrw satp, t0
    ld x31, 248(sp)       # t6
    ld x30, 240(sp)       # t5
    ld x29, 232(sp)       # t4
    ld x28, 224(sp)       # t3
    ld x27, 216(sp)       # s11
    ld x26, 208(sp)       # s10
    ld x25, 200(sp)       # s9
    ld x24, 192(sp)       # s8
    ld x23, 184(sp)       # s7
    ld x22, 176(sp)       # s6
    ld x21, 168(sp)       # s5
    ld x20, 160(sp)       # s4
    ld x19, 152(sp)       # s3
    ld x18, 144(sp)       # s2
    ld x17, 136(sp)       # a7
    ld x16, 128(sp)       # a6
    ld x15, 120(sp)       # a5
    ld x14, 112(sp)       # a4
    ld x13, 104(sp)       # a3
    ld x12, 96(sp)        # a2
    ld x11, 88(sp)        # a1
    ld x10, 80(sp)        # a0
    ld x9,  72(sp)        # s1
    ld x8,  64(sp)        # s0/fp
    ld x7,  56(sp)        # t2
    ld x6,  48(sp)        # t1
    ld x5,  40(sp)        # t0
    ld x4,  32(sp)        # tp
    ld x3,  24(sp)        # gp
    ld x1,  8(sp)         # ra
    
    ld sp, 16(sp)
    sret

to_kernel_mode:
    ld x31, 248(sp)       # t6
    ld x30, 240(sp)       # t5
    ld x29, 232(sp)       # t4
    ld x28, 224(sp)       # t3
    ld x27, 216(sp)       # s11
    ld x26, 208(sp)       # s10
    ld x25, 200(sp)       # s9
    ld x24, 192(sp)       # s8
    ld x23, 184(sp)       # s7
    ld x22, 176(sp)       # s6
    ld x21, 168(sp)       # s5
    ld x20, 160(sp)       # s4
    ld x19, 152(sp)       # s3
    ld x18, 144(sp)       # s2
    ld x17, 136(sp)       # a7
    ld x16, 128(sp)       # a6
    ld x15, 120(sp)       # a5
    ld x14, 112(sp)       # a4
    ld x13, 104(sp)       # a3
    ld x12, 96(sp)        # a2
    ld x11, 88(sp)        # a1
    ld x10, 80(sp)        # a0
    ld x9,  72(sp)        # s1
    ld x8,  64(sp)        # s0/fp
    ld x7,  56(sp)        # t2
    ld x6,  48(sp)        # t1
    ld x5,  40(sp)        # t0
    ld x4,  32(sp)        # tp
    ld x3,  24(sp)        # gp
    ld x1,  8(sp)         # ra

    addi sp, sp, 280
    sret