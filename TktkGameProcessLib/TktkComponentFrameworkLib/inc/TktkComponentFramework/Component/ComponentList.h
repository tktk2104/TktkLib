#ifndef COMPONENT_LIST_H_
#define COMPONENT_LIST_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSimpleContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasAlwaysRunFuncClass.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasOneArgFuncClass.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasTwoArgFuncClass.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasHandleMessageChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasAfterChangeParentChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnDestroyChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollisionEnterChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollisionStayChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollisionExitChecker.h>
#include "../ComponentFrameworkProcessor.h"

namespace tktk
{
	// 別名ーズ
	template <class T>
	using SimpleCont = RunFuncSimpleContainer<T>;

	// コンポーネントを管理するリスト
	class ComponentList
	{
	public:

		ComponentList() = default;
		~ComponentList() {}

	public:

		// 新たなコンポーネントを追加
		template <class T>
		CfpPtr<T> add(bool isStatic, T* component);

		// 最初に見つけたテンプレートパラメータのコンポーネントを取得
		template <class T>
		CfpPtr<T> getComponent() const;

		// 全てのテンプレートパラメータのコンポーネントを取得
		template <class T>
		std::forward_list<CfpPtr<T>> getComponentAll() const;

		void updateContainer();

		// 全てのコンポーネントを削除する
		void destroyAll();

		// 全てのコンポーネントの親要素が変わった時関数を呼ぶ
		void afterChangeParentAll(CfpPtr<GameObject> beforParent);
		
		// 全てのコンポーネントにメッセージを送信する
		void handleMessageAll(int eventMessageType, const SafetyVoidPtr& param);

		// 全てのコンポーネントの削除時関数を呼ぶ
		void onDestroyAll();
		
		// 全てのコンポーネントの衝突開始関数を呼ぶ
		void onCollisionEnterAll(CfpPtr<GameObject> other);
		
		// 全てのコンポーネントの衝突中関数を呼ぶ
		void onCollisionStayAll(CfpPtr<GameObject> other);
		
		// 全てのコンポーネントの衝突終了関数を呼ぶ
		void onCollisionExitAll(CfpPtr<GameObject> other);

	private:

		std::forward_list<ProcessingClassPtr> m_componentList;

		// 親要素が変わった時に呼ばれるコンポーネントのリスト
		SimpleCont<HasOneArgFuncClass<
			has_afterChangeParent_checker<CfpPtr<GameObject>>,
			afterChangeParent_runner<CfpPtr<GameObject>>,
			CfpPtr<GameObject>
		>> m_afterChangeParentableList;
		
		// メッセージ受信関数を持っているコンポーネントのリスト
		SimpleCont<HasTwoArgFuncClass<
			has_handleMessage_checker<int, const SafetyVoidPtr&>,
			handleMessage_runner<int, const SafetyVoidPtr&>,
			int, const SafetyVoidPtr&
		>> m_messageableList;

		// 削除時関数を持っているコンポーネントのリスト
		SimpleCont<HasAlwaysRunFuncClass<
				has_onDestroy_checker<>,
				onDestroy_runner<>
		>> m_hasOnDestroyClassContainer;
		
		// 衝突（開始・中・終了）時の関数を持っているコンポーネントのリスト
		SimpleCont<HasOneArgFuncClass<
			has_onCollisionEnter_checker<CfpPtr<GameObject>>,
			onCollisionEnter_runner<CfpPtr<GameObject>>,
			CfpPtr<GameObject>
		>> m_hasCollisionEnterClassContainer;

		SimpleCont<HasOneArgFuncClass<
			has_onCollisionStay_checker<CfpPtr<GameObject>>,
			onCollisionStay_runner<CfpPtr<GameObject>>,
			CfpPtr<GameObject>
		>> m_hasCollisionStayClassContainer;

		SimpleCont<HasOneArgFuncClass<
			has_onCollisionExit_checker<CfpPtr<GameObject>>,
			onCollisionExit_runner<CfpPtr<GameObject>>,
			CfpPtr<GameObject>
		>> m_hasCollisionExitClassContainer;
	};

	template<class T>
	inline CfpPtr<T> ComponentList::add(bool isStatic, T* component)
	{
		CfpPtr<T> componentPtr = ComponentFrameworkProcessor::addClass(isStatic, component);
		m_componentList.push_front(componentPtr.processingClassPtr());
		m_afterChangeParentableList.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_messageableList.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_hasOnDestroyClassContainer.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_hasCollisionEnterClassContainer.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_hasCollisionStayClassContainer.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_hasCollisionExitClassContainer.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		return componentPtr;
	}

	template<class T>
	inline CfpPtr<T> ComponentList::getComponent() const
	{
		for (ProcessingClassPtr component : m_componentList)
		{
			if (component->canCast<T>()) return CfpPtr<T>(component);
		}
		return CfpPtr<T>();
	}

	template<class T>
	inline std::forward_list<CfpPtr<T>> ComponentList::getComponentAll() const
	{
		std::forward_list<CfpPtr<T>> resultList;

		auto curItr = std::begin(m_componentList);

		while (curItr != std::end(m_componentList))
		{
			curItr = std::find_if(
				++curItr,
				std::end(m_componentList),
				[](ProcessingClassPtr node) { return node->canCast<T>(); }
			);

			if (curItr == std::end(m_componentList)) break;

			resultList.push_front(CfpPtr<T>((*curItr)));
		}
		return resultList;
	}
}
#endif // !COMPONENT_LIST_H_