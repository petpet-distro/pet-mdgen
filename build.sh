#!/bin/sh

set -e; # exit on error

if [ "${CC}" = "" ]; then
	CC="cc"
fi

${CC} ${CFLAGS} -o pet-mdgen src/index.c

