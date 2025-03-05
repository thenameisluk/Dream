import {} from "std"//no header files


name{//namespaces
    class e{//class
        e()//constructor
        ~e()//destructor
        operator++()//operator overloading
    };    
    struct e{//stuct

    };
};

enum e{
    a:sth,
    b,
    none
}

match e{
    a(e):{

    }
    b:fun()
    _:
}

loop{//infinit

}

while true{//infinit

}

for n in 0..10 {

}

0..x ranges

let e:(u32,i8) = (0,0);//tupples
let (a,b) = e;//extraction

function pointers (no closures)

use namespace::element//for direct access

?super+self

let //no need to specify obvious types

if let a(e) = someEnumWithA {

}

while let Some(i) = optional{
    
}

type sth = u8

const/static

mut//immutability by default

8 as u8 //explicit convertion, implicity only for types up size

cstr/str/vec //types built-in
/*
cstr ascii
str utf8
vec T
*/

macros

slices

lifetime

fn main():i32{//<- entry point
}

thread safe?