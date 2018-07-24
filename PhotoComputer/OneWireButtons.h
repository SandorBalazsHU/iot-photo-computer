#ifndef ONEWIREBUTTONS_H
#define ONEWIREBUTTONS_H

class OneWireButtons {
  public:
    int status;
    OneWireButtons(int inputPin);
    int checkButtons();

  private:
    const int inputPin;
    int keyboardState;
    int inputValue;
    const int callibrationLimits[6][2] = 
      {
        {600,610},
        {550,570},
        {830,840},
        {690,700},
        {970,980},
        {920,940}
      };
};

#endif
