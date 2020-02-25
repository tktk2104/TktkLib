#ifndef SHADER_CONSTANT_BUFFER_UPDATER_MAKER_H_
#define SHADER_CONSTANT_BUFFER_UPDATER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ShaderConstantBufferUpdater.h"

namespace tktk
{
	class ShaderConstantBufferUpdaterMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static ShaderConstantBufferUpdaterMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<ShaderConstantBufferUpdater> create();

		// ���g�̃V�F�[�_�[�p�萔�o�b�t�@ID��ݒ�
		ShaderConstantBufferUpdaterMaker& shaderConstantBufferId(int value);

	private:

		// ���g�̃|�C���^
		static ShaderConstantBufferUpdaterMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		int m_shaderConstantBufferId{ -1 };
	};
}
#endif // !SHADER_CONSTANT_BUFFER_UPDATER_MAKER_H_