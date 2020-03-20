#include "TktkAppendDirectX11Component/Graphics/Sprite/SpriteClippingDrawer.h"

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
	SpriteClippingDrawer::SpriteClippingDrawer(
		float drawPriority,
		int textureId,
		int blendStateId,
		int depthStencilStateId,
		int rasterizerStateId,
		const Vector2 & textureClippingLeftTopPos,
		const Vector2 & textureClippingSize,
		const Vector2 & textureUvMulRate,
		const Color & blendRate,
		const Vector2 & spriteCenterRate
	)
		: ComponentBase(drawPriority)
		, m_textureId(textureId)
		, m_blendStateId(blendStateId)
		, m_depthStencilStateId(depthStencilStateId)
		, m_rasterizerStateId(rasterizerStateId)
		, m_textureClippingLeftTopPos(textureClippingLeftTopPos)
		, m_textureClippingSize(textureClippingSize)
		, m_textureUvMulRate(textureUvMulRate)
		, m_blendRate(blendRate)
		, m_spriteCenterRate(spriteCenterRate)
	{
	}

	void SpriteClippingDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void SpriteClippingDrawer::draw() const
	{
		const Texture2DData& texture2DData = Texture2D::getData(m_textureId);
		ID3D11ShaderResourceView* shaderResourceView = texture2DData.getShaderResourceViewPtr();
		ID3D11SamplerState* samplerState = texture2DData.getSamplerStatePtr();

		std::array<float, 4> factor = { 1.0f, 1.0f, 1.0f, 1.0f };
		Screen::getDeviceContextPtr()->OMSetBlendState(BlendState::getDataPtr(m_blendStateId)->getStatePtr(), factor.data(), 0xffffffff);
		Screen::getDeviceContextPtr()->OMSetDepthStencilState(DepthStencilState::getDataPtr(m_depthStencilStateId)->getStatePtr(), 0);

		Screen::getDeviceContextPtr()->PSSetShaderResources(0, 1, &shaderResourceView);
		Screen::getDeviceContextPtr()->PSSetSamplers(0, 1, &samplerState);

		// �萔�o�b�t�@�ɒl���l�ߋl�߂���
		ConstantBufferData* constantBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Sprite);

		SpriteConstantBufferData spriteConstantBufferData;
		spriteConstantBufferData.textureUvOffset = Vector2(m_textureClippingLeftTopPos.x / texture2DData.width(), m_textureClippingLeftTopPos.y / texture2DData.height());
		spriteConstantBufferData.textureUvMulRate = Vector2(m_textureClippingSize.x / texture2DData.width() * m_textureUvMulRate.x, m_textureClippingSize.y / texture2DData.height() * m_textureUvMulRate.y);
		spriteConstantBufferData.textureSize = m_textureClippingSize;
		spriteConstantBufferData.spritePosition = m_transform->getWorldPosition();
		spriteConstantBufferData.spriteScaleRate = m_transform->getWorldScaleRate();
		spriteConstantBufferData.spriteAngleDeg = m_transform->getWorldRotationDeg();
		spriteConstantBufferData.blendRate = m_blendRate;
		spriteConstantBufferData.spriteCenterRate = m_spriteCenterRate;
		spriteConstantBufferData.screenSize = Window::getWindowSize();
		constantBufferData->setBufferData(std::move(spriteConstantBufferData));

		constantBufferData->updateBuffer();

		// ���X�^���C�U�X�e�[�g���Z�b�g
		RasterizerState::getData(m_rasterizerStateId).setState();

		// �V�F�[�_�[���Z�b�g
		VertexShader::getData(SystemVertexShaderId::Sprite).beginVertexShader();
		PixelShader::getData(SystemPixelShaderId::Sprite).beginShader();

		MeshData* meshDataPtr = Mesh::getDataPtr(SystemMeshId::Sprite);

		// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ肷��
		meshDataPtr->setVertexAndIndexBuffer();

		meshDataPtr->setPrimitiveTopology();

		// �h���[�R�[��
		Screen::getDeviceContextPtr()->DrawIndexed(4, 0, 0);
	}

	void SpriteClippingDrawer::setTextureClippingLeftTopPos(const Vector2 & leftTopPos)
	{
		m_textureClippingLeftTopPos = leftTopPos;
	}

	void SpriteClippingDrawer::setTextureClippingSize(const Vector2 & size)
	{
		m_textureClippingSize = size;
	}

	void SpriteClippingDrawer::setTextureUvMulRate(const Vector2 & offset)
	{
		m_textureUvMulRate = offset;
	}

	void SpriteClippingDrawer::setBlendRate(const Color & blendRate)
	{
		m_blendRate = blendRate;
	}

	void SpriteClippingDrawer::setSpriteCenterRate(const Vector2 & centerRate)
	{
		m_spriteCenterRate = centerRate;
	}

	void SpriteClippingDrawer::setTextureIdImpl(int id)
	{
		m_textureId = id;
	}

	void SpriteClippingDrawer::setBlendStateIdImpl(int id)
	{
		m_blendStateId = id;
	}

	void SpriteClippingDrawer::setDepthStencilStateIdImpl(int id)
	{
		m_depthStencilStateId = id;
	}

	void SpriteClippingDrawer::setRasterizerStateIdImpl(int id)
	{
		m_rasterizerStateId = id;
	}
}