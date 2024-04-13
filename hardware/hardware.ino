// interface
const int BUTTON_RUNNING = 12;
const int BUTTON_WORKOUT = 11;
const int SWITCH_CONFIG_MODE = 10;

// feedback
const int SOUND = 9;
const int LED_RUNNING;
const int LED_WORKOUT;
const int LED_CONFIG_MODE;

// sensors


// program state
int mode = 0; // 0 none, 1 running, 2 workout 
bool config = false;
unsigned int running_dist = 10; // distance running 

void setup() {
  pinMode(BUTTON_RUNNING, INPUT)
  pinMode(BUTTON_WORKOUT, INPUT)
  pinMode(SWITCH_CONFIG_MODE, INPUT)

}

// main loop 
void loop() {
  // put your main code here, to run repeatedly:

}


// get input and call associated methods
void checkInput(){
  if(digitalRead())
}


// update lcd; led's; sound level
void sendFeedback(){

}