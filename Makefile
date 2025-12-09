include tools/utils.mk

.PHONY: all kernel bootloader disk run bear ovmf clean distclean

$(call USER_VARIABLE, KARCH, x86_64)
$(call USER_VARIABLE, QEMUFLAGS, -m 128M -M smm=off -serial stdio -d int -D qemu.log -no-reboot -no-shutdown)
$(call USER_VARIABLE, TEST_QEMUFLAGS, -m 128M -M smm=off -d int -D qemu.log -no-reboot)

override OUTPUT := zeronix.iso

override XORRISO_FLAGS += \
	-as mkisofs -b boot/limine/limine-bios-cd.bin				\
	-no-emul-boot -boot-load-size 4 -boot-info-table			\
	--efi-boot boot/limine/limine-uefi-cd.bin					\
	-efi-boot-part --efi-boot-image --protective-msdos-label	\
	sysroot -o $(OUTPUT)

all: disk

kernel:
	$(MAKE) -C kernel $(KERNEL_TARGET)

bootloader:
	$(MAKE) -C limine

disk: bootloader kernel
	rm -rf sysroot
	mkdir -p sysroot/boot
	mkdir -p sysroot/boot/limine
	mkdir -p sysroot/EFI/BOOT
	mkdir -p sysroot/system
	cp -v kernel/bin/kernel sysroot/system/
	cp -rv target/* sysroot/
	cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin sysroot/boot/limine/
	cp -v limine/BOOTX64.EFI sysroot/EFI/BOOT/
	cp -v limine/BOOTIA32.EFI sysroot/EFI/BOOT/
	xorriso $(XORRISO_FLAGS)
	./limine/limine bios-install $(OUTPUT)
	rm -rf sysroot

run: ovmf disk
	qemu-system-$(KARCH) \
		-M q35 \
		-drive if=pflash,unit=0,format=raw,file=ovmf/ovmf-code-$(KARCH).fd,readonly=on \
		-drive if=pflash,unit=1,format=raw,file=ovmf/ovmf-vars-$(KARCH).fd \
		-cdrom $(OUTPUT) \
		$(QEMUFLAGS)

test: KERNEL_TARGET=test
test: ovmf disk
	qemu-system-$(KARCH) \
		-M q35 \
		-drive if=pflash,unit=0,format=raw,file=ovmf/ovmf-code-$(KARCH).fd,readonly=on \
		-drive if=pflash,unit=1,format=raw,file=ovmf/ovmf-vars-$(KARCH).fd \
		-cdrom $(OUTPUT) \
		-nographic \
		$(TEST_QEMUFLAGS) \
		-device isa-debug-exit,iobase=0xf4,iosize=0x04 \
		|| [ $$? -eq 33 ]
	
debug: KERNEL_TARGET=debug
debug: ovmf disk
	qemu-system-$(KARCH) \
		-M q35 \
		-drive if=pflash,unit=0,format=raw,file=ovmf/ovmf-code-$(KARCH).fd,readonly=on \
		-drive if=pflash,unit=1,format=raw,file=ovmf/ovmf-vars-$(KARCH).fd \
		-cdrom $(OUTPUT) \
		$(QEMUFLAGS) \
		-s -S

defconfig:
	cp ./kernel/cfgs/$(KARCH)/default_config .config
	./tools/kconfig.sh

menuconfig:
	kconfig-mconf Kconfig
	./tools/kconfig.sh

bear: clean
	bear -- make

ovmf: ovmf/ovmf-code-$(KARCH).fd ovmf/ovmf-vars-$(KARCH).fd

clean:
	$(MAKE) -C kernel clean
	rm -rf $(OUTPUT) qemu.log

distclean: clean
	$(MAKE) -C kernel distclean
	rm -rf limine/ compile_commands.json ovmf/ .config

ovmf/ovmf-code-$(KARCH).fd:
	mkdir -p ovmf
	curl -Lo $@ https://github.com/osdev0/edk2-ovmf-nightly/releases/latest/download/ovmf-code-$(KARCH).fd

ovmf/ovmf-vars-$(KARCH).fd:
	mkdir -p ovmf
	curl -Lo $@ https://github.com/osdev0/edk2-ovmf-nightly/releases/latest/download/ovmf-vars-$(KARCH).fd
