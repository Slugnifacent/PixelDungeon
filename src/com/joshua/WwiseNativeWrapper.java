package com.joshua;

import android.content.Context;
import com.watabou.pixeldungeon.PixelDungeon;

/**
 * Created by Joshua on 4/30/2016.
 */
public class WwiseNativeWrapper {

    static {
        System.loadLibrary("Wwise"); // "myjni.dll" in Windows, "libmyjni.so" in Unixes
    }

    public native static boolean Initialize();
    public native static boolean LoadBank(String BankName);
    public native static boolean RegisterGameObject(String MonitorName, int GameObjectID);
    public native static boolean PostEvent(String EventName, int GameObjectID,boolean Process);
    public native static boolean StopEvent(String EventName, int GameObjectID,boolean Process);
    public native static boolean PauseEvent(String EventName, int GameObjectID,boolean Process);
    public native static boolean ResumeEvent(String EventName, int GameObjectID,boolean Process);
    public native static String  ProcessAudio();
    public native static String  Close();

    public static Context getNativeActivity()
    {
        return PixelDungeon.instance.getApplicationContext();
    }
}
