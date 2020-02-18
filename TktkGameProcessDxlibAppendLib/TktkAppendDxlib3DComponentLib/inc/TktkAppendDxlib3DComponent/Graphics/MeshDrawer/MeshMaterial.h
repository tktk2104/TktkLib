#ifndef MESH_MATERIAL_H_
#define MESH_MATERIAL_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibShader3DParam.h"
#include "../../../TktkDxlib3DWrapper/Graphics/ShaderType.h"
#include "../../../TktkDxlib3DWrapper/Graphics/ShaderUseTextureAddressType.h"

namespace tktk
{
	class MeshMaterial
		: public tktk::ComponentBase
	{
	public:

		MeshMaterial(
			const DxLibShader3DParam& dxLibShader3DParam
		);

	public:

		// DxLibでシェーダーを使用する時のパラメーターを取得
		const DxLibShader3DParam& getDxLibShader3DParam() const;

		// 自作のシェーダーを使用する
		void useOrigShader(int pixelShaderId, int vertexShaderId);
		// デフォルトのシェーダーを使用する
		void unUseOrigShader();
		// シェーダーで使用する定数バッファをクリアする
		void clearShaderUseConstantBuffer();
		// シェーダーで使用する定数バッファを設定する
		void setShaderUseConstantBuffer(int slot, ShaderType targetShaderType, int shaderConstantBufferId);
		// シェーダーで使用する画像データをクリアする
		void clearShaderUseGraphHandleMap();
		// シェーダーで使用するテクスチャを設定する
		void addShaderUsedTexture(int stageIndex, int textureId, ShaderUseTextureAddressType addressType);
		// シェーダーで使用するモデルテクスチャを設定する
		void addShaderUsedModelTexture(int stageIndex, int modelTextureId, ShaderUseTextureAddressType addressType);
		// シェーダーで使用するレンダーターゲットの描画結果を設定する
		void addShaderUsedRenderTarget(int stageIndex, int renderTargetId, ShaderUseTextureAddressType addressType);

	private:

		// DxLibでシェーダーを使用する時のパラメーター
		DxLibShader3DParam m_dxLibShader3DParam{};
	};
}
#endif // !MESH_MATERIAL_H_
