/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:10:24 by kycho             #+#    #+#             */
/*   Updated: 2021/05/23 15:09:59 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <iterator>
# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{
    struct _list_node_base
    {
        _list_node_base* next;
        _list_node_base* prev;

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
        
        typedef ptrdiff_t                           difference_type;
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;

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
        
        typedef ptrdiff_t                           difference_type;
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef T                                   value_type;
        typedef const T*                            pointer;
        typedef const T&                            reference;

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
        typedef typename Alloc::template rebind<_list_node<T> >::other    _node_alloc_type;

        _node_alloc_type    node_allocator;
        _list_node_base     sentry_node;

        typedef _list_node<T>   _Node;

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
    /* 주석 시작(3)
        list& operator=(const list& x);
    주석 끝(3)*/


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
    /* 주석 시작(7)
        void push_front (const value_type& val);
        void pop_front();
    주석 끝(7)*/
        void push_back(const value_type& val);
    /* 주석 시작(7-2)
        void pop_back();
    주석 끝(7-2)*/
    
        //single element (1)	
        iterator insert(iterator position, const value_type& val);
        //fill (2)	
        void insert(iterator position, size_type n, const value_type& val);
        //range (3)	
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);
        
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
    /* 주석 시작(7-3)
        void swap (list& x);
        void resize (size_type n, value_type val = value_type());
        void clear();
    주석 끝(7-3)*/
    


    // ########## Operations: ##########
        //entire list (1)	
        void splice(iterator position, list& x);
        //single element (2)	
        void splice(iterator position, list& x, iterator i);
        //element range (3)	
        void splice(iterator position, list& x, iterator first, iterator last);
    /* 주석 시작(8)
        void remove (const value_type& val);
        template <class Predicate>
        void remove_if (Predicate pred);

        //(1)	
        void unique();
        //(2)	
        template <class BinaryPredicate>
        void unique (BinaryPredicate binary_pred);

        //(1)	
        void merge (list& x);
        //(2)	
        template <class Compare>
        void merge (list& x, Compare comp);

        //(1)
        void sort();
        //(2)
        template <class Compare>
        void sort (Compare comp);

        void reverse();

        // allocator_type get_allocator() const;
    주석 끝(8)*/
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
    void list<T, Alloc>::push_back(const value_type& val)  // TODO : 개선 필요
    {
        _Node* _tmp = _create_node(val);

        _list_node_base* last_node = this->sentry_node.prev;
        
        last_node->next = _tmp;
        _tmp->prev = last_node;
        
        _tmp->next = &(this->sentry_node);
        this->sentry_node.prev = _tmp;
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

/* 주석시작
// ########## Non-member function overloads ##########
    //(1)
    template <class T, class Alloc>
    bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
    //(2)	
    template <class T, class Alloc>
    bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
    //(3)	
    template <class T, class Alloc>
    bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
    //(4)	
    template <class T, class Alloc>
    bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
    //(5)	
    template <class T, class Alloc>
    bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
    //(6)	
    template <class T, class Alloc>
    bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

    template <class T, class Alloc>
    void swap (list<T,Alloc>& x, list<T,Alloc>& y);
주석 끝*/ 

} // end namespace ft 


#endif
