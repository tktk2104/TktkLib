#ifndef ANIMATION_LOADER_H_
#define ANIMATION_LOADER_H_

#include <string>
#include <TktkMetaFunc/TypeCheck/isIdType.h>

namespace tktk
{
	// �A�j���[�V������ǂݍ��ޕ⏕�N���X
	class AnimationLoader
	{
	public:

		// �{�[����->�L�[�t���[�����->�{�[�����c�Ɛ��񂵂Ă���o�C�i���f�[�^�̓ǂݍ��ݐ�p�i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), fileName);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName) { static_assert(false, "AnimationId Fraud Type"); }

	private:

		// load()�̎���
		static void loadImpl(int id, const std::string& fileName);
	};
}
#endif // !ANIMATION_LOADER_H_