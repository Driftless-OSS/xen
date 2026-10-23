CFLAGS := -I./ -I../platform -I../klib -mgeneral-regs-only -Wno-error=format
ALL_OBJECTS := build/start.o build/bvec.o build/bex.o build/binit.o build/plinit.o build/klog.o

all:

pre_setup:
	mkdir -p build

ipod-classic-6g: pre_setup
	@echo "INFO: Building for target iPod Classic 6G."

	arm-none-eabi-as -mcpu=arm926ej-s arm32/start.S -o build/start.o
	arm-none-eabi-as -mcpu=arm926ej-s arm32/vectors.S -o build/bvec.o
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -mcpu=arm926ej-s -marm -c arm32/exception.c -o build/bex.o
	
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -c arm/arm_init.c -o build/binit.o
	
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -c ../platform/ipc-6g/pl_init.c -o build/plinit.o
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -c ../platform/ipc-6g/ipc_clcd.c -o build/plclcd.o
	
	arm-none-eabi-gcc -ffreestanding -Wall -Wextra -Werror $(CFLAGS) -c ../klib/dlog.c -o build/klog.o
	
	arm-none-eabi-ld -T ../defs/ipc-6g.ld $(ALL_OBJECTS) build/plclcd.o -o build/kernel.elf
	arm-none-eabi-objcopy -O binary build/kernel.elf build/kernel.bin
	
	../../qemu-ipod-classic/build/qemu-system-arm -machine iPod-Classic -kernel build/kernel.bin \
	-semihosting -semihosting-config enable=on,target=native -serial stdio -display sdl

clean:
	rm -rf build
