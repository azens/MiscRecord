' C:\Users\wurui\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
set ws=WScript.CreateObject("WScript.Shell")
CurrentPath =  createobject("Scripting.FileSystemObject").GetFolder(".").Path & "\Start_XWin_MobaX.bat" 
Command="cmd /c " &  Chr(34) & CurrentPath &  Chr(34)
' msgbox Command 
ws.Run Command,0