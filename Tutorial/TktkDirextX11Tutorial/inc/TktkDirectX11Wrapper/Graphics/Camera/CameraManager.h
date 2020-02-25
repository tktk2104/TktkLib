#ifndef CAMERA_MANAGER_H_
#define CAMERA_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/CameraAssets.h"

namespace tktk
{
	// �uCameraAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class CameraManager
	{
	public:

		// �uCameraAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃJ�����𐶐�����
		static void create(int id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);

		// �w�肵���J�������폜����
		static void erase(int id);

		// �S�ẴJ�������폜����
		static void clear();

		// �w�肵���J�������Ǘ�����N���X�̃|�C���^���擾����
		static CameraData* getDataPtr(int id);

	private:

		static CfpPtr<CameraAssets> m_assetsPtr;
	};
}
#endif // !CAMERA_MANAGER_H_