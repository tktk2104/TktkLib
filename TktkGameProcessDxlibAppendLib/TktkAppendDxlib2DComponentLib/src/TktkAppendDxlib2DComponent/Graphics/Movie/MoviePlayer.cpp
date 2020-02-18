#include "TktkAppendDxlib2DComponent/Graphics/Movie/MoviePlayer.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include <TktkMath/Matrix3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	MoviePlayer::MoviePlayer(
		float drawPriority,
		int movieId,
		const Vector2 & movieCenterPosRate,
		BlendMode blendMode,
		float blendParam,
		unsigned int reverseFlag,
		bool useClipping,
		const Vector2 & clippingLeftTopPos,
		const Vector2 & clippingRightBottomPos
	)
		: ComponentBase(drawPriority)
		, m_movieId(movieId)
		, m_movieCenterPosRate(movieCenterPosRate)
		, m_blendMode(blendMode)
		, m_blendParam(blendParam)
		, m_reverseFlag(reverseFlag)
		, m_useClipping(useClipping)
		, m_clippingLeftTopPos(clippingLeftTopPos)
		, m_clippingRightBottomPos(clippingRightBottomPos)
	{
	}

	void MoviePlayer::start()
	{
		auto transform2D = getComponent<Transform2D>();

		if (transform2D.expired())
		{
			throw std::runtime_error("MoviePlayer not found Transform2D");
		}
		m_transform2D = transform2D;

		auto movieAssets = Assets2DManager::getMovieAssets();

		if (movieAssets.expired())
		{
			throw std::runtime_error("MoviePlayer not found MovieAssets");
		}
		m_movieAssets = movieAssets;
	}

	void MoviePlayer::draw() const
	{
		if (m_movieId == -1) return;

		if (m_useRenderTarget) RenderTargetManager::setRenderTarget(m_renderTargetId);

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(m_blendMode, static_cast<int>(m_blendParam * 255));

		Matrix3 selfPose = m_transform2D.lock()->calculateWorldMatrix();

		int movieHandle = m_movieAssets.lock()->getMovieHandle(m_movieId);

		Vector2 movieSize = m_movieAssets.lock()->getMovieSize(m_movieId);

		Vector2 reverseScale = Vector2::one;
		if ((m_reverseFlag & HORIZONTAL_REVERSE) != 0)	reverseScale.x = -1.0f;
		if ((m_reverseFlag & VERTICAL_REVERSE) != 0)	reverseScale.y = -1.0f;
		Matrix3 reverseMat = Matrix3::createScale(reverseScale);

		Vector2 pos1 = Vector2(-movieSize.x * m_movieCenterPosRate.x,			-movieSize.y * m_movieCenterPosRate.y)			* reverseMat * selfPose;
		Vector2 pos2 = Vector2( movieSize.x * (1.0f - m_movieCenterPosRate.x),	-movieSize.y * m_movieCenterPosRate.y)			* reverseMat * selfPose;
		Vector2 pos3 = Vector2( movieSize.x * (1.0f - m_movieCenterPosRate.x),	 movieSize.y * (1.0f - m_movieCenterPosRate.y))	* reverseMat * selfPose;
		Vector2 pos4 = Vector2(-movieSize.x * m_movieCenterPosRate.x,			 movieSize.y * (1.0f - m_movieCenterPosRate.y))	* reverseMat * selfPose;

		if (m_useClipping)
		{
			DxLib::DrawRectModiGraphF(
				pos1.x, pos1.y,
				pos2.x, pos2.y,
				pos3.x, pos3.y,
				pos4.x, pos4.y,
				static_cast<int>(m_clippingLeftTopPos.x),
				static_cast<int>(m_clippingLeftTopPos.y),
				static_cast<int>(m_clippingRightBottomPos.x - m_clippingLeftTopPos.x),
				static_cast<int>(m_clippingRightBottomPos.y - m_clippingLeftTopPos.y),
				movieHandle,
				TRUE
			);
		}
		else
		{
			DxLib::DrawModiGraphF(
				pos1.x, pos1.y,
				pos2.x, pos2.y,
				pos3.x, pos3.y,
				pos4.x, pos4.y,
				movieHandle,
				TRUE
			);
		}

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (m_useRenderTarget) RenderTargetManager::unSetRenderTarget();
	}

	int MoviePlayer::getMovieId() const
	{
		return m_movieId;
	}

	void MoviePlayer::setMovieId(int movieId)
	{
		m_movieId = movieId;
	}

	const Vector2 & MoviePlayer::getMovieCenterPosRate() const
	{
		return m_movieCenterPosRate;
	}

	void MoviePlayer::setMovieCenterPosRate(const Vector2 & movieCenterPosRate)
	{
		m_movieCenterPosRate = movieCenterPosRate;
	}

	void MoviePlayer::useClipping(const Vector2 & clippingLeftTopPos, const Vector2 & clippingRightBottomPos)
	{
		m_useClipping = true;
		m_clippingLeftTopPos = clippingLeftTopPos;
		m_clippingRightBottomPos = clippingRightBottomPos;
	}

	void MoviePlayer::unUseClipping()
	{
		m_useClipping = false;
	}

	BlendMode MoviePlayer::getBlendMode() const
	{
		return m_blendMode;
	}

	void MoviePlayer::setBlendMode(BlendMode blendMode)
	{
		m_blendMode = blendMode;
	}

	float MoviePlayer::getBlendParam() const
	{
		return m_blendParam;
	}

	void MoviePlayer::setBlendParam(float blendParam)
	{
		m_blendParam = blendParam;
	}

	void MoviePlayer::setReverseFlag(unsigned int reverseFlag)
	{
		m_reverseFlag = reverseFlag;
	}

	void MoviePlayer::useRenderTarget(int renderTargetId)
	{
		m_useRenderTarget = true;
		m_renderTargetId = renderTargetId;
	}

	void MoviePlayer::unUseRenderTarget()
	{
		m_useRenderTarget = false;
		m_renderTargetId = -1;
	}
}