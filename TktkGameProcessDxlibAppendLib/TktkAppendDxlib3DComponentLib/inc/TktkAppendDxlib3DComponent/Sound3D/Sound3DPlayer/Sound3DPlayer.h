#ifndef SOUND_3D_PLAYER_H_
#define SOUND_3D_PLAYER_H_

#include <memory>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Sound2D/SoundPlayType.h>

namespace tktk
{
	// ３次元サウンド再生コンポーネント
	// 【前提コンポーネント：Transform3D】
	class Sound3DPlayer
		: public ComponentBase
	{
	public:

		Sound3DPlayer(
			bool startToPlay,				// 自身の生成後すぐに再生するか？
			int playSoundId,				// 再生するサウンドのID
			SoundPlayType soundPlayType,	// 再生方法の種類
			bool playFromTop,				// 再再生の時最初から再生するか？
			bool useDefaltPlayRadius,		// デフォルトの再生半径を使用するか？
			bool useDefaltPlayVelocity,		// デフォルトのサウンドの発生源の移動速度を使用するか？
			bool useDefaltVolumeRate,		// デフォルトのボリュームを使用するか？（割合）
			float playRadius,				// サウンドが聞こえる半径
			const Vector3& playVelocity,	// サウンドの発生源の移動速度
			float volumeRate				// サウンド再生で使用するボリューム
		);

	public:

		void start();
		void update();
		void onDestroy() const;

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

		// サウンドが聞こえる半径を再設定
		void setPlayRadius(float playRadius);
		// デフォルトのサウンドが聞こえる半径を使用する
		void useDefaltPlayRadius();

		// サウンドの発生源の移動速度を再設定
		void setPlayVelocity(const Vector3& playVelocity);
		// デフォルトのサウンドの発生源の移動速度を使用する
		void useDefaltPlayVelocity();

		// サウンド再生で使用するボリュームを再設定
		void setVolumeRate(float volumeRate);
		// デフォルトのボリュームを使用する
		void useDefaltVolumeRate();

	private:

		std::weak_ptr<Transform3D> m_transform3D;
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
#endif // !SOUND_3D_PLAYER_H_
