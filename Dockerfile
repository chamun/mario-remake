FROM alpine:latest

# Compiling, SFML dependencies, Needed for OpenGL
RUN apk update && \
  apk add --no-cache \
  binutils cmake make libgcc musl-dev gcc g++ \
  \
  libx11-dev mesa-dev libxrandr-dev      \
  eudev-dev freetype-dev openal-soft-dev \
  flac-dev libvorbis-dev glew-dev        \
  jpeg-dev libsndfile-dev                \
  \
  mesa-dri-swrast

# Compile SFML
COPY lib/SFML-2.0-sources.zip .
RUN unzip SFML-2.0-sources.zip
WORKDIR SFML-2.0
RUN cmake -G "Unix Makefiles"
RUN make && make install

# Compile game
COPY src /mario
WORKDIR /mario
RUN make

CMD /mario/game
