#include "ElementSphereManagerScript.h"

#include <limits>
#include <TktkMath/Random.h>
#include <TktkMath/MathHelper.h>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3D.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawer.h>

#include <TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawer.h>

#include "../../ElementSphere/ElementSphere.h"
#include "../../ElementShapeGuide/ElementShapeGuide.h"
#include "../../../../Enum/_ResourceIds/ResourceIds.h"

#include "../../ElementShape/ElementShape.h"

// ��ʂɕ\�����鋅�̂̏����
constexpr unsigned int ElementSphereManagerScript::m_sphereMaxNum;

void ElementSphereManagerScript::start()
{
	// ��ʂɕ\�����鋅�̂̐��������[�v����
	for (unsigned int i = 0; i < m_sphereMaxNum; i++)
	{
		// ���F�̋��̂��o�������邩�͗������g��
		tktkMath::Color sphereColor;

		switch (tktkMath::Random::getRandI(1, 3))
		{
		case 1: sphereColor = tktkMath::Color_v::red;	break;
		case 2: sphereColor = tktkMath::Color_v::green; break;
		case 3: sphereColor = tktkMath::Color_v::blue;	break;
		}

		// �o�����W���������g��
		tktkMath::Vector3 pos = {
			tktkMath::Random::getRandF(-3.0f, 3.0f),
			tktkMath::Random::getRandF(-3.0f, 3.0f),
			tktkMath::Random::getRandF(-3.0f, 3.0f)
		};

		// ���̂��o�������ĊǗ����X�g�ɒǉ�����
		m_sphereObjectList.push_front(ElementSphere::create(pos, sphereColor));
	}

	m_elementShapeGuide = ElementShapeGuide::create();
}

void ElementSphereManagerScript::update()
{
	// ���S���Ă��鋅�̃I�u�W�F�N�g�����X�g����폜����
	m_sphereObjectList.remove_if([](tktk::GameObjectPtr& node) { return node.expired(); });

	// �X�N���[����ԏ�̓_�ƑΉ�����F���̔z��
	std::vector<ElementShapeVertexData> elementSpherePointArray;

	// X���W���ő�A�ŏ��̍��W�̃C���f�b�N�X
	unsigned int maxXPosIndex = 0U;
	unsigned int minXPosIndex = 0U;

	// Y���W���ő�A�ŏ��̍��W�̃C���f�b�N�X
	unsigned int maxYPosIndex = 0U;
	unsigned int minYPosIndex = 0U;

	// ���݂̃C���f�b�N�X
	unsigned int curIndex = 0U;

	// ��ʏ�̋��̕`��I�u�W�F�N�g������
	for (const auto& sphereObject : m_sphereObjectList)
	{
		// ���W�Ǘ��R���|�[�l���g
		auto transform = sphereObject->getComponent<tktk::Transform3D>();

		// ��ʃT�C�Y
		const auto& screenSize = tktk::DX12GameManager::getWindowSize();

		// ���C���J�����̃r���[�s��
		const auto& viewMatrix = tktk::DX12GameManager::getViewMatrix(toInt(CameraId::Basic));

		// ���C���J�����̃v���W�F�N�V�����s��
		const auto& projectionMatrix = tktk::DX12GameManager::getProjectionMatrix(toInt(CameraId::Basic));

		// �r���[�s��ƃv���W�F�N�V�����s��ŋ��̂̒��S���W�����W�ϊ�����
		auto calculatedScreenPos = transform->getLocalPosition() * viewMatrix * projectionMatrix;

		// ���̒l�Ŋe����������
		calculatedScreenPos /= calculatedScreenPos.z;

		// �X�N���[�����W�����߂�
		calculatedScreenPos = calculatedScreenPos * tktkMath::Matrix4::createScreen(0.0f, 0.0f, screenSize.x, screenSize.y);

		// ���������_����ʊO�ɏo�Ă����ꍇ�A�������Ȃ�
		if (calculatedScreenPos.x < 0.0f || calculatedScreenPos.x > screenSize.x || calculatedScreenPos.y < 0.0f || calculatedScreenPos.y > screenSize.y) continue;

		// �X�N���[����ԏ�̓_�̔z���ǉ�����
		ElementShapeVertexData tempData;
		tempData.position = tktkMath::Vector2(calculatedScreenPos.x, calculatedScreenPos.y);
		tempData.vertexColor = sphereObject->getComponent<tktk::SphereMeshDrawer>()->getAlbedoColor();
		elementSpherePointArray.push_back(tempData);

		// ���W���ꂼ��̐����̍ő�A�ŏ��̍��W�̃C���f�b�N�X���X�V����
		if (elementSpherePointArray.at(maxXPosIndex).position.x < calculatedScreenPos.x) maxXPosIndex = curIndex;
		if (elementSpherePointArray.at(minXPosIndex).position.x > calculatedScreenPos.x) minXPosIndex = curIndex;
		if (elementSpherePointArray.at(maxYPosIndex).position.y < calculatedScreenPos.y) maxYPosIndex = curIndex;
		if (elementSpherePointArray.at(minYPosIndex).position.y > calculatedScreenPos.y) minYPosIndex = curIndex;

		curIndex++;
	}

	// ���_���P�����������牽�����Ȃ�
	if (elementSpherePointArray.size() == 0U) return;

	// ���̂̒��_���Q�[���J�������猩�����̂Q�������W�ō���ł��傫�ȑ��p�`���v�Z����
	calculateElementShape(elementSpherePointArray, maxXPosIndex, minXPosIndex, maxYPosIndex, minYPosIndex);
}

