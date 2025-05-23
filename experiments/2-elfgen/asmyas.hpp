#include <stdint.h>
#include <iostream>
#include <string>

void jitError(std::string e){
    std::cout << "[JIT](ERROR) " << e << std::endl;
    exit(1);
}

enum reg:uint8_t{
    r0=0,
    r1=1,
    r2=2,
    r3=3,
    r4=4,
    r5=5,
    r6=6,
    r7=7,
    r8=8,
    r9=9,
    r10=10,
    r11=11,
    r29=29,
    r30=30,
    //either "zero register" or stack pointer depending on a context
    r31=31,
    sp=31

};
enum cond:uint8_t{
    EQ=0b0000,//==
    NE=0b0001,//!=
    //unsigned
    CS=0b0010,//>=
    CC=0b0011,//<
    HI=0b1000,//>
    LS=0b1001,//<=
    //signed
    GE=0b1010,//>=
    LT=0b1011,//<
    GT=0b1100,//>
    LE=0b1101,//<=
    //other
    MI=0b0100,//minus/negative
    PL=0b0101,//plus or zero
    //overflow
    VS=0b0110,//set
    VC=0b0111,//clear
    //always
    AL=0b1110,//true
    NV=0b1111//true
};

//STP <Xt1>, <Xt2>, [<Xn|SP>], #<imm>
//or
//stp x1, x2, [xn]
//add xn, xn, #imm
//or
//stp x1, x2, [xn]
//add xn, xn, #imm
//64bit imm/8
//32bit imm/4
uint32_t STP_post_index(bool a64,uint8_t imm7,reg r1,reg r2,reg basereg){
    uint32_t out = a64;
    
    //opcode
    out<<=9;
    out|=0b010100010;

    //imm7
    out<<=7;
    out|=imm7&0b1111111;

    //r2
    out<<=5;
    out|=r2;

    //rt
    out<<=5;
    out|=basereg;

    //r1
    out<<=5;
    out|=r1;

    return out;
}

//STP <Xt1>, <Xt2>, [<Xn|SP>, #<imm>]!
uint32_t STP_pre_index(bool a64,uint8_t imm7,reg r1,reg r2,reg basereg){
    uint32_t out = a64;
    
    //opcode
    out<<=9;
    out|=0b010100110;

    //imm7
    out<<=7;
    out|=imm7&0b1111111;

    //r2
    out<<=5;
    out|=r2;

    //rt
    out<<=5;
    out|=basereg;

    //r1
    out<<=5;
    out|=r1;

    return out;
}

//STP <Xt1>, <Xt2>, [<Xn|SP>{, #<imm7>}]
uint32_t STP_signed(bool a64,uint8_t imm7,reg r1,reg r2,reg basereg){
    uint32_t out = a64;
    
    //opcode
    out<<=9;
    out|=0b010100100;

    //imm7
    out<<=7;
    out|=imm7&0b1111111;

    //r2
    out<<=5;
    out|=r2;

    //rt
    out<<=5;
    out|=basereg;

    //r1
    out<<=5;
    out|=r1;

    return out;
}


//LDP <Xt1>, <Xt2>, [<Xn|SP>], #<imm>
uint32_t LDP_post_index(bool a64,uint8_t imm7,reg r1,reg r2,reg basereg){
    uint32_t out = a64;
    
    //opcode
    out<<=9;
    out|=0b010100011;

    //imm7
    out<<=7;
    out|=imm7&0b1111111;

    //r2
    out<<=5;
    out|=r2;

    //rt
    out<<=5;
    out|=basereg;

    //r1
    out<<=5;
    out|=r1;

    return out;
}

//LDP <Xt1>, <Xt2>, [<Xn|SP>, #<imm>]!
uint32_t LDP_pre_index(bool a64,uint8_t imm7,reg r1,reg r2,reg basereg){
    uint32_t out = a64;
    
    //opcode
    out<<=9;
    out|=0b010100111;

    //imm7
    out<<=7;
    out|=imm7&0b1111111;

    //r2
    out<<=5;
    out|=r2;

    //rt
    out<<=5;
    out|=basereg;

    //r1
    out<<=5;
    out|=r1;

    return out;
}

