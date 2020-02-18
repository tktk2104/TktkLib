#ifndef DRAW_PRIORITY_H_
#define DRAW_PRIORITY_H_

// ������������������ɕ`�悳���
namespace DrawPriority
{
	// �V���h�E�}�b�v�̐������J�n
	const float DRAW_PRIORITY_CREATE_SHADOW_BEGIN	= -500.0f;

	// �V���h�E�}�b�v�̐������s���`��D��x
	const float DRAW_PRIORITY_CREATE_SHADOW			= -400.0f;

	// �V���h�E�}�b�v�̐������I��
	const float DRAW_PRIORITY_CREATE_SHADOW_END		= -300.0f;

	// �V���h�E�}�b�v�̓K�����J�n
	const float DRAW_PRIORITY_SHADOW_ENABLE			= -200.0f;

	// ��̕`��
	const float DRAW_PRIORITY_SKY					= -100.0f;

	// ��{�̕`��D��x
	const float DRAW_PRIORITY_DEFAULT				= 0.0f;

	// �V���h�E�}�b�v�̓K�����I��
	const float DRAW_PRIORITY_SHADOW_DISABLE		= 100.0f;

	// �e�𗎂Ƃ��Ȃ��I�u�W�F�N�g�p�̕`��D��x
	const float DRAW_PRIORITY_NOT_DRAW_SHADOW		= 200.0f;
}
#endif // !DRAW_PRIORITY_H_