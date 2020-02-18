#ifndef RUN_FUNC_MANAGER_H_
#define RUN_FUNC_MANAGER_H_

#include <tuple>
#include "../ProcessingClass/ProcessingClassPtr.h"

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasRunFuncChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasUpdateContainerChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasCheckAndAddChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetIsRunFuncChecker.h>
#include "../ProcessingClass/ClassTypeChecker.h"

namespace tktk
{
	/*
	┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	「void runFunc(...)」を持つ<RunFuncContainers>型の複数の要素を管理する「tuple」のラッパー
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	<RunFuncContainers>型の条件
	┃	・引数なしで作成できる
	┃	・要素を追加する「checkAndAdd(bool, ProcessingClassPtr, T*)」を持っている
	┃	・全ての要素の関数を実行する「runFunc(...)」を持っている
	┃	・各コンテナを更新する「updateContainer()」を持っている
	┃　・各コンテナ毎に自身が持つクラスの関数を実行するかのフラグを設定する「setIsRunFunc(bool)」を持っている
	┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	*/
	template <class... RunFuncContainers>
	class RunFuncManager
	{
	public:

		// 引数に自動で実行する関数の数を指定する
		RunFuncManager(unsigned int autoRunFuncCount);
		~RunFuncManager() {}

		RunFuncManager(const RunFuncManager& other) = delete;
		RunFuncManager& operator = (const RunFuncManager& other) = delete;

	public:

		// 関数を実行する
		void runFunc();

		// コンテナを更新する
		void updateContainer();

		// 引数のクラスのポインタを各関数実行コンテナに追加する
		template<class T>
		void addClass(bool isStatic, ProcessingClassPtr addClass);

		// 指定した関数実行コンテナの関数実行フラグを設定する
		template<int ContainerNum>
		void setIsRunFunc(bool flag);

		// 全ての関数実行コンテナの関数実行フラグを設定する
		void setIsRunFuncAll(bool flag);

		// 指定した関数実行コンテナのポインタを取得
		template<int ContainerNum, class RunFuncContainer>
		RunFuncContainer* getRunFuncContainerPtr();

	private:

		// 関数を実行する処理の実装
		template <int N, class Thead, class... Tbody>
		void runFuncImpl();

		// 関数を実行する処理の実装
		template <int N>
		void runFuncImpl();

		// コンテナを更新する処理の実装
		template <int N, class Thead, class... Tbody>
		void updateContainerImpl();

		// コンテナを更新する処理の実装
		template <int N>
		void updateContainerImpl();

		// クラスを追加する処理の実装
		template <int N, class T, class Thead, class... Tbody>
		void addClassImpl(bool isStatic, ProcessingClassPtr addClass);

		// クラスを追加する処理の実装
		template <int N, class T>
		void addClassImpl(bool isStatic, ProcessingClassPtr addClass);

		// 関数実行フラグを設定する処理の実装
		template <int N, class Thead, class... Tbody>
		void setIsRunFuncAllImpl(bool flag);

		// 関数実行フラグを設定する処理の実装
		template <int N>
		void setIsRunFuncAllImpl(bool flag);

	private:

		// 各関数ごとの関数実行コンテナクラス
		std::tuple<RunFuncContainers...> m_runFuncContainers;

		// 自動で実行する関数の数
		unsigned int m_autoRunFuncCount;
	};

	// 引数に自動で実行する関数の数を指定する
	template<class ...RunFuncContainers>
	inline RunFuncManager<RunFuncContainers...>::RunFuncManager(unsigned int autoRunFuncCount)
		: m_autoRunFuncCount(autoRunFuncCount)
	{
	}

	// 関数を実行する
	template<class ...RunFuncContainers>
	inline void RunFuncManager<RunFuncContainers...>::runFunc()
	{
		if (m_autoRunFuncCount == 0U) return;
		runFuncImpl<0, RunFuncContainers...>();
	}

	// コンテナを更新する
	template<class ...RunFuncContainers>
	inline void RunFuncManager<RunFuncContainers...>::updateContainer()
	{
		updateContainerImpl<0, RunFuncContainers...>();
	}

