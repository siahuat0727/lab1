/*
 * File:   newmain.c
 * Author: User
 *
 * Created on 2017?11?2?, ?? 3:41
 */
#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF

#include <xc.h>

int add(int a, int b);

void main(void) {
    int sum=add(0x1234,0x1234);
    return;
}

