# Zeronix

<!--
Zeronix is a minimal operating system designed to serve as a foundation for
other distributions rather than as a standalone system. It provides only the
essential components, including a bootloader, kernel, package manager, and a set
of core utilities.
-->

## Building

This section covers building Zeronix.

### Prequisites

You will need the following external dependecies to build Zeronix:

* `clang`: The C compiler used. Requires version 18 or newer.
* `nasm`: The assember used. Supports version 2.16 or newer.
* `gmake` The build system used. Supports version 4.4 or newer.
* `curl`: Used for downloading dependencies. Supports version 8 or newer.
* `xorriso`: The ISO image creation tool. Supports version 1.5 or newer.
* `git`: The version control used. Supports version 2 or newer.

Keep in mind that you do not need to check every version unless you have issues
building. The only required is Clang which needs to be version 18+ because of
C23 support.

### Getting the source

```sh
git clone https://codeberg.org/zerodev/zeronix.git
cd zeronix
git submodule update --init
```

### Building the ISO

```sh
gmake
```

## Running

This section covers running Zeronix

### QEMU

Before running in QEMU make sure both `curl` and `qemu-system-x86` is installed.

You can run Zeronix in QEMU by running:

```sh
gmake run
```

### Real Hardware

You can run Zeronix on real hardware by using [Balena Etcher] to flash the ISO
to a thumb drive. Keep in mind that [Rufus] is not supported.

Testing on real hardware is made at least every merge into the `stable` branch.
The hardware which is being tested on is the following:

* Intel i7-2760QM
* ATI Radeon 6970M
* 16 GB DDR3

## Getting `compile_commands.json`

The `compile_commands.json` file provides `clangd` and code editors with
information about how each source file in a project is compiled. Before
generating it make sure `bear` is installed.

You can get `compile_commands.json` by running:

```sh
make bear
```

After that you will need to restart you LSP. In Visual Studio Code press
`CRTL + SHIFT + P` and run `clangd: Restart language server`.

[Balena Etcher]: https://etcher.balena.io/
[Rufus]: https://rufus.ie/en/

## License

Zeronix is licensed under the MIT License. See [LICENSE](LICENSE) for more details.

Copyright &copy; 2024-present Viktor Popp and Contributers.
