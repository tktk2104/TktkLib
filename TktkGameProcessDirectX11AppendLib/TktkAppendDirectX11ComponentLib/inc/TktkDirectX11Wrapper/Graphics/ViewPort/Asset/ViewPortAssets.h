#ifndef VIEW_PORT_ASSETS_H_
#define VIEW_PORT_ASSETS_H_

#include <unordered_map>
#include "ViewPortData.h"

namespace tktk
{
	class ViewPortAssets
	{
	public:

		ViewPortAssets() = default;
		~ViewPortAssets();

		ViewPortAssets(const ViewPortAssets& other) = delete;
		ViewPortAssets& operator = (const ViewPortAssets& other) = delete;

	public:

		// �V���ȃr���[�|�[�g�𐶐�����
		void create(int id, const Vector2& position, const Vector2& size);

		// �w�肵���r���[�|�[�g���폜����
		void erase(int id);

		// �S�Ẵr���[�|�[�g���폜����
		void clear();

		// �w�肵���r���[�|�[�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		const ViewPortData& getData(int id) const;

	private:

		// �r���[�|�[�g���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, ViewPortData> m_assets;
	};
}
#endif // !VIEW_PORT_ASSETS_H_