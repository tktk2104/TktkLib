#ifndef SOUND_2D_PLAYER_H_
#define SOUND_2D_PLAYER_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../../../TktkDxlib2DWrapper/Sound2D/SoundPlayType.h"

namespace tktk
{
	// サウンド再生コンポーネント
	class Sound2DPlayer
		: public ComponentBase
	{
	public:

		Sound2DPlayer(
			bool startToPlay,				// 自身の生成後すぐに再生するか？
			int playSoundId,				// 再生するサウンドのID
			SoundPlayType soundPlayType,	// 再生方法の種類
			bool playFromTop,				// 再再生の時最初から再生するか？
			bool useDefaltPanPalRate,		// デフォルトのパンを使用するか？（割合）
			bool useDefaltVolumeRate,		// デフォルトのボリュームを使用するか？（割合）
			float panPalRate,				// サウンド再生で使用するパン
			float volumeRate				// サウンド再生で使用するボリューム
		);

	public:

		void start();

	public:

		// サウンドを再生する
		void playSound();
		// サウンドを停止する
		void stopSound();

		// サウンドが再生中か？
		bool isPlaySound();

		// 再生するサウンドのIDを再設定
		void setPlaySoundId(int playSoundId);

		// 再生方法の種類を再設定
		void setSoundPlayType(SoundPlayType soundPlayType);

		// 再再生の時最初から再生するかを再設定
		void setPlayFromTop(bool playFromTop);

		// サウンド再生で使用するパンを再設定
		void setPanPalRate(float panPalRate);
		// デフォルトのパンを使用する
		void useDefaltPanPalRate();

		// サウンド再生で使用するボリュームを再設定
		void setVolumeRate(float volumeRate);
		// デフォルトのボリュームを使用する
		void useDefaltVolumeRate();

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
#endif // !SOUND_2D_PLAYER_H_