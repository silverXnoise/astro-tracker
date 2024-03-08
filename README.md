# HD Astro Tracker

Based on the models and work by [@baokhangnn](https://www.thingiverse.com/baokhangnn) on Thingiverse

## Summary

This is the third generation of the star tracker [@baokhangnn](https://www.thingiverse.com/baokhangnn) started years ago.

This 3D printed star tracker can handle a relatively large lens and camera. Even though the stepper motor is rather small, it leverages gear reduction stages to improve its load capacity. Assuming perfect conditions, the torque output is over 200 ft-lbs!!!

There is a fair bit of backlash, just keep the camera loaded between the 10-11 o'clock position when looking at the output face.

Previous Design: [https://www.thingiverse.com/thing:4879109/](https://www.thingiverse.com/thing:4879109/)

### Print Settings

- Printer brand: Prusa
- Printer: I3 MK3S
- Rafts: No
- Supports: Yes
- Resolution: .2mm
- Infill: 30% Cubic
- Filament brand: Any
- Filament color: Any
- Filament material: PETG
- Notes:
  - Minimum of 3 layers
  - Test print the planetary gears and planetary plate. The gears should spin freely on the plate. If it doesn't, you need to re-calibrate your printer. Possibly adjust your extrusion rate.
  - Once the calibration is satisfactory, print 1X of everything except:  
    - Qty: 5X Part01-Planetary Plate - 5X  
    - Qty: 5X Part13-Sun-Inner - 5X  
    - Qty: 24X Part08-PlanetaryGear - 24X
  - Ring-Body may require support on build plate only.

### Electronics

- 28BYJ-48 w/ ULN2003 Stepper Driver
- Arduino Nano Every
- USB Portable Charger (a 10000mah charger will run this for close to 24 hours!)
- USB cable to power the Nano from the charger.

### Hardware

- 1x 3/8-16 Hex Bolt x 2.5 Long (McMaster# 91268A538)
- 1x 3/8-16 Hex Nut
- 2x 6806-2RS 30mmx42mmx7mm Ball Bearings
- 1x 3mm x 58mm rod or dowel pin
- 1x 1/4-20 Bolt (McMaster# 92949A537)
- 1x 1/4" Washer
- 1x 1/4-20 Coupler (McMaster# 90264A435)
- 2x M3 x 6mm screw (a M3 tap will also be helpful for threading the holes.)

### Optional

- 1-2x Your favorite ball head w/ 3/8-16 mounting.
- 1x Celestron CG-5 PolarScope (#94224)

### MCU Wiring & Programming

Drive the stepper motor at 8.0 rpm. There are plenty of example code for the stepper listed on the internet.

#### Wiring

```plaintext
- Stepper driver: Arduino Uno (Change the pins and code as needed)
- IN1: D4
- IN2: D5
- IN3: D6
- IN4: D7
- Pwr-: GND
- Pwr+: 5V
```

#### Programming

To use the included test code, download and install the `AccelStepper` library into the Arduino programming environment. Then load the TestCode2.ino on to the Arduino. I modded someone else's code to work with my tracker.You can update the code to run at 8RPM as Etaloche pointed out the earth spins a little faster than 24hour to be more accurate!

```cpp
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
```

---

### Post-Printing

#### Head and Gear Train Assembly

1) Assemble the 1/4-20 hex coupler nut into the body. This is where the tripod will mount. Use metal washer and screw through the front opening to secure the coupler.
2) Press Part08 into one of the ball bearings, the install into rear of the the main body. Note orientation is shown in figures. Install front ball bearing.
3) Install nut into face of Part04 and install through front bearing and rear bearing until seated.
4) Assemble hex bolt along with Part05, Part06 (thick or thin depending of bearing choice), and Part09. NOTE: Part09 has a 1 deg taper, the bigger side goes in first. Also press fit the 3mm rod through the hole of Part09. Then insert into rear of housing and screw the bolt through the nut until snug/tight.
5) With a pair of needle nose pliers add the planetary gears to the base planetary plate. There is a small .5mm step on one face of the planets, that should face away from the plate. Again, give it a spin as it should move freely. (see pic)
6) Assemble the Sun-Inner gear into the base planetary plate. And slide down to interface the installed planets. Again, it should be seated and move freely. Then using needle nose pliers add the next set of planets. Repeat this step until all the plates gear and such are in. (see pic)

#### Drive Assembly

1) Assemble stepper motor into Part02 and secure with screws. Then push the Sun\_Drive gear onto the drive shaft of the stepper motor.
2) Connect the Arduino, stepper driver, and stepper motor accordingly. (see wiring below) Then install into Part02. At this point test the electronic to see if it moves. I find it easiest to assemble the drive unit into the housing while it's moving, allows the gears to mesh easily. Should be seated about 1/3 of an inch below the end (see pics).
3) Install back cap and big over lock nut onto the body. The assembly is now complete.

#### Ball Head attachment

1) using a rod / screw drive / Allen key / some pokey thingy insert into the side hole of the mounting plate, then screw on the ball head and tighten. Keep in mind to not load the gear train. Optional: I would attach a second ball head onto the first ball head. This will give you maximum flexibility for setup. Trust me!

#### Polar Scope Assembly

1) Install and screw on the Polar Scope into the alignment port.
