#include "globals.hpp"

bool clk_en_a;
bool clk_en_b;
bool clk_en_c;

extern void shift_right(bool* LFSRx, unsigned short int size);
extern void conditional_clock_signal(bool a, bool b, bool c, bool &clk_en_a, bool &clk_en_b, bool &clk_en_c);

int main(int argc, char* argv[])
{
    bool LFSR1[LFSR1_WIDTH]={false}, LFSR2[LFSR2_WIDTH]={false}, LFSR3[LFSR3_WIDTH]={false};
    bool key[64] = {false}, frame_no[22] = {false};    
    
    // Initialize LFSRs to zero
    for(int i=0; i<LFSR1_WIDTH; ++i)
        LFSR1[i] = 0;
    for(int i=0; i<LFSR2_WIDTH; ++i)
        LFSR2[i] = 0;
    for(int i=0; i<LFSR3_WIDTH; ++i)
        LFSR3[i] = 0;
   
#ifdef DEBUG
    // Test code for conditional clocking signal
    LFSR1[CLK_BIT_1] = 0;
    LFSR2[CLK_BIT_2] = 0; 
    LFSR3[CLK_BIT_3] = 1;
    conditional_clock_signal(LFSR1[CLK_BIT_1], LFSR2[CLK_BIT_2], LFSR3[CLK_BIT_3], clk_en_a, clk_en_b, clk_en_c);
    cout << "a - " << LFSR1[CLK_BIT_1] << endl << "b - " << LFSR2[CLK_BIT_2] << endl << "c - " << LFSR3[CLK_BIT_3] << endl;
    cout << "m = "<< ((LFSR1[CLK_BIT_1]&&LFSR2[CLK_BIT_2]) | (LFSR1[CLK_BIT_1]&&LFSR3[CLK_BIT_3]) | (LFSR2[CLK_BIT_2]&&LFSR3[CLK_BIT_3])) << endl;
    cout << "clk_en_a - " << clk_en_a << endl << "clk_en_b - " << clk_en_b << endl << "clk_en_c - " << clk_en_c << endl;
#endif
    
    //for (int i=0; i<22; ++i)
    //    LFSR2[i] = true;
    /*    
    for (int i=0; i<19; ++i)
    {
        cout << XOR(LFSR1[i], LFSR2[i]);
        cout << endl;
    }
    */
    return 0;
}