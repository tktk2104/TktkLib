#ifndef MESH_MATERIAL_H_
#define MESH_MATERIAL_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibShader3DParam.h"
#include "../../../TktkDxlib3DWrapper/Graphics/ShaderType.h"
#include "../../../TktkDxlib3DWrapper/Graphics/ShaderUseTextureAddressType.h"

namespace tktk
{
	class MeshMaterial
		: public tktk::ComponentBase
	{
	public:

		MeshMaterial(
			const DxLibShader3DParam& dxLibShader3DParam
		);

	public:

		// DxLib�ŃV�F�[�_�[���g�p���鎞�̃p�����[�^�[���擾
		const DxLibShader3DParam& getDxLibShader3DParam() const;

		// ����̃V�F�[�_�[���g�p����
		void useOrigShader(int pixelShaderId, int vertexShaderId);
		// �f�t�H���g�̃V�F�[�_�[���g�p����
		void unUseOrigShader();
		// �V�F�[�_�[�Ŏg�p����萔�o�b�t�@���N���A����
		void clearShaderUseConstantBuffer();
		// �V�F�[�_�[�Ŏg�p����萔�o�b�t�@��ݒ肷��
		void setShaderUseConstantBuffer(int slot, ShaderType targetShaderType, int shaderConstantBufferId);
		// �V�F�[�_�[�Ŏg�p����摜�f�[�^���N���A����
		void clearShaderUseGraphHandleMap();
		// �V�F�[�_�[�Ŏg�p����e�N�X�`����ݒ肷��
		void addShaderUsedTexture(int stageIndex, int textureId, ShaderUseTextureAddressType addressType);
		// �V�F�[�_�[�Ŏg�p���郂�f���e�N�X�`����ݒ肷��
		void addShaderUsedModelTexture(int stageIndex, int modelTextureId, ShaderUseTextureAddressType addressType);
		// �V�F�[�_�[�Ŏg�p���郌���_�[�^�[�Q�b�g�̕`�挋�ʂ�ݒ肷��
		void addShaderUsedRenderTarget(int stageIndex, int renderTargetId, ShaderUseTextureAddressType addressType);

	private:

		// DxLib�ŃV�F�[�_�[���g�p���鎞�̃p�����[�^�[
		DxLibShader3DParam m_dxLibShader3DParam{};
	};
}
#endif // !MESH_MATERIAL_H_
