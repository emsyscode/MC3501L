/****************************************************/
/* This is only one example of code structure       */
/* OFFCOURSE this code can be optimized, but        */
/* the idea is let it so simple to be easy catch    */
/* where we can do changes and look to the results  */
/* Keep in mind the code is not clean!              */
/****************************************************/
//set your clock speed
//#define F_CPU 16000000UL
//these are the include files. They are outside the project folder
//#include <avr/io.h>
//#include <iom1284p.h>
//#include <util/delay.h>
//#include <avr/interrupt.h>

#include <Wire.h>

#define VFD_data 7// If 0 write LCD, if 1 read of LCD
#define VFD_clk 8 // if 0 is a command, if 1 is a data0
#define VFD_ce 9 // Must be pulsed to LCD fetch data of bus
#define VFD_LED 10 //Only to controle LED 301

/*Global Variables Declarations*/
unsigned char grid;
/*
unsigned int segMC3501L[] ={
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//bar in middle(center)
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//bar
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//bar
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//left grid
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//DSP 1
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//DSP 2
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//DSP 3
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//DSP 4
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//DSP 5
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//DSP 6
            (0b00000000), (0b00100000), (0b00000000), // The third byte is only half byte of third byte.//DSP 7  // this have the point active in front of display 7
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//DSP 8
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//dsp small
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.//right grid
            (0b00000000), (0b00000000), (0b00000000), // The third byte is only half byte of third byte.
            (0b00000000), (0b00000000), (0b00000000)  // The third byte is only half byte of third byte.
};
*/
//    Numbers design        87654321     87654321     87654321
unsigned char number0[]={(0b00100011),(0b00110001),(0b00000000)}; // 0
unsigned char number1[]={(0b00100000),(0b00010000),(0b00000000)}; // 1
unsigned char number2[]={(0b11100001),(0b00100001),(0b00000000)}; // 2
unsigned char number3[]={(0b11100001),(0b00110000),(0b00000000)}; // 3
unsigned char number4[]={(0b11100010),(0b00010000),(0b00000000)}; // 4
unsigned char number5[]={(0b11000011),(0b00110000),(0b00000000)}; // 5
unsigned char number6[]={(0b11000011),(0b00110001),(0b00000000)}; // 6
unsigned char number7[]={(0b00100001),(0b00010000),(0b00000000)}; // 7
unsigned char number8[]={(0b11100011),(0b00110001),(0b00000000)}; // 8
unsigned char number9[]={(0b11100011),(0b00110000),(0b00000000)}; // 9

//    Letters desing        87654321     87654321
unsigned char letterA[]={(0b11100011),(0b00010001),(0b00000000)}; // A
unsigned char letterB[]={(0b10101001),(0b00110100),(0b00000000)}; // B
unsigned char letterC[]={(0b00000011),(0b00100001),(0b00000000)}; // C
unsigned char letterD[]={(0b00101001),(0b00110100),(0b00000000)}; // D
unsigned char letterE[]={(0b11000011),(0b00100001),(0b00000000)}; // E
unsigned char letterF[]={(0b11000011),(0b00000001),(0b00000000)}; // F
unsigned char letterG[]={(0b10000011),(0b00110001),(0b00000000)}; // G
unsigned char letterH[]={(0b11100010),(0b00010001),(0b00000000)}; // H
unsigned char letterI[]={(0b00001001),(0b00100100),(0b00000000)}; // I
unsigned char letterJ[]={(0b00100000),(0b00110001),(0b00000000)}; // J
unsigned char letterK[]={(0b01010010),(0b00001001),(0b00000000)}; // k
unsigned char letterL[]={(0b00000010),(0b00100001),(0b00000000)}; // L
unsigned char letterM[]={(0b00110110),(0b00010001),(0b00000000)}; // M
unsigned char letterN[]={(0b00100110),(0b00011001),(0b00000000)}; // N
unsigned char letterO[]={(0b00100011),(0b00110001),(0b00000000)}; // O
unsigned char letterP[]={(0b11100011),(0b00000001),(0b00000000)}; // P
unsigned char letterQ[]={(0b00100011),(0b00111001),(0b00000000)}; // Q
unsigned char letterR[]={(0b11100011),(0b00001001),(0b00000000)}; // R
unsigned char letterS[]={(0b10000101),(0b00110000),(0b00000000)}; // S
unsigned char letterT[]={(0b00001001),(0b00000100),(0b00000000)}; // T
unsigned char letterU[]={(0b00100010),(0b00110001),(0b00000000)}; // U
unsigned char letterV[]={(0b00010010),(0b00000011),(0b00000000)}; // V
unsigned char letterX[]={(0b00010100),(0b00001010),(0b00000000)}; // X
unsigned char letterY[]={(0b00010100),(0b00000100),(0b00000000)}; // Y
unsigned char letterZ[]={(0b00010001),(0b00100010),(0b00000000)}; // Z
unsigned char letterW[]={(0b00100010),(0b00011010),(0b00000000)}; // W
unsigned char letterSpace[]={(0b0000000),(0b00000000),(0b00000000)}; // Space
//
unsigned char segFind[]={(0b11111111),(0b11111111),(0b11111111)}; // Only to test

