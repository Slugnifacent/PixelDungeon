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

import java.util.HashMap;
import java.util.LinkedList;
import android.media.SoundPool;

import com.joshua.Util;
import com.joshua.Wwise;

public enum Sample implements SoundPool.OnLoadCompleteListener {
	
	INSTANCE;
//	public static final int MAX_STREAMS = 8;
//	protected SoundPool pool =
//		new SoundPool( MAX_STREAMS, AudioManager.STREAM_MUSIC, 0 );
	private LinkedList<String> loadingQueue = new LinkedList<String>();
	protected HashMap<Object, Integer> ids = new HashMap<Object, Integer>();
	private boolean enabled = false;

	public void reset() {
		Wwise.GetInstance().Reset();
	}
	
	public void pause() {
		Wwise.GetInstance().Pause();
	}
	
	public void resume() {
		Wwise.GetInstance().Resume();
	}

	public void load( String... assets ) {
		for (String asset : assets) {
			loadingQueue.add( asset );
		}
	}
	
	private void loadNext() {
//		final String asset = loadingQueue.poll();
//		if (asset != null) {
//			if (!ids.containsKey( asset )) {
//				try {
//					pool.setOnLoadCompleteListener( new SoundPool.OnLoadCompleteListener() {
//						@Override
//						public void onLoadComplete(SoundPool soundPool, int sampleId, int status) {
//							loadNext();
//						}
//					} );
//
//					AssetManager manager = Game.instance.getAssets();
//					AssetFileDescriptor fd = manager.openFd( asset );
//					int streamID = pool.load( fd, 1 ) ;
//					ids.put( asset, streamID );
//					fd.close();
//				} catch (IOException e) {
//					loadNext();
//				} catch (NullPointerException e) {
//					// Do nothing (stop loading sounds)
//				}
//			} else {
//				loadNext();
//			}
//		}
	}
	
	public void unload( Object src ) {
		if (ids.containsKey( src )) {
			//pool.unload( ids.get( src ) );
			ids.remove( src );
		}
	}
	
	public int play( Object id ) {
		return play( id, 1, 1, 1 );
	}
	
	public int play( Object id, float volume ) {
		return play( id, volume, volume, 1 );
	}
	
	public int play( Object id, float leftVolume, float rightVolume, float rate ) {
		if(isEnabled()) {
			Wwise.GetInstance().Post(
					Util.ConformEventNameFromMP3(
							id.toString()
					)
			);
		}
		return 0;
	}
	
	public void enable( boolean value ) {
		enabled = value;
	}
	
	public boolean isEnabled() {
		return enabled;
	}
	
	@Override
	public void onLoadComplete( SoundPool soundPool, int sampleId, int status ) {
	}
}
