#ifndef POST_EFFECT_MATERIAL_DATA_H_
#define POST_EFFECT_MATERIAL_DATA_H_

#include "PostEffectMaterialInitParam.h"
#include "PostEffectMaterialDrawFuncArgs.h"

namespace tktk
{
	// �|�X�g�G�t�F�N�g�}�e���A�����Ǘ�����N���X
	class PostEffectMaterialData
	{
	public:

		PostEffectMaterialData(const PostEffectMaterialInitParam& initParam);
		~PostEffectMaterialData() = default;

	public:

		// �|�X�g�G�t�F�N�g��`�悷��
		void drawPostEffect(const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		unsigned int m_usePipeLineStateId;
		unsigned int m_useDescriptorHeapId;
	};
}
#endif // !POST_EFFECT_MATERIAL_DATA_H_