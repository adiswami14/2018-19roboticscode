#include "robot-config.h"
vex::competition Comp;
int ticksForRotate = 1275;
int ticksPerTile = 688;
void moveDist(double ticks)
{

   
    LeftMotor.setVelocity(100, vex::velocityUnits::pct); 
    RightMotor.setVelocity(100, vex::velocityUnits::pct);
    LeftMotor2.setVelocity(100, vex::velocityUnits::pct); 
    RightMotor2.setVelocity(100, vex::velocityUnits::pct);
   
    //Rotate the Left and Right Motor for degreesToRotate. 
    LeftMotor.rotateFor(ticks, vex::rotationUnits::deg, false); //This command must be non blocking.
    RightMotor.rotateFor(ticks, vex::rotationUnits::deg);
    LeftMotor2.rotateFor(ticks, vex::rotationUnits::deg, false); //This command must be non blocking.
    RightMotor2.rotateFor(ticks, vex::rotationUnits::deg);
      LeftMotor.stop();
    RightMotor.stop();
    LeftMotor2.stop();
    RightMotor2.stop();  
  

  
}
void flipCap()
{
     IntakeMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    vex::task::sleep(750);
    IntakeMotor.stop();
}
void pickBall()
{
    IntakeMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    vex::task::sleep(2200);
    IntakeMotor.stop();
}
void shoot()
{
    Puncher.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    vex::task::sleep(1100);
    Puncher.stop();
}
void turn()  //negative degrees for left turns, positive degrees for right turns
{
    
      LeftMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    LeftMotor2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    RightMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    RightMotor2.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);  
 
    vex::task::sleep(530);
     LeftMotor.stop();
    LeftMotor2.stop();
    RightMotor.stop();
    RightMotor2.stop();
    
}
void turnOther()
{
    LeftMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    LeftMotor2.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    RightMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    RightMotor2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    vex::task::sleep(530);
     LeftMotor.stop();
    LeftMotor2.stop();
    RightMotor.stop();
    RightMotor2.stop();
}
void skillsAuton(void)
{
    moveDist(1.7*ticksPerTile);
    vex::task::sleep(100);
    moveDist(-0.7*ticksPerTile);
    vex::task::sleep(100);
    turnOther();
    vex::task::sleep(100);
    shoot();
    vex::task::sleep(100);
    moveDist(0.5*ticksPerTile);
    vex::task::sleep(100);
    turnOther();
    vex::task::sleep(100);
    turn();
    vex::task::sleep(100);
    moveDist(1*ticksPerTile);
    vex::task::sleep(100);
    moveDist(-4*ticksPerTile);
    vex::task::sleep(100);
    turn();
    vex::task::sleep(100);
    moveDist(1.7*ticksPerTile);
    vex::task::sleep(100);
    turn();
    vex::task::sleep(100);
    moveDist(0.5*ticksPerTile);
    vex::task::sleep(100);
}
void autonomous(void)
{
     moveDist(1.5*ticksPerTile);
    vex::task::sleep(100);
    moveDist(-0.8*ticksPerTile);
    vex::task::sleep(100);
}
void opControl(void)
{
    while(1) {
        
        RightMotor.spin(vex::directionType::fwd, (Controller.Axis2.value() - Controller.Axis1.value()), vex::velocityUnits::pct); //(Axis3+Axis4)/2
        LeftMotor.spin(vex::directionType::fwd, (Controller.Axis2.value() + Controller.Axis1.value()), vex::velocityUnits::pct);//(Axis3-Axis4)/2
        LeftMotor2.spin(vex::directionType::fwd, (Controller.Axis3.value() + Controller.Axis4.value()), vex::velocityUnits::pct);
        RightMotor2.spin(vex::directionType::fwd, (Controller.Axis3.value() - Controller.Axis4.value()), vex::velocityUnits::pct);
            ArmMotor.spin(vex::directionType::fwd, Controller2.Axis3.value(), vex::velocityUnits::pct);
     
        if(Controller.ButtonL1.pressing()) {
            IntakeMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        }
        else if(Controller.ButtonL2.pressing()) {
            IntakeMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        }
        else {
            IntakeMotor.stop(vex::brakeType::brake);
        }
        if(Controller2.ButtonR1.pressing()) {
            Puncher.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
            vex::task::sleep(800);
        }
        else Puncher.stop();
		vex::task::sleep(20);
    }
}

int main() {
    Comp.autonomous(autonomous);
    Comp.drivercontrol(opControl);
}
