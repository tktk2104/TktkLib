#include "Tktk2dCollision/Body2dBase/CollisionSupport2D.h"

#include <cmath>
#include <vector>
#include <algorithm>
#include <TktkMath/MathHelper.h>
#include "Tktk2dCollision/BoundingCircle.h"
#include "Tktk2dCollision/BoundingRect.h"
#include "Tktk2dCollision/BoundingPolygon2d.h"

bool CollisionSupport2D::collideCircleToCircle(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingCircle& selfCircle = dynamic_cast<const BoundingCircle&>(self);
	const BoundingCircle& otherCircle = dynamic_cast<const BoundingCircle&>(other);

	Vector2 selfCenterPos = selfCircle.calculatePose().calculateTranslation();
	Vector2 otherCenterPos = otherCircle.calculatePose().calculateTranslation();

	float selfRadius = selfCircle.calculateRadius();
	float otherRadius = otherCircle.calculateRadius();

	Vector2 selfToOtherDirection = Vector2::normalize(selfCenterPos - otherCenterPos);
	Vector2 otherToSelfDirection = Vector2::normalize(otherCenterPos - selfCenterPos);

	hitinfo->selfPointClosestToOther = selfCenterPos + (selfToOtherDirection * otherRadius);
	hitinfo->otherPointClosestToSelf = otherCenterPos + (otherToSelfDirection * selfRadius);

	hitinfo->isHit = (Vector2::distance(selfCenterPos, otherCenterPos) < selfRadius + otherRadius);

	return hitinfo->isHit;
}

bool CollisionSupport2D::collideRectToRect(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingRect& selfRect = dynamic_cast<const BoundingRect&>(self);
	const BoundingRect& otherRect = dynamic_cast<const BoundingRect&>(other);

	Vector2 selfCenterPos = selfRect.calculatePose().calculateTranslation();
	Vector2 otherCenterPos = otherRect.calculatePose().calculateTranslation();

	Vector2 selfMin = selfRect.calculateCornerPoint(BoundingRect::CornerType::Min);
	Vector2 selfMax = selfRect.calculateCornerPoint(BoundingRect::CornerType::Max);

	Vector2 otherMin = otherRect.calculateCornerPoint(BoundingRect::CornerType::Min);
	Vector2 otherMax = otherRect.calculateCornerPoint(BoundingRect::CornerType::Max);

	hitinfo->selfPointClosestToOther = Vector2::clamp(
		selfCenterPos, otherMin, otherMax
	);

	hitinfo->otherPointClosestToSelf = Vector2::clamp(
		otherCenterPos, selfMin, selfMax
	);

	bool selfMinPosXCheck = selfMin.x < otherMax.x;
	bool selfMinPosYCheck = selfMin.y < otherMax.y;

	bool selfMaxPosXCheck = selfMax.x > otherMin.x;
	bool selfMaxPosYCheck = selfMax.y > otherMin.y;

	// boolの説明変数を使わずに判定した方が比較の処理が減る（誤差の範囲内）
	hitinfo->isHit = (
		selfMinPosXCheck &&
		selfMinPosYCheck &&
		selfMaxPosXCheck &&
		selfMaxPosYCheck
		);

	return hitinfo->isHit;
}

