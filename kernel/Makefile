include ../tools/utils.mk

.PHONY: all clean

$(call USER_VARIABLE,KCC,clang)
$(call USER_VARIABLE,KLD,ld)
$(call USER_VARIABLE,KCFLAGS,-g -pipe)
$(call USER_VARIABLE,KCPPFLAGS,)
$(call USER_VARIABLE,KNASMFLAGS,-F dwarf -g)
$(call USER_VARIABLE,KLDFLAGS,)

override OUTPUT := kernel

override KCFLAGS += \
	-Wall \
	-Wextra \
	-Werror \
	-std=c23 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fPIE \
	-m64 \
	-march=x86-64 \
	-mno-80387 \
	-mno-mmx \
	-g \
	-mno-sse \
	-mno-sse2 \
	-fno-omit-frame-pointer \
	-mno-red-zone \
	-O3 \
	-mcmodel=kernel

override KCPPFLAGS += \
	-I libs/limine/include \
	-MMD \
	-MP

override KNASMFLAGS += \
	-Wall \
	-f elf64

override KLDFLAGS += \
	-m elf_x86_64 \
	-nostdlib \
	-static \
	-z max-page-size=0x1000 \
	-T linker.lds

override CFILES := $(shell cd src && find -L * -type f -name '*.c' | LC_ALL=C sort)
override ASFILES := $(shell cd src && find -L * -type f -name '*.S' | LC_ALL=C sort)
override NASMFILES := $(shell cd src && find -L * -type f -name '*.asm' | LC_ALL=C sort)
override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o))
override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d))

all: bin/$(OUTPUT)

bin/$(OUTPUT): linker.lds $(OBJ)
	mkdir -p "$$(dirname $@)"
	$(KLD) $(OBJ) $(KLDFLAGS) -o $@

# Makes sure that .c files are getting recompiled if any files included change
-include $(HEADER_DEPS)

obj/%.c.o: src/%.c
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

obj/%.S.o: src/%.S 
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

obj/%.asm.o: src/%.asm
	mkdir -p "$$(dirname $@)"
	nasm $(KNASMFLAGS) $< -o $@

clean:
	rm -rf bin/ obj/