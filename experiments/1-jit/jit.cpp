#include <stdint.h>
#include <string>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include <vector>

#include "fromat.cpp"
#include "asmyas.hpp"

void complience_test(){
    if(0xd28000e0!=MOVZ_imm16(true,7,r0))jitError("incorrect encoding for mov x0, #7");
    if(0x52800ba8!=MOVZ_imm16(false,93,r8))jitError("incorrect encoding for mov w8, #93");

    if(0xd4000001!=SVC())jitError("incorrect encoding for svc #0");
}

void run(void (*func)()){
    func();
}

int main(int argc, char *argv[]) {

    const char* message = "Hello!\n";

    uint64_t addr = (uint64_t)message;

    std::vector<uint32_t> code = {
        // BRK(),
        STP_pre_index(true,-4,r29,r30,sp),
        MOV_reg_with_sp(true,r29,sp),
        // BRK(),
        MOVZ_imm16(true,1,r0),
        MOVZ_imm16(true,addr&0xFFFF,r1),
        MOVK_imm16(true,(addr&0xFFFF0000)>>16,r1,1),
        MOVK_imm16(true,(addr&0xFFFF00000000)>>32,r1,2),
        MOVK_imm16(true,(addr&0xFFFF000000000000)>>48,r1,3),
        MOVZ_imm16(true,8,r2),
        MOVZ_imm16(true,64,r8),
        SVC(),
        MOVZ_imm16(true,0,r0),//addr
        MOVZ_imm16(true,16,r1),//len
        MOVZ_imm16(true,PROT_READ|PROT_WRITE,r2),//prop
        MOVZ_imm16(true,MAP_ANONYMOUS|MAP_PRIVATE,r3),//flags
        MOVZ_imm16(true,-1,r4),//fd
        MOVK_imm16(true,-1,r4,1),//fd
        MOVK_imm16(true,-1,r4,2),//fd
        MOVK_imm16(true,-1,r4,3),//fd
        MOVZ_imm16(true,0,r5),//off
        MOVZ_imm16(true,222,r8),//mmap
        SVC(),
        LDP_post_index(true,4,r29,r30,sp),
        RET(),
        MOVZ_imm16(true,7,r0),//mov x0, #7
        MOVZ_imm16(true,93,r8),//mov x8, #93
        SVC(),//svc #0
    };


	uint32_t* mem = (uint32_t*)mmap(NULL, code.size()*4, PROT_READ | PROT_WRITE,
		   MAP_ANON | MAP_PRIVATE, -1, 0);

    for(int i = 0;i<code.size();i++){
        std::cout << hexify(code[i],b32)<<std::endl;
        mem[i] = code[i];
    }
	
    // mmap(0,1024,0,0,-1,0);

	mprotect(mem, sizeof(code), PROT_READ | PROT_EXEC); 

	void (*func)() = reinterpret_cast<void(*)()>(mem);

	run(func);

	return 0;
}