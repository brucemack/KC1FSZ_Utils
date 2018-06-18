#ifndef _Averager_h
#define _Averager_h

class Averager {

  int* buffer;
  const int bufferSize;
  int ptr;

public:

  Averager(int* buffer,int bufferSize);
  void sample(int sample);
  int getAverage() const;
};

Averager::Averager(int* buffer,int bufferSize) :
  buffer(buffer),
  bufferSize(bufferSize),
  ptr(0) {
  for (int i = 0; i < bufferSize; i++) {
    buffer[i] = 0;
  }
}

void Averager::sample(int sample) {
  buffer[ptr++] = sample;
  // Manage the wrap-around
  if (ptr == bufferSize) {
    ptr = 0;
  }
}

int Averager::getAverage() const {
  int total = 0;
  for (int i = 0; i < bufferSize; i++)
    total += buffer[i];
  return total / bufferSize;
}

#endif
