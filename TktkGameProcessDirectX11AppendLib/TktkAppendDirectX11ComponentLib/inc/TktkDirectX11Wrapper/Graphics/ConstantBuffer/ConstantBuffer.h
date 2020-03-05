#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/ConstantBufferData.h"
#include "Asset/SystemConstantBufferId.h"

namespace tktk
{
	// 「ConstantBufferManager」の実装の一部を隠すためのクラス
	class ConstantBuffer
	{
	public:

		// 新たな定数バッファを作成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でバッファを作る場合、idは1以上でなければならない
		template<class IdType, class BufferDataType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, BufferDataType* data)
		{
			createImpl(static_cast<int>(id), SafetyVoidPtr(data));
		}
		template<class IdType, class BufferDataType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, BufferDataType* data) { static_assert(false, "ConstantBufferId Fraud Type"); }

		// 指定した定数バッファを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でバッファを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "ConstantBufferId Fraud Type"); }

		// 指定した定数バッファを管理するクラスのポインタを取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static ConstantBufferData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static ConstantBufferData* getDataPtr(IdType id) { static_assert(false, "ConstantBufferId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, SafetyVoidPtr&& data);
		static void eraseImpl(int id);
		static ConstantBufferData* getDataPtrImpl(int id);
	};
}
#endif // !CONSTANT_BUFFER_H_