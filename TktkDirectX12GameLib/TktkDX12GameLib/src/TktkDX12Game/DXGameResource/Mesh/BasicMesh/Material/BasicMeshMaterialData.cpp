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
		// �f�B�X�N���v�^�q�[�v�����
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// �A���x�h�}�b�v�ƃV���h�E�}�b�v�̂Q���
			srvDescriptorParam.descriptorParamArray = {
				{ BufferType::texture,		initParam.useAlbedoMapTextureId											},
				{ BufferType::depthStencil, DX12GameManager::getSystemId(SystemDepthStencilBufferType::ShadowMap)	}
			};
		}

		{ /* ���_�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// 
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::MeshTransform)		},
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BoneMatCbuffer)		},
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::Light)		},
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshMaterial)	},
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::MeshShadowMap)		}
			};
		}

		{ /* �s�N�Z���V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// 
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::Light)		},
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshMaterial)	}
			};
		}
		DX12GameManager::createBasicDescriptorHeap(m_createDescriptorHeapId, descriptorHeapInitParam);
	}

	void BasicMeshMaterialData::setMaterialData()
	{
		// �}�e���A���̏���萔�o�b�t�@�ɏ�������
		{
			BasicMeshMaterialCbuffer materialBufferData{};

			materialBufferData.materialAmbient = m_materialAmbient;
			materialBufferData.materialDiffuse = m_materialDiffuse;
			materialBufferData.materialSpecular = m_materialSpecular;
			materialBufferData.materialEmissive = m_materialEmissive;
			materialBufferData.materialShiniess = m_materialShiniess;

			DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemConstantBufferType::BasicMeshMaterial), materialBufferData);
		}

		// �ʏ탁�b�V���p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapId } });
	}
}