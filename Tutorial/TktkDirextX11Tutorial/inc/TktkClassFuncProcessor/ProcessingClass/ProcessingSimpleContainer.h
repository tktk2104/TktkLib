#ifndef PROCESSING_SIMPLE_CONTAINER_H_
#define PROCESSING_SIMPLE_CONTAINER_H_

#include <vector>
#include <forward_list>
#include "ProcessingClassPtr.h"

namespace tktk
{
	// このフレームワークのインスタンスを管理する大本のコンテナ
	class ProcessingSimpleContainer
	{
	public:

		ProcessingSimpleContainer() = default;
		~ProcessingSimpleContainer();

		// コピー禁止
		ProcessingSimpleContainer(const ProcessingSimpleContainer& other) = delete;
		ProcessingSimpleContainer& operator = (const ProcessingSimpleContainer& other) = delete;

	public:

		// 新たなクラスをaddClassListに追加する
		// isStaticをtrueにするとインスタンスが可変長配列で管理される
		template <class T>
		ProcessingClassPtr addClass(bool isStatic, T* rawPtr);

		// コンテナの要素を更新する
		void updateContainer();

		// 全てのクラスを削除する
		// ※削除する順番は制御できないので注意
		void deleteAll();

	private:

		// addClassListの要素をprocessingClassArrayかprocessingClassListに移動する
		void moveContainerNode();

		// 削除されたクラスのポインタをコンテナから削除する
		void removeDeleteClass();

	private:

		// 追加するクラスの情報
		struct AddClass
		{
			AddClass(ProcessingClassPtr arg1, bool arg2) 
				: processingClassPtr(arg1), isStatic(arg2){}

			ProcessingClassPtr processingClassPtr;
			bool isStatic{ true };
		};

	private:

		// 追加するクラスの一時保存リスト
		std::forward_list<AddClass> m_addClassList;
		// 追加する静的クラスの数
		unsigned int m_addStaticClassNum{ 0U };

		// 静的なインスタンスを管理する可変長配列
		std::vector<ProcessingClassPtr> m_processingClassArray;
		// 動的なインスタンスを管理する前方リスト
		std::forward_list<ProcessingClassPtr> m_processingClassList;
	};

	// 新たなクラスをaddClassListに追加する
	// isStaticをtrueにするとインスタンスが可変長配列で管理される
	template<class T>
	inline ProcessingClassPtr ProcessingSimpleContainer::addClass(bool isStatic, T * rawPtr)
	{
		if (isStatic) ++m_addStaticClassNum;
		ProcessingClassPtr newClass = ProcessingClassPtr(rawPtr);
		m_addClassList.emplace_front(newClass, isStatic);
		return newClass;
	}
}
#endif // !PROCESSING_SIMPLE_CONTAINER_H_