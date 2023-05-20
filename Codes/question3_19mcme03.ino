// initializing variables used for attached pins
int HIGHswitch = 3;
int LOWswitch = 0;
int PUMP1 = 12;
int PUMP2 = 13;
int HIGHvalue = 0, LOWvalue = 0;


void setup(){
  pinMode(HIGHswitch, INPUT); // this is the HIGH transducer
  pinMode(LOWswitch, INPUT); // this is the LOW transducer
  pinMode(PUMP1, OUTPUT); // this is the first pump
  pinMode(PUMP2, OUTPUT); // this is the second pump
  Serial.begin(9600);
}

void loop(){
  // reading the switch input pins
  HIGHvalue = digitalRead(HIGHswitch);
  LOWvalue = digitalRead(LOWswitch);

    
	// if HIGH switch is on
  if(HIGHvalue == 1){
    Serial.println("PUMP 1 is on");
  	digitalWrite(PUMP1, HIGH); // We switch on the first pump
    delay(3000);
    HIGHvalue = digitalRead(HIGHswitch);
    if(HIGHvalue == 1){ // if after 3 seconds HIGH switch is still on, second pump is switched on
      	Serial.println("Alert! PUMP 1 is not sufficient to reach low level,PUMP 2 is on");
    	digitalWrite(PUMP2, HIGH);
    }
  }
  if (digitalRead(HIGHswitch) == 0  &&  digitalRead(PUMP1) == HIGH){ 
    // if previously the pumps are running, but the HIGH switch is now OFF
    if (digitalRead(LOWswitch) == 0){
      // if LOW switch is NOT Toggled on yet, adviced to switch it on
    	Serial.println("Toggle Low Level Switch to on!");
      	delay(1000);
    }
    else{
      //pumps are switched off
    	digitalWrite(PUMP1, LOW);
    	digitalWrite(PUMP2, LOW);
      
    }  
  }
  
  if(digitalRead(LOWswitch) == 1 && digitalRead(PUMP1) == HIGH){
    // if LOW switch is toggled on and previously pumps are running
    if(digitalRead(HIGHswitch) == 0){
      // if HIGH switch is off, turn off the pumps
    	digitalWrite(PUMP1, LOW);
    	digitalWrite(PUMP2, LOW);
      	Serial.println("Maintaining Low-level water");
    }
  }
  if(digitalRead(LOWswitch) == 1 && digitalRead(PUMP1) == LOW){
    // if LOW switch is toggled on and no pumps are running
    if(digitalRead(HIGHswitch) == 0){
      // do nothing
      	Serial.println("Maintaining Low-level water");
        delay(1000);
    }
    
  }
   if(digitalRead(LOWswitch) == 0 && digitalRead(PUMP1) == LOW){
     // if LOW switch is toggled off and no pumps are running
     // Advised to switch ON LOW switch
   		Serial.println("Advised to Toggle Low Level Switch on");
     delay(1000);
   }

delay(100);
}

