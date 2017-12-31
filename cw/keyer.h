#ifndef __KEYER_H__
#define __KEYER_H__

class Keyer {
public:
  Keyer();

  void init(unsigned long currentMillis);
  void setPin(int value);
  void setWpm(int value);

  bool isIdle();

  bool keying(int elements);
  bool ig(int elements);

  void update(unsigned long currentMillis);

private:
  enum State {
    IDLE,
    KEYING,
    IG // in gap
  };

  State _state;
  int _pin;
  int _mpe;
  unsigned long _lastMillis;
  unsigned long _timeout;

  bool setState(State state, int elements);
};

#endif // __KEYER_H__
