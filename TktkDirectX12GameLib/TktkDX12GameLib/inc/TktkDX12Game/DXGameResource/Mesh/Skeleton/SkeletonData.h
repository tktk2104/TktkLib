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
	class SkeletonData
	{
	public:

		SkeletonData(const SkeletonInitParam& initParam);
		~SkeletonData() = default;

	public:

		void transform(const std::vector<MotionBoneParam>& transformMatrices);

		void updateBoneMatrixCbuffer();

	private:

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
		std::vector<std::string>					m_boneNameArray; // <-ƒ[ƒJƒ‹•Ï”‚Å—Ç‚¢‚Ì‚Å‚ÍH
		std::unordered_map<std::string, BoneNode>	m_boneNodeMap;
	};
}
#endif // !SKELETON_DATA_H_