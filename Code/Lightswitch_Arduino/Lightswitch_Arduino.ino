#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial bluetooth(10, 9); // RX, TX
#define SERVO_PIN 11

#define POS_NEUTRAL 70
#define POS_ON      0
#define POS_OFF     180

Servo servo;

void activateSwitch(int); // Blocking
void watchdog();

void setup() {
  // put your setup code here, to run once:
  servo.attach(SERVO_PIN);
  servo.write(POS_NEUTRAL);
  
  bluetooth.begin(9600);
  bluetooth.print("k");
  
  Serial.begin(9600);
  Serial.println("Lightswitch checking in");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bluetooth.available()) {
    char msg = (char)bluetooth.read();
    if (msg=='a'){
      activateSwitch(POS_ON);
      bluetooth.write('a');
    }
    else if (msg=='b'){
      activateSwitch(POS_OFF);
      bluetooth.write('b');
    }
    else {
      Serial.println("Unexpected BT command found");
    }

    // Flush the bluetooth buffer to not spaz on repeated commands
    while (bluetooth.available())
      bluetooth.read();
     
  }

  watchdog();
}

void activateSwitch(int pos){
  servo.write(pos);
  delay(2000);
  servo.write(POS_NEUTRAL);
}

void watchdog() {
  static unsigned long lastTime = millis();
  if (millis() - lastTime > 1000){
    bluetooth.write('k');
    lastTime = millis();
  }
  }

