rm -r build
mkdir build
cd build
cmake -B./ -H../
make
./SCC
