package com.joshua;

/**
 * Created by Joshua on 4/30/2016.
 */

class WwiseEventImpl {
    protected String monitorName;
    protected String eventName;
    protected int gameObjectId;
    protected boolean initialized;

    public WwiseEventImpl()
    {
        this("","",0);
    }

    public WwiseEventImpl(String MonitorName, String EventName, int GameObjectID)
    {
        monitorName = MonitorName;
        eventName = EventName;
        gameObjectId = GameObjectID;
        WwiseNativeWrapper.RegisterGameObject(MonitorName, GameObjectID);
        initialized = true;
    }

    public void Post() {Post(eventName);}

    public void Post(String EventName )
    {
        if(initialized) {
            WwiseNativeWrapper.PostEvent(EventName, gameObjectId, false);
        }
    }

    public void Mute()
    {

    }

    public void Pause() {
        WwiseNativeWrapper.PauseEvent(eventName, gameObjectId, true);
    }

    public void Resume() {
        WwiseNativeWrapper.ResumeEvent(eventName, gameObjectId, true);
    }

    public void Stop() {
        WwiseNativeWrapper.StopEvent(eventName, gameObjectId, true);
    }

    public void Reset() {

    }

    public boolean isPlaying(){
        return false;
    }

    public String GetMonitorName() {
        return monitorName;
    }

    public String GetEventName() {
        return eventName;
    }

    public int GetGameObjectID(){
        return gameObjectId;
    }
}
