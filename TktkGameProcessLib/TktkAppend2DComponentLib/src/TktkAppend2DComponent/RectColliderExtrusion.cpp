#include "TktkAppend2DComponent/RectColliderExtrusion.h"

#include <limits.h>
#include <TktkMath/MathHelper.h>
#include <Tktk2dCollision/Body2dBase/Body2dBase.h>
#include <Tktk2dCollision/BoundingPolygon2d.h>

namespace tktk
{
	void RectColliderExtrusion::onCollisionStay(CfpPtr<GameObject> other)
	{
		auto otherTransform = other->getComponent<tktk::Transform2D>();
		auto otherCollider = other->getComponent<tktk::RectCollider>();
		if (otherTransform.isNull() || otherCollider.isNull()) return;

		// player->enemyのベクトルとplayerから最も近いのenemyの衝突判定の辺の交差点
		Vector2 crossLinePos_1 = Vector2::zero;
		// m_crossLinePos_1が存在するenemyの衝突判定の辺を作る頂点の番号の小さい方
		size_t lineFirstVertexId_1 = 0u;

		// m_crossLinePos_1が交わる辺からenemy方向へ直角な線から最も近いのplayerの衝突判定の辺の交差点
		Vector2 crossLinePos_2 = Vector2::zero;
		// m_crossLinePos_2が存在するplayerの衝突判定の辺を作る頂点の番号の小さい方
		size_t lineFirstVertexId_2 = 0u;

		auto selfTransform = getComponent<tktk::Transform2D>();
		auto selfCollider = getComponent<tktk::RectCollider>();
		if (selfTransform.isNull() || selfCollider.isNull()) return;

		auto selfPos = selfTransform->getWorldPosition();
		auto selfVertexs = static_cast<const BoundingPolygon2d&>(selfCollider->getBodyBase()).calculateVertexs();
		auto enemyPos = otherTransform->getWorldPosition();
		auto enemyVertexs = static_cast<const BoundingPolygon2d&>(otherCollider->getBodyBase()).calculateVertexs();

		// 基準となる差（最も長さの差が小さい）
		float referenceDist = INFINITY;

		for (size_t i = 0u; i < enemyVertexs.size(); i++)
		{
			float dR = 0;
			float dS = 0;
			Vector2 crossPos = Vector2::zero;

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
		
		// m_crossLinePos_1が存在するenemyの衝突判定の辺のベクトル
		auto crossLineVec_1 = (enemyVertexs.at((lineFirstVertexId_1 + 1u) % enemyVertexs.size()) - enemyVertexs.at(lineFirstVertexId_1)).normalized();
		// m_crossLinePos_1を垂直にする
		crossLineVec_1 = Vector2::perpendicular(crossLineVec_1);

		referenceDist = INFINITY;

		for (size_t i = 0u; i < selfVertexs.size(); i++)
		{
			float dR = 0;
			float dS = 0;
			Vector2 crossPos = Vector2::zero;

			bool notParallel = lineCrossCheck(
				crossLinePos_1 + (crossLineVec_1 * MathHelper::kEpsilon),
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

		float angle = Vector2::signedAngle(enemyVertexs.at((lineFirstVertexId_1 + 1u) % enemyVertexs.size()) - enemyVertexs.at(lineFirstVertexId_1), Vector2::down);
		angle = 360.0f - angle - 90.0f;

		auto vec = (Vector2(MathHelper::sin(angle), -MathHelper::cos(angle)).normalized() * 10000.0f);
		auto resultVel = Vector2::zero;

		{
			float dR = 0;
			float dS = 0;
			Vector2 crossPos = Vector2::zero;

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
			Vector2 crossPos = Vector2::zero;

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
		const Vector2 & a,
		const Vector2 & b,
		const Vector2 & c,
		const Vector2 & d,
		float* dR,
		float* dS,
		Vector2 * crossPos
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