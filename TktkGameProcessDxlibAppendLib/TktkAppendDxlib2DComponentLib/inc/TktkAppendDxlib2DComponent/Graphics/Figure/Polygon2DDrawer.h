#ifndef POLYGON_2D_DRAWER_H_
#define POLYGON_2D_DRAWER_H_

#include <memory>
#include <vector>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// �Q�����|���S����`�悷��R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class Polygon2DDrawer
		: public ComponentBase
	{
	public:

		Polygon2DDrawer(
			const std::vector<Vector2>& vertexs,
			float lineThickness,
			bool isFill,
			const Color& polygonColor,
			float drawPriority,
			BlendMode blendMode,
			float blendParam
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	private:

		void drawPolygon2D() const;

		void drawPolygon2DFlame() const;

	public:

		// �|���S�����`�����钸�_�̔z����擾�i���v���j
		const std::vector<Vector2>& getVertexs() const;
		// �|���S�����`�����钸�_�̔z����Đݒ�i���v���j
		void setVertexs(const std::vector<Vector2>& vertexs);

		// �|���S�����`�����钸�_�̔z����Đݒ�i���v���j
		template<class... Args>
		void setVertexs(Args... vertexs);

		// �^�~�̐��̑������擾
		float getLineThickness() const;
		// �^�~�̐��̑������Đݒ�
		void setLineThickness(float lineThickness);

		// �h��Ԃ��t���O���擾
		bool getIsFill() const;
		// �h��Ԃ��t���O���Đݒ�
		void setIsFill(bool isFill);

		// �|���S���̕`��F���擾
		const Color& getPolygonColor() const;
		// �|���S���̕`��F���Đݒ�
		void setPolygonColor(const Color& polygonColor);

		// �`��̃u�����h���@�̎�ނ��擾
		BlendMode getBlendMode() const;
		// �`��̃u�����h���@�̎�ނ��Đݒ�
		void setBlendMode(BlendMode blendMode);

		// �`��̃u�����h�Ɏg�p����l���擾
		float getBlendParam() const;
		// �`��̃u�����h�Ɏg�p����l���Đݒ�
		void setBlendParam(float blendParam);

		// �w�肵�������_�[�^�[�Q�b�g�ɕ`�悷��
		void useRenderTarget(int renderTargetId);
		// �����_�[�^�[�Q�b�g���g�p�����ɕ`�悷��
		void unUseRenderTarget();

	private:

		// ���g�̂Q�������W�R���|�[�l���g
		std::weak_ptr<Transform2D> m_transform2D;

		// �|���S�����`�����钸�_�̔z��i���v���j
		std::vector<Vector2> m_vertexs;

		// �|���S���̐��̑���
		float m_lineThickness;

		// �h��Ԃ��t���O
		bool m_isFill;

		// �|���S���̕`��F
		Color m_polygonColor;

		// �`��̃u�����h���@�̎��
		BlendMode m_blendMode;

		// �`��̃u�����h�Ɏg�p����l
		float m_blendParam;

		// �����_�[�^�[�Q�b�g�ɕ`�悷�邩
		bool m_useRenderTarget{ false };

		// �`�悷�郌���_�[�^�[�Q�b�g��Id
		int m_renderTargetId{ -1 };
	};

	template<class ...Args>
	inline void Polygon2DDrawer::setVertexs(Args ...vertexs)
	{
		setVertexs(std::vector<Vector2>({ vertexs... }));
	}
}
#endif // !POLYGON_2D_DRAWER_H_