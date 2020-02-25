#ifndef CAMERA_ASSETS_H_
#define CAMERA_ASSETS_H_

#include <unordered_map>
#include "CameraData.h"

namespace tktk
{
	// �uCameraData�v���Ǘ�����N���X
	class CameraAssets
	{
	public:

		CameraAssets() = default;
		~CameraAssets();

		CameraAssets(const CameraAssets& other) = delete;
		CameraAssets& operator = (const CameraAssets& other) = delete;

	public:

		// �V���ȃJ�����𐶐�����
		void create(int id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);

		// �w�肵���J�������폜����
		void erase(int id);

		// �S�ẴJ�������폜����
		void clear();

		// �w�肵���J�������Ǘ�����N���X�̃|�C���^���擾����
		CameraData* getDataPtr(int id);

	private:

		// �J�������Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, CameraData> m_assets;
	};
}
#endif // !CAMERA_ASSETS_H_