#pragma once

#include <TktkMath/Structs/Color.h>
#include <TktkDX12Game/Component/ComponentBase.h>

class ElementColorChanger
	: public tktk::ComponentBase
{
public:

	ElementColorChanger(
		const tktkMath::Color& color,
		unsigned int id
	);

public:

	void start();

	void update();

public:

	const tktkMath::Color& getColor() const;

private:

	tktkMath::Color m_color;
	unsigned int	m_id;
};