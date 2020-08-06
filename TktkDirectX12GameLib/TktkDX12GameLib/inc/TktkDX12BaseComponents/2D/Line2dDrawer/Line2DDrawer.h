#ifndef LINE_2D_DRAWER_H_
#define LINE_2D_DRAWER_H_

#include <vector>
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// 2���������`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform2D�z
	class Line2DDrawer
		: public ComponentBase
	{
	public:

		Line2DDrawer(
			float drawPriority,
			const std::vector<tktkMath::Vector2>& lineVertexArray,
			const tktkMath::Color& lineColor,
			const tktkMath::Color& blendRate,
			unsigned int useRtvDescriptorHeapId
		);

	public:

		void start();
		void draw() const;

	public:

		// �������\�����钸�_���W�̔z����擾����
		const std::vector<tktkMath::Vector2>& getLineVertexArray() const;

		// �������\�����钸�_���W�̔z���ݒ肷��
		void setLineVertexArray(const std::vector<tktkMath::Vector2>& vertexArray);

		// ���̐F���擾����
		const tktkMath::Color& getLineColor() const;

		// ���̐F��ݒ肷��
		void setLineColor(const tktkMath::Color& color);

		// �u�����h���[�g���Đݒ肷��
		void setBlendRate(const tktkMath::Color& blendRate);

	private:

		unsigned int					m_useRtvDescriptorHeapId;
		std::vector<tktkMath::Vector2>	m_lineVertexArray;
		tktkMath::Color					m_lineColor{ tktkMath::colorWhite };
		tktkMath::Color					m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		
		ComponentPtr<Transform2D> m_transform{  };
	};
}
#endif // !LINE_2D_DRAWER_H_