# For macOS
# dsymutil file -> file.dSYM
# dump_syms file.dSYM
xcodebuild dump_syms.xcodeproj -project
dump_syms file > file.sym

# For Windows
src\tools\windows\refresh_binaries.bat
dump_syms file.pdb > file.sym
# or dump_syms file.exe > file.sym

minidump_stackwalk file.dmp file.sym > info.txt 2>&1
find "file.pdb" info.txt
# MacOS
# file.sym/SubtitleClient/C644C83DD49C3403BCDA79C869398B840/SubtitleClient.sym
mkdir -p file.pdb/290C132D8C2C4B9E8172C148D94140361/
copy file.sym file.pdb/290C132D8C2C4B9E8172C148D94140361/
mindump_stackwalk