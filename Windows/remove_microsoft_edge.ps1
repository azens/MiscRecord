# powershell -c start cmd -verb runas
# Install-Package PSSQLite
# Import-Module PSSQLite
# Invoke-SqliteQuery -Database "C:\ProgramData\Microsoft\Windows\AppRepository\StateRepository-Machine.srd" -Query "select PackageFullName,IsInbox from Package where PackageFullName like '%Microsoft%' "

takeown /f C:\ProgramData\Microsoft\Windows\AppRepository /r /d n | out-null
icacls C:\ProgramData\Microsoft\Windows\AppRepository /grant 'Everyone:(OI)(CI)F' /T /Q
Invoke-SqliteQuery -Database "C:\ProgramData\Microsoft\Windows\AppRepository\StateRepository-Machine.srd" -Query "update Package set IsInbox=0 where PackageFullName like '%Edge%' "

Get-AppxPackage *edge*|Remove-AppxPackage