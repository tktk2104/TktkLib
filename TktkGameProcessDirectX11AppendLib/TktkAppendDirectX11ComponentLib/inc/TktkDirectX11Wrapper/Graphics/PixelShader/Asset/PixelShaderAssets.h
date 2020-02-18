#ifndef PIXEL_SHADER_ASSETS_H_
#define PIXEL_SHADER_ASSETS_H_

#include <unordered_map>
#include "PixelShaderData.h"
#include "SystemPixelShaderId.h"

namespace tktk
{
	// �uPixelShaderData�v���Ǘ�����N���X
	class PixelShaderAssets
	{
	public:

		PixelShaderAssets() = default;
		~PixelShaderAssets();

		PixelShaderAssets(const PixelShaderAssets& other) = delete;
		PixelShaderAssets& operator = (const PixelShaderAssets& other) = delete;

	public:

		// �V���ȃs�N�Z���V�F�[�_�[�����[�h����
		void load(int id, int useConstantBufferId, const std::string& fileName);

		// �w�肵���s�N�Z���V�F�[�_�[���폜����
		void erase(int id);

		// �S�Ẵs�N�Z���V�F�[�_�[���폜����
		void clear();

		// �w�肵���s�N�Z���V�F�[�_�[���Ǘ�����N���X�̎Q�Ƃ��擾����
		const PixelShaderData& getData(int id) const;

	private:

		// �s�N�Z���V�F�[�_�[���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, PixelShaderData> m_assets;
	};
}
#endif // !PIXEL_SHADER_ASSETS_H_