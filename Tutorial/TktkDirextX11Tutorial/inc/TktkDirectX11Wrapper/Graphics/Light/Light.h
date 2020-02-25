#ifndef LIGHT_H_
#define LIGHT_H_

#include <unordered_set>
#include <forward_list>
#include "Asset/LightData.h"

namespace tktk
{
	// �uLightManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Light
	{
	public:

		// �V���ȃ��C�g�𐶐�����
		// �����̊֐��Ń��C�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(
			int id,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Vector3& position
		);

		// �w�肵�����C�g���폜����
		// �����̊֐��Ń��C�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

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

		// ���L���ɂȂ��Ă��郉�C�g���Ǘ�����N���X�̃��X�g���쐬����
		static void createEnableLightList(std::forward_list<LightData*>* result);

		// ���L���ɂȂ��Ă��郉�C�g���Ǘ�����N���X�̃��X�g���쐬����
		static std::forward_list<LightData*> createEnableLightList();
	};
}
#endif // !LIGHT_H_
