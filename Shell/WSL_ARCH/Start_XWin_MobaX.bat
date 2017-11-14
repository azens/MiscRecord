REM 计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon
REM UserInit修改为:
REM userinit.exe,cmd /c "<Tht Path>\Start_XWin_MobaX.bat"
set PATH=C:\Users\wurui\DOCUME~1\MobaXterm\slash\bin
start XWin  -silent-dup-error -notrayicon -nolisten inet6 -hostintitle +bs  -clipboard -nowgl -multiwindow -noreset :0