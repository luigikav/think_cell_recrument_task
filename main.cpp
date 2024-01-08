#include <map>
#include <iostream>

template<typename K, typename V>

class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
		
        // (Since an entry for the default value was not implemented in the constructor of 
		// the example, as it is stated in the task description. 
        // I will add an entry encopasing all possibilities with the m_valBegin
		if (m_map.empty() )
		{
            if (m_valBegin)
            {
                m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), m_valBegin));
            } 
            else
            {
                throw std::invalid_argument("Error, failed to add default value)
            }
		}
		
		// Return if given a non-valid range
		if (!(keyBegin < keyEnd)) return;
		
        // Define an iterator type for the map (as we will be using it a couple of times, and auto isn't readable) 
		using iter = typename decltype(m_map)::iterator;

		// Find the iterator pointing to the end of the input range in the map
		iter itEnd = m_map.find(keyEnd);
		// Adjust the value at the end of the range based on the lower bound of keyEnd
		if (iter tmp = m_map.lower_bound(keyEnd); itEnd != m_map.end() )
			itEnd->second = tmp->second;
		else
			itEnd = m_map.insert(m_map.end(), std::make_pair(keyEnd, (--tmp)->second));

		// Insert or assign the value for the beginning of the input range
		iter itBegin = m_map.insert_or_assign(keyBegin, val).first;

		// Remove any elements between the beginning and end of the new range
		m_map.erase(std::next(itBegin), itEnd);
    
		// Make the mapping canonical by removing redundant entries with the same value (going from last to first iter)
		iter itRight = itEnd;
		iter itLeft = (itBegin != m_map.begin() ? std::prev(itBegin) : itBegin);
		while (itRight != itLeft) {
		    iter itNext = std::prev(itRight);
			if (itRight->second == itNext->second)
				m_map.erase(itRight);
			itRight = itNext;
		}
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};

void IntervalMapTest() {
    // Test 1: Creating an interval_map with a default value
    interval_map<int, char> myMap('d');
    
    std::cout << "Init Map:" << std::endl;
    myMap.assign(1, 5, myMap.m_valBegin);
    for (const auto& pair : myMap.m_map) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
    
    // Test 2: Assigning values to intervals
    myMap.assign(1, 5, 'A');
    myMap.assign(10, 15, 'B');
    myMap.assign(20, 25, 'C');
    
    std::cout << "filled with gaps map:" << std::endl;
    for (const auto& pair : myMap.m_map) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }


    // Test 4: Assigning values to overlapping intervals
    myMap.assign(4, 8, 'X');
    myMap.assign(5, 10, 'X');
    std::cout << "overlapped vals map:" << std::endl;
    for (const auto& pair : myMap.m_map) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
    
    // Test 6: Assigning values to an negative interval (should do nothing)
    myMap.assign(15, 10, 'Y');
    
    std::cout << "added vals to map:" << std::endl;
    for (const auto& pair : myMap.m_map) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
    
    std::cout << "testVal: " << myMap[3] << std::endl;
}

int main() {
    IntervalMapTest();

    return 0;
}
