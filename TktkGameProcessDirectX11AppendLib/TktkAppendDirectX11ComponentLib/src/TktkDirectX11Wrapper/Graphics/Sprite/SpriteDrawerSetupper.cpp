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
		ConstantBufferManager::create(SystemConstantBufferId::Sprite, new SpriteConstantBufferData());
		
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

		MaterialSlotsInitParams materialSlotsParams;
		materialSlotsParams.subsets.push_back({ 0, 4 });
		
		MeshManager::create(SYSTEM_MESH_SPRITE, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, vertexBufferParams, indexBufferParams, materialSlotsParams);

		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = std::vector<D3D11_INPUT_ELEMENT_DESC>({
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			});
		VertexShaderManager::load(SystemVertexShaderId::Sprite, useVertexShaderFileName, layout, SystemConstantBufferId::Sprite);

		PixelShaderManager::load(SystemPixelShaderId::Sprite, usePixelShaderFileName, SystemConstantBufferId::Sprite);
	}
}