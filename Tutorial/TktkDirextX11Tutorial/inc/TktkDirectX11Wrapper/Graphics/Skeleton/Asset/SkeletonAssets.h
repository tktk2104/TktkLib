#ifndef SKELETON_ASSETS_H_
#define SKELETON_ASSETS_H_

#include <unordered_map>
#include "SkeletonData.h"

namespace tktk
{
	// �uSkeletonData�v���Ǘ�����N���X
	class SkeletonAssets
	{
	public:

		SkeletonAssets() = default;
		~SkeletonAssets();

		SkeletonAssets(const SkeletonAssets& other) = delete;
		SkeletonAssets& operator = (const SkeletonAssets& other) = delete;

	public:

		// �V�����X�P���g�����쐬����
		void create(int id, const std::vector<Bone>& boneArray);

		// �w�肵���X�P���g�����폜����
		void erase(int id);

		// �S�ẴX�P���g�����폜����
		void clear();

		// �w�肵���X�P���g�����Ǘ�����N���X�̎Q�Ƃ��擾����
		const SkeletonData& getData(int id) const;

	private:

		// �X�P���g�����Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, SkeletonData> m_assets;
	};
}
#endif // !SKELETON_ASSETS_H_