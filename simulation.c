#include <stdio.h>

#include "base.h"

u8 event = 0;
u8 errflg = 0;

#define P1_BTN_MASK 0x03
#define P3_BTN_MASK 0x0F
#define BTN_INVERTER 0x3F

//          BTN   21
u8 P1IN = 0b11111111;
//          BTN 6543
u8 P3IN = 0b11111111;

u8 SLATCH;
u8 V0;
u8 V1;
u8 V2;
u8 btn_sample;

void isr(void)
{
    btn_sample = ((P1IN BAND P1_BTN_MASK) | ((P3IN BAND P3_BTN_MASK) << 2)) XOR BTN_INVERTER;
    // maybe we can use the state to xor the input to switch between press and release

    u8 VMASK = btn_sample ^ SLATCH;
    V0 &= VMASK;
    V1 &= VMASK;
    V2 &= VMASK;

    // ports that have counted to the max
    u8 VTEMP = VMASK & V0 & V1 & V2;
    SLATCH ^= VTEMP;

    VTEMP &= btn_sample;
    if (VTEMP)
    {
        errflg |= event BAND VTEMP;
        event ^= VTEMP;
    }

    V2 ^= VMASK & V1 & V0;
    V1 ^= VMASK & V0;
    V0 ^= VMASK;
}

void simulate(int c)
{
    for (int i = 0; i < c; i++)
    {
        isr();
        printf("|" BYTE_TO_BINARY_PATTERN
               "|" BYTE_TO_BINARY_PATTERN
               "|" BYTE_TO_BINARY_PATTERN
               "|" BYTE_TO_BINARY_PATTERN
               "|" BYTE_TO_BINARY_PATTERN
               "|" BYTE_TO_BINARY_PATTERN
               "|" BYTE_TO_BINARY_PATTERN
               "|"
               "\n",
               BYTE_TO_BINARY(btn_sample),
               BYTE_TO_BINARY(V0),
               BYTE_TO_BINARY(V1),
               BYTE_TO_BINARY(V2),
               BYTE_TO_BINARY(SLATCH),
               BYTE_TO_BINARY(event),
               BYTE_TO_BINARY(errflg));
    }
}

int main()
{
    printf("| BTN    | V0     | V1     | V2     | SLATCH | event  | errflg |\n");

    // press BTN1
    P1IN = 0b11111110;
    simulate(10);

    // clear BTN1 event
    event = 0;

    // release BTN1 for a single tick
    P1IN = 0b11111111;
    simulate(1);
    P1IN = 0b11111110;

    // press BTN5
    P3IN = 0b00001011;
    simulate(8);

    // release BTN5
    P3IN = 0x0F;
    simulate(9);
}
