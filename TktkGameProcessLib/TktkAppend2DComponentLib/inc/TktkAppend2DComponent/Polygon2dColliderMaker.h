#ifndef POLYGON_2D_COLLIDER_MAKER_H_
#define POLYGON_2D_COLLIDER_MAKER_H_

#include <vector>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "Polygon2dCollider.h"

namespace tktk
{
	// RectCollider�̃C���X�^���X���쐬����N���X
	class Polygon2dColliderMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static Polygon2dColliderMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<Polygon2dCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		Polygon2dColliderMaker& collisionGroupType(int value);

		// �����蔻��̑傫����ݒ�
		Polygon2dColliderMaker& vertexs(const std::vector<Vector2>& value);

		// �����蔻��̃��[�J�����W��ݒ�
		Polygon2dColliderMaker& localPosition(const Vector2& value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static Polygon2dColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		int m_collisionGroupType{ 0 };
		std::vector<Vector2> m_vertexs{};
		Vector2 m_localPosition{ Vector2::zero };
	};
}
#endif // !POLYGON_2D_COLLIDER_MAKER_H_