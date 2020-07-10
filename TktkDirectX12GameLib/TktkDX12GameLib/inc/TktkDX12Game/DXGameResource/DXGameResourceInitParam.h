#ifndef DX_GAME_RESOURCE_INIT_PARAM_H_
#define DX_GAME_RESOURCE_INIT_PARAM_H_

#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "PostEffect/PostEffectShaderFilePaths.h"

namespace tktk
{
	// �Q�[���Ŏg�p���郊�\�[�X�Ǘ��N���X����鎞�ɕK�v�ȏ��
	struct DXGameResourceInitParam
	{
		// �X�v���C�g�V�F�[�_�[�̃t�@�C���p�X
		tktk::ShaderFilePaths		spriteShaderFilePaths		{};

		// �ʏ탁�b�V���V�F�[�_�[�̃t�@�C���p�X
		tktk::ShaderFilePaths		basicMeshShaderFilePaths	{};

		// �V���h�E�}�b�v�V�F�[�_�[�̃t�@�C���p�X
		std::string					writeShadowMapVsFilePath	{};

		// �|�X�g�G�t�F�N�g�V�F�[�_�[�̃t�@�C���p�X
		PostEffectShaderFilePaths	postEffectShaderFilePaths	{};

		// �X�v���C�g�}�e���A����
		unsigned int spriteNum				{};

		// �ʏ탁�b�V����
		unsigned int basicMeshNum			{};

		// �ʏ탁�b�V���}�e���A����
		unsigned int basicMeshMaterialNum	{};

		// ���[�V�����f�[�^��
		unsigned int motionNum				{};

		// �X�P���g���f�[�^��
		unsigned int skeletonNum			{};

		// �|�X�g�G�t�F�N�g�}�e���A����
		unsigned int postEffectMaterialNum	{};
	};
}
#endif // !DX_GAME_RESOURCE_INIT_PARAM_H_