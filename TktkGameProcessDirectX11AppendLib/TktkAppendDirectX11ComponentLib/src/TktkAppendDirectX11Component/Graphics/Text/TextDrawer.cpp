#include "TktkAppendDirectX11Component/Graphics/Text/TextDrawer.h"

#include <TktkComponentFramework/GameObject/GameObjectManager.h>
#include <TktkAppend2DComponent/Transform2DMaker.h>
#include "TktkAppendDirectX11Component/Graphics/Sprite/SpriteDrawerMaker.h"
#include "TktkDirectX11Wrapper/Graphics/Text/FontLoader.h"

namespace tktk
{
	TextDrawer::TextDrawer(float drawPriority, const std::string & initText)
		: m_drawPriority(drawPriority)
		, m_text(initText)
	{
		m_charObjectArray.reserve(m_text.size());
	}

	void TextDrawer::update()
	{
		unsigned int i;

		for (i = 0; i < m_text.size(); i++)
		{
			if (m_charObjectArray.size() < (i + 1))
			{
				auto gameObject = GameObjectManager::createGameObject(false);
				Transform2DMaker::makeStart(gameObject)
					.position(Vector2(30.0f * i, 0.0f))
					.create();

				SpriteDrawerMaker::makeStart(gameObject)
					.drawPriority(m_drawPriority)
					.textureId(FontLoader::getCharTextureId("ÑMÇrÅ@Çoñæí©", &m_text.at(i)))
					.create();

				getGameObject()->addChild(gameObject);

				m_charObjectArray.push_back(gameObject);
			}
			else
			{
				auto charObject = m_charObjectArray.at(i);
				charObject->setActive(true);
				auto charDrawer = charObject->getComponent<SpriteDrawer>();
				charDrawer->setTextureId(FontLoader::getCharTextureId("ÑMÇrÅ@Çoñæí©", &m_text.at(i)));
			}
		}

		for (unsigned int j = i; j < m_charObjectArray.size(); j++)
		{
			m_charObjectArray.at(j)->setActive(false);
		}
	}

	const std::string & TextDrawer::getText() const
	{
		return m_text;
	}

	void TextDrawer::setText(const std::string & newText)
	{
		m_text = newText;
	}
}