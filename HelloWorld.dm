import {} from "std"//no header files


name{//namespaces
    class e{//class
        //members private by default
        e()//constructor
        ~e()//destructor
        //methods
        operator++(){
            this
        }//operator overloading
    };    
    struct e{//stuct
        //members public by default
        //no constructors
        //methods
    };
};



//store single value
[type] enum e{
    a,
    b = 1
}

//diffrent possible falues
variant e{
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

while(true){//infinit

}

for (let n in 0..10) {

}
//both valid
for (let i = 0;i<10;i++){

}

//arrays are static length
let arr =  {0,0,2}//:i32[3]


x..y ranges

let e:(u32,i8) = (0,0);//tupples
let (a,b) = e;//extraction

use namespace::element//for direct access


let //no need to specify obvious types
const/static //mutability by default
let& refference
let* pointer

if a(e&) = someVariantWithA{//if someVariantWithA is a then refference to e

}

while Some(i) = optional{while optional is Some then assign value to i
    
}

//Some(i) = optional
//a(e&) = someVariantWithA
//can be treadted as true or false an expression

type sth = u8

8 as u8 //explicit convertion, implicity only up

cstr/str/vec //types built-in
/*
cstr ascii
str utf8
vec T
*/


fn main():i32{//<- entry point
}

//to be figured out

macros

lifetime
slices

function pointers (no closures)