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

.global _start
.type _start, %function

/*
 * Primary start function where the bootloader jumps to after setting up clocks and etc.
 * Sets up stack and clears BSS then sets up the vector table and jumps to the C init.
 *
 * Variables:
 *  r2 - DTB pointer
*/
_start:
	/* Cache the DTB ptr so we can get it later */
	mov r4, r2

	/* Setup stack and relocate the exception vector table */
	ldr sp, =STACK_TOP

	/* Copy to low vectors */
	ldr r0, =arm32_vectors
	mov r1, #0
	ldmia r0!, {r5-r12}
	stmia r1!, {r5-r12}
	ldmia r0!, {r5-r12}
	stmia r1!, {r5-r12}

	mov r0, #0
	mcr p15, 0, r0, c7, c10, 4
	mcr p15, 0, r0, c7, c5, 0

	/* Clear BSS */
	ldr r0, =__bss_start
	ldr r1, =__bss_end
	mov r2, #0
1:	cmp r0, r1
	bhs 2f
	str r2, [r0], #4
	b 1b
2:
	/* Retrieve cached DTB and hop to C init */
	mov r0, r4
	bl arm_init
	
3:	b 3b

.size _start, . - _start
