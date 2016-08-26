#include "globals.hpp"

// shift right operation
void shift_right(bool* LFSRx, unsigned short int size)
{
    int tmp_last;
    tmp_last = LFSRx[size-1];
    for(int i=(size-1); i>0; --i)
        LFSRx[i] = LFSRx[i-1];   
    LFSRx[0] = tmp_last;
}

void conditional_clock_signal(bool a, bool b, bool c, bool &clk_en_a, bool &clk_en_b, bool &clk_en_c)
{
    bool m;
    m = ((a&&b) | (a&&c) | (b&&c));
    
    clk_en_a = XNOR(a,m);
    clk_en_b = XNOR(b,m);
    clk_en_c = XNOR(c,m);
}