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

// setPcm would bring noticeable noise from the speaker.
void CPlayer::setPcm()
{
    snd_pcm_open(&this->mPcm, "default", SND_PCM_STREAM_PLAYBACK, 0);
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
}

void CPlayer::play()
{
    this->setPcm();
    for (int i = 0; i < this->mNumFrames * this->mNumChannels; i += this->mPcmPeriodSize * this->mNumChannels)
    {
        snd_pcm_writei(this->mPcm, this->mDecodedSound.get() + i, this->mPcmPeriodSize);
    }
}


void CPlayer::playAsync(bool& killSignal)
{
    this->setPcm();
    for (int i = 0; i < this->mNumFrames * this->mNumChannels; i += this->mPcmPeriodSize * this->mNumChannels)
    {
        if (killSignal == true)
        {
            break;
        }
        snd_pcm_writei(this->mPcm, this->mDecodedSound.get() + i, this->mPcmPeriodSize);
    }
}

void CPlayer::loop()
{
    while (true)
    {
        this->play();
    }
}

void CPlayer::loopAsync(bool& killSignal)
{
    while (true)
    {
        if (killSignal == true)
        {
            break;
        }
        this->playAsync(killSignal);
    }
}

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