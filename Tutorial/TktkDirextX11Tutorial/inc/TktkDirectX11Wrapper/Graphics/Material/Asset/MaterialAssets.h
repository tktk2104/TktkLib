#ifndef MATERIAL_ASSETS_H_
#define MATERIAL_ASSETS_H_

#include <unordered_map>
#include "MaterialData.h"

namespace tktk
{
	// �uMaterialData�v���Ǘ�����N���X
	class MaterialAssets
	{
	public:

		MaterialAssets() = default;
		~MaterialAssets();

		MaterialAssets(const MaterialAssets& other) = delete;
		MaterialAssets& operator = (const MaterialAssets& other) = delete;

	public:

		// �V���ȃ}�e���A���𐶐�����
		void create(
			int id,
			int indexBufferStartPos,
			int indexBufferUseCount,
			int useVertexShaderId,
			int usePixelShaderId,
			const std::unordered_map<unsigned int, int>& useTextureIdMap,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shiniess
		);

		// �}�e���A���𕡐�����
		void duplicate(int id, int originalId);

		// �w�肵���}�e���A�����폜����
		void erase(int id);

		// �S�Ẵ}�e���A�����폜����
		void clear();

		// �}�e���A�����Ǘ�����N���X�̃|�C���^���擾����
		MaterialData* getDataPtr(int id);

	private:

		std::unordered_map<int, MaterialData> m_assets;
	};
}
#endif // !MATERIAL_ASSETS_H_
