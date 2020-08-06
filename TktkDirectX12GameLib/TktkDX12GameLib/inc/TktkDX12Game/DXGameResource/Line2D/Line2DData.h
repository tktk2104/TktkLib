#ifndef LINE_2D_DATA_H_
#define LINE_2D_DATA_H_

#include "Line2DDrawFuncArgs.h"

namespace tktk
{
	// ���C���QD�̏����Ǘ�����N���X
	// ������Ǘ�������͖���
	class Line2DData
	{
	public:

		Line2DData() = default;
		~Line2DData() = default;

	public:

		void drawLine(const Line2DDrawFuncArgs& drawFuncArgs) const;

	private:

		// ���C���`��p�̒��_�o�b�t�@�����
		// ���O�ɍ��ꂽ���_�o�b�t�@�͍폜�����
		void createVertexBuffer(const std::vector<tktkMath::Vector2>& lineVertexArray) const;

		void updateLine2DCbuffer(const Line2DDrawFuncArgs& drawFuncArgs) const;
	};
}

#endif // !LINE_2D_DATA_H_