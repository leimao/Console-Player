#ifndef CPLAYER_H
#define CPLAYER_H

#include <memory>
#include <sndfile.h>
#include <alsa/asoundlib.h>

class CPlayer
{
public:
    CPlayer();
    //CPlayer(const char* filename);
    ~CPlayer();
    bool readSoundFile(const char* filename);
    bool setPcm();
    void releasePcm();
    void load(const char* filename);
    void play();
    void loop();
    void playAsync(bool& killSignal);
    void loopAsync(bool& killSignal);
    const char* getFilename() const;
    void printSoundInfo() const;

private:
    const char* mFilename;
    SF_INFO mSoundInfo;
    SNDFILE* mSoundFile;
    int mNumChannels;
    int mSampleRate;
    int mNumFrames;
    std::unique_ptr<float> mDecodedSound;
    snd_pcm_t* mPcm;
    snd_pcm_uframes_t mPcmPeriodSize;
    snd_pcm_uframes_t mPcmBufferSize;
};

#endif