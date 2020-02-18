#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_

#include "ReceiveMessageToSelfDestroyer.h"

namespace tktk
{
	class ReceiveMessageToSelfDestroyerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static ReceiveMessageToSelfDestroyerMaker& makeStart();

	public:

		// �쐬����
		ReceiveMessageToSelfDestroyer* create();

		// ���g���E�����b�Z�[�W�̎�ނ�ݒ�
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(int value);

	private:

		// ���g�̃|�C���^
		static ReceiveMessageToSelfDestroyerMaker m_self;

	private:

		int m_destroyMessegeType;
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_