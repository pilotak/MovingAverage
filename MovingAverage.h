/*
MIT License

Copyright (c) 2018 Pavel Slama

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include "mbed.h"

template <class T, uint16_t N>
class MovingAverage {
 public:
  MovingAverage();
  virtual ~MovingAverage(void);

  T add(T value);
  T get();
  int32_t get_sum();
  void fill(T value);
  void reset();

 private:
  bool _first;
  uint8_t _next;
  uint8_t _shift;
  int32_t _sum;

  T _buffer[N];
  T _result;
};

template <class T, uint16_t N>
MovingAverage<T, N>::MovingAverage():
  _first(true),
  _next(0),
  _shift(0),
  _sum(0) {

  _result = 0;
  
  while (N >> _shift != 1) {
    _shift++;
  }
}

template <class T, uint16_t N>
MovingAverage<T, N>::~MovingAverage(void) {
}

template <class T, uint16_t N>
T MovingAverage<T, N>::get() {
  return _result;
}
template <class T, uint16_t N>
int32_t MovingAverage<T, N>::get_sum() {
  return _sum;
}

template <class T, uint16_t N>
T MovingAverage<T, N>::add(T value) {

  // fill buffer when using first
  if (_first) {
    _first = false;
    fill(value);

  } else {
    _sum = _sum - _buffer[_next] + value;
    _buffer[_next] = value;
    _next = (_next + 1) & (N - 1);
  }

  _result = (_sum + (N >> 1)) >> _shift; // same as (_sum + (N / 2)) / N;

  return _result;
}

template <class T, uint16_t N>
void MovingAverage<T, N>::fill(T value) {
  for (uint16_t i = 0; i < N; i++) {
    _buffer[i] = value;
  }

  _sum = value * N;
  _next = 0;
}

template <class T, uint16_t N>
void MovingAverage<T, N>::reset() {
  _first = true;
}

/*template <class T, uint16_t N>
T MovingAverage<T, N>::get_median(bool hysteresis) {
  T buffer_sorted[N];
  T result;

  for (int i = 0; i < N; i++) {
    buffer_sorted[i] = _buffer[i];
  }

  for (int i = N - 1; i > 0; --i) {
    for (int j = 0; j < i; ++j) {
      if (buffer_sorted[j] > buffer_sorted[j + 1]) {
        T dTemp = buffer_sorted[j];
        buffer_sorted[j] = buffer_sorted[j + 1];
        buffer_sorted[j + 1] = dTemp;
      }
    }
  }

  result = buffer_sorted[(N >> 1)];

  if (hysteresis) {
    result = ((result + (_hysteresis / 2)) / _hysteresis) * _hysteresis;
  }

  return result;
}*/

#endif
