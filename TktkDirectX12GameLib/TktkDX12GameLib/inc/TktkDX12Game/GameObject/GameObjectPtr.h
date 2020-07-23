#ifndef GAME_OBJECT_PTR_H_
#define GAME_OBJECT_PTR_H_

#include <memory>

namespace tktk
{
	// �O���錾
	class GameObject;

	// �Q�[���I�u�W�F�N�g���������߂̃|�C���^
	class GameObjectPtr
	{
	public:

		// nullptr�Ƃ��č쐬����
		GameObjectPtr() = default;

		// ������weak�|�C���^�����`�ō쐬����
		explicit GameObjectPtr(const std::weak_ptr<GameObject>& weakPtr);

	public:

		// ���g�̃|�C���^���w���Ă���Q�[���I�u�W�F�N�g������ł��邩���肷��
		bool expired() const;

		// �����̃|�C���^�Ɠ���ȃQ�[���I�u�W�F�N�g���𔻒肷��
		bool isSame(const GameObjectPtr& other) const;

		// �|�C���^�ɃA�N�Z�X����
		std::shared_ptr<GameObject> operator ->() const;

	private:

		std::weak_ptr<GameObject> m_gameObjectPtr;
	};
}
#endif // !GAME_OBJECT_PTR_H_