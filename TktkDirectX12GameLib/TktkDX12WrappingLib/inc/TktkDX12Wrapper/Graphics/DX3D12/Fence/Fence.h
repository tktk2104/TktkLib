#ifndef FENCE_H_
#define FENCE_H_

#include <d3d12.h>

namespace tktk
{
	class Fence
	{
	public:

		Fence() = default;
		~Fence();

	public:

		void initialize(ID3D12Device* device);

		void waitGpuProcess(ID3D12CommandQueue* commandQueue);

	private:

		ID3D12Fence* m_fence{ nullptr };
		unsigned int m_fenceVal{ 0U };
	};
}
#endif // !FENCE_H_