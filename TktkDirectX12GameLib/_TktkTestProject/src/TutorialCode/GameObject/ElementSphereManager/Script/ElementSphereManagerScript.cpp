#include "ElementSphereManagerScript.h"

#include <stdexcept>
#include <limits>
#include <cmath>
#include <TktkMath/Random.h>

#include <TktkDX12BaseComponents/3D/Transform3D/Transform3D.h>
#include <TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawer.h>
#include "../../ElementSphere/Script/ElementColorChanger.h"

#include "../../ElementSphere/ElementSphere.h"
#include "../../ElementShapeGuide/ElementShapeGuide.h"
#include "../../ElementShape/ElementShape.h"

constexpr unsigned int ElementSphereManagerScript::m_firstElementMaterialId;
constexpr unsigned int ElementSphereManagerScript::m_lastElementMaterialId;
constexpr unsigned int ElementSphereManagerScript::m_useMatArraySize;

void ElementSphereManagerScript::start()
{
	for (unsigned int i = 0; i < m_useMatArraySize; i++)
	{
		tktkMath::Color sphereColor;

		switch (tktkMath::Random::getRandI(1, 3))
		{
		case 1: sphereColor = tktkMath::colorRed;	break;
		case 2: sphereColor = tktkMath::colorGreen; break;
		case 3: sphereColor = tktkMath::colorBlue;	break;
		}

		createElementSphere(
			tktkMath::Vector3(
				tktkMath::Random::getRandF(-3.0f, 3.0f),
				tktkMath::Random::getRandF(-3.0f, 3.0f),
				tktkMath::Random::getRandF(-3.0f, 3.0f)
			),
			sphereColor
		);
	}

	m_elementShapeGuide = ElementShapeGuide::create();
}

