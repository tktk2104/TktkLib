#ifndef CUR_STATE_TYPE_LIST_MAKER_H_
#define CUR_STATE_TYPE_LIST_MAKER_H_

#include "CurStateTypeList.h"

namespace tktk
{
	class CurStateTypeListMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static CurStateTypeListMaker& makeStart();

	public:

		// �쐬����
		CurStateTypeList* create();

	private:

		// ���g�̃|�C���^
		static CurStateTypeListMaker m_self;
	};
}
#endif // !CUR_STATE_TYPE_LIST_MAKER_H_