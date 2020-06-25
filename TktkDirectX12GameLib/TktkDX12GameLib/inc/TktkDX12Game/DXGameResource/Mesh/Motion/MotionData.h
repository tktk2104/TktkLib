#ifndef MOTION_DATA_H_
#define MOTION_DATA_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Quaternion.h>
#include <TktkMath/Structs/Matrix4.h>
#include "MotionBoneParam.h"

namespace tktk
{
	class MotionData
	{
	public:

		MotionData(const std::string& motionFileName);
		~MotionData() = default;

	public:

		// 指定のフレームのボーン毎の行列を取得する（キーが無い時は前後のキーから計算する）
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(unsigned int frame);

	private:

		struct KeyFrame
		{
			unsigned int			frameNo;
			tktkMath::Vector3		position;
			tktkMath::Vector3		scale;
			tktkMath::Quaternion	rotation;
		};

	private:

		// 現在のフレームに対応したキーフレームを求める
		KeyFrame calculateKeyFrame(const std::vector<KeyFrame>& keyFrames, unsigned int frame);

	private:

		// ボーンごとのキーフレームの配列を管理する連想配列
		std::unordered_map<std::string, std::vector<KeyFrame>> m_boneKeyFrames;
	};
}
#endif // !MOTION_DATA_H_