#ifndef VERTEX_SHADER_MANAGER_H_
#define VERTEX_SHADER_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/VertexShaderAssets.h"
#include "Asset/SystemVertexShaderId.h"

namespace tktk
{
	// 「VertexShaderAssets」に簡単にアクセスするためのクラス
	class VertexShaderManager
	{
	public:

		// 「VertexShaderAssets」を生成
		static void setUp();

	public:

		// 新たな頂点シェーダーをロードする
		static void load(
			int id,
			int useConstantBufferId,
			const std::string& fileName,
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
		);

		// 指定した頂点シェーダーを削除する
		static void erase(int id);

		// 全ての頂点シェーダーを削除する
		static void clear();

		// 指定した頂点シェーダーを管理するクラスの参照を取得する
		static const VertexShaderData& getData(int id);

	private:

		static CfpPtr<VertexShaderAssets> m_assetsPtr;
	};
}
#endif // !VERTEX_SHADER_MANAGER_H_
