#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>

namespace tktk
{
	// �X�v���C�g�`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform2D�z
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(
			float drawPriority,
			int textureId,
			int blendStateId,
			const Color& blendRate,
			int depthStencilStateId
		);

	public:

		void start();
		void draw() const;

	private:

		int m_textureId;
		int m_blendStateId;
		Color m_blendRate;
		int m_depthStencilStateId;

		CfpPtr<Transform2D> m_transform;
	};
}
#endif // !SPRITE_DRAWER_H_