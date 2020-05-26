#ifndef SCISSOR_RECT_H_
#define SCISSOR_RECT_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "ScissorRectData.h"

namespace tktk
{
	class ScissorRect
	{
	public:

		ScissorRect(unsigned int scissorRectNum);

	public:

		void create(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		HeapArray<ScissorRectData> m_scissorRectDataArray;
	};
}
#endif // !SCISSOR_RECT_H_