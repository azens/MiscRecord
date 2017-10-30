REM git.exe clone http://repo.or.cz/tinycc.git 
@call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\vcvars32.bat""
@mkdir tinycc\tcc-0.9.27
@cd tinycc\win32
@call build-tcc.bat -c cl -t 32 -i ..\tcc-0.9.27 -b ..\tcc-0.9.27\tools
@cd ..
@pause
@cls
REM ..\tcc\tcc.exe -DONE_SOURCE -DTCC_TARGET_PE -run tcc.c