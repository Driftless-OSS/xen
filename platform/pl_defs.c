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

struct pl_info *g_pinfo;

/*
 * Platform Layer kernel APIs
*/

struct pl_info *PL_get_info(void)
{
	return g_pinfo;
}

void PL_set_info(struct pl_info *pinfo)
{
	g_pinfo = pinfo;
}

void PL_param_setup(void *b_args)
{
	/* ideally we would parse the actual logs here.. but that is later */
	(void)b_args;
	g_startup_verbose = true;
}

u64 PL_get_ram_size()
{
	return g_pinfo->machine_ram_size;
}

uptr PL_get_kern_start_address()
{
	return g_pinfo->kernel_start_address;
}

uptr PL_get_kern_end_address()
{
	return g_pinfo->kernel_end_address;
}
