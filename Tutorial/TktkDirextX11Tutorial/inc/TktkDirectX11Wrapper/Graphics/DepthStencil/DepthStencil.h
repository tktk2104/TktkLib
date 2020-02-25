#ifndef DEPTH_STENCIL_H_
#define DEPTH_STENCIL_H_

#include "Asset/DepthStencilData.h"
#include "Asset/SystemDepthStencilId.h"

namespace tktk
{
	// �uDepthStencilManager�v�̎����̈ꕔ���B�����߂̃N���X
	class DepthStencil
	{
	public:

		// �V���Ȑ[�x�r���[���쐬����
		// �����̊֐��Ńr���[�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(int id, const Vector2& useTextureSize);

		// �w�肵���[�x�r���[���폜����
		// �����̊֐��Ńr���[���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵���[�x�r���[���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const DepthStencilData& getData(int id);
	};
}
#endif // !DEPTH_STENCIL_H_
