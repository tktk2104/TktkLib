#include "TktkComponentFramework/Scene/SceneManager.h"

namespace tktk
{
	// �V�[���̃|�C���^���擾���鑬�x���グ�邽�߂�map
	std::unordered_map<unsigned int, ProcessingClassPtr> SceneManager::m_sceneMap;
}