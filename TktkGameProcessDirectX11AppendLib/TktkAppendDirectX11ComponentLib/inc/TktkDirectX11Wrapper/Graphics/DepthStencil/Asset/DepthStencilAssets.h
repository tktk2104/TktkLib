#ifndef DEPTH_STENCIL_ASSETS_H_
#define DEPTH_STENCIL_ASSETS_H_

#include <unordered_map>
#include "DepthStencilData.h"

namespace tktk
{
	// �uDepthStencilData�v���Ǘ�����N���X
	class DepthStencilAssets
	{
	public:

		DepthStencilAssets();
		~DepthStencilAssets();

		DepthStencilAssets(const DepthStencilAssets& other) = delete;
		DepthStencilAssets& operator = (const DepthStencilAssets& other) = delete;

	public:

		// �V���Ȑ[�x�r���[���쐬����
		void create(int id, const Vector2& useTextureSize);

		// �w�肵���[�x�r���[���폜����
		void erase(int id);

		// �S�Ă̐[�x�r���[���폜����
		void clear();

		// �w�肵���[�x�r���[���Ǘ�����N���X�̎Q�Ƃ��擾����
		const DepthStencilData& getData(int id) const;

	private:

		// �[�x�r���[���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, DepthStencilData> m_assets;
	};
}
#endif // !DEPTH_STENCIL_ASSETS_H_