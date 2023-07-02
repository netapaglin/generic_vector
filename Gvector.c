#include <stdio.h>/* for prints*/
#include<stdlib.h>/* size_t malloc*/
#include "Gvector.h"
#define BLOCK_SIZE_FACTOR 2
#define SIZE_OF_VECTOR _vector -> m_size 

static VectorResult CheakIncrease(Vector *_vector);
static VectorResult CheakIfDelete(Vector *_vector);
static VectorResult CheckParamGetSet(const Vector *_vector ,  size_t _index);
struct Vector
{
	void** m_items;
	size_t m_originalSize; 
	size_t m_size;
	size_t m_numItems;
	size_t m_blockSize;
};


Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
	Vector* vec;
	void**  temp;
	if (_initialCapacity == 0 && _blockSize == 0)
	{
		return NULL;
	}
	vec = (Vector*)malloc( sizeof(Vector));
	 if(vec == NULL)
	 {
		 return NULL;
	 }
	  temp = (void**)malloc( _initialCapacity * sizeof(void*));
	  if(temp == NULL)
	  {
	  		free(vec);
	    	return NULL;
	  }
	 vec->m_items = temp;
	 vec-> m_size = _initialCapacity ;
     vec-> m_originalSize = _initialCapacity ;
     vec-> m_blockSize = _blockSize;
     vec->m_numItems = 0;
	 return vec ;
}


void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{
	size_t i;
	if (_vector != NULL && *_vector != NULL)
	{
	if(_elementDestroy != NULL)
	{
		for(i=0 ; i <(*_vector) -> m_numItems ; ++i)
		{
			_elementDestroy((*_vector) -> m_items[i]);			
		}
	}
	free((*_vector) -> m_items);
	free(*_vector);
	*_vector = NULL;
	}
}


VectorResult VectorAppend(Vector* _vector, void* _item)
{
	VectorResult resault;
	if(_item == NULL)
	{
		return VECTOR_INPUT_ERROR;
	}
	if(_vector == NULL )
	{
	  	 return VECTOR_UNITIALIZED_ERROR;
	}
	if( (resault = CheakIncrease(_vector)) != VECTOR_SUCCESS)
	{
		return resault;
	}
	_vector -> m_items[_vector -> m_numItems] = _item;
    _vector -> m_numItems += 1;
    return VECTOR_SUCCESS;
}



VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
	size_t resault;
    if(_vector == NULL || _pValue == NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_vector ->  m_numItems  == 0 )
	{
		return VECTOR_UNDER_FLOW_ERROR;
	}
	if (SIZE_OF_VECTOR > _vector -> m_originalSize  && 
	(SIZE_OF_VECTOR - _vector -> m_numItems) >=  BLOCK_SIZE_FACTOR * _vector->m_blockSize)
	{
		if( (resault = CheakIfDelete(_vector) ) != VECTOR_SUCCESS)
		{
			return resault;
		}
	}   
  *_pValue = _vector -> m_items[_vector -> m_numItems - 1];
   -- _vector ->  m_numItems ;
   return VECTOR_SUCCESS;
}



VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
	VectorResult res;
	if(_pValue == NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	res = CheckParamGetSet( _vector, _index);
	if (res != VECTOR_SUCCESS)
	{
		return res;
	}
	*(_pValue) = _vector -> m_items[_index];
	 return VECTOR_SUCCESS;
}


VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
	VectorResult res;
	if(_value == NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	res = CheckParamGetSet(_vector, _index);
	if ( res != VECTOR_SUCCESS)
	{
		return res;
	}
	_vector -> m_items[_index] = _value;
 	return VECTOR_SUCCESS;
}



size_t VectorSize(const Vector* _vector)
{
	if(_vector == NULL )
	{
		return 0;
	}
	return _vector -> m_numItems;	
}

size_t VectorCapacity(const Vector* _vector)
{
	if(_vector == NULL )
	{
		return 0;
	}
	return _vector -> m_size;	
}

size_t VectorForEach(Vector* _vector, VectorElementAction _action, void* _context)
{
	size_t i;
	if(_vector == NULL || _action == NULL)
	{
		return;
	}
	for(i = 0 ; i < _vector -> m_numItems; ++i)
	{
		if(_action(_vector -> m_items[i] ,  i , _context) == 0)
		{
			break;	
		}
	}
	return i;
}


static VectorResult CheakIfDelete(Vector *_vector)
{
	void** temp;
	int newSize;

	newSize = _vector -> m_size - (_vector ->m_blockSize)  ;
	temp = (void**)realloc( _vector -> m_items ,newSize  * sizeof(void*)); 
	if(temp == NULL)
	 {
		return VECTOR_REALLOCATION_ERROR;
	 }
	  _vector -> m_size = newSize ; 
	 _vector->m_items = temp; 	
	 return VECTOR_SUCCESS;
}	

static VectorResult CheakIncrease(Vector *_vector)
{
	void** temp;
	int newSize;
	 if (_vector -> m_numItems == _vector -> m_size)
	  {
	   		if (_vector ->m_blockSize == 0 )
	   		{
	   			return VECTOR_OVER_FLOW_ERROR;
	   		} 
	   		newSize =( _vector -> m_size + _vector ->m_blockSize) ;
	   		temp = (void**)realloc( _vector -> m_items ,newSize  * sizeof(void*)); 
	   		if(temp == NULL)
			{
				return VECTOR_REALLOCATION_ERROR;
	 	    }
	 	    _vector -> m_size = newSize ; 	
	 	    _vector -> m_items = 	 temp;
	}	  
	return VECTOR_SUCCESS;
}	

static VectorResult CheckParamGetSet(const Vector *_vector ,  size_t _index)
{
	if(_vector == NULL )
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(	 _index >= _vector -> m_numItems || _index < 0)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	return VECTOR_SUCCESS;
}


size_t GetVectorSize(Vector *_vector)
{
	return _vector -> m_size;
}

size_t GetVectorOriginalSize(Vector *_vector)
{
	return _vector -> m_originalSize;
}

size_t GetVectorNumItems(Vector *_vector)
{
	return _vector -> m_numItems;
}

size_t GetVectorBlockSize(Vector *_vector)
{
	return _vector -> m_blockSize;
}

