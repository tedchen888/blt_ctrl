#include "sound.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
void MySound::sound_test() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

const int buzzer = 10;
void MySound::sound_110() {  // put your main code here, to run repeatedly:  
  static bool open = false;  
  if ( Serial.available() && Serial.read() == 'O' ) {    
    open = true;  
  } 
  if (open)  {    
    for (int i = 0; i<80; ++i)    {      
      digitalWrite(buzzer, HIGH);      
      delay(1);      
      digitalWrite(buzzer, LOW);      
      delay(1);   
    }   
    for (int i = 0; i<100; ++i)   {      
      digitalWrite(buzzer, HIGH);      
      delay(2);     
      digitalWrite(buzzer, LOW);      
      delay(2);    
    }
  }
}


