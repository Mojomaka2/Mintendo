/** Author: Tim Lindquist
 *  Rev: 0.0
 *
 *  NOTES: This program tests to see if hardware connections are correct. 
 */

//pin assignment
#define JOYVANSTER 19
#define JOYHOGER 16
#define A 15
#define B 14
#define X_BUTTON 13
#define Y_BUTTON 12
#define UP 10
#define DOWN 7
#define RIGHT_BUTTON 9
#define LEFT_BUTTON 8
#define START 2
#define SELECT 3
#define ANALOG_LEFT_VERT 20
#define ANALOG_LEFT_HORZ 21
#define ANALOG_RIGHT_VERT 18
#define ANALOG_RIGHT_HORZ 17
#define LEFT_BUMPER 6
#define RIGHT_BUMPER 22
#define LEFT_TRIGGER 5
#define RIGHT_TRIGGER 11
#define HOME 4


int analogLV=512;    //ideal analog center reading
int analogLH=512;
int analogRV=512;
int analogRH=512;
int GAIN=2;       //analog stick sensitivity adjustment
int LVC=488;      //actual measured analog values (left vertical center)
int LHC=515;
int RVC=521;
int RHC=500;
int led_lvl=1;      //brightness of LED's 0-255
int batt_delay=100;   //delay for battery growth annimation
int i;
int vol_lvl=0;      //boot volume level (muted)
int prev_vol=vol_lvl;
int counter=0;      //cycle counter used to call funtions less frequenctly with % function
int timeout=0;      //initialized to 0 for timeout of led annimations
int backlight_lvl=2;  //backlight value
float battery_lvl;    //voltage read value from the battery
float battery_full=4.1;                //voltage read of "full" battery 
float battery_dead=3;         //voltage read of "dead" battery
float voltage_step=(battery_full-battery_dead)/5.0; //voltage step size for LED's displaying battery level
double proc_temp;             //temperature read of proc
double fan_speed=128;             //default fan_speed speed
double ideal_proc_temp=45;  


void setup() {
  Serial.begin(9600);
  pinMode(JOYVANSTER,INPUT_PULLUP);            
  pinMode(JOYHOGER,INPUT_PULLUP);              
  pinMode(A,INPUT_PULLUP);      
  pinMode(B,INPUT_PULLUP);     
  pinMode(X_BUTTON,INPUT_PULLUP);     
  pinMode(Y_BUTTON,INPUT_PULLUP);     
  pinMode(UP,INPUT_PULLUP);       
  pinMode(DOWN,INPUT_PULLUP);      
  pinMode(RIGHT_BUTTON,INPUT_PULLUP);      
  pinMode(LEFT_BUTTON,INPUT_PULLUP);      
  pinMode(START,INPUT_PULLUP);      
  pinMode(SELECT,INPUT_PULLUP);      
  pinMode(ANALOG_LEFT_VERT,INPUT);     
  pinMode(ANALOG_LEFT_HORZ,INPUT);     
  pinMode(ANALOG_RIGHT_VERT,INPUT);     
  pinMode(ANALOG_RIGHT_HORZ,INPUT);     
  pinMode(LEFT_BUMPER,INPUT_PULLUP);      
  pinMode(RIGHT_BUMPER,INPUT_PULLUP);     
  pinMode(LEFT_TRIGGER,INPUT_PULLUP);      
  pinMode(RIGHT_TRIGGER,INPUT_PULLUP);     
  pinMode(HOME,INPUT_PULLUP);
  
}

void loop() {
  analogSticks();
  buttonsPressed();
}

///Funktioner----------------------------------------------

