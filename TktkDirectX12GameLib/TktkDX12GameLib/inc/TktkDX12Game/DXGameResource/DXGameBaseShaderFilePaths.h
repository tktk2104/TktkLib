#ifndef DX_GAME_BASE_SHADER_FILE_PATHS_H_
#define DX_GAME_BASE_SHADER_FILE_PATHS_H_

#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "PostEffect/PostEffectShaderFilePaths.h"

namespace tktk
{
	// �Q�[���Ŏg�p����\�ʓI�ȃ��\�[�X�Ŏg�p����V�F�[�_�[�̃t�@�C���p�X
	struct DXGameBaseShaderFilePaths
	{
		// �X�v���C�g�V�F�[�_�[�̃t�@�C���p�X
		tktk::ShaderFilePaths		spriteShaderFilePaths{};

		// �ʏ탁�b�V���V�F�[�_�[�̃t�@�C���p�X
		tktk::ShaderFilePaths		basicMeshShaderFilePaths{};

		// �V���h�E�}�b�v�V�F�[�_�[�̃t�@�C���p�X
		std::string					writeShadowMapVsFilePath{};

		// �|�X�g�G�t�F�N�g�V�F�[�_�[�̃t�@�C���p�X
		PostEffectShaderFilePaths	postEffectShaderFilePaths{};
	};
}
#endif // !DX_GAME_BASE_SHADER_FILE_PATHS_H_