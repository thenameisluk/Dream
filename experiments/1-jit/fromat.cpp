#include <string>
#include <stdint.h>
#include <iostream>


std::string bitify(uint64_t inst){
    std::string out = "0b";
    uint64_t mask = 0x8000000000000000;

    for(int i = 0;i<64;i++){
        if(inst&mask){
            out+="1";
        }else out += "0";

        inst<<=1;
    }
    
    return out;
}

enum hex_size:uint64_t{
    b8=2,
    b16=4,
    b32=8,
    b64=16,
};

std::string hexify(uint64_t inst,hex_size size=b32,bool append0x=true){
    std::string out = "";

    if(append0x){
        out += "0x";
    }

    uint64_t mask = 0xF;

    mask<<=((size-1)*4);

    // std::cout << bitify(mask) << std::endl;

    for(int i = 1;i<=size;i++){
        uint8_t val = (inst&mask)>>((size-i)*4);
        // std::cout << (uint64_t)val << std::endl;
        if(val<10)out+=std::to_string(val);
        else out+=(char)('A'+(val-10));

        mask>>=4;
    }
    
    return out;
}

int main(){
    std::cout << hexify(0xFEDCBA9876543210,b64) << std::endl;
    std::cout << hexify(0x1234BA9876543210,b64) << std::endl;
    std::cout << hexify(0x12345678,b32) << std::endl;
    std::cout << hexify(0xABCD,b16) << std::endl;
    std::cout << hexify(0x69,b8) << std::endl;
}