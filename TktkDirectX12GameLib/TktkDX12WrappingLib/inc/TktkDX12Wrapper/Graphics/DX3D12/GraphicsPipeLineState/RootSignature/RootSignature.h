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

		template <int RootSignatureIndex>
		void create(ID3D12Device* device, const RootSignatureInitParam& initParam);

		template <int RootSignatureIndex>
		ID3D12RootSignature* getPtr() const;

		template <int RootSignatureIndex>
		void set(ID3D12GraphicsCommandList* commandList) const;

		void set(int rootSignatureIndex, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::array<RootSignatureData, RootSignatureNum> m_rootSignatureDataArray{};
	};

	template<int RootSignatureNum>
	template<int RootSignatureIndex>
	inline void RootSignature<RootSignatureNum>::create(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_rootSignatureDataArray.at(RootSignatureIndex).initialize(device, initParam);
	}

	template<int RootSignatureNum>
	template<int RootSignatureIndex>
	inline ID3D12RootSignature* RootSignature<RootSignatureNum>::getPtr() const
	{
		return m_rootSignatureDataArray.at(RootSignatureIndex).getPtr();
	}

	template<int RootSignatureNum>
	template<int RootSignatureIndex>
	inline void RootSignature<RootSignatureNum>::set(ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignatureDataArray.at(RootSignatureIndex).set(commandList);
	}

	template<int RootSignatureNum>
	inline void RootSignature<RootSignatureNum>::set(int rootSignatureIndex, ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignatureDataArray.at(rootSignatureIndex).set(commandList);
	}
}
#endif // !ROOT_SIGNATURE_H_