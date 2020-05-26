#ifndef ROOT_SIGNATURE_DATA_H_
#define ROOT_SIGNATURE_DATA_H_

#include <d3d12.h>
#include "RootSignatureInitParam.h"

namespace tktk
{
	class RootSignatureData
	{
	public:

		RootSignatureData(ID3D12Device* device, const RootSignatureInitParam& initParam);
		~RootSignatureData();

	public:

		ID3D12RootSignature* getPtr() const;

		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		ID3D12RootSignature* m_rootSignature{ nullptr };
	};
}
#endif // !ROOT_SIGNATURE_DATA_H_