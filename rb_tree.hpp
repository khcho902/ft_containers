/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 19:23:30 by kycho             #+#    #+#             */
/*   Updated: 2021/05/28 02:48:44 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

# include <memory>
# include <iterator>
# include "iterator.hpp"

namespace ft 
{
    enum _rb_tree_color
    {
        red = false,
        black = true
    };

	struct _rb_tree_node_base
	{
		_rb_tree_color			color;
		_rb_tree_node_base*		parent;
		_rb_tree_node_base*		left;
		_rb_tree_node_base*		right;

        static _rb_tree_node_base* _minimum(_rb_tree_node_base* x)
        {
            while (x->left != 0)
                x = x->left;
            return x;
        }

        static _rb_tree_node_base* _maxinum(_rb_tree_node_base* x)
        {
            while (x->right != 0)
                x = x->right;
            return x;
        }
	};

	template <typename T>
	struct _rb_tree_node : public _rb_tree_node_base
	{
		T value;
	};

    _rb_tree_node_base* _rb_tree_increment(_rb_tree_node_base* x)
    {
        if (x->right != 0)
        {
            x = x->right;
            while (x->left != 0)
                x = x->left;
        }
        else
        {
            _rb_tree_node_base* y = x->parent;
            while (x == y->right)
            {
                x = y;
                y = y->parent;
            }
            if (x->right != y)
                x = y;
        }
        return x;
    }

    _rb_tree_node_base* _rb_tree_decrement(_rb_tree_node_base* x)
    {
        if (x->color == red && x->parent->parent == x)
            x = x->right;
        else if (x->left != 0)
        {
            _rb_tree_node_base* y = x->left;
            while (y->right != 0)
                y = y->right;
                x = y;
        }
        else
        {
            _rb_tree_node_base* y = x->parent;
            while (x == y->left)
            {
                x = y;
                y = y->parent;
            }   
            x = y;
        }
        return x;
    }

    const _rb_tree_node_base* _rb_tree_increment(const _rb_tree_node_base* x)
    {
        return _rb_tree_increment(const_cast<_rb_tree_node_base*>(x));
    }

    const _rb_tree_node_base* _rb_tree_decrement(const _rb_tree_node_base* x)
    {
        return _rb_tree_decrement(const_cast<_rb_tree_node_base*>(x));
    }

	// ############## rb_tree iterator ############################################################
    template <typename T>
    struct _rb_tree_iterator
    {
        typedef _rb_tree_iterator<T>                _Self;
        typedef _rb_tree_node<T>                    _Node;
        
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef std::bidirectional_iterator_tag     iterator_category;
        
        _rb_tree_node_base *node_ptr;

        _rb_tree_iterator() : node_ptr() {}
        explicit _rb_tree_iterator(_Node* x) : node_ptr(x) {}

        reference operator*() const
        {
            return static_cast<_Node*>(node_ptr)->value;
        }

        // TODO : __addressof 사용하는거 확인해봐야함 
        pointer operator->() const
        {
            return std::addressof(static_cast<_Node*>(node_ptr)->value);
        }

        _Self& operator++()
        {
            node_ptr = _rb_tree_increment(node_ptr);
            return *this;
        }

        _Self operator++(int)
        {
            _Self tmp = *this;
            node_ptr = _rb_tree_increment(node_ptr);
            return tmp;
        }

        _Self& operator--()
        {
            node_ptr = _rb_tree_decrement(node_ptr);
            return *this;
        }

        _Self operator--(int)
        {
            _Self tmp = *this;
            node_ptr = _rb_tree_decrement(node_ptr);
            return tmp;
        }

        bool operator==(const _Self &x) const
        {
            return node_ptr == x.node_ptr;
        }

        bool operator!=(const _Self &x) const
        {
            return node_ptr != x.node_ptr;
        }
    };

    // ############## rb_tree const iterator #######################################################
    template <typename T>
    struct _rb_tree_const_iterator
    {
        typedef _rb_tree_const_iterator<T>          _Self;
        typedef const _rb_tree_node<T>              _Node;
        typedef _rb_tree_iterator<T>                iterator;
        
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef std::bidirectional_iterator_tag     iterator_category;
        
        const _rb_tree_node_base *node_ptr;

        _rb_tree_const_iterator() : node_ptr() {}
        explicit _rb_tree_const_iterator(_Node* x) : node_ptr(x) {}
        _rb_tree_const_iterator(const iterator& it) : node_ptr(it.node_ptr) {}

        iterator _const_cast() const
        {
            return iterator(static_cast<_rb_tree_node<T> *>(const_cast<_rb_tree_node_base *>(node_ptr)));
        }

        reference operator*() const
        {
            return static_cast<_Node*>(node_ptr)->value;
        }

        // TODO : __addressof 사용하는거 확인해봐야함 
        pointer operator->() const
        {
            return std::addressof(static_cast<_Node*>(node_ptr)->value);
        }

        _Self& operator++()
        {
            node_ptr = _rb_tree_increment(node_ptr);
            return *this;
        }

        _Self operator++(int)
        {
            _Self tmp = *this;
            node_ptr = _rb_tree_increment(node_ptr);
            return tmp;
        }

        _Self& operator--()
        {
            node_ptr = _rb_tree_decrement(node_ptr);
            return *this;
        }

        _Self operator--(int)
        {
            _Self tmp = *this;
            node_ptr = _rb_tree_decrement(node_ptr);
            return tmp;
        }

        bool operator==(const _Self &x) const
        {
            return node_ptr == x.node_ptr;
        }

        bool operator!=(const _Self &x) const
        {
            return node_ptr != x.node_ptr;
        }
    };
    
    template<typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Val> >
    class rb_tree
    {
    public:
    // ########## Member types ##########
        typedef Key                                         key_type;
        typedef Val                                         value_type;
        typedef Alloc                                       allocator_type;
        typedef value_type&                                 reference;
        typedef const value_type&                           const_reference;
        typedef value_type*                                 pointer;
        typedef const value_type*                           const_pointer;

        typedef _rb_tree_iterator<Val>                      iterator;
        typedef _rb_tree_const_iterator<Val>                const_iterator;
        typedef std::reverse_iterator<iterator>             reverse_iterator;
        typedef std::reverse_iterator<const_iterator>       const_reverse_iterator;

        typedef ptrdiff_t                                   difference_type;
        typedef size_t                                      size_type;

    protected:
        typedef _rb_tree_node<Val>                                          _Node;
        typedef typename Alloc::template rebind<_rb_tree_node<Val> >::other _node_alloc_type;

        _rb_tree_node_base  header;
        size_type           node_count;
        _node_alloc_type    node_allocator;
        Compare             key_compare;

        void _initialize()
        {
            this->header.color = red;
            this->header.parent = 0;
            this->header.left = &(this->header);
            this->header.right = &(this->header);
        }

    public:
    // ########## (constructor) ##########
    rb_tree()
        : header(), node_count(0), node_allocator(), key_compare()
    {
        _initialize();
    }

    rb_tree(const Compare& comp, const allocator_type& a = allocator_type())
        : header(), node_count(0), node_allocator(a), key_compare(comp)
    {
        _initialize();
    }

    /*
    rb_tree(const rb_tree& x)
        : header(), node_count(0), node_allocator(x.node_allocator), key_compare(x.key_compare)
    {
        _initialize();
    }
    */

    // ########## (destructor) ##########
    /*
    ~_Rb_tree()
    */

    // ########## operator= ##########
    /*
    _Rb_tree& operator=(const _Rb_tree& __x);
    */

    // ########## functions: ##########
    Compare key_comp() const
    {
        return this->keycompare;
    }

    /*
      iterator
      begin()  // 필요(map) 필요(set)
      { 
    return iterator(static_cast<_Link_type>
            (this->_M_impl._M_header._M_left));
      }

      const_iterator
      begin() const  // 필요(map)
      { 
    return const_iterator(static_cast<_Const_Link_type>
                  (this->_M_impl._M_header._M_left));
      }

      iterator
      end()      // 필요(map) 필요(set)
      { return iterator(static_cast<_Link_type>(&this->_M_impl._M_header)); }

      const_iterator
      end() const  // 필요(map)
      { 
    return const_iterator(static_cast<_Const_Link_type>
                  (&this->_M_impl._M_header));
      }

      reverse_iterator
      rbegin()   // 필요(map) 필요(set)
      { return reverse_iterator(end()); }

      const_reverse_iterator
      rbegin() const    // 필요(map)
      { return const_reverse_iterator(end()); }

      reverse_iterator
      rend()             // 필요(map) 필요(set)
      { return reverse_iterator(begin()); }

      const_reverse_iterator
      rend() const       // 필요(map)
      { return const_reverse_iterator(begin()); }

      bool
      empty() const      // 필요(map) 필요(set)
      { return _M_impl._M_node_count == 0; }

      size_type
      size() const      // 필요(map) 필요(set)
      { return _M_impl._M_node_count; }

      size_type
      max_size() const   // 필요(map) 필요(set)
      { return _M_get_Node_allocator().max_size(); }

      void
      swap(_Rb_tree& __t);   // 필요(map) 필요(set)

      pair<iterator, bool>
      _M_insert_unique(const value_type& __x);  // 필요(map) 필요(set)

      iterator
      _M_insert_equal(const value_type& __x);

      iterator
      _M_insert_unique_(const_iterator __position, const value_type& __x);  // 필요(map) 필요(set)

      iterator
      _M_insert_equal_(const_iterator __position, const value_type& __x);

      template<typename _InputIterator>
        void
        _M_insert_unique(_InputIterator __first, _InputIterator __last);  // 필요(map) 필요(set)

      template<typename _InputIterator>
        void
        _M_insert_equal(_InputIterator __first, _InputIterator __last);

        void
      erase(iterator __position)     // 필요(map) 필요(set)
      { _M_erase_aux(__position); }

      void
      erase(const_iterator __position)
      { _M_erase_aux(__position); }

      size_type
      erase(const key_type& __x);  // 필요(map) 필요(set)

      void
      erase(iterator __first, iterator __last)  // 필요(map) 필요(set)
      { _M_erase_aux(__first, __last); }

      void
      erase(const_iterator __first, const_iterator __last)
      { _M_erase_aux(__first, __last); }

      void
      erase(const key_type* __first, const key_type* __last);

      void
      clear()  // 필요(map) 필요(set)
      {
        _M_erase(_M_begin());
        _M_leftmost() = _M_end();
        _M_root() = 0;
        _M_rightmost() = _M_end();
        _M_impl._M_node_count = 0;
      }

      // Set operations.
      iterator
      find(const key_type& __k);  // 필요(map) 필요(set)

      const_iterator
      find(const key_type& __k) const;  // 필요(map) 필요(set)

      size_type
      count(const key_type& __k) const;

      iterator
      lower_bound(const key_type& __k)  // 필요(map) 필요(set)
      { return _M_lower_bound(_M_begin(), _M_end(), __k); }

      const_iterator
      lower_bound(const key_type& __k) const  // 필요(map) 필요(set)
      { return _M_lower_bound(_M_begin(), _M_end(), __k); }

      iterator
      upper_bound(const key_type& __k)  // 필요(map) 필요(set)
      { return _M_upper_bound(_M_begin(), _M_end(), __k); }

      const_iterator
      upper_bound(const key_type& __k) const  // 필요(map) 필요(set)
      { return _M_upper_bound(_M_begin(), _M_end(), __k); }

      pair<iterator, iterator>
      equal_range(const key_type& __k);  // 필요(map) 필요(set)

      pair<const_iterator, const_iterator>
      equal_range(const key_type& __k) const;  // 필요(map) 필요(set)
      */

    };

} // end namespace ft 

#endif
