#include "VertexColor2DPolygonDrawer.h"

#include <stdexcept>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../VertexColor2DPolygonConstantBufferData.h"
#include "../../../../Enum/_ResourceIds/ResourceIds.h"

VertexColor2DPolygonDrawer::VertexColor2DPolygonDrawer(
	float drawPriority,
	const std::vector<ElementShapeVertexData>& vertexArray
)
	: ComponentBase(drawPriority)
	, m_vertexArray(vertexArray)
{
}

void VertexColor2DPolygonDrawer::start()
{
	ElementShapeVertexData center;

	for (const auto& node : m_vertexArray)
	{
		center.position += node.position;
		center.vertexColor += node.vertexColor;
	}
	center.position		/= m_vertexArray.size();
	center.vertexColor	/= m_vertexArray.size();

	m_vertexArray.push_back(center);

	tktk::DX12GameManager::createVertexBuffer(toInt(VertexBufferId::VertexColorPolygon), m_vertexArray);
	{
		std::vector<unsigned short> indexArray;

		for (unsigned int i = 0; i < (m_vertexArray.size() - 1); i++)
		{
			indexArray.push_back(m_vertexArray.size() - 1);
			indexArray.push_back((i + 0));
			indexArray.push_back((i + 1) % (m_vertexArray.size() - 1));
		}

		tktk::DX12GameManager::createIndexBuffer(toInt(IndexBufferId::VertexColorPolygon), indexArray);

		m_indexCount = indexArray.size();
	}

	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("SpriteDrawer not found Transform2D");
	}
}

void VertexColor2DPolygonDrawer::draw() const
{
	{
		VertexColor2DPolygonConstantBufferData vertexColor2DPolygonConstantBufferData;

		tktkMath::Matrix3 worldMat = m_transform->calculateWorldMatrix();

		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;

			vertexColor2DPolygonConstantBufferData.worldMatrix[i] = worldMat.m[i / 4U][i % 4U];
		}

		vertexColor2DPolygonConstantBufferData.blendRate = { 1.0f, 1.0f, 1.0f, 0.8f };
		vertexColor2DPolygonConstantBufferData.screenSize = tktk::DX12GameManager::getWindowSize();

		tktk::DX12GameManager::updateCBuffer(toInt(CbufferId::VertexColorPolygon), vertexColor2DPolygonConstantBufferData);
	}

	// �r���[�|�[�g��ݒ肷��
	tktk::DX12GameManager::setViewport(tktk::DX12GameManager::getSystemId(tktk::SystemViewportType::Basic));

	// �V�U�[��`��ݒ肷��
	tktk::DX12GameManager::setScissorRect(tktk::DX12GameManager::getSystemId(tktk::SystemScissorRectType::Basic));

	// �����_�[�^�[�Q�b�g��ݒ肷��
	tktk::DX12GameManager::setBackBufferView();

	// ��p�̃p�C�v���C���X�e�[�g��ݒ肷��
	tktk::DX12GameManager::setPipeLineState(toInt(PipeLineStateId::VertexColorPolygon));

	// ��p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
	tktk::DX12GameManager::setDescriptorHeap({ { tktk::DescriptorHeapType::basic, toInt(BasicDescriptorHeapId::VertexColorPolygon)} });

	// �g���C�A���O�����X�g�ŕ`����s��
	tktk::DX12GameManager::setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ��p�̒��_�o�b�t�@��ݒ肷��
	tktk::DX12GameManager::setVertexBuffer(toInt(VertexBufferId::VertexColorPolygon));

	// ��p�̃C���f�b�N�X�o�b�t�@��ݒ肷��
	tktk::DX12GameManager::setIndexBuffer(toInt(IndexBufferId::VertexColorPolygon));

	// �h���[�R�[��
	tktk::DX12GameManager::drawIndexedInstanced(m_indexCount, 1U, 0U, 0U, 0U);

	// �R�}���h���X�g�����s����
	tktk::DX12GameManager::executeCommandList();
}
