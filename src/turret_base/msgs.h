#ifndef MSGS_H
#define MSGS_H

#include <Arduino.h>

struct robotCmd {
  String f_vel_str;
  String a_vel_str;
  String r_shooter_str;
  String l_shooter_str;
  String feed_str;

  int f_vel;   // Forward velocity - between -100 and 100
  int a_vel;   // Angular veloctiy - between -100 and 100
  int r_shooter; // Right shooter velocity - between 0 and 100
  int l_shooter; // Left shooter velocity - between 0 and 100
  int feed;
};

#endif
