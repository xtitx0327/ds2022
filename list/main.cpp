#include <iostream>
#include "DoubleLinkedList.h"

/// @brief This function finds value _val in the double linked list _list
/// @tparam DT Abstract data type
/// @param _list An instance of List
/// @param _val The value to be found
/// @return If found, return the iterator of the first node whose value is _val; otherwise, return nullptr
template <typename DT>
typename List <DT> :: iterator find (List <DT> &_list, const DT _val) {
    typename List <DT> :: iterator itr;
    itr = _list.begin ();
    for (int i = 1; i <= _list.size (); ++ i) {
        if (_val == *itr)
            return itr;
        ++ itr;
    }
    return itr; // If not found, the node that itr refers to will be nullptr
}

int main () {
    List <int> l; // Create an instance of double linked list
    for (int i = 1; i <= 5; ++ i) 
        l.push_back (i); // Insert 1 to 5 using push_back
    
    List <int> :: iterator itr;
    itr = l.begin ();
    for (int i = 1; i <= l.size (); ++ i) {
        std :: cout << *itr;
        ++ itr;
    } // Output the list
    std :: cout << std :: endl;

    itr = find (l, 3); 
    l.erase (itr);
    itr = l.begin ();

    for (int i = 1; i <= l.size (); ++ i) {
        std :: cout << *itr;
        ++ itr;
    } // Output the list once again
    std :: cout << std :: endl;

    itr = find (l, 3);

    return 0;
}