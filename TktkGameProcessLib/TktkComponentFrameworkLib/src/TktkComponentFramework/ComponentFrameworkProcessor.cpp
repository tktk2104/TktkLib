#include "TktkComponentFramework/ComponentFrameworkProcessor.h"

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetGameObjectChecker.h>
#include "TktkComponentFramework/GameObject/GameObject.h"
#include "TktkComponentFramework/Time/TimeManager.h"

#include "TktkComponentFramework/GameObject/GameObject.h"

namespace tktk
{
	ClassFuncProcessor<
		SimpleCont<HasAlwaysRunFuncClass<has_frameBegin_checker<>, frameBegin_runner<>>>,
		SimpleCont<HasActiveCheckClass>,
		MovOneCont<HasFuncClass<has_start_checker<>, start_runner<>>>,
		SortedCont<HasFuncClass<has_update_checker<>, update_runner<>>, getUpdatePriority_runner<>>,
		SimColCont<HasCollideClass, getCollisionGroup_runner<>>,
		SimpleCont<HasFuncClass<has_afterCollide_checker<>, afterCollide_runner<>>>,
		SortedCont<HasFuncClass<has_draw_checker<>, draw_runner<>>, getDrawPriority_runner<>>,
		SimpleCont<HasAlwaysRunFuncClass<has_frameEnd_checker<>, frameEnd_runner<>>>,
		SimpleCont<HasIsDestroyClass>
	> ComponentFrameworkProcessor::m_classFuncProcessor(8U);

	GameObjectList ComponentFrameworkProcessor::m_gameObjectList;

	bool ComponentFrameworkProcessor::m_isExit{ false };

	void ComponentFrameworkProcessor::run()
	{
		TimeManager::initialize();

		while (!m_isExit)
		{
			TimeManager::update();

			m_classFuncProcessor.processing();
			m_gameObjectList.removeExpandPtr();
		}
		// GameObject���ɊJ�����鏈���i��ɃR���|�[�l���g����������ƃ������O�Q�Ƃ��N����j
		m_gameObjectList.removeAll();

		m_classFuncProcessor.finalize();
	}

	// ���݂̃t���[���ŃQ�[�����I������
	void ComponentFrameworkProcessor::exitGame()
	{
		m_isExit = true;
	}

	// GameObject�𐶐�����
	CfpPtr<GameObject> ComponentFrameworkProcessor::createGameObject(bool isStatic)
	{
		GameObject* rawGameObjectPtr = new GameObject(isStatic);
		CfpPtr<GameObject> gameObject = addClass(isStatic, rawGameObjectPtr);
		setGameObject_runner<CfpPtr<GameObject>>::checkAndRun(rawGameObjectPtr, gameObject);
		m_gameObjectList.add(gameObject);
		return gameObject;
	}

	// �Փ˔���̃O���[�v��ǉ�
	void ComponentFrameworkProcessor::addCollisionGroupPair(int first, int second)
	{
		auto collisionContainer = m_classFuncProcessor.getRunFuncContainerPtr<4, tktk::RunFuncSimpleCollisionContainer<tktk::HasCollideClass, getCollisionGroup_runner<>>>();
		collisionContainer->addCollisionGroupPair(first, second);
	}

	// �����̃^�O������GameObject���擾����
	CfpPtr<GameObject> ComponentFrameworkProcessor::findGameObjectWithTag(int tag)
	{
		return m_gameObjectList.findWithTag(tag);
	}

	// �����̃^�O������GameObject���擾����
	std::forward_list<CfpPtr<GameObject>> ComponentFrameworkProcessor::findGameObjectsWithTag(int tag)
	{
		return m_gameObjectList.findWithTagAll(tag);
	}

	// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
	void ComponentFrameworkProcessor::sendMessage(int eventMessageType, const SafetyVoidPtr & param)
	{
		m_gameObjectList.sendMessage(eventMessageType, param);
	}

	// �S�Ă̊֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
	void ComponentFrameworkProcessor::setIsRunFuncAll(bool flag)
	{
		m_classFuncProcessor.setIsRunFuncAll(flag);
	}
}