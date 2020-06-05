#ifndef POST_EFFECT_MATERIAL_H_
#define POST_EFFECT_MATERIAL_H_

#include "PostEffectShaderFilePaths.h"
#include "PostEffectMaterialData.h"
#include <TktkContainer/HeapArray/HeapArray.h>

namespace tktk
{
	class PostEffectMaterial
	{
	public:

		PostEffectMaterial(const PostEffectShaderFilePaths& shaderFilePaths, unsigned int postEffectMaterialNum);
		~PostEffectMaterial() = default;

	public:

		void create(unsigned int id, const PostEffectMaterialInitParam& initParam);

		void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		HeapArray<PostEffectMaterialData> m_postEffectMaterialArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_H_
