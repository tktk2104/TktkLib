#ifndef PIXEL_SHADER_MANAGER_H_
#define PIXEL_SHADER_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/PixelShaderAssets.h"
#include "Asset/SystemPixelShaderId.h"

namespace tktk
{
	// 「PixelShaderAssets」に簡単にアクセスするためのクラス
	class PixelShaderManager
	{
	public:

		// 「PixelShaderAssets」を生成
		static void setUp();

	public:

		// 新たなピクセルシェーダーをロードする（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), static_cast<int>(useConstantBufferId), fileName);
		}
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<!is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName) { static_assert(false, "Id Fraud Type"); }

		// 指定したピクセルシェーダーを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "PixelShaderId Fraud Type"); }

		// 指定したピクセルシェーダーを管理するクラスの参照を取得する
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const PixelShaderData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const PixelShaderData& getData(IdType id) { static_assert(false, "PixelShaderId Fraud Type"); }

		// 全てのピクセルシェーダーを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void loadImpl(int id, int useConstantBufferId, const std::string& fileName);
		static void eraseImpl(int id);
		static const PixelShaderData& getDataImpl(int id);

	private:

		static CfpPtr<PixelShaderAssets> m_assetsPtr;
	};
}
#endif // !PIXEL_SHADER_MANAGER_H_