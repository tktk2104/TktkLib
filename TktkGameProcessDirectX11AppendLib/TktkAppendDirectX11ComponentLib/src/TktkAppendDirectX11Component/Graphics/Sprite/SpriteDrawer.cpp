#include "TktkAppendDirectX11Component/Graphics/Sprite/SpriteDrawer.h"

#include <stdexcept>
#include <array>
#include <d3d11.h>
#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2D.h"
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendState.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilState.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShader.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShader.h"
#include "TktkDirectX11Wrapper/Graphics/Sprite/SpriteConstantBufferData.h"

namespace tktk
{
	SpriteDrawer::SpriteDrawer(
		float drawPriority,
		int textureId,
		int blendStateId,
		const Color & blendRate,
		int depthStencilStateId
	)
		: ComponentBase(drawPriority)
		, m_textureId(textureId)
		, m_blendStateId(blendStateId)
		, m_blendRate(blendRate)
		, m_depthStencilStateId(depthStencilStateId)
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

		std::array<float, 4> factor = { m_blendRate.r, m_blendRate.g, m_blendRate.b, m_blendRate.a };
		Screen::getDeviceContextPtr()->OMSetBlendState(BlendState::getDataPtr(m_blendStateId)->getStatePtr(), factor.data(), 0xffffffff);
		Screen::getDeviceContextPtr()->OMSetDepthStencilState(DepthStencilState::getDataPtr(m_depthStencilStateId)->getStatePtr(), 0);

		Screen::getDeviceContextPtr()->PSSetShaderResources(0, 1, &shaderResourceView);
		Screen::getDeviceContextPtr()->PSSetSamplers(0, 1, &samplerState);

		// 定数バッファに値を詰め詰めする
		ConstantBufferData* constantBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Sprite);

		SpriteConstantBufferData spriteConstantBufferData;
		spriteConstantBufferData.texturePosition = Vector2::zero;
		spriteConstantBufferData.textureSize = Vector2::one;
		spriteConstantBufferData.size = Vector2(static_cast<float>(texture2DData.width()), static_cast<float>(texture2DData.height()));
		spriteConstantBufferData.position = m_transform->getWorldPosition();
		spriteConstantBufferData.scaleRate = m_transform->getWorldScaleRate();
		spriteConstantBufferData.angleDeg = m_transform->getWorldRotationDeg();
		spriteConstantBufferData.color = Color::white;
		spriteConstantBufferData.center = Vector2::one;
		spriteConstantBufferData.screenSize = Window::getWindowSize();
		constantBufferData->setBufferData(std::move(spriteConstantBufferData));

		constantBufferData->updateBuffer();

		// シェーダーをセット
		VertexShader::getData(SystemVertexShaderId::Sprite).beginVertexShader();
		PixelShader::getData(SystemPixelShaderId::Sprite).beginShader();

		MeshData* meshDataPtr = Mesh::getDataPtr(SYSTEM_MESH_SPRITE);

		// 頂点バッファとインデックスバッファをレンダリングパイプラインに設定する
		meshDataPtr->setVertexAndIndexBuffer();

		// ドローコール
		Screen::getDeviceContextPtr()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		Screen::getDeviceContextPtr()->DrawIndexed(4, 0, 0);
	}
}