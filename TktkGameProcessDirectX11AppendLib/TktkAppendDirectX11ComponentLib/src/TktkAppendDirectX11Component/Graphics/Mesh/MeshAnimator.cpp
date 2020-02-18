#include "TktkAppendDirectX11Component/Graphics/Mesh/MeshAnimator.h"

#include <cmath>
#include <stdexcept>
#include <TktkComponentFramework/Time/Time.h>
#include "TktkDirectX11Wrapper/Graphics/Skeleton/Skeleton.h"
#include "TktkDirectX11Wrapper/Graphics/Animation/Animation.h"

namespace tktk
{
	MeshAnimator::MeshAnimator(
		CfpPtr<MeshDrawer> meshDrawer,
		int animationId,
		float animFrameIntervalPerSec,
		float animSpeedRate
	)
		: m_meshDrawer(meshDrawer)
		, m_animationId(animationId)
		, m_animFrameIntervalPerSec(animFrameIntervalPerSec)
		, m_animSpeedRate(animSpeedRate)
	{
	}

	MeshAnimator::~MeshAnimator()
	{
	}

	void MeshAnimator::start()
	{
		m_meshDrawer = getComponent<MeshDrawer>();

		if (m_meshDrawer.isNull())
		{
			throw std::runtime_error("MeshAnimator not found MeshDrawer");
		}
	}

	void MeshAnimator::update()
	{
		const SkeletonData& skeletonData = Skeleton::getData(m_meshDrawer->getSkeltonId());
		const AnimationData& animationData = Animation::getData(m_animationId);

		m_animSecTimer += Time::deltaTime() * m_animFrameIntervalPerSec * m_animSpeedRate;
		m_animSecTimer = std::fmod(m_animSecTimer, animationData.findEndFrameNo());

		std::array<Matrix4, 256U> localBoneMatrices;

		for (const auto& bone : skeletonData.getBoneArray())
		{
			const KeyFrame& keyFrame = animationData.calculateKeyFrame(bone.name, m_animSecTimer);

			localBoneMatrices.at(bone.id) = Matrix4::createTRS(keyFrame.position, keyFrame.rotate, keyFrame.scale);
		}

		m_meshDrawer->setLocalBoneMatrices(
			localBoneMatrices,
			skeletonData.getSize()
		);
	}
}