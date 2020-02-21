#ifndef SOUND_3D_PLAYER_MAKER_H_
#define SOUND_3D_PLAYER_MAKER_H_

#include <TktkMath/Vector3.h>
#include "Sound3DPlayer.h"

namespace tktk
{
	class Sound3DPlayerMaker
	{
	public:

		// �C���X�^���X�����J�n
		static Sound3DPlayerMaker& makeStart();

	public:

		// �쐬����
		Sound3DPlayer* create();

		// ���g�̐����シ���ɍĐ����邩��ݒ�
		Sound3DPlayerMaker& startToPlay(bool value);

		// �Đ�����T�E���h��ID��ݒ�
		Sound3DPlayerMaker& playSoundId(int value);

		// �Đ����@�̎�ނ�ݒ�
		Sound3DPlayerMaker& soundPlayType(SoundPlayType value);

		// �čĐ��̎��ŏ�����Đ����邩��ݒ�
		Sound3DPlayerMaker& playFromTop(bool value);

		// �T�E���h���������锼�a��ݒ�
		Sound3DPlayerMaker& playRadius(float value);

		// �T�E���h�̔������̈ړ����x���Đݒ�
		Sound3DPlayerMaker& playVelocity(const Vector3& value);

		// �T�E���h�Đ��Ŏg�p����{�����[����ݒ�
		Sound3DPlayerMaker& volumeRate(float value);

	private:

		// ���g�̃|�C���^
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