#!/bin/bash
#sudo make uninstall
#make clean
#cmake ../
make
sudo make install
sudo ldconfig

#cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..

