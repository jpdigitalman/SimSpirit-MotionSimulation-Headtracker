#include <Button2.h>

#define PowerBtnPin 33  //active high 33 25wired
#define LeftBtnPin 21  //left active low
#define RightBtnPin 26 //right active low
#define PairBtnPin 0 //pair active low/ ALSO BOOT MODE

#define KeyLatchPin 27  // power stay on

Button2 PowerBtn, LeftBtn, RightBtn, PairBtn;
void power_handler(Button2& btn);
void power_LongPressed(Button2& btn);
void power_released(Button2& btn);

void LeftBtnPressed(Button2& btn);
void LeftBtnLong(Button2& btn);
void LeftBtnReleased(Button2& btn);

void RightBtnPressed(Button2& btn);
void RightBtnLong(Button2& btn);
void RightBtnReleased(Button2& btn);

void PairBtnPressed(Button2& btn);
void PairBtnLong(Button2& btn);
void PairBtnReleased(Button2& btn);

////
void powerOnline(){
    digitalWrite(KeyLatchPin, HIGH);
}
void poweroff(){
    digitalWrite(KeyLatchPin, LOW);
}

void initButtons(){

    PowerBtn.begin(PowerBtnPin);
    PowerBtn.setClickHandler(power_handler);
    PowerBtn.setDoubleClickHandler(power_released);
    PowerBtn.setLongClickDetectedHandler(power_LongPressed);
    
    LeftBtn.begin(LeftBtnPin);
    LeftBtn.setPressedHandler(LeftBtnPressed);
    LeftBtn.setReleasedHandler(LeftBtnReleased);
    LeftBtn.setLongClickDetectedHandler(LeftBtnLong);

    RightBtn.begin(RightBtnPin);
    RightBtn.setPressedHandler(RightBtnPressed);
    RightBtn.setReleasedHandler(RightBtnReleased);
    RightBtn.setLongClickDetectedHandler(RightBtnLong);
    
    PairBtn.begin(PairBtnPin);
    PairBtn.setPressedHandler(PairBtnPressed);
    PairBtn.setReleasedHandler(PairBtnReleased);
    PairBtn.setLongClickDetectedHandler(PairBtnLong);

}

void processBtn(){
    PowerBtn.loop();
    LeftBtn.loop();
    RightBtn.loop();
    PairBtn.loop(); 
}

/// @brief do power btn
/// @param btn 
void power_handler(Button2& btn) {
    Serial.println("Power Pressed");
    cmdBTN = 88; //enter cockpit mode
}
void power_released(Button2& btn) {
    Serial.print("Power Released: ");
    Serial.println(btn.wasPressedFor());
    cmdBTN = 0;
}
void power_LongPressed(Button2& btn) {
    Serial.println("Power Long Pressed: Powering Off...");
    redLed(true); //on LED
    delay(1500);
    poweroff();
}


/// @brief do left btn
/// @param btn 
void LeftBtnPressed(Button2& btn) {
    Serial.println("LeftBtnPressed");
    BUTTONCOMMAND = LEFT_TURN;
    cmdBTN = 1;
}
void LeftBtnLong(Button2& btn){
    Serial.print("left long click");
    cmdBTN = 11; //press and hold for speed turn
}
void LeftBtnReleased(Button2& btn) {
    Serial.print("LeftBtnReleased: ");
    Serial.println(btn.wasPressedFor());
    BUTTONCOMMAND = NONE;
    cmdBTN = 0;
}


/// @brief do right btn
/// @param btn 
void RightBtnPressed(Button2& btn) {
    Serial.println("RightBtnPressed");
    BUTTONCOMMAND = RIGHT_TURN;
    cmdBTN = 2;
}
void RightBtnLong(Button2& btn){
    Serial.print("right long click");
    cmdBTN = 22; //press and hold for speed turn
}
void RightBtnReleased(Button2& btn) {
    Serial.print("RightBtnReleased: ");
    Serial.println(btn.wasPressedFor());
    BUTTONCOMMAND = NONE;
    cmdBTN = 0;
}


/// @brief do pair btn
/// @param btn 
void PairBtnPressed(Button2& btn) {
    Serial.println("PairBtnPressed");
    BUTTONCOMMAND = PAIR;
    cmdBTN = 3;
}
void PairBtnReleased(Button2& btn) {
    Serial.print("PairBtnReleased: ");
    Serial.println(btn.wasPressedFor());
    BUTTONCOMMAND = NONE;
    cmdBTN = 0;
    if(proximity == 0){
        nearToFar = false;
    }    
}
void PairBtnLong(Button2& btn) {
    Serial.println("Pair Btn Long Pressed");
    cmdBTN = 117;
}




