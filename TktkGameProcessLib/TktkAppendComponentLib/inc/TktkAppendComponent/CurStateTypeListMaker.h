#ifndef CUR_STATE_TYPE_LIST_MAKER_H_
#define CUR_STATE_TYPE_LIST_MAKER_H_

#include "CurStateTypeList.h"

namespace tktk
{
	class CurStateTypeListMaker
	{
	public:

		// インスタンス作成開始
		static CurStateTypeListMaker& makeStart();

	public:

		// 作成する
		CurStateTypeList* create();

	private:

		// 自身のポインタ
		static CurStateTypeListMaker m_self;
	};
}
#endif // !CUR_STATE_TYPE_LIST_MAKER_H_