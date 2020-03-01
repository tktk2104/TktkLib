#ifndef PIXEL_SHADER_H_
#define PIXEL_SHADER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/PixelShaderData.h"
#include "Asset/SystemPixelShaderId.h"

namespace tktk
{
	// 「PixelShaderManager」の実装の一部を隠すためのクラス
	class PixelShader
	{
	public:

		// 新たなピクセルシェーダーをロードする
		// ※この関数でシェーダーをロードする場合、idは1以上でなければならない
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), static_cast<int>(useConstantBufferId), fileName);
		}
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<!is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName) { static_assert(false, "Id Fraud Type"); }

		// 指定したピクセルシェーダーを削除する
		// ※この関数でシェーダーを削除する場合、idは1以上でなければならない
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

	private:

		// 各種id指定系の関数の実装
		static void loadImpl(int id, int useConstantBufferId, const std::string& fileName);
		static void eraseImpl(int id);
		static const PixelShaderData& getDataImpl(int id);
	};
}
#endif // !PIXEL_SHADER_H_
