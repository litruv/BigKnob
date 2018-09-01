#define BOUNCE_LOCK_OUT
#include <Bounce2.h>
#include <Rotary.h>

//Knob Steps
int SmallKnob = 6;
int BigKnob = 1;

//PINS

// -- Switch --
int switchpin1 = 13;
int switchpin2 = 26;

// -- Buttons --
int buttonpin1 = 14;
int buttonpin2 = 17;
int buttonpin3 = 16;
int buttonpin4 = 15;
int buttonpin5 = 6;
int buttonpin6 = 7;

// -- Encoders --
int encoderApin1 = 0;
int encoderApin2 = 1;
int encoderBpin1 = 4;
int encoderBpin2 = 3;

// -- LED -- PWM
int redPin = 20;
int bluePin = 10;
int greenPin = 22;


//SETTINGS
int state = 0;
float brightnessMultiplier = 0.1f;

//GLOBAL VARS
float redDesired = 0;
float blueDesired = 0;
float greenDesired = 0;
float redVal = 0;
float blueVal = 0;
float greenVal = 0;
int val[] = {100, 100, 100};
int lastval[] = {0, 0, 0};
bool volChanged = false;
Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();
Bounce debouncer3 = Bounce();
Bounce debouncer4 = Bounce();
Bounce debouncer5 = Bounce();
Bounce debouncer6 = Bounce();

Rotary encoder1 = Rotary(encoderApin1, encoderApin2);
Rotary encoder2 = Rotary(encoderBpin1, encoderBpin2);
unsigned char encoder1result;
unsigned char encoder2result;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonpin1, INPUT_PULLDOWN);
  pinMode(buttonpin2, INPUT_PULLDOWN);
  pinMode(buttonpin3, INPUT_PULLDOWN);
  pinMode(buttonpin4, INPUT_PULLDOWN);
  pinMode(buttonpin5, INPUT_PULLDOWN);
  pinMode(buttonpin6, INPUT_PULLDOWN);
  debouncer1.attach(buttonpin1);
  debouncer1.interval(10);
  debouncer2.attach(buttonpin2);
  debouncer2.interval(10);
  debouncer3.attach(buttonpin3);
  debouncer3.interval(10);
  debouncer4.attach(buttonpin4);
  debouncer4.interval(10);
  debouncer5.attach(buttonpin5);
  debouncer5.interval(10);
  debouncer6.attach(buttonpin6);
  debouncer6.interval(10);

  pinMode(switchpin1, INPUT_PULLDOWN);
  pinMode(switchpin2, INPUT_PULLDOWN);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  checkState();
  checkDials();
  checkButtons();

  queueMidi();

  lerpLED();

  while (usbMIDI.read()) {
  }
  
  delay(1);
}

void queueMidi() {
  if (debouncer1.rose())
    sendMidi(state, 21, 128, 0);
  if (debouncer1.fell())
    sendMidi(state, 21, 128, 1);
  if (debouncer2.rose())
    sendMidi(state, 22, 128, 0);
  if (debouncer2.fell())
    sendMidi(state, 22, 128, 1);
  if (debouncer3.rose())
    sendMidi(state, 23, 128, 0);
  if (debouncer3.fell())
    sendMidi(state, 23, 128, 1);
  if (debouncer4.rose())
    sendMidi(state, 24, 128, 0);
  if (debouncer4.fell())
    sendMidi(state, 24, 128, 1);
  if (debouncer5.rose())
    sendMidi(state, 25, 128, 0);
  if (debouncer5.fell())
    sendMidi(state, 25, 128, 1);
  if (debouncer6.rose())
    sendMidi(state, 26, 128, 0);
  if (debouncer6.fell())
    sendMidi(state, 26, 128, 1);

  if (volChanged)
    sendMidi(state, 11, val[state], 2);
}

void sendMidi(int channel, int note, int vel, int type)
{
  Serial.print("note: ");
  Serial.print(note);

  Serial.print(" velocity: ");
  Serial.print(vel);
  switch (type) {
    case 0:// noteOn
      Serial.print(" type: noteOn ");
      usbMIDI.sendNoteOn(note, vel, channel);
      break;
    case 1:// noteOff
      Serial.print(" type: noteOff ");
      usbMIDI.sendNoteOff(note, vel, channel);
      break;
    case 2:// ControlChange
      Serial.print(" type: ControlChange ");
      usbMIDI.sendControlChange(note, vel, channel);
      break;
    default:
      break;
  }
  Serial.print(" channel: ");
  Serial.println(channel);
}

void checkButtons() {
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();
  debouncer4.update();
  debouncer5.update();
  debouncer6.update();
}

void checkState() {
  if (digitalRead(switchpin1) == HIGH)
    state = 0;
  else if (digitalRead(switchpin2) == HIGH)
    state = 2;
  else
    state = 1;
}

void checkDials() {
  volChanged = false;
  
  encoder1result = encoder1.process();
  if (encoder1result) {
    if (encoder1result == DIR_CW)
      val[state] = min(val[state] + SmallKnob, 128);
    else
      val[state] = max(val[state] - SmallKnob, 0);
  }

  encoder2result = encoder2.process();
  if (encoder2result) {
    if (encoder2result == DIR_CW)
      val[state] = min(val[state] + BigKnob, 128);
    else
      val[state] = max(val[state] - BigKnob, 0);
  }

  if (val[state] != lastval[state]) {
    lastval[state] = val[state];
    volChanged = true;
  }
}

void lerpLED() {
  switch (state) {
    case 0:
      redDesired = 100;
      blueDesired = 0;
      greenDesired = 0;
      break;
    case 1:
      redDesired = 0;
      blueDesired = 100;
      greenDesired = 0;
      break;
    case 2:
      redDesired = 0;
      blueDesired = 0;
      greenDesired = 100;
      break;
    default:
      break;
  }

  redVal = lerp(redVal, redDesired, 0.005f);
  blueVal = lerp(blueVal, blueDesired, 0.005f);
  greenVal = lerp(greenVal, greenDesired, 0.005f);

  analogWrite(redPin, redVal * brightnessMultiplier);
  analogWrite(bluePin, blueVal * brightnessMultiplier);
  analogWrite(greenPin, greenVal * brightnessMultiplier);
}

float lerp(float a, float b, float x) {
  return a + x * (b - a);
}
