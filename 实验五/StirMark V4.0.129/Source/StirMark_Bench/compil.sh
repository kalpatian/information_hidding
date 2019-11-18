#!/bin/sh

SRC_DIRS="Base \
	  EmbedDLL \
	  GeometricTransforms \
	  SignalProcessing \
	  SpecialTransforms \
	  Tests";

for dir in ${SRC_DIRS}; do
  echo "Entering $dir ...";
  cd $dir;
  for file in  *.cpp ; do
    echo "  $file";
    /usr/bin/g++ -Wall $file -c -I.
  done;
  cd ..;
done;