#ifndef CONSTANT_BUFFER_MANAGER_H_
#define CONSTANT_BUFFER_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/ConstantBufferAssets.h"
#include "Asset/SystemConstantBufferId.h"
#include "Asset/SystemConstantBufferParamLocationType.h"

namespace tktk
{
	// �uConstantBufferAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class ConstantBufferManager
	{
	public:

		// �uConstantBufferAssets�v���쐬
		static void setUp();

	public:

		// �V���Ȓ萔�o�b�t�@���쐬����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, class BufferDataType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, BufferDataType* data)
		{
			createImpl(static_cast<int>(id), SafetyVoidPtr(data));
		}
		template<class IdType, class BufferDataType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, BufferDataType* data) { static_assert(false, "ConstantBufferId Fraud Type"); }

		// �w�肵���萔�o�b�t�@���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "ConstantBufferId Fraud Type"); }

		// �w�肵���萔�o�b�t�@���Ǘ�����N���X�̃|�C���^���擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static ConstantBufferData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static ConstantBufferData* getDataPtr(IdType id) { static_assert(false, "ConstantBufferId Fraud Type"); }

		// �w�肵���萔�o�b�t�@�ɓ����\��̃f�[�^�̓���̒l�ɃA�N�Z�X���邽�߂̐ݒ���s���i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, class LocationType, std::enable_if_t<(is_idType_v<IdType> && is_idType_v<LocationType>)>* = nullptr>
		static void addParamLocation(IdType id, LocationType locationType, unsigned int locationFromBufferTop)
		{
			addParamLocationImpl(static_cast<int>(id), static_cast<int>(locationType), locationFromBufferTop);
		}
		template <class IdType, class LocationType, std::enable_if_t<!(is_idType_v<IdType> && is_idType_v<LocationType>)>* = nullptr>
		static void addParamLocation(IdType id, LocationType locationType, unsigned int locationFromBufferTop) { static_assert(false, "Id Fraud Type"); }

		// �S�Ă̒萔�o�b�t�@���폜����
		static void clear();

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, SafetyVoidPtr&& data);
	private:
		static void eraseImpl(int id);
		static ConstantBufferData* getDataPtrImpl(int id);
		static void addParamLocationImpl(int id, int locationType, unsigned int locationFromBufferTop);

	private:

		static CfpPtr<ConstantBufferAssets> m_assetsPtr;
	};
}
#endif // !CONSTANT_BUFFER_MANAGER_H_