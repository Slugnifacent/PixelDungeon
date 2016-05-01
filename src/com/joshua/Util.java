package com.joshua;

/**
 * Created by Joshua on 5/1/2016.
 */
public class Util {
    public static String ConformEventNameFromMP3(String FileName)
    {
        FileName.replace(".mp3", "");
        return "Play_" + FileName.replace(".mp3", "");
    }
}
