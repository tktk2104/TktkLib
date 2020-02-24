#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetActiveChecker.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSimpleContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasAlwaysRunFuncClass.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "CurStateTypeList.h"
#include "StateMachineRegistrationList.h"

namespace tktk
{
	// スーパー★別名ーズ
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker>
	using SimpleCont = RunFuncSimpleContainer<NodeType, HasFuncChecker>;

	template <class JudgePtrType>
	using HasSetActiveChecker = has_setActive_checker<JudgePtrType, void, bool>;

	// サブ★別名ーズ
	using SetActiveCont = SimpleCont<HasAlwaysRunFuncClass<setActive_runner, void, bool>, HasSetActiveChecker>;

	// ステートマシーンコンポーネント
	// 【前提コンポーネント：CurStateTypeList】
	class StateMachine
		: public ComponentBase
	{
	public:

		// StateMachinePtrを生成する
		static CfpPtr<StateMachine> create(
			CfpPtr<GameObject> user,	// このステートを持つGameObject
			int stateType				// このステートマシンのステートタイプ
		);

		// StateMachinePtrを生成する（入れ子ステート）
		static CfpPtr<StateMachine> create(
			CfpPtr<StateMachine> parentState,	// このステートを持つステート
			int stateType					// このステートマシンのステートタイプ
		);

	public:

		StateMachine(
			int stateType	// このステートマシンのステートタイプ
		);

	public:

		// <PolymorphismFunc>
		void onDisable();
		void update();

	public:

		// このステートに子要素を追加する
		void addChild(bool isStatic, CfpPtr<GameObject> child);

		// このステートにコンポーネントを追加する
		template <class T>
		CfpPtr<T> addComponent(T* component);

		// 引数のコンポーネントがステートマシンに登録されているかを判定する
		template <class T>
		bool isRegistrationStateMachine(CfpPtr<T> component);

	private:

		// 自身のステートの種類
		int m_selfStateType;

		// 自身の現在のステートの種類のコンポーネント
		CfpPtr<CurStateTypeList> m_curStateTypeList;

		// アクティブ状態を切り替えるためのコンテナのラッパー
		SetActiveCont m_hasSetActiveClassList;

		// このステートマシーンにどのコンポーネントが登録されているかを管理するリスト
		StateMachineRegistrationList m_stateMachineRegistrationList;
	};

	// このステートにコンポーネントを追加する
	template<class T>
	inline CfpPtr<T> StateMachine::addComponent(T* component)
	{
		auto cfpPtr = getGameObject()->addComponent(component);
		setActive_runner<bool>::checkAndRun(component, false);
		m_hasSetActiveClassList.checkAndAdd<T>(getGameObject()->isStatic(), cfpPtr.processingClassPtr(), component);
		m_stateMachineRegistrationList.addNode(cfpPtr.processingClassPtr());
		return cfpPtr;
	}

	// 引数のコンポーネントがステートマシンに登録されているかを判定する
	template<class T>
	inline bool StateMachine::isRegistrationStateMachine(CfpPtr<T> component)
	{
		return m_stateMachineRegistrationList.contain(component);
	}
}
#endif // !STATE_MACHINE_H_