#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Asset/MaterialData.h"

namespace tktk
{
	// �uMaterialManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Material
	{
	public:

		// �V���ȃ}�e���A���𐶐�����
		// �����̊֐��Ń}�e���A�������ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
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
		// �����̊֐��Ń}�e���A�������ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ��i��������id�̒l�̐����͂Ȃ��j
		static void duplicate(int id, int originalId);

		// �w�肵���}�e���A�����폜����
		// �����̊֐��Ń}�e���A�����폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �}�e���A�����Ǘ�����N���X�̃|�C���^���擾����
		static MaterialData* getDataPtr(int id);
	};
}
#endif // !MATERIAL_H_