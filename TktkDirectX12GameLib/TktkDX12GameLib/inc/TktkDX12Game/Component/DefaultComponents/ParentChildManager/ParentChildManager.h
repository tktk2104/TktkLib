#ifndef PARENT_CHILD_MANAGER_H_
#define PARENT_CHILD_MANAGER_H_

#include "../../ComponentBase.h"
#include "../../../GameObject/GameObjectPtr.h"
#include "ChildList.h"

namespace tktk
{
	// �e�q�֌W���Ǘ�����R���|�[�l���g
	// ��GameObject�����Ə����AddComponent�����
	class ParentChildManager
		: public ComponentBase
	{
	public:

		ParentChildManager() = default;

	public:

		// �q�v�f�̃��X�g���X�V����
		void updateContainer();

	public:

		// �S�Ă̎q���̑S�ẴR���|�[�l���g�̐e�v�f���ς�������֐����Ă�
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// �S�Ă̎q�v�f���폜����
		void removeChild(const GameObjectPtr& child);

		// �S�Ă̎q�v�f���E��
		void destroyChildren();

		// �e�v�f���擾����
		const GameObjectPtr& getParent() const;

		// �e�v�f��ݒ肷��
		void setParent(const GameObjectPtr& parent);

		// �q�v�f�̃��X�g���擾����
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// �q�v�f��ǉ�����
		void addChild(const GameObjectPtr& child);

		// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		void sendMessage(unsigned int messageId, const MessageAttachment& value);

	public:

		GameObjectPtr m_parent;

		ChildList m_childList;
	};
}
#endif // !PARENT_CHILD_MANAGER_H_