unsigned int segments[] ={ // Draw numbers to the display of 7 segments
  //This not respect the normal table for 7segm like "abcdefgh"  // 
      0b01110111, //0  // 
      0b00010010, //1  // 
      0b01101011, //2  // 
      0b01011011, //3  // 
      0b00011110, //4  // 
      0b01011101, //5  // 
      0b01111101, //6  // 
      0b00010011, //7  // 
      0b01111111, //8  // 
      0b00011111, //9  // 
      0b00000000, //10 // empty display
  };
/*****************************************************************/
void MC3501L_init(void){
  delayMicroseconds(200); //power_up delay
  // Note: Allways the first byte in the input data after the STB go to LOW is interpret as command!!!

  // Configure VFD display (grids)
  cmd_with_stb(0b00001001);//     cmd1 10 Grids and 24 segments! 
  delayMicroseconds(1);
  cmd_with_stb((0b10001000) | 7); // IMPORTANT:  After define the size GRIDs is necessary do a cmd "ON" display.
  delayMicroseconds(1);
  // turn vfd on, stop key scannig
   cmd_with_stb(0b10001000);//(BIN(01100110)); 
  delayMicroseconds(1);
  // Write to memory display, increment address, normal operation
  cmd_with_stb(0b01000000);//(BIN(01000000));
  delayMicroseconds(1);
  // Address 00H - 15H ( total of 11*2Bytes=176 Bits)
  cmd_with_stb(0b11000000);//(BIN(01100110)); 
  delayMicroseconds(1);
  // set DIMM/PWM to value
  cmd_with_stb((0b10001000) | 7);//0 min - 7 max  )(0b01010000)
  delayMicroseconds(1);
}
/*****************************************************************/
void send_char(unsigned char grid, unsigned char byte0, unsigned char byte1,unsigned char byte2){
 
        cmd_with_stb(0b00001001); //       cmd 1 // 10 Grids & 24 Segments
        delayMicroseconds(2);
        cmd_with_stb((0b10001000) | 7); // IMPORTANT:  After define the size GRIDs is necessary do a cmd "ON" display.
        delayMicroseconds(2);
        cmd_with_stb(0b01000000); //       cmd 2 //Normal operation; Auto increment
        digitalWrite(VFD_ce, LOW);
        delayMicroseconds(2);
            cmd_without_stb((0b11000000) | grid); // cmd 3 //wich define the start address (00H to 15H)
            cmd_without_stb(byte0); // Data to fill table of 5 grids * 16 segm = 80 bits on the table
            cmd_without_stb(byte1); // Data to fill table of 5 grids * 16 segm = 80 bits on the table
            cmd_without_stb(byte2); // only half byte of third byte.
            //
            digitalWrite(VFD_ce, HIGH);
            delayMicroseconds(2);
             /*
            Serial.println("******************");  // only to debug on the console print
            Serial.println(((0b11000000) | grid), BIN);
            Serial.println("------------------");
            Serial.println(grid, BIN);//
            Serial.println(byte0, BIN);//
            Serial.println(byte1, BIN);//
            Serial.println(byte2, BIN);
            Serial.println("++++++++++++++++++");
            */
            delay(200); //To write slowly, char by char at VFD
}
/*****************************************************************/
void cmd_without_stb(unsigned char a){
  // send without stb
  unsigned char transmit = 7; //define our transmit pin
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  
  data=a;
  //This don't send the strobe signal, to be used in burst data send
   for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
     digitalWrite(VFD_clk, LOW);
     if (data & mask){ // if bitwise AND resolves to true
        digitalWrite(VFD_data, HIGH);
     }
     else{ //if bitwise and resolves to false
       digitalWrite(VFD_data, LOW);
     }
    delayMicroseconds(5);
    digitalWrite(VFD_clk, HIGH);
    delayMicroseconds(5);
   }
   //digitalWrite(VFD_clk, LOW);
}
/****************************************************************/
void cmd_with_stb(unsigned char a){
  // send with stb
  unsigned char transmit = 7; //define our transmit pin
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  
  data=a;
  
  //This send the strobe signal
  //Note: The first byte input at in after the STB go LOW is interpreted as a command!!!
  digitalWrite(VFD_ce, LOW);
  delayMicroseconds(1);
   for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
     digitalWrite(VFD_clk, LOW);
     delayMicroseconds(1);
     if (data & mask){ // if bitwise AND resolves to true
        digitalWrite(VFD_data, HIGH);
     }
     else{ //if bitwise and resolves to false
       digitalWrite(VFD_data, LOW);
     }
    digitalWrite(VFD_clk, HIGH);
    delayMicroseconds(1);
   }
   digitalWrite(VFD_ce, HIGH);
   delayMicroseconds(1);
}
/****************************************************************/
void test_VFD(void){
  clear_VFD();
      
      digitalWrite(VFD_ce, LOW);
      delayMicroseconds(1);
      cmd_with_stb(0b00001001); // cmd 1 // 10 Grids & 24 Segments
      cmd_with_stb((0b10001000) | 7); // IMPORTANT:  After define the size GRIDs is necessary do a cmd "ON" display.
      cmd_with_stb(0b01000000); // cmd 2 //Write VFD, Normal operation; Set pulse as 1/16, Auto increment
      cmd_with_stb(0b10001000 | 0x07); // cmd 2 //set on, dimmer to max
        digitalWrite(VFD_ce, LOW);
        delayMicroseconds(1);
        cmd_without_stb((0b11000000)); //cmd 3 wich define the start address (00H to 15H)
        // Only here must change the bit to test, first 2 bytes and 1/2 byte of third.
         for (int i = 0; i < 10 ; i++){ // test base to 10 grids and 24 segm
          // Zone of test, if write 1 on any position of 3 bytes below position, will bright segment corresponding it.
         cmd_without_stb(0b00000000); // Data to fill table 5*16 = 80 bits
         cmd_without_stb(0b00000000); // Data to fill table 5*16 = 80 bits
         cmd_without_stb(0b00000000); // Data to fill table 5*16 = 80 bits
         }
    
      //cmd_without_stb(0b00000001); // cmd1 Here I define the 5 grids and 16 Segments
      //cmd_with_stb((0b10001000) | 7); //cmd 4
      digitalWrite(VFD_ce, HIGH);
      delay(1);
      delay(3000);  
}
/****************************************************************/
void swapLed1(){
  byte myByte;
    digitalWrite(VFD_ce, LOW);
    delayMicroseconds(20);
    cmd_without_stb(0b01000001);
    delayMicroseconds(20);
    myByte ^=(0b00000001);  // Here is only to invert bit of led 1.
    cmd_without_stb(myByte);
    delayMicroseconds(20);
    digitalWrite(VFD_ce, HIGH);
    delayMicroseconds(20);
}
/****************************************************************/

