#include "TktkAppendDxlib3DComponent/Graphics/Billboard/RectBillboardAnimatorMaker.h"

namespace tktk
{
	RectBillboardAnimatorMaker RectBillboardAnimatorMaker::m_self;

	RectBillboardAnimatorMaker & RectBillboardAnimatorMaker::makeStart()
	{
		m_self = RectBillboardAnimatorMaker();
		return m_self;
	}

	std::shared_ptr<RectBillboardAnimator> RectBillboardAnimatorMaker::create()
	{
		return std::make_shared<RectBillboardAnimator>(
			m_textureId,
			m_splitTextureIndexList,
			m_animationIntervalSec,
			m_loop,
			m_animSpeedRate
			);
	}

	RectBillboardAnimatorMaker & RectBillboardAnimatorMaker::textureId(int value)
	{
		m_textureId = value;
		return *this;
	}

	RectBillboardAnimatorMaker & RectBillboardAnimatorMaker::animationIntervalSec(float value)
	{
		m_animationIntervalSec = value;
		return *this;
	}

	RectBillboardAnimatorMaker & RectBillboardAnimatorMaker::loop(bool value)
	{
		m_loop = value;
		return *this;
	}

	RectBillboardAnimatorMaker & RectBillboardAnimatorMaker::animSpeedRate(float value)
	{
		m_animSpeedRate = value;
		return *this;
	}
}