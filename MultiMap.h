#ifndef MULTIMAP_H
#define MULTIMAP_H

// Implementation of MultiMap using BST

//The Iterator class must have a public destructor, copy constructor and assignment
//operator, either declared and implemented by you or left unmentioned so that the
//compiler will generate them for you. If you design your class well, the compiler-
//generated versions of these operations will do the right thing. Each of these
//operations must run in O(1) time.

//#include <string>
#include <cassert>

class MultiMap
{
private:
	typedef BST::iterator BSTIterator;
public:
	class Iterator
	{
	public:
		Iterator() : m_mmap_iter(nullptr) {}
		Iterator(const BST& mm, BSTIterator iter)
		 : m_mmap_iter(iter != mm.end() ? &mm : nullptr), m_iter(iter) {}//check
		bool valid() const { return m_mmap_iter != nullptr; }
		std::string getKey() const { assert(valid()); return m_iter->key; }
		unsigned int getValue() const { assert(valid()); return m_iter->value; }
		bool next()
		{
			if (!valid())
				return false;
			if (++m_iter != m_mmap->end())
				return true;
			m_mmap = nullptr;
			return false;
		}
		bool prev()
		{
			if (!valid())
				return false;
			if (m_iter != m_mmap->begin())
			{
				m_iter--;
				return true;
			}
			m_mmap = nullptr;
			return false;
		}
	private:
		const BST* m_mmap_iter;
		BSTIterator m_iter;
	};

	MultiMap();
	~MultiMap();
	void clear();
	void insert(std::string key, unsigned int value);
	Iterator findEqual(std::string key) const
	{
		MMapIterator p = m_mmap.lower_bound(key);
		if (p == m_mmap.end()  ||  p->first != key)
			return Iterator();
		return Iterator(m_mmap, p);
	}
	Iterator findEqualOrSuccessor(std::string key) const
	{
		MMapIterator p = m_mmap.lower_bound(key);
		if (p == m_mmap.end())
			return Iterator();
		return Iterator(m_mmap, p);
	}
	Iterator findEqualOrPredecessor(std::string key) const
	{
		MMapIterator p = m_mmap.upper_bound(key);
		if (p == m_mmap.begin())
			return Iterator();
		return Iterator(m_mmap, --p);
	}

private:
//	struct valueList{
//		unsigned int value;
//		valueList* next;
//		valueList(unsigned int v){
//			value = v;
//			next = nullptr;
//		}
//	};

	class BST{
		std::string key;
		unsigned int value;
		BST* left;
		BST* right;

		struct iterator{
			std::string key;
			unsigned int value;
		};

		BST(std::string k, unsigned int v){
			key = k;
			left = nullptr;
			right = nullptr;
			value = v;
		}

		void insert(std::string k, unsigned int v){
			if(k <= key){
				if(left == nullptr){
					left = new BST(k,v);
					return;
				}
				else{
					return left->insert(k,v);
				}
			}
			else if(k > key){
				if(right == nullptr){
					right = new BST(k,v);
					return;
				}
				else{
					return right->insert(k,v);
				}
			}
			return;
		}
	};

	BST* m_mmap;

//	void deleteList(valueList* node){//helper function for destructor
//		if(node->next != nullptr){
//			valueList* nextNode = node->next;
//			deleteList(nextNode);
//		}
//		delete node;
//	}

	void deleteMap(BST* node){//helper function for destructor
		if(node != nullptr){
			if(node->left != nullptr){
				deleteMap(node->left);
			}
			if(node->right != nullptr){
				deleteMap(node->right);
			}
			delete node;
		}
	}
	
	  // To prevent MultiMaps from being copied or assigned, declare these members
	  // private and do not implement them.
	MultiMap(const MultiMap& other);
	MultiMap& operator=(const MultiMap& rhs);
};
#endif
