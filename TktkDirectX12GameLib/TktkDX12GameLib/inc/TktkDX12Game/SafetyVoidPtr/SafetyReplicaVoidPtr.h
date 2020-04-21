#ifndef SAFETY_REPLICA_VOID_PTR_H_
#define SAFETY_REPLICA_VOID_PTR_H_

#ifdef _DEBUG
#include <stdexcept>
#endif
#include "SafetyVoidPtrVTable.h"

namespace tktk
{
	class SafetyOriginalVoidPtr;

	// 「SafetyOriginalVoidPtr」で管理するポインタをコピーして使うためのクラス
	class SafetyReplicaVoidPtr
	{
	public:

		// nullptrとして作成する
		SafetyReplicaVoidPtr();

		SafetyReplicaVoidPtr(const SafetyOriginalVoidPtr& original);

		// デストラクタでは何もしない
		~SafetyReplicaVoidPtr() = default;

	public:

		bool isNull();

		// 引数のポインタと自身の持つポインタが同じかどうかを判定する
		template<class T>
		bool isSame(T* other) const;

		// テンプレートパラメーターの型に自身の持つポインタをキャストできるかを判定する
		template<class T>
		bool canCast() const;

		// テンプレートパラメーターの型に自身のポインタをキャストする
		template<class T>
		T* castPtr() const;

		// 管理しているポインタの元の型番号を取得する
		unsigned int getClassId() const;

		// 管理しているポインタの元の型のサイズを取得する
		unsigned int getClassSize() const;

	private:

		void*					m_rawPtr;
		SafetyVoidPtrVTable*	m_vtablePtr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class T>
	inline bool SafetyReplicaVoidPtr::isSame(T* other) const
	{
		return (m_rawPtr == other);
	}

	template<class T>
	inline bool SafetyReplicaVoidPtr::canCast() const
	{
		return (m_vtablePtr->getTypeId() == ClassTypeChecker::getClassId<T>());
	}

	template<class T>
	inline T* SafetyReplicaVoidPtr::castPtr() const
	{
		if (isNull()) return nullptr;

#ifdef _DEBUG
		if (canCast<T>()) return reinterpret_cast<T*>(m_rawPtr);
		throw std::runtime_error("invalid cast");
#else
		return reinterpret_cast<T*>(m_rawPtr);
#endif // _DEBUG
	}
}
#endif // !SAFETY_REPLICA_VOID_PTR_H_