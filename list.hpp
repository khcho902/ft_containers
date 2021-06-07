/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:10:24 by kycho             #+#    #+#             */
/*   Updated: 2021/06/07 10:38:31 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <iterator>
# include "reverse_iterator.hpp"
# include "utils.hpp"

namespace ft
{
    struct _list_node_base
    {
        _list_node_base* next;
        _list_node_base* prev;

        static void swap(_list_node_base& x, _list_node_base& y)
        {
            if (x.next != &x)
            {
                if (y.next != &y)
                {
                    // Both x and y are not empty.
                    ft::swap(x.next, y.next);
                    ft::swap(x.prev, y.prev);
                    x.next->prev = x.prev->next = &x;
                    y.next->prev = y.prev->next = &y;
                }
                else
                {
                    // x is not empty, y is empty.
                    y.next = x.next;
                    y.prev = x.prev;
                    y.next->prev = y.prev->next = &y;
                    x.next = x.prev = &x;
                }
            }
            else if (y.next != &y)
            {
                // x is empty, y is not empty.
                x.next = y.next;
                x.prev = y.prev;
                x.next->prev = x.prev->next = &x;
                y.next = y.prev = &y;
            }
        }

        // [first, last) 를 this앞으로 이동 시킨다. 
        void _transfer(_list_node_base* const first, _list_node_base* const last)
        {
            if (this != last)
            {
                _list_node_base* const first_prev = first->prev;
                _list_node_base* const last_prev = last->prev;
                _list_node_base* const this_prev = this->prev;

                first_prev->next = last;
                last->prev = first_prev;

                this_prev->next = first;
                first->prev= this_prev;

                last_prev->next = this;
                this->prev = last_prev;
            }
        }

        void _hook(_list_node_base* const position)
        {
            this->next = position;
            this->prev = position->prev;
            position->prev->next = this;
            position->prev = this;
        }

        void _unhook()
        {
            _list_node_base* const _next_node = this->next;
            _list_node_base* const _prev_node = this->prev;
            _prev_node->next = _next_node;
            _next_node->prev = _prev_node;
        }
    };

    template <typename T>
    struct _list_node : public _list_node_base
    {
        T data;
        _list_node(T data) : data(data) {}
    };

    // ############## list iterator ############################################################
    template<typename T>
    struct _list_iterator
    {
        typedef _list_iterator<T>                   _Self;
        typedef _list_node<T>                       _Node;
        
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef std::bidirectional_iterator_tag     iterator_category;

        _list_node_base* node_ptr;

        _list_iterator() : node_ptr() {}
        _list_iterator(_list_node_base* _x) : node_ptr(_x) {}
        
        reference operator*() const
        {
            return static_cast<_Node*>(node_ptr)->data;
        }
        
        // TODO : __addressof 사용하는거 확인해봐야함 
        pointer operator->() const
        {
            return std::addressof(static_cast<_Node*>(node_ptr)->data);
        }
        
        _Self& operator++()
        {
            node_ptr = node_ptr->next;
            return *this;
        }

        _Self operator++(int)
        {
            _Self _tmp = *this;
            node_ptr = node_ptr->next;
            return _tmp;
        }
        
        _Self& operator--()
        {
            node_ptr = node_ptr->prev;
            return *this;
        }
        
        _Self operator--(int)
        {
            _Self _tmp = *this;
            node_ptr = node_ptr->prev;
            return _tmp;
        }
        
        bool operator==(const _Self& _x) const
        {
            return node_ptr == _x.node_ptr;
        }
        
        bool operator!=(const _Self& _x) const
        {
            return node_ptr != _x.node_ptr;
        }
    };

    // ############## list const iterator #######################################################
    template<typename T>
    struct _list_const_iterator
    {
        typedef _list_const_iterator<T>             _Self;
        typedef const _list_node<T>                 _Node;
        typedef _list_iterator<T>                   iterator;
        
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef const T*                            pointer;
        typedef const T&                            reference;
        typedef std::bidirectional_iterator_tag     iterator_category;

        const _list_node_base* node_ptr;

        _list_const_iterator() : node_ptr() {}
        explicit _list_const_iterator(const _list_node_base* _x) : node_ptr(_x) {}  // TODO : 왜 explicit 붙이는거지 ??
        _list_const_iterator(const iterator& _x) : node_ptr(_x.node_ptr) {}
        
        reference operator*() const
        {
            return static_cast<_Node*>(node_ptr)->data;
        }
        
        // TODO : __addressof 사용하는거 확인해봐야함 
        pointer operator->() const
        {
            return std::addressof(static_cast<_Node*>(node_ptr)->data);
        }
        
        _Self& operator++()
        {
            node_ptr = node_ptr->next;
            return *this;
        }

        _Self operator++(int)
        {
            _Self _tmp = *this;
            node_ptr = node_ptr->next;
            return _tmp;
        }
        
        _Self& operator--()
        {
            node_ptr = node_ptr->prev;
            return *this;
        }
        
        _Self operator--(int)
        {
            _Self _tmp = *this;
            node_ptr = node_ptr->prev;
            return _tmp;
        }
        
        bool operator==(const _Self& _x) const
        {
            return node_ptr == _x.node_ptr;
        }
        
        bool operator!=(const _Self& _x) const
        {
            return node_ptr != _x.node_ptr;
        }
    };

    template <typename T>
    inline bool operator==(const _list_iterator<T> &lhs, const _list_const_iterator<T> &rhs)
    {
        return lhs.node_ptr == rhs.node_ptr;
    }

    template <typename T>
    inline bool operator!=(const _list_iterator<T> &lhs, const _list_const_iterator<T> &rhs)
    {
        return lhs.node_ptr != rhs.node_ptr;
    }

    // ############## list class ###############################################################
    template <class T, class Alloc = std::allocator<T> >
    class list
    {
    public:
    // ########## Member types ##########
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        
        typedef _list_iterator<T>                           iterator;
        typedef _list_const_iterator<T>                     const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

        // iterator_traits<iterator>::difference_type
        typedef ptrdiff_t                                   difference_type;
        //an unsigned integral type that can represent any non-negative value of difference_type
        typedef size_t                                      size_type;
    

    protected:
        typedef _list_node<T>                                           _Node;
        typedef typename Alloc::template rebind<_list_node<T> >::other  _node_alloc_type;
        

        _node_alloc_type    node_allocator;
        _list_node_base     sentry_node;

        // TODO : 제대로 된건지 테스트필요 
        _Node* _create_node(const value_type& val)
        {
            _Node* _p = node_allocator.allocate(1);
            node_allocator.construct(_p, _Node(val));
            _p->data = val;
            return _p;
        }

        void _init()
        {
            this->sentry_node.next = &(this->sentry_node);
            this->sentry_node.prev = &(this->sentry_node);
        }

        void _clear()
        {
            _Node* _cur = static_cast<_Node*>(this->sentry_node.next);
            
            while (_cur != &(this->sentry_node))
            {
                _Node* _tmp = _cur;
                _cur = static_cast<_Node*>(_cur->next);

                node_allocator.destroy(_tmp);
                node_allocator.deallocate(_tmp, 1);
            }
        }

        void _erase(iterator _position)
        {
            _position.node_ptr->_unhook();
            _Node* _n = static_cast<_Node*>(_position.node_ptr);
            node_allocator.destroy(_n);
            node_allocator.deallocate(_n, 1);
        }

        void _fill_initialize(size_type n, const value_type& val)
        {
            for (; n; --n)
            {
                push_back(val);
            }
        }

        template<typename Integer>
        void _initialize_dispatch(Integer n, Integer val, ft::true_type)
        {
            _fill_initialize(static_cast<size_type>(n), val);
        }

        template<typename InputIterator>
        void _initialize_dispatch(InputIterator first, InputIterator last, ft::false_type)
        {
            for (; first != last; ++first)
            {
                push_back(*first);
            }
        }

        void _fill_assign(size_type n, const value_type& val)
        {
            iterator i = begin();
            const iterator end_i = end();

            for (; i != end_i && n > 0; ++i, --n)
                *i = val;

            if (n > 0)
                insert(end_i, n, val);
            else
                erase(i, end_i);
        }

        template<typename Integer>
        void _assign_dispatch(Integer n, Integer val, ft::true_type)
        {
            _fill_assign(n, val);
        }

        template<typename InputIterator>
        void _assign_dispatch(InputIterator first, InputIterator last, ft::false_type)
        {
            iterator i = begin();
            const iterator end_i = end();

            for (; i != end_i && first != last; ++i, ++first)
                *i = *first;
            
            if (first == last)
                erase(i, end_i);
            else
                insert(end_i, first, last);
        }


    public:
    // ########## (constructor) ##########
        //default (1)	
        explicit list(const allocator_type& alloc = allocator_type());
        //fill (2)	
        explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
        //range (3)	
        template <class InputIterator>
        list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
        //copy (4)	
        list(const list& x);

    // ########## (destructor) ##########
        ~list();

    // ########## operator= ##########
        list& operator=(const list& x);

    // ########## Iterators: ##########
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;    

    // ########## Capacity: ##########
        bool empty() const;
        size_type size() const;
        size_type max_size() const;

    // ########## Element access: ##########
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;

    // ########## Modifiers: ##########
        //range (1)	
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last);
        //fill (2)	
        void assign(size_type n, const value_type& val);
        void push_front(const value_type& val);
        void pop_front();
        void push_back(const value_type& val);
        void pop_back();
        //single element (1)	
        iterator insert(iterator position, const value_type& val);
        //fill (2)	
        void insert(iterator position, size_type n, const value_type& val);
        //range (3)	
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        void swap(list& x);
        void resize(size_type n, value_type val = value_type());
        void clear();
    
    // ########## Operations: ##########
        //entire list (1)	
        void splice(iterator position, list& x);
        //single element (2)	
        void splice(iterator position, list& x, iterator i);
        //element range (3)	
        void splice(iterator position, list& x, iterator first, iterator last);
        void remove(const value_type& val);
        template <class Predicate>
        void remove_if(Predicate pred);
        //(1)	
        void unique();
        //(2)	
        template <class BinaryPredicate>
        void unique(BinaryPredicate binary_pred);
        //(1)	
        void merge(list& x);
        //(2)	
        template <class Compare>
        void merge(list& x, Compare comp);
        //(1)
        void sort();
        //(2)
        template <class Compare>
        void sort(Compare comp);
        void reverse();

    /*
    // ########## Allocator: ##########
        allocator_type get_allocator() const;
    */
    
    };

    // ########## (constructor) ##########
    //default (1)
    template <class T, class Alloc>
    list<T, Alloc>::list(const allocator_type& alloc) :
        node_allocator(alloc),
        sentry_node()
    {
        _init();
    }
    //fill (2)
    template <class T, class Alloc>
    list<T, Alloc>::list(size_type n, const value_type& val, const allocator_type& alloc) :
        node_allocator(alloc),
        sentry_node()
    {
        _init();
        _fill_initialize(n, val);
    }
    //range (3)
    template <class T, class Alloc>
    template <class InputIterator>
    list<T, Alloc>::list::list(InputIterator first, InputIterator last, const allocator_type& alloc) :
        node_allocator(alloc),
        sentry_node()
    {
        _init();
        typedef typename ft::is_integer<InputIterator>::type is_integer_type;
        _initialize_dispatch(first, last, is_integer_type());
    }
    //copy (4)
    template <class T, class Alloc>
    list<T, Alloc>::list::list(const list& x) :
        node_allocator(x.node_allocator),
        sentry_node()
    {
        _init();
        _initialize_dispatch(x.begin(), x.end(), ft::false_type());
    }

    // ########## (destructor) ##########
    template <class T, class Alloc>
    list<T, Alloc>::list::~list()
    {
        _clear();
    }

    // ########## operator= ##########
    template <class T, class Alloc>
    list<T, Alloc>& list<T, Alloc>::operator=(const list& x)
    {
        if (this != &x)
        {
            iterator first1 = begin();
            iterator last1 = end();
            const_iterator first2 = x.begin();
            const_iterator last2 = x.end();
            for (; first1 != last1 && first2 != last2; ++first1, ++first2)
                *first1 = *first2;
            if (first2 == last2)
                erase(first1, last1);
            else
                insert(last1, first2, last2);
        }
        return *this;
    }

    // ########## Iterators: ##########
    template <class T, class Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::begin()
    {
        return iterator(this->sentry_node.next);
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::begin() const
    {
        return const_iterator(this->sentry_node.next);
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::end()
    {
        return iterator(&(this->sentry_node));
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::end() const
    {
        return const_iterator(&(this->sentry_node));
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rbegin()
    {
        return reverse_iterator(end());
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rbegin() const
    {
        return const_reverse_iterator(end());
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rend()
    {
        return reverse_iterator(begin());
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rend() const
    {
        return const_reverse_iterator(begin());
    }

    // ########## Capacity: ##########
    template <class T, class Alloc>
    bool list<T, Alloc>::empty() const
    {
        return this->sentry_node.next == &(this->sentry_node);
    }
    
    // TODO : distance를 사용하는 방법으로 개선
    template <class T, class Alloc>
    typename list<T, Alloc>::size_type list<T, Alloc>::size() const
    {
        typename list<T, Alloc>::size_type size = 0;
        typename list<T, Alloc>::const_iterator begin_it = this->begin();
        typename list<T, Alloc>::const_iterator end_it = this->end();
        
        while(begin_it != end_it)
        {
            size++;
            begin_it++;
        }
        return size;
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::size_type list<T, Alloc>::max_size() const
    {
        return this->node_allocator.max_size();
    }

    // ########## Element access: ##########
    template <class T, class Alloc>
    typename list<T, Alloc>::reference list<T, Alloc>::front()
    {
        return *begin();
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::const_reference list<T, Alloc>::front() const
    {
        return *begin();
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::reference list<T, Alloc>::back()
    {
        iterator tmp = end();
        --tmp;
        return *tmp;
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::const_reference list<T, Alloc>::back() const
    {
        const_iterator tmp = end();
        --tmp;
        return *tmp;
    }

    // ########## Modifiers: ##########
    //range (1)
    template <class T, class Alloc>
    template <class InputIterator>
    void list<T, Alloc>::assign(InputIterator first, InputIterator last)
    {
        typedef typename ft::is_integer<InputIterator>::type is_integer_type;
        _assign_dispatch(first, last, is_integer_type());
    }

    //fill (2)
    template <class T, class Alloc>
    void list<T, Alloc>::assign(size_type n, const value_type& val)
    {
        _fill_assign(n, val);
    }

    template <class T, class Alloc>
    void list<T, Alloc>::push_front(const value_type& val)
    {
       _Node* tmp = _create_node(val);
       tmp->_hook(begin().node_ptr);
    }

    template <class T, class Alloc>
    void list<T, Alloc>::pop_front()
    {
       _erase(begin());
    }

    template <class T, class Alloc>
    void list<T, Alloc>::push_back(const value_type& val)
    {
        _Node* tmp = _create_node(val);
        tmp->_hook(end().node_ptr);
    }
    
    template <class T, class Alloc>
    void list<T, Alloc>::pop_back()
    {
        iterator i = end();
        i--;
        _erase(i);
    }

    //single element (1)
    template <class T, class Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::insert(iterator position, const value_type& val)
    {
        _Node * tmp = _create_node(val);
        tmp->_hook(position.node_ptr);
        return iterator(tmp);
    }
    //fill (2)
    template <class T, class Alloc>
    void list<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
    {
        list tmp(n, val);
        splice(position, tmp);
    }
    //range (3)
    template <class T, class Alloc>
    template <class InputIterator>
    void list<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
    {
        list tmp(first, last);
        splice(position, tmp);
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::erase(iterator position)
    {
        iterator _ret = iterator(position.node_ptr->next);
        _erase(position);
        return _ret;
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::erase(iterator first, iterator last)
    {
        while (first != last)
        {
            first = erase(first);       
        }
        return last;
    }

    template <class T, class Alloc>
    void list<T, Alloc>::swap(list& x)
    {
        _list_node_base::swap(sentry_node, x.sentry_node);
        
        // TODO : 확인필요
        _node_alloc_type tmp = this->node_allocator;
        this->node_allocator = x.node_allocator;
        x.node_allocator = tmp;
    }

    template <class T, class Alloc>
    void list<T, Alloc>::resize(size_type n, value_type val)
    {
       size_type list_size = size();

       if (list_size == n)
           return;
       
       if (list_size < n)
           insert(end(), n - list_size, val);
       else
       {
           iterator i = begin();
           while (n-- > 0)
               i++;
           erase(i, end());
       }
    }

    template <class T, class Alloc>
    void list<T, Alloc>::clear()
    {
        _clear();
        _init();
    }

    // ########## Operations: ##########
    //entire list (1)
    template <class T, class Alloc>
    void list<T, Alloc>::splice(iterator position, list& x)
    {
        if (x.empty())
            return;
        position.node_ptr->_transfer(x.begin().node_ptr, x.end().node_ptr);
    }
    //single element (2)
    template <class T, class Alloc>
    void list<T, Alloc>::splice(iterator position, list& x, iterator i)
    {
        if ((void *)&x == NULL) // TODO : x 사용안해서 일단 넣음 
            return ;
        iterator j = i;
        ++j;
        if (position == i || position == j)
            return;
        position.node_ptr->_transfer(i.node_ptr, j.node_ptr);
    }
    //element range (3)
    template <class T, class Alloc>
    void list<T, Alloc>::splice(iterator position, list& x, iterator first, iterator last)
    {
        if ((void *)&x == NULL) // TODO : x 사용안해서 일단 넣음 
            return ;
        if (first == last)
            return;
        position.node_ptr->_transfer(first.node_ptr, last.node_ptr);
    }

    template <class T, class Alloc>
    void list<T, Alloc>::remove(const value_type& val)
    {
        iterator first = begin();
        iterator last = end();
        iterator extra = last;

        while (first != last)
        {
            iterator next = first;
            ++next;
            
            if (*first == val)
            {
                if (std::addressof(*first) != std::addressof(val))
                    _erase(first);
                else
                    extra = first;
            }
            first = next;
        }
        if (extra != last)
            _erase(extra);
    }

    template <class T, class Alloc>
    template <class Predicate>
    void list<T, Alloc>::remove_if(Predicate pred)
    {
        iterator first = begin();
        iterator last = end();
        while (first != last)
        {
            iterator next = first;
            ++next;
            if (pred(*first))
                _erase(first);
            first = next;
        }
    }

    //(1)
    template <class T, class Alloc>
    void list<T, Alloc>::unique()
    {
        iterator first = begin();
        const iterator last = end();

        if (first == last)
            return;
        
        iterator next = first;
        next++;
        while(next != last)
        {
            if (*first == *next)
                _erase(next);
            else
                first = next;
            
            next = first;
            next++;
        }
    }
    //(2)
    template <class T, class Alloc>
    template <class BinaryPredicate>
    void list<T, Alloc>::unique(BinaryPredicate binary_pred)
    {
        iterator first = begin();
        const iterator last = end();

        if (first == last)
            return;
        
        iterator next = first;
        next++;
        while(next != last)
        {
            if (binary_pred(*first, *next))
                _erase(next);
            else
                first = next;
            
            next = first;
            next++;
        }
    }

    //(1)
    template <class T, class Alloc>
    void list<T, Alloc>::merge(list& x)
    {
        if (this != &x)
        {
            iterator first1 = begin();
            iterator last1 = end();
            iterator first2 = x.begin();
            iterator last2 = x.end();
            while (first1 != last1 && first2 != last2)
                if (*first2 < *first1)
                {
                    iterator next = first2;
                    next++;
                    first1.node_ptr->_transfer(first2.node_ptr, next.node_ptr);
                    first2 = next;
                }
                else
                    ++first1;
            if (first2 != last2)
            {
                last1.node_ptr->_transfer(first2.node_ptr, last2.node_ptr);
            }
        }
    }
    //(2)
    template <class T, class Alloc>
    template <class Compare>
    void list<T, Alloc>::merge(list& x, Compare comp)
    {
        if (this != &x)
        {
            iterator first1 = begin();
            iterator last1 = end();
            iterator first2 = x.begin();
            iterator last2 = x.end();
            while (first1 != last1 && first2 != last2)
                if (comp(*first2, *first1))
                {
                    iterator next = first2;
                    next++;
                    first1.node_ptr->_transfer(first2.node_ptr, next.node_ptr);
                    first2 = next;
                }
                else
                    ++first1;
            if (first2 != last2)
            {
                last1.node_ptr->_transfer(first2.node_ptr, last2.node_ptr);
            }
        }
    }

    //(1)
    template <class T, class Alloc>
    void list<T, Alloc>::sort()
    {
        // Do nothing if the list has length 0 or 1.
        if (this->sentry_node.next != &this->sentry_node && this->sentry_node.next->next != &this->sentry_node)
        {
            list carry;
            list tmp[64];
            list *fill = &tmp[0];
            list *counter;

            do
            {
                carry.splice(carry.begin(), *this, begin());

                for (counter = &tmp[0]; counter != fill && !counter->empty(); ++counter)
                {
                    counter->merge(carry);
                    carry.swap(*counter);
                }
                carry.swap(*counter);
                if (counter == fill)
                    ++fill;
            } while (!empty());

            for (counter = &tmp[1]; counter != fill; ++counter)
                counter->merge(*(counter - 1));
            swap(*(fill - 1));
        }
    }

    //(2)
    template <class T, class Alloc>
    template <class Compare>
    void list<T, Alloc>::sort(Compare comp)
    {
        // Do nothing if the list has length 0 or 1.
        if (this->sentry_node.next != &this->sentry_node && this->sentry_node.next->next != &this->sentry_node)
        {
            list carry;
            list tmp[64];
            list *fill = &tmp[0];
            list *counter;

            do
            {
                carry.splice(carry.begin(), *this, begin());

                for (counter = &tmp[0]; counter != fill && !counter->empty(); ++counter)
                {
                    counter->merge(carry, comp);
                    carry.swap(*counter);
                }
                carry.swap(*counter);
                if (counter == fill)
                    ++fill;
            } while (!empty());

            for (counter = &tmp[1]; counter != fill; ++counter)
                counter->merge(*(counter - 1), comp);
            swap(*(fill - 1));
        }
    }

    template <class T, class Alloc>
    void list<T, Alloc>::reverse()
    {
        _list_node_base* tmp = &(this->sentry_node);
        
        do
        {
            ft::swap(tmp->next, tmp->prev);
            tmp = tmp->prev;
        }
        while (tmp != &(this->sentry_node));
    }

// ########## Non-member function overloads ##########
    //(1)
    template <class T, class Alloc>
    bool operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
        typedef typename list<T, Alloc>::const_iterator const_iterator;
        
        const_iterator i1 = lhs.begin();
        const_iterator end1 = lhs.end();

        const_iterator i2 = rhs.begin();
        const_iterator end2 = rhs.end();
        
        while (i1 != end1 && i2 != end2 && *i1 == *i2)
        {
            ++i1;
            ++i2;
        }
        return i1 == end1 && i2 == end2;
    }
    
    //(2)	
    template <class T, class Alloc>
    bool operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    { return !(lhs == rhs); }
    
    //(3)	
    template <class T, class Alloc>
    bool operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
    
    //(4)	
    template <class T, class Alloc>
    bool operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    { return !(rhs < lhs); }
    
    //(5)	
    template <class T, class Alloc>
    bool operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    { return rhs < lhs; }
    
    //(6)	
    template <class T, class Alloc>
    bool operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    { return !(lhs < rhs); }

    template <class T, class Alloc>
    void swap(list<T, Alloc>& x, list<T, Alloc>& y)
    { x.swap(y); }

} // end namespace ft 

#endif
