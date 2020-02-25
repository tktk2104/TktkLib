#ifndef LIGHT_MANAGER_H_
#define LIGHT_MANAGER_H_

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

		// �V���ȃ��C�g�𐶐�����
		static void create(
			int id,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Vector3& position
		);

		// �w�肵�����C�g���폜����
		static void erase(int id);

		// �S�Ẵ��C�g���폜����
		void clear();

		// ���C�g���Ǘ�����N���X�̃|�C���^���擾����
		static LightData* getLightDataPtr(int id);

		// �w�肵�����C�g��L���ɂ���
		static void enableLight(int id);

		// �w�肵�����C�g�𖳌��ɂ���
		static void disableLight(int id);

		// �S�Ẵ��C�g�𖳌��ɂ���
		static void disableLightAll();

		// ���L���ɂȂ��Ă��郉�C�g��Id�̈ꗗ���擾����
		static const std::unordered_set<int>& getEnableLightIdList();

		// ���L���ɂȂ��Ă��郉�C�g���Ǘ�����N���X�̃��X�g���쐬����i�����Ŏ擾�^�j
		static void createEnableLightList(std::forward_list<LightData*>* result);

		// ���L���ɂȂ��Ă��郉�C�g���Ǘ�����N���X�̃��X�g���쐬����i�߂�l�Ŏ擾�^�j
		static std::forward_list<LightData*> createEnableLightList();

	private:

		static CfpPtr<LightUpdater> m_updaterPtr;
	};
}
#endif // !LIGHT_MANAGER_H_