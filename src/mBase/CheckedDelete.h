#ifndef __H_CHECKED_DELETE__
#define __H_CHECKED_DELETE__

#include <vector>
#include <list>
#include <set>
#include <map>

namespace mBase{
	template < class K, class V > void CheckedDelete(std::map< K, V > & ar_map)
	{
		for (auto itb = ar_map.begin(); itb != ar_map.end(); ++itb)
		{
			CheckedDelete(*itb);
		}
		ar_map.clear();
	}

	template< class T > inline void CheckedDelete(T*& p_ptr)
	{
		if (p_ptr)
		{
			delete p_ptr;
			p_ptr = nullptr;
		}
	}

	template< class T > inline void DeleteArray(T*& p_ptr)
	{
		delete[] p_ptr;
		p_ptr = nullptr;
	}
}

#endif // __H_CHECKED_DELETE__
