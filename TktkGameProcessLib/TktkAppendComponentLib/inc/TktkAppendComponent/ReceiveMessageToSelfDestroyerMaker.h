#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "ReceiveMessageToSelfDestroyer.h"

namespace tktk
{
	class ReceiveMessageToSelfDestroyerMaker
	{
	public:

		// インスタンス作成開始
		static ReceiveMessageToSelfDestroyerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<ReceiveMessageToSelfDestroyer> create();

		// 自身を殺すメッセージの種類を設定
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(int value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static ReceiveMessageToSelfDestroyerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		int m_destroyMessegeType{ 0 };
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_