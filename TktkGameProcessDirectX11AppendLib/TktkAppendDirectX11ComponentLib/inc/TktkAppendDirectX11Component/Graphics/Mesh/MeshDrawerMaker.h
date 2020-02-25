#ifndef MESH_DRAWER_MAKER_H_
#define MESH_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "MeshDrawer.h"

namespace tktk
{
	class MeshDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static MeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<MeshDrawer> create();

		MeshDrawerMaker& drawPriority(float value);

		MeshDrawerMaker& cameraId(int value);

		MeshDrawerMaker& meshId(int value);

		MeshDrawerMaker& skeltonId(int value);

		MeshDrawerMaker& materialIdArray(const std::vector<int>& value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static MeshDrawerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		int m_cameraId{ 0 };
		int m_meshId{ 0 };
		int m_skeltonId{ 0 };
		std::vector<int> m_materialIdArray{ };
	};
}

#endif // !MESH_DRAWER_MAKER_H_