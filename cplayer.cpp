#include "cplayer.h"
#include <sndfile.h>
#include <alsa/asoundlib.h>
#include <iostream>

#include <thread>

CPlayer::CPlayer()
{
    this->mPcm = NULL;
}

CPlayer::CPlayer(const char* filename)
{
    this->readSoundFile(filename);
    this->setPcm();
}

CPlayer::~CPlayer()
{
    this->releasePcm();
}

void CPlayer::readSoundFile(const char* filename)
{
    this->mFilename = filename;
    this->mSoundFile = sf_open(this->mFilename, SFM_READ, &this->mSoundInfo);
    if (this->mSoundFile)
    {
        this->mNumChannels = this->mSoundInfo.channels;
        this->mSampleRate = this->mSoundInfo.samplerate;
        this->mNumFrames = this->mSoundInfo.frames;
        // Read the entire sound file to buffer on the heap
        this->mDecodedSound.reset(new float[this->mNumFrames * this->mNumChannels]);
        sf_count_t ret = sf_readf_float(this->mSoundFile, this->mDecodedSound.get(), this->mNumFrames);
        sf_close(this->mSoundFile);
    }
    else
    {
        sf_close(this->mSoundFile);
        // throw "Unable to read the input file!";
        std::cerr << "Unable to read the input file " << filename << "!" << std::endl;
    }
}

void CPlayer::setPcm()
{
    snd_pcm_open(&this->mPcm, "default", SND_PCM_STREAM_PLAYBACK, 0);
    //snd_pcm_open(&this->mPcm, "default", SND_PCM_STREAM_PLAYBACK, 1);
    snd_pcm_set_params(this->mPcm, SND_PCM_FORMAT_FLOAT_LE,SND_PCM_ACCESS_RW_INTERLEAVED, this->mNumChannels, this->mSampleRate, 1, this->mSampleRate / 4);
    snd_pcm_get_params(this->mPcm, &this->mPcmBufferSize, &this->mPcmPeriodSize);
}

void CPlayer::releasePcm()
{
    if (this->mPcm)
    {
        snd_pcm_drain(this->mPcm);
        snd_pcm_close(this->mPcm);
    }
}


void CPlayer::load(const char* filename)
{
    this->readSoundFile(filename);
    this->releasePcm();
    this->setPcm();
}


void CPlayer::play() const
{
    for (int i = 0; i < this->mNumFrames * this->mNumChannels; i += this->mPcmPeriodSize * this->mNumChannels)
    {
        snd_pcm_writei(this->mPcm, this->mDecodedSound.get() + i, this->mPcmPeriodSize);
    }
}


void CPlayer::loop() const
{
    while (true)
    {
        this->play();
    }
}

/*
struct async_private_data {
    float *samples;
    snd_pcm_channel_area_t *areas;
    double phase;
};

void CPlayer::playAsync() const
{
    struct async_private_data data;
    snd_async_handler_t* ahandler;
    int err, count;

    data.samples = this->mDecodedSound.get();
    data.areas = areas;
    data.phase = 0;
}
*/

const char* CPlayer::getFilename() const
{
    return this->mFilename;
}

void CPlayer::printSoundInfo() const
{
    std::cout << this->mFilename << std::endl;
    std::cout << this->mNumChannels << std::endl;
    std::cout << this->mNumFrames << std::endl;
    std::cout << this->mSampleRate << std::endl;
}