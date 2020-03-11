#ifndef LINE_2D_DRAWER_H_
#define LINE_2D_DRAWER_H_

#include <vector>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>

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
			const std::vector<Vector2>& lineVertexArray,
			const Color& lineColor,
			int blendStateId,
			int depthStencilStateId,
			const Color& blendRate
		);

	public:

		void start();
		void draw() const;

	public:

		// �������\�����钸�_���W�̔z����擾����
		const std::vector<Vector2>& getLineVertexArray() const;

		// �������\�����钸�_���W�̔z���ݒ肷��
		void setLineVertexArray(const std::vector<Vector2>& vertexArray);

		// ���̐F���擾����
		const Color& getLineColor() const;

		// ���̐F��ݒ肷��
		void setLineColor(const Color& color);

		// �u�����h�X�e�[�gID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id)
		{
			setBlendStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setBlendStateId(IdType id) { static_assert(false, "BlendStateId Fraud Type"); }

		// �[�x�X�e���V���X�e�[�gID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id)
		{
			setDepthStencilStateIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setDepthStencilStateId(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// �u�����h���[�g���Đݒ肷��
		void setBlendRate(const Color& blendRate);

	private:

		// �e��id�w��n�̊֐��̎���
		void setBlendStateIdImpl(int id);
		void setDepthStencilStateIdImpl(int id);

	private:

		std::vector<Vector2> m_lineVertexArray;
		Color m_lineColor{ Color::white };
		int m_blendStateId{ -1 };
		int m_depthStencilStateId{ -1 };
		Color m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };
		
		CfpPtr<Transform2D> m_transform{  };
	};
}
#endif // !LINE_2D_DRAWER_H_