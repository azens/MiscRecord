section .data
    hello db "hello world!", 0xa, 0

section .text

global _main;  // 说明程序的入口点,这个可以随便取任意合法的标号,但要调用c语言的库函数还是要用main,否则链接的时候会提示找不到main

_main:
    push dword hello  ;; //c语言中函数的参数的传递都是放在栈中的
    extern _printf
    call _printf                 ; // 调用外部函数的作用
    add esp, byte 4      ;; // 事实上这是一个出栈动作,以让程序找到正确的地址进行返回
    ret