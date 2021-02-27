#ifndef DEFINES_H
#define DEFINES_H



//DEFS
#define Nh 40 //1024
#define Ns 40//1024 (400)
#define Nc 1  //1024


#define K 6
#define MAX_TIME 200000
#define T 0.8

#define FILE_NAME_FIELD "SITE02RSB.txt"
#define FILE_NAME_SITE  "QSITE_QSTATE.txt"

#define WORKTAG 1
#define DIETAG  -1
//INCS

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <vector>

#include "bethepop.h"
#include "quicksort.h"


//TYPEDEF
using namespace std;

typedef class myCluster MPI_CLUSTER;
#endif // DEFINES_H
