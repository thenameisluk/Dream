#include <vector>
#include <map>
#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <array>
#include "asmyas.hpp"

struct dataspam
{
    uint64_t span;
    uint8_t v = 0;
};

void panic(std::string e, std::string section = "?")
{
    std::cout << "[" << section << "](panic) " << e << std::endl;
    exit(1);
}
void warning(std::string e, std::string section = "?")
{
    std::cout << "[" << section << "](warning) " << e << std::endl;
}

enum byte_size : uint64_t
{
    b8 = 1,
    b16 = 2,
    b32 = 4,
    b64 = 8,
};

class sraw
{ // stream resolver and writer
public:
    uint64_t capacity = 1;
    uint8_t *data = (uint8_t *)malloc(1);
    uint64_t pointer = 0; // defacto size
    std::map<std::string, std::vector<uint64_t>> promises;

    ~sraw()
    {
        free(data);
        // prevent memory leak
    }
    void bump()
    {
        capacity <<= 1;
        data = (uint8_t *)realloc(data, capacity);
    }
    sraw &operator<<(uint64_t v)
    {
        int64_t req = 8;
        while (req + pointer >= capacity)
        {
            bump();
        }
        *((uint64_t *)(data + pointer)) = v;

        pointer += req;

        return *this;
    }
    sraw &operator<<(uint32_t v)
    {
        int64_t req = 4;
        while (req + pointer >= capacity)
        {
            bump();
        }
        *((uint32_t *)(data + pointer)) = v;

        pointer += req;

        return *this;
    }
    sraw &operator<<(uint16_t v)
    {
        int64_t req = 2;
        while (req + pointer >= capacity)
        {
            bump();
        }
        *((uint16_t *)(data + pointer)) = v;

        pointer += req;
        return *this;
    }
    sraw &operator<<(uint8_t v)
    {
        int64_t req = 1;
        while (req + pointer >= capacity)
        {
            bump();
        }
        *(data + pointer) = v;

        pointer += req;
        return *this;
    }
    sraw &operator<<(char v)
    {
        int64_t req = 1;
        while (req + pointer >= capacity)
        {
            bump();
        }
        *(data + pointer) = v;

        pointer += req;
        return *this;
    }
    void span(uint8_t len, uint8_t v = 0)
    {
        for (int i = 0; i < len; i++)
        {
            (*this) << v;
        }
    }
    void promise(byte_size size, std::string name)
    {
        while (size + pointer >= capacity)
        {
            bump();
        }
        promises[name].push_back(pointer);

        pointer += size;
    }
    void resolve(uint64_t value, std::string name)
    {
        if (promises.find(name) == promises.end())
        {
            panic("promise "+name+" doesn't exist","reolver");
        }
        if(promises[name].size()==0){
            panic("double resolution of "+name,"resolver");
        }

        for(uint64_t place : promises[name]){
            *((uint64_t *)(data + place)) = value;
        }

        promises[name].clear();
    }
    void resolve(uint32_t value, std::string name)
    {
        if (promises.find(name) == promises.end())
        {
            panic("promise "+name+" doesn't exist","reolver");
        }
        if(promises[name].size()==0){
            panic("double resolution of "+name,"resolver");
        }

        for(uint64_t place : promises[name]){
            *((uint32_t *)(data + place)) = value;
        }

        promises[name].clear();
    }
    void resolve(uint16_t value,std::string name){
        if (promises.find(name) == promises.end())
        {
            panic("promise "+name+" doesn't exist","reolver");
        }
        if(promises[name].size()==0){
            panic("double resolution of "+name,"resolver");
        }

        for(uint64_t place : promises[name]){
            *((uint16_t *)(data + place)) = value;
        }

        promises[name].clear();
    }
    // void resolve(uint8_t value,std::string name){

    // }
    
    //really proud of this one
    //since it uses exclusively syscalls it can be semi easily rewriten in assembly
    void dumpfile(const char *filename)
    {
        
        int fd = open(filename, O_RDWR|O_CREAT);//open the file

        if(fd==-1){
            panic("failed to open the file");
        }

        ftruncate(fd, pointer);//resize file

        uint8_t *file = (uint8_t *)mmap(0, pointer, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);//map file to memory
        //aparently it has to be shared for file to updated

        for (int i = 0; i < pointer; i++)
        {
            // std::cout << i << std::endl;
            file[i] = data[i];//copy over the data
        }

        msync(file, pointer, MS_SYNC);//sync file with filesystem

        close(fd);//close the file
    }
    std::vector<uint8_t> dumpvector()
    {
        std::vector<uint8_t> out(pointer);
        for (int i = 0; i < pointer; i++)
        {
            out[i] = data[i];
        }
        return out;
    }
};

uint32_t lb(uint32_t v){
    int out = 0;
    out|= (0xFF000000|v)>>24;
    out|= (0xFF0000|v)>>8;
    out|= (0xFF00|v)<<8;
    out|= (0xFF|v)<<24;
    return out;
}

int main(){
    sraw elf;

    elf << (uint8_t)0x7F << 'E' << 'L' << 'F';
    elf << (uint8_t)2;//64bit
    elf << (uint8_t)1;//little endian
    elf << (uint8_t)1;//elf version
    elf << (uint8_t)0;//OS abi (system V)
    elf.span(8);//padding
    elf << (uint16_t)2;//executable
    elf << (uint16_t)0xB7;//arm64
    elf << (uint32_t)1;//elf version

    elf << (uint64_t)0x40078;//entry
    
    elf.promise(b64,"program_header_offset");
    elf.promise(b64,"section_header_offset");//never resolved :<

    elf << (uint32_t)0;//flags
    elf << (uint16_t)64;//elf header size

    elf << (uint16_t)56;//size of program header entry
    elf << (uint16_t)1;//number of entries

    elf << (uint16_t)64;//size of section header entry
    elf << (uint16_t)0;//number of entries

    elf << (uint16_t)0;//index to string section
    
    std::vector<uint32_t> code = {
        MOVZ_imm16(true,7,r0),
        MOVZ_imm16(true,93,r8),
        SVC()
    };
    
    //program header
    elf.resolve(elf.pointer,"program_header_offset");
    elf << (uint32_t)1;//type = load
    elf << (uint32_t)(1+4);
    elf.promise(b64,"code_section");//where in the file is the code
    elf << (uint64_t)0x40078;//where put it in memory
    elf << (uint64_t)0x40078;//physical address (for systems where it's relevant???)
    elf << (uint64_t)4*code.size();//size in file
    elf << (uint64_t)4*code.size();//size in memory
    elf << (uint64_t)0x1000;//allignment
    //section header

    //code
    elf.resolve(elf.pointer,"code_section");
    for(int i = 0;i<code.size();i++){
        elf << code[i];
    }


    elf.dumpfile("./testme");
}