bool CollisionSupport2D::collidePolygonToPolygon(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingPolygon2d& selfPolygon = dynamic_cast<const BoundingPolygon2d&>(self);
	const BoundingPolygon2d& otherPolygon = dynamic_cast<const BoundingPolygon2d&>(other);

	std::vector<Vector2> selfVertexs = selfPolygon.calculateVertexs();
	std::vector<Vector2> otherVertexs = otherPolygon.calculateVertexs();

	Vector2 selfMinPos = Vector2::positiveInfinity;
	Vector2 selfMaxPos = Vector2::negativeInfinity;
	Vector2 otherMinPos = Vector2::positiveInfinity;
	Vector2 otherMaxPos = Vector2::negativeInfinity;

	std::for_each(
		std::begin(selfVertexs),
		std::end(selfVertexs),
		[&selfMinPos, &selfMaxPos](const Vector2& node)
		{
			if (selfMinPos.x > node.x) selfMinPos.x = node.x;
			if (selfMaxPos.x < node.x) selfMaxPos.x = node.x;
			if (selfMinPos.y > node.y) selfMinPos.y = node.y;
			if (selfMaxPos.y < node.y) selfMaxPos.y = node.y;
		}
	);

	std::for_each(
		std::begin(otherVertexs),
		std::end(otherVertexs),
		[&otherMinPos, &otherMaxPos](const Vector2& node)
		{
			if (otherMinPos.x > node.x) otherMinPos.x = node.x;
			if (otherMaxPos.x < node.x) otherMaxPos.x = node.x;
			if (otherMinPos.y > node.y) otherMinPos.y = node.y;
			if (otherMaxPos.y < node.y) otherMaxPos.y = node.y;
		}
	);

	Vector2 selfCenterPos = selfMinPos + (selfMaxPos - selfMinPos) / 2;
	Vector2 otherCenterPos = otherMinPos + (otherMaxPos - otherMinPos) / 2;

	if (collidePolygonToPoint(self, otherCenterPos)) return true;
	if (collidePolygonToPoint(other, selfCenterPos)) return true;

	for (size_t i = 0; i < otherVertexs.size(); i++)
	{
		bool isHit = true;

		for (size_t j = 0; j < selfVertexs.size(); j++)
		{
			Vector2 line = selfVertexs.at((j + 1) % selfVertexs.size()) - selfVertexs.at(j);

			Vector2 selfToOther = otherVertexs.at(i) - selfVertexs.at(j);

			float cross = Vector2::cross(selfToOther, line);

			if (cross > 0.0f) isHit = false;
		}

		if (isHit)
		{
			hitinfo->isHit = true;
			return hitinfo->isHit;
		}
	}

	for (size_t i = 0; i < selfVertexs.size(); i++)
	{
		bool isHit = true;

		for (size_t j = 0; j < otherVertexs.size(); j++)
		{
			Vector2 line = otherVertexs.at((j + 1) % otherVertexs.size()) - otherVertexs.at(j);

			Vector2 otherToSelf = selfVertexs.at(i) - otherVertexs.at(j);

			float cross = Vector2::cross(otherToSelf, line);

			if (cross > 0.0f) isHit = false;
		}

		if (isHit)
		{
			hitinfo->isHit = true;
			return hitinfo->isHit;
		}
	}

	return false;
}

bool CollisionSupport2D::collideCircleToRect(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingCircle& selfCircle = dynamic_cast<const BoundingCircle&>(self);
	const BoundingRect& otherRect = dynamic_cast<const BoundingRect&>(other);

	Vector2 selfCenterPos = selfCircle.calculatePose().calculateTranslation();
	Vector2 otherCenterPos = otherRect.calculatePose().calculateTranslation();

	Vector2 otherMin = otherRect.calculateCornerPoint(BoundingRect::CornerType::Min);
	Vector2 otherMax = otherRect.calculateCornerPoint(BoundingRect::CornerType::Max);

	hitinfo->selfPointClosestToOther = Vector2::clamp(
		selfCenterPos, otherMin, otherMax
	);

	float selfRadius = selfCircle.calculateRadius();

	// 自分の当たり判定の中心から見た相手の当たり判定の中心の方向
	Vector2 selfToOtherDirection = Vector2::normalize(otherCenterPos - selfCenterPos);

	hitinfo->otherPointClosestToSelf = selfCenterPos 
		+ (selfToOtherDirection * MathHelper::clamp((otherCenterPos - selfCenterPos).length(), 0.0f, selfRadius));

	hitinfo->isHit = (Vector2::distance(selfCenterPos, hitinfo->selfPointClosestToOther) < selfRadius);

	return hitinfo->isHit;
}

