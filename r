#!/bin/sh
cd $(dirname $0)
env LD_LIBRARY_PATH=. ./r.bin
