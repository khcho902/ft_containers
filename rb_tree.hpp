/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 19:23:30 by kycho             #+#    #+#             */
/*   Updated: 2021/05/30 16:33:11 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

# include <memory>
# include <utility>
# include <iterator>
# include "iterator.hpp"

namespace ft
{
    enum _rb_tree_color { red = false, black = true };

	struct _rb_tree_node_base
	{
		_rb_tree_color			color;
		_rb_tree_node_base*		parent;
		_rb_tree_node_base*		left;
		_rb_tree_node_base*		right;

        static _rb_tree_node_base* _s_minimum(_rb_tree_node_base* x)
        {
            while (x->left != 0)
                x = x->left;
            return x;
        }

        static const _rb_tree_node_base* _s_minimum(const _rb_tree_node_base* x)
        {
            while (x->left != 0)
                x = x->left;
            return x;
        }

        static _rb_tree_node_base* _s_maximum(_rb_tree_node_base* x)
        {
            while (x->right != 0)
                x = x->right;
            return x;
        }

        static const _rb_tree_node_base* _s_maximum(const _rb_tree_node_base* x)
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

    static void _rb_tree_rotate_left(
        _rb_tree_node_base *const x, _rb_tree_node_base *& root)
    {
        _rb_tree_node_base *const y = x->right;

        x->right = y->left;
        if (y->left != 0)
            y->left->parent = x;
        y->parent = x->parent;

        if (x == root)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    static void _rb_tree_rotate_right(
        _rb_tree_node_base *const x, _rb_tree_node_base *&root)
    {
        _rb_tree_node_base *const y = x->left;

        x->left = y->right;
        if (y->right != 0)
            y->right->parent = x;
        y->parent = x->parent;

        if (x == root)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void _rb_tree_insert_and_rebalance( const bool is_insert_left,
            _rb_tree_node_base* x, _rb_tree_node_base* p, _rb_tree_node_base& header)
    {
        _rb_tree_node_base *& root = header.parent;

        // Initialize fields in new node to insert.
        x->parent = p;
        x->left = 0;
        x->right = 0;
        x->color = red;

        // Insert.
        // Make new node child of parent and maintain root, leftmost and rightmost nodes.
        // N.B. First node is always inserted left.
        if (is_insert_left)
        {
            p->left = x; // also makes leftmost = x when p == &header

            if (p == &header)
            {
                header.parent = x;
                header.right = x;
            }
            else if (p == header.left)
                header.left = x; // maintain leftmost pointing to min node
        }
        else
        {
            p->right = x;
            
            if (p == header.right)
                header.right = x; // maintain rightmost pointing to max node 
        }

        // Rebalance.
        while (x != root && x->parent->color == red)
        {
            _rb_tree_node_base *const xpp = x->parent->parent;

            if (x->parent == xpp->left)
            {
                _rb_tree_node_base *const y = xpp->right;
                if (y && y->color == red)
                {
                    x->parent->color = black;
                    y->color = black;
                    xpp->color = red;
                    x = xpp;
                }
                else
                {
                    if (x == x->parent->right)
                    {
                        x = x->parent;
                        _rb_tree_rotate_left(x, root);
                    }
                    x->parent->color = black;
                    xpp->color = red;
                    _rb_tree_rotate_right(xpp, root);
                }
            }
            else
            {
                _rb_tree_node_base *const y = xpp->left;
                if (y && y->color == red)
                {
                    x->parent->color = black;
                    y->color = black;
                    xpp->color = red;
                    x = xpp;
                }
                else
                {
                    if (x == x->parent->left)
                    {
                        x = x->parent;
                        _rb_tree_rotate_right(x, root);
                    }
                    x->parent->color = black;
                    xpp->color = red;
                    _rb_tree_rotate_left(xpp, root);
                }
            }
        }
        root->color = black;
    }

    _rb_tree_node_base* _rb_tree_rebalance_for_erase(_rb_tree_node_base* const z, _rb_tree_node_base& header)
    {
        _rb_tree_node_base*& root = header.parent;
        _rb_tree_node_base*& leftmost = header.left;
        _rb_tree_node_base*& rightmost = header.right;
        _rb_tree_node_base* y = z;
        _rb_tree_node_base* x = 0;
        _rb_tree_node_base* x_parent = 0;

        if (y->left == 0)       // __z has at most one non-null child. y == z.
            x = y->right;     // __x might be null.
        else if (y->right == 0) // __z has exactly one non-null child. y == z.
            x = y->left;      // __x is not null.
        else
        {
            // __z has two non-null children.  Set __y to
            y = y->right; //   __z's successor.  __x might be null.
            while (y->left != 0)
                y = y->left;
            x = y->right;
        }
        if (y != z)
        {
            // relink y in place of z.  y is z's successor
            z->left->parent = y;
            y->left = z->left;
            if (y != z->right)
            {
                x_parent = y->parent;
                if (x)
                    x->parent = y->parent;
                y->parent->left = x; // __y must be a child of _M_left
                y->right = z->right;
                z->right->parent = y;
            }
            else
                x_parent = y;
            if (root == z)
                root = y;
            else if (z->parent->left == z)
                z->parent->left = y;
            else
                z->parent->right = y;
            y->parent = z->parent;
            ft::swap(y->color, z->color);
            y = z;
            // __y now points to node to be actually deleted
        }
        else
        { // __y == __z
            x_parent = y->parent;
            if (x)
                x->parent = y->parent;
            if (root == z)
                root = x;
            else if (z->parent->left == z)
                z->parent->left = x;
            else
                z->parent->right = x;
            if (leftmost == z)
            {
                if (z->right == 0) // __z->_M_left must be null also
                    leftmost = z->parent;
                // makes __leftmost == _M_header if __z == __root
                else
                    leftmost = _rb_tree_node_base::_s_minimum(x);
            }
            if (rightmost == z)
            {
                if (z->left == 0) // __z->_M_right must be null also
                    rightmost = z->parent;
                // makes __rightmost == _M_header if __z == __root
                else // __x == __z->_M_left
                    rightmost = _rb_tree_node_base::_s_maximum(x);
            }
        }
        if (y->color != red)
        {
            while (x != root && (x == 0 || x->color == black))
                if (x == x_parent->left)
                {
                    _rb_tree_node_base* w = x_parent->right;
                    if (w->color == red)
                    {
                        w->color = black;
                        x_parent->color = red;
                        _rb_tree_rotate_left(x_parent, root);
                        w = x_parent->right;
                    }
                    if ((w->left == 0 ||
                         w->left->color == black) &&
                        (w->right == 0 ||
                         w->right->color == black))
                    {
                        w->color = red;
                        x = x_parent;
                        x_parent = x_parent->parent;
                    }
                    else
                    {
                        if (w->right == 0 || w->right->color == black)
                        {
                            w->left->color = black;
                            w->color = red;
                            _rb_tree_rotate_right(w, root);
                            w = x_parent->right;
                        }
                        w->color = x_parent->color;
                        x_parent->color = black;
                        if (w->right)
                            w->right->color = black;
                        _rb_tree_rotate_left(x_parent, root);
                        break;
                    }
                }
                else
                {
                    // same as above, with _M_right <-> _M_left.
                    _rb_tree_node_base* w = x_parent->left;
                    if (w->color == red)
                    {
                        w->color = black;
                        x_parent->color = red;
                        _rb_tree_rotate_right(x_parent, root);
                        w = x_parent->left;
                    }
                    if ((w->right == 0 ||
                         w->right->color == black) &&
                        (w->left == 0 ||
                         w->left->color == black))
                    {
                        w->color = red;
                        x = x_parent;
                        x_parent = x_parent->parent;
                    }
                    else
                    {
                        if (w->left == 0 || w->left->color == black)
                        {
                            w->right->color = black;
                            w->color = red;
                            _rb_tree_rotate_left(w, root);
                            w = x_parent->left;
                        }
                        w->color = x_parent->color;
                        x_parent->color = black;
                        if (w->left)
                            w->left->color = black;
                        _rb_tree_rotate_right(x_parent, root);
                        break;
                    }
                }
            if (x)
                x->color = black;
        }
        return y;
    }

    // ############## rb_tree class #############################################################
    template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Val> >
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

        _Node* _create_node(const value_type& x)
        {
            _Node* tmp = node_allocator.allocate(1);
            allocator_type(node_allocator).construct(std::addressof(tmp->value),x);
            return tmp;
        }

        void _destroy_node(_Node* p)
        {
            allocator_type(node_allocator).destroy(std::addressof(p->value));
            node_allocator.deallocate(p, 1);
        }

        _Node* _clone_node(const _Node* x)
        {
            _Node* tmp = _create_node(x->value);
            tmp->color = x->color;
            tmp->left = 0;
            tmp->right = 0;
            
            return tmp;
        }

        _rb_tree_node_base*& _root()
        { return this->header.parent; }

        const _rb_tree_node_base* _root() const
        { return this->header.parent; }

        _rb_tree_node_base*& _leftmost()
        { return this->header.left; }

        const _rb_tree_node_base* _leftmost() const
        { return this->header.left; }

        _rb_tree_node_base*& _rightmost()
        { return this->header.right; }

        const _rb_tree_node_base* _rightmost() const
        { return this->header.right; }

        _Node* _begin()
        { return static_cast<_Node*>(this->header.parent); }

        const _Node* _begin() const
        { return static_cast<const _Node*>(this->header.parent); }

        _Node* _end()
        { return static_cast<_Node*>(&this->header); }

        const _Node* _end() const
        { return static_cast<const _Node*>(&this->header); }

        static const_reference _s_value(const _Node* x)
        { return x->value; }

        static const_reference _s_value(const _rb_tree_node_base* x)
        { return static_cast<const _Node *>(x)->value; }

        static const Key& _s_key(const _Node* x)
        { return KeyOfValue()(_s_value(x)); }

        static const Key& _s_key(const _rb_tree_node_base* x)
        { return KeyOfValue()(_s_value(x)); }

        static _Node* _s_left(_rb_tree_node_base* x)
        { return static_cast<_Node*>(x->left); }

        static const _Node* _s_left(const _rb_tree_node_base* x)
        { return static_cast<const _Node*>(x->left); }

        static _Node* _s_right(_rb_tree_node_base* x)
        { return static_cast<_Node*>(x->right); }

        static const _Node* _s_right(const _rb_tree_node_base* x)
        { return static_cast<const _Node*>(x->right); }

        static _rb_tree_node_base* _s_minimum(_rb_tree_node_base* x)
        { return _rb_tree_node_base::_s_minimum(x); }

        static const _rb_tree_node_base* _s_minimum(const _rb_tree_node_base* x)
        { return _rb_tree_node_base::_s_minimum(x); }

        static _rb_tree_node_base* _s_maximum(_rb_tree_node_base* x)
        { return _rb_tree_node_base::_s_maximum(x); }

        static const _rb_tree_node_base* _s_maximum(const _rb_tree_node_base* x)
        { return _rb_tree_node_base::_s_maximum(x); }

    private:
        iterator _insert_(const _rb_tree_node_base* x, const _rb_tree_node_base* p, const value_type& v)
        {
            bool is_insert_left = (x != 0 || p == _end() || key_compare(KeyOfValue()(v), _s_key(p)));

            _Node* z = _create_node(v);

            _rb_tree_insert_and_rebalance(is_insert_left, z, const_cast<_rb_tree_node_base*>(p), this->header);

            this->node_count++;
            return iterator(z);
        }

        _Node* _copy(const _Node* x, _Node* p)
        {
            // Structural copy.  __x and __p must be non-null.
            _Node* top = _clone_node(x);
            top->parent = p;

            if (x->right)
                top->right = _copy(_s_right(x), top);
            p = top;
            x = _s_left(x);

            while (x != 0)
            {
                _Node* y = _clone_node(x);
                p->left = y;
                y->parent = p;
                if (x->right)
                    y->right = _copy(_s_right(x), y);
                p = y;
                x = _s_left(x);
            }            
            return top;
        }

        // TODO : 확인필요
        void _erase(_Node* x)
        {
            // Erase without rebalancing.
            while (x != 0)
            {
                _erase(_s_right(x));
                _Node* y = _s_left(x);
                _destroy_node(x);
                x = y;
            }
        }

        iterator _lower_bound(_Node* x, _Node* y, const key_type& k)
        {
            while (x != 0)
            {
                if (!key_compare(_s_key(x), k))
                {
                    y = x;
                    x = _s_left(x);
                }
                else
                    x = _s_right(x);
            }
            return iterator(y);
        }

        const_iterator _lower_bound(const _Node* x, const _Node* y, const key_type& k) const
        {
            while (x != 0)
            {
                if (!key_compare(_s_key(x), k))
                {
                    y =  x;
                    x = _s_left(x);
                }
                else
                    x = _s_right(x);
            }
            return const_iterator(y);
        }

        iterator _upper_bound(_Node* x, _Node* y, const key_type& k)
        {
            while (x != 0)
            {
                if (key_compare(k, _s_key(x)))
                {
                    y = x;
                    x = _s_left(x);
                }
                else
                    x = _s_right(x);
            }
            return iterator(y);
        }

        const_iterator _upper_bound(const _Node* x, const _Node* y, const key_type& k)
        {
            while (x != 0)
            {
                if (key_compare(k, _s_key(x)))
                {
                    y = x;
                    x = _s_left(x);
                }
                else
                    x = _s_right(x);
            }
            return const_iterator(y);
        }

        void _erase_aux(const_iterator position)
        {
            _Node* y = static_cast<_Node*>(_rb_tree_rebalance_for_erase(const_cast<_rb_tree_node_base*>(position.node_ptr), this->header));
            _destroy_node(y);
            node_count--;
        }

        void _erase_aux(const_iterator first, const_iterator last)
        {
            if (first == begin() && last == end())
                clear();
            else
            {
                while (first != last)
                {
                    erase(first);
                    first++;
                }
            }
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

        rb_tree(const rb_tree& x)
            : header(), node_count(0), node_allocator(x.node_allocator), key_compare(x.key_compare)
        {
            if (x._root() != 0)
            {
                _root() = _copy(x._begin(), x._end());
                _leftmost() = _s_minimum(_root());
                _rightmost() = _s_maximum(_root());
                node_count = x.node_count;
            }
        }

        // ########## (destructor) ##########
        ~rb_tree()
        { _erase(_begin()); }

        // ########## operator= ##########
        rb_tree& operator=(const rb_tree& x)
        {
            if (this != &x)
            {
                // Note that _Key may be a constant type.
                clear();
                key_compare = x.key_compare;
                if (x._root() != 0)
                {
                    _root() = _copy(x._begin(), _end());
                    _leftmost() = _s_minimum(_root());
                    _rightmost() = _s_maximum(_root());
                    node_count = x.node_count;
                }
            }
            return *this;
        }

        // ########## functions: ##########
        Compare key_comp() const
        {
            return this->keycompare;
        }

        iterator begin()
        {
            return iterator(static_cast<_Node *>(this->header.left));
        }
        
        const_iterator begin() const
        {
            return const_iterator(static_cast<const _Node *>(this->header.left));
        }

        iterator end()
        {
            return iterator(static_cast<_Node *>(&(this->header)));
        }

        const_iterator end() const
        {
            return const_iterator(static_cast<const _Node *>(&(this->header)));
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }
        
        bool empty() const
        {
            return this->node_count == 0;
        }

        size_type size() const
        {
            return this->node_count;
        }

        size_type max_size() const
        {
            return this->node_allocator.max_size();
        }

        void swap(rb_tree& t)
        {
            if (_root() == 0)
            {
                if (t._root() != 0)
                {
                    _root() = t._root();
                    _leftmost() = t._leftmost();
                    _rightmost() = t._rightmost();
                    _root()->parent = _end();
                    
                    t._root() = 0;
                    t._leftmost() = t._end();
                    t._rightmost() = t._end();
                }
            }   
            else if (t._root() == 0)
            {
                t._root() = _root();
                t._leftmost() = _leftmost();
                t._rightmost() = _rightmost();
                t._root()->parent = t._end();
                
                _root() = 0;
                _leftmost() = _end();
                _rightmost() = _end();
            }
            else
            {
                ft::swap(_root(), t._root());
                ft::swap(_leftmost(), t._leftmost());
                ft::swap(_rightmost(), t._rightmost());
                
                _root()->parent = _end();
                t._root()->parent = t._end();
            }

            // No need to swap header's color as it does not change.
            ft::swap(this->node_count, t.node_count);
            ft::swap(this->key_compare, t.key_compare);

            ft::swap(this->node_allocator, t.node_allocator);  // TODO : 확인필요
            /*
            _node_alloc_type tmp = this->node_allocator;
            this->node_allocator = t.node_allocator;
            t.node_allocator = tmp;
            */
        }

        std::pair<iterator, bool> insert_unique(const value_type& v)
        {
            _Node* x = _begin();
            _Node* y = _end();

            bool comp = true;
            while (x != 0)
            {
                y = x;
                comp = this->key_compare(KeyOfValue()(v), _s_key(x));
                x = comp ? _s_left(x) : _s_right(x);
            }

            iterator j = iterator(y);

            if (comp)
            {
                if (j == begin())
                    return std::pair<iterator, bool>(_insert_(x, y, v), true);
                else
                    j--;
            }

            if (this->key_compare(_s_key(j.node_ptr), KeyOfValue()(v)))
                return std::pair<iterator, bool>(_insert_(x, y, v), true);
            
            return std::pair<iterator, bool>(j, false);
        }

        iterator insert_unique_(const_iterator position, const value_type &v)
        {
            // end()
            if (position.node_ptr == _end())
            {
                if (size() > 0 && key_compare(_s_key(_rightmost()), KeyOfValue()(v)))
                    return _insert_(0, _rightmost(), v);
                else
                    return insert_unique(v).first;
            }
            else if (key_compare(KeyOfValue()(v), _s_key(position.node_ptr)))
            {
                // First, try before...
                const_iterator before = position;

                if (position.node_ptr == _leftmost()) // begin()
                    return _insert_(_leftmost(), _leftmost(), v);
                else if (key_compare(_s_key((--before).node_ptr), KeyOfValue()(v)))
                {
                    if (_s_right(before.node_ptr) == 0)
                        return _insert_(0, before.node_ptr,  v);
                    else
                        return _insert_(position.node_ptr, position.node_ptr, v);
                }
                else
                    return insert_unique(v).first;
            }
            else if (key_compare(_s_key(position.node_ptr), KeyOfValue()(v)))
            {
                // ... then try after.
                const_iterator after = position;

                if (position.node_ptr == _rightmost())
                    return _insert_(0, _rightmost(), v);
                else if (key_compare(KeyOfValue()(v), _s_key((++after).node_ptr)))
                {
                    if (_s_right(position.node_ptr) == 0)
                        return _insert_(0, position.node_ptr, v);
                    else
                        return _insert_(after.node_ptr, after.node_ptr, v);
                }
                else
                    return insert_unique(v).first;
            }
            else
                //Equivalent keys.
                return position._const_cast();
        }

        template <typename InputIterator>
        void insert_unique(InputIterator first, InputIterator last)
        {
            for (; first != last; first++)
            {
                insert_unique_(end(), *first);
            }
        }

        /* TODO : 해야함 
        iterator _M_insert_equal(const value_type& __x);

        iterator _M_insert_equal_(const_iterator __position, const value_type& __x);

        template<typename _InputIterator>
        void _M_insert_equal(_InputIterator __first, _InputIterator __last);
        */
        
        void erase(iterator position)     // 필요(map) 필요(set)
        { _erase_aux(position); }

        void erase(const_iterator position)
        { _erase_aux(position); }

        size_type erase(const key_type& x)
        {
            std::pair<iterator, iterator> p = equal_range(x);
            const size_type old_size = size();
            erase(p.first, p.second);
            
            return old_size - size();
        }
        
        void erase(iterator first, iterator last)
        { _erase_aux(first, last); }

        void erase(const_iterator first, const_iterator last)
        { _erase_aux(first, last); }

        // TODO : 확인필요
        void erase(const key_type* first, const key_type* last)
        {
            while (first != last)
            {
                erase(*first++);
            }
        }

        void clear()  // 필요(map) 필요(set)
        {
            _erase(_begin());
            _leftmost() = _end();
            _root() = 0;
            _rightmost() = _end();
            node_count = 0;
        }

        // Set operations.
        iterator find(const key_type& k)
        {
            iterator j = _lower_bound(_begin(), _end(), k);
            return (j == end() || key_compare(k, _s_key(j.node_ptr))) ? end() : j;
        }

        const_iterator find(const key_type& k) const
        {
            const_iterator j = _lower_bound(_begin(), _end(), k);
            return (j == end() || key_compare(k, _s_key(j.node_ptr))) ? end() : j;
        }

        /*  TODO : 구현해야함
        size_type
        count(const key_type& __k) const;  // 필요(multimap)
        */

        iterator lower_bound(const key_type& k)
        { return _lower_bound(_begin(), _end(), k); }

        const_iterator lower_bound(const key_type& k) const
        { return _lower_bound(_begin(), _end(), k); }

        iterator upper_bound(const key_type& k)
        { return _upper_bound(_begin(), _end(), k); }

        const_iterator upper_bound(const key_type& k) const
        { return _upper_bound(_begin(), _end(), k); }

        
        std::pair<iterator, iterator> equal_range(const key_type& k)
        {
            _Node* x = _begin();
            _Node* y = _end();
            while (x != 0)
            {
                if (key_compare(_s_key(x), k))
                    x = _s_right(x);
                else if (key_compare(k, _s_key(x)))
                {
                    y = x;
                    x = _s_left(x);
                }
                else
                {
                    _Node* xu(x);
                    _Node* yu(y);
                    
                    y = x;
                    x = _s_left(x);
                    xu = _s_right(xu);
                    
                    return std::pair<iterator, iterator>(_lower_bound(x, y, k), _upper_bound(xu, yu, k));
                }
            }
            return std::pair<iterator, iterator>(iterator(y), iterator(y));
        }

        std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
        {
            const _Node* x = _begin();
            const _Node* y = _end();
            while (x != 0)
            {
                if (key_compare(_s_key(x), k))
                    x = _s_right(x);
                else if (key_compare(k, _s_key(x)))
                {
                    y = x;
                    x = _s_left(x);
                }
                else
                {
                    const _Node* xu(x);
                    const _Node* yu(y);
                    y = x;
                    x = _s_left(x);
                    xu = _s_right(xu);
                    return std::pair<const_iterator, const_iterator>(_lower_bound(x, y, k), _upper_bound(xu, yu, k));
                }
            }
            return std::pair<const_iterator, const_iterator>(const_iterator(y), const_iterator(y));
        }

    };

    template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
    inline bool operator==(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &x, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &y)
    {
        // TODO : std::equal ?? 
        return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
    }

    template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
    inline bool operator<(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &x, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &y)
    {
        // TODO : std::lexicographical_compare ?? 
        return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }

    template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
    inline bool operator!=(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &x, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &y)
    {
        return !(x == y);
    }

    template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
    inline bool operator>(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &x, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &y)
    {
        return y < x;
    }

    template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
    inline bool operator<=(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &x, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &y)
    {
        return !(y < x);
    }

    template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
    inline bool operator>=(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &x, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &y)
    {
        return !(x < y);
    }

    template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
    inline void swap(const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &x, const rb_tree<Key, Val, KeyOfValue, Compare, Alloc> &y)
    {
        x.swap(y);
    }

} // end namespace ft 

#endif
