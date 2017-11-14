Set ws = CreateObject("Wscript.Shell")
ws.run "cmd /c bash -c 'DISPLAY=:0 thunar'",vbhide 
' 快捷方式
' %windir%\system32\mshta.exe vbscript:createobject("wscript.shell").run("bash -c 'DISPLAY=:0 thunar'",0)(window.close)