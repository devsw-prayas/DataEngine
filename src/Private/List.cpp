#include "../Public/List.h"

namespace core
{
	template<typename E>
	bool List<E>::addAll(E items[]) {
		return addAll(items, 0);
	}

}