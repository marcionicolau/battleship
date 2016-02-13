#!/bin/bash

set -xue

MXE_DIR=/usr/lib/mxe

if [ "$BATTLESHIP_PLATFORM" = "windows32" ]; then
    MXE_TARGET=i686-w64-mingw32.static
fi

if [ "$BATTLESHIP_PLATFORM" = "windows64" ]; then
    MXE_TARGET=x86_64-w64-mingw32.static
fi

$MXE_DIR/usr/bin/$MXE_TARGET-cmake . -Bbuild-dir
cmake --build build-dir --config Release
source build-dir/rename_exe.sh

set +xue
