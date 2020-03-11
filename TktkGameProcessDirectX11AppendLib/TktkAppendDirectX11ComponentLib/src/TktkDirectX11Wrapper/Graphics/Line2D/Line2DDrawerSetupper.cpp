#include "TktkDirectX11Wrapper/Graphics/Line2D/Line2DDrawerSetupper.h"

#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShaderManager.h"
#include "TktkDirectX11Wrapper/Graphics/Line2D/ConstantBufferData/Line2DVertexConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Line2D/ConstantBufferData/Line2DPixelConstantBufferData.h"

namespace tktk
{
	void Line2DDrawerSetupper::setUp(
		const std::string & line2DPixelShaderFileName,
		const std::string & line2DVertexShaderFileName
	)
	{
		ConstantBufferManager::create(SystemConstantBufferId::Line2DVertex, new Line2DVertexConstantBufferData());
		ConstantBufferManager::create(SystemConstantBufferId::Line2DPixel, new Line2DPixelConstantBufferData());

		PixelShaderManager::load(
			SystemPixelShaderId::Line2D,
			line2DPixelShaderFileName,
			SystemConstantBufferId::Line2DPixel
		);

		std::vector<D3D11_INPUT_ELEMENT_DESC> line2dVertexLayout = std::vector<D3D11_INPUT_ELEMENT_DESC>({
			{ "POSITION",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			});

		VertexShaderManager::load(
			SystemVertexShaderId::Line2D,
			line2DVertexShaderFileName,
			line2dVertexLayout,
			SystemConstantBufferId::Line2DVertex
		);
	}
}