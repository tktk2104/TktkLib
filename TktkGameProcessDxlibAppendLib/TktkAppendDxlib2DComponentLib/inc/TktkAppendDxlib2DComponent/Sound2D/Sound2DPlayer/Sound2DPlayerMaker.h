#ifndef SOUND_2D_PLAYER_MAKER_H_
#define SOUND_2D_PLAYER_MAKER_H_

#include <memory>
#include "Sound2DPlayer.h"

namespace tktk
{
	class Sound2DPlayerMaker
	{
	public:

		// インスタンス作成開始
		static Sound2DPlayerMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<Sound2DPlayer> create();

		// 自身の生成後すぐに再生するかを設定
		Sound2DPlayerMaker& startToPlay(bool value);

		// 再生するサウンドのIDを設定
		Sound2DPlayerMaker& playSoundId(int value);

		// 再生方法の種類を設定
		Sound2DPlayerMaker& soundPlayType(SoundPlayType value);

		// 再再生の時最初から再生するかを設定
		Sound2DPlayerMaker& playFromTop(bool value);

		// サウンド再生で使用するパンを設定
		Sound2DPlayerMaker& panPalRate(float value);

		// サウンド再生で使用するボリュームを設定
		Sound2DPlayerMaker& volumeRate(float value);

	private:

		// 自身のポインタ
		static Sound2DPlayerMaker m_self;

	private:

		bool m_startToPlay{ true };
		int m_playSoundId{ -1 };
		SoundPlayType m_soundPlayType{ SoundPlayType::SOUND_PLAY_TYPE_BACKGROUND };
		bool m_playFromTop{ true };
		bool m_useDefaltPanPalRate{ true };
		bool m_useDefaltVolumeRate{ true };
		float m_panPalRate{ 0.5f };
		float m_volumeRate{ 1.0f };
	};
}
#endif // !SOUND_2D_PLAYER_MAKER_H_