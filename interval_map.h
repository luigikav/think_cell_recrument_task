#pragma once
#include <map>
#include <iostream>

template<typename K, typename V>
class interval_map {
public:
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;
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
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!std::less<K>{}(keyBegin, keyEnd)) // keyBegin should be >= keyEnd
            return;
        if (m_map.empty() && std::equal_to<V>{}(val, m_valBegin))
            return;
        if (!m_map.empty()) {// without this there will be an error, because dereferencing the pointer to end is also an additional heuristic
            auto&& tmp_last = std::prev(m_map.end());
            if(!std::less<K>{}(m_map.begin()->first, keyBegin) // if keyBegin <= first interval
                && !std::less<K>{}(keyEnd, tmp_last->first)  // if keyEnd >= upper_bound
                && std::equal_to<V>{}(val, m_valBegin)) // and val == m_valBegin
                {
                    m_map.clear(); // then need to clear the entire map
                    return;
                }
            if ((!std::less<K>{}(keyBegin, tmp_last->first) || std::less<K>{}(keyEnd, m_map.begin()->first)) && // if keyBegin >= last_interval or keyEnd < first_interval
                std::equal_to<V>{}(val, m_valBegin))
                return;
        }
        auto last = m_map.upper_bound(keyEnd); // get iterator of upper_bound
        if (last == m_map.begin()) // if it's to the right of the rightmost interval
            last = m_map.insert(last, std::make_pair(keyEnd, m_valBegin));
        else
        {
            // else we need to define value_before
            auto&& value_before = std::prev(last)->second;
            last = m_map.insert(last, std::make_pair(keyEnd, value_before));
        }
        auto first = m_map.lower_bound(keyBegin); // find lower_bound
        // if keyBegin <= leftmost interval and val == m_valBegin, then we should erase every interval which < keyEnd (our last upper_bound)
        if (!std::less<K>{}(m_map.begin()->first, keyBegin) && std::equal_to<V>{}(val, m_valBegin))
        {
            m_map.erase(first, last);
            return;
        }
        
        if (first != m_map.begin()) // if we insert somewhere in the middle, then we may need to merge the intervals
            if (!std::less<K>{}(first->first, keyBegin)) // if keyBegin >= lower_bound which is already in the map, then we need to merge
            {
                if (std::equal_to<V>{}(std::prev(first)->second, val)) // if prev interval has the same value, then it should be merge (else we need just swap lower_bound's val)
                {
                    if (std::equal_to<V>{}(last->second, val)) // if after upper_bound we have same value
                        m_map.erase(first, std::next(last)); //then we should merge 3 interval (prev, cur, next)
                    else
                        m_map.erase(first, last); // else merge 2 intervals: (prev and cur)
                    return;
                }

            }
        // if previous relative to the upper limit val same as we insert, then we need merge
        if (std::equal_to<V>{}(first->second, val)) 
        {
            m_map.insert(first, std::make_pair(std::move(keyBegin), std::move(val)));
            if (std::equal_to<V>{}(last->second, val) && // upper_bound value same as we got
                !std::less<K>{}(keyEnd, last->first)) // and KeyEnd >= upper_bound
                m_map.erase(first, std::next(last)); // then merge 3 intervals (prev (relative to the upper limit), cur, next)
            else
                m_map.erase(first, last); // else merge 2 intervals (prev (relative to the upper limit), cur)
        }
        else
        {
            m_map.erase(first, last);
            m_map.insert(last, std::make_pair(std::move(keyBegin), std::move(val)));
        }

    

    }

    V const& operator[](K const& key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return m_valBegin;
        }
        else {
            return (--it)->second;
        }
    }


    void PrintMap() {
        for (auto const& pair : m_map) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
    }

    void PrintValBegin() {
        std::cout << m_valBegin;
    }
private:
    
};
template<typename K, typename V>
void PrintRange(int start, int end, interval_map<K, V> m) {
    for (int i = start; i <= end; i++) {
        std::cout << "Key: " << i << " Value: " << m[i] << std::endl;
    }
}
template<typename K, typename V>
void Print(interval_map<K, V> m) {
    std::cout << std::endl << "Range" << std::endl;
    PrintRange(-5, 30, m);
    std::cout << std::endl << "Map" << std::endl;
    std::cout << "{: ";
    m.PrintValBegin();
    std::cout << "}" << std::endl;
    m.PrintMap();
}






template <class T>
class A {
private:
    T a;
public:
    A(T t) :a(t) {};

    A() = delete;
    friend bool operator<(const A& l, const A& r)
    {
        return l.a < r.a;
    }
    friend std::ostream& operator<< (std::ostream& stream, const A& m)
    {
        return stream << m.a;
    }
};
template <class T>
class B
{
private:
    T b;
public:
    B(T t) :b(t) {};

    B() = delete;
    friend bool operator==(const B& lhs, const B& rhs)
    {
        return lhs.b == rhs.b;
    }
    friend std::ostream& operator<< (std::ostream& stream, const B& m)
    {
        return stream << m.b;
    }
};