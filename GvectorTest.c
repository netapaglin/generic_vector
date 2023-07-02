#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Gvector.h"
#define SIZE 4
#define BLOCK_SIZE 2

static void DestroyPersons( void* _per);

typedef struct Person Person;
struct Person
{
	int m_id; 
	int m_age;
};

static void TestCreateZero();
static void TestCreateCheckMembers();
static void TestCreateWithAllocation();

static void TestAddWorkNormal();
static void TestAddVectorNULL();
static void TestAddInputNULL();
static void TestAddBlockSize0();

static void TestDestroy();
static void TestDoubleDestroy();
static void TestDestroyWithAllocation();

static void TestRemoveNormal();
static void TestRemoveVectorNULL();
static void TestRemoveValueNULL();
static void TestRemoveSizeZero();

static void TestGetNormal();
static void TestGetVectorNull();
static void TestGetValueNull();
static void TestGetWrongIndex1();
static void TestGetWrongIndex2();

static void TestSetNormal();
static void TestSetValueNull();
static void TestSetVectorNull();
static void TestSetIndexErr();

static void Testprint();
static void TestPrintStruct();
static void TestPrintString();

static void TestVectorSizeNormal();
static void TestVectorSizeNULL();

static void TestCapacityNormal();
static void TestCapacityNULL();



int main (void)
{


	TestCreateZero();
	TestCreateCheckMembers();
	TestCreateWithAllocation();
	
	TestAddWorkNormal();
	TestAddVectorNULL();
	TestAddInputNULL();
	TestAddBlockSize0();
	
	TestDestroy();
	TestDoubleDestroy();
	TestDestroyWithAllocation();
	
	TestRemoveNormal();
	TestRemoveVectorNULL();
	TestRemoveValueNULL();
	TestRemoveSizeZero();
	
	TestGetNormal();
	TestGetVectorNull();
	TestGetValueNull();
    TestGetWrongIndex1();
	TestGetWrongIndex2();
		
	TestSetNormal();
	TestSetValueNull();
	TestSetVectorNull();
	TestSetIndexErr();
	
	Testprint();
	TestPrintStruct();
	TestPrintString();
	
	
	TestVectorSizeNormal();
	TestVectorSizeNULL();
	
	TestCapacityNormal();
	TestCapacityNULL();
	
	
	return 1;
}


	static int PrintIString(void* _element, size_t _index, void* _context)
	{
			
		printf(" %s  ",  ((char*)_element)  );
		return 1;
	}



static void TestPrintString()
{
 	Vector *  vec;
	 char strings[5][20];
	strcpy(strings[0], "This");
    strcpy(strings[1], "is");
    strcpy(strings[2], "array");
     strcpy(strings[3], "of");
      strcpy(strings[4], "strings");
	 vec = VectorCreate(10 , 5);
	VectorAppend(vec , strings);
	VectorAppend(vec , strings +1);
	VectorAppend(vec , strings +2);
	VectorAppend(vec , strings +3);
	VectorAppend(vec , strings +4);

	VectorForEach(vec, PrintIString,  NULL);
	printf("\n");
	VectorDestroy(&vec , NULL);
}



	static int PrintIStruct(void* _element, size_t _index, void* _context)
	{
			
		printf("age - %d   id - %d \n",  (((Person*)_element)->m_age ), (((Person*)_element)->m_id )  );
		return 1;
	}



static void TestPrintStruct()
{
	/*aloocation for every member */
 	Vector *  vec;
 	Person * list;
	 list = (Person*)malloc(5*sizeof(Person));

	 list[0].m_age = 25;
	  list[0].m_id = 15;
	  list[1].m_age = 26;
	  list[1].m_id = 16;
	  list[2].m_age = 27;
	  list[2].m_id = 17;
	 vec = VectorCreate(10 , 5);
	 
	VectorAppend(vec , list);
	VectorAppend(vec , list +1);
	VectorAppend(vec , list +2);

	VectorForEach(vec, PrintIStruct,  NULL);
	
	VectorDestroy(&vec , NULL);
}


