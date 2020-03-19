#ifndef TEXT_DRAWER_H_
#define TEXT_DRAWER_H_

#include <string>
#include <vector>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
namespace tktk
{
	// �e�L�X�g�`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform2D�z
	class TextDrawer
		: public ComponentBase
	{
	public:

		TextDrawer(
			float drawPriority,
			const std::string& initText
		);

	public:

		void update();

	public:

		const std::string& getText() const;

		void setText(const std::string& newText);

	private:

		float m_drawPriority;
		std::string m_text;
		std::vector<GameObjectPtr> m_charObjectArray;
	};
}
#endif // !TEXT_DRAWER_H_