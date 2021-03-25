/* TECLADO MACRO
Teclado para minha filha fazer aulas no Google Meet mais confortavelmente sem se estressar com o mouse ou com o trackpad do notebook

*/

#include <Keypad.h>
#include <Encoder.h>
#include "HID-Project.h"





Encoder RotaryEncoder(14, 16); 
const int muteButton = 9;

const byte ROWS = 1;
const byte COLS = 5;

  
char keys [ROWS][COLS] = {
  {'a','v','g','y','p'} //SEQUENCIA: 'AZUL','VERMELHO','VERDE','AMARELO','PRETO'
};

long positionEncoder  = -999; //encoder RIGHT position variable

byte rowPins[ROWS] = {7};
byte colPins[COLS] = {2, 3, 4, 5, 6}; //SEQUENCIA: 'AZUL','VERMELHO','VERDE','AMARELO','PRETO'

Keypad keypad = Keypad (makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup(){
  pinMode(muteButton, INPUT_PULLUP);
  
  Serial.begin(9600);
  Keyboard.begin();
  Consumer.begin();
 // Mouse.begin();
}

void loop(){
  char key = keypad.getKey();
  encoder_Mode();
  encoder_Mute();

  
  if(key) {
    Serial.println(key);
    switch(key){
      case 'a':
        meetCam();
        break;
      case 'v':
        meetClose();
        break;
      case 'g':
        meetMute();
        break;
      case 'y':
        swapTab();
        break;
      case 'p':
        meetMax();
        break;
    }

    delay(100);
    Keyboard.releaseAll();
  }
}
  /*Keyboardvapy
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('0');
      Keyboard .releaseAll();       delay(100);
      
*/

//--------------- SUB-ROTINAS------------------


void encoder_Mode(){ // INVERTI OS FIOS NA HORA DE LIGAR TIVE QUE CONSERTAR NO CODIGO
  long newPos = RotaryEncoder.read()/2; 
    if (newPos != positionEncoder && newPos < positionEncoder) {
    positionEncoder = newPos;
      Consumer.write(MEDIA_VOL_UP); 
      }
        
    if (newPos != positionEncoder && newPos > positionEncoder) {
    positionEncoder = newPos;
      Consumer.write(MEDIA_VOL_DOWN);
    }
  }

void encoder_Mute(){
  if (!digitalRead(muteButton)){
    Consumer.write(MEDIA_VOL_MUTE);
    delay(100);
  }
  
}

void meetMute(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_D);
  delay(250);
  Keyboard.releaseAll();
}

void meetCam(){ 
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_E);
  delay(100);
  Keyboard.releaseAll();
}

void meetMax(){ 
  Keyboard.press(KEY_F11);
  delay(100);
  Keyboard.releaseAll();
}

void meetClose(){ 
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_W);
  delay(100);
  Keyboard.releaseAll();
}

void swapTab(){ 
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_PAGE_DOWN);
  delay(100);
  Keyboard.releaseAll();
}
/*
void meetBlkpp(){ 
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_K);
  delay(100);
  Keyboard.releaseAll();
}

void meetBlkmm(){ 
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_J);
  delay(100);
  Keyboard.releaseAll();
}
*/
