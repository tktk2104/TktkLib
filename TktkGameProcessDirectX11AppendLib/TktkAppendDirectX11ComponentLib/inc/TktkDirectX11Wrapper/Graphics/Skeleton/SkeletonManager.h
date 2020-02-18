#ifndef SKELETON_MANAGER_H_
#define SKELETON_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/SkeletonAssets.h"

namespace tktk
{
	// �uSkeletonAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class SkeletonManager
	{
	public:

		// �uSkeletonAssets�v�𐶐�
		static void setUp();

	public:

		// �V�����X�P���g�����쐬����
		static void create(int id, const std::vector<Bone>& boneArray);

		// �w�肵���X�P���g�����폜����
		static void erase(int id);

		// �S�ẴX�P���g�����폜����
		static void clear();

		// �w�肵���X�P���g�����Ǘ�����N���X�̎Q�Ƃ��擾����
		static const SkeletonData& getData(int id);

	private:

		static CfpPtr<SkeletonAssets> m_assetsPtr;
	};
}
#endif // !SKELETON_MANAGER_H_