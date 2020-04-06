#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

#include <d3d12.h>
#include <dxgi1_6.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>
#include "../../Window/Window.h"

namespace tktk
{
	class DX3DBaseObjects
	{
	public:

		DX3DBaseObjects(
			HWND hwnd,
			const tktkMath::Vector2& windowSize
		);

	public:

		void update();

	private:

		ID3D12Device*				m_device			{ nullptr };
		IDXGIFactory6*				m_factory			{ nullptr };
		ID3D12CommandAllocator*		m_commandAllocator	{ nullptr };
		ID3D12GraphicsCommandList*	m_commandList		{ nullptr };
		ID3D12CommandQueue*			m_commandQueue		{ nullptr };
		IDXGISwapChain1*			m_swapChain			{ nullptr };
	};
}
#endif // !DX3D_BASE_OBJECTS_H_