#ifndef GAME_OBJECT_LIST_H_
#define GAME_OBJECT_LIST_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>

namespace tktk
{
	class GameObject;

	// �S�ẴQ�[���I�u�W�F�N�g�̃��X�g
	class GameObjectList
	{
	public:

		GameObjectList() = default;

		// �V����GameObject��ǉ�����
		void add(CfpPtr<GameObject> addGameObject);
		
		// �폜�t���O�̗�����GameObject���폜����
		void removeExpandPtr();
		
		// �����̃^�O������GameObject���擾����
		CfpPtr<GameObject> findWithTag(int tag);
		
		// �����̃^�O������GameObject��S�Ď擾����
		std::forward_list<CfpPtr<GameObject>> findWithTagAll(int tag);

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		void sendMessage(int eventMessageType, const SafetyVoidPtr& param);

		// �S�Ă�GameObject���폜����
		void removeAll();

	private:

		std::forward_list<CfpPtr<GameObject>> m_gameObjectList;
	};
}
#endif // !GAME_OBJECT_LIST_H_