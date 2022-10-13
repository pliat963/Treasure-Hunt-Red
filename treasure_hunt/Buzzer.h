#ifndef _BUZZER_H
#define _BUZZER_H

// sounds of the buzzer
class Buzzer
{
    // void tone(byte pin, int freq, int duration); //the regular "tone" buzzer function doesn't work with esp32

public:
    // default constructor
    Buzzer() = default;
    bool withSound;
    void playgettingCloseSound();
    void playTreasureFoundSound();
    void playSuccessSound();
    void playTimeUpSound();
};

// void Buzzer::tone(byte pin, int freq, int duration)
// {
//     ledcWriteTone(0, freq); // play tone
//     delay(duration);
// }
void Buzzer::playgettingCloseSound()
{
    if (!withSound)
    {
        return;
    }
    tone(BUZZER, 300, 100);
}
void Buzzer::playTreasureFoundSound()
{
    if (!withSound)
    {
        return;
    }
    tone(BUZZER, 523, 100);
    delay(120);
    tone(BUZZER, 698, 100);
    delay(300);
}

void Buzzer::playSuccessSound()
{
    if (!withSound)
    {
        return;
    }
    tone(BUZZER, 261, 100);
    delay(120);
    tone(BUZZER, 329, 100);
    delay(120);
    tone(BUZZER, 392, 100);
    delay(120);
    tone(BUZZER, 523, 200);
    delay(320);
    tone(BUZZER, 329, 100);
    delay(120);
    tone(BUZZER, 523, 500);
}

void Buzzer::playTimeUpSound()
{
    if (!withSound)
    {
        return;
    }
    tone(BUZZER, 261, 100); // CHECK change this
    delay(400);
}

#endif