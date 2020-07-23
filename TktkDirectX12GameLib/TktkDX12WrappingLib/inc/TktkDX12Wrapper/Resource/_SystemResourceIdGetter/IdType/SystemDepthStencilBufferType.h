#ifndef SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_
#define SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���[�x�X�e���V���o�b�t�@�̐�
	constexpr unsigned int SystemDsBufferNum = 2U;

	// �V�X�e���Ŏg�p���Ă���[�x�X�e���V���o�b�t�@�̎��
	enum class SystemDsBufferType
	{
		Basic		= 0U,
		ShadowMap	= 1U
	};
}
#endif // !SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_