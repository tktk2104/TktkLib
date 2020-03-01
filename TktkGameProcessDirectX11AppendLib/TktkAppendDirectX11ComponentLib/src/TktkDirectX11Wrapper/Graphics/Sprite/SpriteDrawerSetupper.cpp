#include "TktkDirectX11Wrapper/Graphics/Sprite/SpriteDrawerSetupper.h"

#include <array>
#include <vector>

#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshManager.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShaderManager.h"
#include "TktkDirectX11Wrapper/Graphics/Sprite/SpriteConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Sprite/SpriteVertexBufferData.h"

namespace tktk
{
	void SpriteDrawerSetupper::setUp(
		const std::string & usePixelShaderFileName,
		const std::string & useVertexShaderFileName
	)
	{
		SpriteConstantBufferData* spriteConstantBufferData = new SpriteConstantBufferData();
		ConstantBufferManager::create(SystemConstantBufferId::Sprite, spriteConstantBufferData);
		unsigned int location = 0U;
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Sprite, SystemConstantBufferParamLocationType::texturePosition, location);
		location += sizeof(Vector2);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Sprite, SystemConstantBufferParamLocationType::textureSize, location);
		location += sizeof(Vector2);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Sprite, SystemConstantBufferParamLocationType::size, location);
		location += sizeof(Vector2);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Sprite, SystemConstantBufferParamLocationType::position, location);
		location += sizeof(Vector2);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Sprite, SystemConstantBufferParamLocationType::scaleRate, location);
		location += sizeof(Vector2);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Sprite, SystemConstantBufferParamLocationType::angleDeg, location);
		location += sizeof(float) * 2;
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Sprite, SystemConstantBufferParamLocationType::color, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Sprite, SystemConstantBufferParamLocationType::center, location);
		location += sizeof(Vector2);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Sprite, SystemConstantBufferParamLocationType::screenSize, location);

		std::array<SpriteVertexBufferData, 4U> vertices = std::array<SpriteVertexBufferData, 4U>({
			Vector2(0.0f, 0.0f),
			Vector2(1.0f, 0.0f),
			Vector2(0.0f, 1.0f),
			Vector2(1.0f, 1.0f)
			});

		VertexBufferInitParams vertexBufferParams;
		vertexBufferParams.stride = sizeof(SpriteVertexBufferData);
		vertexBufferParams.offset = 0U;
		vertexBufferParams.bufferSize = sizeof(SpriteVertexBufferData) * vertices.size();
		vertexBufferParams.bufferData = vertices.data();

		IndexBufferInitParams indexBufferParams;
		indexBufferParams.indices = std::vector<unsigned int>({ 0U, 1U, 2U, 3U });
		
		MeshManager::create(SYSTEM_MESH_SPRITE, vertexBufferParams, indexBufferParams);

		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = std::vector<D3D11_INPUT_ELEMENT_DESC>({
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			});
		VertexShaderManager::load(SystemVertexShaderId::Sprite, SystemConstantBufferId::Sprite, useVertexShaderFileName, layout);

		PixelShaderManager::load(SystemPixelShaderId::Sprite, SystemConstantBufferId::Sprite, usePixelShaderFileName);
	}
}