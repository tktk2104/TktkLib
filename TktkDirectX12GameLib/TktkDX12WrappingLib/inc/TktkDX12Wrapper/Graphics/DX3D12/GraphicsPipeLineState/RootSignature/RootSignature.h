#ifndef ROOT_SIGNATURE_H_
#define ROOT_SIGNATURE_H_

#include <array>
#include "RootSignatureData.h"

namespace tktk
{
	template <int RootSignatureNum>
	class RootSignature
	{
	public:

		RootSignature() = default;

	public:

		void create(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

		ID3D12RootSignature* getPtr(unsigned int id) const;

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::array<RootSignatureData, RootSignatureNum> m_rootSignatureDataArray{};
	};

	template<int RootSignatureNum>
	inline void RootSignature<RootSignatureNum>::create(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_rootSignatureDataArray.at(id).initialize(device, initParam);
	}

	template<int RootSignatureNum>
	inline ID3D12RootSignature* RootSignature<RootSignatureNum>::getPtr(unsigned int id) const
	{
		return m_rootSignatureDataArray.at(id).getPtr();
	}

	template<int RootSignatureNum>
	inline void RootSignature<RootSignatureNum>::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignatureDataArray.at(id).set(commandList);
	}
}
#endif // !ROOT_SIGNATURE_H_