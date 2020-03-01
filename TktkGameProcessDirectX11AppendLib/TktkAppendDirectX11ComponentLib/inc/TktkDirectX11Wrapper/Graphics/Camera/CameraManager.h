#ifndef CAMERA_MANAGER_H_
#define CAMERA_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
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

		// �V���ȃJ�����𐶐�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix)
		{
			createImpl(static_cast<int>(id), viewMatrix, projectionMatrix);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix) { static_assert(false, "CameraId Fraud Type"); }

		// �w�肵���J�������폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "CameraId Fraud Type"); }

		// �w�肵���J�������Ǘ�����N���X�̃|�C���^���擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static CameraData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static CameraData* getDataPtr(IdType id) { static_assert(false, "CameraId Fraud Type"); }

		// �S�ẴJ�������폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);
		static void eraseImpl(int id);
		static CameraData* getDataPtrImpl(int id);

	private:

		static CfpPtr<CameraAssets> m_assetsPtr;
	};
}
#endif // !CAMERA_MANAGER_H_