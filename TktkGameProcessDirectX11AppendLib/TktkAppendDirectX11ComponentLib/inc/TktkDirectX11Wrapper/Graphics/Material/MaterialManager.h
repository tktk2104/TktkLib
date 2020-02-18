#ifndef MATERIAL_MANAGER_H_
#define MATERIAL_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/MaterialAssets.h"

namespace tktk
{
	// �uMaterialAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class MaterialManager
	{
	public:

		// �uMaterialAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃ}�e���A���𐶐�����
		static void create(
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
		static void duplicate(int id, int originalId);

		// �w�肵���}�e���A�����폜����
		static void erase(int id);

		// �S�Ẵ}�e���A�����폜����
		static void clear();

		// �}�e���A�����Ǘ�����N���X�̃|�C���^���擾����
		static MaterialData* getDataPtr(int id);

	private:

		static CfpPtr<MaterialAssets> m_assetsPtr;
	};
}
#endif // !MATERIAL_MANAGER_H_