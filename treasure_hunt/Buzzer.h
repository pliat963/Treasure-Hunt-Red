#ifndef _BUZZER_H
#define _BUZZER_H



// sounds of the buzzer
class Buzzer
{

public:
    //default constructor
    Buzzer() = default;
    bool withSound = true;
    void playgettingCloseSound();
    void playTreasureFoundSound();
    void playSuccessSound();
};

void Buzzer::playgettingCloseSound(){
    tone(BUZZER, 300, 100);
}
void Buzzer::playTreasureFoundSound()
{
    if (!withSound) return;
    tone(BUZZER, 523, 100);
    delay(120);
    tone(BUZZER, 698, 100);
    delay(300);  
}

void Buzzer::playSuccessSound()
{
    if (!withSound) return;
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



#endif