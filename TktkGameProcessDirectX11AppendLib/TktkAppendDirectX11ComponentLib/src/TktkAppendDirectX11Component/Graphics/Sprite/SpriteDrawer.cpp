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
#include "TktkDirectX11Wrapper/Graphics/RasterizerState/RasterizerState.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShader.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShader.h"
#include "TktkDirectX11Wrapper/Graphics/Sprite/SpriteConstantBufferData.h"

namespace tktk
{
	SpriteDrawer::SpriteDrawer(
		float drawPriority,
		int textureId,
		int blendStateId,
		int depthStencilStateId,
		int rasterizerStateId,
		const Vector2 & textureUvOffset,
		const Vector2 & textureUvMulRate,
		const Color & blendRate,
		const Vector2& spriteCenterRate
	)
		: ComponentBase(drawPriority)
		, m_textureId(textureId)
		, m_blendStateId(blendStateId)
		, m_depthStencilStateId(depthStencilStateId)
		, m_rasterizerStateId(rasterizerStateId)
		, m_textureUvOffset(textureUvOffset)
		, m_textureUvMulRate(textureUvMulRate)
		, m_blendRate(blendRate)
		, m_spriteCenterRate(spriteCenterRate)
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

		std::array<float, 4> factor = { 1.0f, 1.0f, 1.0f, 1.0f };
		Screen::getDeviceContextPtr()->OMSetBlendState(BlendState::getDataPtr(m_blendStateId)->getStatePtr(), factor.data(), 0xffffffff);
		Screen::getDeviceContextPtr()->OMSetDepthStencilState(DepthStencilState::getDataPtr(m_depthStencilStateId)->getStatePtr(), 0);

		Screen::getDeviceContextPtr()->PSSetShaderResources(0, 1, &shaderResourceView);
		Screen::getDeviceContextPtr()->PSSetSamplers(0, 1, &samplerState);

		// 定数バッファに値を詰め詰めする
		ConstantBufferData* constantBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Sprite);

		SpriteConstantBufferData spriteConstantBufferData;
		spriteConstantBufferData.textureUvOffset = m_textureUvOffset;
		spriteConstantBufferData.textureUvMulRate = m_textureUvMulRate;
		spriteConstantBufferData.textureSize = Vector2(static_cast<float>(texture2DData.width()), static_cast<float>(texture2DData.height()));
		spriteConstantBufferData.spritePosition = m_transform->getWorldPosition();
		spriteConstantBufferData.spriteScaleRate = m_transform->getWorldScaleRate();
		spriteConstantBufferData.spriteAngleDeg = m_transform->getWorldRotationDeg();
		spriteConstantBufferData.blendRate = m_blendRate;
		spriteConstantBufferData.spriteCenterRate = m_spriteCenterRate;
		spriteConstantBufferData.screenSize = Window::getWindowSize();
		constantBufferData->setBufferData(std::move(spriteConstantBufferData));

		constantBufferData->updateBuffer();

		// ラスタライザステートをセット
		RasterizerState::getData(m_rasterizerStateId).setState();

		// シェーダーをセット
		VertexShader::getData(SystemVertexShaderId::Sprite).beginVertexShader();
		PixelShader::getData(SystemPixelShaderId::Sprite).beginShader();

		MeshData* meshDataPtr = Mesh::getDataPtr(SystemMeshId::Sprite);

		// 頂点バッファとインデックスバッファをレンダリングパイプラインに設定する
		meshDataPtr->setVertexAndIndexBuffer();

		meshDataPtr->setPrimitiveTopology();

		// ドローコール
		Screen::getDeviceContextPtr()->DrawIndexed(4, 0, 0);
	}

	int SpriteDrawer::getTextureId() const
	{
		return m_textureId;
	}

	void SpriteDrawer::setTextureUvOffset(const Vector2 & offset)
	{
		m_textureUvOffset = offset;
	}

	void SpriteDrawer::setTextureUvMulRate(const Vector2 & offset)
	{
		m_textureUvMulRate = offset;
	}

	void SpriteDrawer::setBlendRate(const Color & blendRate)
	{
		m_blendRate = blendRate;
	}

	void SpriteDrawer::setSpriteCenterRate(const Vector2 & centerRate)
	{
		m_spriteCenterRate = centerRate;
	}

	void SpriteDrawer::setTextureIdImpl(int id)
	{
		m_textureId = id;
	}

	void SpriteDrawer::setBlendStateIdImpl(int id)
	{
		m_blendStateId = id;
	}

	void SpriteDrawer::setDepthStencilStateIdImpl(int id)
	{
		m_depthStencilStateId = id;
	}

	void SpriteDrawer::setRasterizerStateIdImpl(int id)
	{
		m_rasterizerStateId = id;
	}
}