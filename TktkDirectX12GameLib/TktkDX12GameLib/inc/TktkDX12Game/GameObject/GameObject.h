#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "GameObjectTagList.h"

namespace tktk
{
	class GameObject
	{
	public:

		GameObject();

	public:



	private:

		bool				m_isStatic{ false };
		bool				m_isDestroy{ false };
		bool				m_isActive{ true };
		bool				m_nextFrameIsActive{ true };
		GameObjectTagList	m_tagList{};
	};
}
#endif // !GAME_OBJECT_H_