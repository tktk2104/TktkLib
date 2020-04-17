#ifndef SAFETY_VOID_PTR_H_
#define SAFETY_VOID_PTR_H_

#include "ClassTypeChecker.h"

namespace tktk
{
	// コンストラクタ引数のポインタを「voidPtr」として管理するクラス
	// このクラスのデストラクタが呼ばれる時、管理するポインタの元の型のデストラクタを呼ぶ
	class SafetyVoidPtr
	{
	public:

		// void*のnullptrとして作成する
		SafetyVoidPtr();

		template<class T>
		explicit SafetyVoidPtr(T* rawPtr);

		// デストラクタで自身のポインタを開放する
		~SafetyVoidPtr();

		// コピー禁止
		SafetyVoidPtr(const SafetyVoidPtr& other) = delete;
		SafetyVoidPtr& operator = (const SafetyVoidPtr& other) = delete;

		// ムーブコンストラクタ
		SafetyVoidPtr(SafetyVoidPtr&& other) noexcept;
		SafetyVoidPtr& operator = (SafetyVoidPtr&& other) noexcept;

	public:

		// 引数のポインタと自身の持つポインタが同じかどうかを判定する
		template<class T>
		bool isSame(T* other) const;

		// テンプレートパラメーターの型に自身の持つポインタをキャストできるかを判定する
		template<class T>
		bool canCast() const;

		// テンプレートパラメーターの型に自身のポインタをキャストする
		template<class T>
		T* castPtr() const;

		// voidPtrを取得する
		void* voidPtr() const;

		// 管理しているポインタの元の型番号を取得する
		unsigned int getClassId() const;

		// 管理しているポインタの元の型のサイズを取得する
		unsigned int getClassSize() const;

	private:

		// 自前のVTable
		struct VTable
		{
			unsigned int(*getTypeId)();
			unsigned int(*getTypeSize)();
			void(*runDestructor)(void**);
		};

		// 自前のVTableの実態がある所
		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;
			static unsigned int getTypeId();
			static unsigned int getTypeSize();
			static void runDestructor(void** self);
		};

	private:

		void* m_rawPtr;
		VTable* m_vtablePtr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class T>
	inline SafetyVoidPtr::SafetyVoidPtr(T* rawPtr)
		: m_rawPtr(rawPtr)
		, m_vtablePtr(&VTableInitializer<T>::m_vtable)
	{
	}

	// 引数のポインタと自身の持つポインタが同じかどうかを判定する
	template<class T>
	inline bool SafetyVoidPtr::isSame(T* other) const
	{
		return (m_rawPtr == other);
	}

	// テンプレートパラメーターの型に自身の持つポインタをキャストできるかを判定する
	template<class T>
	inline bool SafetyVoidPtr::canCast() const
	{
		return (m_vtablePtr->getTypeId() == ClassTypeChecker::getClassId<T>());
	}

	// テンプレートパラメーターの型に自身のポインタをキャストする
	template<class T>
	inline T* SafetyVoidPtr::castPtr() const
	{
		if (canCast<T>()) return reinterpret_cast<T*>(m_rawPtr);
		return nullptr;
	}

	template<class T>
	typename SafetyVoidPtr::VTable SafetyVoidPtr::VTableInitializer<T>::m_vtable =
	{
		&SafetyVoidPtr::VTableInitializer<T>::getTypeId,
		&SafetyVoidPtr::VTableInitializer<T>::getTypeSize,
		&SafetyVoidPtr::VTableInitializer<T>::runDestructor
	};

	// 自身のポインタの元の型情報番号を取得する
	template<class T>
	inline unsigned int SafetyVoidPtr::VTableInitializer<T>::getTypeId()
	{
		return ClassTypeChecker::getClassId<T>();
	}

	// 自身のポインタの元の型のサイズを取得する
	template<class T>
	inline unsigned int SafetyVoidPtr::VTableInitializer<T>::getTypeSize()
	{
		return sizeof(T);
	}

	// void型のサイズを取得しないようにするための物
	inline unsigned int SafetyVoidPtr::VTableInitializer<void>::getTypeSize() { return 0U; }

	// 自身のポインタを開放する
	template<class T>
	inline void SafetyVoidPtr::VTableInitializer<T>::runDestructor(void** self)
	{
		// 引数のポインタの実態（ポインタ）が既に「nullptr」だったら何もしない
		if (*self == nullptr) return;

		// ポインタの開放
		delete(reinterpret_cast<T*>(*self));

		// 引数のポインタを「nullptr」にする
		*self = nullptr;
	}
}
#endif // !SAFETY_VOID_PTR_H_