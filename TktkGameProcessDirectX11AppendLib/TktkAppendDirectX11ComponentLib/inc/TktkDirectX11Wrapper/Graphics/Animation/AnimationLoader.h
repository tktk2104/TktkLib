#ifndef ANIMATION_LOADER_H_
#define ANIMATION_LOADER_H_

#include <string>

namespace tktk
{
	// �A�j���[�V������ǂݍ��ޕ⏕�N���X
	class AnimationLoader
	{
	public:

		// �{�[����->�L�[�t���[�����->�{�[�����c�Ɛ��񂵂Ă���o�C�i���f�[�^�̓ǂݍ��ݐ�p
		static void load(int id, const std::string& fileName);
	};
}
#endif // !ANIMATION_LOADER_H_