#ifndef GRAPHICS_PIPELINE_STATE_INIT_PARAM_H_
#define GRAPHICS_PIPELINE_STATE_INIT_PARAM_H_

#include <string>
#include <vector>
#include <d3d12.h>

namespace tktk
{
	struct GraphicsPipeLineStateInitParam
	{
		D3D12_RASTERIZER_DESC					m_rasterizerDesc{};
		D3D12_BLEND_DESC						m_blendDesc{};
		std::vector<D3D12_INPUT_ELEMENT_DESC>	m_inputLayoutArray{};
		D3D12_PRIMITIVE_TOPOLOGY_TYPE			m_primitiveTopology{};
		std::vector<DXGI_FORMAT>				m_renderTargetFormatArray{};
	};

	struct ShaderFilePaths
	{
		std::string vsFilePath;
		std::string psFilePath;
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_INIT_PARAM_H_