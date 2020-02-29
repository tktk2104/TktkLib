#ifndef DEPTH_STENCIL_VIEW_ASSETS_H_
#define DEPTH_STENCIL_VIEW_ASSETS_H_

#include <unordered_map>
#include "DepthStencilViewData.h"

namespace tktk
{
	// �uDepthStencilViewData�v���Ǘ�����N���X
	class DepthStencilViewAssets
	{
	public:

		DepthStencilViewAssets();
		~DepthStencilViewAssets();

		DepthStencilViewAssets(const DepthStencilViewAssets& other) = delete;
		DepthStencilViewAssets& operator = (const DepthStencilViewAssets& other) = delete;

	public:

		// �V���Ȑ[�x�r���[���쐬����
		void create(int id, const Vector2& useTextureSize);

		// �w�肵���[�x�r���[���폜����
		void erase(int id);

		// �S�Ă̐[�x�r���[���폜����
		void clear();

		// �w�肵���[�x�r���[���Ǘ�����N���X�̎Q�Ƃ��擾����
		const DepthStencilViewData& getData(int id) const;

	private:

		// �[�x�r���[���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, DepthStencilViewData> m_assets;
	};
}
#endif // !DEPTH_STENCIL_VIEW_ASSETS_H_