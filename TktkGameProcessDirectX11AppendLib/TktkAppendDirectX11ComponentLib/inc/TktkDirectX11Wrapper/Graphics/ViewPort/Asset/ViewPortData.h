#ifndef VIEW_PORT_DATA_H_
#define VIEW_PORT_DATA_H_

#include <d3d11.h>
#include <TktkMath/Vector2.h>

namespace tktk
{
	// �r���[�|�[�g���Ǘ�����N���X
	class ViewPortData
	{
	public:

		ViewPortData(const Vector2& position, const Vector2& size);
		~ViewPortData();

		ViewPortData(const ViewPortData& other) = delete;
		ViewPortData& operator = (const ViewPortData& other) = delete;

	public:

		// �r���[�|�[�g�̎Q�Ƃ��擾����
		const D3D11_VIEWPORT& getViewPort() const;

	private:

		// �r���[�|�[�g
		D3D11_VIEWPORT m_viewPort{};
	};
}
#endif // !VIEW_PORT_DATA_H_