// ���̂̒��_���Q�[���J�������猩�����̂Q�������W�ō���ł��傫�ȑ��p�`���v�Z����
void ElementSphereManagerScript::calculateElementShape(
	const std::vector<ElementShapeVertexData>& elementSpherePointArray,
	unsigned int maxXPosIndex,
	unsigned int minXPosIndex,
	unsigned int maxYPosIndex,
	unsigned int minYPosIndex
)
{
	// ���p�`�Ŏg�p���Ă��Ȃ��C���f�b�N�X�̃��X�g
	std::forward_list<unsigned int> notUseIndexList;

	// �X�N���[����ԏ�̓_�̔z��̗v�f���������[�v����
	for (unsigned int i = 0; i < elementSpherePointArray.size(); i++)
	{
		// ���݂̒��_��������̐����̍ő�A�ŏ��l�Ŗ�����΁u�ő�A�ŏ��ł͂Ȃ����_�̃C���f�b�N�X�̃��X�g�v�ɒǉ�����
		if (maxXPosIndex != i && minXPosIndex != i && maxYPosIndex != i && minYPosIndex != i)
		{
			notUseIndexList.push_front(i);
		}
	}

	// �쐬����}�`�̒��_�J���[���݂̒��_���̔z��
	std::vector<ElementShapeVertexData> elementShapeVertexArray;

	// ���O�ɒǉ��������_�����ϐ�
	tktkMath::Vector2 previousAddPos = elementSpherePointArray.at(minXPosIndex).position;

	// �u�����W���ŏ��̍��W�v���ŏ��̒��_�Ƃ��Ĕz��ɒǉ�����
	elementShapeVertexArray.push_back(elementSpherePointArray.at(minXPosIndex));

	// �u�����W���ŏ��̍��W�v���u�����W���ŏ��̍��W�v�Ɠ����łȂ����
	if (minYPosIndex != minXPosIndex)
	{
		// �u�����W���ŏ��̍��W�v�Ɓu�����W���ŏ��̍��W�v�����Ԑ����𕪊��������̒��_�C���f�b�N�X���擾����
		auto result = getSplitLineVertexIndexArray(
			elementSpherePointArray,
			notUseIndexList,
			previousAddPos,
			elementSpherePointArray.at(minYPosIndex).position
		);

		// �擾�������_�C���f�b�N�X�ɑΉ��������_�����쐬����}�`�̒��_���z��ɒǉ�����
		for (unsigned int index : result)
		{
			elementShapeVertexArray.push_back(elementSpherePointArray.at(index));
		}

		// �u�����W���ŏ��̍��W�v��}�`�̒��_���z��ɒǉ�����
		elementShapeVertexArray.push_back(elementSpherePointArray.at(minYPosIndex));

		// �u�����W���ŏ��̍��W�v�𒼑O�ɒǉ��������_�ɂ���
		previousAddPos = elementSpherePointArray.at(minYPosIndex).position;
	}

	// �u�����W���ŏ��̍��W�v�A�u�����W���ŏ��̍��W�v�A�u�����W���ő�̍��W�v�������łȂ����
	if (maxXPosIndex != minXPosIndex && maxXPosIndex != minYPosIndex)
	{
		// �u���O�ɔ��肵�����W�v�Ɓu�����W���ő�̍��W�v�����Ԑ����𕪊��������̒��_�C���f�b�N�X���擾����
		auto result = getSplitLineVertexIndexArray(
			elementSpherePointArray,
			notUseIndexList,
			previousAddPos,
			elementSpherePointArray.at(maxXPosIndex).position
		);

		// �擾�������_�C���f�b�N�X�ɑΉ��������_�����쐬����}�`�̒��_���z��ɒǉ�����
		for (unsigned int index : result)
		{
			elementShapeVertexArray.push_back(elementSpherePointArray.at(index));
		}

		// �u�����W���ő�̍��W�v��}�`�̒��_���z��ɒǉ�����
		elementShapeVertexArray.push_back(elementSpherePointArray.at(maxXPosIndex));

		// �u�����W���ő�̍��W�v�𒼑O�ɒǉ��������_�ɂ���
		previousAddPos = elementSpherePointArray.at(maxXPosIndex).position;
	}

	// �u�����W���ŏ��̍��W�v�A�u�����W���ŏ��̍��W�v�A�u�����W���ő�̍��W�v�A�u�����W���ő�̍��W�v�������łȂ����
	if (maxYPosIndex != minXPosIndex && maxYPosIndex != minYPosIndex && maxYPosIndex != maxXPosIndex)
	{
		// �u���O�ɔ��肵�����W�v�Ɓu�����W���ő�̍��W�v�����Ԑ����𕪊��������̒��_�C���f�b�N�X���擾����
		auto result = getSplitLineVertexIndexArray(
			elementSpherePointArray,
			notUseIndexList,
			previousAddPos,
			elementSpherePointArray.at(maxYPosIndex).position
		);

		// �擾�������_�C���f�b�N�X�ɑΉ��������_�����쐬����}�`�̒��_���z��ɒǉ�����
		for (unsigned int index : result)
		{
			elementShapeVertexArray.push_back(elementSpherePointArray.at(index));
		}

		// �u�����W���ő�̍��W�v��}�`�̒��_���z��ɒǉ�����
		elementShapeVertexArray.push_back(elementSpherePointArray.at(maxYPosIndex));

		// �u�����W���ő�̍��W�v�𒼑O�ɒǉ��������_�ɂ���
		previousAddPos = elementSpherePointArray.at(maxYPosIndex).position;
	}

	// �Ō�̂P�ӂ͏����s��Ŏ��s
	{
		// �u���O�ɔ��肵�����W�v�Ɓu�����W���ŏ��̍��W�v�����Ԑ����𕪊��������̒��_�C���f�b�N�X���擾����
		auto result = getSplitLineVertexIndexArray(
			elementSpherePointArray,
			notUseIndexList,
			previousAddPos,
			elementSpherePointArray.at(minXPosIndex).position
		);

		// �擾�������_�C���f�b�N�X�ɑΉ��������_�����쐬����}�`�̒��_���z��ɒǉ�����
		for (unsigned int index : result)
		{
			elementShapeVertexArray.push_back(elementSpherePointArray.at(index));
		}

		//// �u�����W���ŏ��̍��W�v��}�`�̒��_���z��ɒǉ�����
		//elementShapeVertexArray.push_back(elementSpherePointArray.at(minXPosIndex));
	}

	// ���`��R���|�[�l���g�p�̒��_�����
	std::vector<tktkMath::Vector2> shapeGuideVertexArray;
	shapeGuideVertexArray.reserve(elementShapeVertexArray.size() + 1U);
	for (const auto& node : elementShapeVertexArray)
	{
		shapeGuideVertexArray.push_back(node.position);
	}
	//+
	shapeGuideVertexArray.push_back(elementShapeVertexArray.at(0).position);

	// ���`��R���|�[�l���g�̒��_���X�V
	m_elementShapeGuide->getComponent<tktk::Line2DDrawer>()->setLineVertexArray(shapeGuideVertexArray);

	if (tktk::DX12GameManager::isTrigger(tktk::KeybordKeyType::key_Space) && elementShapeVertexArray.size() >= 3U)
	{
		ElementShape::create(elementShapeVertexArray);
	}
}

