# powershell -c start cmd -verb runas
# Install-Package PSSQLite
# Invoke-SqliteQuery -Database "C:\ProgramData\Microsoft\Windows\AppRepository\StateRepository-Machine.srd" -Query "select PackageFullName,IsInbox from Package where PackageFullName like '%Microsoft%' "

takeown /f C:\ProgramData\Microsoft\Windows\AppRepository /r /d n | out-null
icacls C:\ProgramData\Microsoft\Windows\AppRepository /grant 'Everyone:(OI)(CI)F' /T /Q
Import-Module PSSQLite
Invoke-SqliteQuery -Database "C:\ProgramData\Microsoft\Windows\AppRepository\StateRepository-Machine.srd" -Query "update set IsInbox=1 from Package where PackageFullName like '%Edge%' "

Get-AppxPackage *edge*|Remove-AppxPackage