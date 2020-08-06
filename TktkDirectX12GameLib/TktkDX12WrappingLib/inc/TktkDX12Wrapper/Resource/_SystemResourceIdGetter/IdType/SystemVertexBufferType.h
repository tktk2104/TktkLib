#ifndef SYSTEM_VERTEX_BUFFER_TYPE_H_
#define SYSTEM_VERTEX_BUFFER_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă��钸�_�o�b�t�@�̐�
	constexpr unsigned int SystemVertexBufferNum = 2U;

	// �V�X�e���Ŏg�p���Ă��钸�_�o�b�t�@�̎��
	enum class SystemVertexBufferType
	{
		Sprite = 0U,
		Line2D
	};
}
#endif // !SYSTEM_VERTEX_BUFFER_TYPE_H_