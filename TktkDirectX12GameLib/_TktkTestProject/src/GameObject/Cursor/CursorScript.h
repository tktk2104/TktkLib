#ifndef CURSOR_SCRIPT_H_
#define CURSOR_SCRIPT_H_

#include <TktkDX12Game/Component/ComponentBase.h>
#include <TktkDX12Game/Component/DefaultComponents/2DComponents/Transform2D/Transform2D.h>

class CursorScript
	: public tktk::ComponentBase
{
public:

	void start();

	void update();

private:

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !CURSOR_SCRIPT_H_