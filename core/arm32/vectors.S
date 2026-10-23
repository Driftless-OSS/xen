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

.section .text
.global arm32_vectors

/*
 * 32 byte aligned stub definitions, this should be used to
 * populate the vector table at 0x00.
*/
.balign 32
arm32_vectors:
	ldr pc, _vector_reset
	ldr pc, _vector_undef
	ldr pc, _vector_svc
	ldr pc, _vector_pabt
	ldr pc, _vector_dabt
	ldr pc, _vector_reserved
	ldr pc, _vector_irq
	ldr pc, _vector_fiq

_vector_reset: .word stub_reset
_vector_undef: .word stub_undef
_vector_svc: .word stub_svc
_vector_pabt: .word stub_pabt
_vector_dabt: .word stub_dabt
_vector_reserved: .word stub_reserved
_vector_irq: .word stub_irq
_vector_fiq: .word stub_fiq

.macro stub name, idx
\name:
	/* Stack might be garbage here, so load our own to be fully safe */
	ldr sp, =exc_stack_top
	mov r0, #\idx
	mov r1, lr
	mrs r2, spsr
	bl arm32_exception
	b .
.endm

	stub stub_reset, 0
	stub stub_undef, 1
	stub stub_svc, 2
	stub stub_pabt, 3
	stub stub_dabt, 4
	stub stub_reserved, 5
	stub stub_irq, 6
	stub stub_fiq, 7
	.ltorg

.section .bss
.balign 8
exc_stack:
	.space 4096
exc_stack_top:
