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

#define UART0_BASE 0x09000000

/*
 * Platform Layer implementation for the QEMU VIRT ARM64.
*/

/*
 * Routine PL_init_platform
 *
 * Initializes the platform by setting up the serial for early output, the
 * RAMFB and other peripheral or clocks needed and parses boot arguments.
 *
 * Parameters
 *  pinfo - Platform Layer Information pointer.
*/
void PL_init_platform(struct pl_info *pinfo)
{
	PL_set_info(pinfo);
	PL_param_setup(pinfo->boot_args);

	/* set parameters */
	pinfo->kernel_start_address = 0x00;
	pinfo->kernel_end_address = 0x00;
	pinfo->kernel_size = 0;

	pinfo->machine_ram_start = 0x00;
	pinfo->machine_ram_end = 0x00;
	pinfo->machine_ram_size = 0x4000000;

	pinfo->machine_has_display = true;

	/* QEMU virt generally requires no UART setup */
	kputs("DriftlessPL: initialized uart\n");

	/* TODO initialize ramfb here */

	/* done */
	kputs("DriftlessPL: Platform Layer initialized\n");
}

void PL_write_char_serial(char c)
{
    *(volatile uint8_t *)(UART0_BASE) = c;
}
