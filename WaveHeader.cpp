// Daniel Gilbert
// loglow@gmail.com
// copyright 2013



#include "WaveHeader.h"



// ------------------------------------------------------------
// initializer, is passed audio settings, configures the header
// accordingly. makes some assumptions about format, endian, etc.
// ------------------------------------------------------------
void WaveHeader::init(uint32_t newSampleRate, uint8_t newBitDepth, uint8_t newNumChans) {
  
  // set all the ASCII literals
  memcpy(myData.chunkID, "RIFF", 4);
  memcpy(myData.format, "WAVE", 4);
  memcpy(myData.subchunk1ID, "fmt ", 4);
  memcpy(myData.subchunk2ID, "data", 4);
  
  // set all the known numeric values
  myData.audioFormat = 1;
  myData.chunkSize = 36;
  myData.subchunk1Size = 16;
  myData.subchunk2Size = 0;
  
  // set the passed-in numeric values
  myData.sampleRate = newSampleRate;
  myData.bitsPerSample = newBitDepth;
  myData.numChannels = newNumChans;
  
  // calculate the remaining dependent values
  myData.blockAlign = myData.numChannels * myData.bitsPerSample / 8;
  myData.byteRate = myData.sampleRate * myData.blockAlign;
  
}



// ------------------------------------------------------------
// passed the number of bytes of audio data in the file, then
// adjusts the header. must be called before file is written
// ------------------------------------------------------------
void WaveHeader::update(uint32_t numBytes) {
  myData.subchunk2Size = numBytes;
  myData.chunkSize = myData.subchunk2Size + 36;
}



// ------------------------------------------------------------
// copies all header data into the provided buffer
// ------------------------------------------------------------
void WaveHeader::dataInto(uint32_t* dataArray) {
  memcpy(dataArray, &myData, mySize());
}



// ------------------------------------------------------------
// returns the size of the wave header in bytes
// ------------------------------------------------------------
uint8_t WaveHeader::mySize() {
  return sizeof(myData);
}



// EOF
