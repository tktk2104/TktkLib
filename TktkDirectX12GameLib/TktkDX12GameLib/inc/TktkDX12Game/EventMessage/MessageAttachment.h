#ifndef MESSAGE_ATTACHMENT_H_
#define MESSAGE_ATTACHMENT_H_

#include <memory>
#include <utility>

namespace tktk
{
	// ���b�Z�[�W�𑗂�Ƃ��ɓn���l���i�[����N���X
	class MessageAttachment
	{
	public:

		MessageAttachment() = default;

		// �Ӑ}�I�Ɂuexplicit�v���O���Ă���
		template<class T>
		MessageAttachment(T value);

		// �R���X�g���N�^�œn�����l�̃|�C���^���擾����
		// ���e���v���[�g�������������Ȃ��^�������ꍇ�A�����؂�̃|�C���^���Ԃ����
		template<class T>
		std::weak_ptr<T> getValuePtr() const;

	private:

		// �|�C���^����������\���̂̃C���^�[�t�F�[�X
		struct PtrCarrierInterface
		{
			virtual ~PtrCarrierInterface() = default;
		};

		// �|�C���^����������\����
		template<class T>
		struct PtrCarrier : public PtrCarrierInterface
		{
			PtrCarrier(const T& value);

			std::shared_ptr<T> m_ptr;
		};

	private:

		// �|�C���^����������\���̂̃|�C���^�i�^���͉B������j
		std::shared_ptr<PtrCarrierInterface> m_ptrCarrier { nullptr };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class T>
	inline MessageAttachment::MessageAttachment(T value)
	{
		m_ptrCarrier = std::make_shared<PtrCarrier<T>>(value);
	}

	// �R���X�g���N�^�œn�����l�̃|�C���^���擾����
	// ���e���v���[�g�������������Ȃ��^�������ꍇ�A�����؂�̃|�C���^���Ԃ����
	template<class T>
	inline std::weak_ptr<T> MessageAttachment::getValuePtr() const
	{
		auto tempPtr = std::dynamic_pointer_cast<PtrCarrier<T>>(m_ptrCarrier);
		if (tempPtr == nullptr) return std::weak_ptr<T>();
		return tempPtr->m_ptr;
	}

	template<class T>
	inline MessageAttachment::PtrCarrier<T>::PtrCarrier(const T& value)
	{
		m_ptr = std::make_shared<T>(value);
	}
}
#endif // !MESSAGE_ATTACHMENT_H_