# list dshow devices
ffplay -f dshow -i dummy -list_devices true 2>&1|findstr dshow
# Camera with dshow
ffplay -f dshow -i video="Camera"
# Screen Record use gdigrab
ffplay -f gdigrab -i desktop -video_size 1280x720
# render subtitle without video
ffplay -f lavfi -i color=s=1289x720 -vf subtitles=test.ass
ffplay -f lavfi -i nullsrc=s=1280x720,geq=r=0:g=0:b=0 -vf subtitles=test.ass
ffplay -f lavfi -i nullsrc=s=1280x720,geq=random(1)*255:128:128 -vf subtitles=test.ass
# set video time for subtitle
ffplay -f lavfi -i "color=size=1280x720,trim=6:60" -vf subtitles=test.ass
# use AviSynth
ffplay -i test.avs
ffplay -f avisynth test.avs