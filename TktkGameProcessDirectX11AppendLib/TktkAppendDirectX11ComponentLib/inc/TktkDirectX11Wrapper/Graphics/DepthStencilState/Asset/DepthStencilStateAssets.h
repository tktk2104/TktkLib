#ifndef DEPTH_STENCIL_STATE_ASSETS_H_
#define DEPTH_STENCIL_STATE_ASSETS_H_

#include <unordered_map>
#include "DepthStencilStateData.h"

namespace tktk
{
	class DepthStencilStateAssets
	{
	public:

		DepthStencilStateAssets() = default;
		~DepthStencilStateAssets();

		// �R�s�[�֎~
		DepthStencilStateAssets(const DepthStencilStateAssets& other) = delete;
		DepthStencilStateAssets& operator = (const DepthStencilStateAssets& other) = delete;

	public:

		// �V���Ȑ[�x�X�e���V���X�e�[�g���쐬����
		void create(int id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);

		// �w�肵���[�x�X�e���V���X�e�[�g���폜����
		void erase(int id);

		// �S�Ă̐[�x�X�e���V���X�e�[�g���폜����
		void clear();

		// �w�肵���[�x�X�e���V���X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����
		DepthStencilStateData* getDataPtr(int id);

	private:

		std::unordered_map<int, DepthStencilStateData> m_assets;
	};
}
#endif // !DEPTH_STENCIL_STATE_ASSETS_H_