#pragma once

#include <forward_list>
#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Game/Component/ComponentBase.h>
#include "../../ElementShape/VertexColor2DPolygonVertexData.h"

class ElementSphereManagerScript
	: public tktk::ComponentBase
{
public:

	ElementSphereManagerScript() = default;

public:

	void start();

	void update();

private:

	// ���̂̒��_���Q�[���J�������猩�����̂Q�������W�ō���ł��傫�ȑ��p�`���v�Z����
	void calculateElementShape(
		const std::vector<ElementShapeVertexData>& elementSpherePointArray,
		unsigned int maxXPosIndex,
		unsigned int minXPosIndex,
		unsigned int maxYPosIndex,
		unsigned int minYPosIndex
	);

	// �����̂Q���_�����Ԑ����𕪊����鎞�̒��_�̃C���f�b�N�X���擾����
	std::forward_list<unsigned int> getSplitLineVertexIndexArray(
		const std::vector<ElementShapeVertexData>& elementSpherePointArray,
		std::forward_list<unsigned int>& notUseIndexList,
		const tktkMath::Vector2& previousPos,
		const tktkMath::Vector2& nextPos
	);

private:

	// ��ʂɕ\�����鋅�̂̏����
	static constexpr unsigned int m_sphereMaxNum{ 8U };

private:

	// ���̂�`�悷��I�u�W�F�N�g�̃��X�g
	std::forward_list<tktk::GameObjectPtr> m_sphereObjectList;

	// ����鑽�p�`�̑�܂��Ȍ`�������K�C�h
	tktk::GameObjectPtr m_elementShapeGuide;
};