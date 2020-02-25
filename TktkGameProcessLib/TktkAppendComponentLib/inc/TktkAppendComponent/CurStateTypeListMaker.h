#ifndef CUR_STATE_TYPE_LIST_MAKER_H_
#define CUR_STATE_TYPE_LIST_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "CurStateTypeList.h"

namespace tktk
{
	class CurStateTypeListMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static CurStateTypeListMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<CurStateTypeList> create();

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static CurStateTypeListMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
	};
}
#endif // !CUR_STATE_TYPE_LIST_MAKER_H_