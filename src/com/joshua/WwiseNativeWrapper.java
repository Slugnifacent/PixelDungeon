package com.joshua;

/**
 * Created by Joshua on 4/30/2016.
 */
public class WwiseNativeWrapper {
    private native boolean Initialize();
    private native boolean LoadBank(String BankName);
    private native boolean RegisterGameObject(String MonitorName, int GameObjectID);
    private native boolean PostEvent(String EventName, int GameObjectID,boolean Process);
    private native String  ProcessAudio();
    private native String  Close();

}
