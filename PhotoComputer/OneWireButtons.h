#ifndef ONEWIREBUTTONS_H
#define ONEWIREBUTTONS_H

class OneWireButtons {
  public:
    int status;
    OneWireButtons();
    int checkButtons();

  private:
    int keyboardState;
    int inputValue;
    int callibrationLimits[5][1];
};

#endif
