#ifndef MESH_DRAWER_SETUPPER_H_
#define MESH_DRAWER_SETUPPER_H_

#include <string>

namespace tktk
{
	// メッシュを描画するための前準備を行うクラス
	class MeshDrawerSetupper
	{
	public:

		static void setUp(
			const std::string& basicPixelShaderFileName,
			const std::string& basicVertexShaderFileName,
			const std::string& monoColorMeshPixelShaderFileName,
			const std::string& monoColorMeshVertexShaderFileName,
			const std::string& pbrPixelShaderFileName,
			const std::string& pbrVertexShaderFileName,
			const std::string& iblMeshPixelShaderFileName,
			const std::string& iblMeshVertexShaderFileName,
			const std::string& pbrIblPixelShaderFileName,
			const std::string& pbrIblVertexShaderFileName
		);
	};
}
#endif // !MESH_DRAWER_SETUPPER_H_
