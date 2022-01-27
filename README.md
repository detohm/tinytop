# TinyTop
A system monitoring tool for linux system. This project is for educational purpose while I studied at Udacity C++ Nanodegree Program.
## Screenshot
![TinyTop](https://github.com/detohm/tinytop/blob/main/docs/tinytop.jpg?raw=true)

## Features
- Get basic information from machine such as cpu and memory utilization
- Get uptime and linux version
- List all the processes and their related information such as pid, resource utilization in real-time
## How To Build and Run
This project depends on [ncurses](https://invisible-island.net/ncurses/announce.html) library.

This project uses `CMake` as a cross-platform build automation tool. For example, in Linux and macOS, you can use the following command to build and run.
```shell
# supposing that you are at the project directory (where the CMakeLists.txt is hosted.)
mkdir build
cd build
cmake ..
make
./TinyTop
```
Alternatively, you can run this project using docker command below,
```shell
docker build -f Dockerfile.linux.base -t tinytop-linux-base .
docker build -f Dockerfile.linux -t tinytop-linux . --no-cache
docker run -it tinytop-linux
```