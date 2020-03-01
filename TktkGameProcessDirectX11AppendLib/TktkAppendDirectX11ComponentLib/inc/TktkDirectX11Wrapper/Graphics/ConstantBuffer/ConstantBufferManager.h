#ifndef CONSTANT_BUFFER_MANAGER_H_
#define CONSTANT_BUFFER_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/ConstantBufferAssets.h"
#include "Asset/SystemConstantBufferId.h"
#include "Asset/SystemConstantBufferParamLocationType.h"

namespace tktk
{
	// 「ConstantBufferAssets」に簡単にアクセスするためのクラス
	class ConstantBufferManager
	{
	public:

		// 「ConstantBufferAssets」を作成
		static void setUp();

	public:

		// 新たな定数バッファを作成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, class BufferDataType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, BufferDataType* data)
		{
			createImpl(static_cast<int>(id), SafetyVoidPtr(data));
		}
		template<class IdType, class BufferDataType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, BufferDataType* data) { static_assert(false, "ConstantBufferId Fraud Type"); }

		// 指定した定数バッファを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
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

		// 指定した定数バッファに入れる予定のデータの特定の値にアクセスするための設定を行う（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, class LocationType, std::enable_if_t<(is_idType_v<IdType> && is_idType_v<LocationType>)>* = nullptr>
		static void addParamLocation(IdType id, LocationType locationType, unsigned int locationFromBufferTop)
		{
			addParamLocationImpl(static_cast<int>(id), static_cast<int>(locationType), locationFromBufferTop);
		}
		template <class IdType, class LocationType, std::enable_if_t<!(is_idType_v<IdType> && is_idType_v<LocationType>)>* = nullptr>
		static void addParamLocation(IdType id, LocationType locationType, unsigned int locationFromBufferTop) { static_assert(false, "Id Fraud Type"); }

		// 全ての定数バッファを削除する
		static void clear();

		// 各種id指定系の関数の実装
		static void createImpl(int id, SafetyVoidPtr&& data);
	private:
		static void eraseImpl(int id);
		static ConstantBufferData* getDataPtrImpl(int id);
		static void addParamLocationImpl(int id, int locationType, unsigned int locationFromBufferTop);

	private:

		static CfpPtr<ConstantBufferAssets> m_assetsPtr;
	};
}
#endif // !CONSTANT_BUFFER_MANAGER_H_