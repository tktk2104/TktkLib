#include "TktkDX12BaseComponents/2D/RectColliderExtrusion/RectColliderExtrusion.h"

#include <limits.h>
#include <TktkMath/MathHelper.h>
#include <TktkCollision/2D/BoundingPolygon2d.h>

namespace tktk
{
	void RectColliderExtrusion::onCollisionStay(const tktk::GameObjectPtr& other)
	{
		auto otherTransform = other->getComponent<tktk::Transform2D>();
		auto otherCollider = other->getComponent<tktk::RectCollider>();
		if (otherTransform.expired() || otherCollider.expired()) return;

		// player->enemy�̃x�N�g����player����ł��߂���enemy�̏Փ˔���̕ӂ̌����_
		tktkMath::Vector2 crossLinePos_1 = tktkMath::vec2Zero;
		// m_crossLinePos_1�����݂���enemy�̏Փ˔���̕ӂ���钸�_�̔ԍ��̏�������
		size_t lineFirstVertexId_1 = 0u;

		// m_crossLinePos_1�������ӂ���enemy�����֒��p�Ȑ�����ł��߂���player�̏Փ˔���̕ӂ̌����_
		tktkMath::Vector2 crossLinePos_2 = tktkMath::vec2Zero;
		// m_crossLinePos_2�����݂���player�̏Փ˔���̕ӂ���钸�_�̔ԍ��̏�������
		size_t lineFirstVertexId_2 = 0u;

		auto selfTransform = getComponent<tktk::Transform2D>();
		auto selfCollider = getComponent<tktk::RectCollider>();
		if (selfTransform.expired() || selfCollider.expired()) return;

		auto selfPos = selfTransform->getWorldPosition();
		auto selfVertexs = static_cast<const BoundingPolygon2d&>(selfCollider->getBodyBase()).calculateVertexs();
		auto enemyPos = otherTransform->getWorldPosition();
		auto enemyVertexs = static_cast<const BoundingPolygon2d&>(otherCollider->getBodyBase()).calculateVertexs();

		// ��ƂȂ鍷�i�ł������̍����������j
		float referenceDist = INFINITY;

		for (size_t i = 0u; i < enemyVertexs.size(); i++)
		{
			float dR = 0;
			float dS = 0;
			tktkMath::Vector2 crossPos = tktkMath::vec2Zero;

			bool notParallel = lineCrossCheck(
				selfPos - (enemyPos - selfPos).normalized() * 10000.0f,
				enemyPos,
				enemyVertexs.at(i),
				enemyVertexs.at((i + 1u) % enemyVertexs.size()),
				&dR,
				&dS,
				&crossPos
			);

			float dist = (crossPos - selfPos).length();

			if (notParallel &&
				(dR < 1.0f && dS < 1.0f && dR > 0.0f && dS > 0.0f) &&
				dist < referenceDist)
			{
				referenceDist = dist;
				crossLinePos_1 = crossPos;
				lineFirstVertexId_1 = i;
			}
		}
		
		// m_crossLinePos_1�����݂���enemy�̏Փ˔���̕ӂ̃x�N�g��
		auto crossLineVec_1 = (enemyVertexs.at((lineFirstVertexId_1 + 1u) % enemyVertexs.size()) - enemyVertexs.at(lineFirstVertexId_1)).normalized();
		// m_crossLinePos_1�𐂒��ɂ���
		crossLineVec_1 = tktkMath::Vector2::perpendicular(crossLineVec_1);

		referenceDist = INFINITY;

		for (size_t i = 0u; i < selfVertexs.size(); i++)
		{
			float dR = 0;
			float dS = 0;
			tktkMath::Vector2 crossPos = tktkMath::vec2Zero;

			bool notParallel = lineCrossCheck(
				crossLinePos_1 + (crossLineVec_1 * tktkMath::MathHelper::kEpsilon),
				crossLinePos_1 + (crossLineVec_1 * 10000.0f),
				selfVertexs.at(i),
				selfVertexs.at((i + 1u) % selfVertexs.size()),
				&dR,
				&dS,
				&crossPos
			);

			float dist = (crossPos - crossLinePos_1).length();

			if (notParallel &&
				(dR < 1.0f && dS < 1.0f && dR > 0.0f && dS > 0.0f) &&
				dist < referenceDist)
			{
				referenceDist = dist;
				crossLinePos_2 = crossPos;
				lineFirstVertexId_2 = i;
			}
		}

		float angle = tktkMath::Vector2::signedAngle(enemyVertexs.at((lineFirstVertexId_1 + 1u) % enemyVertexs.size()) - enemyVertexs.at(lineFirstVertexId_1), tktkMath::vec2Down);
		angle = 360.0f - angle - 90.0f;

		auto vec = (tktkMath::Vector2(tktkMath::MathHelper::sin(angle), -tktkMath::MathHelper::cos(angle)).normalized() * 10000.0f);
		auto resultVel = tktkMath::vec2Zero;

		{
			float dR = 0;
			float dS = 0;
			tktkMath::Vector2 crossPos = tktkMath::vec2Zero;

			bool notParallel = lineCrossCheck(
				selfVertexs.at(lineFirstVertexId_2),
				selfVertexs.at(lineFirstVertexId_2) + vec,
				enemyVertexs.at(lineFirstVertexId_1),
				enemyVertexs.at((lineFirstVertexId_1 + 1u) % enemyVertexs.size()),
				&dR,
				&dS,
				&crossPos
			);

			if (notParallel &&
				(dR < 1.0f && dR > 0.0f) &&
				resultVel.length() < (crossPos - selfVertexs.at(lineFirstVertexId_2)).length())
			{
				resultVel = (crossPos - selfVertexs.at(lineFirstVertexId_2));
			}
		}

		{
			float dR = 0;
			float dS = 0;
			tktkMath::Vector2 crossPos = tktkMath::vec2Zero;

			bool notParallel = lineCrossCheck(
				selfVertexs.at((lineFirstVertexId_2 + 1u) % selfVertexs.size()),
				selfVertexs.at((lineFirstVertexId_2 + 1u) % selfVertexs.size()) + vec,
				enemyVertexs.at(lineFirstVertexId_1),
				enemyVertexs.at((lineFirstVertexId_1 + 1u) % enemyVertexs.size()),
				&dR,
				&dS,
				&crossPos
			);

			if (notParallel &&
				(dR < 1.0f && dR > 0.0f) &&
				resultVel.length() < (crossPos - selfVertexs.at((lineFirstVertexId_2 + 1u) % selfVertexs.size())).length())
			{
				resultVel = (crossPos - selfVertexs.at((lineFirstVertexId_2 + 1u) % selfVertexs.size()));
			}
		}
		selfTransform->setLocalPosition(selfPos + resultVel);
	}

	bool RectColliderExtrusion::lineCrossCheck(
		const tktkMath::Vector2 & a,
		const tktkMath::Vector2 & b,
		const tktkMath::Vector2 & c,
		const tktkMath::Vector2 & d,
		float* dR,
		float* dS,
		tktkMath::Vector2 * crossPos
	)
	{
		float bunbo = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
		if (bunbo == 0) return false;

		auto vecAC = c - a;

		(*dR) = ((d.y - c.y) * vecAC.x - (d.x - c.x) * vecAC.y) / bunbo;
		(*dS) = ((b.y - a.y) * vecAC.x - (b.x - a.x) * vecAC.y) / bunbo;

		(*crossPos) = a + (b - a) * (*dR);
		return true;
	}
}