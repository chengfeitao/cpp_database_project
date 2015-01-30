#include "MultiMap.h"

MultiMap::MultiMap(){
	m_mmap = nullptr;
}

MultiMap::~MultiMap(){
	deleteMap(m_mmap);
}

void MultiMap::clear(){
	deleteMap(m_mmap);
}

void MultiMap::insert(std::string key, unsigned int value){
	if(m_mmap == nullptr){
		m_mmap = new BST(key,value);
		return;
	}
	else{
		return m_mmap->insert(key,value);
	}
}

