#ifndef CHILD_LIST_H_
#define CHILD_LIST_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>

namespace tktk
{
	class GameObject;

	// �q�v�f�̃��X�g
	class ChildList
	{
	public:

		ChildList() = default;
		~ChildList() {}

	public:

		// �V���Ȏq�v�f��ǉ�
		void addChild(CfpPtr<GameObject> child);

		// �q�v�f�̃��X�g���擾
		const std::forward_list<CfpPtr<GameObject>>& getChildren() const;

		// ���X�g���X�V����
		void updateContainer();

		// �w��̎q�v�f���폜����
		void remove(CfpPtr<GameObject> gameObject);

		// �S�Ă̎q�v�f�����X�g����폜����
		void removeAll();

		// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		void sendMessage(int eventMessageType, const SafetyVoidPtr& param);

	private:

		std::forward_list<CfpPtr<GameObject>> m_childList;
	};
}
#endif // !CHILD_LIST_H_