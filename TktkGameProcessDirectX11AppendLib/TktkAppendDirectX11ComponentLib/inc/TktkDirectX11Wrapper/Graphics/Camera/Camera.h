#ifndef CAMERA_H_
#define CAMERA_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/CameraData.h"

namespace tktk
{
	// �uCameraManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Camera
	{
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

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);
		static void eraseImpl(int id);
		static CameraData* getDataPtrImpl(int id);
	};
}
#endif // !CAMERA_H_