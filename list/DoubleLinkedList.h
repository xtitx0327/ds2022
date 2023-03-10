#include <iostream>

template <typename DT>
class List {
    private:
        struct Node {
            DT data;
            Node *prev;
            Node *next;
            Node (const DT &d = DT{}, Node *p = nullptr, Node *n = nullptr)
                : data {d}, prev {p}, next {n} {}
            Node (DT &&d, Node *p = nullptr, Node *n = nullptr)
                : data {std::move (d)}, prev {p}, next {n} {}
        };
    
    public:
        class const_iterator {
            public:
                const_iterator () : current {nullptr} {}
                
                const DT &operator * () const {
                    return retrieve ();
                }

                const_iterator &operator ++ () {
                    current = current -> next;
                    return *this;
                }

                const_iterator operator ++ (int) {
                    const_iterator old = *this;
                    ++ (*this);
                    return old;
                }
                bool operator == (const const_iterator &rhs) const {
                    return current == rhs.current;
                }
                bool operator != (const const_iterator &rhs) const {
                    return ! (*this == rhs);
                }
            
            protected:
                Node *current;

                DT &retrieve () const {
                    return current -> data;
                }

                const_iterator (Node *p) : current {p} {}

                friend class List <DT>;
        };

        class iterator : public const_iterator {
            public:
                iterator () {}

                DT & operator * () {
                    return const_iterator::retrieve ();
                }
                const DT & operator * () const {
                    return const_iterator::operator* ();
                }

                iterator & operator ++ () {
                    this -> current = this -> current -> next;
                    return *this;
                }

                iterator operator ++ (int) {
                    iterator old = *this;
                    ++ (*this);
                    return old;
                }

            protected:
                iterator (Node *p) : const_iterator {p} {}

                friend class List <DT>;
        };

    public:
        List () {
            init ();
        }
        List (const List &rhs) {
            init ();
            for (auto & x : rhs)
                push_back (x);
        }
        ~List () {
            clear ();
            delete head;
            delete tail;
        }
        List &operator = (const List &rhs) {
            List copy = rhs;
            std::swap (*this, copy);
            return *this;
        }

        List (List && rhs) : theSize {rhs.theSize}, head {rhs.head}, tail{rhs.tail} {
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }

        List &operator = (List && rhs) {
            std::swap (theSize, rhs.theSize);
            std::swap (head, rhs.head);
            std::swap (tail, rhs.tail);

            return *this;
        }

        /// @brief This functions returns the iterator of the first node of the linked list
        /// @return An iterator of the first node of the linked list
        iterator begin () {
            return {head -> next};
        }
        const_iterator begin () const {
            return {head -> next};
        }

        /// @brief This functions returns the iterator of the last node of the linked list
        /// @return An iterator of the last node of the linked list
        iterator end () {
            return {tail};
        }
        const_iterator end () const {
            return {tail};
        }

        /// @brief This function gives the size of the list
        /// @return The size of the list
        int size() const {
            return theSize;
        }
        /// @brief Judges whether the list is empty
        /// @return Returns 1 if the list is empty and vice versa
        bool empty() const {
            return size () == 0;
        }

        /// @brief Make the list empty
        void clear () {
            while (!empty ())
                pop_front ();
        }

        /// @brief This function gets the value of the first node of the linked list
        /// @return The value of the first node of the linked list
        DT &front () {
            return *begin();
        }
        const DT & front () const {
            return *begin();
        }

        /// @brief This function gets the value of the last node of the linked list
        /// @return The value of the last node of the linked list
        DT &back () {
            return *--end ();
        }
        const DT & back() const {
            return *--end ();
        }

        /// @brief Create a node in the front of the list
        /// @param x The value contained the node to be inserted
        void push_front (const DT &x) {
            insert (begin(), x);
        }
        void push_front (DT &&x) {
            insert (begin (), std::move (x));
        }

        /// @brief Create a node in the back of the list
        /// @param x The value contained the node to be inserted
        void push_back (const DT &x) {
            insert (end (), x);
        }
        void push_back (DT &&x) {
            insert (end (), std::move (x));
        }

        /// @brief Delete the node in the front of the list
        void pop_front () {
            erase (begin ());
        }

        /// @brief Delete the node in the back of the list
        void pop_back () {
            erase (--end ());
        }

        /// @brief Insert a node before a certain node
        /// @param itr The node inserted before the node referred to itr
        /// @param x The value of the node to be inserted
        /// @return The iterator of the node to be inserted
        iterator insert (iterator itr, const DT &x) {
            Node *p = itr.current;
            theSize ++;
            return {p -> prev = p -> prev -> next = new Node {x, p -> prev, p}};
        }

        /// @brief Insert a node before a certain node
        /// @param itr The node inserted before the node referred to itr
        /// @param x The value of the node to be inserted
        /// @return The iterator of the node to be inserted
        iterator insert (iterator itr, DT &&x) {
            Node *p = itr.current;
            theSize++;
            return {p -> prev = p -> prev -> next = new Node {std::move (x), p -> prev, p}};
        }

        /// @brief Erase item at itr
        /// @param itr The iterator of the node to be erased
        /// @return The iterator of the next node of the node to be erased
        iterator erase (iterator itr) {
            Node *p = itr.current;
            iterator retVal {p -> next};
            p -> prev -> next = p -> next;
            p -> next -> prev = p -> prev;
            delete p;
            theSize --;

            return retVal;
        }

        /// @brief Erase item from "from" to "to"
        /// @param from The iterator of the first node to be erased
        /// @param to The iterator of the last node to be erased
        /// @return The iterator of the next node of the node whose iterator is "to"
        iterator erase (iterator from, iterator to) {
            for (iterator itr = from; itr != to; )
                itr = erase (itr);
            
            return to;
        }
    
    private:
        int theSize;
        Node *head;
        Node *tail;

        void init () {
            theSize = 0;
            head = new Node;
            tail = new Node;
            head -> next = tail;
            tail -> prev = head;
        }
};