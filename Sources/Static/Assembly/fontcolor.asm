.386
.model flat,stdcall
include windows.inc
include kernel32.inc
include user32.inc
include gdi32.inc
includelib kernel32.lib
includelib user32.lib
includelib gdi32.lib
WinMain proto :DWORD,:DWORD,:DWORD,:DWORD 
.DATA 
ClassName db "SimpleWinClass",0 
AppName  db "Our First Window",0 
OurText  db "Hello World!",0 
FontName db "Consolas",0
.DATA? 
hInstance HINSTANCE ? 
CommandLine LPSTR ? 
hfont HFONT ?

RGB macro red,green,blue 
        xor eax,eax 
        mov ah,blue 
        shl eax,8 
        mov ah,green 
        mov al,red 
endm 

.CODE 
start: 
    invoke GetModuleHandle, NULL 
    mov    hInstance,eax 
    invoke GetCommandLine
    mov CommandLine,eax
    invoke WinMain, hInstance,NULL,CommandLine, SW_SHOWDEFAULT 
    invoke ExitProcess,eax 

WinMain proc hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:DWORD 
    LOCAL wc:WNDCLASSEX 
    LOCAL msg:MSG 
    LOCAL hwnd:HWND 
    mov   wc.cbSize,SIZEOF WNDCLASSEX 
    mov   wc.style, CS_HREDRAW or CS_VREDRAW 
    mov   wc.lpfnWndProc, OFFSET WndProc 
    mov   wc.cbClsExtra,NULL 
    mov   wc.cbWndExtra,NULL 
    push  hInst 
    pop   wc.hInstance 
    mov   wc.hbrBackground,COLOR_WINDOW+1 
    mov   wc.lpszMenuName,NULL 
    mov   wc.lpszClassName,OFFSET ClassName 
    invoke LoadIcon,NULL,IDI_APPLICATION 
    mov   wc.hIcon,eax 
    mov   wc.hIconSm,eax 
    invoke LoadCursor,NULL,IDC_ARROW 
    mov   wc.hCursor,eax 
    invoke RegisterClassEx, addr wc 
    invoke CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,\ 
           WS_OVERLAPPEDWINDOW,350,\ 
           120,640,480,NULL,NULL,\ 
           hInst,NULL 
    mov   hwnd,eax 
    invoke ShowWindow, hwnd,SW_SHOWNORMAL 
    invoke UpdateWindow, hwnd 
        .WHILE TRUE 
                invoke GetMessage, ADDR msg,NULL,0,0 
                .BREAK .IF (!eax) 
                invoke TranslateMessage, ADDR msg 
                invoke DispatchMessage, ADDR msg 
        .ENDW 
        mov     eax,msg.wParam 
        ret 
WinMain endp 

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM 
    LOCAL hdc:HDC 
    LOCAL ps:PAINTSTRUCT 
    LOCAL rect:RECT 
    
    .IF uMsg==WM_CREATE
    	invoke CreateFont,100,0,0,0,0,1,0,0,1,0,0,0,0,ADDR FontName
	mov hfont,eax
    .ELSEIF uMsg==WM_DESTROY 
        invoke PostQuitMessage,NULL 
    .ELSEIF uMsg==WM_PAINT 
        invoke BeginPaint,hWnd, ADDR ps 
        mov    hdc,eax
        invoke SelectObject,hdc,hfont
        RGB 0,0,255
        invoke SetTextColor,hdc,eax
        RGB 128,128,128
	invoke SetBkColor,hdc,eax
        invoke GetClientRect,hWnd, ADDR rect 
        invoke DrawText, hdc,ADDR OurText,-1, ADDR rect, \ 
                DT_SINGLELINE or DT_CENTER or DT_VCENTER 
        invoke EndPaint,hWnd, ADDR ps 
    .ELSE 
        invoke DefWindowProc,hWnd,uMsg,wParam,lParam 
        ret 
    .ENDIF 
    xor   eax, eax 
    ret 
WndProc endp 
end start 


