#include "driveBase.h"


DiffDriveBase::DiffDriveBase(){

}

void DiffDriveBase::setup(){
  shield.begin();
  feedServo.attach(10);
  feedServo.write(84); // Start off stopped
}

void DiffDriveBase::run(robotCmd *cmd){
  // Set limits on command inputs
  if (cmd->f_vel > 100) cmd->f_vel = 100;
  if (cmd->f_vel < -100) cmd->f_vel = -100;
  if (cmd->a_vel > 100) cmd->a_vel = 100;
  if (cmd->a_vel < -100) cmd->a_vel = 100;
  if (cmd->l_shooter > 100) cmd->l_shooter = 100;
  if (cmd->l_shooter < 0) cmd->l_shooter = 0;
  if (cmd->r_shooter > 100) cmd->r_shooter = 100;
  if (cmd->r_shooter < 0) cmd->r_shooter = 0;
  if (cmd->feed > 100) cmd->feed = 100;
  if (cmd->feed < -100) cmd->feed = -100;

  int forward = map(cmd->f_vel, -100, 100, -255, 255);
  int turn = map(cmd->a_vel, -100, 100, -255, 255);    // Left is positive, RH rule
  int l_shoot_speed = map(cmd->l_shooter, 0, 100, 0, 255);
  int r_shoot_speed = map(cmd->r_shooter, 0, 100, 0, 255);
  int feed = map(cmd->feed, -100, 100, 0, 168);

  int Rspeed = forward + turn; // Speed goes from 0 to 255
  int Lspeed = forward - turn;

  if (Rspeed < 0) {
    RMotor->setSpeed(-Rspeed);
    RMotor->run(BACKWARD);
  } else {
    RMotor->setSpeed(Rspeed);
    RMotor->run(FORWARD);
  }
  if (Lspeed < 0) {
    LMotor->setSpeed(-Lspeed);
    LMotor->run(BACKWARD);
  } else {
    LMotor->setSpeed(Lspeed);
    LMotor->run(FORWARD);
  }

  analogWrite(l_shooter_pin, l_shoot_speed); // Can go from 0 to 255
  analogWrite(r_shooter_pin, r_shoot_speed); // Can go from 0 to 255

  // LShooter->setSpeed(l_shoot_speed);
  // LShooter->run(BACKWARD); // Actually Forwards
  // RShooter->setSpeed(r_shoot_speed);
  // RShooter->run(FORWARD);

  feedServo.write(feed);
}
