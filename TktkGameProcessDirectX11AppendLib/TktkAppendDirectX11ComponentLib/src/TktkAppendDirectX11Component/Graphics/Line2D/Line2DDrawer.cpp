#include "TktkAppendDirectX11Component/Graphics/Line2D/Line2DDrawer.h"

#include <stdexcept>
#include <array>
#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendState.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilState.h"
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShader.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShader.h"
#include "TktkDirectX11Wrapper/Graphics/Line2D/ConstantBufferData/Line2DVertexConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Line2D/ConstantBufferData/Line2DPixelConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Line2D/VertexBufferData/Line2DVertexBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/RasterizerState/RasterizerState.h"

namespace tktk
{
	Line2DDrawer::Line2DDrawer(
		float drawPriority,
		const std::vector<Vector2>& lineVertexArray,
		const Color & lineColor,
		int blendStateId,
		int depthStencilStateId,
		const Color & blendRate
	)
		: ComponentBase(drawPriority)
		, m_lineVertexArray(lineVertexArray)
		, m_lineColor(lineColor)
		, m_blendStateId(blendStateId)
		, m_depthStencilStateId(depthStencilStateId)
		, m_blendRate(blendRate)
	{
	}

	void Line2DDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void Line2DDrawer::draw() const
	{
		std::array<float, 4> factor = { 1.0f, 1.0f, 1.0f, 1.0f };
		Screen::getDeviceContextPtr()->OMSetBlendState(BlendState::getDataPtr(m_blendStateId)->getStatePtr(), factor.data(), 0xffffffff);
		Screen::getDeviceContextPtr()->OMSetDepthStencilState(DepthStencilState::getDataPtr(m_depthStencilStateId)->getStatePtr(), 0);
	
		// 定数バッファに値を詰め詰めする
		ConstantBufferData* vertexConstantBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Line2DVertex);
		Line2DVertexConstantBufferData line2DVertexConstantBufferData;

		Matrix3 worldMat = m_transform->calculateWorldMatrix();

		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;

			line2DVertexConstantBufferData.worldMatrix[i] = worldMat.m[i / 4U][i % 4U];
		}

		line2DVertexConstantBufferData.screenSize = Window::getWindowSize();
		vertexConstantBufferData->setBufferData(std::move(line2DVertexConstantBufferData));
		vertexConstantBufferData->updateBuffer();

		ConstantBufferData* pixelConstantBufferData = ConstantBuffer::getDataPtr(SystemConstantBufferId::Line2DPixel);
		Line2DPixelConstantBufferData line2DPixelConstantBufferData;
		line2DPixelConstantBufferData.lineColor = m_lineColor;
		pixelConstantBufferData->setBufferData(std::move(line2DPixelConstantBufferData));
		pixelConstantBufferData->updateBuffer();

		// ラスタライザステートをセット
		RasterizerState::getData(SystemRasterizerStateId::Basic).setState();

		// シェーダーをセット
		VertexShader::getData(SystemVertexShaderId::Line2D).beginVertexShader();
		PixelShader::getData(SystemPixelShaderId::Line2D).beginShader();

		std::vector<Line2DVertexBufferData> vertexBufferData;
		vertexBufferData.reserve(m_lineVertexArray.size());

		for (unsigned int i = 0; i < m_lineVertexArray.size(); i++)
		{
			vertexBufferData.push_back({ m_lineVertexArray.at(i) });
		}

		// 頂点バッファを作成する
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(Line2DVertexBufferData) * vertexBufferData.size();
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subresourceData{};
		subresourceData.pSysMem = vertexBufferData.data();

		ID3D11Buffer* vertexBufferPtr;
		Screen::getDevicePtr()->CreateBuffer(&desc, &subresourceData, &vertexBufferPtr);

		unsigned int stride = sizeof(Vector2);
		unsigned int offset = 0U;

		// 頂点バッファをセットする
		Screen::getDeviceContextPtr()->IASetVertexBuffers(
			0,
			1,
			&vertexBufferPtr,
			&stride,
			&offset
		);

		// ドローコール
		Screen::getDeviceContextPtr()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
		Screen::getDeviceContextPtr()->Draw(m_lineVertexArray.size(), 0);

		// 使用済み頂点バッファを開放する
		vertexBufferPtr->Release();
	}

	const std::vector<Vector2>& Line2DDrawer::getLineVertexArray() const
	{
		return m_lineVertexArray;
	}

	void Line2DDrawer::setLineVertexArray(const std::vector<Vector2>& vertexArray)
	{
		m_lineVertexArray = vertexArray;
	}

	const Color & Line2DDrawer::getLineColor() const
	{
		return m_lineColor;
	}

	void Line2DDrawer::setLineColor(const Color & color)
	{
		m_lineColor = color;
	}

	void Line2DDrawer::setBlendRate(const Color & blendRate)
	{
		m_blendRate = blendRate;
	}

	void Line2DDrawer::setBlendStateIdImpl(int id)
	{
		m_blendStateId = id;
	}

	void Line2DDrawer::setDepthStencilStateIdImpl(int id)
	{
		m_depthStencilStateId = id;
	}
}