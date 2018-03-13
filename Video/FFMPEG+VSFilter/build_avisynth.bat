REM use `comenv` set cmake
pushd .
@call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86
popd

REM get ffmpeg
pushd .
mkdir ffmpeg32
cd ffmpeg32
set PackageVersion=ffmpeg-3.4.2-win32
bash -c "wget -c https://ffmpeg.zeranoe.com/builds/win32/dev/%PackageVersion%-dev.zip"
bash -c "wget -c https://ffmpeg.zeranoe.com/builds/win32/shared/%PackageVersion%-shared.zip"

bash -c "unzip %PackageVersion%-dev.zip"
bash -c "unzip %PackageVersion%-shared.zip"

rename %PackageVersion%-dev dev
rename %PackageVersion%-shared shared

move dev/include include
move dev/lib lib
move shared/bin bin

rmdir /s/q dev
rmdir /s/q shared

del lib\*.lib
del lib\*.dll.a

cd lib 

for %%f in (*.def) do lib /def:%%f

del *.exp *.def

rename avcodec-57.lib avcodec.lib
rename avdevice-57.lib avdevice.lib
rename avfilter-6.lib avfilter.lib
rename avformat-57.lib avformat.lib
rename avutil-55.lib avutil.lib
rename postproc-54.lib postproc.lib
rename swresample-2.lib swresample.lib
rename swscale-4.lib swscale.lib
popd

REM build xy-VSFilter [Need MFC]
pushd .
bash -c "git clone https://github.com/wurui1994/xy-VSFilter"
cd xy-VSFilter
msbuild /m /p:platform=win32 /p:configuration=release
popd
copy /y xy-VSFilter\bin\lib_15.0\Win32\Release\VSFilter.dll ffmpeg32\bin

REM build AviSynthPlus
pushd .
bash -c "git clone https://github.com/wurui1994/AviSynthPlus"
cd AviSynthPlus
cmake -Bbuild -H. -G "Visual Studio 15 2017"
copy ..\xy-VSFilter\bin\lib_15.0\Win32\strmbaseR.lib build\plugins\DirectShowSource\
cd build
msbuild /m /p:platform=win32 /p:configuration=release "AviSynth+.sln"
popd
xcopy /y /s /i AviSynthPlus\build\Output\ ffmpeg32\bin\

REM build zlib
pushd .
bash -c "git clone https://github.com/wurui1994/zlib"
cd zlib\contrib\vstudio\vc14
msbuild /m /p:platform=win32 /p:configuration=release zlibvc.sln
popd
copy zlib\zlib.h ffmpeg32\include
copy zlib\zconf.h ffmpeg32\include
copy /y zlib\contrib\vstudio\vc14\x86\ZlibStatRelease\zlibstat.lib ffmpeg32\lib\zlib.lib

REM build ffms2
pushd . 
bash -c "git clone https://github.com/wurui1994/ffms2"
cd ffms2\build-msvc
msbuild /m /p:platform=x86 /p:configuration=release ffms2.sln
popd
copy /y ffms2\build-msvc\bin\Win32\Release\ffms2.dll ffmpeg32\bin