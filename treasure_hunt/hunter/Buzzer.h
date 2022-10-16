#ifndef _BUZZER_H
#define _BUZZER_H

// sounds of the buzzer
class Buzzer
{

public:
    // default constructor
    Buzzer() = default;
    bool withSound;
    void playgettingCloseSound();
    void playTreasureFoundSound();
    void playSuccessSound();
    void playTimeUpSound();
    void playGetReadySound(int index);
};

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
    tone(BUZZER, 200, 100); // CHECK change this
    delay(200);
    tone(BUZZER, 200, 100); // CHECK change this
    delay(200);
    tone(BUZZER, 200, 100); // CHECK change this
    delay(400);
}

void Buzzer::playGetReadySound(int index)
{
    if (!withSound)
    {
        return;
    }
    if (index == 1 || index == 2)
    {

        tone(BUZZER, 300, 100); // CHECK change this
    }
    else
    {
        tone(BUZZER, 390, 100); // CHECK change this
    }
}
#endif