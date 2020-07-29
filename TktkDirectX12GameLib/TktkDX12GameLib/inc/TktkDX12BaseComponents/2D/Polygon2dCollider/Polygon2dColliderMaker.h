#ifndef POLYGON_2D_COLLIDER_MAKER_H_
#define POLYGON_2D_COLLIDER_MAKER_H_

#include "Polygon2dCollider.h"

namespace tktk
{
	// RectCollider�̃C���X�^���X���쐬����N���X
	class Polygon2dColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		Polygon2dColliderMaker() = default;
		Polygon2dColliderMaker(const Polygon2dColliderMaker& other) = default;
		Polygon2dColliderMaker& operator = (const Polygon2dColliderMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static Polygon2dColliderMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<Polygon2dCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		Polygon2dColliderMaker& collisionGroupType(int value);

		// �����蔻��̑傫����ݒ�
		Polygon2dColliderMaker& vertexs(const std::vector<tktkMath::Vector2>& value);

		// �����蔻��̃��[�J�����W��ݒ�
		Polygon2dColliderMaker& localPosition(const tktkMath::Vector2& value);

	private:

		// ���g�̃|�C���^
		static Polygon2dColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr					m_user					{ };
		int								m_collisionGroupType	{ 0 };
		std::vector<tktkMath::Vector2>	m_vertexs				{};
		tktkMath::Vector2				m_localPosition			{ tktkMath::vec2Zero };
	};
}
#endif // !POLYGON_2D_COLLIDER_MAKER_H_