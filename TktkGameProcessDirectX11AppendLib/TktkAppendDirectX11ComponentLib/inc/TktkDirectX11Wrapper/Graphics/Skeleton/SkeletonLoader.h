#ifndef SKELETON_LOADER_H_
#define SKELETON_LOADER_H_

#include <string>

namespace tktk
{
	// �X�P���g����ǂݍ��ޕ⏕�N���X
	class SkeletonLoader
	{
	public:

		// �ȉ��̌`���Ő��񂵂Ă���o�C�i���f�[�^�̓ǂݍ��ݐ�p
		// �uchar[32]name, int id, int parentId, Matrix4 transform, Matrix4 inverse�v
		static void load(int id, const std::string& fileName);
	};
}
#endif // !SKELETON_LOADER_H_
