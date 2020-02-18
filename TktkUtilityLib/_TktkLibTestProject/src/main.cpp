#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkMathLib_mt.lib" )
#pragma comment( lib, "Tktk2dCollisionLib_mt.lib" )
#else
#pragma comment( lib, "TktkMathLib_mtd.lib" )
#pragma comment( lib, "Tktk2dCollisionLib_mtd.lib" )
#endif

#include <iostream>
#include <vector>
#include <forward_list>
#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix3.h>
#include <TktkMath/Matrix4.h>
#include <TktkMath/Quaternion.h>
#include <Tktk2dCollision/BoundingCircle.h>
#include <Tktk2dCollision/BoundingRect.h>
#include <Tktk2dCollision/BoundingPolygon2d.h>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>
#include <ctime>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <vector>
#include <typeindex>
#include <list>

#include <type_traits>
#include <array>

template <class T>
struct TCarrierImpl
{
	static constexpr T* value{ nullptr };
};

template<class T>
constexpr T* TCarrier = TCarrierImpl<T>::value;

class MyClass
{
public:
	template <class T, class... Args>
	MyClass(T*, Args&&... args)
	{
		auto temp = std::make_shared<T>(std::forward<Args>(args)...);

		m_self = temp;
	}

private:

	std::shared_ptr<void> m_self;
};

int main()
{
	MyClass mc = MyClass(TCarrier<int>, 10);

	return 0;
}