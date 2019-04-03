g++ $(pkg-config --libs --cflags opencv4) main.cpp -o program && ./program $*
