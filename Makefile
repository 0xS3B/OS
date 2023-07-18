OSSOURCES = OS

QEMUFLAGS := 	-no-reboot \
				-m 512M \
				-cdrom ./bin/os.iso

all: build-bootloader build-kernel
	mkdir -m 777 -p bin
	cd $(OSSOURCES)/bootloader && \
	cp -v limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin ../../bin

	rm -f bin/os.iso
	xorriso -as mkisofs -b limine-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot limine-cd-efi.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        bin -o bin/os.iso

	./$(OSSOURCES)/bootloader/limine/limine-deploy bin/os.iso

build-bootloader:
	make -C $(OSSOURCES)/bootloader/limine

install-limine:
	cd $(OSSOURCES)/bootloader && \
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1

build-kernel:
	make -C $(OSSOURCES)/kernel

run:
	qemu-system-x86_64 $(QEMUFLAGS) -enable-kvm

debug:
	qemu-system-x86_64 $(QEMUFLAGS) -s -S