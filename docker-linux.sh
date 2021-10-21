#!/bin/bash
docker build -f Dockerfile.linux.base -t tinytop-linux-base .
docker build -f Dockerfile.linux -t tinytop-linux . --no-cache
docker run -it tinytop-linux