#include "TktkAppendDirectX11Component/Graphics/Sprite/SpriteDrawer.h"

#include <stdexcept>
#include <d3d11.h>
#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2D.h"
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShader.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShader.h"
#include "TktkDirectX11Wrapper/Graphics/Sprite/SpriteConstantBufferData.h"

namespace tktk
{
	SpriteDrawer::SpriteDrawer(float drawPriority, int textureId)
		: ComponentBase(drawPriority)
		, m_textureId(textureId)
	{
	}

	void SpriteDrawer::start()
	{
		m_transform = getComponent<tktk::Transform2D>();

		if (m_transform.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void SpriteDrawer::draw() const
	{
		const Texture2DData& texture2DData = Texture2D::getData(m_textureId);
		ID3D11ShaderResourceView* shaderResourceView = texture2DData.getShaderResourceViewPtr();
		ID3D11SamplerState* samplerState = texture2DData.getSamplerStatePtr();

		Screen::getDeviceContextPtr()->PSSetShaderResources(0, 1, &shaderResourceView);
		Screen::getDeviceContextPtr()->PSSetSamplers(0, 1, &samplerState);

		// 定数バッファに値を詰め詰めする
		ConstantBufferData* constantBufferData = ConstantBuffer::getDataPtr(SYSTEM_CONSTANT_BUFFER_SPRITE);

		constantBufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_texturePosition,	Vector2::zero);
		constantBufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_textureSize,		Vector2::one);
		constantBufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_size,				Vector2(static_cast<float>(texture2DData.width()), static_cast<float>(texture2DData.height())));
		constantBufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_position,			m_transform->getWorldPosition());
		constantBufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_scaleRate,			m_transform->getWorldScaleRate());
		constantBufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_angleDeg,			m_transform->getWorldRotationDeg());
		constantBufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_color,				Color::white);
		constantBufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_center,				Vector2::one);
		constantBufferData->setBufferParam(SYSTEM_CONSTANT_BUFFER_PARAM_screenSize,			Window::getWindowSize());
		constantBufferData->updateBuffer();

		// シェーダーをセット
		VertexShader::getData(SYSTEM_VERTEX_SHADER_SPRITE).beginVertexShader();
		PixelShader::getData(SYSTEM_PIXEL_SHADER_SPRITE).beginShader();

		MeshData* meshDataPtr = Mesh::getDataPtr(SYSTEM_MESH_SPRITE);

		// 頂点バッファをセット
		const VertexBuffer& vertexBuffer = meshDataPtr->getVertexBuffer();
		ID3D11Buffer* rawVertexBuffer = vertexBuffer.getVertexBufferPtr();
		unsigned int stride = vertexBuffer.getStride();
		unsigned int offset = vertexBuffer.getOffset();
		Screen::getDeviceContextPtr()->IASetVertexBuffers(0, 1, &rawVertexBuffer, &stride, &offset);

		// インデックスバッファをセット
		const IndexBuffer& indexBuffer = meshDataPtr->getIndexBuffer();
		Screen::getDeviceContextPtr()->IASetIndexBuffer(indexBuffer.getBufferPtr(), DXGI_FORMAT_R32_UINT, 0);

		// ドローコール
		Screen::getDeviceContextPtr()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		Screen::getDeviceContextPtr()->DrawIndexed(4, 0, 0);
	}
}