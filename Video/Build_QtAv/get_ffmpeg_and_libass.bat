@echo off
set PackageVersion=ffmpeg-20171204-71421f3-win32
REM bash -c "wget https://github.com/ShiftMediaProject/FFmpeg/releases/download/3.3.5.r89114/libffmpeg_3.3.5.r89114_msvc14.zip"
bash -c "wget https://ffmpeg.zeranoe.com/builds/win32/dev/%PackageVersion%-dev.zip"
bash -c "wget https://ffmpeg.zeranoe.com/builds/win32/shared/%PackageVersion%-shared.zip"

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
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"

pushd %cd%
cd lib 

for %%f in (*.def) do lib /def:%%f

del *.exp *.def

rename avcodec-58.lib avcodec.lib
rename avdevice-58.lib avdevice.lib
rename avfilter-7.lib avfilter.lib
rename avformat-58.lib avformat.lib
rename avutil-56.lib avutil.lib
rename postproc-55.lib postproc.lib
rename swresample-3.lib swresample.lib
rename swscale-5.lib swscale.lib
popd

pushd %cd%
cd include\libavfilter
echo #ifndef AVFILTER_AVFILTERGRAPH_H > avfiltergraph.h
echo #define AVFILTER_AVFILTERGRAPH_H >> avfiltergraph.h
echo #include "avfilter.h" >> avfiltergraph.h
echo #include "libavutil/log.h" >> avfiltergraph.h
echo #endif /* AVFILTER_AVFILTERGRAPH_H */ >> avfiltergraph.h
popd

bash -c "wget https://github.com/ShiftMediaProject/libass/releases/download/0.14.0/libass_0.14.0_msvc14.zip"

bash -c "unzip libass_0.14.0_msvc14.zip"

copy bin\x86\ass.dll bin\ass.dll
copy lib\x86\ass.lib lib\ass.lib
rmdir /s/q bin\x86
rmdir /s/q bin\x64
rmdir /s/q lib\x86
rmdir /s/q lib\x64
rmdir /s/q licenses

del *.zip
