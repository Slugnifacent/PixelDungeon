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
    private native boolean PostEvent(String EventName, int GameObjectID);

    private native String ProcessAudio();

    private native String Close();

    boolean initialized;
    public static Context context;

    public wwise() {
        initialized = false;
    }

    public void Init() {
        initialized = Initialize();
        LoadBank("Init.bnk");
        LoadBank("SoundBank.bnk");
        String MonitorName = "Monitor Name";
        int GameObjectID = 100;

        RegisterGameObject(MonitorName, GameObjectID);
        PostEvent("Play_Game", GameObjectID);
    }

    public String Loadbanks() {
        return "";
    }

    public String Update() {
        String result = "";
        if(initialized) {
            result = ProcessAudio();
        }
        return result;
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
