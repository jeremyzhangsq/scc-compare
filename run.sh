rm -r build
mkdir build
cd build
cmake -B./ -H../
make
./SCC ../epinions.txt 1
./SCC ../epinions.txt 2
./SCC ../pokec.txt 1
./SCC ../pokec.txt 2

