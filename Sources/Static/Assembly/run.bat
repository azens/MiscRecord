set masm32=D:\Program\Languages\masm32
set include=%masm32%\include
set lib=%masm32%\lib
set path=%PATH%;%masm32%\bin
ml /c /coff /Cp %1
link /subsystem:windows %~n1.obj
%~n1.exe
pause

