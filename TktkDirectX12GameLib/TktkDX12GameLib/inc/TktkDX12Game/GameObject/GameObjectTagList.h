#ifndef GAME_OBJECT_TAG_LIST_H_
#define GAME_OBJECT_TAG_LIST_H_

#include <unordered_set>

namespace tktk
{
	// �Q�[���I�u�W�F�N�g�̃^�O���Ǘ�����R���e�i
	class GameObjectTagList
	{
	public:

		GameObjectTagList() = default;
		~GameObjectTagList() {}

	public:

		// �����̃^�O��ǉ�����
		void addTag(int tag);

		// �����̃^�O���폜����
		void removeTag(int tag);

		// �����̃^�O���������Ă��邩�𔻒肷��
		bool contain(int tag) const;

	private:

		std::unordered_set<int> m_tagList;
	};
}
#endif // !GAME_OBJECT_TAG_LIST_H_