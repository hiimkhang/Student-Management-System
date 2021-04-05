#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include "string.h"
using namespace std;

struct StudentInfo {
    int No, StudentID, SocialID;
    char *Firstname, *Lastname; 
    char Gender[6];
    string DoB;
};

// Function to input First name and Last name of student.
void inputName (char *name);
// Function to input student's information using handwork.
void inputInfo (StudentInfo &SI);
// Function to input student's information using CSV file.
void loadInfo (StudentInfo &SI, char *filename);
#endif