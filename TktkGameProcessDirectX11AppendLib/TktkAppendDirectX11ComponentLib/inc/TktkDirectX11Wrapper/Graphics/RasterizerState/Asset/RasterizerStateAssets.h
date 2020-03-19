#ifndef RASTERIZER_STATE_ASSETS_H_
#define RASTERIZER_STATE_ASSETS_H_

#include <unordered_map>
#include "RasterizerStateData.h"

namespace tktk
{
	// �uRasterizerStateData�v���Ǘ�����N���X
	class RasterizerStateAssets
	{
	public:

		RasterizerStateAssets() = default;
		~RasterizerStateAssets();

		// �R�s�[�֎~
		RasterizerStateAssets(const RasterizerStateAssets& other) = delete;
		RasterizerStateAssets& operator = (const RasterizerStateAssets& other) = delete;
	
	public:

		// �V���ȃ��X�^���C�U�X�e�[�g���쐬����
		void create(int id, const D3D11_RASTERIZER_DESC& desc);

		// �w�肵�����X�^���C�U�X�e�[�g���폜����
		void erase(int id);

		// �S�Ẵ��X�^���C�U�X�e�[�g���폜����
		void clear();
	
		// �w�肵�����X�^���C�U�X�e�[�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		const RasterizerStateData& getData(int id) const;
	
	private:

		// ���X�^���C�U�X�e�[�g���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, RasterizerStateData> m_assets;
	};
}
#endif // !RASTERIZER_STATE_ASSETS_H_