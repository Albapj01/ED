/**
 * @file avltree_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <cassert>

#include "avltree.hpp"

/****
 * AVLTNode class implementation.
 ****/


template <class T>
AVLTNode<T>::AVLTNode (T const& it, AVLTNode<T>::Ref parent,
                       AVLTNode<T>::Ref left, AVLTNode<T>::Ref right)
{
    //TODO
    _item = it;
    _parent = parent;
    _left = left;
    _right = right;
    compute_height();
    //
    assert(check_height_invariant());
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const& it,
                                              AVLTNode<T>::Ref parent,
                                              AVLTNode<T>::Ref left,
                                              AVLTNode<T>::Ref right)
{
    return std::make_shared< AVLTNode<T> > (it, parent, left, right);
}

template <class T>
T AVLTNode<T>::item() const
{
    T value;
    //TODO
    value = _item;
    //
    return value;
}

template <class T>
int AVLTNode<T>::height() const
{
    int height=0;
    //TODO
    height = _height;
    //
    return height;
}

template <class T>
int AVLTNode<T>::balance_factor() const
{
    int bf = 0;
    //TODO
    int height_l = 0, height_r = 0;
    if(_right!=nullptr)
    {
        height_r = _right->height()+1;
    }
    if(_left!=nullptr)
    {
        height_l = _left->height()+1;
    }

    bf = height_r-height_l;
    //
    return bf;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::parent() const
{
    AVLTNode<T>::Ref node;
    //TODO
    node = _parent;
    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::left() const
{
    AVLTNode<T>::Ref node;
    //TODO
    node = _left;
    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::right() const
{
    AVLTNode<T>::Ref node;
    //TODO
    node = _right;
    //
    return node;
}

template <class T>
bool AVLTNode<T>::check_height_invariant () const
{
    bool ret_val = false;
    //TODO
    int height_l = -1, height_r = -1;
    if(_left!=nullptr)
    {
        height_l = _left->height();
    }
    if(_right!=nullptr)
    {
        height_r = _right->height();
    }
    if(_height == std::max(height_l,height_r)+1)
    {
        ret_val = true;
    }
    //
    return ret_val;
}

template <class T>
void AVLTNode<T>::set_item(const T& new_it)
{
    //TODO
    _item = new_it;
    //
    assert(item()==new_it);
}

template <class T>
void AVLTNode<T>::set_parent(AVLTNode<T>::Ref new_parent)
{
    //TODO
    _parent = new_parent;
    //
    assert(parent()==new_parent);
}


template <class T>
void AVLTNode<T>::set_left(AVLTNode<T>::Ref new_child)
{
    //TODO
    //Remember to update the height property.
    _left = new_child;
    compute_height();
    //
    assert(check_height_invariant());
    assert(left()==new_child);
}

template <class T>
void AVLTNode<T>::set_right(AVLTNode<T>::Ref new_child)
{
    //TODO
    //Remember to update the height property.
    _right = new_child;
    compute_height();
    //
    assert(check_height_invariant());
    assert(right()==new_child);
}

template <class T>
void AVLTNode<T>::compute_height()
{
    //TODO
    //Remember: we want O(1) here.
    int height_l = -1, height_r = -1;
    if(_left!=nullptr)
    {
        height_l = _left->height();
    }
    if(_right!=nullptr)
    {
        height_r = _right->height();
    }
    _height = std::max(height_l,height_r)+1;
    //
    assert(check_height_invariant());
}

/***
 * AVLTree class implementation.
 ***/

template <class T>
AVLTree<T>::AVLTree ()
{
    //TODO
    _root = nullptr;
    _current = nullptr;
    _parent = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(is_empty());
}

template <class T>
AVLTree<T>::AVLTree (T const& item)
{
    //TODO
    create_root(item);
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create ()
{
    return std::make_shared< AVLTree<T> >();
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create (T const& item)
{
    return std::make_shared<AVLTree<T>> (item);
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::istream& in) noexcept(false)
{
    auto tree = AVLTree<T>::create();
    std::string token;
    //TODO
    in >> token;
    if (!in)
    {
        throw std::runtime_error("Wrong input format.");
    }

     if (token == "[")
    {
        T newItem;
        in >> newItem;
        tree->create_root(newItem);
        auto l_subtree = AVLTree<T>::create(in);
        auto r_subtree = AVLTree<T>::create(in);
        tree->set_left(l_subtree);
        tree->set_right(r_subtree);
        in >> token;
    }
    else if (token != "[]")
    {
        throw std::runtime_error("Wrong input format.");
    }
    //
    if (! tree->is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (! tree->is_a_balanced_tree())
        throw std::runtime_error("It is not an avl bstree");
    return tree;
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create an perfectly balanced BSTree by inserting the median of
 *        an ordered sub sequence data[begin, end).
 * @param data is the ordered sequence of values.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of array data to use.
 * @pre 0 <= begin <= end <=data.size()
 * @pre begin==end || data[begin]<data[end];
 */
template<class T>
void create_inserting_median(std::vector<T> const& data,
                             size_t begin,
                             size_t end,
                             typename AVLTree<T>::Ref& tree)
{
    assert(begin<=end);
    assert(end<=data.size());
    assert(begin==end || data[begin]<=data[end-1]);

    //TODO
    //Hint: if (end==begin) none thing must be done (it is an empty sub array)
    // else, insert the median in the tree and (recursively) process
    // the two sub sequences [begin, median_idx) and [median_idx+1, end)
    if((end-begin) > 0)
    {
        tree->insert(data[begin+((end-begin)/2)]);
        create_inserting_median(data,begin,begin+((end-begin)/2),tree);
        create_inserting_median(data,(begin+((end-begin)/2))+1,end,tree);
    }
    //
}

template<class T>
typename AVLTree<T>::Ref
create_perfectly_balanced_bstree(std::vector<T> & data)
{
    typename AVLTree<T>::Ref tree = AVLTree<T>::create();
    //TODO
    //Remember: the empty tree is perfectly balanced.
    //Remember: first, an ordered sequence (using < order) of values is needed.
    //Then you should use the above create_inserting_median function
    //on a empty tree to recursively create the perfectly balanced bstree.
    std::sort(data.begin(),data.end());
    create_inserting_median(data,0,data.size(),tree);
    //
    assert(tree != nullptr);
    return tree;    
}
#endif //__ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty () const
{
    bool empty = false;
    //TODO
    empty = _root==nullptr;
    //
    return empty;
}

template <class T>
T AVLTree<T>::item() const
{
    assert(!is_empty());
    T value;
    //TODO
    value = _root->item();
    //
    return value;
}

template <class T>
std::ostream& AVLTree<T>::fold(std::ostream& out) const
{
    //TODO
    if(is_empty())
    {
        out << "[]";
    }
    else
    {
        out << "[ ";
        out << item() << " ";
        left()->fold(out);
        out << " ";
        right()->fold(out);
        out << " ]";
    }
    //
    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    bool exists = false;
    //TODO
    auto aux = _root;

    while(true)
    {
        if(_current==nullptr)
        {
            exists = false;
            break;
        }

        if(_current->item() > aux->item())//bajo por la derecha
        {
            if(aux->right()!=nullptr)
            {
                aux = aux->right();
            }
            else
            {
                exists = false;
                break;
            }
        }
        else if(_current->item() < aux->item())//bajo la izquierda
        {
            if(aux->left()!=nullptr)
            {
                aux = aux->left();
            }
            else
            {
                exists = false;
                break;
            }
        }
        else
        {
            exists = true;
            break;
        }
    }
    //
    return exists;
}

template <class T>
T AVLTree<T>::current() const
{
    assert(current_exists());
    T value;
    //TODO
    value = _current->item();
    //
    return value;
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    //TODO
    auto aux = _root;
    while(aux!=_current)
    {
        if(aux->item() > _current->item())
        {
            aux = aux->left();
        }
        else if (aux->item() < _current->item())
        {
            aux = aux->right();
        }

        level++;

    }
    //
    return level;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::left() const
{
    assert(!is_empty());
    typename AVLTree<T>::Ref subtree;
    //TODO
    subtree = AVLTree<T>::create();
    if(_root->left()!=nullptr)
    {
      subtree->create_root(_root->left()->item());
      subtree->_root->set_left(_root->left()->left());
      subtree->_root->set_right(_root->left()->right());
      subtree->_root->set_parent(nullptr);
    }
    //
    return subtree;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::right() const
{
    assert(!is_empty());
    typename AVLTree<T>::Ref subtree;
    //TODO
    subtree = AVLTree<T>::create();
    if(_root->right()!=nullptr)
    {
      subtree->create_root(_root->right()->item());
      subtree->_root->set_left(_root->right()->left());
      subtree->_root->set_right(_root->right()->right());
      subtree->_root->set_parent(nullptr);
    }
    //
    return subtree;
}

template <class T>
int AVLTree<T>::size() const
{
    int s = 0;
    //TODO
    if (!is_empty())
    {
        s = 1 + left()->size() + right()->size();
    }
    //
    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = 0;
    //TODO
    //Remenber: we want O(1) here.
    if(!is_empty())
    {
        h = _root->height();
    }
    //
    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
#ifdef __ONLY_BSTREE__
    return 0;
#else
    int bf = 0;
    //TODO
    if(!is_empty())
    {
        bf = _root->balance_factor();
    }
    //
    return bf;
#endif
}

template <class T>
bool AVLTree<T>::has(const T& k) const
{
#ifndef NDEBUG
  bool old_current_exists = current_exists();
  T old_current;
  if (old_current_exists)
      old_current = current();
#endif

  bool found = true;

  //TODO
  //Hint: you can reuse the search method for this but in this case you will
  //      need to use "const_cast" to remove constness of "this" and
  //      save/restore the old state of current before returning.

  auto aux = _root;

  while(true)
  {
    if(k < aux->item())
    {
        if(aux->left()!=nullptr)
        {
            aux = aux->left();
        }
        else
        {
            found = false;
            break;
        }
    }
    else if( k > aux->item())
    {
        if(aux->right()!=nullptr)
        {
            aux = aux->right();
        }
        else
        {
            found = false;
            break;
        }
    }
    else
    {
        break;
    }
    }
  //

#ifndef NDEBUG
  assert (!old_current_exists || old_current == current());
#endif
  return found;
}

/**
 * @brief infix process of a node.
 * The Processor must allow to be used as a function with a parameter  (the
 * item to be processed) and returning true if the process must continue or
 * false if not.
 * @param node is the node to be processed.
 * @param p is the Processor.
 * @return true if all the tree was in-fix processed.
 */
template <class T, class Processor>
bool
infix_process(typename AVLTNode<T>::Ref node, Processor& p)
{
    bool retVal = true;
    //TODO
    //Remember: if node is nullptr return true.
    if(node!=nullptr)
    {
        retVal = infix_process<T>(node->left(),p);

        retVal = retVal && p(node->item());

        retVal = retVal && infix_process<T>(node->right(),p);
    }
    //
    return retVal;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    //TODO
    //Remenber: a empty tree is a binary searh tree.
    //
    //Remenber: for a non empty binary search tree, the in-fix traversal from
    //the root node must follow an ordered sequence of items.
    //
    //Remember: use a lambda function with signature '(T v) -> bool' to
    // implement the Processor.
    //
    if(!is_empty())
    {
        std::vector<T> v;
        auto p = [&v](T const &it)
        {
            v.push_back(it);
            return std::is_sorted(v.begin(),v.end());
        };
        is_bst = infix_process<T>(_root,p);
    }
    //
    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    bool is_balanced = true;
    //TODO
    //Remenber: a empty tree is balanced.
    //
    //Remenber: A non empty tree is balanced if both children are balanced
    //and the absolute value of the balance factor of the tree is less or
    //equal to one.
    if(is_empty()==false)
    {
        is_balanced = ( 
            std::abs(balance_factor())<=1 
            && left()->is_a_balanced_tree() 
            && right()->is_a_balanced_tree() );
    }
    //
    return is_balanced;
#endif
}

template <class T>
void AVLTree<T>::create_root(T const& v)
{
    assert(is_empty());
    //TODO
    _root = AVLTNode<T>::create(v,nullptr,nullptr,nullptr);
    _current = _root;
    _parent = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item()==v);
}

template <class T>
bool AVLTree<T>::search(T const& k)
{
    bool found = false;
    //TODO
    _current = _root;
    _parent = nullptr;
    while (_current!=nullptr and not found)
    {
        if(_current->item() == k)
        {
            found = true;
        }
        else
        {
            _parent = _current;
            if(_current->item() > k)
            {
                _current = _current->left();
            }
            else
            {
                _current = _current->right();
            }
        }
    }
    //
    assert(!found || current()==k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const& k)
{
    //Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    if (!search(k))
    {        
        //TODO
        if(is_empty())
        {
            _current = AVLTNode<T>::create(k,nullptr,nullptr,nullptr);;
            _root = _current;
        }
        else
        {
            _current = AVLTNode<T>::create(k,_parent,nullptr,nullptr);
            if(_parent->item() > k)
            {
                _parent->set_left(_current);
            }
            else
            {
                _parent->set_right(_current);
            }
        }
        //
        make_balanced();
    }

    //Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    //check postconditions.
    assert(current_exists());
    assert(current()==k);
}

template <class T>
void AVLTree<T>::remove ()
{
    //check preconditions.
    assert(current_exists());

#ifndef NDEBUG
    //the invariants only must be checked for the first recursive call.
    //We use a static variable to count the recursion levels.
    //see section "Static variables in a Function" in
    //ref https://www.geeksforgeeks.org/static-keyword-cpp/ for more info.
    static int recursion_count = 0;
    recursion_count++;
    if (recursion_count==1)
    {
        //Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());
    }
#endif //NDEBUG

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    //TODO
    // Check which of cases 0,1,2,3 we have (see theorical class slides).

    if(_current->left()==nullptr and _current->right()==nullptr)
    {
        subtree = nullptr;
    }
    else if(_current->right()==nullptr)
    {
        subtree = _current->left();
    }
    else if(_current->left()==nullptr)
    {
        subtree = _current->right();
    }
    else
    {
        replace_with_subtree = false;
    }
    //

    if (replace_with_subtree)
    {   
        //TODO
        //Manage cases 0,1,2
        if(_parent ==nullptr)
        {
            _root = subtree;
        }
        else if(_parent->right() == _current)
        {
            _parent -> set_right(subtree);
        }
        else
        {
            _parent->set_left(subtree);
        }

        _current = nullptr;

        //
        make_balanced();
    }
    else
    {
        //TODO
        //Manage case 3.
        auto aux = _current;
        find_inorder_sucessor();
        aux->set_item(_current->item());
        remove();

        //
    }

#ifndef NDEBUG
    //We come back so the recursion count must be decreased.
    recursion_count--;
    assert(recursion_count>=0);
    if (recursion_count==0)
    {
        //Only check for the last return.
        //Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());

        //Check postconditions.
        assert(! current_exists());
    }
#endif
}

template <class T>
AVLTree<T>::AVLTree (typename AVLTNode<T>::Ref root_node)
{
    //TODO
    create_root(root_node);
    //
    assert(!current_exists());
}

template <class T>
typename AVLTree<T>::Ref  AVLTree<T>::create (typename AVLTNode<T>::Ref root)
{
     AVLTree<T>::Ref ret_v (new AVLTree<T>(root));
     return ret_v;
}

template <class T>
void AVLTree<T>::set_left(Ref subtree)
{
    assert(!is_empty());
    //TODO
    //Remenber to set parent's link of the subtree root to this.
    if(not subtree->is_empty())
    {
        auto nuevo = AVLTNode<T>::create(subtree->_root->item(),_root,subtree->_root->left(),subtree->_root->right());
        nuevo->compute_height();
        _root->set_left( nuevo );
    }
    else
    {
        _root->set_left( nullptr );
    }

    //
    assert(subtree->is_empty() || left()->item()==subtree->item());
    assert(!subtree->is_empty() || left()->is_empty());
}

template <class T>
void AVLTree<T>::set_right(Ref subtree)
{
    assert(!is_empty());
    //TODO
    //Remenber to set parent's link of the subtree root to this.

    if(not subtree->is_empty())
    {
        auto nuevo = AVLTNode<T>::create(subtree->_root->item(),_root,subtree->_root->left(),subtree->_root->right());
        nuevo -> compute_height();
        _root->set_right( nuevo );
    }
    else
    {
        _root->set_right( nullptr );
    }

    //
    assert(subtree->is_empty()|| right()->item()==subtree->item());
    assert(!subtree->is_empty()|| right()->is_empty());
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::current_node() const
{
    typename AVLTNode<T>::Ref node;
    //TODO
    node = _current;
    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::root_node() const
{
    typename AVLTNode<T>::Ref node;
    //TODO
    node = _root;
    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::parent_node() const
{
    typename AVLTNode<T>::Ref node;
    //TODO
    node = _parent;
    //
    return node;
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
    assert(is_a_binary_search_tree());

#ifndef NDEBUG
    T old_curr = current();
#endif
    //TODO
    _parent = _current;
    _current = _current->right();

    while(_current->left()!=nullptr)
    {
        _parent = _current;
        _current = _current->left();
    }
    //
    assert(current_exists() && current_node()->left()==nullptr);
#ifndef NDEBUG
    assert(current()>old_curr);
#endif
}

template <class T>
void AVLTree<T>::rotate_left(typename AVLTNode<T>::Ref node)
{
    assert(node->left()!=nullptr);
    //TODO
    //Remenber: when set a node A as child of a node B, also is needed set
    // node B as parent of node A.
    //Remenber: update the node height at the end.
    auto lC = node->left();

    if(node->parent()==nullptr)
    {
        _root = lC;
    }
    else if(node->parent()->right() == node)
    {
        node->parent()->set_right(lC);
    }
    else
    {
        node->parent()->set_left(lC);
    }

    lC->set_parent(node->parent());

    if( lC->right()!=nullptr)
    {
        node->set_left(lC->right());
        lC->right()->set_parent(node);
    }
    else
    {
        node->set_left(nullptr);
    }

    lC->set_right(node);
    node->set_parent(lC);

    node->compute_height();
    lC->compute_height();
    //
}

template <class T>
void AVLTree<T>::rotate_right(typename AVLTNode<T>::Ref node)
{
    assert(node->right()!=nullptr);
    //TODO
    //Remenber: when set a node A as child of a node B, also is needed set
    // node B as parent of node A.
    //Remenber: update the node height at the end.

    auto rC = node->right();

    if(node->parent()==nullptr )
    {
        _root = rC;
    }
    else if(node->parent()->right() == node)
    {
        node->parent()->set_right(rC);
    }
    else
    {
        node->parent()->set_left(rC);
    }

    rC->set_parent(node->parent());

    if(rC->left()!=nullptr)
    {
        node->set_right(rC->left());
        rC->left()->set_parent(node);
    }
    else
    {
        node->set_right(nullptr);
    }

    rC->set_left(node);
    node->set_parent(rC);

    node->compute_height();
    rC->compute_height();

    //
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return;
#else
    //TODO
    //From current position, go up until root's node is achieved.
    //In each step, check if the current subtree is balanced and balance it
    //   if it is not.
    //Remenber: use parent_ to travel to the root and restore it properly at
    //the end.
    //
    while (_parent!=nullptr)
    {
        _parent->compute_height();
        int bfP = _parent->balance_factor();

        if (bfP < -1)
        {
            auto child = _parent->left();
            int bfC = child->balance_factor();

            if (bfC <= 0)
            {
                rotate_left(_parent);
            }
            else
            {
                rotate_right(child);
                rotate_left(_parent);
            }
        }
        else if (bfP > 1)
        {
            auto child = _parent->right();
            int bfC = child->balance_factor();

            if (bfC >= 0)
            {
                rotate_right(_parent);
            }
            else
            {
                rotate_left(child);
                rotate_right(_parent);
            }
        }
        else
        {
            _parent = _parent->parent();
        }
    }

    if(current_exists())
    {
        _parent = _current->parent();
    }

    //
    assert(!current_exists() || current_node()->parent()==parent_node());
#endif //__ONLY_BSTREE__
}
