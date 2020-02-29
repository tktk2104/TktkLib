#ifndef DEPTH_STENCIL_STATE_H_
#define DEPTH_STENCIL_STATE_H_

#include "Asset/DepthStencilStateData.h"

namespace tktk
{
	class DepthStencilState
	{
	public:

		// �V���Ȑ[�x�X�e���V���X�e�[�g���쐬����
		// �����̊֐��Ő[�x�X�e���V���X�e�[�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(int id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);

		// �w�肵���[�x�X�e���V���X�e�[�g���폜����
		// �����̊֐��Ő[�x�X�e���V���X�e�[�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵���[�x�X�e���V���X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����
		static DepthStencilStateData* getData(int id);
	};
}
#endif // !DEPTH_STENCIL_STATE_H_