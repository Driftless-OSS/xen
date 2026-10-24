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

#ifndef ARCH_RV64_REGS
#define ARCH_RV64_REGS

__attribute__((packed))
struct rv64_trapframe
{
    unsigned long long zero;    // zero
    unsigned long long ra;      // ra
    unsigned long long sp;      // sp
    unsigned long long gp;      // gp
    unsigned long long tp;      // tp
    unsigned long long t0;      // t0
    unsigned long long t1;      // t1
    unsigned long long t2;      // t2
    unsigned long long s0;      // s0
    unsigned long long s1;      // s1
    unsigned long long a0;      // a0
    unsigned long long a1;      // a1
    unsigned long long a2;      // a2
    unsigned long long a3;      // a3
    unsigned long long a4;      // a4
    unsigned long long a5;      // a5
    unsigned long long a6;      // a6
    unsigned long long a7;      // a7
    unsigned long long s2;      // s2
    unsigned long long s3;      // s3
    unsigned long long s4;      // s4
    unsigned long long s5;      // s5
    unsigned long long s6;      // s6
    unsigned long long s7;      // s7
    unsigned long long s8;      // s8
    unsigned long long s9;      // s9
    unsigned long long s10;     // s10
    unsigned long long s11;     // s11
    unsigned long long t3;      // t3
    unsigned long long t4;      // t4
    unsigned long long t5;      // t5
    unsigned long long t6;      // t6
    unsigned long long scause;  // scause
    unsigned long long sstatus; // sstatus
    unsigned long long sepc;    // sepc
};

#endif