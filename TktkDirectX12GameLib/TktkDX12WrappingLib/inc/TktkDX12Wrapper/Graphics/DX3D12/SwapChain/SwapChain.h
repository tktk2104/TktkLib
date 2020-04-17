#ifndef SWAP_CHAIN_H_
#define SWAP_CHAIN_H_

#include <d3d12.h>
#include <dxgi1_6.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	class SwapChain
	{
	public:

		SwapChain() = default;
		~SwapChain();

	public:

		void initialize(HWND hwnd, IDXGIFactory6* factory, ID3D12CommandQueue* commandQueue, const tktkMath::Vector2& windowSize);

		// TODO : ‚à‚Á‚ÆƒJƒvƒZƒ‹‰»‚·‚é
		IDXGISwapChain1* getPtr() const;

	private:

		IDXGISwapChain1*	m_swapChain{ nullptr };
		unsigned int		m_curBackBufferIndex{ 0U };
	};
}
#endif // !SWAP_CHAIN_H_