void ElementSphereManagerScript::update()
{
	m_elementSphereObjectList.remove_if(
		[](tktk::GameObjectPtr& node) { return node.expired(); }
	);

	// �g�p���Ă���J�����̏��
	auto cameraDataPtr = tktk::DX12GameManager::getProjectionMatrix();
		
		Camera::getDataPtr(CameraId::PlayerCamera);

	// �X�N���[����ԏ�̓_�̔z��
	std::vector<VertexColor2DPolygonVertexData> elementSpherePointArray;

	// X���W���ő�A�ŏ��̍��W�̃C���f�b�N�X
	unsigned int maxXPosIndex = 0U;
	unsigned int minXPosIndex = 0U;

	// Y���W���ő�A�ŏ��̍��W�̃C���f�b�N�X
	unsigned int maxYPosIndex = 0U;
	unsigned int minYPosIndex = 0U;

	// ���݂̃C���f�b�N�X
	unsigned int curIndex = 0U;

	for (const auto& node : m_elementSphereObjectList)
	{
		auto transform = node->getComponent<tktk::Transform3D>();
		const auto& screenSize = tktk::DX12GameManager::getWindowSize();

		// �X�N���[�����W�����߂�
		tktkMath::Vector3 result = transform->getWorldPosition() * tktk::DX12GameManager::getViewMatrix(0) * tktk::DX12GameManager::getProjectionMatrix(0);
		result /= result.z;
		result = result * tktkMath::Matrix4::createScreen(0.0f, 0.0f, screenSize.x, screenSize.y);

		// ���������_����ʊO�ɏo�Ă����ꍇ�A�������Ȃ�
		if (result.x < 0.0f || result.x > screenSize.x || result.y < 0.0f || result.y > screenSize.y) continue;

		// �X�N���[����ԏ�̓_�̔z���ǉ�����
		VertexColor2DPolygonVertexData tempData;
		tempData.position = tktkMath::Vector2(result.x, result.y);
		tempData.vertexColor = node->getComponent<ElementColorChanger>()->getColor();

		elementSpherePointArray.push_back(tempData);

		// ���W���ꂼ��̐����̍ő�A�ŏ��̍��W�̃C���f�b�N�X���X�V����
		if (elementSpherePointArray.at(maxXPosIndex).position.x < result.x) maxXPosIndex = curIndex;
		if (elementSpherePointArray.at(minXPosIndex).position.x > result.x) minXPosIndex = curIndex;
		if (elementSpherePointArray.at(maxYPosIndex).position.y < result.y) maxYPosIndex = curIndex;
		if (elementSpherePointArray.at(minYPosIndex).position.y > result.y) minYPosIndex = curIndex;

		curIndex++;
	}

	// �ő�A�ŏ��ł͂Ȃ����_�̃C���f�b�N�X�̃��X�g
	std::forward_list<unsigned int> notMaxOrMinIndexList;

	// ���݂̒��_��������̐����̍ő�A�ŏ��l�Ŗ�����΁u�ő�A�ŏ��ł͂Ȃ����_�̃C���f�b�N�X�̃��X�g�v�ɒǉ�����
	for (unsigned int i = 0; i < elementSpherePointArray.size(); i++)
	{
		if (maxXPosIndex != i || minXPosIndex != i || maxYPosIndex != i || minYPosIndex != i)
		{
			notMaxOrMinIndexList.push_front(i);
		}
	}

	// ���_���P�����������牽�����Ȃ�
	if (curIndex == 0U) return;

	// �쐬����}�`�̒��_�̔z��
	std::vector<tktkMath::Vector2> elementShapeGuideVertexArray;
	// �쐬����}�`�̒��_�J���[���݂̒��_���̔z��
	std::vector<VertexColor2DPolygonVertexData> elementShapeVertexArray;

	// ���O�ɒǉ��������_�����ϐ�
	tktkMath::Vector2 previousAddPos = elementSpherePointArray.at(minXPosIndex).position;

	// �u�����W���ŏ��̍��W�v���ŏ��̒��_�Ƃ��Ĕz��ɒǉ�����
	elementShapeGuideVertexArray.push_back(previousAddPos);
	elementShapeVertexArray.push_back(elementSpherePointArray.at(minXPosIndex));

	// �u�����W���ŏ��̍��W�v���u�����W���ŏ��̍��W�v�Ɠ����łȂ����
	if (minYPosIndex != minXPosIndex)
	{
		addElementShapeVertexArray(
			&elementShapeGuideVertexArray,
			&elementShapeVertexArray,
			&notMaxOrMinIndexList,
			previousAddPos,
			elementSpherePointArray.at(minYPosIndex).position,
			elementSpherePointArray
		);

		// �u�����W���ŏ��̍��W�v���ŏ��̒��_�Ƃ��Ĕz��ɒǉ�����
		previousAddPos = elementSpherePointArray.at(minYPosIndex).position;
		elementShapeGuideVertexArray.push_back(previousAddPos);
		elementShapeVertexArray.push_back(elementSpherePointArray.at(minYPosIndex));
	}

	if (maxXPosIndex != minXPosIndex && maxXPosIndex != minYPosIndex)
	{
		addElementShapeVertexArray(
			&elementShapeGuideVertexArray,
			&elementShapeVertexArray,
			&notMaxOrMinIndexList,
			previousAddPos,
			elementSpherePointArray.at(maxXPosIndex).position,
			elementSpherePointArray
		);

		previousAddPos = elementSpherePointArray.at(maxXPosIndex).position;
		elementShapeGuideVertexArray.push_back(previousAddPos);
		elementShapeVertexArray.push_back(elementSpherePointArray.at(maxXPosIndex));
	}

	if (maxYPosIndex != minXPosIndex && maxYPosIndex != minYPosIndex && maxYPosIndex != maxXPosIndex)
	{
		addElementShapeVertexArray(
			&elementShapeGuideVertexArray,
			&elementShapeVertexArray,
			&notMaxOrMinIndexList,
			previousAddPos,
			elementSpherePointArray.at(maxYPosIndex).position,
			elementSpherePointArray
		);

		previousAddPos = elementSpherePointArray.at(maxYPosIndex).position;
		elementShapeGuideVertexArray.push_back(previousAddPos);
		elementShapeVertexArray.push_back(elementSpherePointArray.at(maxYPosIndex));
	}

	addElementShapeVertexArray(
		&elementShapeGuideVertexArray,
		&elementShapeVertexArray,
		&notMaxOrMinIndexList,
		previousAddPos,
		elementSpherePointArray.at(minXPosIndex).position,
		elementSpherePointArray
	);

	elementShapeGuideVertexArray.push_back(elementSpherePointArray.at(minXPosIndex).position);

	m_elementShapeGuide->getComponent<tktk::Line2DDrawer>()->setLineVertexArray(elementShapeGuideVertexArray);

	if (tktk::DX12GameManager::isTrigger(tktk::KeybordKeyType::key_Space) && elementShapeVertexArray.size() >= 3U)
	{
		ElementShape::create(elementShapeVertexArray);
	}
}

void ElementSphereManagerScript::createElementSphere(const tktkMath::Vector3 & position, const tktkMath::Color & color)
{
	for (unsigned int i = 0; i < m_useMatArray.size(); i++)
	{
		if (!m_useMatArray.at(i))
		{
			m_elementSphereObjectList.push_front(ElementSphere::create(position, color, static_cast<MaterialId>(m_firstElementMaterialId + i)));
			m_useMatArray.at(i) = true;
			return;
		}
	}

	throw std::runtime_error("nou found can use ElementMaterialId");
}

