#ifndef SKELETON_DATA_H_
#define SKELETON_DATA_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "SkeletonInitParam.h"
#include "../Motion/MotionBoneParam.h"

namespace tktk
{
	// �X�P���g���̏����Ǘ�����N���X
	class SkeletonData
	{
	public:

		SkeletonData(const SkeletonInitParam& initParam);
		~SkeletonData() = default;

	public:

		// �����̃{�[�����̍��W�ϊ��s����g���ăX�P���g����ό`����
		void transform(const std::vector<MotionBoneParam>& transformMatrices);

		// �������Ǘ�����萔�o�b�t�@���X�V����
		void updateBoneMatrixCbuffer();

	private:

		// ���̏��
		struct BoneNode
		{
			int						boneIndex	{};
			tktkMath::Vector3		startPos	{};
			tktkMath::Vector3		endPos		{};
			std::vector<BoneNode*>	children	{};
		};

	private:

		void transform(const SkeletonData::BoneNode* boneNode, const tktkMath::Matrix4& transformMat);

	private:

		std::vector<tktkMath::Matrix4>				m_boneMatrixArray;
		std::unordered_map<std::string, BoneNode>	m_boneNodeMap;
	};
}
#endif // !SKELETON_DATA_H_