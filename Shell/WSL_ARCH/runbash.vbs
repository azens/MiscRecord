Set ws = CreateObject("Wscript.Shell")
ws.run "cmd /c bash -c 'DISPLAY=:0 thunar'",vbhide 
' 快捷方式
' %windir%\system32\mshta.exe vbscript:createobject("wscript.shell").run("bash -c 'DISPLAY=:0 thunar'",0)(window.close)
' Manjaro
'%windir%\system32\mshta.exe vbscript:createobject("wscript.shell").run("cmd /c start C:\Users\wurui\Documents\MobaXterm\slash\bin\XWin.exe & bash -c 'export LANG=zh_CN.UTF-8 && export LC_ALL=zh_CN.UTF-8 && export DISPLAY=:0 && startxfce4 '",0)(window.close)