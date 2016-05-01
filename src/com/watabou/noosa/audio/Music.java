/*
 * Copyright (C) 2012-2015 Oleg Dolya
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

package com.watabou.noosa.audio;

import com.joshua.Util;
import com.joshua.Wwise;
import com.joshua.WwiseEvent;

import android.media.MediaPlayer;

public enum Music implements MediaPlayer.OnPreparedListener, MediaPlayer.OnErrorListener {
	
	INSTANCE;

	String songplaying;
	private String lastPlayed;
	private boolean lastLooping;

	private boolean enabled = false;
	WwiseEvent OST;

	public void Initialize()
	{
		Wwise.GetInstance().Init();
		Wwise.GetInstance().LoadBank("Init.bnk");
		Wwise.GetInstance().LoadBank("SoundBank.bnk");
		OST = new WwiseEvent("OST","",200);
		songplaying="";
	}

	public void Update()
	{
		Wwise.GetInstance().Update();
	}


	public void Exit() {
		Wwise.GetInstance().Exit();
	}


	public void play( String assetName, boolean looping ) {
		if (assetName == null) return;

		lastPlayed = assetName;
		lastLooping = looping;

		if(enabled) {
			if (assetName.compareTo(songplaying) != 0) {
				OST.Stop();
				OST.SetEventName(Util.ConformEventNameFromMP3(assetName));
				OST.Post();
				songplaying = assetName;
			}
		}
	}
	
	public void mute() {
		lastPlayed = null;
		OST.Mute();
	}

	@Override
	public void onPrepared( MediaPlayer player ) {

	}
	
	@Override
	public boolean onError( MediaPlayer mp, int what, int extra ) {
		return true;
	}
	
	public void pause() {
		OST.Pause();
	}
	
	public void resume() {
		OST.Resume();
	}
	
	public void stop() {
		OST.Stop();
	}
	
	public void volume( float value ) {
		Wwise.GetInstance().Volume(value);
	}
	
	public boolean isPlaying() {
		return OST.isPlaying();
	}
	
	public void enable( boolean value ) {
		enabled = value;
		if (!value) {
			stop();
			songplaying = "";
		} else {
			play(lastPlayed, lastLooping);
		}
	}
	
	public boolean isEnabled() {
		return enabled;
	}

}
