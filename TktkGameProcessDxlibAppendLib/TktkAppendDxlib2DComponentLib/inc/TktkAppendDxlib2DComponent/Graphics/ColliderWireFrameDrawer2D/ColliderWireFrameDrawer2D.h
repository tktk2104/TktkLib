#ifndef COLLIDER_WIREFRAME_DRAWER_2D_H_
#define COLLIDER_WIREFRAME_DRAWER_2D_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncClassList.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasSetActiveClass.h>
#include <TktkComponentFramework/Component/ComponentBase.h>

namespace tktk
{
	class ColliderWireFrameDrawer2D
		: public ComponentBase
	{
	public:

		ColliderWireFrameDrawer2D(
			float drawPriority,			// �`��D��x
			const Color& wireFrameColor	// ���C���[�t���[���̐F
		);

	public:

		void start();
		void update();
		void onEnable();
		void onDisable();

	private:

		float m_drawPriority;
		Color m_wireFrameColor;

		// �A�N�e�B�u��Ԃ�؂�ւ��邽�߂̃R���e�i�̃��b�p�[
		RunFuncClassList<HasSetActiveClass> m_hasSetActiveClassList;
	};
}
#endif // !COLLIDER_WIREFRAME_DRAWER_2D_H_