	// 引数のクラスのポインタを各関数実行コンテナに追加する
	template<class ...RunFuncContainers>
	template<class T>
	inline void RunFuncManager<RunFuncContainers...>::addClass(bool isStatic, ProcessingClassPtr addClass)
	{
		addClassImpl<0, T, RunFuncContainers...>(isStatic, addClass);
	}

	// 指定した関数実行コンテナの関数実行フラグを設定する
	template<class ...RunFuncContainers>
	template<int ContainerNum>
	inline void RunFuncManager<RunFuncContainers...>::setIsRunFunc(bool flag)
	{
		std::get<ContainerNum>(m_runFuncContainers).setIsRunFunc(flag);
	}

	// 全ての関数実行コンテナの関数実行フラグを設定する
	template<class ...RunFuncContainers>
	inline void RunFuncManager<RunFuncContainers...>::setIsRunFuncAll(bool flag)
	{
		setIsRunFuncAllImpl<0, RunFuncContainers...>(flag);
	}

	// 指定した関数実行コンテナのポインタを取得
	template<class ...RunFuncContainers>
	template<int ContainerNum, class RunFuncContainer>
	inline RunFuncContainer * RunFuncManager<RunFuncContainers...>::getRunFuncContainerPtr()
	{
		return &(std::get<ContainerNum>(m_runFuncContainers));
	}

	// 関数を実行する処理の実装
	template<class ...RunFuncContainers>
	template <int N, class Thead, class... Tbody>
	inline void RunFuncManager<RunFuncContainers...>::runFuncImpl()
	{
		runFunc_runner<>::checkAndRun(&std::get<N>(m_runFuncContainers));
		if (static_cast<unsigned int>(N + 1) >= m_autoRunFuncCount) return;
		runFuncImpl<N + 1, Tbody...>();
	}

	// 関数を実行する処理の実装
	template<class ...RunFuncContainers>
	template <int N>
	inline void RunFuncManager<RunFuncContainers...>::runFuncImpl()
	{
		/* not value */
	}

	// コンテナを更新する処理の実装
	template<class ...RunFuncContainers>
	template<int N, class Thead, class ...Tbody>
	inline void RunFuncManager<RunFuncContainers...>::updateContainerImpl()
	{
		updateContainer_runner<>::checkAndRun(&std::get<N>(m_runFuncContainers));
		updateContainerImpl<N + 1, Tbody...>();
	}

	// コンテナを更新する処理の実装
	template<class ...RunFuncContainers>
	template<int N>
	inline void RunFuncManager<RunFuncContainers...>::updateContainerImpl()
	{
		/* not value */
	}

	// クラスを追加する処理の実装
	template<class ...RunFuncContainers>
	template<int N, class T, class Thead, class ...Tbody>
	inline void RunFuncManager<RunFuncContainers...>::addClassImpl(bool isStatic, ProcessingClassPtr addClass)
	{
		checkAndAdd_runner<bool, const ProcessingClassPtr &, T*>::checkAndRun(&std::get<N>(m_runFuncContainers), isStatic, addClass, nullptr);
		addClassImpl<N + 1, T, Tbody...>(isStatic, addClass);
	}

	// クラスを追加する処理の実装
	template<class ...RunFuncContainers>
	template<int N, class T>
	inline void RunFuncManager<RunFuncContainers...>::addClassImpl(bool isStatic, ProcessingClassPtr addClass)
	{
		/* not value */
	}

	// 関数実行フラグを設定する処理の実装
	template<class ...RunFuncContainers>
	template<int N, class Thead, class ...Tbody>
	inline void RunFuncManager<RunFuncContainers...>::setIsRunFuncAllImpl(bool flag)
	{
		setIsRunFunc_runner<bool>::checkAndRun(&std::get<N>(m_runFuncContainers), flag);
		setIsRunFuncAllImpl<N + 1, Tbody...>(flag);
	}

	// 関数実行フラグを設定する処理の実装
	template<class ...RunFuncContainers>
	template<int N>
	inline void RunFuncManager<RunFuncContainers...>::setIsRunFuncAllImpl(bool flag)
	{
		/* not value */
	}
}
#endif // !RUN_FUNC_MANAGER_H_