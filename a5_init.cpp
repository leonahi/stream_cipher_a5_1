#include "globals.hpp"

extern void shift_right(bool* LFSRx, unsigned short int size, unsigned short int lfsr_no);

void a5_init(bool* key, bool* frame_no, bool* LFSR1, bool* LFSR2, bool* LFSR3)
{
    for(int i=0; i<KEY_WIDTH; ++i)
    {
        LFSR1[0] = XOR(LFSR1[0], key[i]);
        LFSR2[0] = XOR(LFSR2[0], key[i]);
        LFSR3[0] = XOR(LFSR3[0], key[i]);
        shift_right(LFSR1, LFSR1_WIDTH, 1);
        shift_right(LFSR2, LFSR2_WIDTH, 2);
        shift_right(LFSR3, LFSR3_WIDTH, 3);
    }

    for(int i=0; i<FRAME_NO_WIDTH; ++i)
    {
        LFSR1[0] = XOR(LFSR1[0], frame_no[i]);
        LFSR2[0] = XOR(LFSR2[0], frame_no[i]);
        LFSR3[0] = XOR(LFSR3[0], frame_no[i]);
        shift_right(LFSR1, LFSR1_WIDTH, 1);
        shift_right(LFSR2, LFSR2_WIDTH, 2);
        shift_right(LFSR3, LFSR3_WIDTH, 3);
    }
    /*
    for(int i=0; i<6; ++i)
        cout << LFSR1[i] << " , ";
    cout << endl;
    for(int i=0; i<6; ++i)
        cout << LFSR2[i] << " , ";
    cout << endl;
    for(int i=0; i<6; ++i)
        cout << LFSR3[i] << " , ";
    cout << endl << endl;
    */
    
    for(int i=0; i<100; ++i)
    {
        shift_right(LFSR1, LFSR1_WIDTH, 1);
        shift_right(LFSR2, LFSR2_WIDTH, 2);
        shift_right(LFSR3, LFSR3_WIDTH, 2);
    }
   
}