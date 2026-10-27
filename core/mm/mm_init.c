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
#include <player.h>
#include <klib.h>
#include <mm/mm.h>

/*
 * Initialization of the memory manager systems
*/

void mm_bootstrap_log(const char *msg)
{
	if (g_startup_verbose) {
		kputs("mm_bootstrap: ");
		kputs(msg);
		kputs("\n");
	}
}

void mm_bootstrap(void)
{
	/*
	 * Initialize the bootstrap allocator that allows us to allocate
	 * any bootstrap metadata structures for the proper allocator.
	*/
	mm_bootstrap_log("mm_alloc_bootstrap");
	mm_alloc_bootstrap();
}