/****************************************************************/
void clear_VFD(void){
  int sum=0;
  /*
  Here I clean all registers 
  Could be done only on the number of grid
  to be more fast. The 12 * 3 bytes = 36 registers
  */
      for (int n=0; n < 16; n++){  //
        cmd_with_stb(0b00001001); //       cmd 1 // 10 Grids & 24 Segments
        delayMicroseconds(1);
        cmd_with_stb((0b10001000) | 7); // IMPORTANT:  After define the size GRIDs is necessary do a cmd "ON" display.
        delayMicroseconds(1);
        cmd_with_stb(0b01000000); //       cmd 2 //Normal operation; Set pulse as 1/16
        digitalWrite(VFD_ce, LOW);
        delayMicroseconds(1);
            cmd_without_stb((0b11000000) | sum); // cmd 3 //wich define the start address (00H to 15H)
            cmd_without_stb(0b00000000); // Data to fill table of 5 grids * 16 segm = 80 bits on the table
            cmd_without_stb(0b00000000); // Data to fill table of 5 grids * 16 segm = 80 bits on the table
            cmd_without_stb(0b00000000); // only half byte of third byte.
            //
            digitalWrite(VFD_ce, HIGH);
            delayMicroseconds(2);
            sum=(sum +3);
     }
}
/****************************************************************/
void seg(void){
  int sum=0;
  /*
  Here I test all registers 
  Could be done only on the number of grid
  to be more fast. The 12 * 3 bytes = 36 registers
  */
      for (int n=0; n < 16; n++){  //
        cmd_with_stb(0b00001001); //       cmd 1 // 14 Grids & 14 Segments
        delayMicroseconds(1);
        cmd_with_stb((0b10001000) | 7); // IMPORTANT:  After define the size GRIDs is necessary execute a cmd "ON" display.
        delayMicroseconds(1);
        cmd_with_stb(0b01000000); //       cmd 2 //Normal operation; Set pulse as 1/16
        digitalWrite(VFD_ce, LOW);
        delayMicroseconds(1);
            cmd_without_stb((0b11000000)); // Start address 00;
            // 
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.// bar in middle(center)
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.// bar
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.//bar
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.// left grid
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.//DSP 1
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.//DSP 2
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.//DSP 3
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.//DSP 4
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.//DSP 5
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.//DSP 6
            cmd_without_stb(0b00000000); cmd_without_stb(0b00100000); cmd_without_stb(0b00000000); // only half byte of third byte.//DSP 7
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.//DSP 8
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.//dsp small
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.// right grid
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.
            cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); cmd_without_stb(0b00000000); // only half byte of third byte.
            //
            digitalWrite(VFD_ce, HIGH);
            delayMicroseconds(3000);
            Serial.println(((0b11000000) | sum), BIN);
     }
}
/****************************************************************/
void led_on(void){
  byte myByte;
  //Important: The MC3501L only have one pin marked as LED!!!
    digitalWrite(VFD_ce, LOW);
    delayMicroseconds(20);
    cmd_without_stb(0b01000001);
    delayMicroseconds(2);
    myByte ^=(0b01000010);  // Here is only to invert bit of led 1.
    cmd_without_stb(myByte);
    delayMicroseconds(2);
    digitalWrite(VFD_ce, HIGH);
    delayMicroseconds(2);
}
/***************************************************************/
void all_ON(void){
  int sum=0;
  /*
  Here I test all registers 
  Could be done only on the number of grid
  to be more fast. The 12 * 3 bytes = 36 registers
  */
      for (int n=0; n < 16; n++){  //
        cmd_with_stb(0b00001001); //       cmd 1 // 14 Grids & 14 Segments
        delayMicroseconds(1);
        cmd_with_stb((0b10001000) | 7); // IMPORTANT:  After define the size GRIDs is necessary do a cmd "ON" display.
        delayMicroseconds(1);
        cmd_with_stb(0b01000000); //       cmd 2 //Normal operation; Set pulse as 1/16
        digitalWrite(VFD_ce, LOW);
        delayMicroseconds(1);
            cmd_without_stb((0b11000000) | sum); // cmd 3 //wich define the start address (00H to 15H)
            cmd_without_stb(0b11111111); // Data to fill table of 5 grids * 16 segm = 80 bits on the table
            cmd_without_stb(0b11111111); // Data to fill table of 5 grids * 16 segm = 80 bits on the table
            cmd_without_stb(0b11111111); // Data to fill table of 5 grids * 16 segm = 80 bits on the table
            //
            digitalWrite(VFD_ce, HIGH);
            delayMicroseconds(3000);
            Serial.println(((0b11000000) | sum), BIN);
            sum=(sum +3);
     }
}
/***************************************************************/
void numbersLetters(void){
 // Zone to test the numbers and letters
send_char(0x00,number0[0], number0[1], number0[2]);
send_char(0x03,number1[0], number1[1], number1[2]);
send_char(0x06,number2[0], number2[1], number2[2]);
send_char(0x09,number3[0], number3[1], number3[2]);
send_char(0x0C,number4[0], number4[1], number4[2]);
send_char(0x0F,number5[0], number5[1], number5[2]);
send_char(0x12,number6[0], number6[1], number6[2]);
send_char(0x15,number7[0], number7[1], number7[2]);
send_char(0x18,number8[0], number8[1], number8[2]);
send_char(0x1B,number9[0], number9[1], number9[2]);
clear_VFD();
send_char(0x00,letterA[0], letterA[1], letterA[2]);
send_char(0x03,letterB[0], letterB[1], letterB[2]);
send_char(0x06,letterC[0], letterC[1], letterC[2]);
send_char(0x09,letterD[0], letterD[1], letterD[2]);
send_char(0x0C,letterE[0], letterE[1], letterE[2]);
send_char(0x0F,letterF[0], letterF[1], letterF[2]);
send_char(0x12,letterG[0], letterG[1], letterG[2]);
send_char(0x15,letterH[0], letterH[1], letterH[2]);
send_char(0x18,letterI[0], letterI[1], letterI[2]);
send_char(0x1B,letterJ[0], letterJ[1], letterJ[2]);
clear_VFD();
send_char(0x00,letterK[0], letterK[1], letterK[2]);
send_char(0x03,letterL[0], letterL[1], letterL[2]);
send_char(0x06,letterM[0], letterM[1], letterM[2]);
send_char(0x09,letterN[0], letterN[1], letterN[2]);
send_char(0x0C,letterO[0], letterO[1], letterO[2]);
send_char(0x0F,letterP[0], letterP[1], letterP[2]);
send_char(0x12,letterQ[0], letterQ[1], letterQ[2]);
send_char(0x15,letterR[0], letterR[1], letterR[2]);
send_char(0x18,letterS[0], letterS[1], letterS[2]);
send_char(0x1B,letterT[0], letterT[1], letterT[2]);
clear_VFD();
send_char(0x00,letterU[0], letterU[1], letterU[2]);
send_char(0x03,letterV[0], letterV[1], letterV[2]);
send_char(0x06,letterX[0], letterX[1], letterX[2]);
send_char(0x09,letterZ[0], letterZ[1], letterZ[2]);
send_char(0x0C,letterW[0], letterW[1], letterW[2]);
clear_VFD(); 
}
void msgHiFolks(void){
clear_VFD();
send_char(0x00,letterH[0], letterH[1], letterH[2]);
send_char(0x03,letterI[0], letterI[1], letterI[2]);
send_char(0x06, letterSpace[0], letterSpace[1], letterSpace[2]);
send_char(0x09,letterF[0], letterF[1], letterF[2]);
send_char(0x0C,letterO[0], letterO[1], letterO[2]);
send_char(0x0F,letterL[0], letterL[1], letterL[2]);
send_char(0x12,letterK[0], letterK[1], letterK[2]);
send_char(0x15,letterS[0], letterS[1], letterS[2]);
}
void msgHiGuys(void){
clear_VFD();
send_char(0x00,letterH[0], letterH[1], letterH[2]);
send_char(0x03,letterI[0], letterI[1], letterI[2]);
send_char(0x06, letterSpace[0], letterSpace[1], letterSpace[2]);
send_char(0x09,letterG[0], letterG[1], letterG[2]);
send_char(0x0C,letterU[0], letterU[1], letterU[2]);
send_char(0x0F,letterY[0], letterY[1], letterY[2]);
send_char(0x12,letterS[0], letterS[1], letterS[2]);
}
void msgHiPeople(void){
clear_VFD();
send_char(0x00,letterH[0], letterH[1], letterH[2]);
send_char(0x03,letterI[0], letterI[1], letterI[2]);
send_char(0x06, letterSpace[0], letterSpace[1], letterSpace[2]);
send_char(0x09,letterP[0], letterP[1], letterP[2]);
send_char(0x0C,letterE[0], letterE[1], letterE[2]);
send_char(0x0F,letterO[0], letterO[1], letterO[2]);
send_char(0x12,letterP[0], letterP[1], letterP[2]);
send_char(0x15,letterL[0], letterL[1], letterL[2]);
send_char(0x18,letterE[0], letterE[1], letterE[2]);
}
void segBySeg(void){
    int u=0;
  int sum=0;
  unsigned char word1, word2, word3, word4;
  unsigned int mask0=0b000000000000000000000001;
  unsigned int mask1=0b000000000000000000000001;
 
      for ( u =0; u < 32; u++){
        cmd_with_stb(0b00001001); //       cmd 1 // 10 Grids & 24 Segments
        delayMicroseconds(1);
        cmd_with_stb((0b10001000) | 7); // IMPORTANT:  After define the size GRIDs is necessary do a cmd "ON" display.
        delayMicroseconds(1);
        cmd_with_stb(0b01000000); //       cmd 2 //Normal operation; Set pulse as 1/16
        digitalWrite(VFD_ce, LOW);
        delayMicroseconds(1);
        cmd_without_stb((0b11000000) | sum); // cmd 3 //wich define the start address (00H to 15H)
            
        if (u<=15){
       word4 = (mask0 & 0xff000000) >>  24; // remaning segments 
       word3 = (mask0 & 0x00ff0000) >>  16; // remaning segments
       word2 = (mask0 & 0x0000ff00) >>  8; // grid 9 & 10 and segments
       word1 = (mask0 & 0x000000ff) >>  0; // grids
        mask0=(mask0 <<= 1);
        }
        if (u>15){
       word4 = (mask1 & 0xff000000) >>  24; // remaning segments 
       word3 = (mask1 & 0x00ff0000) >>  16; // remaning segments
       word2 = (mask1 & 0x0000ff00) >>  8; // grid 9 & 10 and segments
       word1 = (mask1 & 0x000000ff) >>  0; // grids
        mask1=(mask1 <<= 1);
        }
       //
       //Serial.println(mask0, BIN);
       //Serial.println(mask1, BIN);
            cmd_without_stb(word1); // Data to fill table of 5 grids * 16 segm = 80 bits on the table
            cmd_without_stb(word2); // Data to fill table of 5 grids * 16 segm = 80 bits on the table
            cmd_without_stb(word3); // only half byte of third byte.
            //
            digitalWrite(VFD_ce, HIGH);
            delay(500);
            //Serial.println(((0b11000000) | sum), BIN);
            //sum=(sum +3); //This add allow keep same digit or skip to next digit!
    }
}
void findI2C(){
  //Variables to store the error status and address
  byte error, address;
  // Number of devices found
  int nDevices = 0;
  // Print "Scanning..."
  Serial.println("Scanning...");
  // Run over the range of possible I2C addresses < 128)
  for (address = 1; address < 127; address++) {
    // Try a transmission to the specified address
    Wire.beginTransmission(address);
    Serial.println(address, DEC);
    // Close the transmission and keep the return status in 'error'
    error = Wire.endTransmission();
    // If 'error' is 0, it means that a device has been found at that address
    if (error == 0) {
      // Print the address to the Serial Monitor
      Serial.print("I2C device found at address 0x");
      // If the address is less than 16, print an additional "0" for formatting
      if (address < 16) Serial.print("0");
      // Print the address in hexadecimal format
      Serial.println(address, HEX);
      // Increment the device count
      nDevices++;
    }
  }
  // Case if no devices were found, print a message to the Serial Monitor
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    // If one or more devices were found, print "Done" to the Serial Monitor
    Serial.println("Done\n");
  }
  // Wait 7 seconds before the next scan
  delay(7000);
}
void writeWire(){
 /*
Notes important about I2C: 
-Start Condition: The SDA line switches from a high voltage level to a low voltage level before the SCL line switches from high to low.
-Stop Condition: The SDA line switches from a low voltage level to a high voltage level after the SCL line switches from low to high.
-Address Frame: A 7 or 10 bit sequence unique to each slave that identifies the slave when the master wants to talk to it.
-Read/Write Bit: A single bit specifying whether the master is sending data to the slave (low voltage level) or requesting data from it (high voltage level).
-ACK/NACK Bit: Each frame in a message is followed by an acknowledge/no-acknowledge bit. If an address frame or data frame was successfully 
received, an ACK bit is returned to the sender from the receiving device.

ADDRESSING:
I2C doesn’t have slave select lines like SPI, so it needs another way to let the slave know that data is being sent to it, and not another 
slave. It does this by addressing. The address frame is always the first frame after the start bit in a new message.

The master sends the address of the slave it wants to communicate with to every slave connected to it. Each slave then compares the 
address sent from the master to its own address. If the address matches, it sends a low voltage ACK bit back to the master. If the address 
doesn’t match, the slave does nothing and the SDA line remains high.

READ/WRITE BIT
The address frame includes a single bit at the end that informs the slave whether the master wants to write data to it or receive data 
from it. If the master wants to send data to the slave, the read/write bit is a low voltage level. If the master is requesting data from 
the slave, the bit is a high voltage level.

THE DATA FRAME
After the master detects the ACK bit from the slave, the first data frame is ready to be sent.

The data frame is always 8 bits long, and sent with the most significant bit first. Each data frame is immediately followed by an 
ACK/NACK bit to verify that the frame has been received successfully. The ACK bit must be received by either the master or the slave 
(depending on who is sending the data) before the next data frame can be sent.
*/

/*
STEPS OF I2C DATA TRANSMISSION
1. The master sends the start condition to every connected slave by switching the SDA line from a high 
voltage level to a low voltage level before switching the SCL line from high to low:

Introduction to I2C - Data Transmission Diagram START CONDITION

2. The master sends each slave the 7 or 10 bit address of the slave it wants to communicate with, 
along with the read/write bit:

Introduction to I2C - Data Transmission Diagram ADDRESS FRAME

3. Each slave compares the address sent from the master to its own address. If the address matches, 
the slave returns an ACK bit by pulling the SDA line low for one bit. If the address from the master 
does not match the slave’s own address, the slave leaves the SDA line high.

Introduction to I2C - Data Transmission Diagram ACK Bit Slave to Master

4. The master sends or receives the data frame:

Introduction to I2C - Data Transmission Diagram Data Frame

5. After each data frame has been transferred, the receiving device returns another ACK bit to the sender 
to acknowledge successful receipt of the frame:

Introduction to I2C - Data Transmission Diagram ACK Bit Slave to Master

6. To stop the data transmission, the master sends a stop condition to the slave by switching SCL high 
before switching SDA high: 
 */
byte error = 0x00;
byte count = 0;
//byte arr[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//byte 0 = 01, Stay running and skip over all 2 leds
//byte 0 = 02, >>>>> left to right one time
//byte 0 = 03, <<<<< right to left one time
//byte 0 = 04, All 18 LED's blinking 2 times
//byte 0 = 05, 3 set of >>>>> 3 times
//byte 0 = 06, Set of 3 movements <<<.>>>
//byte 0 = 07, Set of 3 movements >>>.<<<
//byte 0 = 08, Stay running over all LED's >>>>>
//byte 0 = 09, Stay running over all LED's <<<<<
//byte 0 = 0A, Running as close windows
//byte 0 = 0B, Running as close windows >>>>>!<<<<<
//byte 0 = 0C, 0D,0E, 0F ??

byte arr[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};

Wire.begin();
for (int n=1; n<12; n++){  //The 0 and the C,D,E and F don't have any reaction, by this reason I skip it's!
     Wire.beginTransmission(0x73);
     //Wire.write(arr, sizeof(arr));
     Wire.write(arr[n]);
      //Wire.beginTransmission(115); //115 is 73Hex
      //Wire.beginTransmission(0xE6);
      //Wire.beginTransmission(B01110011);  //(B01110011) = 0xE6 address As a Byte
      // Wire.beginTransmission(0b01110011);  //(B01110011) = 0xE6 address Pure binary
   error = Wire.endTransmission();
   Serial.println(error, HEX);
    if (Wire.endTransmission() == 0)
      {
      Serial.println("Close transmission successful!");
      } // end of good response
      else{
        Serial.print("Error: ");
        Serial.println(error, HEX);
      }
      delay(4000);
}
  Wire.end();
}
/**************************************************************/
void setup() {
pinMode(LED_BUILTIN, OUTPUT);
Serial.begin (115200);
//
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
digitalWrite(10, LOW);

MC3501L_init();
//
test_VFD();
//
clear_VFD();
//
Wire.begin(1);//This is optional, this add the master to BUS.
//findI2C(); //If you will go use the port I2C(pins 4 and 5 of Arduino) and is connected, uncomment this line!
}

void loop() { 
digitalWrite(10, HIGH); 
all_ON();
delay(3000);
clear_VFD();
// 
segBySeg();
delay(500);
// 
msgHiFolks();
delay(1000);
// 
msgHiGuys();
delay(1000);
//
digitalWrite(10, LOW);
msgHiPeople();
writeWire();
//
numbersLetters();
//
seg();
delay(1000);
//
clear_VFD();
//led_on();
delay(500);
}
/***************************************************************/
ISR(TIMER1_COMPA_vect)   {  //This is the interrupt request
                            // https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
     ; // Take trigger every 0.5 second to perfome a count of seconds
} 
