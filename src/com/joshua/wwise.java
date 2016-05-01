package com.joshua;

import android.os.Environment;
import android.util.Log;
import android.content.Context;
import android.os.Debug;

import com.watabou.pixeldungeon.PixelDungeon;

import java.io.File;

/**
 * Created by Joshua on 4/9/2016.
 */
public class wwise {


    static {
        System.loadLibrary("Wwise"); // "myjni.dll" in Windows, "libmyjni.so" in Unixes
    }

    private native boolean Initialize();
    private native boolean LoadBank(String BankName);
    private native boolean RegisterGameObject(String MonitorName, int GameObjectID);
    private native boolean PostEvent(String EventName, int GameObjectID,boolean Process);
    private native String  ProcessAudio();
    private native String  Close();

    String MonitorName = "Monitor Name";
    int GameObjectID = 100;

    boolean initialized;
    public static Context context;

    public wwise() {
        initialized = false;
    }

    public void Init() {
        initialized = Initialize();
        LoadBank("Init.bnk");
        LoadBank("SoundBank.bnk");
        RegisterGameObject(MonitorName, GameObjectID);
    }

    public void Play(String assetName, boolean looping )
    {
        if(initialized) {
            assetName.replace(".mp3", "");
            String newName = "Play_" + assetName.replace(".mp3", "");
            PostEvent(newName, GameObjectID,false);
        }
    }

    public void Update() {
        if(initialized) {
            ProcessAudio();
        }
    }

    public void Mute() {
        postEvent("Mute_All", GameObjectID,true);
    }

    public void Pause() {
        postEvent("Pause_All", GameObjectID, true);
    }

    public void Resume() {
        postEvent("Resume_All", GameObjectID, true);
    }

    public void Stop() {
        postEvent("Stop_All", GameObjectID, true);
    }

    public void Reset() {
        postEvent("Reset_All", GameObjectID, true);
    }

    private void postEvent(String EventName, int GameObjectID,boolean Process)
    {
        if(initialized) {
            PostEvent(EventName, GameObjectID, Process);
        }
    }

    public void Volume(float Value) {
    }

    public boolean isPlaying() {
        return false;
    }

    public String Exit() {
        initialized = false;
        String result = Close();
        return result;
    }

    public Context getNativeActivity()
    {
        return PixelDungeon.instance.getApplicationContext();
    }


}
