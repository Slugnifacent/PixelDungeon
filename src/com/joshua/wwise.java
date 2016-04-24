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

    private native String Initialize();

    private native String getMessage();

    private native String ProcessAudio();

    private native String LoadBanks();

    private native String Close();

    boolean initialized;
    public static Context context;

    public wwise() {
        initialized = false;
    }

    public void Init() {
        String temp = Initialize();
        File file = Environment.getExternalStorageDirectory();

        Log.d("DEBUG",file.getAbsolutePath()+ "/Android/obb/com.watabou.pixeldungeon" );
        if (temp != null) {
            Log.d("Debug", temp);

        }
        initialized = true;
        Loadbanks();
    }

    public String Loadbanks() {
        String result = "";
        if(initialized) {
            result = LoadBanks();
        }
        Log.d("Debug", "Loadbanks:" + result);
        return result;
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

    public void Message() {
        String temp = Initialize();
        if (temp != null) {
            Log.d("Debug", temp);
        }
    }

    public Context getNativeActivity()
    {
        return PixelDungeon.instance.getApplicationContext();
    }


}
