#ifndef CUR_STATE_TYPE_LIST_MAKER_H_
#define CUR_STATE_TYPE_LIST_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "CurStateTypeList.h"

namespace tktk
{
	class CurStateTypeListMaker
	{
	public:

		// インスタンス作成開始
		static CurStateTypeListMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<CurStateTypeList> create();

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static CurStateTypeListMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
	};
}
#endif // !CUR_STATE_TYPE_LIST_MAKER_H_