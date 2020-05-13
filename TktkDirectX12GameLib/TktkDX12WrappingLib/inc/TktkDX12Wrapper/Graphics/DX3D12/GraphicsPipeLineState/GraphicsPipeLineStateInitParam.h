#ifndef GRAPHICS_PIPELINE_STATE_INIT_PARAM_H_
#define GRAPHICS_PIPELINE_STATE_INIT_PARAM_H_

#include <string>
#include <vector>
#include <d3d12.h>
#undef min
#undef max

namespace tktk
{
	struct GraphicsPipeLineStateInitParam
	{
		D3D12_RASTERIZER_DESC					m_rasterizerDesc{};
		D3D12_BLEND_DESC						m_blendDesc{};
		std::vector<D3D12_INPUT_ELEMENT_DESC>	m_inputLayoutArray{};
		D3D12_PRIMITIVE_TOPOLOGY_TYPE			m_primitiveTopology{};
		std::vector<DXGI_FORMAT>				m_renderTargetFormatArray{};
		bool									m_useDepth{ false };
		bool									m_writeDepth{ false };
		D3D12_COMPARISON_FUNC					m_depthFunc{};
	};

	struct ShaderFilePaths
	{
		std::string vsFilePath;
		std::string psFilePath;
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_INIT_PARAM_H_