//LDP <Xt1>, <Xt2>, [<Xn|SP>{, #<imm7>}]
uint32_t LDP_signed(bool a64,uint8_t imm7,reg r1,reg r2,reg basereg){
    uint32_t out = a64;
    
    //opcode
    out<<=9;
    out|=0b010100101;

    //imm7
    out<<=7;
    out|=imm7&0b1111111;

    //r2
    out<<=5;
    out|=r2;

    //rt
    out<<=5;
    out|=basereg;

    //r1
    out<<=5;
    out|=r1;

    return out;
}

uint32_t B(int32_t imm26){
    //opcode
    uint32_t out = 0b000101;
    
    imm26&=0x03FFFFFF;

    out<<=26;
    out|=imm26;

    return out;
}

uint32_t NOP(){
    return 0b11010101000000110010000000011111;
}

uint32_t B_cond(int32_t imm19,uint8_t cond){
    jitError("B.cond not implementd");
    return 0;
}

uint32_t BL(int32_t imm19,uint8_t cond){
    jitError("B.cond not implementd");
    return 0;
}

uint32_t BLR(int32_t imm19,uint8_t cond){
    jitError("B.cond not implementd");
    return 0;
}

uint32_t BR(int32_t imm19,uint8_t cond){
    jitError("B.cond not implementd");
    return 0;
}

uint32_t RET(reg r=r30){
    uint32_t out = 0b1101011001011111000000;

    out<<=5;
    out|=r;

    out<<=5;
    // out=0b00000;
    return out;
}

uint32_t BRK(int16_t imm16=0){
    uint32_t out = 0b11010100001;

    out<<=16;
    out|=imm16;

    out<<=5;
    // out=0b00000;
    return out;
}

//moves 16bit value to register at x offset
//this one wipes the register
//w32
//x64
//shift 0-3 for 64bit 0-1 32bit
uint32_t MOVZ_imm16(bool a64,uint16_t imm16,reg r,uint8_t shift=0){
    //variant 64/32bit
    uint32_t out = a64;
    //opcode
    out<<=8;
    out|=0b10100101;

    //shift
    if(a64){
        if(shift>3)jitError("too big shift");
    }else if(shift>1)jitError("too big shift");

    out<<=2;
    out|=(shift&0b11);

    //imm16
    out<<=16;
    out|=imm16;
    
    //target register
    out<<=5;
    out|=r;

    return out;
}

//moves 16bit value to register at x offset
//this one keeps other parts of ther register
//w32
//x64
//shift 0-3 for 64bit 0-1 32bit
uint32_t MOVK_imm16(bool a64,uint16_t imm16,reg r,uint8_t shift=0){
    //variant 64/32bit
    uint32_t out = a64;
    //opcode
    out<<=8;
    out|=0b11100101;
           

    //shift
    if(a64){
        if(shift>3)jitError("too big shift");
    }else if(shift>1)jitError("too big shift");

    out<<=2;
    out|=(shift&0b11);

    //imm16
    out<<=16;
    out|=imm16;
    
    //target register
    out<<=5;
    out|=r;

    return out;
}

//this is an alias to ORR so it might be a good idea to make it utilize ORR to generate
//Warning. this instruction doesn't work with stack pointer, if needed pls use MOV_reg_with_sp
uint32_t MOV_reg(bool a64,reg destination,reg source){
    uint32_t out = a64;
    //opcode
    out<<=10;
    out|=0b0101010000;

    out<<=5;
    out|=source;

    out<<=11;
    out|=0b00000011111;

    out<<=5;
    out|=destination;

    return out;
}

//this is an alias to ADD so it might be a good idea to make it utilize ADD to generate
uint32_t MOV_reg_with_sp(bool a64,reg destination,reg source){
    uint32_t out = a64;
    //opcode
    out<<=21;
    out|=0b001000100000000000000;

    out<<=5;
    out|=source;

    out<<=5;
    out|=destination;

    return out;
}

//it is unknown to the internet what the imm16 here does
//so keep it as 0 unless you feel funny
uint32_t SVC(uint16_t imm16=0){
    //opcode
    uint32_t out = 0b11010100000;
    
    //imm16
    out<<=16;
    out|=imm16;

    //opcode 2
    out<<=5;
    out|=0b00001;

    return out;
}