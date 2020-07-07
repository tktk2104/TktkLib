#ifndef SCISSOR_RECT_H_
#define SCISSOR_RECT_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "ScissorRectData.h"

namespace tktk
{
	// �uScissorRectData�v���Ǘ�����N���X
	class ScissorRect
	{
	public:

		ScissorRect(unsigned int scissorRectNum);
		~ScissorRect() = default;

	public:

		// �uScissorRectData�v�̃C���X�^���X�����
		void create(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray);

		// �w��̃V�U�[��`���R�}���h���X�g�ɓo�^����
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		HeapArray<ScissorRectData> m_scissorRectDataArray;
	};
}
#endif // !SCISSOR_RECT_H_