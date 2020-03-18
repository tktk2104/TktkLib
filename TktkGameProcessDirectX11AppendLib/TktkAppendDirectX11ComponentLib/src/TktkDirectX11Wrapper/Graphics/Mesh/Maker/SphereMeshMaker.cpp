#include "TktkDirectX11Wrapper/Graphics/Mesh/Maker/SphereMeshMaker.h"

#include <TktkMath/MathHelper.h>
#include <TktkMath/Vector3.h>
#include <vector>
#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshVertexBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Material/Material.h"
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Asset/SystemTexture2DId.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h"

namespace tktk
{
	void SphereMeshMaker::makeImpl(int meshId, int materialId)
	{
		int uMax = 24;
		int vMax = 12;

		std::vector<MeshVertexBufferData> vertices;
		vertices.resize(uMax * (vMax + 1));

		for (int v = 0; v <= vMax; v++)
		{
			for (int u = 0; u < uMax; u++)
			{
				MeshVertexBufferData tempVertexData;

				float x = MathHelper::sin(180.0f * v / vMax) * MathHelper::cos(360.0f * u / uMax);
				float y = MathHelper::cos(180.0f * v / vMax);
				float z = MathHelper::sin(180.0f * v / vMax) * MathHelper::sin(360.0f * u / uMax);

				tempVertexData.point = Vector3(x, y, z);
				tempVertexData.normal = Vector3(0.0f, 0.0f, 1.0f);

				tempVertexData.texcoord = Vector2(0.5f, 0.5f);

				Vector3::orthoNormalize(
					&tempVertexData.normal,
					&tempVertexData.tangent,
					&tempVertexData.binormal
				);

				tempVertexData.bones[0] = 0;
				tempVertexData.bones[1] = 0;
				tempVertexData.bones[2] = 0;
				tempVertexData.bones[3] = 0;

				tempVertexData.weight[0] = 1.0f;
				tempVertexData.weight[1] = 0.0f;
				tempVertexData.weight[2] = 0.0f;
				tempVertexData.weight[3] = 0.0f;

				vertices.at(uMax * v + u) = (tempVertexData);
			}
		}

		int i = 0;

		std::vector<unsigned int> indices;
		indices.resize(2 * vMax * (uMax + 1));

		for (int v = 0; v < vMax; v++)
		{
			for (int u = 0; u <= uMax; u++)
			{
				if (u == uMax)
				{
					indices.at(i) = v * uMax;
					i++;
					indices.at(i) = (v + 1) * uMax;
					i++;
				}
				else
				{
					indices.at(i) = (v * uMax) + u;
					i++;
					indices.at(i) = indices.at(i - 1) + uMax;
					i++;
				}
			}
		}

		// 頂点バッファを作る上で必要なパラメータ
		VertexBufferInitParams vertexBufferParams = { sizeof(MeshVertexBufferData), 0U, sizeof(MeshVertexBufferData) * vertices.size(), vertices.data() };

		// インデックスバッファを作る上で必要なパラメータ
		IndexBufferInitParams indexBufferParams = { indices };

		// マテリアルスロットを作る上で必要なパラメータ
		MaterialSlotsInitParams materialSlotsParams;
		materialSlotsParams.subsets.push_back({ 0, static_cast<int>(indices.size()) });

		// メッシュデータを作成
		Mesh::create(meshId, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, vertexBufferParams, indexBufferParams, materialSlotsParams);

		// マテリアルデータを生成
		Material::create(
			materialId,
			SystemVertexShaderId::MonoColorMesh,
			SystemPixelShaderId::MonoColorMesh,
			Color(0.3f, 0.3f, 0.3f, 1.0f),
			Color::white,
			Color::white,
			Color::white,
			10.0f,
			SystemTexture2DId::blueShaderRes
		);
	}
}