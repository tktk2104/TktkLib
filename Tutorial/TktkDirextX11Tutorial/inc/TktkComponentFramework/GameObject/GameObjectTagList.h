#ifndef GAME_OBJECT_TAG_LIST_H_
#define GAME_OBJECT_TAG_LIST_H_

#include <unordered_set>

namespace tktk
{
	class GameObjectTagList
	{
	public:

		GameObjectTagList() = default;
		~GameObjectTagList() {}

	public:

		void addTag(int tag);

		void removeTag(int tag);

		bool contain(int tag) const;

	private:

		std::unordered_set<int> m_tagList;
	};
}
#endif // !GAME_OBJECT_TAG_LIST_H_