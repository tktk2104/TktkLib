#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/VertexShaderData.h"
#include "Asset/SystemVertexShaderId.h"

namespace tktk
{
	// 「VertexShaderManager」の実装の一部を隠すためのクラス
	class VertexShader
	{
	public:

		// 新たな頂点シェーダーをロードする（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でシェーダーをロードする場合、idは1以上でなければならない
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout)
		{
			loadImpl(static_cast<int>(id), static_cast<int>(useConstantBufferId), fileName, vertexLayout);
		}
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<!is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout)
		{ static_assert(false, "Id Fraud Type"); }

		// 指定した頂点シェーダーを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でシェーダーを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "VertexShaderId Fraud Type"); }

		// 指定した頂点シェーダーを管理するクラスの参照を取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const VertexShaderData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const VertexShaderData& getData(IdType id) { static_assert(false, "VertexShaderId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		static void loadImpl(int id, int useConstantBufferId, const std::string& fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout);
		static void eraseImpl(int id);
		static const VertexShaderData& getDataImpl(int id);
	};
}
#endif // !VERTEX_SHADER_H_