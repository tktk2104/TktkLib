#ifndef SCENE_INSTANCE_CARRIER_H_
#define SCENE_INSTANCE_CARRIER_H_

#include "SceneVTable.h"

namespace tktk
{
	// �V�[���̃C���X�^���X��ێ�����N���X
	class SceneInstanceCarrier
	{
	public:

		SceneInstanceCarrier(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);
		~SceneInstanceCarrier();

	public:

		// �V�[����L���ɂ���
		void enable();

		// �V�[���𖳌��ɂ���
		void disable();

		// �V�[���̍X�V����
		void update();

	private:

		bool						m_isActive			{ false };
		bool						m_nextFrameIsActive	{ false };
		std::shared_ptr<SceneBase>	m_scenePtr			{ nullptr };
		SceneVTable*				m_vtablePtr			{ nullptr };
	};
}
#endif // !SCENE_INSTANCE_CARRIER_H_