static void TestCapacityNULL()
{
	int x = 4 , y = 6 , z = 7;
 	Vector * vec;

	if (VectorCapacity(NULL)  == 0)
	 {
	 	printf("test Capacity NULL - PASS\n");
	 }else
	 {
	 	printf("test Capacity NULL- FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestCapacityNormal()
{
	int x = 4 , y = 6 , z = 7;
 	Vector * vec;
     vec = VectorCreate(2 , 5);
     
     VectorAppend(vec , &y);
     
     VectorAppend(vec , &z);
     
     VectorAppend(vec , &x);

     
	if (VectorCapacity(vec)  == 7)
	 {
	 	printf("test Capacity normal - PASS\n");
	 }else
	 {
	 	printf("test Capacity normal - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestVectorSizeNULL()
{
	int x = 4 , y = 6 , z = 7;
 	Vector * vec;
     vec = VectorCreate(2 , 5);
     
	if (VectorSize(NULL)  == 0)
	 {
	 	printf("test Vector Size NULL - PASS\n");
	 }else
	 {
	 	printf("ttest Vector Size NULL - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestVectorSizeNormal()
{
	int x = 4 , y = 6 , z = 7;
 	Vector * vec;
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &y);
     VectorAppend(vec , &z);
     VectorAppend(vec , &x);
     
	if (VectorSize(vec)  == 3)
	 {
	 	printf("test Vector Size normal - PASS\n");
	 }else
	 {
	 	printf("test Vector Size normal - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}

	static int PrintInt(void* _element, size_t _index, void* _context)
	{
		printf("%d,",   (*(int*)_element));
		return 1;
	}


static void Testprint()
{
	int l = 5 , m = 6 , n = 7, o = 8;
 	Vector * vec;
 	int a = 9;
 	 int context = 1;
     vec = VectorCreate(2 , 5);

     VectorAppend(vec , &l);
     VectorAppend(vec , &m);
     VectorAppend(vec , &n);
     VectorAppend(vec , &o);
	VectorForEach(vec, PrintInt,  NULL);
	printf("\n");
	VectorDestroy(&vec , NULL);
}

/************************************************************************************/

static void TestSetIndexErr()
{
	int l = 5 , m = 6 , n = 7;
 	Vector * vec;
 	int a = 9;
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &l);
     VectorAppend(vec , &m);
     VectorAppend(vec , &n);
	if (VectorSet(vec ,5 , (void*) &a) == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	 {
	 	printf("test Set wrong index - PASS\n");
	 }else
	 {
	 	printf("test Set wrong index - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestSetVectorNull()
{
	int l = 5 , m = 6 , n = 7;
 	Vector * vec;
 	int a = 9;
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &l);
     VectorAppend(vec , &m);
     VectorAppend(vec , &n);
	if (VectorSet(NULL ,1 , (void*) &a) == VECTOR_UNITIALIZED_ERROR)
	 {
	 	printf("test Set _vector  NULL- PASS\n");
	 }else
	 {
	 	printf("test Set _vector  NULL - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}

static void TestSetValueNull()
{
	int l = 5 , m = 6 , n = 7;
 	Vector * vec;
 	int a = 9;
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &l);
     VectorAppend(vec , &m);
     VectorAppend(vec , &n);
	if (VectorSet(vec,1 , NULL) == VECTOR_UNITIALIZED_ERROR)
	 {
	 	printf("test Set value NULL- PASS\n");
	 }else
	 {
	 	printf("test Set value NULL - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestSetNormal()
{
	int l = 5 , m = 6 , n = 7;
 	Vector * vec;
 	int a = 9;
 	int ** num;
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &l);
     VectorAppend(vec , &m);
     VectorAppend(vec , &n);
     VectorSet(vec, 1, (void*) &a);
     VectorGet(vec, 1, (void**)num);
	if (**num == 9)
	 {
	 	printf("test Set normal - PASS\n");
	 }else
	 {
	 	printf("test Set normal - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}



static void TestGetWrongIndex2()
{
	int x = 5 , y = 6 , z = 7;
 	Vector * vec;
 	int * a;
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &y);
     VectorAppend(vec , &z);
     VectorAppend(vec , &x);

	if (VectorGet(vec, -2, (void*)&a)  == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	 {
	 	printf("test Get Wrong Index 2 - PASS\n");
	
	 }else
	 {
	 	printf("ttest Wrong Index 2 - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}



static void TestGetWrongIndex1()
{
	int x = 5 , y = 6 , z = 7;
 	Vector * vec;
 	int * a;
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &y);
     VectorAppend(vec , &z);
     VectorAppend(vec , &x);
	if (VectorGet(vec, 5, (void*)&a) == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	 {
	 	printf("test Get Wrong Index 1 - PASS\n");
	
	 }else
	 {
	 	printf("ttest Wrong Index 1 - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}

static void TestGetValueNull()
{
	Vector * vec;
 	int * a;
     vec = VectorCreate(2 , 5);
	if (VectorGet(vec, 1, NULL) == VECTOR_UNITIALIZED_ERROR)
	 {
	 	printf("test Get pValue NULL - PASS\n");
	 }else
	 {
	 	printf("test Get pValue  NULL - FAIL\n");
	 }
}

static void TestGetVectorNull()
{
	Vector * vec;
 	int * a;
     vec = VectorCreate(2 , 5);
	if (VectorGet(NULL, 1, (void*)&a) == VECTOR_UNITIALIZED_ERROR)
	 {
	 	printf("test Get vector NULL - PASS\n");
	 }else
	 {
	 	printf("test Get vector NULL - FAIL\n");
	 }
}


static void TestGetNormal()
{
	int x = 5 , y = 6 , z = 7;
 	Vector * vec;
	int *ptr ;
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &y);
     VectorAppend(vec , &z);
     VectorAppend(vec , &x);
     VectorGet(vec, 0, (void*)&ptr);
	if (*ptr  == 6)
	 {
	 	printf("test Get normal - PASS\n");
	 }else
	 {
	 	printf("ttest Get normal - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestRemoveSizeZero()
{

 	Vector * vec;
 	int a;
 	void * b =&a;
	VectorResult res;    
	 vec = VectorCreate(2 , 5);
	 res = VectorRemove(vec,&b);
	if (res  == VECTOR_UNDER_FLOW_ERROR)
	 {
	 	printf("test Remove Size 0- PASS\n");
	
	 }else
	 {
	 	printf("test Remove Size 0  - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}

static void TestRemoveValueNULL()
{

 	Vector * vec;
 	int a;
 	void * b =&a;
	VectorResult res;
     vec = VectorCreate(2 , 5);
     
	 res = VectorRemove(vec, NULL);

	if (res  == VECTOR_UNITIALIZED_ERROR)
	 {
	 	printf("test Remove value NULL- PASS\n");
	
	 }else
	 {
	 	printf("ttest Remove value NULL  - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestRemoveVectorNULL()
{
 	Vector * vec;
 	int a;
 	void * b =&a;
	VectorResult res;
     vec = VectorCreate(2 , 5);
        
	 res = VectorRemove(NULL, &b);

	if (res  == VECTOR_UNITIALIZED_ERROR)
	 {
	 	printf("test Remove vector NULL- PASS\n");
	
	 }else
	 {
	 	printf("ttest Remove vector NULL  - FAIL\n");
	 }
}


static void TestRemoveNormal()
{
	int x = 4 , y = 6 , z = 7;
 	Vector * vec;
 	int** a;
 	
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &y);
     VectorAppend(vec , &z);
     VectorAppend(vec , &x);
     
	VectorRemove(vec, (void **)a);

	if (**a  == 4)
	 {
	 	printf("test Remove normal - PASS\n");
	
	 }else
	 {
	 	printf("ttest Remove normal - FAIL\n");
	 }
	  VectorDestroy(&vec , NULL);
}


static void DestroyPersons( void* _per)
{
	free( (Person *)_per);
}

static void TestDestroyWithAllocation()
{
 	Vector *  vec;
 	Person * pers1;
 	 Person * pers2;
	 pers1 = (Person*)malloc( sizeof(Person));
	 pers1-> m_id = 8;
	 pers1 -> m_age = 15;

	 pers2 = (Person*)malloc( sizeof(Person));
	 pers2-> m_id = 2;
	 pers2 -> m_age = 25;
	 
	 vec = VectorCreate(10 , 5);
	 VectorAppend(vec , pers1);
	 VectorAppend(vec , pers2);
	 
	 VectorDestroy(&vec , DestroyPersons);
	 
	 
	 	printf("test Destroy With Allocation- PASS\n");
	 	

}

static void TestDoubleDestroy()
{
	int x = 5 , y = 6 , z = 7;
 	Vector * vec;
 	VectorResult res;
 
     vec = VectorCreate(SIZE , BLOCK_SIZE);
       VectorAppend(vec , &y);
     VectorAppend(vec , &z);
     VectorAppend(vec , &x);

	VectorDestroy(&vec , NULL);
	VectorDestroy(&vec , NULL);
	printf("test double destroy- PASS\n");
	
}


static void TestDestroy()
{
	int x = 5 , y = 6 , z = 7;
 	Vector * vec;
 	VectorResult res;
 
     vec = VectorCreate(SIZE , BLOCK_SIZE);
       VectorAppend(vec , &y);
     VectorAppend(vec , &z);
     VectorAppend(vec , &x);

	VectorDestroy(&vec , NULL);
		 if (vec == NULL)
	 {
	 	printf("test destroy normal - PASS\n");
	
	 }else
	 {
	 	printf("ttest destroy normal - FAIL\n");
	 }

}


static void TestAddWorkNormal()
{
	int x = 5 , y = 6 , z = 7;
	int arr[] = {5, 16, 91, 23, 17 ,26, 8, 15, 4, 62};
 	Vector * vec;
 	VectorResult res;
 
     vec = VectorCreate(2 , 5);
     VectorAppend(vec , &y);
     VectorAppend(vec , &z);
     res = VectorAppend(vec , &x);
	 if (res == VECTOR_SUCCESS && VectorSize(vec) == 3)
	 {
	 	printf("test add works normal - PASS\n");
	
	 }else
	 {
	 	printf("ttest add works normal - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestAddBlockSize0()
{
	int x = 5 , y = 6 , z = 7;
 	Vector * vec;
 	VectorResult res;
 
     vec = VectorCreate(2 , 0);
       VectorAppend(vec , &y);
     VectorAppend(vec , &z);
     res = VectorAppend(vec , &x);

	 if (res == VECTOR_OVER_FLOW_ERROR)
	 {
	 	printf("test add block Size 0 - PASS\n");
	
	 }else
	 {
	 	printf("ttest addi block Size 0- FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}

static void TestAddInputNULL()
{
	int x = 5 , y = 6 , z = 7;
 	Vector * vec;
 	VectorResult res;
 
     vec = VectorCreate(2 , 5);
     res = VectorAppend(vec , NULL);

	 if (res == VECTOR_INPUT_ERROR)
	 {
	 	printf("test add input NULL - PASS\n");
	
	 }else
	 {
	 	printf("ttest addinput NULL- FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}

static void TestAddVectorNULL()
{
	int x = 5 , y = 6 , z = 7;
 	VectorResult res;
     res = VectorAppend(NULL , &x);

	 if (res == VECTOR_UNITIALIZED_ERROR)
	 {
	 	printf("test add vector  NULL - PASS\n");
	
	 }else
	 {
	 	printf("ttest add vector NULL- FAIL\n");
	 }
}




static void TestCreateZero()
{
 Vector *  vec;
	 vec = VectorCreate(0 , 0 );
	 if (vec == NULL)
	 {
	 	printf("test both parameter zero - PASS\n");
	 }else
	 {
	 	printf("test both parameter zero - FAIL\n");
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestCreateCheckMembers()
{
 Vector *  vec;
	 vec = VectorCreate(10 , 5);
	 if (vec != NULL &&
	  GetVectorSize(vec) == 10 &&
	  GetVectorOriginalSize(vec) == 10 &&
	  GetVectorBlockSize(vec) == 5 &&
	  GetVectorNumItems(vec) == 0 
	   )
	 {
	 	printf("test struct members - PASS\n");

	 }else
	 {
		printf("test struct members - FAIL\n"); 
	 }
	 VectorDestroy(&vec , NULL);
}


static void TestCreateWithAllocation()
{
 	Vector *  vec;
 	Person * pers1;
 	 Person * pers2;
	 pers1 = (Person*)malloc( sizeof(Person));
	 pers1-> m_id = 8;
	 pers1 -> m_age = 15;
	 
	
	 pers2 = (Person*)malloc( sizeof(Person));
	 pers2-> m_id = 2;
	 pers2 -> m_age = 25;
	 
	 vec = VectorCreate(10 , 5);
	 VectorAppend(vec , &pers1);
	 VectorAppend(vec , &pers2);
	 
	 
	 if ( GetVectorNumItems(vec) == 2  )
	 {
	 	printf("test create with allocation - PASS\n");

	 }else
	 {
		printf("test create with allocation - FAIL\n"); 
	 }
	 
	  VectorDestroy(&vec , NULL);
}





