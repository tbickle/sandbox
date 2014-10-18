#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/matt/sandbox/gr-sandbox/lib
export PATH=/home/matt/sandbox/gr-sandbox/build/lib:$PATH
export LD_LIBRARY_PATH=/home/matt/sandbox/gr-sandbox/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-sandbox 
