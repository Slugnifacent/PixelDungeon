package com.joshua;

import android.util.Log;

/**
 * Created by Joshua on 4/9/2016.
 */
public class wwise {

    static {
        System.loadLibrary("Wwise"); // "myjni.dll" in Windows, "libmyjni.so" in Unixes
    }

    private native String getMessage();

    public wwise()
    {


    }

    public void Message()
    {
        String temp = getMessage();
        if(temp != null) {
            Log.d("Debug",temp);
        }
    }


}
