#ifndef DESCRIPTOR_RANGE_DATA_H_
#define DESCRIPTOR_RANGE_DATA_H_

#include <d3d12.h>

namespace tktk
{
	class DescriptorRangeData
	{
	public:

		enum class Type
		{
			shaderResourceView		= D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
			unorderedAccessViews	= D3D12_DESCRIPTOR_RANGE_TYPE_UAV,
			constantBufferViews		= D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
			samplers				= D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER
		};

	public:

		DescriptorRangeData() = default;
		~DescriptorRangeData() = default;

	public:

		void initialize(unsigned int numDescriptors, Type type);

		

	private:

		D3D12_DESCRIPTOR_RANGE m_descriptorRange{ };
	};
}
#endif // !DESCRIPTOR_RANGE_DATA_H_