/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 19:23:30 by kycho             #+#    #+#             */
/*   Updated: 2021/05/27 16:08:33 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

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
            while (x = y->right)
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
        _rb_tree_const_iterator(const iteartor& it) : node_ptr(it.node_ptr) {}

        iterator _const_cast() const
        {
            return iterator(static_cast<_rb_tree_node<T> *>(const_cast<_rb_tree_node_base *>(node_ptr))));
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

} // end namespace ft 

#endif
