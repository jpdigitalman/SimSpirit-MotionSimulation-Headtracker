

#define LedBlue 23 //active high output
#define LedGreen 22 //active high output
#define LedCharge 34 //active low output Red Led: Low input shows charging 


#define ON true
#define On true
#define on true
#define Off false
#define OFF false
#define off false

unsigned long previous_millis = 0;
unsigned int interval = 3000;


//////
///

///


void blueLed(bool status){
    if(status){
        digitalWrite(LedBlue, HIGH);
    }
    else{
        digitalWrite(LedBlue, LOW);
    }
}

void greenLed(bool status){
    if(status){
        digitalWrite(LedGreen, HIGH);
    }
    else{
        digitalWrite(LedGreen, LOW);
    }
}

void redLed(bool status){
    if(status){
        digitalWrite(LedCharge, LOW);
    }
    else{
        digitalWrite(LedCharge, HIGH);
    }
}

void randomLed(){
    analogWrite(LedBlue, random(128));
    analogWrite(LedGreen, random(200));
    //analogWrite(LedCharge, random(64));
}


int ledStatex = LOW;  
unsigned long previousMillisx = 0;  
const long intervalx = 500; 

void flashBlue() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisx >= interval) {
    previousMillisx = currentMillis;
    if (ledStatex == LOW) {
      ledStatex = HIGH;
    } else {
      ledStatex = LOW;
    }
    digitalWrite(LedBlue, ledStatex);
  }
}




void initPins(){
    pinMode(KeyLatchPin, OUTPUT);    
    digitalWrite(KeyLatchPin, HIGH);

    pinMode(LedBlue, OUTPUT);
    digitalWrite(LedBlue, LOW);

    pinMode(LedGreen, OUTPUT);
    digitalWrite(LedGreen, LOW);   

    ///
    pinMode(PowerBtnPin, INPUT_PULLDOWN);
    pinMode(LeftBtnPin, INPUT_PULLUP);
    pinMode(RightBtnPin, INPUT_PULLUP);
    pinMode(PairBtnPin, INPUT_PULLUP);

}

void ledSeq(){
    PRINTLINE("Power On Sequence 1");
    powerOnline();
    PRINTLINE("Sucess On Sequence 1");
    blueLed(on);  
    PRINTLINE("Blue LED On 1");
    
    PRINTLINE("Power On Sequence 1");

    initButtons();
    PRINTLINE("Output Pins Initialized");
    powerOnline();

    PRINTLINE("Assert Power On Sequence 2");

    PRINTLINE("\nSerial Port Enabled:");
}

