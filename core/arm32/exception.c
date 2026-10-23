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

#include <stdint.h>
#include <klib.h>

/*
 * ARM32 exception handling is implemented here.
*/

static const char *const names[] = {
	"Reset", "Undefined instruction", "SVC", "Prefetch abort",
	"Data abort", "Reserved", "IRQ", "FIQ"
};

__attribute__((noreturn))
void arm32_exception(unsigned int vec, unsigned int lr, unsigned int spsr) {
	/*
	 * The dprintfs are commented out because we don't have them yet..
	 * TODO implement debugging prints.
	*/

	(void)vec;
	(void)spsr;
	(void)lr;

	//dprintf("\n*** EXCEPTION: %s\n", names[vec]);
	kputs("\n*** EXCEPTION: ");
	kputs(names[vec]);
	kputs("\n");

	/* LR points past fault instruction so the offset depends on type */
	if (vec == 1) {
		//dprintf("PC   = %x (undefined instruction)\n", lr - 4);
		kputs("Undefined Instruction\n");
	} else if (vec == 3) {
		unsigned int ifsr, ifar;
		__asm__ volatile("mrc p15, 0, %0, c5, c0, 1" : "=r"(ifsr));
		__asm__ volatile("mrc p15, 0, %0, c6, c0, 2" : "=r"(ifar));
		//dprintf("PC   = %x\nIFSR = %x  IFAR = %x\n", lr - 4, ifsr, ifar);
	} else if (vec == 4) {
		unsigned int dfsr, dfar;
		__asm__ volatile("mrc p15, 0, %0, c5, c0, 0" : "=r"(dfsr));
		__asm__ volatile("mrc p15, 0, %0, c6, c0, 0" : "=r"(dfar));
		//dprintf("PC   = %x\nDFSR = %x  DFAR = %x\n", lr - 8, dfsr, dfar);
	} else {
		//dprintf("LR   = %x\n", lr);
	}
	//dprintf("SPSR = %x\n", spsr);
	kputs("hanging!\n");

	for (;;);
}
