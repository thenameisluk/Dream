import {} from "std"//no header files

use namespace::element//for direct access by name

export name{//namespaces
    class e{//class
        //members private by default
        
        pub i32 sth;
        //or
        prv u8 a;//alternative
    pub:
        e()//constructor
        ~e()//destructor
        //methods
        operator++(){//no need for void (look class below for example with void)
            this.sth++;
        }//operator overloading
        i32 getSth(){
            if(false)
                ret sth;//
            
            this.sth//last value is also return statement
        }
    };
    e someE = e(...)//create e instance in place

    struct e{//stuct
        //members public by default
        //no constructors
        //but methods, static and not static
    };

    e someE = e{...}//create e instance in place

    

    i32 fun(i8 uwu){

    }//no need for ; after }

    //templates
    T fun<T>(T a){
        ret a;
    }

    class e<T>{//class
        
        pub sth:T;
        
        e()//constructor
        ~e()//destructor
        //methods
        
        void operator++(){//no need for void
            this.sth++;
        }//operator overloading
        
        T getSth(){
            ret sth;
        }
    };
};

//a comment
#also a comment (for #! support)
/*
this too
*/