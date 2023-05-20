#include <Servo.h> /* to use microservo's we need this library */
Servo myservo; /* creating a servo object, that we will be connecting */

// initializing variables used globally
int servoPin = 9;
int moisture = 0;
int temperature = 0;
int celsius = 0;
int moistlevel = 0;

void setup(){	
  pinMode(A1, INPUT); // Temperature sensor pin is connected	
  pinMode(A2, OUTPUT); // Soil moisture sensor taking output
  pinMode(A3, INPUT); // Soil moisture sensor taking input
  pinMode(13, OUTPUT); // LED is in output mode
  myservo.attach(servoPin); // declaring which pin we have attached the servo to
  Serial.begin(9600);
}

void loop(){
  // Apply power to the soil moisture sensor
  digitalWrite(A2, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  moisture = analogRead(A3);
  moistlevel = map((moisture), 0, 872, 0, 100); 
  // real soil moisture output ranges from 0-872 due to resistance of the device
 
  temperature = analogRead(A1); // read temperature value from sensor
    
  // convert temperature to celcius Celsius
  celsius = map(((temperature - 20) * 3.04), 0, 1023, -40, 125);
  // Serial.print(celsius);
  //Serial.print(" C\n");
    //	Serial.println(temperature);
  // Turn off the sensor to reduce metal corrosion over time
  digitalWrite(A2, LOW);

  // decision making for needing water
  if (moistlevel <= 40 || celsius >= 38){
    Serial.print("NEEDS WATER: Temperature level = ");
    Serial.print(celsius);
    Serial.print("C, Soil Moisture = ");
    Serial.print(moistlevel);
    Serial.print("\% \n");
    digitalWrite(13, HIGH); // turn LED on to alert that watering is happening
    myservo.write(90); // "Opens" the "valve" if water is required
  }
  else{
    Serial.print("NO WATER NEEDED: Temperature level = ");
    Serial.print(celsius);
    Serial.print("C, Soil Moisture = ");
    Serial.print(moistlevel);
    Serial.print("\% \n");
    digitalWrite(13, LOW); // turn LED off, if it was on previously
    myservo.write(0); 
    // "closes" the "valve" to original place if "valve" was open previously
  }
  delay(1000); // Wait for 100 millisecond(s)
}