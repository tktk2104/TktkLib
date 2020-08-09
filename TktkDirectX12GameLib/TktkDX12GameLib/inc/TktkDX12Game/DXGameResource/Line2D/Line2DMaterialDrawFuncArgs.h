#ifndef LINE_2D_DRAW_FUNC_ARGS_H_
#define LINE_2D_DRAW_FUNC_ARGS_H_

#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	struct Line2DMaterialDrawFuncArgs
	{
		// �g�p����r���[�|�[�gID
		unsigned int		viewportId;

		// �g�p����V�U�[��`ID
		unsigned int		scissorRectId;

		// �g�p���郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�vID
		unsigned int		rtvDescriptorHeapId;

		// ���[���h�s��
		tktkMath::Matrix3	worldMatrix;

		// ���C���̐F
		tktkMath::Color		lineColor;

		// ���C�����\�����钸�_�̔z��
		std::vector<tktkMath::Vector2> lineVertexArray;
	};
}
#endif // !LINE_2D_DRAW_FUNC_ARGS_H_
