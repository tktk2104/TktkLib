#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include "Asset/VertexShaderData.h"
#include "Asset/SystemVertexShaderId.h"

namespace tktk
{
	// 「VertexShaderManager」の実装の一部を隠すためのクラス
	class VertexShader
	{
	public:

		// 新たな頂点シェーダーをロードする
		// ※この関数でシェーダーをロードする場合、idは1以上でなければならない
		static void load(
			int id,
			int useConstantBufferId,
			const std::string& fileName,
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
		);

		// 指定した頂点シェーダーを削除する
		// ※この関数でシェーダーを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定した頂点シェーダーを管理するクラスの参照を取得する
		static const VertexShaderData& getData(int id);
	};
}
#endif // !VERTEX_SHADER_H_