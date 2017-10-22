let fib_help f= match f with
      [|a;b|]->[|b;a+b|]
     |_->raise(Invalid_argument "f must be a int array");;

let rec fib n = match n with
        1->[|0;1|]
       |n->fib_help( fib(n-1) );;

let _=
     Printf.printf "%d\n" (fib 40).(1);
exit 0