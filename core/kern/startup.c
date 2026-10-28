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
#include <version.h>
#include <klib.h>
#include <mm/mm.h>

bool g_startup_verbose = false;

void kernel_startup_log(const char *msg)
{
	if (g_startup_verbose) {
		kputs("kernel_startup: ");
		kputs(msg);
		kputs("\n");
	}
}

void kernel_startup(void)
{
	/* show kernel version */
	kputs(XEN_VERSION_STRING);
	kputs("\n");

	kernel_startup_log("mm_bootstrap");
	mm_bootstrap();

	/* temporary test */
	uptr p = (uptr)mm_balloc(4096);

	if (!p) {
		kernel_startup_log("failed allocation test");
		for(;;);
	}

	kernel_startup_log("allocated 4096 bytes");

	*(uptr*)p = 420;
	if (*(uptr*)p != 420) {
		kernel_startup_log("failed read/write test");
		for(;;);
	}

	kernel_startup_log("read and wrote 420");

	for(;;);
}
