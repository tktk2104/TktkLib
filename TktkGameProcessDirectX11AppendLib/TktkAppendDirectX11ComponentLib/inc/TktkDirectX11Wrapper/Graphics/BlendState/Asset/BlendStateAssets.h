#ifndef BLEND_STATE_ASSETS_H_
#define BLEND_STATE_ASSETS_H_

#include <unordered_map>
#include "BlendStateData.h"

namespace tktk
{
	class BlendStateAssets
	{
	public:

		BlendStateAssets() = default;
		~BlendStateAssets();

		// �R�s�[�֎~
		BlendStateAssets(const BlendStateAssets& other) = delete;
		BlendStateAssets& operator = (const BlendStateAssets& other) = delete;

	public:

		// �V���ȃu�����h�X�e�[�g���쐬����
		void create(int id, const D3D11_BLEND_DESC& blendDesc);

		// �w�肵���u�����h�X�e�[�g���폜����
		void erase(int id);

		// �S�Ẵu�����h�X�e�[�g���폜����
		void clear();

		// �w�肵���u�����h�X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����
		BlendStateData* getDataPtr(int id);

	private:

		// �u�����h�X�e�[�g���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, BlendStateData> m_assets;
	};
}
#endif // !BLEND_STATE_ASSETS_H_