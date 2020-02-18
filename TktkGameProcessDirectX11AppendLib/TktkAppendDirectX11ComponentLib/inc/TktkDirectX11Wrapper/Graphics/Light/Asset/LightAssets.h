#ifndef LIGHT_ASSETS_H_
#define LIGHT_ASSETS_H_

#include <unordered_map>
#include "LightData.h"

namespace tktk
{
	// �uLightData�v���Ǘ�����N���X
	class LightAssets
	{
	public:

		LightAssets() = default;
		~LightAssets();

		LightAssets(const LightAssets& other) = delete;
		LightAssets& operator = (const LightAssets& other) = delete;

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

	private:

		// ���C�g���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, LightData> m_lightAssets;
	};
}
#endif // !LIGHT_ASSETS_H_