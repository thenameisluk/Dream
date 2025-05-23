root<-{object_def}[]

object_def<-{fn_def}

fn_def<-{type_name,"fn","void"} fn_name(args_dec){fn_body};

fn_body<-expr;[]

//to-do
object_def<-{class_def};
object_def<-{struct_def};
object_def<-{type_def};

object_def<-{var_dec};

args<-expr*,expr*[]

var_dec<-{type_name} {value_dec}*,{value_dev}*[];
var_dec<-{type_name}[*num*] name{arr_dev};

arr_dec//to-finish

value_dec<-name(args[])
value_dec<-name = expr
value_dec<-name = type_name(*args[]*)

expr<-var_dec

fn_call<-fn_name(args[])

expr<-fn_call