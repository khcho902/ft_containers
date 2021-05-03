/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:10:24 by kycho             #+#    #+#             */
/*   Updated: 2021/05/03 18:53:40 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>

namespace ft
{
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
        
        typedef implementation-defined                      iterator;
        typedef implementation-defined                      const_iterator;
        typedef reverse_iterator<iterator>                  reverse_iterator;
        typedef reverse_iterator<const_iterator>            const_reverse_iterator;

        // iterator_traits<iterator>::difference_type
        typedef ptrdiff_t                                   difference_type;
        //an unsigned integral type that can represent any non-negative value of difference_type
        typedef size_t                                      size_type;
    

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
        void assign (InputIterator first, InputIterator last);
        //fill (2)	
        void assign (size_type n, const value_type& val);
        
        void push_front (const value_type& val);
        void pop_front();
        void push_back (const value_type& val);
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


    // ########## Operations: ##########
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
    };


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
}

#endif
