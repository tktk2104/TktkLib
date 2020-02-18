#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "../ComponentFrameworkProcessor.h"

namespace tktk
{
	class GameObject;

	// �S�ẴQ�[���I�u�W�F�N�g�̃}�l�[�W���[
	class GameObjectManager
	{
	public:

		// GameObject���쐬����
		static CfpPtr<GameObject> createGameObject(bool isStatic);

		// �����̃^�O������GameObject���擾����
		static CfpPtr<GameObject> findGameObjectWithTag(int tag);

		// �w�肵���R���e�i�ň����̃^�O������GameObject���擾����
		static std::forward_list<CfpPtr<GameObject>> findGameObjectsWithTag(int tag);

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		static void sendMessage(int eventMessageType, const SafetyVoidPtr& param = SafetyVoidPtr());
	};
}
#endif // !GAME_OBJECT_MANAGER_H_