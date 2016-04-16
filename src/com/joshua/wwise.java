package com.joshua;

import android.util.Log;

/**
 * Created by Joshua on 4/9/2016.
 */
public class wwise {

    static {
        System.loadLibrary("Wwise"); // "myjni.dll" in Windows, "libmyjni.so" in Unixes
    }

    private native String Initialize();

    private native String getMessage();

    private native String ProcessAudio();

    private native String Close();

    boolean initialized;

    public wwise() {
        initialized = false;

    }

    public void Init() {
        String temp = Initialize();
        if (temp != null) {
            Log.d("Debug", temp);
        }
        initialized = true;
    }

    public string Update() {
        string result = ProcessAudio();
        return result;
    }

    public string Exit() {
        initialized = false;
        string result = Close();
        return result;
    }

    public void Message() {
        String temp = Initialize();
        if (temp != null) {
            Log.d("Debug", temp);
        }
    }


}
