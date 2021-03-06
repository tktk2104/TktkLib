#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_

#include <TktkComponentFramework/Component/ComponentBase.h>

namespace tktk
{
	// 特定のメッセージを取得したら自身のGameObjectを削除する
	class ReceiveMessageToSelfDestroyer
		: public ComponentBase
	{
	public:

		ReceiveMessageToSelfDestroyer(int destroyMessegeType);

	public:

		// <PolymorphismFunc>
		void handleMessage(int eventMessageType, const tktk::SafetyVoidPtr& param);

	private:

		// 自身を削除するメッセージの種類
		int m_destroyMessegeType;
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_