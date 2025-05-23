#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <string>
#include <iostream>

#define filename "./a.out"

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

char chariar(char c){
    if(c>='0'&&c<='9')return c;
    if(c>='A'&&c<='Z')return c;
    if(c>='a'&&c<='z')return c;

    return '.';
}
static int uwu;

int main(){
    int fd = open(filename,O_RDWR|O_CREAT);

    struct stat st;

    // fstat(fd,&st);

    uint8_t* file = (uint8_t*)mmap(0,64,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    // file[0]=0;

    // msync(file,1,MS_SYNC);

    

    std::cout << "ELF header" << std::endl;
    for(int i = 0;i<64;i++){
        std::cout << hexify(file[i],b8)<< " " << chariar(file[i])<< " ";

        if(i%8==7) std::cout << std::endl;
    }
    

}