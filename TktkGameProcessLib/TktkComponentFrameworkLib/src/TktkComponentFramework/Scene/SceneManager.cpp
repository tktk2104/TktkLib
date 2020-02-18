#include "TktkComponentFramework/Scene/SceneManager.h"

namespace tktk
{
	// シーンのポインタを取得する速度を上げるためのmap
	std::unordered_map<unsigned int, ProcessingClassPtr> SceneManager::m_sceneMap;
}