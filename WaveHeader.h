// Daniel Gilbert
// loglow@gmail.com
// copyright 2013



#ifndef __WAVEHEADER_H__
#define __WAVEHEADER_H__

#include <stdint.h>
#include <string.h>



class WaveHeader {
  private:
    struct {
      uint8_t chunkID[4];
      uint32_t chunkSize;
      uint8_t format[4];
      uint8_t subchunk1ID[4];
      uint32_t subchunk1Size;
      uint16_t audioFormat;
      uint16_t numChannels;
      uint32_t sampleRate;
      uint32_t byteRate;
      uint16_t blockAlign;
      uint16_t bitsPerSample;
      uint8_t subchunk2ID[4];
      uint32_t subchunk2Size;
    } myData;
  public:
    void init(uint32_t sampleRate, uint8_t bitDepth, uint8_t numChans);
    void update(uint32_t numBytes);
    void dataInto(uint32_t* dataArray);
    uint8_t mySize();
};



#endif



// EOF
