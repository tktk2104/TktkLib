#ifndef LINE_2D_H_
#define LINE_2D_H_

#include <memory>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "Line2DData.h"

namespace tktk
{
	// �uLine2DData�v���Ǘ�����N���X
	// ����͒P��́uLine2DData�v�݂̂̊Ǘ�
	class Line2D
	{
	public:

		Line2D(const ShaderFilePaths& shaderFilePaths);
		~Line2D() = default;

	public:

		// ����`�悷��
		void drawLine(const Line2DDrawFuncArgs& drawFuncArgs) const;

	private:

		// �Q�c���C���`��p�̃f�B�X�N���v�^�q�[�v�����
		void craeteDescriptorHeap() const;

		// �Q�c���C���`��p�̃��[�g�V�O�l�`�������
		void createRootSignature() const;

		// �Q�c���C���`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		std::unique_ptr<Line2DData> m_line2DData;
	};
}
#endif // !LINE_2D_H_