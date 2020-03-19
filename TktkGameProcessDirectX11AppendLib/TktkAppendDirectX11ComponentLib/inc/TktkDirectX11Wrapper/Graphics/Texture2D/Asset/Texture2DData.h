#ifndef TEXTURE_2D_DATA_H_
#define TEXTURE_2D_DATA_H_

#include <string>
#include <vector>
#include <d3d11.h>
#include "Texture2DBindFlag.h"
#include "Texture2DUsage.h"
#include "Texture2DCpuAccessFlag.h"

namespace tktk
{
	// 2D�e�N�X�`�����Ǘ�����N���X
	class Texture2DData
	{
	public:

		Texture2DData(
			Texture2DBindFlag bindFlag,
			const std::vector<D3D11_SUBRESOURCE_DATA>& subrescorceDataArray,
			unsigned int width,
			unsigned int height,
			unsigned int mipCount,
			unsigned int arraySize,
			DXGI_FORMAT format,
			Texture2DUsage usage,
			Texture2DCpuAccessFlag cpuAccessFlag,
			bool isCubeMap
		);

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

		// �}�b�v���ꂽ�T�u���\�[�X���擾����
		// �����̊֐��̖߂�l�̎g�p���I�������͕K���uunMapSubResource()�v���Ă�ł�������
		D3D11_MAPPED_SUBRESOURCE mapSubResource() const;

		// �umapSubResource()�v��Map�������\�[�X��Unmap����
		void unMapSubResource() const;

	private:

		ID3D11Texture2D* m_texturePtr{ nullptr };
		ID3D11ShaderResourceView* m_shaderResouceViewPtr{ nullptr };
		ID3D11SamplerState* m_samplerPtr{ nullptr };
		unsigned int m_width;
		unsigned int m_height;
		bool m_isAfterChange;
	};
}
#endif // !TEXTURE_2D_DATA_H_