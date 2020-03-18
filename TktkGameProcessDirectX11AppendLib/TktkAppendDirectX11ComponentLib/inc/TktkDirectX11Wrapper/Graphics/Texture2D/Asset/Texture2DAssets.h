#ifndef TEXTURE_ASSETS_H_
#define TEXTURE_ASSETS_H_

#include <string>
#include <unordered_map>
#include "Texture2DData.h"

namespace tktk
{
	// �uTexture2DData�v���Ǘ�����N���X
	class Texture2DAssets
	{
	public:

		Texture2DAssets() = default;
		~Texture2DAssets();

		Texture2DAssets(const Texture2DAssets& other) = delete;
		Texture2DAssets& operator = (const Texture2DAssets& other) = delete;

	public:

		// �V����2D�e�N�X�`�����쐬����
		void create(
			int id,
			Texture2DBindFlag bindFlag,
			const std::vector<unsigned char>& textureData,
			unsigned int width,
			unsigned int height,
			unsigned int mipCount,
			unsigned int arraySize,
			DXGI_FORMAT format,
			bool isCubeMap
		);

		// �V����2D�e�N�X�`�������[�h����
		void load(int id, const std::string& fileName);

		// �w�肵��2D�e�N�X�`�����폜����
		void erase(int id);

		// �S�Ă�2D�e�N�X�`�����폜����
		void clear();

		// �w�肵��2D�e�N�X�`�����Ǘ�����N���X�̎Q�Ƃ��擾����
		const Texture2DData& getData(int id);

	private:

		// 2D�e�N�X�`�����Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, Texture2DData> m_texture2DAssets;
	};
}
#endif // !TEXTURE_ASSETS_H_