#include <Servo.h>

const int servo_pin = D1

Servo my_servo;
String user_response;
int servo_position = 0;

void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.setTimeout(1000);

  my_servo.attach(servo_pin);
  my_servo.write(servo_position);
  Serial.println("Pret");
}

void loop() {
  Serial.println("\nNouvel angle du servo [0-180] :");
  do {
    user_response = Serial.readStringUntil('\r');
  } while(user_response.length() == 0);
  
  servo_position = user_response.toInt() % 181;

  Serial.print("Valeur recue: ");
  Serial.print(servo_position, DEC);
  Serial.println("");

  my_servo.write(servo_position);
}
