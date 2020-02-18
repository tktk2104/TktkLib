#ifndef RENDER_TARGET_HANDLE_H_
#define RENDER_TARGET_HANDLE_H_

#include <array>
#include "../../DxlibStructWrapper/Vertex2dShaderData.h"

namespace tktk
{
	class RenderTargetHandle
	{
	public:

		// SetDrawScreen �ŕ`��Ώۂɂł���O���t�B�b�N�n���h��
		int screenGraphHandle{ -1 };

		// ���_�f�[�^�̔z��
		std::array<Vertex2dShaderData, 4U> vertices;

		// ���t���[�������Ŏ��g�ɕ`�悳�ꂽ�����������H
		bool autoRefresh{ true };
	};
}

#endif // !RENDER_TARGET_HANDLE_H_
