#include "globals.hpp"

extern void shift_right(bool* LFSRx, unsigned short int size, unsigned short int lfsr_no);
extern void conditional_clock_signal(bool a, bool b, bool c, bool &clk_en_a, bool &clk_en_b, bool &clk_en_c);
extern void a5_init(bool* key, bool* frame_no, bool* LFSR1, bool* LFSR2, bool* LFSR3);
extern bool grab_outbit(bool* LFSRx, unsigned short int size);
extern void generate_keystream(bool* LFSR1, bool* LFSR2, bool* LFSR3, bool* keystream, unsigned int key_size);

int main(int argc, char* argv[])
{
#ifndef DEBUG
    clock_t start, end;
    char file_char;
    unsigned long int plain_text_bits_length=0;
    bool* plain_text_bits;
    bool* cipher_text_bits;
    
    bool LFSR1[LFSR1_WIDTH]={false}, LFSR2[LFSR2_WIDTH]={false}, LFSR3[LFSR3_WIDTH]={false};
    bool clk_en_a;
    bool clk_en_b;
    bool clk_en_c;
    bool k_i=0;
    bool key[64] = {1,0,1,0,1,0,1,1,  0,1,0,1,0,1,1,0,  1,0,1,0,1,1,0,1,  0,1,0,1,1,0,1,0,
                    1,0,1,1,0,1,0,1,  0,1,1,0,1,0,1,0,  1,1,0,1,0,1,0,1,  1,0,1,0,1,0,1,0};
                
    bool frame_no[22] = {1,0,1,0,1,0,1,0,  1,0,1,0,1,0,1,0,  1,0,1,0,1,0};
    
    
    bool plain_text[88] = {0,1,1,0,1,1,1,0, 0,1,1,0,0,0,0,1, 0,1,1,0,1,0,0,0, 0,1,1,0,1,0,0,1, 
                           0,1,1,1,0,1,0,0, 0,0,1,0,0,0,0,0, 0,1,1,1,0,0,0,0, 0,1,1,0,0,0,0,1, 
                           0,1,1,1,0,1,1,1, 0,1,1,0,0,0,0,1 ,0,1,1,1,0,0,1,0 };
                           
    bool cipher_text[88] = {false};
    
    /*
     * 
     * Read plain text from binary file - argv[1]
     * 
     */
    if(argc != 2)
    {
        cout<<"Error: Input file not found"<<endl;
        exit(1);
    }
    ifstream file(argv[1]);
    if(!file.is_open())
    {
        cout << endl << "-----------------------------------------------------------------------" << endl;
        cout << "Error: Unable to open file" << argv[1] << endl;
        cout << endl << "-----------------------------------------------------------------------" << endl;
        exit(1);
    }
    
    while(!file.eof())
    {
        file.get(file_char);
        if(file_char == '\n') continue;
        else if(file_char == '\r') continue;
        else if(file_char == ' ') continue;
        ++plain_text_bits_length;
    }
    file.close();
    cout << endl << "Number of bits in plaintext file : " << plain_text_bits_length << endl;
    plain_text_bits = new bool [plain_text_bits_length];
    cipher_text_bits = new bool [plain_text_bits_length];
    
    file.open(argv[1]);
    if(!file.is_open())
    {
        cout << endl << "-----------------------------------------------------------------------" << endl;
        cout << "Error: Unable to open file" << argv[1] << endl;
        cout << endl << "-----------------------------------------------------------------------" << endl;
        exit(1);
    }
    
    unsigned int i_plain_text=0;
    while(!file.eof())
    {
        file.get(file_char);
        if(file_char == '\n') continue;
        else if(file_char == '\r') continue;
        else if(file_char == ' ') continue;
        else if(file_char == '0')
        {
            plain_text_bits[i_plain_text] = 0;
            ++i_plain_text;
            continue;
        }
        else if(file_char == '1')
        {
            plain_text_bits[i_plain_text] = 1;
            ++i_plain_text;
            continue;
        }
    }
    /*
    cout << endl;
    for(int i=0; i<plain_text_bits_length; ++i)
    {
        cout << plain_text_bits[i];
    }
    cout << endl;
    */
    file.close();
#endif    
      

// Debug code for testing purpose    
#ifdef DEBUG
    // test variables
    bool key_test[4] = {1, 0, 1, 1};
    bool frame_no_test[2] = {0, 1};
    bool keystream[10]={false};
    bool lfsr1_test[6] = {0,0,0,0,0,0};
    bool lfsr2_test[6] = {0,0,0,0,0,0};
    bool lfsr3_test[6] = {0,0,0,0,0,0};
    bool plain_text[88] = {0,1,1,0,1,1,1,0, 0,1,1,0,0,0,0,1, 0,1,1,0,1,0,0,0, 0,1,1,0,1,0,0,1, 
                           0,1,1,1,0,1,0,0, 0,0,1,0,0,0,0,0, 0,1,1,1,0,0,0,0, 0,1,1,0,0,0,0,1, 
                           0,1,1,1,0,1,1,1, 0,1,1,0,0,0,0,1, 0,1,1,1,0,0,1,0 };
                           
    a5_init(key_test, frame_no_test, lfsr1_test, lfsr2_test, lfsr3_test);
    generate_keystream(lfsr1_test, lfsr2_test, lfsr3_test, keystream, 10);
    for(int i=0; i<10; ++i)
        cout << keystream[i] << " , ";
#endif

#ifndef DEBUG    
    // Initialize LFSRs to zero
    for(int i=0; i<LFSR1_WIDTH; ++i)
        LFSR1[i] = 0;
    for(int i=0; i<LFSR2_WIDTH; ++i)
        LFSR2[i] = 0;
    for(int i=0; i<LFSR3_WIDTH; ++i)
        LFSR3[i] = 0;
    
    a5_init(key, frame_no, LFSR1, LFSR2, LFSR3);
    
    // Encryption
    cout << endl;
    cout << "Starting Encryption..." << endl;
    start = clock();
    for (int i=0; i<plain_text_bits_length; ++i)
    {
        conditional_clock_signal(LFSR1[CLK_BIT_1], LFSR2[CLK_BIT_2], LFSR3[CLK_BIT_3], clk_en_a, clk_en_b, clk_en_c);
        if (clk_en_a == 1)
            shift_right(LFSR1, LFSR1_WIDTH, 1);
        if (clk_en_b == 1)
            shift_right(LFSR2, LFSR2_WIDTH, 2);
        if (clk_en_c == 1)
            shift_right(LFSR3, LFSR3_WIDTH, 3);
        k_i = XOR( XOR(LFSR1[LFSR1_WIDTH-1],LFSR2[LFSR2_WIDTH-1]) , LFSR3[LFSR3_WIDTH-1]);
        cipher_text_bits[i] = XOR(k_i, plain_text_bits[i]);
    }
    end = clock();
    cout << "Encryption Done!" << endl;
    cout << "Total time for encryption : " << (double)(end-start)/CLOCKS_PER_SEC << " seconds" <<endl;
    cout << "Speed in Gbps : " << (double)(((double)((double)(end-start)/(CLOCKS_PER_SEC))/plain_text_bits_length))*1000000000 << endl;
    /*
    cout << endl;
    for(int i=0; i<plain_text_bits_length; ++i)
        cout << cipher_text_bits[i];
    cout << endl;
    */
    
    // Initialize LFSR to zeros
    for(int i=0; i<LFSR1_WIDTH; ++i)
        LFSR1[i] = 0;
    for(int i=0; i<LFSR2_WIDTH; ++i)
        LFSR2[i] = 0;
    for(int i=0; i<LFSR3_WIDTH; ++i)
        LFSR3[i] = 0;
    
    // Initialize LFSR w.r.t to key and frame number
    a5_init(key, frame_no, LFSR1, LFSR2, LFSR3);
    
    // Decryption
    cout << endl;
    cout << "Starting Decryption..." << endl;
    for (int i=0; i<plain_text_bits_length; ++i)
    {
        conditional_clock_signal(LFSR1[CLK_BIT_1], LFSR2[CLK_BIT_2], LFSR3[CLK_BIT_3], clk_en_a, clk_en_b, clk_en_c);
        if (clk_en_a == 1)
            shift_right(LFSR1, LFSR1_WIDTH, 1);
        if (clk_en_b == 1)
            shift_right(LFSR2, LFSR2_WIDTH, 2);
        if (clk_en_c == 1)
            shift_right(LFSR3, LFSR3_WIDTH, 3);
        k_i = XOR( XOR(LFSR1[LFSR1_WIDTH-1],LFSR2[LFSR2_WIDTH-1]) , LFSR3[LFSR3_WIDTH-1]);
        cipher_text_bits[i] = XOR(k_i, cipher_text_bits[i]);
    }
    cout << "Decryption Done!" << endl;
    /*
    cout << endl;
    for(int i=0; i<plain_text_bits_length; ++i)
        cout << cipher_text_bits[i];
    cout << endl;
    */
    
    delete plain_text_bits;
    delete cipher_text_bits;
#endif


   
#ifdef DEBUG
    // Test code for conditional clocking signal
    cout << endl << "Testing conditional clocking..." << endl;
    LFSR1[CLK_BIT_1] = 0;
    LFSR2[CLK_BIT_2] = 0; 
    LFSR3[CLK_BIT_3] = 1;
    conditional_clock_signal(LFSR1[CLK_BIT_1], LFSR2[CLK_BIT_2], LFSR3[CLK_BIT_3], clk_en_a, clk_en_b, clk_en_c);
    cout << "a - " << LFSR1[CLK_BIT_1] << endl << "b - " << LFSR2[CLK_BIT_2] << endl << "c - " << LFSR3[CLK_BIT_3] << endl;
    cout << "m = "<< ((LFSR1[CLK_BIT_1]&&LFSR2[CLK_BIT_2]) | (LFSR1[CLK_BIT_1]&&LFSR3[CLK_BIT_3]) | (LFSR2[CLK_BIT_2]&&LFSR3[CLK_BIT_3])) << endl;
    cout << "clk_en_a - " << clk_en_a << endl << "clk_en_b - " << clk_en_b << endl << "clk_en_c - " << clk_en_c << endl;
    cout << "Done..." << endl << endl;
#endif
 
    return 0;
}