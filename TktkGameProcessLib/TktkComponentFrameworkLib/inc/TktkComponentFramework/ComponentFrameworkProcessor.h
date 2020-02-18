#ifndef COMPONENT_FRAMEWORK_PROCESSOR_H_
#define COMPONENT_FRAMEWORK_PROCESSOR_H_

#include <TktkClassFuncProcessor/ClassFuncProcessor.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSimpleContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSortedContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSimpleCollisionContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncMoveOnceContainer.h>

#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasActiveCheckClass.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasCollideClass.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasIsDestroyClass.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasFuncClass.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasAlwaysRunFuncClass.h>

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasFrameBeginChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasAfterCollideChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasFrameEndChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasGetCollisionGroupChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasGetUpdatePriorityChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasGetDrawPriorityChecker.h>

#include "GameObject/GameObjectList.h"
#include "Component/ComponentUpdatePrioritySetter.h"

namespace tktk
{
	class GameObject;

	// �ʖ��[�Y
	template <class T>
	using SimpleCont = RunFuncSimpleContainer<T>;
	template <class T, class U>
	using SortedCont = RunFuncSortedContainer<T, U>;
	template <class T>
	using MovOneCont = RunFuncMoveOnceContainer<T>;
	template <class T, class U>
	using SimColCont = RunFuncSimpleCollisionContainer<T, U>;

	// �R���|�[�l���g�w���ŃQ�[������鏈�����Ǘ�����@�\�̑����C���^�[�t�F�[�X
	class ComponentFrameworkProcessor
	{
	public:

		// �N������
		static void run();

		// ���݂̃t���[���ŃQ�[�����I������
		static void exitGame();

	public:

		// �V���ȃN���X�����̃t���[���Œǉ�
		// ��isStatic��true�ɂ���Ɠ���͌y���Ȃ邪�A�ǉ����ƍ폜�����d����
		template <class T>
		static CfpPtr<T> addClass(bool isStatic, T* newClass);

		// �ǉ��������N���X���쐬������Ŏ��̃t���[���Œǉ�
		// ��isStatic��true�ɂ���Ɠ���͌y���Ȃ邪�A�ǉ����ƍ폜�����d����
		template <class T, class... Args>
		static CfpPtr<T> createClass(bool isStatic, const Args&... constructorValue);

		// GameObject�𐶐�����
		static CfpPtr<GameObject> createGameObject(bool isStatic);

		// �w�肵���^�̃R���|�[�l���g�̍X�V�D��x��ݒ�
		template <class T>
		static void addComponentUpdatePriority(float priority);

		// �Փ˔���̃O���[�v��ǉ�
		static void addCollisionGroupPair(int first, int second);

		// �����̃^�O������GameObject���擾����
		static CfpPtr<GameObject> findGameObjectWithTag(int tag);

		// �����̃^�O������GameObject��S�Ď擾����
		static std::forward_list<CfpPtr<GameObject>> findGameObjectsWithTag(int tag);

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		static void sendMessage(int eventMessageType, const SafetyVoidPtr& param);

		// �w�肵���֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
		template<int FuncNum>
		static void setIsRunFunc(bool flag);

		// �S�Ă̊֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
		static void setIsRunFuncAll(bool flag);

	private:

		// �|�����[�t�B�Y���Ȋ֐����񂷃}�l�[�W���[�N���X
		static ClassFuncProcessor<
			SimpleCont<HasAlwaysRunFuncClass<has_frameBegin_checker<>, frameBegin_runner<>>>,
			SimpleCont<HasActiveCheckClass>,
			MovOneCont<HasFuncClass<has_start_checker<>, start_runner<>>>,
			SortedCont<HasFuncClass<has_update_checker<>, update_runner<>>, getUpdatePriority_runner<>>,
			SimColCont<HasCollideClass, getCollisionGroup_runner<>>,
			SimpleCont<HasFuncClass<has_afterCollide_checker<>, afterCollide_runner<>>>,
			SortedCont<HasFuncClass<has_draw_checker<>, draw_runner<>>, getDrawPriority_runner<>>,
			SimpleCont<HasAlwaysRunFuncClass<has_frameEnd_checker<>, frameEnd_runner<>>>,
			SimpleCont<HasIsDestroyClass>
		> m_classFuncProcessor;

		// GameObject���Ǘ����郊�X�g
		static GameObjectList m_gameObjectList;

		// �Q�[���I���t���O
		static bool m_isExit;
	};

	// �V���ȃN���X�����̃t���[���Œǉ�
	// ��isStatic��true�ɂ���Ɠ���͌y���Ȃ邪�A�ǉ����ƍ폜�����d����
	template<class T>
	inline CfpPtr<T> ComponentFrameworkProcessor::addClass(bool isStatic, T* newClass)
	{
		return m_classFuncProcessor.addClass<T>(isStatic, newClass);
	}

	// �ǉ��������N���X���쐬������Ŏ��̃t���[���Œǉ�
	// ��isStatic��true�ɂ���Ɠ���͌y���Ȃ邪�A�ǉ����ƍ폜�����d����
	template<class T, class ...Args>
	inline CfpPtr<T> ComponentFrameworkProcessor::createClass(bool isStatic, const Args & ...constructorValue)
	{
		return addClass<T>(isStatic, new T(constructorValue...));
	}

	// �w�肵���^�̃R���|�[�l���g�̍X�V�D��x��ݒ�
	template<class T>
	inline void ComponentFrameworkProcessor::addComponentUpdatePriority(float priority)
	{
		ComponentUpdatePrioritySetter::addUpdatePriority<T>(priority);
	}

	// �w�肵���֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
	template<int FuncNum>
	inline void ComponentFrameworkProcessor::setIsRunFunc(bool flag)
	{
		m_classFuncProcessor.setIsRunFunc<FuncNum>(flag);
	}
}
#endif // !COMPONENT_FRAMEWORK_PROCESSOR_H_