#ifndef POST_EFFECT_MATERIAL_H_
#define POST_EFFECT_MATERIAL_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "PostEffectShaderFilePaths.h"
#include "PostEffectMaterialData.h"

namespace tktk
{
	// �uPostEffectMaterialData�v���Ǘ�����N���X
	class PostEffectMaterial
	{
	public:

		PostEffectMaterial(const PostEffectShaderFilePaths& shaderFilePaths, unsigned int postEffectMaterialNum);
		~PostEffectMaterial() = default;

	public:

		// �uPostEffectMaterialData�v�̃C���X�^���X�����
		void create(unsigned int id, const PostEffectMaterialInitParam& initParam);

		// �w�肵���|�X�g�G�t�F�N�g��`�悷��
		void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		HeapArray<PostEffectMaterialData> m_postEffectMaterialArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_H_
