set masm32=D:\Program\Languages\masm32
set include=%masm32%\include
set lib=%masm32%\lib
set path=%PATH%;%masm32%\bin
ml /DDOS /Zm /c %1
doslnk %~n1.obj,"","","",""
dosbox -c cls %~n1.exe
del *.obj *.exe