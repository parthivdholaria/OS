#! /bin/bash

cd processC
cp -r /home/parthiv/linux-5.19.9 .
cd linux-5.19.9
make
cd..
rm -rf linux-5.19.9