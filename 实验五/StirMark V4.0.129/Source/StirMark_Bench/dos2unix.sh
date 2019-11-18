#!/bin/sh


#
# Uner Windows, the lines end with \r\n ... the \r is 
# useless. The scripts are no more executable under Unix because
# it is interpreted ... so we have to remove it from everywhere :(
#  
# Bad news : this has to be done for this file manually :(((
#

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
    /usr/bin/perl -pi -e "s/\r//gi" $file
  done;
  for file in  *.h ; do
    echo "  $file";
    /usr/bin/perl -pi -e "s/\r//gi" $file
  done;
  cd ..;
done;

SCRIPTS="convert.sh \
	 compil.sh";

echo "SCRIPTS :"
for file in ${SCRIPTS}; do
  echo "  $file";
  /usr/bin/perl -pi -e "s/\r//gi" $file
done;