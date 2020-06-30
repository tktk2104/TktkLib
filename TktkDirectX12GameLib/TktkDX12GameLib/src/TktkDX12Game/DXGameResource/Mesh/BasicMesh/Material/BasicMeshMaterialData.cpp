#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/BasicMeshMaterialCbuffer.h"

namespace tktk
{
	BasicMeshMaterialData::BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam)
		: m_createDescriptorHeapId(initParam.createDescriptorHeapId)
		, m_materialAmbient(initParam.materialAmbient)
		, m_materialDiffuse(initParam.materialDiffuse)
		, m_materialSpecular(initParam.materialSpecular)
		, m_materialEmissive(initParam.materialEmissive)
		, m_materialShiniess(initParam.materialShiniess)
	{
		// ディスクリプタヒープを作る
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

		{ /* シェーダーリソースビューのディスクリプタの情報 */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// アルベドマップとシャドウマップの２種類
			srvDescriptorParam.descriptorParamArray = {
				{ BufferType::texture,		initParam.useAlbedoMapTextureId											},
				{ BufferType::depthStencil, DX12GameManager::getSystemId(SystemDepthStencilBufferType::ShadowMap)	}
			};
		}

		{ /* 頂点シェーダー用のコンスタントバッファービューのディスクリプタの情報 */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// 
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::MeshTransform)		},
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BoneMatCbuffer)		},
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshLight)		},
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshMaterial)	}
			};
		}

		{ /* ピクセルシェーダー用のコンスタントバッファービューのディスクリプタの情報 */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// 
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshLight)		},
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshMaterial)	}
			};
		}
		DX12GameManager::createBasicDescriptorHeap(m_createDescriptorHeapId, descriptorHeapInitParam);
	}

	void BasicMeshMaterialData::setMaterialData()
	{
		// マテリアルの情報を定数バッファに書き込む
		{
			BasicMeshMaterialCbuffer materialBufferData{};

			materialBufferData.materialAmbient = m_materialAmbient;
			materialBufferData.materialDiffuse = m_materialDiffuse;
			materialBufferData.materialSpecular = m_materialSpecular;
			materialBufferData.materialEmissive = m_materialEmissive;
			materialBufferData.materialShiniess = m_materialShiniess;

			DX12GameManager::updateConstantBuffer(DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshMaterial), materialBufferData);
		}

		// 通常メッシュ用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapId } });
	}
}