void analogSticks(){
   analogLV=-1*(-511+GAIN*(analogRead(ANALOG_LEFT_VERT)-LVC)); //invert 
     if(analogLV>1023) analogLV=1023;
     else if(analogLV<0) analogLV=0;
     Joystick.Y(analogLV);
     
   analogLH=512+GAIN*(analogRead(ANALOG_LEFT_HORZ)-LHC);
     if(analogLH>1023)analogLH=1023;
     else if(analogLH<0) analogLH=0;
     Joystick.X(analogLH);
     
   analogRV=512+GAIN*(analogRead(ANALOG_RIGHT_VERT)-RVC);
     if(analogRV>1023)analogRV=1023;
     else if(analogRV<0)analogRV=0;
     Joystick.Z(analogRV);
     
   analogRH=512+GAIN*(analogRead(ANALOG_RIGHT_HORZ)-RHC);
     if(analogRH>1023) analogRH=1023;
     else if(analogRH<0) analogRH=0;
     Joystick.Zrotate(analogRH);
}

void buttonsPressed(){
  (digitalRead(A))?Joystick.button(1,0):Joystick.button(1,1);
  (digitalRead(B))?Joystick.button(2,0):Joystick.button(2,1);
  (digitalRead(X_BUTTON))?Joystick.button(3,0):Joystick.button(3,1);
  (digitalRead(Y_BUTTON))?Joystick.button(4,0):Joystick.button(4,1);
  (digitalRead(UP))?Joystick.button(5,0):Joystick.button(5,1);
  (digitalRead(DOWN))?Joystick.button(6,0):Joystick.button(6,1);
  (digitalRead(RIGHT_BUTTON))?Joystick.button(7,0):Joystick.button(7,1);
  (digitalRead(LEFT_BUTTON))?Joystick.button(8,0):Joystick.button(8,1);
  (digitalRead(START))?Joystick.button(9,0):Joystick.button(9,1);
  (digitalRead(RIGHT_BUMPER))?Joystick.button(14,0):Joystick.button(14,1);
  (digitalRead(LEFT_BUMPER))?Joystick.button(13,0):Joystick.button(13,1);
  (digitalRead(LEFT_TRIGGER))?Joystick.button(12,0):Joystick.button(12,1);
  (digitalRead(RIGHT_TRIGGER))?Joystick.button(15,0):Joystick.button(15,1);

 (digitalRead(JOYVANSTER))?Joystick.button(16,0):Joystick.button(16,1);
 (digitalRead(JOYHOGER))?Joystick.button(17,0):Joystick.button(17,1);
  
 
   
     if(!digitalRead(SELECT)){              //select
        while(!digitalRead(SELECT)){            //hotkey hold
          if(!digitalRead(HOME)){             //desktop enviroment
            Keyboard.press(KEY_G);
            Keyboard.release(KEY_G);
            
          }
          if(!digitalRead(LEFT_TRIGGER)){    //left=brightness lower
            if(counter%8==0){
              
              timeout=0;
            }
          }
          if(!digitalRead(RIGHT_TRIGGER)){   //right=brightness higher
            if(counter%8==0){
              
              timeout=0;
            }
          }
          delay(50);
          counter++;
          timeout++;
          if (counter>100){
            counter=0;
          }
          if(timeout>50){
            
          }
        }
      Joystick.button(10,1);
      }
    else{
      Joystick.button(10,0);
      }
    
    if(!digitalRead(LEFT_TRIGGER)){   
      if(counter%8==0){
      
      timeout=0;
      }
    }
   
    if(!digitalRead(RIGHT_TRIGGER)){   
      if(counter%8==0){
     
      timeout=0;
      }
    }

    
    if(!digitalRead(HOME)){ //home=press start and select  
      while(!digitalRead(HOME)); //debounce
      Joystick.button(9,1);
      Joystick.button(10,1);
      }
    else{
      Joystick.button(9,0);
      Joystick.button(10,0);
      }


}