void ElementSphereManagerScript::addElementShapeVertexArray(
	std::vector<tktkMath::Vector2>* elementShapeGuideVertexArrayPtr,
	std::vector<VertexColor2DPolygonVertexData>* elementShapeVertexArrayPtr,
	std::forward_list<unsigned int>* notMaxOrMinIndexListPtr,
	const tktkMath::Vector2 & previousPos,
	const tktkMath::Vector2 & nextPos,
	const std::vector<VertexColor2DPolygonVertexData>& elementSpherePointArray
)
{
	// �ufirstPos->nextPos�v�̃x�N�g��
	tktkMath::Vector2 line = nextPos - previousPos;

	// firstPos��nextPos�̊Ԃɓ��鎑�i�̂��钸�_�̃C���f�b�N�X�̃��X�g
	std::forward_list<unsigned int> insertVertexIndexList;

	// �쐬����}�`�̒��_�ɂȂ��Ă��Ȃ����_�̃C���f�b�N�X������
	for (auto node : *notMaxOrMinIndexListPtr)
	{
		// �ufirstPos->���񒆂̒��_�v�̃x�N�g��
		tktkMath::Vector2 firstToPoint = elementSpherePointArray.at(node).position - previousPos;

		// firstPos��nextPos�̊Ԃɓ��鎑�i�̂��钸�_�Ȃ�ufirstPos��nextPos�̊Ԃɓ��鎑�i�̂��钸�_�̃��X�g�v�ɒǉ�����
		if (tktkMath::Vector2::cross(firstToPoint, line) > 0.0f) insertVertexIndexList.push_front(node);
		// �����]
	}

	// �ufirstPos��nextPos�̊Ԃɓ��鎑�i�̂��钸�_�v�����݂�����
	if (std::begin(insertVertexIndexList) != std::end(insertVertexIndexList))
	{
		// �ł��ufirstPos->nextPos�v�̐������牓�����_�̃C���f�b�N�X
		unsigned int mostFarVertexIndex = 0U;

		// �ł������ufirstPos->nextPos�v����umostFarVertexIndex�v�̒��_�̋���
		float mostFarDist = std::numeric_limits<float>::min();

		// firstPos��nextPos�̊Ԃɓ��鎑�i�̂��钸�_�̃C���f�b�N�X������
		for (auto node : insertVertexIndexList)
		{
			float tempDist = 0.0f;

			tktkMath::Vector2 chackVertex = elementSpherePointArray.at(node).position;

			float a = nextPos.x - previousPos.x;
			float b = nextPos.y - previousPos.y;

			float a2 = a * a;
			float b2 = b * b;

			// �����̒����̂Q��̒l�H
			float r2 = a2 + b2;

			float tt = -(a * (previousPos.x - chackVertex.x) + b * (previousPos.y - chackVertex.y));

			if (tt < 0)
			{
				tempDist = std::sqrtf((previousPos.x - chackVertex.x) * (previousPos.x - chackVertex.x) + (previousPos.y - chackVertex.y) * (previousPos.y - chackVertex.y));
			}
			else if (tt > r2)
			{
				tempDist = std::sqrtf((nextPos.x - chackVertex.x) * (nextPos.x - chackVertex.x) + (nextPos.y - chackVertex.y) * (nextPos.y - chackVertex.y));
			}
			else
			{
				float f1 = a * (previousPos.y - chackVertex.y) - b * (previousPos.x - chackVertex.x);
				tempDist = std::sqrtf((f1 * f1) / r2);
			}

			if (mostFarDist < tempDist)
			{
				mostFarVertexIndex = node;
				mostFarDist = tempDist;
			}
		}

		// �ufirstPos->nextPos�v�̐�������ł��������W�����̒��_�Ƃ��Ĕz��ɒǉ�����
		elementShapeGuideVertexArrayPtr->push_back(elementSpherePointArray.at(mostFarVertexIndex).position);
		elementShapeVertexArrayPtr->push_back(elementSpherePointArray.at(mostFarVertexIndex));

		// �ǉ��������_�̃C���f�b�N�X���unotMaxOrMinIndexList�v����폜����
		notMaxOrMinIndexListPtr->remove(mostFarVertexIndex);

		// �V�������_�ōċN����
		addElementShapeVertexArray(
			elementShapeGuideVertexArrayPtr,
			elementShapeVertexArrayPtr,
			notMaxOrMinIndexListPtr,
			elementSpherePointArray.at(mostFarVertexIndex).position,
			nextPos,
			elementSpherePointArray
		);
	}
}
