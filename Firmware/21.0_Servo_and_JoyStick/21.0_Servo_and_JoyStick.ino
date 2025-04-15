#include <Servo.h>

Servo servo;

#define xValue_pin A0
#define yValue_pin A1
#define sw_pin     A3




void setup(){
  Serial.begin(115200);
  servo.attach(6);
  pinMode(xValue_pin, INPUT);
  pinMode(yValue_pin, INPUT);
  pinMode(sw_pin, INPUT);

}

void loop(){
  int x_value = map(analogRead(xValue_pin), 0, 1024, 0, 180);
  int y_value = map(analogRead(yValue_pin), 400, 1024, 0, 180);
  bool sw_value = digitalRead(sw_pin);
  Serial.print("X:");
  Serial.print(x_value);
  Serial.print(" ");
  Serial.print("Y:");
  Serial.print(y_value);

  Serial.println();

  servo.write(y_value);
  // // delay(1000);
  // servo.write(90);
  // // delay(1000);
  // for(int i=0; i<=180; i++){
  //   servo.write(i);
  //   delay(50);
  // }
  // for(int i=370; i>0; i--){
  //   servo.write(i);
  //   delay(50);
  // }

}