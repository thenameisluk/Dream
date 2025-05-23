### mini project
# ELF file analizer
(this is really small one)

as the goal of the language is to be self hosted

simple idea to dump elf file header

while at this moment i can use ```readelf```

it sets up groud for being able to analize elf files

so i can actually gather informations on how to generate them

it also helped me distance my self more from c library which

i don't want to rely on if i want to achive independence

instead we use exclusively syscalls to read the content of the file

```cpp
int fd = open(filename,O_RDWR|O_CREAT);

uint8_t* file = (uint8_t*)mmap(0,64,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

std::cout << "ELF header" << std::endl;
for(int i = 0;i<64;i++){
    std::cout << hexify(file[i],b8)<< " " << chariar(file[i])<< " ";

    if(i%8==7) std::cout << std::endl;
}
```