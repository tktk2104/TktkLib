#ifndef MESH_DRAWER_H_
#define MESH_DRAWER_H_

#include <vector>
#include <unordered_map>
#include <TktkMath/Vector3.h>
#include <TktkMath/Quaternion.h>
#include <TktkMath/Matrix4.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"
#include "MeshMaterial.h"

namespace tktk
{
	// ���b�V���̕`��R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform3D�z
	class MeshDrawer
		: public ComponentBase
	{
	public:

		MeshDrawer(
			const DxLibDraw3DParam& dxLibDraw3DParam,	// DxLib���g����3D�`��Ŏg�p����p�����[�^
			int meshID									// �\�����郁�b�V����Id
		);

	public:

		// <PolymorphismFunc>
		void awake();
		void start();
		void draw() const;

	public:

		// �\�����Ă��郁�b�V��Id���擾
		int getMeshID() const;
		// �\�����Ă��郁�b�V��Id���Đݒ�
		void setMeshID(int meshID);

		// �{�[���̑������擾
		unsigned int getBoneCount() const;

		// �����Ŏw�肵���{�[���̕ϊ��s����擾
		const Matrix4& getLocalBoneMatrix(int boneIndex);
		// �����Ŏw�肵���{�[���̕ϊ��s����Đݒ�
		void setLocalBoneMatrix(int boneIndex, const Matrix4& localBoneMatrix);

		// �S�Ẵ{�[���̕ϊ��s����擾
		const std::vector<Matrix4>& getLocalBoneMatrices() const;
		// �S�Ẵ{�[���̕ϊ��s����Đݒ�
		void setLocalBoneMatrices(const std::vector<Matrix4>& localBoneMatrices);
		// �S�Ẵ{�[���̕ϊ��s����Đݒ�
		template <class... Args>
		void setLocalBoneMatrices(Args... localBoneMatrices);

		// ���b�V���Ŏg�p����e�N�X�`�����Đݒ肷��
		// �i���b�V���Ŏg�p����e�N�X�`���́uModelTextureLoader�v�œǂݍ��݂��s���K�v������܂��j
		void setTextureGraphHandle(int materialIndex, int textureId, bool haveAlpha);

		// DxLib���g����3D�`��Ŏg�p����p�����[�^���擾
		const DxLibDraw3DParam& getDxLibDraw3DParam() const;

		// �\�����郁�b�V���̃��[�J���s����Đݒ�
		void setMeshLocalMat(const Matrix4& localMat);
		// �`��̃u�����h���@�̎�ނ��Đݒ�
		void setBlendMode(BlendMode blendMode);
		// �`��̃u�����h�Ɏg�p����l���Đݒ�
		void setBlendParam(float blendParam);
		// ���C�g���g�p���ĕ`����s�������Đݒ�
		void setUseLight(bool useLight);
		// Z�o�b�t�@���g�p���ĕ`����s�������Đݒ�
		void setWriteZBuffer(bool writeZBuffer);
		// �w�肵�������_�[�^�[�Q�b�g�ɕ`�悷��
		void useRenderTarget(int renderTargetId);
		// �����_�[�^�[�Q�b�g���g�p�����ɕ`�悷��
		void unUseRenderTarget();

	private:

		// ���g�̂R�������W�R���|�[�l���g
		CfpPtr<Transform3D> m_transform3D;

		// ���g�̃}�e���A�����̃R���|�[�l���g
		CfpPtr<MeshMaterial> m_meshMaterial;

		// DxLib���g����3D�`��Ŏg�p����p�����[�^
		DxLibDraw3DParam m_dxLibDraw3DParam;

		// �`�悷�郂�f����ID
		int m_meshID{ -1 };

		// ���f���̃{�[�����̍s����
		std::vector<Matrix4> m_localBoneMatrices;
	};

	template<class ...Args>
	inline void MeshDrawer::setLocalBoneMatrices(Args ...localBoneMatrices)
	{
		setLocalBoneMatrices(std::vector<Matrix4>({ localBoneMatrices... }));
	}
}
#endif // !MESH_DRAWER_H_