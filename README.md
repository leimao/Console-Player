# Console Player

Lei Mao

## Introduction

The Console Player (CPlayer) was implemented using C++, and the library [`libsndfile`](https://github.com/erikd/libsndfile) and [`libasound`](https://github.com/alsa-project/alsa-lib). `libsndfile` was used to decode audio files and `libasound` was used to play audio in the hardware. 

The commonly supported audio formats in CPlayer includes `wav`, `ogg`, and `flac`. More effort of [supporting `mp3` in `libsndfile`](https://github.com/erikd/libsndfile/issues/258) is coming from the community. Additionally, the CPlayer library `libcplayer` could be used for other C++ projects, such as games, to play audio in the background asynchronously.


## Dependencies

* CMake 3.13.0+
* [`libsndfile`](https://github.com/erikd/libsndfile)
* [`libasound`](https://github.com/alsa-project/alsa-lib)

## Files

```
.
├── bgm
│   ├── bgm.cpp
│   └── CMakeLists.txt
├── CMakeLists.txt
├── demo
│   ├── BIS1536-001-flac-16.flac
│   ├── punch-deck-elegance-in-simplicity.wav
│   └── spring-village.ogg
├── LICENSE.md
├── README.md
└── src
    ├── CMakeLists.txt
    ├── cplayer.cpp
    ├── cplayer.h
    └── main.cpp
```


## Installation

### Build Docker Image

```bash
$ docker build -f docker/clayer.Dockerfile --no-cache --tag=clayer:0.0.1 .
```

### Run Docker Container

```bash
$ docker run -it --rm --device /dev/snd -v $(pwd):/mnt clayer:0.0.1
```

### Install CMake

Check out [the installation guide from Kitware](https://apt.kitware.com/).

### Install Dependencies

```bash
$ apt-get install libsndfile-dev libasound2-dev
```

### Install to Custom Directory (Recommended)

```bash
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_INSTALL_PREFIX=[custom_dir] ..
$ make
$ make install
```

### Install to Default Directory

```bash
$ mkdir -p build
$ cd build
$ cmake ..
$ make
$ # This requires writing permissions to `usr` directory
$ sudo make install
```

## Usages

### Play Audio in Console

```bash
./console_player audio_file [loop]
```

Add optional argument `loop` if you want to repeatedly playing the audio file.

### Use CPlayer Library

The `libcplayer` library supports playing the audio in the background asynchronously. Please check the header file [`cplayer.h`](src/cplayer.h) and the demo code [`bgm.cpp`](bgm/bgm.cpp) for details.

## Demo

### Run CPlayer in Console

```bash
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_INSTALL_PREFIX=. ..
$ make
$ make install
$ cd bin/
$ # Play the audio file once.
$ ./console_player ../../demo/punch-deck-elegance-in-simplicity.wav
$ # Loop playing the audio file.
$ ./console_player ../../demo/spring-village.ogg loop
```

### Run BGM Demo

```bash
$ ./bgm ../../demo/spring-village.ogg
```
The music would be played 6 times. In the first 3 times, the full audio file would be played. In the last 3 times, the player would receive kill signal from the program, and the audio play would be terminated before its end.

## References

* [Decoding and Playing Audio Files in Linux](https://gavv.github.io/articles/decode-play/)
* [Royalty Free Music - Free Stock Music](https://www.free-stock-music.com/punch-deck-elegance-in-simplicity.html)
* [Royalty Free Music - Patrick De Arteaga](https://patrickdearteaga.com/royalty-free-music/)
* [Sample FLAC Music - EClassical](https://www.eclassical.com/pages/24-bit-faq.html)

