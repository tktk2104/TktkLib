#ifndef FENCE_H_
#define FENCE_H_

#include <d3d12.h>

namespace tktk
{
	// GPU�̏�����҂t�F���X���Ǘ�����N���X
	class Fence
	{
	public:

		Fence() = default;
		~Fence();

	public:

		// ������
		void initialize(ID3D12Device* device);

		// GPU�̏������I���܂őҋ@����
		void waitGpuProcess(ID3D12CommandQueue* commandQueue);

	private:

		ID3D12Fence* m_fence{ nullptr };
		unsigned int m_fenceVal{ 0U };
	};
}
#endif // !FENCE_H_