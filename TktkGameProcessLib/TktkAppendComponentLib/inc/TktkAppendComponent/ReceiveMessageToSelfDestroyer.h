#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_

#include <TktkComponentFramework/Component/ComponentBase.h>

namespace tktk
{
	// ����̃��b�Z�[�W���擾�����玩�g��GameObject���폜����
	class ReceiveMessageToSelfDestroyer
		: public ComponentBase
	{
	public:

		ReceiveMessageToSelfDestroyer(int destroyMessegeType);

	public:

		// <PolymorphismFunc>
		void handleMessage(int eventMessageType, const tktk::SafetyVoidPtr& param);

	private:

		// ���g���폜���郁�b�Z�[�W�̎��
		int m_destroyMessegeType;
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_