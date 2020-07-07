#ifndef VIEWPORT_DATA_H_
#define VIEWPORT_DATA_H_

#include <vector>
#include <d3d12.h>
#undef min
#undef max
#include "ViewportInitParam.h"

namespace tktk
{
	// �r���[�|�[�g���Ǘ�����N���X
	class ViewportData
	{
	public:

		ViewportData(const std::vector<ViewportInitParam>& initParamArray);
		~ViewportData() = default;

	public:

		// ���g���R�}���h���X�g�ɓo�^����
		void set(ID3D12GraphicsCommandList* commandList) const;
	
	private:

		std::vector<D3D12_VIEWPORT> m_viewportArray{};
	};
}
#endif // !VIEWPORT_DATA_H_