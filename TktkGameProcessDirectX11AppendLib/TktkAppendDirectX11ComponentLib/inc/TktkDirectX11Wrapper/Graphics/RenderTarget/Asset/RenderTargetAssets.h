#ifndef RENDER_TARGET_ASSETS_H_
#define RENDER_TARGET_ASSETS_H_

#include <unordered_map>
#include "RenderTargetData.h"

namespace tktk
{
	// �uRenderTargetData�v���Ǘ�����N���X
	class RenderTargetAssets
	{
	public:

		RenderTargetAssets();
		~RenderTargetAssets();

		RenderTargetAssets(const RenderTargetAssets& other) = delete;
		RenderTargetAssets& operator = (const RenderTargetAssets& other) = delete;

	public:

		// �V���ȃ����_�[�^�[�Q�b�g�𐶐�����
		void create(int id, ID3D11Texture2D* renderTargetTexture);

		// �w�肵�������_�[�^�[�Q�b�g���폜����
		void erase(int id);

		// �S�Ẵ����_�[�^�[�Q�b�g���폜����
		void clear();

		// �w�肵�������_�[�^�[�Q�b�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		const RenderTargetData& getData(int id) const;

	private:

		// �����_�[�^�[�Q�b�g���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, RenderTargetData> m_assets;
	};
}
#endif // !RENDER_TARGET_ASSETS_H_