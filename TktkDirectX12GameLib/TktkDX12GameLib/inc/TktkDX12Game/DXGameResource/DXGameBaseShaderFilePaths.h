#ifndef DX_GAME_BASE_SHADER_FILE_PATHS_H_
#define DX_GAME_BASE_SHADER_FILE_PATHS_H_

#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "PostEffect/PostEffectShaderFilePaths.h"

namespace tktk
{
	// �Q�[���Ŏg�p����\�ʓI�ȃ��\�[�X�Ŏg�p����V�F�[�_�[�̃t�@�C���p�X
	struct DXGameBaseShaderFilePaths
	{
		// �X�v���C�g�V�F�[�_�[�̃t�@�C���p�X
		tktk::ShaderFilePaths		spriteShaderFilePaths{};

		// 2D���C���V�F�[�_�[�̃t�@�C���p�X
		tktk::ShaderFilePaths		line2DShaderFilePaths{};

		// �ʏ탁�b�V���V�F�[�_�[�̃t�@�C���p�X
		tktk::ShaderFilePaths		basicMeshShaderFilePaths{};

		// �P�F�h��Ԃ����b�V���V�F�[�_�[�̃t�@�C���p�X
		std::string					monoColorShaderPsFilePath;

		// �V���h�E�}�b�v�V�F�[�_�[�̃t�@�C���p�X
		std::string					writeShadowMapVsFilePath{};

		// �|�X�g�G�t�F�N�g�V�F�[�_�[�̃t�@�C���p�X
		PostEffectShaderFilePaths	postEffectShaderFilePaths{};
	};
}
#endif // !DX_GAME_BASE_SHADER_FILE_PATHS_H_