#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <memory>
#include <forward_list>
#include "GameObjectPtr.h"

namespace tktk
{
	class GameObject;

	// �Q�[���I�u�W�F�N�g�Ǘ��N���X
	class GameObjectManager
	{
	public:

		GameObjectManager() = default;

	public:

		void update();

	public:

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		GameObjectPtr createGameObject();

		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		GameObjectPtr findGameObjectWithTag(int tag) const;

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag) const;

	private:

		std::forward_list<std::shared_ptr<GameObject>> m_gameObjectList;
	};
}
#endif // !GAME_OBJECT_MANAGER_H_