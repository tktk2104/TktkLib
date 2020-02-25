#ifndef POLYGON_2D_DRAWER_MAKER_H_
#define POLYGON_2D_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "Polygon2DDrawer.h"

namespace tktk
{
	struct Polygon2DDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static Polygon2DDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<Polygon2DDrawer> create();

	public:

		// �|���S�����`�����钸�_�̔z���ݒ�i���v���j
		Polygon2DDrawerMaker& vertexs(const std::vector<Vector2>& value);

		// �|���S�����`�����钸�_�̔z����Đݒ�i���v���j
		template<class... Args>
		void vertexs(Args... value);

		// �|���S���̐��̑�����ݒ肷��
		Polygon2DDrawerMaker& lineThickness(float value);

		// �h��Ԃ��t���O��ݒ肷��
		Polygon2DDrawerMaker& isFill(bool value);

		// �|���S���̕`��F��ݒ肷��
		Polygon2DDrawerMaker& polygonColor(const Color& value);

		// �`��D��x��ݒ肷��
		Polygon2DDrawerMaker& drawPriority(float value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		Polygon2DDrawerMaker& blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		Polygon2DDrawerMaker& blendParam(float value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		Polygon2DDrawerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static Polygon2DDrawerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		std::vector<Vector2> m_vertexs{ };
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_polygonColor{ Color::white };
		float m_drawPriority{ 0.0f };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};

	template<class ...Args>
	inline void Polygon2DDrawerMaker::vertexs(Args ...value)
	{
		vertexs(std::vector<Vector2>({ value... }));
	}
}
#endif // !POLYGON_2D_DRAWER_MAKER_H_