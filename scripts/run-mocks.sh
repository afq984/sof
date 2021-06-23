#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2021 Intel Corporation. All rights reserved.

# fail on any errors
set -e

rm -rf build_ut

mkdir build_ut
#copy initial defconfig - make it TGL
cp src/arch/xtensa/configs/tgph_defconfig initial.config
cd build_ut

cmake -DBUILD_UNIT_TESTS=ON -DBUILD_UNIT_TESTS_HOST=ON ..

make -j$(nproc --all)

TESTS=`find test -type f -executable -print`
echo test are ${TESTS}
for test in ${TESTS}
do
	echo got ${test}
	valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all ./${test}
done
