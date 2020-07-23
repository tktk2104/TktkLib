#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "SpriteMaterialData.h"

namespace tktk
{
	// �uSpriteMaterialData�v���Ǘ�����N���X
	class SpriteMaterial
	{
	public:

		SpriteMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int spriteMaterialNum);
		~SpriteMaterial() = default;

	public:

		// �uSpriteMaterialData�v�̃C���X�^���X�����
		void create(unsigned int id, const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g��`�悷��
		void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	private:

		// �X�v���C�g�`��p�̃��[�g�V�O�l�`�������
		void createRootSignature();

		// �X�v���C�g�`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths);

	private:

		HeapArray<SpriteMaterialData> m_spriteMaterialArray;
	};
}
#endif // !SPRITE_MATERIAL_H_