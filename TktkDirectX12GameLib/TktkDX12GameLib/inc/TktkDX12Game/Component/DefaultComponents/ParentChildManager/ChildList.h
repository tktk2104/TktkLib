#ifndef CHILD_LIST_H_
#define CHILD_LIST_H_

#include <forward_list>
#include "../../../GameObject/GameObjectPtr.h"

namespace tktk
{
	// �q�v�f�̃��X�g
	class ChildList
	{
	public:

		ChildList() = default;
		~ChildList() {}

	public:

		// �V���Ȏq�v�f��ǉ�
		void addChild(const GameObjectPtr& child);

		// �q�v�f�̃��X�g���擾
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// ���X�g���X�V����
		void updateContainer();

		// �w��̎q�v�f�����X�g����폜����
		void remove(const GameObjectPtr& gameObject);

		// �S�Ă̎q�v�f���E��
		void destroyAll();

		//// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		//void sendMessage(int eventMessageType, const GameObjectPtr& param);

	private:

		std::forward_list<GameObjectPtr> m_childList;
	};
}
#endif // !CHILD_LIST_H_