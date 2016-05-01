package com.joshua;

/**
 * Created by Joshua on 4/30/2016.
 */
public class WwiseEvent extends WwiseEventImpl {
    public WwiseEvent(String MonitorName, String EventName,int GameObjectID)
    {
        super(MonitorName,EventName,GameObjectID);
    }

    public void SetMonitorName(String MonitorName)
    {
        monitorName = MonitorName;
    }

    public void SetEventName(String EventName)
    {
        eventName = EventName;
    }
}
