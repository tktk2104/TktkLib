#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "ViewportData.h"

namespace tktk
{
	class Viewport
	{
	public:

		Viewport(unsigned int viewportNum);

	public:

		void create(unsigned int id, const std::vector<ViewportInitParam>& initParamArray);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		HeapArray<ViewportData> m_viewportDataArray;
	};
}
#endif // !VIEWPORT_H_