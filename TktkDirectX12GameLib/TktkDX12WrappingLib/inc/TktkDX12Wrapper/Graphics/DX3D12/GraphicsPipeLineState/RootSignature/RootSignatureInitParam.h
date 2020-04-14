#ifndef ROOT_SIGNATURE_INIT_PARAM_H_
#define ROOT_SIGNATURE_INIT_PARAM_H_

#include <vector>
#include <d3d12.h>

namespace tktk
{
	struct RootSignatureInitParam
	{
	public:

		struct DescriptorRange
		{
			unsigned int					m_numDescriptors{};
			D3D12_DESCRIPTOR_RANGE_TYPE		m_type{};
		};

		struct RootParam
		{
			D3D12_SHADER_VISIBILITY			m_shaderVisibility{};
			std::vector<DescriptorRange>	m_descriptorTableArray{};
		};

		struct SamplerDesc
		{
			D3D12_TEXTURE_ADDRESS_MODE	m_addressU{};
			D3D12_TEXTURE_ADDRESS_MODE	m_addressV{};
			D3D12_TEXTURE_ADDRESS_MODE	m_addressW{};
			D3D12_STATIC_BORDER_COLOR	m_bordercolor{};
			D3D12_FILTER				m_filter{};
			float						m_minLod{};
			float						m_maxLod{};
			D3D12_SHADER_VISIBILITY		m_shaderVisibility{};
			D3D12_COMPARISON_FUNC		m_comparisonFunc{};
		};

	public:

		D3D12_ROOT_SIGNATURE_FLAGS	m_flag{};
		std::vector<RootParam>		m_rootParamArray{};
		std::vector<SamplerDesc>	m_samplerDescArray{};
	};
}
#endif // !ROOT_SIGNATURE_INIT_PARAM_H_