path=/sdcard/Android/obb/com.watabou.pixeldungeon/
mkdir SoundBank
adb shell "mkdir $path"
find . -name "*.bnk" -exec cp {} ./SoundBank/ \; adb push {} /sdcard/$path \;
