#ifndef MOTION_H_
#define MOTION_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "MotionData.h"

namespace tktk
{
	// �uMotionData�v���Ǘ�����N���X
	class Motion
	{
	public:

		Motion(unsigned int motionNum);

	public:

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����
		void load(unsigned int id, const std::string& motionFileName);

		// �w��̃t���[���̃{�[�����̍s����擾����i�L�[���������͑O��̃L�[����v�Z����j
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(unsigned int id, unsigned int frame) const;

	private:

		HeapArray<MotionData> m_motionArray;
	};
}
#endif // !MOTION_H_