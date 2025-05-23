# Just-in-time compiler (arm64)
first of my "experiments"

all files found here (except for the binaries) were part of it

i'm not fluent in arm64 assembly but i understand the idea of cpu instructions fairly well

which doesn't seam to be that hard

```asmyas.hpp```
a collection of functions that generate arm64 instructions

### it aint really rocket science
```cpp
uint32_t B(int32_t imm26){
    //opcode
    uint32_t out = 0b000101;
    
    imm26&=0x03FFFFFF;

    out<<=26;
    out|=imm26;

    return out;
}
```
but it abstracts away instructions encoding which is gread

```format.cpp```
is meant to turn numbers to their hex and bit representation
```cpp
int main(){
    std::cout << hexify(0xFEDCBA9876543210,b64) << std::endl;
    std::cout << hexify(0x1234BA9876543210,b64) << std::endl;
    std::cout << hexify(0x12345678,b32) << std::endl;
    std::cout << hexify(0xABCD,b16) << std::endl;
    std::cout << hexify(0x69,b8) << std::endl;
}
```
while it should in theory be a header file
C++ allows us to include source file so whatever

### Executing generated instructions

fairly simple
```jit.cpp```
maps readable and writable memory region
```cpp
uint32_t* mem = (uint32_t*)mmap(NULL, code.size()*4, PROT_READ | PROT_WRITE,
		   MAP_ANON | MAP_PRIVATE, -1, 0);
```

writes the code to it
```cpp
for(int i = 0;i<code.size();i++){
    std::cout << hexify(code[i],b32)<<std::endl;
    mem[i] = code[i];
}
```

makes it exacutable
```cpp
mprotect(mem, sizeof(code), PROT_READ | PROT_EXEC); 
```

interprets it as function pointer :3 and calls
```cpp
void (*func)() = reinterpret_cast<void(*)()>(mem);

run(func);
```

it's quiet simple really but it gets the job of being simple jit done

sources :
- mapping executable memory
- arm64 instructions encoding : https://developer.arm.com/documentation/ddi0602/2025-03/Base-Instructions?lang=en