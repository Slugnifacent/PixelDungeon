package com.joshua;

/**
 * Created by Joshua on 4/30/2016.
 */
public class Wwise extends WwiseEventImpl {
    private static Wwise wwise;

    private Wwise() {
    }

    public static Wwise GetInstance()
    {
        if(wwise == null)
        {
            wwise = new Wwise();
        }
        return wwise;
    }

    public void Init() {
        initialized = WwiseNativeWrapper.Initialize();
        monitorName = "Wwise";
        gameObjectId = 100;
        WwiseNativeWrapper.RegisterGameObject(monitorName, gameObjectId);
    }

    public void LoadBank(String BankName)
    {
        WwiseNativeWrapper.LoadBank(BankName);
    }

    public void Update() {
        if(initialized) {
            WwiseNativeWrapper.ProcessAudio();
        }
    }

    public void Mute() {
        postEvent("Mute_All", gameObjectId,true);
    }

    public void Pause() {
        postEvent("Pause_All", gameObjectId, true);
    }

    public void Resume() {
        postEvent("Resume_All", gameObjectId, true);
    }

    public void Stop() {
        postEvent("Stop_All", gameObjectId, true);
    }

    public void Reset() {
        postEvent("Reset_All", gameObjectId, true);
    }

    private void postEvent(String EventName, int GameObjectID,boolean Process)
    {
        if(initialized) {
            WwiseNativeWrapper.PostEvent(EventName, GameObjectID, Process);
        }
    }

    public void Volume(float Value){

    }

    public boolean isPlaying(){
        return false;
    }


    public String Exit() {
        initialized = false;
        String result = WwiseNativeWrapper.Close();
        return result;
    }
}
