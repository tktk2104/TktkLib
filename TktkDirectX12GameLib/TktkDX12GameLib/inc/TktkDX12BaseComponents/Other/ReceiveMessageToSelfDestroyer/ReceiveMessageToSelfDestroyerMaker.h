#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_

#include "ReceiveMessageToSelfDestroyer.h"

namespace tktk
{
	class ReceiveMessageToSelfDestroyerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		ReceiveMessageToSelfDestroyerMaker() = default;
		ReceiveMessageToSelfDestroyerMaker(const ReceiveMessageToSelfDestroyerMaker& other) = default;
		ReceiveMessageToSelfDestroyerMaker& operator = (const ReceiveMessageToSelfDestroyerMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static ReceiveMessageToSelfDestroyerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<ReceiveMessageToSelfDestroyer> create();

	public:

		// ���g���E�����b�Z�[�W�̎�ނ�ݒ�
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(int value);

	private:

		// ���g�̃|�C���^
		static ReceiveMessageToSelfDestroyerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		int m_destroyMessegeType{ 0 };
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_