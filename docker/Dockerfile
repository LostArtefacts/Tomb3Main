# Tomb3Main building toolchain.
#
# This is a multi-stage Docker image. It is designed to keep the final image
# size low. Each stage builds an external dependency. The final stage takes the
# artifacts (binaries, includes etc.) from previous stages and installs all the
# tools necessary to build Tomb3Main.

# MinGW
FROM ubuntu:latest as mingw

RUN apt-get update \
    && apt-get upgrade -y \
    && apt-get install -y \
        gcc-mingw-w64-i686 \
        g++-mingw-w64-i686 \
        git \
        make

# Tomb3Main
FROM mingw

# set the build dir - actual files are mounted with a Docker volume
RUN mkdir /app
WORKDIR /app

# system dependencies
# don't prompt during tzinfo installation
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Warsaw
# configure pkgconfig manually
# https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=967969
ENV PKG_CONFIG_LIBDIR=/ext/lib/
ENV PKG_CONFIG_PATH=/ext/lib/pkgconfig/
RUN apt-get update \
    && apt-get upgrade -y \
    && apt-get install -y \
        mingw-w64-tools \
        pkg-config \
        upx \
        python3-pip \
    && python3 -m pip install \
        pyjson5 \
        meson \
        ninja

ENTRYPOINT ["/app/docker/entrypoint.sh"]
