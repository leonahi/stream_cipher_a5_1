#include <iostream>

using namespace std;

//#define DEBUG

// XOR operation
#define XOR(x,y) (x ? !y : y)

// XNOR operation
#define XNOR(x,y) (x ? y : !y)

#ifndef DEBUG
#define LFSR1_WIDTH 19
#define LFSR2_WIDTH 22
#define LFSR3_WIDTH 23

#define KEY_WIDTH 64
#define FRAME_NO_WIDTH 22

// Clocking bits
#define CLK_BIT_1 8
#define CLK_BIT_2 10
#define CLK_BIT_3 10

// Tap bits LFSR1
#define TAP1_BIT_13 13
#define TAP1_BIT_16 16
#define TAP1_BIT_17 17
#define TAP1_BIT_18 18

// Tap bits LFSR2
#define TAP2_BIT_20 20
#define TAP2_BIT_21 21

// Tap bits LFSR3
#define TAP3_BIT_07 7
#define TAP3_BIT_20 20
#define TAP3_BIT_21 21
#define TAP3_BIT_22 22
#endif




#ifdef DEBUG
#define LFSR1_WIDTH 6
#define LFSR2_WIDTH 6
#define LFSR3_WIDTH 6

#define KEY_WIDTH 4
#define FRAME_NO_WIDTH 2

#define CLK_BIT_1 2
#define CLK_BIT_2 3
#define CLK_BIT_3 3

// Tap bits LFSR1
#define TAP1_BIT_13 13
#define TAP1_BIT_16 16
#define TAP1_BIT_17 17
#define TAP1_BIT_18 18

// Tap bits LFSR2
#define TAP2_BIT_20 20
#define TAP2_BIT_21 21

// Tap bits LFSR3
#define TAP3_BIT_07 7
#define TAP3_BIT_20 20
#define TAP3_BIT_21 21
#define TAP3_BIT_22 22
#endif




