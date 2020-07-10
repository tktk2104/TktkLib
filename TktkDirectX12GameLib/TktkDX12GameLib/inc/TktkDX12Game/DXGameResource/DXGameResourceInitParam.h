#ifndef DX_GAME_RESOURCE_INIT_PARAM_H_
#define DX_GAME_RESOURCE_INIT_PARAM_H_

#include <TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "PostEffect/PostEffectShaderFilePaths.h"

namespace tktk
{
	// ゲームで使用するリソース管理クラスを作る時に必要な情報
	struct DXGameResourceInitParam
	{
		// スプライトシェーダーのファイルパス
		tktk::ShaderFilePaths		spriteShaderFilePaths		{};

		// 通常メッシュシェーダーのファイルパス
		tktk::ShaderFilePaths		basicMeshShaderFilePaths	{};

		// シャドウマップシェーダーのファイルパス
		std::string					writeShadowMapVsFilePath	{};

		// ポストエフェクトシェーダーのファイルパス
		PostEffectShaderFilePaths	postEffectShaderFilePaths	{};

		// スプライトマテリアル数
		unsigned int spriteNum				{};

		// 通常メッシュ数
		unsigned int basicMeshNum			{};

		// 通常メッシュマテリアル数
		unsigned int basicMeshMaterialNum	{};

		// モーションデータ数
		unsigned int motionNum				{};

		// スケルトンデータ数
		unsigned int skeletonNum			{};

		// ポストエフェクトマテリアル数
		unsigned int postEffectMaterialNum	{};
	};
}
#endif // !DX_GAME_RESOURCE_INIT_PARAM_H_