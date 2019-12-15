# Console Player

Lei Mao

## Introduction

The Console Player (CPlayer) was implemented using C++, and the library [`libsndfile`](https://github.com/erikd/libsndfile) and [`libasound`](https://github.com/alsa-project/alsa-lib). It uses `libsndfile` to decode sound files and uses `libasound` to play sound in the hardware. The Console Player library `libcplayer` could be used for other C++ projects, such as games, to play sound in the background asynchronously.

The commonly supported sound formats includes `wav`, `ogg`, and `flac`. More effort of [supporting `mp3` in `libsndfile`](https://github.com/erikd/libsndfile/issues/258) is coming from the community.


## Dependencies

* CMake 3.0.0+
* [`libsndfile`](https://github.com/erikd/libsndfile)
* [`libasound`](https://github.com/alsa-project/alsa-lib)

## Installation

## Installation of Dependencies

```bash
$ apt-get install libsndfile-dev libasound2
```

### Installation to Custom Directory (Recommended)

```bash
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_INSTALL_PREFIX=[custom_dir] ..
$ make
$ make install
```

### Installation to Default Directory

```bash
$ mkdir -p build
$ cd build
$ cmake ..
$ make
$ # This requires writing permissions to `usr` directory
$ sudo make install
```

## Usages

### Playing Sound in Console

```bash
./console_player music.wav [loop]
```

Add optional argument `loop` if you want to repeat playing the sound file.

### Use CPlayer Library

The `cplayer` library supports playing the sound in the background asynchronously. Please check the header file [`cplayer.h`](src/cplayer.h) and the demo code [`bgm.cpp`](bgm.cpp) for details.

## Demo

```bash
$ mkdir -p build
$ cd build
$ cmake -DCMAKE_INSTALL_PREFIX=. ..
$ make
$ make install
$ cd bin/
$ # Play the sound file once.
$ ./console_player ../../demo/punch-deck-elegance-in-simplicity.wav
$ # Loop playing the sound file.
$ ./console_player ../../demo/BIS1536-001-flac-16.flac loop
```

## References

* [](https://gavv.github.io/articles/decode-play/)


* [Royalty Free Music](https://www.free-stock-music.com/punch-deck-elegance-in-simplicity.html)
* [](https://patrickdearteaga.com/royalty-free-music/)
* [](https://www.eclassical.com/pages/24-bit-faq.html)