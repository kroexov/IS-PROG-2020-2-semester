#include <functional>
template<class iterator, class predicate>
bool allOf(iterator first, iterator last, const predicate &condition) {
    while (first != last) {
        if (!condition(*first))
            return false;
        ++first;
    }
    return true;
}

template<class iterator, class predicate>
bool anyOf(iterator first, iterator last, const predicate &condition) {
    while (first != last) {
        if (condition(*first))
            return true;
        ++first;
    }
    return false;
}

template<class iterator, class predicate>
bool noneOf(iterator first, iterator last, const predicate &condition) {
    while (first != last) {
        if (condition(*first))
            return false;
        ++first;
    }
    return true;
}

template<class iterator, class predicate>
bool oneOf(iterator first, iterator last, const predicate &condition) {
    int num = 0;
    while (first != last) {
        if (condition(*first))
            num++;
        ++first;
    }
    if (num == 1)
        return true;
    else
        return false;
}

//fixed default template parameter
template<class iterator, class criteria = std::less<>>
bool isSorted(iterator first, iterator last, const criteria condition = criteria()) {
    if (first == last)
        return true;

    for (iterator prev = first++; first != last && condition(*prev, *first); prev++, first++); //empty cycle but ok

    return first == last;
}

template<class iterator, class criteria>
bool isPartitioned(iterator first, iterator last, const criteria &condition) {
    if (first == last)
        return false;

    bool start = condition(*first); // either true or false from first element
    bool end = !start;
    for (; first != last && condition(*first) == start; first++); //another empty cycle
    if (first == last)
        return false;
    for (; first != last && condition(*first) == end; first++); //and another empty cycle

    return first == last;
}

template<typename iterator, typename element>
iterator findNot(iterator first, iterator last, const element &indicated) {
    while (first != last && *first == indicated) {
        ++first;
    }
    return first;
}

template<typename iterator, typename element>
iterator findBackward(iterator first, iterator last, const element &indicated) {
    iterator backward = last;
    while (first != last) {
        if (*first == indicated)
            backward = first;
        first++;
    }
    return backward;
}

template<typename iterator, typename criteria>
bool isPalindrome(iterator first, iterator last, const criteria &condition) {
    if (first == last)
        return true;

    while (first != last) {

        last--;

        if (first == last)
            break;

        if (!condition(*first, *last))
            return false;

        ++first;
    }

    return true;
}
