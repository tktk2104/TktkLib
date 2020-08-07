#include "ElementColorChanger.h"

ElementColorChanger::ElementColorChanger(
	const tktkMath::Color& color,
	unsigned int id
)
	: m_color(color)
	, m_id(id)
{
}

void ElementColorChanger::start()
{
	/*tktk::Material::getDataPtr(m_id)->getParametersRef().setConstantBufferSetData(
		tktk::SystemConstantBufferId::MonoColor,
		tktk::MonoColorConstantBufferData({ m_color })
	);*/
}

void ElementColorChanger::update()
{
	
}

const tktkMath::Color & ElementColorChanger::getColor() const
{
	return m_color;
}