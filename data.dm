i32 a//alternative
const/static //mutability by default, but variable never modified will give warning
i32& refference
i32* pointer

//arrays are static length
i32[] arr =  {0,0,2}



(u32,i8) e: = (0,0);//tupples
(a,b) = e;//extraction
u32 a& = e(0);//extraction

type color u32//type definition

8 as u8 //explicit convertion, implicity only up



//types
//primitive
char
i8/i16/i32/i64
u8/u16/u32/u64
bool



//dynamic
cstr/str/vec //types built-in
/*
cstr ascii
str utf8
vec
uptr<...>//unique pointer
sptr<...>//shared pointer
*/