/*
void fanControl(){
  //SYNTAX: PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, Direction) 
  //input: variable we are trying to control=proc_temp
  //output: variable to be adjusted=fan_speed
  //setpoint: value we want the input to maintain=ideal_proc_temp
  //Kp Ki Kd: tuning peramiters for the controller
  //Kp=controls the output in proportion to the error (if the error gets bigger the control action gets bigger).
  //Ki=produces an output based on how much error is present. (error small= small changes, large error=big changes).
  //Kd=produces an output basied on the rate of change of the error. (d/dt(error) small=small changes, d/dt(error) large=big changes)
  double Kp=1;  //not sure tune this to be correct
  double Ki=1;  //not sure tune this to be correct
  double Kd=0;  //turn off derivative most likey will make it oscillate
  
  if(counter%50==0){
    digitalWrite(TEMP_VDD,HIGH);        //turn on temperature sensor
    proc_temp=(analogRead(TEMP)-650)/10.0;  //take temperature reading and convert to celcius
    PID(&proc_temp, &fan_speed, &ideal_proc_temp, Kp, Ki, Kd, DIRECT) 
    analogWrite(FAN,fan_speed);
    digitalWrite(TEMP_VDD,LOW);       //adjust fan speed
  }
}
*/

void lightCheck(){ 
    counter++;
    timeout++;
    if (counter>100){
    counter=0;
    }
    if(timeout>50){
    
    }
}



/*
void loop() {
  unsigned long time_now = 0;
  unsigned long wait_time=3000;
  byte led_lvl=50;
  int LVC;
  int LHC;
  int RVC;
  int RHC;
  
  Serial.println("For each of the following tests you have 3 sec to complete the action");
  Serial.print("Begin Testing");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.println(".");
  delay(500);
  Serial.println("\n");

  Serial.println("\n------BUTTON TESTS-----");
  //A TEST
  Serial.print("Press Button A: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(A)) break;
   }
  (!digitalRead(A)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  
  //B TEST
  Serial.print("Press Button B: ");
  time_now=millis();
    while(millis() < time_now + wait_time){
    if(!digitalRead(B)) break;
   }
  (!digitalRead(B)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  //X TEST
  Serial.print("Press Button X: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(X_BUTTON)) break;
   }
  (!digitalRead(X_BUTTON)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  

  //Y TEST
  Serial.print("Press Button Y: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(Y_BUTTON)) break;
   }
  (!digitalRead(Y_BUTTON)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  
  //UP TEST
  Serial.print("Press D-pad UP: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(UP)) break;
   }
  (!digitalRead(UP)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  //DOWN TEST
  Serial.print("Press D-pad DOWN: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(DOWN)) break;
   }
  (!digitalRead(DOWN)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

   //RIGHT TEST
  Serial.print("Press D-pad RIGHT: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(RIGHT_BUTTON)) break;
   }
  (!digitalRead(RIGHT_BUTTON)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  
    //LEFT TEST
   Serial.print("Press D-pad LEFT: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(LEFT_BUTTON)) break;
   }
  (!digitalRead(LEFT_BUTTON)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

//  START TEST
  Serial.print("Press button START: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(START)) break;
   }
  (!digitalRead(START)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  //SELECT TEST
  Serial.print("Press button SELECT: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(SELECT)) break;
   }
  (!digitalRead(SELECT)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  //HOME TEST
  Serial.print("Press button HOME: ");
  time_now=millis();
  while(millis() < time_now + wait_time){
    if(!digitalRead(HOME)) break;
   }
  (!digitalRead(HOME)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
/*
    //POWER TEST
  Serial.print("Press Button POWER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(PWR)) break;
   }
  (!digitalRead(PWR)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);
  */
