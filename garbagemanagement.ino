#include <Servo.h>  //servo library
#include <LiquidCrystal_I2C.h>


const int trigPin = 9;
const int echoPin = 10;
const int btrigPin = 5;
const int bechoPin = 6;
int servoPin = 8;
const int buzzerPin = 11;

Servo servo;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// defines variables
// long duration1, duration;
int distance1, distance2;
void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(btrigPin, OUTPUT);
  pinMode(bechoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  servo.write(180);  //close cap on power on
  delay(100);
  servo.detach();

  lcd.init();
  lcd.clear();
  lcd.backlight();
}
int SonarSensor(int trigPinSensor, int echoPinSensor) {

  digitalWrite(trigPinSensor, LOW);              // put trigpin LOW
  delayMicroseconds(2);                          // wait 2 microseconds
  digitalWrite(trigPinSensor, HIGH);             // switch trigpin HIGH
  delayMicroseconds(10);                         // wait 10 microseconds
  digitalWrite(trigPinSensor, LOW);              // turn it LOW again
  long duration = pulseIn(echoPinSensor, HIGH);  //pulseIn funtion will return the time on how much the configured pin remain the level HIGH or LOW; in this case it will return how much time echoPinSensor stay HIGH
  int distance = duration * 0.034 / 2;
  return distance;
}
void loop() {


  distance1 = SonarSensor(trigPin, echoPin);
 // Serial.print("Sensor1: ");
  //Serial.println(distance1);
  distance2 = SonarSensor(btrigPin, bechoPin);
  //Serial.print("Sensor2: ");
  //Serial.println(distance2);
  if (distance2 < 30 && distance1 > 3) {
    //Change distance as per your need
    servo.attach(servoPin);
    delay(1);
    servo.write(0);
   // Serial.print("motor opening----");
    delay(5000);
    servo.write(180);
   // Serial.println("motor closing");

    delay(1000);
    servo.detach();
  } else {
    servo.write(0);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garbage level: ");


  if (distance1 < 30) {
    int senddistance;

    if (distance1 < 30 && distance1 > 20) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Garbage level: ");
      lcd.setCursor(0, 1);
      lcd.print("0%");
      senddistance=0;
      Serial.println(senddistance);

    } else if (distance1 <= 20 && distance1 > 16) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Garbage level: ");
      lcd.setCursor(0, 1);
      lcd.print("20%");
      senddistance=20;
      Serial.println(senddistance);

    } else if (distance1 <= 16 && distance1 > 12) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Garbage level: ");
      lcd.setCursor(0, 1);
      lcd.print("40%");
      senddistance=40;
      Serial.println(senddistance);

    } else if (distance1 <= 12 && distance1 > 8) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Garbage level: ");
      lcd.setCursor(0, 1);
      lcd.print("60%");
      senddistance=60;
      Serial.println(senddistance);

    } else if (distance1 <= 8 && distance1 > 4) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Garbage level: ");
      lcd.setCursor(0, 1);
      lcd.print("80%");
      senddistance=80;
      Serial.println(senddistance);

    } else if (distance1 <= 4) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Garbage level: ");
      lcd.setCursor(0, 1);
      lcd.print("100%");
      senddistance=100;
      Serial.println(senddistance);

     
    }
    while (distance1 <= 4) {
    digitalWrite(buzzerPin, HIGH);  // Activate buzzer
    delay(500);  // On duration
    digitalWrite(buzzerPin, LOW);   // Deactivate buzzer
    delay(500);  // Off duration
    distance1 = SonarSensor(trigPin, echoPin); // Update distance1 inside the loop
  }
  }


  delay(2000);
}