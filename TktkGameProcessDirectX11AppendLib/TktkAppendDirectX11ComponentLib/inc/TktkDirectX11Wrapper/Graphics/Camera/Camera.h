#ifndef CAMERA_H_
#define CAMERA_H_

#include "Asset/CameraData.h"

namespace tktk
{
	// �uCameraManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Camera
	{
	public:

		// �V���ȃJ�����𐶐�����
		static void create(int id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);

		// �w�肵���J�������폜����
		static void erase(int id);

		// �w�肵���J�������Ǘ�����N���X�̃|�C���^���擾����
		static CameraData* getDataPtr(int id);
	};
}
#endif // !CAMERA_H_