/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:10:24 by kycho             #+#    #+#             */
/*   Updated: 2021/05/06 22:40:39 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <iterator>

namespace ft
{
    struct _list_node_base
    {
        _list_node_base* next;
        _list_node_base* prev;
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
        explicit _list_const_iterator(_list_node_base* _x) : node_ptr(_x) {}  // TODO : 왜 explicit 붙이는거지 ??
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
        /* 주석 시작(1)
        typedef reverse_iterator<iterator>                  reverse_iterator;
        typedef reverse_iterator<const_iterator>            const_reverse_iterator;
        주석 끝(1) */

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


    public:
    // ########## (constructor) ##########
        //default (1)	
        explicit list (const allocator_type& alloc = allocator_type());
        //fill (2)	
        explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
        //range (3)	
        template <class InputIterator>
        list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
        //copy (4)	
        list (const list& x);


    // ########## (destructor) ##########
    /* 주석 시작(2)
        ~list();
    주석 끝(2) */


    // ########## operator= ##########
    /* 주석 시작(3)
        list& operator=(const list& x);
    주석 끝(3)*/


    // ########## Iterators: ##########
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
    /* 주석 시작(4)
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
    주석 끝(4)*/


    // ########## Capacity: ##########
    /* 주석 시작(5)
        bool empty() const;
        size_type size() const;
        size_type max_size() const;
    주석 끝(5)*/


    // ########## Element access: ##########
    /* 주석 시작(6)
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;
    주석 끝(6)*/


    // ########## Modifiers: ##########
    /* 주석 시작(7)
        //range (1)	
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last);
        //fill (2)	
        void assign (size_type n, const value_type& val);
        
        void push_front (const value_type& val);
        void pop_front();
    주석 끝(7)*/
        void push_back (const value_type& val);
    /* 주석 시작(7-2)
        void pop_back();

        //single element (1)	
        iterator insert (iterator position, const value_type& val);
        //fill (2)	
        void insert (iterator position, size_type n, const value_type& val);
        //range (3)	
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last);
    
        iterator erase (iterator position);
        iterator erase (iterator first, iterator last);
        void swap (list& x);
        void resize (size_type n, value_type val = value_type());
        void clear();
    주석 끝(7-2)*/
    


    // ########## Operations: ##########
    /* 주석 시작(8)
        //entire list (1)	
        void splice (iterator position, list& x);
        //single element (2)	
        void splice (iterator position, list& x, iterator i);
        //element range (3)	
        void splice (iterator position, list& x, iterator first, iterator last);

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

    template<class T, class Alloc>
    list<T, Alloc>::list(const allocator_type& alloc) :
        node_allocator(alloc),
        sentry_node()
    {
        this->sentry_node.next = &(this->sentry_node);
        this->sentry_node.prev = &(this->sentry_node);
    }

    // TODO : 개선 필요
    // template<class T, class Alloc>
    // list<T, Alloc>::list(size_type n, const value_type& val, const allocator_type& alloc) :
    //     node_allocator(alloc),
    //     sentry_node()
    // {
    //     for (; n; --n)
    //         push_back(val);
    // }

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
    void list<T, Alloc>::push_back (const value_type& val)  // TODO : 개선 필요
    {
        _Node* _tmp = _create_node(val);

        _list_node_base* last_node = this->sentry_node.prev;
        
        last_node->next = _tmp;
        _tmp->prev = last_node;
        
        _tmp->next = &(this->sentry_node);
        this->sentry_node.prev = _tmp;
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

}


#endif
