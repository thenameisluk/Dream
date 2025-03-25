import {} from "std"//no header files

use namespace::element//for direct access by name

export name{//namespaces
    class e{//class
        //members private by default
        
        pub sth:i32;
        //or
        prv u8 a;//alternative
        
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

    

    fun(uwu:i8):i32{

    }

    //templates
    fun<T>(a:T):T{
        ret a;
    }

    class e<T>{//class
        
        pub sth:T;
        
        e()//constructor
        ~e()//destructor
        //methods
        
        operator++(){//no need for void
            this.sth++;
        }//operator overloading
        
        getSth():T(){
            ret sth;
        }
    };
};