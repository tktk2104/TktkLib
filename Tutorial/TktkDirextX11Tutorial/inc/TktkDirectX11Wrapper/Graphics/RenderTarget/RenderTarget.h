#ifndef RENDER_TARGET_H_
#define RENDER_TARGET_H_

#include "Asset/RenderTargetData.h"
#include "Asset/SystemRenderTargetId.h"

namespace tktk
{
	// �uRenderTargetManager�v�̎����̈ꕔ���B�����߂̃N���X
	class RenderTarget
	{
	public:

		// �V���ȃ����_�[�^�[�Q�b�g�𐶐�����
		// �����̊֐��Ń����_�[�^�[�Q�b�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(int id, ID3D11Texture2D* renderTargetTexture);

		// �w�肵�������_�[�^�[�Q�b�g���폜����
		// �����̊֐��Ń����_�[�^�[�Q�b�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵�������_�[�^�[�Q�b�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const RenderTargetData& getData(int id);
	};
}
#endif // !RENDER_TARGET_H_