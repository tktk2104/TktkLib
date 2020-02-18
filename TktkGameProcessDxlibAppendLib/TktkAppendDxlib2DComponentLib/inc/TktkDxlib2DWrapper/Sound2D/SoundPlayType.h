#ifndef SOUND_PLAY_TYPE_H_
#define SOUND_PLAY_TYPE_H_

namespace tktk
{
	enum SoundPlayType
	{
		SOUND_PLAY_TYPE_NORMAL		= 0,	// ノーマル再生（処理が止まります）
		SOUND_PLAY_TYPE_BACKGROUND	= 1,	// バックグラウンド再生
		SOUND_PLAY_TYPE_LOOP		= 3,	// ループ再生
	};
}
#endif // !SOUND_PLAY_TYPE_H_