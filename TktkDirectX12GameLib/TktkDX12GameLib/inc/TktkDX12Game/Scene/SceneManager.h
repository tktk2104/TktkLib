#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <vector>
#include "SceneInstanceCarrier.h"

namespace tktk
{
	class SceneManager
	{
	public:

		SceneManager(unsigned int sceneNum);
		~SceneManager();

	public:

		template<class SceneType, class... Args>
		void addScene(unsigned int id, Args... constructorArgs);

		void enableScene(unsigned int id);

		void disableScene(unsigned int id);

		void update();

	private:

		std::vector<SceneInstanceCarrier> m_sceneArray{};
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class SceneType, class ...Args>
	inline void SceneManager::addScene(unsigned int id, Args ...constructorArgs)
	{
		m_sceneArray.at(id).initialize<SceneType>(constructorArgs...);
	}
}
#endif // !SCENE_MANAGER_H_