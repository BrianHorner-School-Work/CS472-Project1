// CS472 Project 1 - MIPS Disassembler
//
// Author: Brian Horner
// Edit History:
// 2/5/2022 - Initial Version and Establishing Git Repo

// Standard Library Includes
#include <iostream>
#include <bitset>
#include <map>

// User Built Includes

unsigned int CalcOpCode(int originalHex); //Calculates OP Code
unsigned int CalcRFormat(int OriginalHex); //Calculates R Format Instruction


// Map for opcodes
std::map<unsigned int, std::string> OPCodeDict{
    {0b000000, "Error"},    {0b000010, "j"},
    {0b000011, "jal"},      {0b000100, "beq"},
    {0b000101, "bne"},      {0b000110, "blez"},
    {0b000111, "bgtz"},     {0b001000, "addi"},
    {0b001001, "addiu"},    {0b001010, "siti"},
    {0b001011, "sltiu"},    {0b001100, "andi"},
    {0b001101, "ori"},      {0b001110, "xori"},
    {0b001111, "lui"},      {0b100000, "lb"},
    {0b100001, "lh"},       {0b100010, "lwl"},
    {0b100011, "lw"},       {0b100100, "lbu"},
    {0b100101, "lhu"},      {0b100110, "lwr"},
    {0b101000, "sb"},       {0b101001, "sh"},
    {0b101010, "swl"},      {0b101011, "sw"},
    {0b101110, "swr"},      {0b101111, "cache"},
    {0b110000, "li"},       {0b110001, "lwc1"},
    {0b110010, "lwc2"},     {0b110011, "pref"},
    {0b110101, "idc1"},     {0b110110, "idc2"},
    {0b111000, "sc"},       {0b111001, "swc1"},
    {0b111010, "swc2"},     {0b111101, "sdc1"},
    {0b111110, "sdc2"},
};

// Map for Function Codes
std::map<unsigned int, std::string> FuncCodeDict = {
        {0b000000, "sll"},      {0b000010, "srl"},
        {0b000011, "sra"},      {0b000100, "sllv"},
        {0b000110, "srlv"},     {0b000111, "srav"},
        {0b001000, "jr"},       {0b001001, "jalr"},
        {0b001010, "movz"},     {0b001011, "movn"},
        {0b001100, "syscall"},  {0b001101, "break"},
        {0b001111, "sync"},     {0b010000, "mfhi"},
        {0b010001, "mthi"},     {0b010010, "mflo"},
        {0b010011, "mtlo"},     {0b011000, "multi"},
        {0b011001, "multiu"},   {0b011010, "div"},
        {0b011011, "divu"},     {0b100000, "add"},
        {0b100001, "addu"},     {0b100010, "sub"},
        {0b100011, "subu"},     {0b100100, "and"},
        {0b100101, "or"},       {0b100110, "xor"},
        {0b100111, "nor"},      {0b101010, "slt"},
        {0b101011, "sltu"},     {0b110000, "tge"},
        {0b110001, "tgeu"},     {0b110010, "tlt"},
        {0b110011, "tltu"},     {0b110100, "teq"},
        {0b110110, "tne"},
};

unsigned int startMem{0x9A040};

int main() {
//    unsigned int test1 = 0x8CE90014;
//    std::cout << "Test hex instruction in decimal is " <<test1 <<std::endl;
//    std::cout << "Test hex instruction in binary is " <<std::bitset<32>
//            (test1)<<std::endl;
//    std::cout << "Test hex instruction in hex is " << std::hex <<test1
//    <<std::endl;
//
//    unsigned int OpCodeMask;
//    OpCodeMask = 0b11111100000000000000000000000000;
//    unsigned int OpCodeShiftTest;
//    OpCodeShiftTest = 0b111111<<26;
//    std::cout << "Did the shift work?  " <<bool(OpCodeMask ==
//    OpCodeShiftTest) <<std::endl;
//    std::cout << "OpCodeMaskManual is: " <<OpCodeMask << "\n"
//                                                         "OpCodeTestWithShift"
//                                                         " is: "
//                                                         <<OpCodeShiftTest
//                                                         <<std::endl;
//    std::cout << "Mask in binary is " << std::bitset<32>(OpCodeMask)
//            <<std::endl;
//    unsigned int OpcodeResult = (test1 & OpCodeShiftTest)>>26;
//    std::cout << "Return Op Code after shift is " <<std::bitset<6>
//            (OpcodeResult) <<std::endl;
//
//    std::cout << "Testing OpCode Func " <<std::bitset<6>(CalcOpCode(test1))
//    <<std::endl;

unsigned int test2 = 0x022DA822;
//std::cout << std::bitset<32>(test2<<6)<<std::endl;
//unsigned int mem1Mask = (0b11111<<27);
//std::cout << std::bitset<32>(mem1Mask) <<std::endl;
    CalcRFormat(test2);
//std::cout <<std::bitset<32>(0x022DA822)<<std::endl;
////std::cout << "Left shift: ";
//std::cout << std::bitset<32>((0b11111<<26)>>5)<<std::endl;
    return 0;
}

// Start of checks
unsigned int CalcOpCode(int originalHex){
    // Calculates the OP Code
    unsigned int OpCodeMask = 0b111111<<26;
    unsigned int OpCode = OpCodeMask & originalHex;
    return OpCode >> 26;

}

// If Op Code equals 000000 go here
unsigned int CalcRFormat(int OriginalHex){
    //Calculates the R format instructions
    unsigned int MemMask = 0b11111;
    unsigned int FuncMask = 0b111111;
    int MaskShift{26};
    for(unsigned int i{0}; i<5; i++){
        MaskShift-=5;
        if (i < 3){
            std::cout << i << std::endl;
            std::cout << (std::bitset<5>(((MemMask<<MaskShift) & OriginalHex)
            >>MaskShift))
            <<std::endl;
        }else if (i>3){
            MaskShift-=1;
            std::cout << i <<std::endl;
            std::cout << (std::bitset<6>(((FuncMask<<MaskShift)&OriginalHex)
            >>MaskShift))<<std::endl;
        }
    }
}