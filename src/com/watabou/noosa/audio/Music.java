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

import java.io.IOException;

import com.joshua.MusicObject;
import com.watabou.noosa.Game;

import android.content.res.AssetFileDescriptor;
import android.media.AudioManager;
import android.media.MediaPlayer;

import com.joshua.wwise;
import com.joshua.MusicObject;

public enum Music implements MediaPlayer.OnPreparedListener, MediaPlayer.OnErrorListener {
	
	INSTANCE;
	
	private MediaPlayer player;
	String songplaying;
	private String lastPlayed;
	private boolean lastLooping;
	private MusicObject music;
	
	private boolean enabled = false;

	public static wwise wise;

	public void Initialize()
	{
		wise = new wwise();
		wise.Init();
		songplaying="";
		music = new MusicObject("Current Music",200);
	}

	public void Update()
	{
		wise.Update();
	}


	public void Exit() {
		wise.Exit();
	}


	public void play( String assetName, boolean looping ) {
		if (assetName == null) return;

		lastPlayed = assetName;
		lastLooping = looping;

		if(enabled) {
			if (wise != null) {
				if (assetName.compareTo(songplaying) != 0) {
					wise.Stop();
					wise.Play(assetName, looping);
					songplaying = assetName;
				}
			}
		}
	}
	
	public void mute() {
		lastPlayed = null;
		if(wise != null) wise.Mute();
	}

	@Override
	public void onPrepared( MediaPlayer player ) {

	}
	
	@Override
	public boolean onError( MediaPlayer mp, int what, int extra ) {
		if (player != null) {
			player.release();
			player = null;
		}
		return true;
	}
	
	public void pause() {
		if(wise != null) wise.Pause();
	}
	
	public void resume() {
		if(wise != null) wise.Resume();
	}
	
	public void stop() {

		if(wise != null){
			wise.Stop();
		}
	}
	
	public void volume( float value ) {
		if(wise != null) wise.Volume(value);
	}
	
	public boolean isPlaying() {
		return wise != null;
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
