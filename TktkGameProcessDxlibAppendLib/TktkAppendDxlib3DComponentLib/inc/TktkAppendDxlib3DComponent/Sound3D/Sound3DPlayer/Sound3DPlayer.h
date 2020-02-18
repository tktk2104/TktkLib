#ifndef SOUND_3D_PLAYER_H_
#define SOUND_3D_PLAYER_H_

#include <memory>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Sound2D/SoundPlayType.h>

namespace tktk
{
	// �R�����T�E���h�Đ��R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform3D�z
	class Sound3DPlayer
		: public ComponentBase
	{
	public:

		Sound3DPlayer(
			bool startToPlay,				// ���g�̐����シ���ɍĐ����邩�H
			int playSoundId,				// �Đ�����T�E���h��ID
			SoundPlayType soundPlayType,	// �Đ����@�̎��
			bool playFromTop,				// �čĐ��̎��ŏ�����Đ����邩�H
			bool useDefaltPlayRadius,		// �f�t�H���g�̍Đ����a���g�p���邩�H
			bool useDefaltPlayVelocity,		// �f�t�H���g�̃T�E���h�̔������̈ړ����x���g�p���邩�H
			bool useDefaltVolumeRate,		// �f�t�H���g�̃{�����[�����g�p���邩�H�i�����j
			float playRadius,				// �T�E���h���������锼�a
			const Vector3& playVelocity,	// �T�E���h�̔������̈ړ����x
			float volumeRate				// �T�E���h�Đ��Ŏg�p����{�����[��
		);

	public:

		void start();
		void update();
		void onDestroy() const;

	public:

		// �T�E���h���Đ�����
		void playSound();
		// �T�E���h���~����
		void stopSound();

		// �T�E���h���Đ������H
		bool isPlaySound();

		// �Đ�����T�E���h��ID���Đݒ�
		void setPlaySoundId(int playSoundId);

		// �Đ����@�̎�ނ��Đݒ�
		void setSoundPlayType(SoundPlayType soundPlayType);

		// �čĐ��̎��ŏ�����Đ����邩���Đݒ�
		void setPlayFromTop(bool playFromTop);

		// �T�E���h���������锼�a���Đݒ�
		void setPlayRadius(float playRadius);
		// �f�t�H���g�̃T�E���h���������锼�a���g�p����
		void useDefaltPlayRadius();

		// �T�E���h�̔������̈ړ����x���Đݒ�
		void setPlayVelocity(const Vector3& playVelocity);
		// �f�t�H���g�̃T�E���h�̔������̈ړ����x���g�p����
		void useDefaltPlayVelocity();

		// �T�E���h�Đ��Ŏg�p����{�����[�����Đݒ�
		void setVolumeRate(float volumeRate);
		// �f�t�H���g�̃{�����[�����g�p����
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
