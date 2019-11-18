#!/bin/sh


#bon ... ok ... I should have used Perl directly ...

for dir in *; do
  if [ -d $dir ]; then
    echo "Entering $dir ...";
    cd $dir;
    for file in  *.cpp *.h ; do
      echo "  $file";
#      /usr/bin/perl -pi -e 'if (m/^\#include/) {s/SMBmemoryException\.h/SMBMemoryException\.h/g}' $file;
#      /usr/bin/perl -pi -e 'if (m/^\#include/) {s/SMBimage\.h/SMBImage\.h/g}' $file;
#      /usr/bin/perl -pi -e 'if (m/^\#include/) {s/StirMarkBenchMark\.h/StirMarkBenchmark\.h/g}' $file;
#      /usr/bin/perl -pi -e 'if (m/^\#include/) {s/SMBconfig\.h/SMBConfig\.h/g}' $file;

#      /usr/bin/perl -pi -e 'if (m/^\#include/) {s/SMBtypes\.h/SMBTypes\.h/g}' $file;
      /usr/bin/perl -pi -e 'if (m/^\#include/) {s/\\/\//g}' $file;
    done;
    cd ..;
  fi;
done;