#ifndef SOUND_3D_PLAYER_MAKER_H_
#define SOUND_3D_PLAYER_MAKER_H_

#include <TktkMath/Vector3.h>
#include "Sound3DPlayer.h"

namespace tktk
{
	class Sound3DPlayerMaker
	{
	public:

		// インスタンス生成開始
		static Sound3DPlayerMaker& makeStart();

	public:

		// 作成する
		Sound3DPlayer* create();

		// 自身の生成後すぐに再生するかを設定
		Sound3DPlayerMaker& startToPlay(bool value);

		// 再生するサウンドのIDを設定
		Sound3DPlayerMaker& playSoundId(int value);

		// 再生方法の種類を設定
		Sound3DPlayerMaker& soundPlayType(SoundPlayType value);

		// 再再生の時最初から再生するかを設定
		Sound3DPlayerMaker& playFromTop(bool value);

		// サウンドが聞こえる半径を設定
		Sound3DPlayerMaker& playRadius(float value);

		// サウンドの発生源の移動速度を再設定
		Sound3DPlayerMaker& playVelocity(const Vector3& value);

		// サウンド再生で使用するボリュームを設定
		Sound3DPlayerMaker& volumeRate(float value);

	private:

		// 自身のポインタ
		static Sound3DPlayerMaker m_self;

	private:

		bool m_startToPlay{ true };
		int m_playSoundId{ -1 };
		SoundPlayType m_soundPlayType{ SoundPlayType::SOUND_PLAY_TYPE_BACKGROUND };
		bool m_playFromTop{ true };
		bool m_useDefaltPlayRadius{ true };
		bool m_useDefaltPlayVelocity{ true };
		bool m_useDefaltVolumeRate{ true };
		float m_playRadius{ 1000.0f };
		Vector3 m_playVelocity{ Vector3::zero };
		float m_volumeRate{ 1.0f };
	};
}
#endif // !SOUND_3D_PLAYER_MAKER_H_