#ifndef MOVIE_PLAYER_H_
#define MOVIE_PLAYER_H_

#include <memory>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Assets/MovieAssets/MovieAssets.h"
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"
#include "../Sprite/ReverseFlag.h"

namespace tktk
{
	class MoviePlayer
		: public ComponentBase
	{
	public:

		MoviePlayer(
			float drawPriority,						// �`��D��x
			int movieId,							// �`�悷�铮���Id
			const Vector2& movieCenterPosRate,		// ����̒��S�ʒu�i���� 0.0�`1.0�j
			BlendMode blendMode,					// �`��̃u�����h���@�̎��
			float blendParam,						// �`��̃u�����h�Ɏg�p����l
			unsigned int reverseFlag,				// �`�悷�铮��𔽓]���邩
			bool useClipping,						// �ؔ����`����s�����H
			const Vector2& clippingLeftTopPos,		// �؂蔲��������W
			const Vector2& clippingRightBottomPos	// �؂蔲���E�����W
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// ���[�r�[ID���擾
		int getMovieId() const;
		// ���[�r�[ID�̍Đݒ�
		void setMovieId(int movieId);

		// ����̒��S�ʒu�i���� 0.0�`1.0�j���擾
		const Vector2& getMovieCenterPosRate() const;
		// ����̒��S�ʒu�i���� 0.0�`1.0�j���Đݒ�
		void setMovieCenterPosRate(const Vector2& movieCenterPosRate = Vector2(0.5f, 0.5f));

		// �����؂蔲���ĕ\������
		void useClipping(
			const Vector2& clippingLeftTopPos,		// �؂蔲��������W
			const Vector2& clippingRightBottomPos	// �؂蔲���E�����W
		);
		// �����؂蔲���ĕ\������̂���߂�
		void unUseClipping();

		// �`��̃u�����h���@�̎�ނ��擾
		BlendMode getBlendMode() const;
		// �`��̃u�����h���@�̎�ނ��Đݒ�
		void setBlendMode(BlendMode blendMode);

		// �`��̃u�����h�Ɏg�p����l���擾
		float getBlendParam() const;
		// �`��̃u�����h�Ɏg�p����l���Đݒ�
		void setBlendParam(float blendParam);

		// �`�悷�铮��̔��]�t���O���Đݒ�
		void setReverseFlag(unsigned int reverseFlag);

		// �w�肵�������_�[�^�[�Q�b�g�ɕ`�悷��
		void useRenderTarget(int renderTargetId);
		// �����_�[�^�[�Q�b�g���g�p�����ɕ`�悷��
		void unUseRenderTarget();

	private:

		// ���g�̂Q�������W�R���|�[�l���g
		std::weak_ptr<Transform2D> m_transform2D;

		// ���惊�\�[�X�̊Ǘ��N���X
		std::weak_ptr<MovieAssets> m_movieAssets;

		// �\�����铮���Id
		int m_movieId{ -1 };

		// �X�v���C�g�̒��S�ʒu�i���� 0.0�`1.0�j
		Vector2 m_movieCenterPosRate{ Vector2(0.5f, 0.5f) };

		// �`��̃u�����h���@�̎��
		BlendMode m_blendMode;

		// �`��̃u�����h�Ɏg�p����l
		float m_blendParam;

		// ���]�t���O
		unsigned int m_reverseFlag{ NOT_REVERSE };

		// ����̐ؔ������s����
		bool m_useClipping{ false };

		// ����̐ؔ����Ɏg�p���鍶����W
		Vector2 m_clippingLeftTopPos{ Vector2::zero };

		// ����̐ؔ����Ɏg�p����E�����W
		Vector2 m_clippingRightBottomPos{ Vector2::one };

		// �����_�[�^�[�Q�b�g�ɕ`�悷�邩
		bool m_useRenderTarget{ false };

		// �`�悷�郌���_�[�^�[�Q�b�g��Id
		int m_renderTargetId{ -1 };
	};
}
#endif // !MOVIE_PLAYER_H_