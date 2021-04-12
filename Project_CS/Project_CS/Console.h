#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

// Function to set the size of the console
void setConsoleWindow(int w, int h);

// Function to lock the size of the console
void fixConsoleWindow();

// Function to coloring text
void textColor(int x);

// Function to move cursor 
void gotoXY(int x, int y);

#endif