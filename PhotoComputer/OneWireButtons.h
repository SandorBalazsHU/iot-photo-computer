#ifndef ONEWIREBUTTONS_H
#define ONEWIREBUTTONS_H

class OneWireButtons {
  public:
    int status;
    OneWireButtons(byte inputPin);
    byte checkButtons();
    int callibrationCheck();

  private:
    const byte inputPin;
    int inputValue;
    static const byte buttonsNumber = 6; 
    const int callibrationLimits[buttonsNumber][2] = 
      {
        {600,610},
        {550,560},
        {690,700},
        {830,840},
        {970,980},
        {920,940}
      };
};

#endif
