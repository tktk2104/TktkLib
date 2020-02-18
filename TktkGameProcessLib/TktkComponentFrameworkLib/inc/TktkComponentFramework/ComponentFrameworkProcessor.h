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

namespace tktk
{
	class GameObject;

	// 別名ーズ
	template <class T>
	using SimpleCont = RunFuncSimpleContainer<T>;
	template <class T, class U>
	using SortedCont = RunFuncSortedContainer<T, U>;
	template <class T>
	using MovOneCont = RunFuncMoveOnceContainer<T>;
	template <class T, class U>
	using SimColCont = RunFuncSimpleCollisionContainer<T, U>;

	// コンポーネント指向でゲームを作る処理を管理する機能の総合インターフェース
	class ComponentFrameworkProcessor
	{
	public:

		// 起動する
		static void run();

		// 現在のフレームでゲームを終了する
		static void exitGame();

	public:

		// 新たなクラスを次のフレームで追加
		// ※isStaticをtrueにすると動作は軽くなるが、追加時と削除時が重たい
		template <class T>
		static CfpPtr<T> addClass(bool isStatic, T* newClass);

		// 追加したいクラスを作成した上で次のフレームで追加
		// ※isStaticをtrueにすると動作は軽くなるが、追加時と削除時が重たい
		template <class T, class... Args>
		static CfpPtr<T> createClass(bool isStatic, const Args&... constructorValue);

		// GameObjectを生成する
		static CfpPtr<GameObject> createGameObject(bool isStatic);

		// 衝突判定のグループを追加
		static void addCollisionGroupPair(int first, int second);

		// 引数のタグを持つGameObjectを取得する
		static CfpPtr<GameObject> findGameObjectWithTag(int tag);

		// 引数のタグを持つGameObjectを全て取得する
		static std::forward_list<CfpPtr<GameObject>> findGameObjectsWithTag(int tag);

		// 全てのGameObjectにメッセージを送信する
		static void sendMessage(int eventMessageType, const SafetyVoidPtr& param);

		// 指定した関数実行コンテナの関数実行フラグを設定する
		template<int FuncNum>
		static void setIsRunFunc(bool flag);

		// 全ての関数実行コンテナの関数実行フラグを設定する
		static void setIsRunFuncAll(bool flag);

	private:

		// ポリモーフィズムな関数を回すマネージャークラス
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

		// GameObjectを管理するリスト
		static GameObjectList m_gameObjectList;

		// ゲーム終了フラグ
		static bool m_isExit;
	};

	// 新たなクラスを次のフレームで追加
	// ※isStaticをtrueにすると動作は軽くなるが、追加時と削除時が重たい
	template<class T>
	inline CfpPtr<T> ComponentFrameworkProcessor::addClass(bool isStatic, T* newClass)
	{
		return m_classFuncProcessor.addClass<T>(isStatic, newClass);
	}

	// 追加したいクラスを作成した上で次のフレームで追加
	// ※isStaticをtrueにすると動作は軽くなるが、追加時と削除時が重たい
	template<class T, class ...Args>
	inline CfpPtr<T> ComponentFrameworkProcessor::createClass(bool isStatic, const Args & ...constructorValue)
	{
		return addClass<T>(isStatic, new T(constructorValue...));
	}

	// 指定した関数実行コンテナの関数実行フラグを設定する
	template<int FuncNum>
	inline void ComponentFrameworkProcessor::setIsRunFunc(bool flag)
	{
		m_classFuncProcessor.setIsRunFunc<FuncNum>(flag);
	}
}
#endif // !COMPONENT_FRAMEWORK_PROCESSOR_H_