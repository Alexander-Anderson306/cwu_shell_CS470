#!/bin/bash
echo "Compiling shell, cpuinfo, and meminfo executables. Executables will reside in $HOME/cwushell/bin/"
gcc cpuinfo.c -o cpuinfo
gcc cwushell.c -o cwushell

mkdir -p $HOME/cwushell/bin
mv cpuinfo cwushell $HOME/cwushell/bin
