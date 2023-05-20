// initializing variables of pin numbers
int potentioPin = 0;

void setup() {
    Serial.begin(9600); // setting the baud rate of the serial connection
}

void loop() {
    int analogValue = analogRead(potentioPin);
  	String toPrint = "Potentiometer converted voltage: ";
  	int convertedValue = map(analogValue, 0, 1023, 0, 100);
    /* this function maps the analog values to scaled down values like so:
      syntax -> map(value, fromLow, fromHigh, toLow, toHigh)
    */
    //Serial.println(toPrint + convertedValue); // printing value to serial monitor
  Serial.println(convertedValue); // printing value to serial monitor
	delay(10);
}