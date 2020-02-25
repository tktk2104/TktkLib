#ifndef CFP_PTR_H_
#define CFP_PTR_H_

#include <stdexcept>
#include "ProcessingClassPtr.h"

namespace tktk
{
	// このフレームワークを使う上で使用するポインタクラス
	template <class T>
	class CfpPtr
	{
	public:

		// デフォルトコンストラクタでnullptrとして作成される
		CfpPtr() = default;
		explicit CfpPtr(ProcessingClassPtr processingClassPtr);

		~CfpPtr() {}

	public:

		// 自身のポインタが死んでいたらnullptrが返る
		T* operator ->() const;

		// お互いのポインタが同じ番地を指していたらtrueが返る
		// お互いにポインタが死んでいたらtrueが返り、片方のポインタが死んでいたらfalseが返る
		bool operator ==(CfpPtr other) const;

		// お互いのポインタが同じ番地を指していたらfalseが返る
		// お互いにポインタが死んでいたらfalseが返り、片方のポインタが死んでいたらtrueが返る
		bool operator !=(CfpPtr other) const;

		// 自身のポインタが死んでいないかを判定する
		bool isNull() const;

		// このフレームワークでのインスタンスの共通規格を取得
		ProcessingClassPtr processingClassPtr() const;

	private:

		ProcessingClassPtr m_processingClassPtr;
	};

	template<class T>
	inline CfpPtr<T>::CfpPtr(ProcessingClassPtr processingClassPtr)
		: m_processingClassPtr(processingClassPtr)
	{
	}

	// 自身のポインタが死んでいたらnullptrが返る
	template<class T>
	inline T * CfpPtr<T>::operator->() const
	{
		if (m_processingClassPtr.isNull()) return nullptr;
		return m_processingClassPtr->castPtr<T>();
	}

	// お互いのポインタが同じ番地を指していたらtrueが返る
	// お互いにポインタが死んでいたらtrueが返り、片方のポインタが死んでいたらfalseが返る
	template<class T>
	inline bool CfpPtr<T>::operator==(CfpPtr other) const
	{
		if (m_processingClassPtr.isNull() && other.m_processingClassPtr.isNull()) return true;
		if (m_processingClassPtr.isNull() || other.m_processingClassPtr.isNull()) return false;
		return m_processingClassPtr->isSame(other.m_processingClassPtr->voidPtr());
	}

	// お互いのポインタが同じ番地を指していたらfalseが返る
	// お互いにポインタが死んでいたらfalseが返り、片方のポインタが死んでいたらtrueが返る
	template<class T>
	inline bool CfpPtr<T>::operator!=(CfpPtr other) const
	{
		return !(*this == other);
	}

	// ポインタが死んでいないかを判定する
	template<class T>
	inline bool CfpPtr<T>::isNull() const
	{
		return m_processingClassPtr.isNull();
	}

	// このフレームワークでのインスタンスの共通規格を取得
	template<class T>
	inline ProcessingClassPtr CfpPtr<T>::processingClassPtr() const
	{
		return m_processingClassPtr;
	}
}
#endif // !CFP_PTR_H_