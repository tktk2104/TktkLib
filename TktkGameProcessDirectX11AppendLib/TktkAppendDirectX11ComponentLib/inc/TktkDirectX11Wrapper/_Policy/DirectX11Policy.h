#ifndef DIRECTX_11_POLICY_H_
#define DIRECTX_11_POLICY_H_

#include <string>
#include <TktkMath/Vector2.h>
#include "TktkDirectX11Wrapper/Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	class DirectX11Policy
	{
	public:

		DirectX11Policy(
			HINSTANCE hInstance,
			int nCmdShow,
			const std::string & windowName,
			const Vector2& gameScreenSize,						// �Q�[���E�B���h�E�̑傫��
			bool fullScreenFlag,								// �t���X�N���[���ɂ��邩
			const std::string& line2DPixelShaderFileName,		// �f�t�H���g��2���������\���p�̃s�N�Z���V�F�[�_�[�̃t�@�C���p�X
			const std::string& line2DVertexShaderFileName,		// �f�t�H���g��2���������\���p�̒��_�V�F�[�_�[�̃t�@�C���p�X
			const std::string& spritePixelShaderFileName,		// �f�t�H���g�̃X�v���C�g�\���p�̃s�N�Z���V�F�[�_�[�̃t�@�C���p�X
			const std::string& spriteVertexShaderFileName,		// �f�t�H���g�̃X�v���C�g�\���p�̒��_�V�F�[�_�[�̃t�@�C���p�X
			const std::string& basicMeshPixelShaderFileName,	// �f�t�H���g�̃��b�V���\���p�̃s�N�Z���V�F�[�_�[�̃t�@�C���p�X
			const std::string& basicMeshVertexShaderFileName,	// �f�t�H���g�̃��b�V���\���p�̒��_�V�F�[�_�[�̃t�@�C���p�X
			const std::string& pbrMeshPixelShaderFileName,		// �f�t�H���g��Pbr���b�V���\���p�̃s�N�Z���V�F�[�_�[�̃t�@�C���p�X
			const std::string& pbrMeshVertexShaderFileName,		// �f�t�H���g��Pbr���b�V���\���p�̒��_�V�F�[�_�[�̃t�@�C���p�X
			const std::string& iblMeshPixelShaderFileName,		// �f�t�H���g��Ibl���b�V���\���p�̃s�N�Z���V�F�[�_�[�̃t�@�C���p�X
			const std::string& iblMeshVertexShaderFileName,		// �f�t�H���g��Ibl���b�V���\���p�̒��_�V�F�[�_�[�̃t�@�C���p�X
			const std::string& pbrIblMeshPixelShaderFileName,	// �f�t�H���g��PbrIbl���b�V���\���p�̃s�N�Z���V�F�[�_�[�̃t�@�C���p�X
			const std::string& pbrIblMeshVertexShaderFileName	// �f�t�H���g��PbrIbl���b�V���\���p�̒��_�V�F�[�_�[�̃t�@�C���p�X
		);

	public:

		bool isDestroy() const;

	private:

		void setUpdatePriority();
	};
}
#endif // !DIRECTX_11_POLICY_H_