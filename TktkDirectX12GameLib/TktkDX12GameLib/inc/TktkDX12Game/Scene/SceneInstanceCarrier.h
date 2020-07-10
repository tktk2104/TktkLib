#ifndef SCENE_INSTANCE_CARRIER_H_
#define SCENE_INSTANCE_CARRIER_H_

#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasEndChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>
#include "../SafetyVoidPtr/SafetyUniqueVoidPtr.h"

namespace tktk
{
	// �V�[���̃C���X�^���X��ێ�����N���X
	class SceneInstanceCarrier
	{
	public:

		template<class SceneType>
		SceneInstanceCarrier(SceneType* ptr);
		~SceneInstanceCarrier();

	public:

		// �V�[����L���ɂ���
		void enableScene();

		// �V�[���𖳌��ɂ���
		void disableScene();

		// �V�[���̍X�V����
		void update();

	private:

		struct VTable
		{
			void (*start)(const SafetyUniqueVoidPtr&);
			void (*update)(const SafetyUniqueVoidPtr&);
			void (*end)(const SafetyUniqueVoidPtr&);
		};

		template <class T>
		struct VTableInitializer
		{
			static VTable m_vtable;

			static void start(const SafetyUniqueVoidPtr& self);
			static void update(const SafetyUniqueVoidPtr& self);
			static void end(const SafetyUniqueVoidPtr& self);
		};

	private:

		bool				m_isActive{ false };
		bool				m_nextFrameIsActive{ false };
		SafetyUniqueVoidPtr	m_scenePtr{};
		VTable*				m_vtablePtr{ nullptr };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template <class T>
	SceneInstanceCarrier::VTable SceneInstanceCarrier::VTableInitializer<T>::m_vtable =
	{
		&SceneInstanceCarrier::VTableInitializer<T>::start,
		&SceneInstanceCarrier::VTableInitializer<T>::update,
		&SceneInstanceCarrier::VTableInitializer<T>::end
	};

	template<class SceneType>
	inline SceneInstanceCarrier::SceneInstanceCarrier(SceneType* ptr)
	{
		m_isActive			= false;
		m_nextFrameIsActive = false;
		m_scenePtr			= SafetyUniqueVoidPtr(ptr);
		m_vtablePtr			= &VTableInitializer<SceneType>::m_vtable;
	}

	template<class T>
	inline void SceneInstanceCarrier::VTableInitializer<T>::start(const SafetyUniqueVoidPtr& self)
	{
		start_runner<void>::checkAndRun(self.castPtr<T>());
	}

	template<class T>
	inline void SceneInstanceCarrier::VTableInitializer<T>::update(const SafetyUniqueVoidPtr& self)
	{
		update_runner<void>::checkAndRun(self.castPtr<T>());
	}

	template<class T>
	inline void SceneInstanceCarrier::VTableInitializer<T>::end(const SafetyUniqueVoidPtr& self)
	{
		end_runner<void>::checkAndRun(self.castPtr<T>());
	}
	
}
#endif // !SCENE_INSTANCE_CARRIER_H_