let //no need to specify obvious types
i32 a//alternative
const/static //mutability by default, but variable never modified will give warning
let& refference
let* pointer

//arrays are static length
let arr:i32[] =  {0,0,2}//:i32[3]
//or
let arr =  {0,0,2}
//or
i32[] arr =  {0,0,2}



let e:(u32,i8) = (0,0);//tupples
let (a,b) = e;//extraction

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
vec T
*/