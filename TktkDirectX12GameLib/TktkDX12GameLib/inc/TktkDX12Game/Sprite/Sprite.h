#ifndef SPRITE_H_
#define SPRITE_H_

#include <TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/GraphicsPipeLineStateInitParam.h>
#undef min
#undef max
#include "../Sprite/SpriteMaterial.h"

namespace tktk
{
	class Sprite
	{
	public:

		Sprite(const tktk::ShaderFilePaths& shaderFilePaths, unsigned int spriteMaterialNum);

	public:

		void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		void drawSprite(unsigned int spriteMaterialId, const tktkMath::Matrix3& worldMatrix);

	private:

		void createRootSignature();

		void createGraphicsPipeLineState(const tktk::ShaderFilePaths& shaderFilePaths);

	private:

		SpriteMaterial m_spriteMaterial;
	};
}
#endif // !SPRITE_H_