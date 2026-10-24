CFLAGS := -I./ -I../platform -I../klib -Wno-error=format
ALL_OBJECTS := build/start.o build/bvec.o build/bex.o build/binit.o build/plinit.o build/klog.o \
				build/kinit.o

all:

pre_setup:
	mkdir -p build

ipod-classic-6g: pre_setup
	@echo "INFO: Building for target iPod Classic 6G."

	arm-none-eabi-as -mcpu=arm926ej-s arm32/start.S -o build/start.o
	arm-none-eabi-as -mcpu=arm926ej-s arm32/vectors.S -o build/bvec.o
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mcpu=arm926ej-s -marm -mgeneral-regs-only -c arm32/exception.c -o build/bex.o
	
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mgeneral-regs-only -c arm/arm_init.c -o build/binit.o
	
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mgeneral-regs-only -c ../platform/ipc-6g/pl_init.c -o build/plinit.o
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mgeneral-regs-only -c ../platform/ipc-6g/ipc_clcd.c -o build/plclcd.o
	
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mgeneral-regs-only -c ../klib/dlog.c -o build/klog.o
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mgeneral-regs-only -c kern/startup.c -o build/kinit.o
	
	arm-none-eabi-ld -T ../defs/ipc-6g.ld $(ALL_OBJECTS) build/plclcd.o -o build/kernel.elf
	arm-none-eabi-objcopy -O binary build/kernel.elf build/kernel.bin
	
	../../qemu-ipod-classic/build/qemu-system-arm -machine iPod-Classic -kernel build/kernel.bin \
	-semihosting -semihosting-config enable=on,target=native -serial stdio -display sdl

qemu-virt-riscv: pre_setup
	@echo "INFO: Building for target QEMU VIRT RISC-V."

	riscv64-unknown-elf-as riscv/start.S -o build/start.o
	riscv64-unknown-elf-as riscv/vectors.S -o build/bvec.o
	riscv64-unknown-elf-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mcmodel=medany -Iriscv/ -c riscv/exception.c -o build/bex.o
	
	riscv64-unknown-elf-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mcmodel=medany -c riscv/riscv_init.c -o build/binit.o
	
	riscv64-unknown-elf-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mcmodel=medany -c ../platform/qvirtrv/pl_init.c -o build/plinit.o
	
	riscv64-unknown-elf-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mcmodel=medany -c ../klib/dlog.c -o build/klog.o
	riscv64-unknown-elf-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mcmodel=medany -c kern/startup.c -o build/kinit.o
	
	riscv64-unknown-elf-ld -T ../defs/qvirtrv.ld $(ALL_OBJECTS) -o build/kernel.elf
	riscv64-unknown-elf-objcopy -O binary build/kernel.elf build/kernel.bin

	qemu-system-riscv64 -machine virt -bios default -kernel build/kernel.elf -serial mon:stdio -device ramfb

qemu-virt-arm64: pre_setup
	aarch64-linux-gnu-as arm64/start.S -o build/start.o
	aarch64-linux-gnu-as arm64/vectors.S -o build/bvec.o
	aarch64-linux-gnu-gcc -ffreestanding -nostdlib -nostartfiles -Wall -Wextra -Werror $(CFLAGS) -mgeneral-regs-only \
	-c arm64/exception.c -o build/bex.o
	
	aarch64-linux-gnu-gcc -ffreestanding -nostdlib -nostartfiles -Wall -Wextra -Werror $(CFLAGS) -c arm/arm_init.c -o build/binit.o
	aarch64-linux-gnu-gcc -ffreestanding -nostdlib -nostartfiles -Wall -Wextra -Werror $(CFLAGS) -c ../platform/qvirtarm/pl_init.c -o build/plinit.o
	aarch64-linux-gnu-gcc -ffreestanding -nostdlib -nostartfiles -Wall -Wextra -Werror $(CFLAGS) -c ../klib/dlog.c -o build/klog.o
	aarch64-linux-gnu-gcc -ffreestanding -nostdlib -nostartfiles -Wall -Wextra -Werror $(CFLAGS) -c kern/startup.c -o build/kinit.o
	
	aarch64-linux-gnu-ld -nostdlib -T ../defs/qvirtarm.ld $(ALL_OBJECTS) -o build/kernel.elf
	qemu-system-aarch64 -machine virt -cpu cortex-a57 -kernel build/kernel.elf -serial mon:stdio -device ramfb

clean:
	rm -rf build
