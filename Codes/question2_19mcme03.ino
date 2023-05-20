// initializing variables of pin numbers
int ledPin =  13;
int potentioPin = 0;

void setup() {
    pinMode(ledPin, OUTPUT); // setting the led to output mode
    Serial.begin(9600); // setting the baud rate of the serial connection
}

void loop() {
    int analogValue = analogRead(potentioPin);
    String toPrint = "Potentiometer voltage: ";
    Serial.println(toPrint + analogValue); // printing value to serial monitor
    analogWrite(ledPin, analogValue); // giving the value as an input for led light
	delay(10);
}