#include "globals.hpp"

// shift right operation
void shift_right(bool* LFSRx, unsigned short int size, unsigned short int lfsr_no)
{ 
    //int tmp_last;
    //tmp_last = LFSRx[size-1];
    for(int i=(size-1); i>0; --i)
        LFSRx[i] = LFSRx[i-1];
    if (lfsr_no == 1)
        LFSRx[0] = XOR( XOR(LFSRx[TAP1_BIT_13], LFSRx[TAP1_BIT_16]),  XOR(LFSRx[TAP1_BIT_17], LFSRx[TAP1_BIT_18]));
    else if (lfsr_no == 2)
        LFSRx[0] = XOR(LFSRx[TAP2_BIT_20], LFSRx[TAP2_BIT_21]);
    else if (lfsr_no == 3)
        LFSRx[0] = XOR( XOR(LFSRx[TAP3_BIT_07], LFSRx[TAP3_BIT_20]),  XOR(LFSRx[TAP3_BIT_21], LFSRx[TAP3_BIT_22]));
        //LFSRx[0] = tmp_last;
}

void conditional_clock_signal(bool a, bool b, bool c, bool &clk_en_a, bool &clk_en_b, bool &clk_en_c)
{
    bool m = ((a&&b) | (a&&c) | (b&&c));
    
    clk_en_a = XNOR(a,m);
    clk_en_b = XNOR(b,m);
    clk_en_c = XNOR(c,m);
}

void generate_keystream(bool* LFSR1, bool* LFSR2, bool* LFSR3, bool* keystream, unsigned int key_size)
{
    for (int i=0; i<key_size; ++i)
    {
        shift_right(LFSR1, LFSR1_WIDTH, 1);
        shift_right(LFSR2, LFSR2_WIDTH, 2);
        shift_right(LFSR3, LFSR3_WIDTH, 3);
        keystream[i] = XOR(XOR(LFSR1[(LFSR1_WIDTH-1)], LFSR2[(LFSR2_WIDTH-1)]), LFSR3[(LFSR3_WIDTH-1)]);
    }
}

bool grab_outbit(bool* LFSRx, unsigned short int size)
{
    return LFSRx[(size-1)];
}