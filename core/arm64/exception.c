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
 * ARM64 exception handling is implemented here.
*/

static const char *const grp[] = {
	"Current EL SP0", "Current EL SPx", "Lower EL A64", "Lower EL A32"
};
static const char *const typ[] = { "Sync", "IRQ", "FIQ", "SError" };

static const char *ec_name(unsigned int ec) {
	switch (ec) {
	case 0x00: return "Unknown / undefined instruction";
	case 0x01: return "WFI/WFE trapped";
	case 0x07: return "FP/SIMD access trapped";
	case 0x15: return "SVC (AArch64)";
	case 0x20: return "Instruction abort, lower EL";
	case 0x21: return "Instruction abort, same EL";
	case 0x22: return "PC alignment fault";
	case 0x24: return "Data abort, lower EL";
	case 0x25: return "Data abort, same EL";
	case 0x26: return "SP alignment fault";
	case 0x2f: return "SError";
	case 0x3c: return "BRK";
	default:   return "Other";
	}
}

__attribute__((noreturn))
void arm64_exception(unsigned int vec) {
	uint64_t esr, elr, far, spsr;

	__asm__ volatile("mrs %0, esr_el1"  : "=r"(esr));
	__asm__ volatile("mrs %0, elr_el1"  : "=r"(elr));
	__asm__ volatile("mrs %0, far_el1"  : "=r"(far));
	__asm__ volatile("mrs %0, spsr_el1" : "=r"(spsr));

	unsigned int ec = (esr >> 26) & 0x3f;

	kputs("\n***EXCEPTION: ");
	kputs(grp[vec >> 2]);
	kputs(" ");
	kputs(typ[vec & 3]);
	kputs("\n");
	kputs(ec_name(ec));
	kputs("\nhanging!\n");

	// dprintf("ESR  = %llx  EC = %x (%s)\n", (unsigned long long)esr, ec, ec_name(ec));
	// dprintf("ELR  = %llx\n", (unsigned long long)elr);
	// dprintf("FAR  = %llx  (valid for aborts/alignment only)\n", (unsigned long long)far);
	// dprintf("SPSR = %llx\n", (unsigned long long)spsr);

	for (;;) {
		__asm__ volatile("wfe");
	}
}
