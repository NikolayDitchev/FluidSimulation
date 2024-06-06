FROM gcc:13.3

USER root

RUN apt update

RUN apt install cmake -y

RUN apt install -y \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev

ADD include /usr/src/include
ADD CMakeLists.txt /usr/src
ADD src /usr/src/src

WORKDIR /usr/src

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build

# ENV DISPLAY=host.docker.internal:0.0

CMD [ "build/bin/fluid-sim" ]