#ifndef _RGBLED_H
#define _RGBLED_H

// rgb led
class RGBLed
{

public:
    // default constructor
    RGBLed() = default;
    void turnOff();
    void turnOnOrange();
    void turnOnGreen(int strength); // strength between 0 and 255
    void turnOnRed(int strength); // strength between 0 and 255
};

void RGBLed::turnOff()
{
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
}

void RGBLed::turnOnOrange()
{
    analogWrite(RED, 255);
    analogWrite(GREEN, 40);
}

void RGBLed::turnOnGreen(int strength)
{
    analogWrite(RED, 0);
    analogWrite(GREEN, strength);
}
void RGBLed::turnOnRed(int strength)
{
    analogWrite(GREEN, 0);
    analogWrite(RED, strength);
}

#endif