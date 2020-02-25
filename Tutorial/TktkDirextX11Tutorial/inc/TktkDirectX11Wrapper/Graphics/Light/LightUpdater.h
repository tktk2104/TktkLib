#ifndef LIGHT_UPDATER_H_
#define LIGHT_UPDATER_H_

#include <memory>
#include <forward_list>
#include <unordered_set>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/LightAssets.h"

namespace tktk
{
	// �uLightAssets�v�ŊǗ����Ă��郉�C�g���̗L��������؂�ւ���N���X
	class LightUpdater
	{
	public:

		LightUpdater();
		~LightUpdater();

		LightUpdater(const LightUpdater& other) = delete;
		LightUpdater& operator = (const LightUpdater& other) = delete;

	public:

		// �V���ȃ��C�g�𐶐�����
		void create(
			int id,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Vector3& position
		);

		// �w�肵�����C�g���폜����
		void erase(int id);

		// �S�Ẵ��C�g���폜����
		void clear();

		// ���C�g���Ǘ�����N���X�̃|�C���^���擾����
		LightData* getLightDataPtr(int id);

		// �w�肵�����C�g��L���ɂ���
		void enableLight(int id);

		// �w�肵�����C�g�𖳌��ɂ���
		void disableLight(int id);

		// �S�Ẵ��C�g�𖳌��ɂ���
		void disableLightAll();

		// ���L���ɂȂ��Ă��郉�C�g��Id�̈ꗗ���擾����
		const std::unordered_set<int>& getEnableLightIdList() const;

		// ���L���ɂȂ��Ă��郉�C�g���Ǘ�����N���X�̃��X�g���쐬����
		void createEnableLightList(std::forward_list<LightData*>* result);

	private:

		// ���L���ɂȂ��Ă��郉�C�g��Id�̈ꗗ
		std::unordered_set<int> m_enableLightIdList;

		// ���C�g�A�Z�b�g�̃|�C���^
		CfpPtr<LightAssets> m_assets;
	};
}
#endif // !LIGHT_UPDATER_H_
