#ifndef DEFINES_H
#define DEFINES_H


//TYPEDEF
using namespace std;

//DEFS
#define Nh 70 //1024
#define Ns 70 //1024 (400)
#define Nc 70 //1024

#define K 6

#define NUM_CYCLES 50
#define BIAS 4

#define MAX_TIME (NUM_CYCLES+BIAS)*Nh
#define T 0.8

#define FILE_NAME_XY    "FVSXY2RSB.txt"
#define FILE_NAME_Q    "Q0Q1Q2.txt"
//INCS 

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <vector>

#include "mySystem.h"

#include "functions.h"


#endif // DEFINES_H
