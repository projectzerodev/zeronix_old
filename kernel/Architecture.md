# Kernel Architecure

The `src` folder structure is as follow:

```py
arch        # Architecture-specific code    f. x. `amd64/`
boot        # Bootloader abstraction        f. x. `boot.h`
core        # Scheduler, panic etc.         f. x. `panic.h`
dev         # Devices abstractions          f. x. `tty.h`
drivers     # Device drivers                f. x. `uart16550/`
fs          # Filesystem implementations    f. x. `fat32/`
hal         # Hardware abstraction          f. x. `vfs.h`
lib         # Pure library functions        f. x. `string.c`
mem         # Memory management             f. x. `pmm.h`
util        # Kernel-aware helpers          f. x. `log.h`
```
