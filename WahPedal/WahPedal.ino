#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define TEENSY_A0 0

// Audio Setup
  AudioFilterBiquad wahFilter;
  //AudioSynthWaveform       SquareWave;      //xy=251.1999969482422,178.1999969482422
  AudioInputI2S            i2sIn;
  AudioOutputI2S           i2sOut;           //xy=584.2000370025635,210.20001745224
  AudioConnection          patchCord0(i2sIn, wahFilter);
  AudioConnection          patchCord1(wahFilter, 0, i2sOut, 0);
  AudioConnection          patchCord2(wahFilter, 0, i2sOut, 1);
  AudioControlSGTL5000     codec;     //xy=216.1999969482422,91.19999694824219

  unsigned long filterLow = 300;           // Hz
  unsigned long filterHigh = 5000;     // HZ
  unsigned int filterQ = 2.2;


  

void setup() {
  // ADC Setup
  Serial.begin(115200);
  pinMode(TEENSY_A0, INPUT);

  

  AudioMemory(18);
  
  codec.enable();
  codec.lineInLevel(12);
  codec.volume(0.5);
  AudioNoInterrupts();
  

  //SquareWave.begin(0.5, 50, WAVEFORM_SQUARE);
  
  AudioProcessorUsageMaxReset();
  AudioMemoryUsageMaxReset();
  AudioInterrupts();

}

int pedalPosition;

void loop() {
  // put your main code here, to run repeatedly:
  pedalPosition = map(analogRead(0), 0, 1023, filterLow, filterHigh);
  wahFilter.setLowpass(0, pedalPosition, filterQ);
  Serial.print("Pedal Position = ");
  Serial.println(pedalPosition);
}
