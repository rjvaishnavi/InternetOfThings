// initializing variables of pin numbers
int potentioPin = 0;

void setup() {
    Serial.begin(9600); // setting the baud rate of the serial connection
}

void loop() {
    int analogValue = analogRead(potentioPin);
    String toPrint = "Potentiometer voltage: ";
    //Serial.println(toPrint + analogValue); // printing value to serial monitor
  	Serial.println(analogValue);
	delay(10);
}