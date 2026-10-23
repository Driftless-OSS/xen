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

/*
 * Primary start function where the bootloader jumps to after setting up clocks and etc.
 * Sets up stack and clears BSS then sets up the vector table and jumps to the C init.
 *
 * Variables:
 *  x0 - DTB pointer
*/
_start:
	/* Cache DTB pointer */
	mov x19, x0

	/* Set stack */
	ldr x30, =stack_top
	mov sp, x30

	/* Set up vectors and VBAR */
	ldr x0, =arm64_vectors
	msr vbar_el1, x0
	isb

	/* Clear BSS */
	ldr x0, =__bss_start
	ldr x1, =__bss_end
1:	cmp x0, x1
	b.hs 2f
	str xzr, [x0], #8
	b 1b
2:
	/* Retrieve DTB */
	mov x0, x19
	bl arm_init
	b .
