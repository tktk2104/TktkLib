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

	// �X�[�p�[���ʖ��[�Y
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker>
	using SimpleCont = RunFuncSimpleContainer<NodeType, HasFuncChecker>;
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker, class GetPriorityFuncRunner>
	using SortedCont = RunFuncSortedContainer<NodeType, HasFuncChecker, GetPriorityFuncRunner>;
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker>
	using MovOneCont = RunFuncMoveOnceContainer<NodeType, HasFuncChecker>;
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker, class GetGroupFuncRunner>
	using SimColCont = RunFuncSimpleCollisionContainer<NodeType, HasFuncChecker, GetGroupFuncRunner>;

	template <class JudgePtrType>
	using hasFrameBeginChecker		= has_frameBegin_checker<JudgePtrType, void>;
	template <class JudgePtrType>
	using hasActiveCheckFuncChecker = std::bool_constant<has_isActive_checker<JudgePtrType, bool>::value && (has_onEnable_checker<JudgePtrType, void>::value || has_onDisable_checker<JudgePtrType, void>::value)>;
	template <class JudgePtrType>
	using hasStartChecker			= has_start_checker<JudgePtrType, void>;
	template <class JudgePtrType>
	using hasUpdateChecker			= has_update_checker<JudgePtrType, void>;
	template <class JudgePtrType>
	using hasCollideFuncChecker		= std::bool_constant<has_isCollide_checker<JudgePtrType, bool, ProcessingClassPtr>::value && has_onCollide_checker<JudgePtrType, void, ProcessingClassPtr>::value>;
	template <class JudgePtrType>
	using hasAfterCollideChecker	= has_afterCollide_checker<JudgePtrType, void>;
	template <class JudgePtrType>
	using hasDrawChecker			= has_draw_checker<JudgePtrType, void>;
	template <class JudgePtrType>
	using hasFrameEndChecker		= has_frameEnd_checker<JudgePtrType, void>;
	template <class JudgePtrType>
	using hasDestroyFuncChecker		= has_isDestroy_checker<JudgePtrType, bool>;

	// �T�u���ʖ��[�Y
	using FrameBeginCont	= SimpleCont<HasAlwaysRunFuncClass<frameBegin_runner, void>, hasFrameBeginChecker>;
	using ActiveCheckCont	= SimpleCont<HasActiveCheckClass, hasActiveCheckFuncChecker>;
	using StartCont			= MovOneCont<HasFuncClass<start_runner, void>, hasStartChecker>;
	using UpdateCont		= SortedCont<HasFuncClass<update_runner, void>, hasUpdateChecker, getUpdatePriority_runner<float>>;
	using CollideCont		= SimColCont<HasCollideClass, hasCollideFuncChecker, getCollisionGroup_runner<int>>;
	using AfterCollideCont	= SortedCont<HasFuncClass<afterCollide_runner, void>, hasAfterCollideChecker, getUpdatePriority_runner<float>>;
	using DrawCont			= SortedCont<HasFuncClass<draw_runner, void>, hasDrawChecker, getDrawPriority_runner<float>>;
	using FrameEndCont		= SimpleCont<HasAlwaysRunFuncClass<frameEnd_runner, void>, hasFrameEndChecker>;
	using DestroyCheckCont	= SimpleCont<HasIsDestroyClass, hasDestroyFuncChecker>;

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
		static ClassFuncProcessor<FrameBeginCont, ActiveCheckCont, StartCont, UpdateCont, CollideCont, AfterCollideCont, DrawCont, FrameEndCont, DestroyCheckCont> m_classFuncProcessor;
		
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