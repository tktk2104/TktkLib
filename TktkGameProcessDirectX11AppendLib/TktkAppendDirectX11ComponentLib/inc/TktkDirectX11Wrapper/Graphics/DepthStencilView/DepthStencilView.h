#ifndef DEPTH_STENCIL_VIEW_H_
#define DEPTH_STENCIL_VIEW_H_

#include "Asset/DepthStencilViewData.h"
#include "Asset/SystemDepthStencilViewId.h"

namespace tktk
{
	// �uDepthStencilViewManager�v�̎����̈ꕔ���B�����߂̃N���X
	class DepthStencilView
	{
	public:

		// �V���Ȑ[�x�r���[���쐬����
		// �����̊֐��Ńr���[�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void create(int id, const Vector2& useTextureSize);

		// �w�肵���[�x�r���[���폜����
		// �����̊֐��Ńr���[���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵���[�x�r���[���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const DepthStencilViewData& getData(int id);
	};
}
#endif // !DEPTH_STENCIL_VIEW_H_
