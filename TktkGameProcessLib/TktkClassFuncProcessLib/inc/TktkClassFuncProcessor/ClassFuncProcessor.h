#ifndef CLASS_FUNC_PROCESSOR_H_
#define CLASS_FUNC_PROCESSOR_H_

#include "ProcessingClass/ProcessingSimpleContainer.h"
#include "RunFuncManager/RunFuncManager.h"
#include "ProcessingClass/CfpPtr.h"

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasAwakeChecker.h>

namespace tktk
{
	// クラスのインスタンスを管理する機能の総合インターフェース
	template <class... RunFuncContainers>
	class ClassFuncProcessor
	{
	public:

		// 引数に自動で実行する関数の数を指定する
		ClassFuncProcessor(unsigned int autoRunFuncCount);
		~ClassFuncProcessor() {};

		ClassFuncProcessor(const ClassFuncProcessor& other) = delete;
		ClassFuncProcessor& operator = (const ClassFuncProcessor& other) = delete;

	public:

		// 新たなクラスを次のprocessing()実行時に追加
		// ※isStaticをtrueにすると動作は軽くなるが、追加時と削除時が重たい
		template <class T>
		CfpPtr<T> addClass(bool isStatic, T* rawPtr);

		// 追加したいクラスを作成した上で次のprocessing()実行時に追加
		// ※isStaticをtrueにすると動作は軽くなるが、追加時と削除時が重たい
		template <class T, class... Args>
		CfpPtr<T> createClass(bool isStatic, const Args&... constructorValue);

		// 指定した関数実行コンテナの関数実行フラグを設定する
		template<int ContainerNum>
		void setIsRunFunc(bool flag);

		// 全ての関数実行コンテナの関数実行フラグを設定する
		void setIsRunFuncAll(bool flag);

		// 指定した関数実行コンテナのポインタを取得
		template<int ContainerNum, class RunFuncContainer>
		RunFuncContainer* getRunFuncContainerPtr();

	public:

		// 処理を行う
		void processing();

		// 後始末
		void finalize();

	private:

		ProcessingSimpleContainer m_processingSimpleContainer;
		RunFuncManager<RunFuncContainers...> m_runFuncManager;
	};

	// 引数に自動で実行する関数の数を指定する
	template<class ...RunFuncContainers>
	inline ClassFuncProcessor<RunFuncContainers...>::ClassFuncProcessor(unsigned int autoRunFuncCount)
		: m_runFuncManager({ autoRunFuncCount })
	{
	}

	// 新たなクラスを次のprocessing()実行時に追加
	// ※isStaticをtrueにすると動作は軽くなるが、追加時と削除時が重たい
	template<class ...RunFuncContainers>
	template<class T>
	inline CfpPtr<T> ClassFuncProcessor<RunFuncContainers...>::addClass(bool isStatic, T * rawPtr)
	{
		ProcessingClassPtr newClass = m_processingSimpleContainer.addClass(isStatic, rawPtr);
		m_runFuncManager.addClass<T>(isStatic, newClass);
		awake_runner<void>::checkAndRun(rawPtr);
		return CfpPtr<T>(newClass);
	}

	// 追加したいクラスを作成した上で次のprocessing()実行時に追加
	// ※isStaticをtrueにすると動作は軽くなるが、追加時と削除時が重たい
	template<class ...RunFuncContainers>
	template<class T, class ...Args>
	inline CfpPtr<T> ClassFuncProcessor<RunFuncContainers...>::createClass(bool isStatic, const Args & ...constructorValue)
	{
		return addClass<T>(isStatic, new T(constructorValue...));
	}

	// 指定した関数実行コンテナの関数実行フラグを設定する
	template<class ...RunFuncContainers>
	template<int ContainerNum>
	inline void ClassFuncProcessor<RunFuncContainers...>::setIsRunFunc(bool flag)
	{
		m_runFuncManager.setIsRunFunc<ContainerNum>(flag);
	}

	// 全ての関数実行コンテナの関数実行フラグを設定する
	template<class ...RunFuncContainers>
	inline void ClassFuncProcessor<RunFuncContainers...>::setIsRunFuncAll(bool flag)
	{
		m_runFuncManager.setIsRunFuncAll(flag);
	}

	// 指定した関数実行コンテナのポインタを取得
	template<class ...RunFuncContainers>
	template<int ContainerNum, class RunFuncContainer>
	inline RunFuncContainer * ClassFuncProcessor<RunFuncContainers...>::getRunFuncContainerPtr()
	{
		return m_runFuncManager.getRunFuncContainerPtr<ContainerNum, RunFuncContainer>();
	}

	// 処理を行う
	template<class ...RunFuncContainers>
	inline void ClassFuncProcessor<RunFuncContainers...>::processing()
	{
		m_processingSimpleContainer.updateContainer();
		m_runFuncManager.updateContainer();
		m_runFuncManager.runFunc();
	}

	// 後始末
	template<class ...RunFuncContainers>
	inline void ClassFuncProcessor<RunFuncContainers...>::finalize()
	{
		m_processingSimpleContainer.deleteAll();
	}
}
#endif // !CLASS_FUNC_PROCESSOR_H_