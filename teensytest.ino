#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define pot_1 9 // pin for Channel pot
#define cv_1 6 // pin for Channel CV
#define pot_2 7 // pin for Time pot
#define cv_2 8 // pin for Time CV
#define button 8 // Reset button
#define bled 11 // Reset LED indicator

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=224.5,432.5
AudioSynthWaveformSine   sine3; //xy=228.5,379.5
AudioSynthWaveformSine   sine1;          //xy=238.5,283.5
AudioSynthWaveformSine   sine2;          //xy=240.5,335.5
AudioMixer4              mixer1;         //xy=395.5,340.5
AudioOutputAnalog        dac1;           //xy=548,342
AudioConnection          patchCord1(waveform1, 0, mixer1, 3);
AudioConnection          patchCord2(sine3, 0, mixer1, 2);
AudioConnection          patchCord3(sine1, 0, mixer1, 0);
AudioConnection          patchCord4(sine2, 0, mixer1, 1);
AudioConnection          patchCord5(mixer1, dac1);
// GUItool: end automatically generated code

float mode_selector;
float octmult;

void setup() {                   
  AudioMemory(5);
  Serial.begin(9600);
  waveform1.begin(0.5,0,WAVEFORM_TRIANGLE);
//octave selecting
}
void loop() {
int voct = ((analogRead(cv_1)));
float scanpot = analogRead(cv_2);
float mode = ((analogRead(pot_2)/1024.0)*4.0);
if (mode_selector != 1 && mode < 0.5 ){
 mode_selector = 1;
 octmult = 0.5;
 Serial.println("mode 1");
}
if (mode_selector != 2 && mode > 1 && mode < 1.5){
 mode_selector = 2;
 octmult = 1.0;
 Serial.println("mode 2");
}
if (mode_selector != 3 && mode > 2 && mode < 2.5){
 mode_selector = 3;
 octmult = 2.0;
 Serial.println("mode 3");
}
if (mode_selector != 4 && mode > 3){
 mode_selector = 4;
 octmult = 4.0;
 Serial.println("mode 4");
}
//messy volt to octave conversion
float f1 =  octmult*(440*(pow(2,((((((((voct/315.0)*12)+ 48)-69)/12)))))));
float f2 =  octmult*(440*(pow(2,((((((((voct/315.0)*12)+72)-69)/12)))))));
float f3 =  440*(pow(2,((((((((voct/315.0)*12)+79)-69)/12))))));
float f4 =  440*(pow(2,((((((((voct/315.0)*12)+36)-69)/12))))));
sine1.frequency(f1);
sine2.frequency(f2);
sine3.frequency(f3);
waveform1.frequency(f4);
mixer1.gain(0,(scanpot/1024.0)*0.25);
mixer1.gain(1,(((scanpot/1024.0)*(-1.0)) + 1.0)*0.25);
mixer1.gain(2,(analogRead(9)/1024.0)*0.25);
mixer1.gain(3,0.6);        
}

