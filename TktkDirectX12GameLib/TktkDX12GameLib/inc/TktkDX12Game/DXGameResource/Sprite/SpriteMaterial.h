#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#undef min
#undef max
#include "SpriteMaterialData.h"

namespace tktk
{
	class SpriteMaterial
	{
	public:

		SpriteMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int spriteMaterialNum);
		~SpriteMaterial() = default;

	public:

		void create(unsigned int id, const SpriteMaterialInitParam& initParam);

		void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	private:

		void createRootSignature();

		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths);

	private:

		HeapArray<SpriteMaterialData> m_spriteMaterialArray;
	};
}
#endif // !SPRITE_MATERIAL_H_