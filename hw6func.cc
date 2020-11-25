/*
# Filename hw6func.cc
# Date November 25th, 2020
# Author Josh Mathiak
# Josh.Mathiak@UTDallas.edu
# Course CS 3377.001 Fall 2020
# Version 1.0 (or correct version)
# Copyright 2020, All Rights Reserved
#
# Description
#
# Contains the function endProg which waits for the user to press a key and then ends cdk.
# 
#
*/
#include <iostream>
#include "cdk.h"
using namespace std;
void endProg()
{
  getchar();
  endCDK();
}
