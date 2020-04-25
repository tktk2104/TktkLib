#ifndef COMPONENT_MAIN_LIST_H_
#define COMPONENT_MAIN_LIST_H_

#include <memory>
#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAwakeChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnEnableChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnDisableChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAfterCollideChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnDestroyChecker.h>

namespace tktk
{
	class ComponentBase;

	// �P��ނ̃R���|�[�l���g���Ǘ����郊�X�g�N���X
	class ComponentMainList
	{
	public:

		// ���̃N���X�ŊǗ�����R���|�[�l���g�̌^�̃|�C���^�������ɓn��
		// ���|�C���^�̌^��񂾂�����Ηǂ��̂�NULL�|�C���^�ŗǂ�
		template<class ComponentType>
		ComponentMainList(ComponentType* rawPtr);

	public:

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		// ���R���X�g���N�^�Ŏw�肵���^�łȂ��ƃr���h�s��
		template <class ComponentType, class... Args>
		std::weak_ptr<ComponentType> createComponent(Args... args);

		// ���g���Ǘ�����R���|�[�l���g�����񂵁A�A�N�e�B�u�t���O���O�t���[���ƕς���Ă�����uonEnable()�v�������́uonDisable()�v�֐��̎��s�����݂�
		void activeChangeCheck();

		// ���g���Ǘ�����R���|�[�l���g�̌^���uupdate()�v�֐��������Ă����炻����S�Ď��s����
		void runUpdate();

		// ���g���Ǘ�����R���|�[�l���g�̌^���uafterCollide�v�֐��������Ă����炻����S�Ď��s����
		void runAfterCollide();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		// ���g���Ǘ�����R���|�[�l���g�̌^�����B�����邽�߂̊֐��|�C���^
		struct VTable
		{
			void(*runUpdate)(const std::forward_list<std::shared_ptr<ComponentBase>>&);
			void(*runAfterCollide)(const std::forward_list<std::shared_ptr<ComponentBase>>&);
			void(*runOnEnable)(const std::shared_ptr<ComponentBase>&);
			void(*runOnDisable)(const std::shared_ptr<ComponentBase>&);
			void(*runOnDestroy)(const std::shared_ptr<ComponentBase>&);
		};

		// ���g���Ǘ�����R���|�[�l���g�̌^�����B�����邽�߂̊֐��̎��Ԃ����݂��鏊
		template <class ComponentType>
		struct VTableInitializer
		{
			// �uupdate()�v�֐��������Ă�����Ăԏ������s���ׂ̊֐��B
			static void runUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);
			template <class U, std::enable_if_t<has_update_checker<U*, void>::value>* = nullptr>
			static void checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);
			template <class U, std::enable_if_t<!has_update_checker<U*, void>::value>* = nullptr>
			static void checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);

			// �uafterCollide()�v�֐��������Ă�����Ăԏ������s���ׂ̊֐��B
			static void runAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);
			template <class U, std::enable_if_t<has_afterCollide_checker<U*, void>::value>* = nullptr>
			static void checkAndRunAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);
			template <class U, std::enable_if_t<!has_afterCollide_checker<U*, void>::value>* = nullptr>
			static void checkAndRunAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);

			// �uonEnable()�v�֐��������Ă�����Ăԏ������s���ׂ̊֐�
			static void runOnEnable(const std::shared_ptr<ComponentBase>& runPtr);

			// �uonDisable()�v�֐��������Ă�����Ăԏ������s���ׂ̊֐�
			static void runOnDisable(const std::shared_ptr<ComponentBase>& runPtr);

			// �uonDestroy()�v�֐��������Ă�����Ăԏ������s���ׂ̊֐�
			static void runOnDestroy(const std::shared_ptr<ComponentBase>& runPtr);

			static VTable m_vtable;
		};

	private:

		VTable*												m_vtablePtr;
		std::forward_list<std::shared_ptr<ComponentBase>>	m_mainList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// ���̃N���X�ŊǗ�����R���|�[�l���g�̌^�̃|�C���^�������ɓn��
	// ���|�C���^�̌^��񂾂�����Ηǂ��̂�NULL�|�C���^�ŗǂ�
	template<class ComponentType>
	inline ComponentMainList::ComponentMainList(ComponentType* rawPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
	{
	}

	// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
	// ���R���X�g���N�^�Ŏw�肵���^�łȂ��ƃr���h�s��
	template<class ComponentType, class ...Args>
	inline std::weak_ptr<ComponentType> ComponentMainList::createComponent(Args ...args)
	{
		auto createdComponent = std::make_shared<ComponentType>(args...);
		awake_runner<void>::checkAndRun(createdComponent);
		m_mainList.push_front(createdComponent);
		return createdComponent;
	}

	template<class ComponentType>
	typename ComponentMainList::VTable ComponentMainList::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentMainList::VTableInitializer<ComponentType>::runUpdate,
		&ComponentMainList::VTableInitializer<ComponentType>::runAfterCollide,
		&ComponentMainList::VTableInitializer<ComponentType>::runOnEnable,
		&ComponentMainList::VTableInitializer<ComponentType>::runOnDisable,
		&ComponentMainList::VTableInitializer<ComponentType>::runOnDestroy,
	};

	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
	{
		checkAndRunUpdate<ComponentType>(mainList);
	}

	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
	{
		checkAndRunAfterCollide<ComponentType>(mainList);
	}

	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runOnEnable(const std::shared_ptr<ComponentBase>& runPtr)
	{
		onEnable_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr));
	}

	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runOnDisable(const std::shared_ptr<ComponentBase>& runPtr)
	{
		onDisable_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr));
	}

	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runOnDestroy(const std::shared_ptr<ComponentBase>& runPtr)
	{
		onDestroy_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr));
	}

	template<class ComponentType>
	template<class U, std::enable_if_t<has_update_checker<U*, void>::value>*>
	inline void ComponentMainList::VTableInitializer<ComponentType>::checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
	{
		for (const auto& node : mainList)
		{
			if (!node->isActive()) continue;
			std::dynamic_pointer_cast<U>(node)->update();
		}
	}
	template<class ComponentType>
	template<class U, std::enable_if_t<!has_update_checker<U*, void>::value>*>
	inline void ComponentMainList::VTableInitializer<ComponentType>::checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList) {}

	template<class ComponentType>
	template<class U, std::enable_if_t<has_afterCollide_checker<U*, void>::value>*>
	inline void ComponentMainList::VTableInitializer<ComponentType>::checkAndRunAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
	{
		for (const auto& node : mainList)
		{
			if (!node->isActive()) continue;
			std::dynamic_pointer_cast<U>(node)->afterCollide();
		}
	}
	template<class ComponentType>
	template<class U, std::enable_if_t<!has_afterCollide_checker<U*, void>::value>*>
	inline void ComponentMainList::VTableInitializer<ComponentType>::checkAndRunAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList) {}
}
#endif // !COMPONENT_MAIN_LIST_H_