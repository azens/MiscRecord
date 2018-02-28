# For macOS
# dsymutil file -> file.dSYM
# dump_syms file.dSYM
xcodebuild dump_syms.xcodeproj -project
dump_syms file > file.sym

# For Windows
src\tools\windows\refresh_binaries.bat
dump_syms file.pdb > file.sym
# or dump_syms file.exe > file.sym

minidump_stackwalk file.dmp . > info.txt 2>&1

# MacOS
# file.sym/SubtitleClient/C644C83DD49C3403BCDA79C869398B840/SubtitleClient.sym
s=$(grep "file.pdb|" info.txt | cut -d '|' -f 2|tr -d '\r')
mkdir -p file.pdb/$s
cp file.sym file.pdb/$/
minidump_stackwalk file.dmp . > info.txt