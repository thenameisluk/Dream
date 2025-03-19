import {} from "std"//no header files


name{//namespaces
    class e{//class
        //members private by default
        pub sth:i32;
        prv a:u8;
        e()//constructor
        ~e()//destructor
        //methods
        operator++(){//no need for void
            this.sth++;
        }//operator overloading
        getSth():i32(){
            if(false)
                ret sth;//
            
            this.sth//last value is also return statement
        }
    };
    struct e{//stuct
        //members public by default
        //no constructors
        //methods
    };

    //store single value
    i32 enum e{
        a,
        b = 1,
        c
    }

    //diffrent possible values
    variant e{
        a:sth,
        b,
        none
    }

    fun(uwu:i8):i32{

    }
};






//variant
match e{
    a(e):{

    }
    b:fun()//function
    _:
}
//enum
match e{
    a,b:{//combile

    },
    c,
    _:{//other (optional if all covered)

    }
}

loop{//infinit

}

while(true){//infinit

}

for(n in 0..10){//x..y ranges

}
//both valid
for (let i = 0;i<10;i++){

}

//arrays are static length
let arr =  {0,0,2}//:i32[3]




let e:(u32,i8) = (0,0);//tupples
let (a,b) = e;//extraction

use namespace::element//for direct access


let //no need to specify obvious types
const/static //mutability by default, but variable never modified will give warning
let& refference
let* pointer

if a(e&) = someVariantWithA{//if someVariantWithA is a then refference to e

}

while Some(i) = optional{while optional is Some then assign value to i
    
}

//Some(i) = optional
//a(e&) = someVariantWithA
//can be treadted as true or false an expression

8 as u8 //explicit convertion, implicity only up

cstr/str/vec //types built-in
/*
cstr ascii
str utf8
vec T
*/

type color u32//type definition

fn main():i32{//<- entry point

}

//to be figured out

macros

lifetime
slices

function pointers (no closures)