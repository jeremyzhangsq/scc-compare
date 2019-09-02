rm -r build
mkdir build
cd build
cmake -B./ -H../
make
./SCC ../epinions.txt 3 ../scc-epinions-output.txt
./SCC ../epinions.txt 1 ../scc-e-output.txt
./SCC ../epinions.txt 2 ../scc-livejournal-output.txt
