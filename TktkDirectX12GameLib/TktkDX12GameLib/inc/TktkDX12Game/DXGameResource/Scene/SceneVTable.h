#ifndef SCENE_V_TABLE_H_
#define SCENE_V_TABLE_H_

#include <memory>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasEndChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>
#include "SceneBase.h"

namespace tktk
{
	// �V�[���N���X�̊֐����s�N���X
	struct SceneVTable
	{
		void (*start)	(const std::weak_ptr<SceneBase>&);
		void (*update)	(const std::weak_ptr<SceneBase>&);
		void (*end)		(const std::weak_ptr<SceneBase>&);
	};

	// �uSceneVTable�v����邽�߂ɕK�v�ȐÓI�֐��|�C���^
	template <class SceneType>
	struct SceneVTableInitializer
	{
		static SceneVTable m_vtable;

		static void start	(const std::weak_ptr<SceneBase>& self);
		static void update	(const std::weak_ptr<SceneBase>& self);
		static void end		(const std::weak_ptr<SceneBase>& self);
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template <class SceneType>
	SceneVTable SceneVTableInitializer<SceneType>::m_vtable =
	{
		&SceneVTableInitializer<SceneType>::start,
		&SceneVTableInitializer<SceneType>::update,
		&SceneVTableInitializer<SceneType>::end
	};

	template<class SceneType>
	inline void SceneVTableInitializer<SceneType>::start(const std::weak_ptr<SceneBase>& self)
	{
		start_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
	}

	template<class SceneType>
	inline void SceneVTableInitializer<SceneType>::update(const std::weak_ptr<SceneBase>& self)
	{
		update_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
	}

	template<class SceneType>
	inline void SceneVTableInitializer<SceneType>::end(const std::weak_ptr<SceneBase>& self)
	{
		end_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
	}
}
#endif // !SCENE_V_TABLE_H_