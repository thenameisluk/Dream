//is a value
i32 enum e{
    a,
    b = 1,//can specify
    c
}

//diffrent possible values
variant e{
    a:sth,
    b,
    none
}


//variant
switch e{
    a(e):{

    }
    b:fun()//function
    _:
}
//enum
switch (e){//() are optional
    a,b:{//combine

    },
    c:,//nothing
    _:{//other (optional if all covered)

    }
}

//the sack 
//ties const properties to specyfic name and value
//without need for combining enum with arrays

//type specification is optional
i32 sack animal(str name,i32 luck){
    cat:{"cat",100}=0,//=optional
    dog:{"dog",40}//static properties
}

fun(animal a){//a is an int but can be used to refference it's properties
    call(a.name)

    if(a==animal::cat){
        do(a.name);
        //same thing
        do(animal::cat.name);
    }else{
        do(animal::dog.luck);
    }
}

sack key(ascii:i32,name:str,c:char){
    a:{65,"A",'A'},
    b:{66,"B",'A'},
    ...
    space:{32,"space",' '},
}

//can be treaded as enum with extra steps
match (e){
    a,b:{//combine
        e.ascii;
    },
    _:{//other (optional if all covered)

    }
}