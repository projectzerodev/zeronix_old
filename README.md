# Zeronix

>[!Caution]
>Zeronix is in early development. Many components are incomplete, experimental,
>or not yet implemented.

Zeronix is a minimal operating system designed to serve as a foundation for
other distributions rather than as a standalone system. It provides only the
essential components, including a bootloader, kernel, package manager, and a set
of core utilities.

## Building

This section covers building Zeronix.

### Prerequisites

You will need the following external dependencies to build Zeronix:

| **Dependency** | Version | Purpose         |
| -------------- | ------- | --------------- |
| `clang`        | 18+     | C23 compiler    |
| `nasm`         | 2.16+   | Assembler       |
| `make`         | 4.4+    | Build system    |
| `xorriso`      | 1.5+    | ISO creation    |
| `git`          | 2+      | Version control |

Keep in mind that you do not need to check every version unless you have issues
building. Only Clang must meet the version requirement because of C23 support.

### Getting the Source

```sh
git clone https://codeberg.org/zerodev/zeronix.git
cd zeronix
git submodule update --init
```

### Building the ISO

```sh
make
```

## Running

This section covers running Zeronix

### QEMU

Before running in QEMU make sure both `curl` and `qemu-system-x86` are installed.

You can run Zeronix in QEMU by running:

```sh
make run
```

### Real Hardware

You can run Zeronix on real hardware by using [Balena Etcher] to flash the ISO
to a thumb drive. Keep in mind that [Rufus] is not supported.

Testing on real hardware is made at least every merge into the `stable` branch.
The hardware which is being tested on is the following:

* Intel i7-2760QM
* ATI Radeon 6970M
* 16 GB DDR3

## Configuring

You can configure the build using Kconfig. Keep in mind you will need to
have `kconfig-frontends` installed.

You can launch the configuration menu by running:

```sh
make menuconfig
```

## Getting `compile_commands.json`

The `compile_commands.json` file provides `clangd` and code editors with
information about how each source file in a project is compiled. Before
generating it make sure `bear` are installed.

You can get `compile_commands.json` by running:

```sh
make bear
```

After that you will need to restart you LSP. In Visual Studio Code press
`Ctrl + Shift + P` and run `clangd: Restart language server`.

[Balena Etcher]: https://etcher.balena.io/
[Rufus]: https://rufus.ie/en/

## License

Zeronix is licensed under the MIT License. See [LICENSE](LICENSE) for more details.

Copyright &copy; 2024-present Viktor Popp and Contributors.
