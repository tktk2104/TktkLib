#ifndef RENDER_TARGET_MANAGER_H_
#define RENDER_TARGET_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/RenderTargetAssets.h"
#include "Asset/SystemRenderTargetId.h"

namespace tktk
{
	// �uRenderTargetAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class RenderTargetManager
	{
	public:

		// �uRenderTargetAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃ����_�[�^�[�Q�b�g�𐶐�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, ID3D11Texture2D* renderTargetTexture)
		{
			createImpl(static_cast<int>(id), renderTargetTexture);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, ID3D11Texture2D* renderTargetTexture) { static_assert(false, "RenderTargetId Fraud Type"); }

		// �w�肵�������_�[�^�[�Q�b�g���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "RenderTargetId Fraud Type"); }

		// �w�肵�������_�[�^�[�Q�b�g���Ǘ�����N���X�̎Q�Ƃ��擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const RenderTargetData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const RenderTargetData& getData(IdType id) { static_assert(false, "RenderTargetId Fraud Type"); }

		// �S�Ẵ����_�[�^�[�Q�b�g���폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, ID3D11Texture2D* renderTargetTexture);
		static void eraseImpl(int id);
		static const RenderTargetData& getDataImpl(int id);

	private:

		static CfpPtr<RenderTargetAssets> m_assetsPtr;
	};
}
#endif // !RENDER_TARGET_MANAGER_H_