#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"

#include <TktkFileIo/lodepmd.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	// �X�P���g�������
	inline void craeteSkeleton(unsigned int createSkeletonId, const std::vector<lodepmd::loadData::OutBone>& boneData);

	// �ǂݍ��݊֐�
	BasicMeshLoadPmdReturnValue BasicMeshPmdLoader::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		// pmd�t�@�C���̃��[�h�����̏o�͕ϐ�
		lodepmd::loadData outData{};

		// ���[�h���s��
		lodepmd::load(&outData, args.filePath);

		// ���_�o�b�t�@�����
		DX12GameManager::createVertexBuffer(args.createVertexBufferId, outData.vertexData);

		// �C���f�b�N�X�o�b�t�@�����
		DX12GameManager::createIndexBuffer(args.createIndexBufferId, outData.indexData);

		// �ʏ탁�b�V���̍쐬�ɕK�v�ȏ��
		BasicMeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferId = args.createVertexBufferId;
		meshInitParam.useIndexBufferId = args.createIndexBufferId;
		meshInitParam.indexNum = outData.indexData.size();
		meshInitParam.primitiveTopology = MeshPrimitiveTopology::TriangleList;
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		// �A�Ԃ�ID�ō쐬���郊�\�[�X�̎��Ɏg�p����ID�̒l
		unsigned int curDescriptorHeapId	= args.createDescriptorHeapIdStartNum;
		unsigned int curTextureId			= args.createTextureIdStartNum;
		unsigned int curMaterialId			= args.createBasicMeshMaterialIdStartNum;

		// ���݂̃C���f�b�N�X�i�C���f�b�N�X�o�b�t�@�̈ʒu�j
		unsigned int curIndex				= 0U;

		// �}�e���A���̐��������[�v
		for (unsigned int i = 0; i < outData.materialData.size(); i++)
		{
			// �}�e���A���̍쐬�ɕK�v�ȏ��
			BasicMeshMaterialInitParam materialParam{};

			// �f�t�H���g�̃p�C�v���C���X�e�[�g���g��
			materialParam.usePipeLineStateId = DX12GameManager::getSystemId(SystemPipeLineStateType::BasicMesh);

			// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă�����
			if (outData.materialData.at(i).textureFilePath != "")
			{
				// �e�N�X�`����ǂݍ���
				DX12GameManager::cpuPriorityLoadTextureBuffer(curTextureId, outData.materialData.at(i).textureFilePath);
			}
			// �e�N�X�`�����ݒ肳��Ă��Ȃ�������
			else
			{
				// �ŏ��̑傫���̊����̐F�̃e�N�X�`�����쐬����

				TexBufFormatParam formatParam{};
				formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
				formatParam.arraySize = 1U;
				formatParam.mipLevels = 1U;
				formatParam.sampleDescCount = 1U;
				formatParam.sampleDescQuality = 0U;

				TexBuffData dataParam{};

				for (unsigned int j = 0; j < 16; j++)
				{
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.r));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.g));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.b));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.a));
				}

				dataParam.width = 4U;
				dataParam.height = 4U;

				// �e�N�X�`��������������̂ŃR�}���h���X�g
				DX12GameManager::cpuPriorityCreateTextureBuffer(curTextureId, formatParam, dataParam);
			}

			materialParam.materialAmbient	= { 0.3f, 1.0f }; // ���}�e���A���̊����̒l�͒萔�l��ݒ肷��
			materialParam.materialDiffuse	= outData.materialData.at(i).diffuse;
			materialParam.materialSpecular	= outData.materialData.at(i).speqular;
			materialParam.materialEmissive	= outData.materialData.at(i).emissive;
			materialParam.materialShiniess	= outData.materialData.at(i).shiniess;

			materialParam.useDescriptorHeapId = curDescriptorHeapId;

			// �f�B�X�N���v�^�q�[�v�����
			{
				BasicDescriptorHeapInitParam descriptorHeapInitParam{};
				descriptorHeapInitParam.shaderVisible = true;
				descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

				{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
					auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
					srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

					// �A���x�h�}�b�v�ƃV���h�E�}�b�v�̂Q���
					srvDescriptorParam.descriptorParamArray = {
						{ BufferType::texture,		curTextureId												},
						{ BufferType::depthStencil, DX12GameManager::getSystemId(SystemDsBufferType::ShadowMap)	}
					};
				}

				{ /* ���_�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// 
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::MeshTransform)		},
						{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::BoneMatCbuffer)		},
						{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::Light)				},
						{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::BasicMeshMaterial)	},
						{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::MeshShadowMap)		}
					};
				}

				{ /* �s�N�Z���V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// 
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::Light)		},
						{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::BasicMeshMaterial)	}
					};
				}
				DX12GameManager::createBasicDescriptorHeap(materialParam.useDescriptorHeapId, descriptorHeapInitParam);
			}

			// �ʏ탁�b�V���̃}�e���A�������
			DX12GameManager::createBasicMeshMaterial(curMaterialId, materialParam);

			// �ʏ탁�b�V���̃T�u�Z�b�g�����X�V
			meshInitParam.materialSlots.push_back({ curMaterialId, curIndex, outData.materialData.at(i).indexCount });

			// �e��A��ID���C���N�������g
			curDescriptorHeapId++;
			curMaterialId++;
			curTextureId++;

			// ���݂̃C���f�b�N�X�����Z
			curIndex += outData.materialData.at(i).indexCount;
		}
		DX12GameManager::createBasicMesh(args.createBasicMeshId, meshInitParam);

		// �X�P���g�������
		craeteSkeleton(args.createSkeletonId, outData.boneData);

		// �A�Ԃ�ID�ō쐬�������\�[�X�̍Ō��ID�̒l��Ԃ�
		return { curDescriptorHeapId--, curMaterialId--, curTextureId-- };
	}

	// �X�P���g�������
	void craeteSkeleton(unsigned int createSkeletonId, const std::vector<lodepmd::loadData::OutBone>& boneData)
	{
		// �����̍쐬�ɕK�v�ȏ��
		SkeletonInitParam skeletonInitParam{};
		skeletonInitParam.boneDataArray.reserve(boneData.size());

		for (const auto& node : boneData)
		{
			skeletonInitParam.boneDataArray.push_back({ node.name, node.parentNo, node.pos });
		}

		// �X�P���g�����쐬����
		DX12GameManager::createSkeleton(createSkeletonId, skeletonInitParam);
	}
}