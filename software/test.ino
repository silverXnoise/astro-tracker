 #include<AccelStepper.h>
 #define HALFSTEP 8 
 #define motorPin1 4 // IN1 on the ULN2003 driver 1 
 #define motorPin2 5 // IN2 on the ULN2003 driver 1 
 #define motorPin3 6 // IN3 on the ULN2003 driver 1 
 #define motorPin4 7 // IN4 on the ULN2003 driver 1 
 #define switchPin 2 // the number of the pushbutton pin 
 #define ledPin 10 // the number of the LED pin 

 // initializing AccelStepper
 AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4); 

 // variables
 int switchstate = 0; // variable for reading the pushbutton status
 
 void setup() 
 { 
  // set AccelStepper-values 
  /* Speed: 737.1238124 steps per second in halfstep-mode 
   * 4076 Steps per resolution what is the actual resoluton of a 28BYJ-48 Stepper Motor, not the commonly for calculations used 4096
   * 737.1238124 steps per second times 60 seconds makes 44227.428744 steps per minute divided by 4076 steps per resolution makes it 10.850694 RPM for the Stepper)
   */

  /* Speed: 541.853759075 steps per second in halfstep-mode 
   * 4076 Steps per resolution what is the actual resoluton of a 28BYJ-48 Stepper Motor, not the commonly for calculations used 4096
   * 737.1238124 steps per second times 60 seconds makes 44227.428744 steps per minute divided by 4076 steps per resolution makes it 10.850694 RPM for the Stepper)
   */
   
  stepper1.setMaxSpeed(541.853759075);
  stepper1.setAcceleration(50.0);
  stepper1.setSpeed(541.853759075);

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
 
  // initialize the pushbutton pin as an input (switch is connected to GND):
  pinMode(switchPin, INPUT_PULLUP);
  digitalWrite(switchPin, HIGH);
  }
  void loop()
  { 
    // read the state of the switch value: 
    switchstate = digitalRead(switchPin); 
    if (switchstate == LOW) { 
        stepper1.runSpeed();
        digitalWrite(ledPin, HIGH);
      }
      else
      {
        stepper1.runSpeed();
        digitalWrite(ledPin, LOW);
      }
  }
