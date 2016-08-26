#include "globals.hpp"

extern void shift_right(bool* LFSRx, unsigned short int size);


void a5_init(bool* key, bool* frame_no, bool* LFSR1, bool* LFSR2, bool* LFSR3)
{
    for(int i=0; i<64; ++i)
    {
        LFSR1[0] = XOR(LFSR1[0], key[i]);
        LFSR2[0] = XOR(LFSR2[0], key[i]);
        LFSR3[0] = XOR(LFSR3[0], key[i]);
        shift_right(LFSR1, LFSR1_WIDTH);
        shift_right(LFSR2, LFSR2_WIDTH);
        shift_right(LFSR3, LFSR3_WIDTH);
    }
    for(int i=0; i<22; ++i)
    {
        LFSR1[0] = XOR(LFSR1, frame_no[i]);
        LFSR2[0] = XOR(LFSR2, frame_no[i]);
        LFSR3[0] = XOR(LFSR3, frame_no[i]);
        shift_right(LFSR1, LFSR1_WIDTH);
        shift_right(LFSR2, LFSR2_WIDTH);
        shift_right(LFSR3, LFSR3_WIDTH);
    }
}