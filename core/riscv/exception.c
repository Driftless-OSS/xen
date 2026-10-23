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

#include <regs.h>
#include <stdint.h>
#include <klib.h>

/*
 * RISC-V exception handling is implemented here.
*/

void rv64_exception(struct rv64_trapframe *trapframe) {
	/*
	 * The dprintfs are commented out because we don't have them yet..
	 * TODO implement debugging prints.
	*/

    (void)trapframe;

	//dprintf("\n*** EXCEPTION: %s\n", names[vec]);
	kputs("\n*** EXCEPTION: ");
	kputs("\n");

	kputs("hanging!\n");

	for (;;);
}
