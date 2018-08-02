#ifndef CAMERA_H
#define CAMERA_H

class Camera {
  public:
    Camera(byte expoPin, byte focusPin);
    byte focus(byte time);
    void exposition(byte time);
    void singleExpo();
    void expoStart();
    void expoStop();
    void setup();

  private:
    const byte expoPin;
    const byte focusPin;
    const int singleExpoTime = 200;
    byte focusState;
    byte expoState;
    byte startSemafor;
    unsigned long startTime;
    unsigned long currentTime;
};

#endif
