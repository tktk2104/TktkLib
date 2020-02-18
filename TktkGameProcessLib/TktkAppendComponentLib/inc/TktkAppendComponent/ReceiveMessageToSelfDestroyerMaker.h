#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_

#include "ReceiveMessageToSelfDestroyer.h"

namespace tktk
{
	class ReceiveMessageToSelfDestroyerMaker
	{
	public:

		// インスタンス作成開始
		static ReceiveMessageToSelfDestroyerMaker& makeStart();

	public:

		// 作成する
		ReceiveMessageToSelfDestroyer* create();

		// 自身を殺すメッセージの種類を設定
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(int value);

	private:

		// 自身のポインタ
		static ReceiveMessageToSelfDestroyerMaker m_self;

	private:

		int m_destroyMessegeType;
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_