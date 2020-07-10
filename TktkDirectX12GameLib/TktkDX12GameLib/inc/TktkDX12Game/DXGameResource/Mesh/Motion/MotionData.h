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
	// ���[�V�����f�[�^���Ǘ�����N���X
	class MotionData
	{
	public:

		MotionData(const std::string& motionFileName);
		~MotionData() = default;

	public:

		// �w��̃t���[���̃{�[�����̍s����擾����i�L�[���������͑O��̃L�[����v�Z����j
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(unsigned int frame);

	private:

		// �L�[�t���[�����
		struct KeyFrame
		{
			unsigned int			frameNo;
			tktkMath::Vector3		position;
			tktkMath::Vector3		scale;
			tktkMath::Quaternion	rotation;
		};

	private:

		// ���݂̃t���[���ɑΉ������L�[�t���[�������߂�
		KeyFrame calculateKeyFrame(const std::vector<KeyFrame>& keyFrames, unsigned int frame);

	private:

		// �{�[�����Ƃ̃L�[�t���[���̔z����Ǘ�����A�z�z��
		std::unordered_map<std::string, std::vector<KeyFrame>> m_boneKeyFrames;
	};
}
#endif // !MOTION_DATA_H_