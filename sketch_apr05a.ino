/**********************************************
   Autor : Corentin Dupont
   Date : 06 april 2017
   Object : K2000 and speed control with keypad
 **********************************************/

#include <Keypad.h>

int NbrLed = 4;
int ledPins[] = { 10, 11, 12, 13 };
int interval[3] = {110, 70, 35};
int vit = 0;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  Serial.begin(9600);
  for ( int i = 0; i < NbrLed; i++ )
    pinMode( ledPins[i], OUTPUT );
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad

}

void loop()
{
  char keypressed = keypad.getKey();
  Serial.write(keypressed);
  K2000();
}

void intelligentDelay()
{

  unsigned long startMillis = millis();
  unsigned long currentMillis = millis();

  while ( (currentMillis - startMillis) < vit)
  {
    currentMillis = millis();

  }
}

void K2000()
{
  for ( int i = 0; i < NbrLed; i++)
  {

    digitalWrite( ledPins[i], HIGH );
    digitalWrite( ledPins[i], LOW );
    intelligentDelay();
  }

  for ( int i = NbrLed - 1; i >= 0; i--)
  {
    for ( int iBrowser = 0; iBrowser < NbrLed; iBrowser++ )
    {
      if ( iBrowser == (i - 1) || iBrowser == (i + 1) || iBrowser == i )
        digitalWrite( ledPins[iBrowser], HIGH );
      else
        digitalWrite( ledPins[iBrowser], LOW );
    }
    intelligentDelay();
  }

}

void keypadEvent( KeypadEvent keypressed)
{
  switch (keypad.getState())
  {
    case PRESSED:
      if (keypressed == '1')
      {
        vit = interval[0];
        return;
      }

      if (keypressed == '2')
      {
        vit = interval[1];
        return;
      }
      if (keypressed == '3')
      {
        vit = interval[2];
        return;
      }
      if (keypressed = 'D')
      {
        for ( int i = 0; i < NbrLed; i++ )
          digitalWrite( ledPins[i], LOW );
      }
  }
}
