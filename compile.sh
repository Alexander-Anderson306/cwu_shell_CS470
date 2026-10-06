#!/bin/bash
echo "Compiling shell, cpuinfo, and meminfo executables. Executables will reside in $HOME/cwushell/bin/"
gcc cpuinfo.c -o cpuinfo
gcc meminfo.c -o meminfo
gcc cwushell.c -o cwushell

mkdir -p $HOME/cwushell/bin
mv cpuinfo cwushell meminfo $HOME/cwushell/bin
