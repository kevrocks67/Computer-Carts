#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>

char byte col = 3;
char byte rows = 4;
char keys[rows] [cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte colPins[cols] = {8, 7, 6};
byte rowPins[rows] = {5, 4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys) , colPins, rowPins, cols, rows );

void setup() {
  // put your setup code here, to run once:
bool lockState;
int roomNum = 0;
int moveToRoom = 0;
Servo cart1;
int cart1Pos = 0;
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
   if(key!= NO_KEY){
     Serial.println(key);ss
   }
}
