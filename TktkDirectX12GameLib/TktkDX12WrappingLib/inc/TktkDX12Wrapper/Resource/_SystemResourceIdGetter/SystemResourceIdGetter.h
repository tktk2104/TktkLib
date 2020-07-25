#ifndef SYSTEM_RESOURCE_ID_GETTER_H_
#define SYSTEM_RESOURCE_ID_GETTER_H_

#include "SystemResourceType.h"
#include "../DX3DResourceInitParam.h"

namespace tktk
{
	// �V�X�e���̎g�p���Ă��郊�\�[�X�̎�ނ��烊�\�[�XID���擾����
	class SystemResourceIdGetter
	{
	public:

		// �R���X�g���N�^���ŁuinitParam�v�̒l�����������܂�
		SystemResourceIdGetter(DX3DResourceInitParam* initParam);

	public:

		unsigned int getSystemId(SystemViewportType type)				const;
		unsigned int getSystemId(SystemScissorRectType type)			const;
		unsigned int getSystemId(SystemVertexBufferType type)			const;
		unsigned int getSystemId(SystemIndexBufferType type)			const;
		unsigned int getSystemId(SystemCBufferType type)				const;
		unsigned int getSystemId(SystemTextureBufferType type)			const;
		unsigned int getSystemId(SystemRtBufferType type)				const;
		unsigned int getSystemId(SystemDsBufferType type)				const;
		unsigned int getSystemId(SystemBasicDescriptorHeapType type)	const;
		unsigned int getSystemId(SystemRtvDescriptorHeapType type)		const;
		unsigned int getSystemId(SystemDsvDescriptorHeapType type)		const;
		unsigned int getSystemId(SystemRootSignatureType type)			const;
		unsigned int getSystemId(SystemPipeLineStateType type)			const;

	private:

		DX3DResourceInitParam m_basicResourceNum;
	};
}
#endif // !SYSTEM_RESOURCE_ID_GETTER_H_