#ifndef TEXTURE_2D_DATA_H_
#define TEXTURE_2D_DATA_H_

#include <string>
#include <vector>
#include <d3d11.h>

namespace tktk
{
	// 2D�e�N�X�`�����Ǘ�����N���X
	class Texture2DData
	{
	public:

		Texture2DData(unsigned char* data, unsigned int dataSize);
		explicit Texture2DData(const std::string& fileName);
		~Texture2DData();

		Texture2DData(const Texture2DData& other) = delete;
		Texture2DData& operator = (const Texture2DData& other) = delete;

	public:

		// 2D�e�N�X�`���̃|�C���^���擾����
		ID3D11Texture2D* getTexture2DPtr() const;

		// 2D�e�N�X�`���̃V�F�[�_�[���\�[�X�r���[�̃|�C���^���擾����
		ID3D11ShaderResourceView* getShaderResourceViewPtr() const;

		// 2D�e�N�X�`���̃T���v���[�X�e�[�g�̃|�C���^���擾����
		ID3D11SamplerState* getSamplerStatePtr() const;

		// 2D�e�N�X�`���̉������擾����
		unsigned int width() const;

		// 2D�e�N�X�`���̗������擾����
		unsigned int height() const;

	private:

		void createTextrue2D(const std::vector<unsigned char>& image);
		void createShaderResourceView();
		void createSamplerState();

	private:

		ID3D11Texture2D* m_texturePtr{ nullptr };
		ID3D11ShaderResourceView* m_shaderResouceViewPtr{ nullptr };
		ID3D11SamplerState* m_samplerPtr{ nullptr };
		unsigned int m_width;
		unsigned int m_height;
	};
}
#endif // !TEXTURE_2D_DATA_H_