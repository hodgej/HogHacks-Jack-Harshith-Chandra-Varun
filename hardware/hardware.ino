#include <LiquidCrystal_I2C.h> // Library for LCD



// interface
const int BUTTON_RUNNING = 12;
const int BUTTON_WORKOUT = 11;
const int SWITCH_CONFIG_MODE = 10;
const int ANALOG_POT_RUNNING_DIST = 0;


// feedback
const int SOUND = 9;
const int LED_RUNNING = 8;
const int LED_WORKOUT = 7;
const int LED_CONFIG_MODE = 6;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows


// sensors


// program state
int mode = 0; // 0 none, 1 running, 2 workout 
bool config = false;
unsigned int running_dist = 10; // distance running 

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_RUNNING, INPUT);
  pinMode(BUTTON_WORKOUT, INPUT);
  pinMode(SWITCH_CONFIG_MODE, INPUT);
  pinMode(ANALOG_POT_RUNNING_DIST, INPUT);


  pinMode(LED_RUNNING, OUTPUT);
  pinMode(LED_WORKOUT, INPUT);
  pinMode(LED_CONFIG_MODE, INPUT);

  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  lcd.setCursor(0, 0);

  sendFeedback();
}

// main loop 
void loop() {
  // only update feedback if state change detected
  if( checkForInput() ) sendFeedback();
  
  //debug();
}


// get input and call associated methods
// returns: program state change true/false
bool checkForInput(){


  bool state_change_detected = false;
  if(digitalRead(BUTTON_RUNNING)){
    state_change_detected = mode != 1;
    mode = 1;
    
  } else if(digitalRead(BUTTON_WORKOUT)){
    state_change_detected = mode != 2;
    mode = 2;
  } else if(digitalRead(SWITCH_CONFIG_MODE)){
    state_change_detected = !config; // config=true; false.. config=false; true
    config = true;
  } else {
    state_change_detected = config;
    config = false;
  }

  int pot_inpt = int(analogRead(ANALOG_POT_RUNNING_DIST))/20;
  if(pot_inpt != running_dist){
    state_change_detected = true;
    running_dist = pot_inpt;
  }



  return state_change_detected;
}


void debug(){
  Serial.println("DEBUG: mode: " + String(mode) + ", config: " + String(config));
}


// update lcd; led's; sound level
void sendFeedback(){
  Serial.println("\n\n\n\n\n\n\nUPDATE FEEDBACK!!!!\n\n\n\n\n");
  digitalWrite(LED_RUNNING, mode == 1);
  digitalWrite(LED_WORKOUT, mode == 2);
  digitalWrite(LED_CONFIG_MODE, config);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ThriveBand");
  if(mode == 1){
    // maybe cache prev running dist so we don't need to update every time?
    lcd.setCursor(0, 1);
    lcd.print("Running Mode: " + String(running_dist) + " mi.");
  } else if(mode == 2){
    lcd.setCursor(0, 1);
    lcd.print("Workout Mode");
  } else{
    lcd.setCursor(0, 1);
    lcd.print("NO MODE SET");
  }
}