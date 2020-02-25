#ifndef PARENT_CHILD_MANAGER_H_
#define PARENT_CHILD_MANAGER_H_

#include <forward_list>
#include "ChildList.h"
#include "../../ComponentBase.h"

namespace tktk
{
	class GameObject;

	// �e�v�f�A�q�v�f���Ǘ�����R���|�[�l���g
	class ParentChildManager
		: public ComponentBase
	{
	public:

		ParentChildManager() = default;

	public:

		void updateContainer();

	public:

		// �S�Ă̎q���̑S�ẴR���|�[�l���g�̐e�v�f���ς�������֐����Ă�
		void runAfterChangeParentAll(CfpPtr<GameObject> beforParent);

		// �S�Ă̎q�v�f���폜����
		void removeChild(CfpPtr<GameObject> child);

		// �S�Ă̎q�v�f���폜����
		void removeChildren();

		// �e�v�f���擾����
		CfpPtr<GameObject> getParent() const;

		// �e�v�f��ݒ肷��
		void setParent(CfpPtr<GameObject> parent);

		// �q�v�f�̃��X�g���擾����
		const std::forward_list<CfpPtr<GameObject>>& getChildren() const;

		// �q�v�f��ǉ�����
		void addChild(CfpPtr<GameObject> child);

		// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		void sendMessage(int eventMessageType, const SafetyVoidPtr& param);

	private:

		CfpPtr<GameObject> m_parent;

		ChildList m_children;
	};
}
#endif // !PARENT_CHILD_MANAGER_H_