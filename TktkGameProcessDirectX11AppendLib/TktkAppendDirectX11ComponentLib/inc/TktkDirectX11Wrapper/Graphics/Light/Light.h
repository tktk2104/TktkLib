#ifndef LIGHT_H_
#define LIGHT_H_

#include <unordered_set>
#include <forward_list>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/LightData.h"

namespace tktk
{
	// �uLightManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Light
	{
	public:

		// �V���ȃ��C�g�𐶐�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ń��C�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Color& ambientColor, const Color& diffuseColor, const Color& specularColor, const Vector3& position)
		{
			createImpl(static_cast<int>(id), ambientColor, diffuseColor, specularColor, position);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Color& ambientColor, const Color& diffuseColor, const Color& specularColor, const Vector3& position)
			 { static_assert(false, "LightId Fraud Type"); }

		// �w�肵�����C�g���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ń��C�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
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

		// �S�Ẵ��C�g�𖳌��ɂ���
		static void disableLightAll();

		// ���L���ɂȂ��Ă��郉�C�g��Id�̈ꗗ���擾����
		static const std::unordered_set<int>& getEnableLightIdList();

		// ���L���ɂȂ��Ă��郉�C�g���Ǘ�����N���X�̃��X�g���쐬����
		static void createEnableLightList(std::forward_list<LightData*>* result);

		// ���L���ɂȂ��Ă��郉�C�g���Ǘ�����N���X�̃��X�g���쐬����
		static std::forward_list<LightData*> createEnableLightList();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const Color& ambientColor, const Color& diffuseColor, const Color& specularColor, const Vector3& position);
		static void eraseImpl(int id);
		static LightData* getLightDataPtrImpl(int id);
		static void enableLightImpl(int id);
		static void disableLightImpl(int id);
	};
}
#endif // !LIGHT_H_
