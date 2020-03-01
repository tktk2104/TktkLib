#ifndef LIGHT_MANAGER_H_
#define LIGHT_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "LightUpdater.h"

namespace tktk
{
	// �uLightUpdater�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class LightManager
	{
	public:

		// �uLightUpdater�v�𐶐�
		static void setUp();

	public:

		// �V���ȃ��C�g�𐶐�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Color& ambientColor, const Color& diffuseColor, const Color& specularColor, const Vector3& position)
		{
			createImpl(static_cast<int>(id), ambientColor, diffuseColor, specularColor, position);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Color& ambientColor, const Color& diffuseColor, const Color& specularColor, const Vector3& position)
			 { static_assert(false, "LightId Fraud Type"); }

		// �w�肵�����C�g���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "LightId Fraud Type"); }

		// ���C�g���Ǘ�����N���X�̃|�C���^���擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static LightData* getLightDataPtr(IdType id)
		{
			return getLightDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static LightData* getLightDataPtr(IdType id) { static_assert(false, "LightId Fraud Type"); }

		// �w�肵�����C�g��L���ɂ���i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void enableLight(IdType id)
		{
			enableLightImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void enableLight(IdType id) { static_assert(false, "LightId Fraud Type"); }

		// �w�肵�����C�g�𖳌��ɂ���i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void disableLight(IdType id)
		{
			disableLightImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void disableLight(IdType id) { static_assert(false, "LightId Fraud Type"); }

		// �S�Ẵ��C�g���폜����
		void clear();

		// �S�Ẵ��C�g�𖳌��ɂ���
		static void disableLightAll();

		// ���L���ɂȂ��Ă��郉�C�g��Id�̈ꗗ���擾����
		static const std::unordered_set<int>& getEnableLightIdList();

		// ���L���ɂȂ��Ă��郉�C�g���Ǘ�����N���X�̃��X�g���쐬����i�����Ŏ擾�^�j
		static void createEnableLightList(std::forward_list<LightData*>* result);

		// ���L���ɂȂ��Ă��郉�C�g���Ǘ�����N���X�̃��X�g���쐬����i�߂�l�Ŏ擾�^�j
		static std::forward_list<LightData*> createEnableLightList();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const Color& ambientColor, const Color& diffuseColor, const Color& specularColor, const Vector3& position);
		static void eraseImpl(int id);
		static LightData* getLightDataPtrImpl(int id);
		static void enableLightImpl(int id);
		static void disableLightImpl(int id);

	private:

		static CfpPtr<LightUpdater> m_updaterPtr;
	};
}
#endif // !LIGHT_MANAGER_H_