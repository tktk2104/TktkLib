#include "TktkAppendDxlib3DComponent/Graphics/MeshDrawer/MeshAnimator.h"

#include <stdexcept>
#include <TktkComponentFramework/Time/Time.h>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"
#include <DxLib.h>

namespace tktk
{
	MeshAnimator::MeshAnimator(
		int motionID,
		bool isLoop,
		float motionSpeedRate,
		float motionIntervalSec,
		bool useOtherMotionData
	)
		: m_curUseOtherMotionData(useOtherMotionData)
		, m_preUseOtherMotionData(useOtherMotionData)
		, m_curMotionID(motionID)
		, m_preMotionID(motionID)
		, m_isLoop(isLoop)
		, m_motionSpeedRate(motionSpeedRate)
		, m_motionIntervalSec(motionIntervalSec)

	{
	}

	void MeshAnimator::start()
	{
		auto meshDrawer = getComponent<MeshDrawer>();

		if (meshDrawer.isNull())
		{
			throw std::runtime_error("MeshAnimator not found MeshDrawer");
		}
		m_meshDrawer = meshDrawer;
	}

	void MeshAnimator::update()
	{
		if (m_isLoop)
		{
			m_curMotionTimer = std::fmod(m_curMotionTimer + getCurMotionEndTime(), getCurMotionEndTime());
		}

		MeshHandles drawMeshHandles = Assets3DManager::getMeshAssets()->getMeshHandle(m_meshDrawer->getMeshID());

		int preAttachIndex;

		if (m_preUseOtherMotionData)
		{
			preAttachIndex = DxLib::MV1AttachAnim(drawMeshHandles.meshHandle, 0, drawMeshHandles.animHandles.at(m_preMotionID));
		}
		else
		{
			preAttachIndex = DxLib::MV1AttachAnim(drawMeshHandles.meshHandle, m_preMotionID);
		}

		int curAttachIndex;

		if (m_curUseOtherMotionData)
		{
			curAttachIndex = DxLib::MV1AttachAnim(drawMeshHandles.meshHandle, 0, drawMeshHandles.animHandles.at(m_curMotionID));
		}
		else
		{
			curAttachIndex = DxLib::MV1AttachAnim(drawMeshHandles.meshHandle, m_curMotionID);
		}

		DxLib::MV1SetAttachAnimBlendRate(drawMeshHandles.meshHandle, preAttachIndex, 1.0f - std::fmax(m_lerpSecTimer / m_lerpTimeSec, 0.01f));
		DxLib::MV1SetAttachAnimBlendRate(drawMeshHandles.meshHandle, curAttachIndex, std::fmax(m_lerpSecTimer / m_lerpTimeSec, 0.01f));
		DxLib::MV1SetAttachAnimTime(drawMeshHandles.meshHandle, preAttachIndex, std::fmax(m_preMotionTimer, 0.01f));
		DxLib::MV1SetAttachAnimTime(drawMeshHandles.meshHandle, curAttachIndex, std::fmax(m_curMotionTimer, 0.01f));

		auto meshLocalBoneMatrices = std::vector<Matrix4>(m_meshDrawer->getBoneCount());

		for (int i = 0; i < static_cast<int>(meshLocalBoneMatrices.size()); ++i)
		{
			DxLib::MV1ResetFrameUserLocalMatrix(drawMeshHandles.meshHandle, i);
			meshLocalBoneMatrices.at(i) = DXConverter::toMatrix(DxLib::MV1GetFrameLocalMatrix(drawMeshHandles.meshHandle, i));
		}
		m_meshDrawer->setLocalBoneMatrices(meshLocalBoneMatrices);

		DxLib::MV1DetachAnim(drawMeshHandles.meshHandle, preAttachIndex);
		DxLib::MV1DetachAnim(drawMeshHandles.meshHandle, curAttachIndex);

		m_curMotionTimer += tktk::Time::deltaTime() * m_motionSpeedRate / m_motionIntervalSec;

		m_lerpSecTimer = std::fmin(m_lerpSecTimer + (tktk::Time::deltaTime() * m_motionSpeedRate), m_lerpTimeSec);
	}

	void MeshAnimator::changeMotion(int motionID, bool isLoop, float lerpTimeSec, bool useOtherMotionData)
	{
		if (m_curUseOtherMotionData == useOtherMotionData && m_curMotionID == motionID) return;
	
		m_preUseOtherMotionData = m_curUseOtherMotionData;
		m_preMotionID = m_curMotionID;
		m_preMotionTimer = m_curMotionTimer;

		m_lerpSecTimer = 0.0f;
		if (lerpTimeSec <= 0.0f) lerpTimeSec = 0.001f;
		m_lerpTimeSec = lerpTimeSec;

		m_curUseOtherMotionData = useOtherMotionData;
		m_curMotionID = motionID;
		m_curMotionTimer = 0.0f;

		m_isLoop = isLoop;
	}

	int MeshAnimator::getCurMotionID() const
	{
		return m_curMotionID;
	}

	bool MeshAnimator::isEndAnimation() const
	{
		if (m_motionSpeedRate > 0.0f) return (m_curMotionTimer > getCurMotionEndTime());

		return (m_curMotionTimer < 0.0f);
	}

	float MeshAnimator::getCurMotionEndTime() const
	{
		MeshHandles drawMeshHandles = Assets3DManager::getMeshAssets()->getMeshHandle(m_meshDrawer->getMeshID());

		if (m_curUseOtherMotionData)
		{
			return DxLib::MV1GetAnimTotalTime(drawMeshHandles.animHandles.at(m_curMotionID), 0);
		}
		return DxLib::MV1GetAnimTotalTime(drawMeshHandles.meshHandle, m_curMotionID);
	}

	float MeshAnimator::getMotionSpeedRate() const
	{
		return m_motionSpeedRate;
	}

	void MeshAnimator::setMotionSpeedRate(float speed)
	{
		m_motionSpeedRate = speed;
	}
}