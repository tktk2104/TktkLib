#ifndef ROOT_SIGNATURE_DATA_H_
#define ROOT_SIGNATURE_DATA_H_

#include <d3d12.h>

namespace tktk
{
	class RootSignatureData
	{
	public:

		RootSignatureData() = default;
		~RootSignatureData();

	public:

		void initialize(ID3D12Device* device);



	private:

		ID3D12RootSignature* m_rootSignature{ nullptr };
	};
}
#endif // !ROOT_SIGNATURE_DATA_H_