// �����̂Q���_�����Ԑ����𕪊����鎞�̒��_���擾����
std::forward_list<unsigned int> ElementSphereManagerScript::getSplitLineVertexIndexArray(
	const std::vector<ElementShapeVertexData>& elementSpherePointArray,
	std::forward_list<unsigned int>& notUseIndexList,
	const tktkMath::Vector2& previousPos,
	const tktkMath::Vector2& nextPos
)
{
	// �upreviousPos->nextPos�v�̃x�N�g��
	tktkMath::Vector2 line = nextPos - previousPos;

	// �w�肵���Q���_�Ԃɓ��鎑�i�̂��钸�_�̃C���f�b�N�X�̃��X�g
	std::forward_list<unsigned int> insertVertexIndexList;

	// �쐬����}�`�̒��_�ɂȂ��Ă��Ȃ����_�̃C���f�b�N�X������
	for (unsigned int index : notUseIndexList)
	{
		// �upreviousPos->���񒆂̒��_�v�̃x�N�g��
		tktkMath::Vector2 firstToPoint = elementSpherePointArray.at(index).position - previousPos;

		// �w�肵���Q���_�Ԃɓ��鎑�i�̂��钸�_�����X�g�ɒǉ�����
		if (tktkMath::Vector2::cross(firstToPoint, line) > 0.0f) insertVertexIndexList.push_front(index);
	}

	// �w�肵���Q���_�Ԃɓ��鎑�i�̂��钸�_�����݂��Ȃ��������̃��X�g��Ԃ�
	if (std::begin(insertVertexIndexList) == std::end(insertVertexIndexList)) return std::forward_list<unsigned int>();

	// �ł��upreviousPos->nextPos�v�̐������牓�����_�̃C���f�b�N�X
	unsigned int mostFarVertexIndex = 0U;

	// �ł������ufirstPos->nextPos�v����umostFarVertexIndex�v�̒��_�̋���
	float mostFarDist = std::numeric_limits<float>::min();

	// �w�肵���Q���_�Ԃɓ��鎑�i�̂��钸�_������
	for (unsigned int index : insertVertexIndexList)
	{
		// ���肷�钸�_���W
		tktkMath::Vector2 chackVertex = elementSpherePointArray.at(index).position;

		// �w�肵���Q���_�����Ԑ����Ɣ��肷�钸�_���W���ǂꂾ������Ă��邩�𔻒肷�鏈��
		{
			float a = nextPos.x - previousPos.x;
			float b = nextPos.y - previousPos.y;

			float a2 = a * a;
			float b2 = b * b;

			float r2 = a2 + b2;

			float tt = -(a * (previousPos.x - chackVertex.x) + b * (previousPos.y - chackVertex.y));

			float tempDist = 0.0f;

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
				mostFarVertexIndex = index;
				mostFarDist = tempDist;
			}
		}
	}

	// �g�p����钸�_�̃C���f�b�N�X�̃��X�g
	std::forward_list<unsigned int> result;

	// �w�肵���Q���_�Ԃɓ��鎑�i������A�Q���_�����Ԑ�������ł��������_��ǉ�����
	result.push_front(mostFarVertexIndex);

	// �g�p����钸�_�̃C���f�b�N�X���u���p�`�Ŏg�p���Ă��Ȃ��C���f�b�N�X�̃��X�g�v����폜����
	notUseIndexList.remove(mostFarVertexIndex);

	// �g�p����钸�_�̃C���f�b�N�X���P�ڂ̒��_�Ƃ��čċN���A���ʂ��擾����
	auto childResult = getSplitLineVertexIndexArray(
					elementSpherePointArray,
					notUseIndexList,
					elementSpherePointArray.at(mostFarVertexIndex).position,
					nextPos
				);

	// �g�p����钸�_�̃C���f�b�N�X�̃��X�g�ɍċN�����̌��ʂ𑫂�
	result.splice_after(std::begin(result), std::move(childResult));

	return result;
	
}
