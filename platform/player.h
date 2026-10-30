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

#ifndef _PLATFORM_LAYER_H_
#define _PLATFORM_LAYER_H_

#include <stdint.h>
#include <klib.h>

struct pl_info
{
	void *dtb;
	void *boot_args;

	uptr kernel_start_address;
	uptr kernel_end_address;
	u64 kernel_size;

	uptr machine_ram_start;
	uptr machine_ram_end;
	u64 machine_ram_size;

	bool machine_has_display;
};

extern bool g_startup_verbose;

void PL_init_platform(struct pl_info *pinfo);
void PL_write_char_serial(char c);

struct pl_info *PL_get_info(void);
void PL_set_info(struct pl_info *pinfo);
void PL_param_setup(void *b_args);

u64 PL_get_ram_size();
u64 PL_get_ram_start_address();
uptr PL_get_kern_start_address();
uptr PL_get_kern_end_address();

void PL_put_pixel(u16 x, u16 y, u8 r, u8 g, u8 b);
void PL_clear_display(u8 r, u8 g, u8 b);
void PL_present_display(void);

#endif
