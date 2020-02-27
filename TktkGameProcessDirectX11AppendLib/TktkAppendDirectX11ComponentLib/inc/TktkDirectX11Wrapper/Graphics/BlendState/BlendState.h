#ifndef BLEND_STATE_H_
#define BLEND_STATE_H_

#include "Asset/BlendStateData.h"

namespace tktk
{
	// �uBlendStateManager�v�̎����̈ꕔ���B�����߂̃N���X
	class BlendState
	{
	public:

		// �V���ȃu�����h�X�e�[�g���쐬����
		// �����̊֐��Ńu�����h�X�e�[�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(int id, const D3D11_BLEND_DESC& blendDesc);

		// �w�肵���u�����h�X�e�[�g���폜����
		// �����̊֐��Ńu�����h�X�e�[�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵���u�����h�X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����
		static BlendStateData* getDataPtr(int id);
	};
}
#endif // !BLEND_STATE_H_