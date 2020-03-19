#ifndef RASTERIZER_STATE_MANAGER_H_
#define RASTERIZER_STATE_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/RasterizerStateAssets.h"
#include "Asset/SystemRasterizerStateId.h"

namespace tktk
{
	// �uRasterizerStateAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class RasterizerStateManager
	{
	public:

		// �uRasterizerStateAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃ��X�^���C�U�X�e�[�g���쐬����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_RASTERIZER_DESC& desc)
		{
			createImpl(static_cast<int>(id), desc);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_RASTERIZER_DESC& desc) { static_assert(false, "RasterizerStateId Fraud Type"); }

		// �w�肵�����X�^���C�U�X�e�[�g���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }

		// �w�肵�����X�^���C�U�X�e�[�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const RasterizerStateData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const RasterizerStateData& getData(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }

		// �S�Ẵ��X�^���C�U�X�e�[�g���폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const D3D11_RASTERIZER_DESC& desc);
		static void eraseImpl(int id);
		static const RasterizerStateData& getDataImpl(int id);

	private:

		static CfpPtr<RasterizerStateAssets> m_assetsPtr;
	};
}
#endif // !RASTERIZER_STATE_MANAGER_H_
