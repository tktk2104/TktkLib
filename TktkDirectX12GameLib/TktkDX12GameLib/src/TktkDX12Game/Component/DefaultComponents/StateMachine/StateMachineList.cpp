#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachineList.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/Component/ComponentGameObjectFunc/GameObjectComponentList.h"
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachine.h"

namespace tktk
{
	StateMachineList::StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user, GameObjectComponentList* componentList)
	{
		// �e�̏�Ԃ������Ȃ��X�e�[�g�}�V�������
		for (const auto& node : initParam.m_roots)
		{
			// �X�e�[�g�}�V���������
			auto createdComponent = DX12GameManager::createComponent<StateMachine>(node.m_id);

			// ������GameObject��ݒ肵
			createdComponent.lock()->setUser(user);

			// �X�e�[�g�}�V�����X�g�ɓo�^����
			m_stateMachineList[node.m_id] = { componentList->add<StateMachine>(createdComponent), {} };

			// �e�̏�Ԃ����X�e�[�g�}�V������邽�߂ɍċN�������s��
			createNode(m_stateMachineList.at(node.m_id), node, user, componentList);
		}
	}

	void StateMachineList::addChild(const std::vector<int>& targetState, const GameObjectPtr& child)
	{
		getTarget(targetState)->addChild(child);
	}

	void StateMachineList::addComponent(const std::vector<int>& targetState, const ComponentBasePtr& componentPtr)
	{
		getTarget(targetState)->addComponent(componentPtr);
	}

	void StateMachineList::createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user, GameObjectComponentList* componentList)
	{
		// �e�̏�Ԃ����X�e�[�g�}�V�������
		for (const auto& node : nodeInitParam.m_child)
		{
			// �X�e�[�g�}�V���������
			auto createdComponent = DX12GameManager::createComponent<StateMachine>(node.m_id);

			// ������GameObject��ݒ肵
			createdComponent.lock()->setUser(user);

			// �e�̃X�e�[�g�}�V���ɓo�^��
			parentNode.m_stateMachine->addComponent(ComponentBasePtr(createdComponent));

			// �X�e�[�g�}�V�����X�g�ɓo�^����
			parentNode.m_childNode[node.m_id] = { componentList->add<StateMachine>(createdComponent), {} };

			// ����Ȃ�q�v�f����邽�߂ɍċN����
			createNode(parentNode.m_childNode.at(node.m_id), node, user, componentList);
		}
	}

	ComponentPtr<StateMachine> StateMachineList::getTarget(const std::vector<int>& targetState) const
	{
#ifdef _DEBUG
		if (targetState.size() == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

		const StateMachineList::Node* curNodePtr = nullptr;

		for (int node : targetState)
		{
			// �����񃋁[�v���̂݃A���S���Y�����Ⴄ
			if (curNodePtr == nullptr)
			{
#ifdef _DEBUG
				if (m_stateMachineList.count(node) == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

				curNodePtr = &m_stateMachineList.at(node);
				continue;
			}

#ifdef _DEBUG
			if (m_stateMachineList.count(node) == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

			curNodePtr = &curNodePtr->m_childNode.at(node);
		}

		if (curNodePtr != nullptr) return curNodePtr->m_stateMachine;

#ifdef _DEBUG
		else  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG
		return ComponentPtr<StateMachine>();
	}
}