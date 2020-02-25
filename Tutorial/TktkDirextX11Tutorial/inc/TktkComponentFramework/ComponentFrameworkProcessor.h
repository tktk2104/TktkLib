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

	// スーパー★別名ーズ
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

	// サブ★別名ーズ
	using FrameBeginCont	= SimpleCont<HasAlwaysRunFuncClass<frameBegin_runner, void>, hasFrameBeginChecker>;
	using ActiveCheckCont	= SimpleCont<HasActiveCheckClass, hasActiveCheckFuncChecker>;
	using StartCont			= MovOneCont<HasFuncClass<start_runner, void>, hasStartChecker>;
	using UpdateCont		= SortedCont<HasFuncClass<update_runner, void>, hasUpdateChecker, getUpdatePriority_runner<float>>;
	using CollideCont		= SimColCont<HasCollideClass, hasCollideFuncChecker, getCollisionGroup_runner<int>>;
	using AfterCollideCont	= SortedCont<HasFuncClass<afterCollide_runner, void>, hasAfterCollideChecker, getUpdatePriority_runner<float>>;
	using DrawCont			= SortedCont<HasFuncClass<draw_runner, void>, hasDrawChecker, getDrawPriority_runner<float>>;
	using FrameEndCont		= SimpleCont<HasAlwaysRunFuncClass<frameEnd_runner, void>, hasFrameEndChecker>;
	using DestroyCheckCont	= SimpleCont<HasIsDestroyClass, hasDestroyFuncChecker>;

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
		
		// 指定した型のコンポーネントの更新優先度を設定
		template <class T>
		static void addComponentUpdatePriority(float priority);
		
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
		static ClassFuncProcessor<FrameBeginCont, ActiveCheckCont, StartCont, UpdateCont, CollideCont, AfterCollideCont, DrawCont, FrameEndCont, DestroyCheckCont> m_classFuncProcessor;
		
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
	
	// 指定した型のコンポーネントの更新優先度を設定
	template<class T>
	inline void ComponentFrameworkProcessor::addComponentUpdatePriority(float priority)
	{
		ComponentUpdatePrioritySetter::addUpdatePriority<T>(priority);
	}
	
	// 指定した関数実行コンテナの関数実行フラグを設定する
	template<int FuncNum>
	inline void ComponentFrameworkProcessor::setIsRunFunc(bool flag)
	{
		m_classFuncProcessor.setIsRunFunc<FuncNum>(flag);
	}
}
#endif // !COMPONENT_FRAMEWORK_PROCESSOR_H_