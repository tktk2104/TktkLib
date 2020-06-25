#ifndef MOTION_H_
#define MOTION_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "MotionData.h"

namespace tktk
{
	class Motion
	{
	public:

		Motion(unsigned int motionNum);

	public:

		void load(unsigned int id, const std::string& motionFileName);

		// 指定のフレームのボーン毎の行列を取得する（キーが無い時は前後のキーから計算する）
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(unsigned int id, unsigned int frame);

	private:

		HeapArray<MotionData> m_motionArray;
	};
}
#endif // !MOTION_H_