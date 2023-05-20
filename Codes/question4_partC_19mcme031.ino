#include <Servo.h> /* to use microservo's we need this library */
Servo myservo; /* creating a servo object, that we will be connecting */

// initializing variables of pin numbers
int potentioPin = 0;
int servoPin = 9;

void setup() {
    Serial.begin(9600); // setting the baud rate of the serial connection
	myservo.attach(servoPin); // declaring which pin we have attached the servo to
}

void loop() {
    int analogValue = analogRead(potentioPin);
  //	String toPrint = "Potentiometer converted voltage - anticlockwise: ";
  	int convertedValue = map(analogValue, 0, 1023, 0, 180);
  	// using 0 - 180, as servo input ranges from this
  	myservo.write(convertedValue);
   // Serial.println(toPrint + convertedValue); // printing value to serial monitor
 	 Serial.println(convertedValue); // printing value to serial monitor
	delay(1000);
  	// now rotating the servo the other direction, such that it swings in a range
    convertedValue = map(convertedValue, 1023, 0, 180, 0);
  	// using 180 - 0, as servo input ranges from this
  	myservo.write(convertedValue);
  //	toPrint = "Potentiometer converted voltage - clockwise: ";
   // Serial.println(toPrint + convertedValue); // printing value to serial monitor
  Serial.println(convertedValue); // printing value to serial monitor
	delay(1000);
}