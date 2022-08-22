#include <Servo.h>

#include <LiquidCrystal_I2C.h>

#include <Key.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
Servo myservo;

String buildvalue = "";
int howmuch = 1;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  myservo.attach(10); myservo.write(180); 
}

void loop() {
  char key = keypad.getKey();
  lcd.setCursor(0,0);

  if (key != NO_KEY) {
    buildvalue += String(key);
    howmuch++;
    if (howmuch >= 4) {
        if (String(buildvalue) == "2580") {
            lcd.print(String("[#] Access Grained"));
            Serial.println("(*) Access Grained!");
            myservo.write(90);
            delay(3000);
            myservo.write(180);
        } else {
            lcd.print(String("[#] Incorrect"));
            Serial.println("(*) Incorrect <3");
            myservo.write(180); 
        }
        howmuch = 0;
        buildvalue = "";
    } else {
        lcd.print(String(""));
        lcd.print(String("[#] Code " + buildvalue));
        Serial.println(String("[#] Passcode " + buildvalue));
    }
  }
}
