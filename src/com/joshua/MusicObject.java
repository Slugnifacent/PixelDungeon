package com.joshua;

import com.watabou.noosa.Game;

/**
 * Created by Joshua on 4/30/2016.
 */
public class MusicObject {
    String monitorName;
    int gameObjectID;

    public MusicObject(String MonitorName, int GameObjectID)
    {
        monitorName = MonitorName;
        gameObjectID = GameObjectID;
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



    public String GetMonitorName()
    {
        return monitorName;
    }

    public void SetMonitorName(String MonitorName)
    {
        monitorName = MonitorName;
    }

    public int GetGameObjectID()
    {
        return gameObjectID;
    }

    public void SetGameObjectID(int GameObjectID)
    {
        gameObjectID = GameObjectID;
    }
}