/*
    //LEFT_BUMPER TEST
  Serial.print("Press Button LEFT BUMPER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(LEFT_BUMPER)) break;
   }
  (!digitalRead(LEFT_BUMPER)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);


    //RIGHT_BUMPER TEST
  Serial.print("Press Button RIGHT BUMPER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(RIGHT_BUMPER)) break;
   }
  (!digitalRead(RIGHT_BUMPER)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);


   //LEFT_TRIGGER TEST
  Serial.print("Press Button LEFT TRIGGER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(LEFT_TRIGGER)) break;
   }
  (!digitalRead(LEFT_TRIGGER)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);


    //RIGHT_TRIGGER TEST
  Serial.print("Press Button RIGHT TRIGGER: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(RIGHT_TRIGGER)) break;
   }
  (!digitalRead(RIGHT_TRIGGER)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  
  //JoyVanster TEST
  Serial.print("Press Button JoyVanster: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(JoyVanster)) break;
   }
  (!digitalRead(JoyVanster)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

  
  //JoyHoger TEST
  Serial.print("Press Button JoyHoger: ");
  time_now=millis();
   while(millis() < time_now + wait_time){
    if(!digitalRead(JoyHoger)) break;
   }
  (!digitalRead(JoyHoger)) ? Serial.println("pass"): Serial.println("fail");
  delay(500);

 


/*
  Serial.println("\n------LED TESTS-----");
  delay(500);
  Serial.println("LED 0 ON");
  analogWrite(LED_0,led_lvl);
  analogWrite(LED_1,0);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,0);
  delay(1000);
  Serial.println("LED 1 ON");
  analogWrite(LED_0,0);
  analogWrite(LED_1,led_lvl);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,0);
  delay(1000);
  Serial.println("LED 2 ON");
  analogWrite(LED_0,0);
  analogWrite(LED_1,0);
  analogWrite(LED_2,led_lvl); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,0);
  delay(1000);
  Serial.println("LED 3 ON");
  analogWrite(LED_0,0);
  analogWrite(LED_1,0);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,led_lvl); 
  analogWrite(LED_4,0);
  delay(1000);
  Serial.println("LED 4 ON");
  analogWrite(LED_0,0);
  analogWrite(LED_1,0);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,led_lvl);
  delay(1000);
  analogWrite(LED_0,0);
  analogWrite(LED_1,0);
  analogWrite(LED_2,0); 
  analogWrite(LED_3,0); 
  analogWrite(LED_4,0);
  Serial.println("LED 0-4 OFF");
  delay(500);
*/
/*
  Serial.println("\n------ANALOG TESTS-----");
  Serial.print("Touch nothing measurement in progress");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.println(".");
  LVC=analogRead(ANALOG_LEFT_VERT);
  LHC=analogRead(ANALOG_LEFT_HORZ);
  RVC=analogRead(ANALOG_RIGHT_VERT);
  RHC=analogRead(ANALOG_RIGHT_HORZ);
  delay(1000);
  Serial.print("\n");
  Serial.print("Now rotate the LEFT JOYSTICK: ");
  time_now=millis();
  boolean pass=false;
   while(millis() < time_now + wait_time){
    if(analogRead(ANALOG_LEFT_VERT)>LVC+100 && analogRead(ANALOG_LEFT_HORZ)>LHC+100) pass=true;
   }
   (pass)?Serial.println("pass"):Serial.println("fail");
   delay(500);
  Serial.print("Now rotate the RIGHT JOYSTICK: ");
  time_now=millis();
  pass=false;
   while(millis() < time_now + wait_time){
    if(analogRead(ANALOG_RIGHT_VERT)>RVC+100 && analogRead(ANALOG_RIGHT_HORZ)>RHC+100) pass=true;
   }
   (pass)?Serial.println("pass"):Serial.println("fail");
  delay(500);
  Serial.print("\n");
  Serial.println("Update GLOBAL VARIABLES in Nintimdo_RP_controller_board.ino with the following:");
  Serial.print("LVC=");
  Serial.println(LVC);
  Serial.print("LHC=");
  Serial.println(LHC); 
  Serial.print("RVC=");
  Serial.println(RVC);
  Serial.print("RHC=");
  Serial.println(RHC);
  
  
  
  */
  //hault
  
