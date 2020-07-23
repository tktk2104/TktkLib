#ifndef SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_
#define SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă��郌���_�[�^�[�Q�b�g�̐�
	constexpr unsigned int SystemRtBufferNum = 2U;

	// �V�X�e���Ŏg�p���Ă��郌���_�[�^�[�Q�b�g�̎��
	enum class SystemRtBufferType
	{
		BackBuffer_1	= 0U,
		BackBuffer_2	= 1U,
	};
}
#endif // !SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_