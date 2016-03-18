SOURCE_DIR=`pwd`/lib
cd lib/jansson
./configure --prefix=${SOURCE_DIR}
make
make check
make install
cd ../
mv lib/libjansson.a .
rm -rf lib
