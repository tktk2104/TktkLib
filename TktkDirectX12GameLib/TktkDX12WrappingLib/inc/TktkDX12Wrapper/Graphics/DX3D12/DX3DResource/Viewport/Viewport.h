#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "ViewportData.h"

namespace tktk
{
	// �uViewportData�v���Ǘ�����N���X
	class Viewport
	{
	public:

		Viewport(unsigned int viewportNum);

	public:

		// �uViewportData�v�̃C���X�^���X�����
		void create(unsigned int id, const std::vector<ViewportInitParam>& initParamArray);

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɓo�^����
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		HeapArray<ViewportData> m_viewportDataArray;
	};
}
#endif // !VIEWPORT_H_