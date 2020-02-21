#include "TktkAppendDxlib2DComponent/Graphics/Sprite/SpriteDrawer.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include <TktkMath/Matrix3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	SpriteDrawer::SpriteDrawer(
		int textureId,
		int splitTextureIndex,
		float drawPriority,
		const Vector2 & spriteCenterPosRate,
		BlendMode blendMode,
		float blendParam,
		unsigned int reverseFlag,
		bool useClipping,
		const Vector2 & clippingLeftTopPos,
		const Vector2 & clippingRightBottomPos
	)
		: ComponentBase(drawPriority)
		, m_textureId(textureId)
		, m_splitTextureIndex(splitTextureIndex)
		, m_spriteCenterPosRate(spriteCenterPosRate)
		, m_blendMode(blendMode)
		, m_blendParam(blendParam)
		, m_reverseFlag(reverseFlag)
		, m_useClipping(useClipping)
		, m_clippingLeftTopPos(clippingLeftTopPos)
		, m_clippingRightBottomPos(clippingRightBottomPos)
	{
	}

	void SpriteDrawer::start()
	{
		auto transform2D = getComponent<Transform2D>();

		if (transform2D.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
		m_transform2D = transform2D;

		auto textureAssets = Assets2DManager::getTextureAssets();

		if (textureAssets.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found TextureAssets");
		}
		m_textureAssets = textureAssets;
	}

	void SpriteDrawer::draw() const
	{
		if (m_textureId == -1) return;

		if (m_useRenderTarget) RenderTargetManager::setRenderTarget(m_renderTargetId);

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(m_blendMode, static_cast<int>(m_blendParam * 255));

		Matrix3 selfPose = m_transform2D->calculateWorldMatrix();

		TextureHandles textureHandles = m_textureAssets->getTextureHandles(m_textureId);
		int textureHandle = (m_splitTextureIndex == -1) ? textureHandles.textureHandle : textureHandles.splitTextureHandles.at(m_splitTextureIndex);
	
		Vector2 textureSize = m_textureAssets->getTextureSize(m_textureId, m_splitTextureIndex);
	
		Vector2 reverseScale = Vector2::one;
		if ((m_reverseFlag & HORIZONTAL_REVERSE) != 0)	reverseScale.x = -1.0f;
		if ((m_reverseFlag & VERTICAL_REVERSE) != 0)	reverseScale.y = -1.0f;
		Matrix3 reverseMat = Matrix3::createScale(reverseScale);

		Vector2 pos1 = Vector2(-textureSize.x * m_spriteCenterPosRate.x,			-textureSize.y * m_spriteCenterPosRate.y)			* reverseMat * selfPose;
		Vector2 pos2 = Vector2( textureSize.x * (1.0f - m_spriteCenterPosRate.x),	-textureSize.y * m_spriteCenterPosRate.y)			* reverseMat * selfPose;
		Vector2 pos3 = Vector2( textureSize.x * (1.0f - m_spriteCenterPosRate.x),	 textureSize.y * (1.0f - m_spriteCenterPosRate.y))	* reverseMat * selfPose;
		Vector2 pos4 = Vector2(-textureSize.x * m_spriteCenterPosRate.x,			 textureSize.y * (1.0f - m_spriteCenterPosRate.y))	* reverseMat * selfPose;

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
				textureHandle,
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
				textureHandle,
				TRUE
			);
		}

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
		if (m_useRenderTarget) RenderTargetManager::unSetRenderTarget();
	}

	void SpriteDrawer::setTextureId(int textureId)
	{
		m_textureId = textureId;
	}

	int SpriteDrawer::getTextureId() const
	{
		return m_textureId;
	}

	void SpriteDrawer::setSplitTextureIndex(int splitTextureIndex)
	{
		m_splitTextureIndex = splitTextureIndex;
	}

	const Vector2 & SpriteDrawer::getSpriteCenterPosRate() const
	{
		return m_spriteCenterPosRate;
	}

	int SpriteDrawer::getSplitTextureIndex() const
	{
		return m_splitTextureIndex;
	}

	void SpriteDrawer::setSpriteCenterPosRate(const Vector2 & spriteCenterPosRate)
	{
		m_spriteCenterPosRate = spriteCenterPosRate;
	}

	void SpriteDrawer::useClipping(const Vector2 & clippingLeftTopPos, const Vector2 & clippingRightBottomPos)
	{
		m_useClipping = true;
		m_clippingLeftTopPos = clippingLeftTopPos;
		m_clippingRightBottomPos = clippingRightBottomPos;
	}

	void SpriteDrawer::unUseClipping()
	{
		m_useClipping = false;
	}

	BlendMode SpriteDrawer::getBlendMode() const
	{
		return m_blendMode;
	}

	void SpriteDrawer::setBlendMode(BlendMode blendMode)
	{
		m_blendMode = blendMode;
	}

	void SpriteDrawer::setBlendParam(float blendParam)
	{
		m_blendParam = blendParam;
	}

	float SpriteDrawer::getBlendParam() const
	{
		return m_blendParam;
	}

	void SpriteDrawer::setReverseFlag(unsigned int reverseFlag)
	{
		m_reverseFlag = reverseFlag;
	}

	void SpriteDrawer::useRenderTarget(int renderTargetId)
	{
		m_useRenderTarget = true;
		m_renderTargetId = renderTargetId;
	}

	void SpriteDrawer::unUseRenderTarget()
	{
		m_useRenderTarget = false;
		m_renderTargetId = -1;
	}
}