#include "TktkComponentFramework/GameObject/GameObjectManager.h"

#include "TktkComponentFramework/ComponentFrameworkProcessor.h"
#include "TktkComponentFramework/GameObject/GameObject.h"

namespace tktk
{
	// GameObject���쐬����
	CfpPtr<GameObject> GameObjectManager::createGameObject(bool isStatic)
	{
		return ComponentFrameworkProcessor::createGameObject(isStatic);
	}

	// �����̃^�O������GameObject���擾����
	CfpPtr<GameObject> GameObjectManager::findGameObjectWithTag(int tag)
	{
		return ComponentFrameworkProcessor::findGameObjectWithTag(tag);
	}

	std::forward_list<CfpPtr<GameObject>> GameObjectManager::findGameObjectsWithTag(int tag)
	{
		return ComponentFrameworkProcessor::findGameObjectsWithTag(tag);
	}

	// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
	void GameObjectManager::sendMessage(int eventMessageType, const SafetyVoidPtr & param)
	{
		ComponentFrameworkProcessor::sendMessage(eventMessageType, param);
	}
}