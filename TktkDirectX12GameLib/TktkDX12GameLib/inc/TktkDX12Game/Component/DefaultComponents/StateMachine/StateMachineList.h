#ifndef STATE_MACHINE_LIST_H_
#define STATE_MACHINE_LIST_H_

#include <vector>
#include <unordered_map>
#include "../../../GameObject/GameObjectPtr.h"
#include "../../ComponentBasePtr.h"
#include "StateMachineListInitParam.h"

namespace tktk
{
	class GameObjectComponentList;
	class StateMachine;

	// �X�e�[�g�}�V���̃|�C���^���Ǘ�����N���X
	class StateMachineList
	{
	public:

		StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user, GameObjectComponentList* componentList);

	public:

		// int�^�̔z��ŃX�e�[�g���w�肵�A�q�v�f��ǉ�����
		// ���u{ 1, 10, 30 }�v�Łu�g�X�e�[�g�P�h���́g�X�e�[�g�P�O�h���́g�X�e�[�g�R�O�h�ɒǉ��v�ƂȂ�
		void addChild(const std::vector<int>& targetState, const GameObjectPtr& child);

		// int�^�̔z��ŃX�e�[�g���w�肵�A�����̃R���|�[�l���g��ǉ�����
		// ���u{ 1, 10, 30 }�v�Łu�g�X�e�[�g�P�h���́g�X�e�[�g�P�O�h���́g�X�e�[�g�R�O�h�ɒǉ��v�ƂȂ�
		void addComponent(const std::vector<int>& targetState, const ComponentBasePtr& componentPtr);

	private:

		// ����q�P���̗v�f
		struct Node
		{
			ComponentPtr<StateMachine>		m_stateMachine;
			std::unordered_map<int, Node>	m_childNode;
		};

	private:

		// �e�̏�Ԃ����X�e�[�g�}�V�������
		void createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user, GameObjectComponentList* componentList);

		// int�^�̔z�񂩂�w��̃X�e�[�g���擾����
		ComponentPtr<StateMachine> getTarget(const std::vector<int>& targetState) const;

	private:

		// ����q�\���Ń|�C���^���Ǘ�����
		std::unordered_map<int, Node>	m_stateMachineList;
	};
}
#endif // !STATE_MACHINE_LIST_H_
