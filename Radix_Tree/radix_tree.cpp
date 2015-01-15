// Copyright 2015 Maitesin
#include <string>
#include <vector>
#include <iostream>
#include "./radix_tree.h"

template <class T, size_t R>
const T & RadixTree::radix_tree<T,R>::get(const std::string & key) {
	if (roots[key[0]] != nullptr){
		node_ptr<T,R> node (get(roots[key[0]], key, 0));
		if (node != nullptr){
			aux_ret = node->value;
			node.release();
			return aux_ret;
		}
	}
	return def;
}

template <class T, size_t R>
RadixTree::node_ptr<T,R> RadixTree::radix_tree<T,R>::get(RadixTree::node_ptr<T,R> & n,
							 const std::string & key,
							 unsigned int d) {
	if (n != nullptr) {
		if (key.size() < d + n->path.size()) {
			return nullptr;
		}
		else {
			std::string sub = key.substr(d, n->path.size());
			if (n->path == sub) {
				if (key.size() > d + n->path.size()) {
					// Call it again
					return get(n->sons[key[d+n->path.size()]], key, d+n->path.size());
				}
				else {
					// We found it
					if (n->value != T()) {
						return node_ptr<T,R>(n.get());
					}
				}
			}
		}
	}
	return nullptr;
}

template <class T, size_t R>
void RadixTree::radix_tree<T,R>::put(const std::string & key,
				     const T & value) {
	roots[key[0]] = put(std::move(roots[key[0]]), key, value, 0);
	++s;
}

template <class T, size_t R>
RadixTree::node_ptr<T,R> RadixTree::radix_tree<T,R>::put(RadixTree::node_ptr<T,R> n,
							 const std::string & key,
							 const T & value,
							 unsigned int d) {
	if (n != nullptr) {
		if (key.size() < d + n->path.size()) {
			// We have to split this node
			std::string sub_key = key.substr(d, key.size()-d);
			std::string sub_path = n->path.substr(0, sub_key.size());
			if (sub_key == sub_path) {
				// The path for the key already exists, now split a this point.
				split(n, value, sub_path.size());
				return n;
			}
			else {
				// The path does not match. Find where begin the difference and split there
				find_diff_and_split(n, key, value);
				return n;
			}
		}
		else {
			std::string sub_key = key.substr(d, n->path.size());
			if (n->path == sub_key) {
				if (key.size() > d + n->path.size()) {
					// Call it again with the right son and updating the depth
					n->s += n->sons[key[d+n->path.size()]] != nullptr ? 1 : 0;
					// Added 1 to the size of n if the right son is null
					n->sons[key[d+n->path.size()]] = put(std::move(n->sons[key[d+n->path.size()]]), key, value, d+n->path.size());
					return n;
				}
				else {
					// We found it
					n->value = value;
					return n;
				}
			}
			else {
				// The path does not match. Find where begin the difference and split there
				find_diff_and_split(n, key, value);
				return n;
			}
		}
	}
	else {
		// Create a new node with the information remaining
		return node_ptr<T,R>(new node<T,R>(key.substr(d, key.size()-d), value));
	}
}

template <class T, size_t R>
void RadixTree::radix_tree<T,R>::split(RadixTree::node_ptr<T,R> & n,
				       const T & value,
				       unsigned int p) {
	std::string upper_path = n->path.substr(0, p);
	std::string lower_path = n->path.substr(p, n->path.size()-p);
	n->sons[lower_path[0]] = node_ptr<T,R>(new node<T,R>(lower_path, n->value));
	n->value = value;
	n->path = upper_path;
	++n->s;
}

template <class T, size_t R>
void RadixTree::radix_tree<T,R>::find_diff_and_split(RadixTree::node_ptr<T,R> & n,
						     const std::string & key,
						     const T & value) {
	unsigned int p_s = n->path.size();
	unsigned int k_s = key.size();
	unsigned int len = p_s < k_s ? p_s : k_s; // Take the min of both sizes
	for (unsigned int i = 0; i < len; ++i) {
		if (n->path[i] != key[i]){
			split(n, T(), i);
			std::string branch = key.substr(i, key.size()-i);
			n->sons[branch[0]] = node_ptr<T,R>(new node<T,R>(branch, value));
			++n->s;
			return ;
		}
	}
}
						     

template <class T, size_t R>
void RadixTree::radix_tree<T,R>::clean(RadixTree::node_ptr<T,R> n) {
	for (unsigned int i = 0; i < n->r; ++i) {
		if (n->sons[i] != nullptr) clean(std::move(n->sons[i]));
	}
	n.reset();
}

template <class T, size_t R>
bool RadixTree::radix_tree<T,R>::contains(const std::string & key) {
	if (roots[key[0]] != nullptr) {
		return contains(roots[key[0]], key, 0);
	}
	return false;
}

template <class T, size_t R>
bool RadixTree::radix_tree<T,R>::contains(RadixTree::node_ptr<T,R> & n,
					  const std::string & key,
					  unsigned int d) {
	if (n != nullptr) {
		if (key.size() < d + n->path.size()) {
			return false;
		}
		else {
			std::string sub = key.substr(d, n->path.size());
			if (n->path == sub) {
				if (key.size() > d + n->path.size()) {
					// Call it again
					return contains(n->sons[key[d+n->path.size()]], key, d+n->path.size());
				}
				else {
					// We found it
					if (n->value != T()) {
						return true;
					}
				}
			}
		}
	}
	return false;
}


template <class T, size_t R>
void RadixTree::radix_tree<T,R>::remove(const std::string & key) {
	// TODO
}

template <class T, size_t R>
bool RadixTree::radix_tree<T,R>::remove(RadixTree::node_ptr<T,R> & n,
					const std::string & key,
					unsigned int d,
					bool & decrease) {
	// TODO
}


template <class T, size_t R>
std::vector<std::string> RadixTree::radix_tree<T,R>::get_keys() {
	vec_ptr vec;
	vec = vec_ptr(new std::vector<std::string>());
	for (unsigned int i = 0; i < r; ++i)
		if (roots[i] != nullptr)
			gather_keys(roots[i], "", vec);
	return *vec;
}

template <class T, size_t R>
std::vector<std::string> RadixTree::radix_tree<T,R>::get_keys_with_prefix(const std::string & prefix) {
	// TODO
}

template <class T, size_t R>
void RadixTree::radix_tree<T,R>::get_keys_with_prefix(RadixTree::node_ptr<T,R> & n,
						      std::string prefix,
						      unsigned int d,
						      vec_ptr & v) {
	// TODO
}

template <class T, size_t R>
void RadixTree::radix_tree<T,R>::gather_keys(RadixTree::node_ptr<T,R> & n,
					     std::string prefix,
					     vec_ptr & v) {
	if (n->value != def) {
		v->push_back(prefix);
	}
	if (n->s != 0) {
		for (unsigned int i = 0; i < n->r; ++i) {
			if (n->sons[i] != nullptr) {
				gather_keys(n->sons[i], prefix + n->path, v);
			}
		}
	}
}

template <class T, size_t R>
void RadixTree::radix_tree<T,R>::show() {
	std::cout << "new radix tree to show" << std::endl;
	for (auto key : get_keys()) {
		std::cout << key << std::endl;
	}
}
