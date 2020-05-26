#ifndef ROOT_SIGNATURE_H_
#define ROOT_SIGNATURE_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "RootSignatureData.h"

namespace tktk
{
	class RootSignature
	{
	public:

		RootSignature(unsigned int rootSignatureNum);

	public:

		void create(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

		ID3D12RootSignature* getPtr(unsigned int id) const;

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<RootSignatureData> m_rootSignatureDataArray;
	};
}
#endif // !ROOT_SIGNATURE_H_