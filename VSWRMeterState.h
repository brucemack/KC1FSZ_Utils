/**
Copyright (c) 2018 Bruce MacKinnon, KC1FSZ
*/
#ifndef _VSWRMeterState_h
#define _VSWRMeterState_h

class VSWRMeterState {

  const int fwdPin;
  const int revPin;

  // Used for tracking the data samples
  const unsigned long samplesPerSecond = 32;
  const unsigned long msBetweenSamples = 1000UL / samplesPerSecond;
  unsigned long lastSampleStamp = 0;
  unsigned int samplePtr = 0;
  // This controls how large the window is
  const unsigned int sampleCount = 64;
  // This is where the samples are stored
  int dataFwd[64];
  int dataRev[64];

  // Used for tracking the display update
  const unsigned long msBetweenOutputCycles = 500;
  unsigned long lastOutputCycleStamp = 0;
  bool outputReady = false;
  float vswr = 0.0;
  float pwrFwd = 0.0;

  const float partVoltage = 3.3;

public:

  VSWRMeterState(int fwdPin,int revPin);

  void sampleIfNecessary(unsigned long now);
  bool isOutputReady();
  float getVswr() const;
  float getPwrFwd() const;
};

VSWRMeterState::VSWRMeterState(int fwdPin,int revPin) :
  fwdPin(fwdPin),
  revPin(revPin) {
}

void VSWRMeterState::sampleIfNecessary(unsigned long now) {

  if (now - lastSampleStamp > msBetweenSamples) {
    lastSampleStamp = now;
    dataFwd[samplePtr] = analogRead(fwdPin);
    dataRev[samplePtr] = analogRead(revPin);
    if (++samplePtr == sampleCount) {
      samplePtr = 0;
    }
  }

  // Check to see if we should generate an output
  if (now - lastOutputCycleStamp > msBetweenOutputCycles) {

    lastOutputCycleStamp = now;

    // Average the voltage readings from across all of the data we have collected
    float avgF = 0;
    float avgR = 0;
    for (unsigned int i = 0; i < sampleCount; i++) {
      avgF += dataFwd[i];
      avgR += dataRev[i];
    }

    // Update the display if there is any activity
    avgF /= (float)sampleCount;
    // Move to the 3.3V scale
    avgF = (avgF / 1024.0) * partVoltage;
    // Add the diode drop
    //avgF += 0.3;
    avgR /= (float)sampleCount;
    // Move to the 3.3V scale
    avgR = (avgR / 1024.0) * partVoltage;
    // Add the diode drop
    //avgR += 0.3;
    // Compute the reflection coefficient
    float gama = abs(avgR / avgF);
    // Compute the return loss (db)
    //float rldb = 20.0 * log10(1.0 / gama);
    // Compute the VSWR
    vswr = (1.0 + gama) / (1.0 - gama);
    // Forward power - this is based on the assumption that the bridge transformers are 12:1
    pwrFwd = ((avgF * avgF) / 100.0) / 0.0069;
    outputReady = true;
  }
}

bool VSWRMeterState::isOutputReady() {
  if (outputReady) {
    outputReady = false;
    return true;
  } else {
    return false;
  }
}

float VSWRMeterState::getVswr() const {
  return vswr;
}

float VSWRMeterState::getPwrFwd() const {
  return pwrFwd;
}

#endif
