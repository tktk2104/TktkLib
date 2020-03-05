#include "TktkDirectX11Wrapper/Graphics/Mesh/Loader/FbxLoader/FbxLoader.h"

#include <filesystem>
#include <stdexcept>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h"
#include "TktkDirectX11Wrapper/Graphics/Material/Material.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/Asset/SystemVertexShaderId.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/Asset/SystemPixelShaderId.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Mesh.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/Loader/FbxLoader/FbxMeshLoader.h"

namespace tktk
{
	fbxsdk::FbxManager* FbxLoader::m_managerPtr{ nullptr };

	void FbxLoader::loadImpl(int meshId, const std::vector<int>& materialIdArray, const std::string & fileName)
	{
		fbxsdk::FbxScene* scenePtr;

		initSdkObjects(&scenePtr);

		int lFileFormat = -1;

		if (!m_managerPtr->GetIOPluginRegistry()->DetectReaderFileFormat(fileName.c_str(), lFileFormat))
		{
			lFileFormat = m_managerPtr->GetIOPluginRegistry()->FindReaderIDByDescription("FBX binary (*.fbx)");
		}

		// �C���|�[�^�[���쐬
		fbxsdk::FbxImporter* importerPtr = fbxsdk::FbxImporter::Create(m_managerPtr, "tktkFbxImporter");

		if (!importerPtr)
		{
			m_managerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}

		// �C���|�[�^�[�̏�����
		if (!importerPtr->Initialize(fileName.c_str(), -1, m_managerPtr->GetIOSettings()))
		{
			m_managerPtr->Destroy();
			importerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}

		// �V�[���ɃC���|�[�g����
		if (!importerPtr->Import(scenePtr))
		{
			m_managerPtr->Destroy();
			importerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}

		// �C���|�[�^�[���폜
		importerPtr->Destroy();

		// DirectX�̍��W�n�ɐݒ�
		if (scenePtr->GetGlobalSettings().GetAxisSystem() != fbxsdk::FbxAxisSystem::DirectX)
		{
			fbxsdk::FbxAxisSystem::DirectX.ConvertScene(scenePtr);
		}

		// ���W��Ԃ̒P�ʂ��Z���`���[�g���ɐݒ�
		if (scenePtr->GetGlobalSettings().GetSystemUnit().GetScaleFactor() != 1.0)
		{
			fbxsdk::FbxSystemUnit::cm.ConvertScene(scenePtr);
		}

		// �S�Ẵ|���S����3�p�`��
		fbxsdk::FbxGeometryConverter fbxGeometryConverter(m_managerPtr);
		fbxGeometryConverter.Triangulate(scenePtr, true);

		// �~�������̌^��錾
		FbxLoadDataParam loadDataParam;

		// ���[�g�m�[�h���擾
		fbxsdk::FbxNode* fbxNodePtr = scenePtr->GetRootNode();

		if (!fbxNodePtr)
		{
			m_managerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}

		// fbx�m�[�h�𑖔j����
		for (int i = 0; i < fbxNodePtr->GetChildCount(); i++)
		{
			runningNode(fbxNodePtr->GetChild(i), &loadDataParam);
		}

		std::experimental::filesystem::path meshPath(fileName);

		std::string texturePath;

		if (meshPath.has_parent_path())
		{
			texturePath = meshPath.parent_path().string() + "/";
		}

		// ���_�o�b�t�@������ŕK�v�ȃp�����[�^
		VertexBufferInitParams vertexBufferParams = { sizeof(FbxVertexDataParam), 0U, sizeof(FbxVertexDataParam) * loadDataParam.vertexDataArray.size(), loadDataParam.vertexDataArray.data() };
		// �C���f�b�N�X�o�b�t�@������ŕK�v�ȃp�����[�^
		IndexBufferInitParams indexBufferParams = { loadDataParam.indexDataArray };
		// �}�e���A���X���b�g������ŕK�v�ȃp�����[�^
		MaterialSlotsInitParams materialSlotsParams;
		materialSlotsParams.subsets.reserve(loadDataParam.materialDataArray.size());

		for (unsigned int i = 0; i < loadDataParam.materialDataArray.size(); i++)
		{
			// �}�e���A������ǂݍ��񂾃e�N�X�`���̓}�e���A��ID��100�{�����l�ɉ��Ԗڂ̃e�N�X�`�����𑫂����̒l�̕��̐���ID�ŊǗ������
			int baseMaterialTextureId = -(materialIdArray.at(i) * 100);

			// �A���x�h�e�N�X�`�������[�h����
			Texture2DManager::load(baseMaterialTextureId - 1, texturePath + loadDataParam.materialDataArray.at(i).textureFileName);

			// �@���e�N�X�`�������[�h����
			Texture2DManager::load(baseMaterialTextureId - 2, texturePath + loadDataParam.materialDataArray.at(i).normalFileName);

			// �}�e���A�����쐬
			Material::create(
				materialIdArray.at(i),
				SystemVertexShaderId::Mesh,
				SystemPixelShaderId::Mesh,
				{ baseMaterialTextureId - 1, baseMaterialTextureId - 2 },
				loadDataParam.materialDataArray.at(i).ambient,
				loadDataParam.materialDataArray.at(i).diffuse,
				loadDataParam.materialDataArray.at(i).specular,
				loadDataParam.materialDataArray.at(i).emission,
				loadDataParam.materialDataArray.at(i).shiniess
			);

			materialSlotsParams.subsets.push_back({ loadDataParam.subsetDataArray.at(i).start, loadDataParam.subsetDataArray.at(i).count });
		}
		// ���b�V���f�[�^���쐬
		Mesh::create(meshId, vertexBufferParams, indexBufferParams, materialSlotsParams);
	}

	void FbxLoader::initSdkObjects(fbxsdk::FbxScene** scenePtr)
	{
		// �}�l�[�W���[���쐬
		m_managerPtr = fbxsdk::FbxManager::Create();

		if (!m_managerPtr) throw std::runtime_error("load fbx error");

		// IO�Z�b�e�B���O�̐ݒ������
		fbxsdk::FbxIOSettings* iosPtr = fbxsdk::FbxIOSettings::Create(m_managerPtr, IOSROOT);
		m_managerPtr->SetIOSettings(iosPtr);

		// �V�[�����쐬
		(*scenePtr) = fbxsdk::FbxScene::Create(m_managerPtr, "tktkFbxScene");

		if (!*scenePtr)
		{
			m_managerPtr->Destroy();
			throw std::runtime_error("load fbx error");
		}
	}

	void FbxLoader::runningNode(fbxsdk::FbxNode * nodePtr, FbxLoadDataParam * out)
	{
		if (nodePtr->GetNodeAttribute() != NULL)
		{
			switch (nodePtr->GetNodeAttribute()->GetAttributeType())
			{
			case fbxsdk::FbxNodeAttribute::eMesh:
				
				fbxsdk::FbxMesh* meshPtr = nodePtr->GetMesh();
				FbxMeshLoader::loadMesh(meshPtr, out);
				break;
			}
		}

		for (int i = 0; i < nodePtr->GetChildCount(); i++)
		{
			runningNode(nodePtr->GetChild(i), out);
		}
	}
}