bool CollisionSupport2D::collideRectToCircle(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	bool result = collideCircleToRect(other, self, hitinfo);

	auto tempSelfPoint = hitinfo->selfPointClosestToOther;
	hitinfo->selfPointClosestToOther = hitinfo->otherPointClosestToSelf;
	hitinfo->otherPointClosestToSelf = tempSelfPoint;

	return result;
}

bool CollisionSupport2D::collideCircleToPolygon(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingCircle& selfCircle = dynamic_cast<const BoundingCircle&>(self);
	const BoundingPolygon2d& otherPolygon = dynamic_cast<const BoundingPolygon2d&>(other);

	Vector2 selfCenterPos = selfCircle.calculatePose().calculateTranslation();

	float selfRadius = selfCircle.calculateRadius();
	std::vector<Vector2> otherVertexs = otherPolygon.calculateVertexs();

	for (size_t i = 0; i < otherVertexs.size(); i++)
	{
		if (Vector2::distanceSquared(otherVertexs.at(i), selfCenterPos) <= selfRadius * selfRadius)
		{
			hitinfo->isHit = true;
			return hitinfo->isHit;
		}
	}

	for (size_t i = 0; i < otherVertexs.size(); i++)
	{
		Vector2 line = otherVertexs.at((i + 1) % otherVertexs.size()) - otherVertexs.at(i);

		Vector2 lineBeginToCircleCenter = selfCenterPos - otherVertexs.at(i);
		Vector2 lineEndToCircleCenter = selfCenterPos - otherVertexs.at((i + 1) % otherVertexs.size());

		float distance = std::abs(Vector2::cross(lineBeginToCircleCenter, line.normalized()));

		if (distance <= selfRadius && Vector2::dot(lineBeginToCircleCenter, line) * Vector2::dot(lineEndToCircleCenter, line) < 0.0f)
		{
			hitinfo->isHit = true;
			return hitinfo->isHit;
		}
	}

	for (size_t i = 0; i < otherVertexs.size(); i++)
	{
		Vector2 line = otherVertexs.at((i + 1) % otherVertexs.size()) - otherVertexs.at(i);
		Vector2 otherVertexToSelfCenter = selfCenterPos - otherVertexs.at(i);
		if (Vector2::cross(otherVertexToSelfCenter, line) > 0)
		{
			hitinfo->isHit = false;
			return hitinfo->isHit;
		}
	}
	hitinfo->isHit = true;
	return hitinfo->isHit;
}

bool CollisionSupport2D::collidePolygonToCircle(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	bool result = collideCircleToPolygon(other, self, hitinfo);

	auto tempSelfPoint = hitinfo->selfPointClosestToOther;
	hitinfo->selfPointClosestToOther = hitinfo->otherPointClosestToSelf;
	hitinfo->otherPointClosestToSelf = tempSelfPoint;

	return result;
}

bool CollisionSupport2D::collideRectToPolygon(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	return false;
}

bool CollisionSupport2D::collidePolygonToRect(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	bool result = collideRectToPolygon(other, self, hitinfo);

	auto tempSelfPoint = hitinfo->selfPointClosestToOther;
	hitinfo->selfPointClosestToOther = hitinfo->otherPointClosestToSelf;
	hitinfo->otherPointClosestToSelf = tempSelfPoint;

	return result;
}

bool CollisionSupport2D::collidePolygonToPoint(const Body2dBase & self, const Vector2 & other)
{
	const BoundingPolygon2d& selfPolygon = dynamic_cast<const BoundingPolygon2d&>(self);
	std::vector<Vector2> selfVertexs = selfPolygon.calculateVertexs();

	for (size_t i = 0; i < selfVertexs.size(); i++)
	{
		Vector2 line = selfVertexs.at((i + 1) % selfVertexs.size()) - selfVertexs.at(i);

		Vector2 selfToOther = other - selfVertexs.at(i);

		float cross = Vector2::cross(selfToOther, line);

		if (cross > 0.0f) return false;
	}
	return true;
}
