#include <IRremote.h>
#include <Servo.h>
#include <Stepper.h>

#define servoArmPin 2
#define servoLegPin 3


Servo servoArm;
Servo servoLeg;

int posArm = 0;
int posLeg = 0;

const int stepsPerRevolution = 100;
Stepper StepperLeg(stepsPerRevolution, 8, 9, 10, 11);
Stepper StepperArm(stepsPerRevolution, 4, 5, 6, 7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(12);
  // pinMode(7, OUTPUT);


  servoArm.attach(servoArmPin);
  servoLeg.attach(servoLegPin);

  // set the stepper motor speed (rpm)
  StepperLeg.setSpeed(250);
  StepperArm.setSpeed(250);
  // pinMode(irLeg, INPUT);
  // pinMode(irArm, INPUT);
}

void loop() {
  
  if (IrReceiver.decode()) {
    IrReceiver.resume();

    Serial.println(IrReceiver.decodedIRData.command);
  }
  //////////////////////////////////////////////////////////////////////////arm
  if (IrReceiver.decodedIRData.command == 88) {
    //   togle++;
    // if(togle==1)
    StepperArm.step(stepsPerRevolution);
    // digitalWriteFast(7, HIGH);
  }

  else if (IrReceiver.decodedIRData.command == 89) {
    StepperArm.step(-stepsPerRevolution);
  }

  /////////////////////////////////////////////////////////////////////////////// leg

  else if (IrReceiver.decodedIRData.command == 95) {
    StepperLeg.step(stepsPerRevolution);
  } else if (IrReceiver.decodedIRData.command == 84) {
    StepperLeg.step(-stepsPerRevolution);
  }




  //////////////////////////////////////////////////////////////////////////// servo leg
  else if (IrReceiver.decodedIRData.command == 91 || IrReceiver.decodedIRData.command == 70 || IrReceiver.decodedIRData.command == 23 || IrReceiver.decodedIRData.command == 71) {
    switch (IrReceiver.decodedIRData.command) {
      case 91:
        servoLeg.write(55);
        // for (posArm = 50; posArm <= 200; posArm += 1) {
        //   //Serial.println("Detect");
        //   servoArm.write(posArm);
        //   delay(15);

          break;
          case 70:
            servoLeg.write(200);
            // for (posArm = 200; posArm <= 50; posArm -= 1) {
            //   servoArm.write(posArm);
            //   delay(15);
            // }
        }
    }

// }
    else {
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(2, LOW);
    }


    delay(10);
  }
