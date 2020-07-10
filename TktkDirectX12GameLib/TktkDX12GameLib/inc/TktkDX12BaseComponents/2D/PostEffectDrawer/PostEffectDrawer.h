#ifndef POST_EFFECT_DRAWER_H_
#define POST_EFFECT_DRAWER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// �|�X�g�G�t�F�N�g�`��R���|�[�l���g
	class PostEffectDrawer
		: public ComponentBase
	{
	public:

		PostEffectDrawer(float drawPriority, unsigned int postEffectMaterialId, unsigned int useRtvDescriptorHeapId);

	public:

		void draw() const;

	private:

		unsigned int	m_useRtvDescriptorHeapId;
		unsigned int	m_postEffectMaterialId;
	};
}
#endif // !POST_EFFECT_DRAWER_H_