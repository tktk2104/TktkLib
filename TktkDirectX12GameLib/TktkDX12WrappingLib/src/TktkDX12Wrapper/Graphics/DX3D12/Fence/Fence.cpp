#include "TktkDX12Wrapper/Graphics/DX3D12/Fence/Fence.h"

namespace tktk
{
	Fence::~Fence()
	{
		if (m_fence != nullptr)
		{
			m_fence->Release();
		}
	}

	void Fence::initialize(ID3D12Device* device)
	{
		device->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
	}

	void Fence::waitGpuProcess(ID3D12CommandQueue* commandQueue)
	{
		// GPU�������I������������m���邽�߂̏���
		commandQueue->Signal(m_fence, ++m_fenceVal);

		// ����GPU�������I����Ă��Ȃ����
		if (m_fence->GetCompletedValue() != m_fenceVal)
		{
			// �C�x���g������Ă��̃n���h�����擾
			auto eventHandle = CreateEvent(nullptr, false, false, nullptr);

			// �t�F���X��GPU�������I�������C�x���g�𔭐������鎖��ݒ肷��
			m_fence->SetEventOnCompletion(m_fenceVal, eventHandle);

			// �t�F���X�Ɏw�肵���C�x���g����������܂Ŗ����ɑ҂�������
			WaitForSingleObject(eventHandle, INFINITE);

			// �C�x���g�n���h�������
			CloseHandle(eventHandle);
		}
	}
}