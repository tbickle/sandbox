#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/matthew/sandbox/gr-sandbox/lib
export PATH=/home/matthew/sandbox/gr-sandbox/build/lib:$PATH
export LD_LIBRARY_PATH=/home/matthew/sandbox/gr-sandbox/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-sandbox 
