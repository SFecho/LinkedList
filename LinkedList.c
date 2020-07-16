#include <malloc.h>
#include "LinkedList.h"
#define _DEBUG_

#undef NULL
#define NULL 0

#ifdef _INTEL_GNU_C_
static void memcpy(void * dest, void * src, size_t data_size)
{
    asm ("cld;  \
          rep;  \
          movsb;"
          : /*input list*/
          :"S"(src), "D"(dest),  "c"(data_size) /*output list*/
        );
}
#endif

#ifdef _INTEL_X86_MSVC_
static void memcpy(void * dest, void * src, size_t data_size)
{
    __asm {
            push esi
            push edi
            push ecx
            
            mov esi, src
            mov edi, dest
            mov ecx, data_size
            
            cld
            rep
            movsb
            
            pop ecx
            pop edi
            pop esi
    }
}
#endif

#ifdef _INTEL_X64_MSVC_
static void memcpy(void * dest, void * src, size_t data_size)
{
    __asm {
            push rsi
            push rdi
            push rcx
            
            mov rsi, src
            mov rdi, dest
            mov rcx, data_size
            
            cld
            rep
            movsb
            
            pop rcx
            pop rdi
            pop rsi
    }
}
#endif


static boolean swap(void *first, void *second, size_t data_size)
{
    void * temp = malloc(data_size);
    if( temp == NULL )
        return FALSE;
    memcpy(temp, first, data_size);
    memcpy(first, second, data_size);
    memcpy(second, temp, data_size);
    free(temp);
    return TRUE;
}

/**
*   @author Simon Fu
*   @param  None
*   @return linked_list *
*   get a manager of linked_list
*/



boolean push_front(linked_list * list, void *data, size_t data_size)
{
    if( data == NULL || data_size <= 0)
        return FALSE;
    list_node * new_node = (list_node *)malloc(sizeof(list_node));
    
	
    if( new_node == NULL )
        return FALSE;
    
    new_node->data = malloc(data_size);
    
    if( new_node->data == NULL )
    {
        free(new_node);
        return FALSE;
    }
	
    memcpy(new_node->data, data, data_size);
    
    new_node->next = list->head;
    list->head = new_node;
	
	list->size++;
	
    return TRUE;
}

boolean push_back(linked_list * list, void *data, size_t data_size)
{
	if( data == NULL || data_size <= 0)
        return FALSE;
    list_node * new_node = (list_node *)malloc(sizeof(list_node));
    
	
    if( new_node == NULL )
        return FALSE;
    
    new_node->data = malloc(data_size);
    
    if( new_node->data == NULL )
    {
        free(new_node);
        return FALSE;
    }
	
	memcpy(new_node->data, data, data_size);
	
	list_node **insert_pos = &list->head;
	
	while( *insert_pos != NULL )
		insert_pos = &(*insert_pos)->next;
	
	*insert_pos = new_node;
	
	new_node->next = NULL;
	
	list->size++;
	
	return TRUE;
}


boolean reverse(linked_list * list)
{
	if( list->head == NULL )
		return FALSE;
	list_node * p = list->head;
	list_node *next_p = NULL;
	while( p->next )
	{
		next_p = p->next;
		p->next = next_p->next;
		next_p->next = list->head;
		list->head = next_p;
	}
	return TRUE;
}

boolean release_node_for_data(linked_list * list, void * data)
{
    list_node ** del_search = &list->head;
    list_node *  del_node = NULL;
    
    boolean flag = FALSE;
    
    while( *del_search != NULL )
    {
        if( list->data_cmp( data, (*del_search)->data ) == 0 )
        {
            flag = TRUE;
            del_node = *del_search;
            *del_search = (*del_search)->next;
            free(del_node);
            break;
        }
        del_search = &(*del_search)->next;
    }
	list->size--;
    return flag;
}

boolean release_node_for_index(linked_list * list, int index)
{
    list_node ** del_search = &list->head;
    list_node *  del_node = NULL;
    
    boolean flag = FALSE;
    
    if( index < 0 )
        return flag;
    
    while( *del_search != NULL )
    {
        if( index == 0 )
        {
            flag = TRUE;
            del_node = *del_search;
            *del_search = (*del_search)->next;
            free(del_node);
            break;
        }
        del_search = &(*del_search)->next;
        index--;
    }
    list->size--;
    return flag;
    
}

list_node * const get_node_for_data(linked_list * list, void * data)
{
    list_node * search_node = list->head;
    while( search_node != NULL )
    {
        if( list->data_cmp(data, search_node->data) == 0 )
            break;
        search_node = search_node->next;
    }
    
    return search_node;
}


list_node * const get_node_for_index(linked_list * list, int index)
{
    list_node * search_node = list->head;
    
    if( index < 0 )
        return NULL;
    
    while( search_node != NULL )
    {
        if( index == 0 )
            break;
		index--;
        search_node = search_node->next;
    }
    
    return search_node;
}


void select_sort(linked_list * list)
{
    list_node ** min_node = NULL;
    list_node ** start_node = &list->head;
    list_node ** next_node = NULL;
    
    list_node * temp_min = NULL;
	
	list_node * temp_start =NULL;
	
    while( *start_node != NULL )
    {
        next_node = &(*start_node)->next;
		
        min_node = start_node;
        
        while( *next_node != NULL )
        {
            if( list->data_cmp( (*min_node)->data, (*next_node)->data ) > 0 )
				min_node = next_node;
            next_node = &(*next_node)->next;
        }
        
        if( start_node != min_node )
        {
            temp_min = *min_node;
			temp_start = *start_node;
			*min_node = (*min_node)->next;
			if( (*start_node)->next != *min_node )
			{
				*start_node = (*start_node)->next;
				temp_start->next = *min_node;
				*min_node = temp_start;
			
				temp_min->next = *start_node;
				*start_node = temp_min;
			}
			else
			{
				temp_min->next = *start_node;
				*start_node = temp_min;
			}
        }
		start_node = &(*start_node)->next;
    }
}

static list_node * merge(list_node ** left_list, list_node ** right_list, int (* cmp)(const void * first, const void * second) )
{
	list_node * head = NULL;
	list_node * temp = NULL;
	list_node *tail_sentinal = NULL;
	list_node ** tail = &tail_sentinal;
	
	if( *left_list == NULL )
		return *right_list;
	
	if( *right_list == NULL )
		return *left_list;
	
	while( *left_list != NULL && *right_list != NULL )
	{
		if( cmp( (*left_list)->data, (*right_list)->data ) > 0 )
		{
			temp = (*left_list)->next;			
			if( head == NULL )
				head = *left_list;				
			(*left_list)->next = NULL;
			*tail = *left_list;
			tail = &(*left_list)->next;
			(*left_list) = temp;
		}
		else
		{
			temp = (*right_list)->next;		
			if( head == NULL )
				head = *right_list;
			(*right_list)->next = NULL;
			*tail = *right_list;
			tail = &(*right_list)->next;	
			(*right_list) = temp;		
		}
	}
	if( *left_list != NULL )
		*tail = *left_list;
	
	if( *right_list != NULL )
		*tail = *right_list;
	*left_list = *right_list = NULL;
	return head;
}

void merge_sort(linked_list * list)
{
	list_node *stk[64] = {NULL};
	
	int i = 0;
	int fill = 0;
	
	list_node *carry = NULL;
	list_node *node = NULL;
	if( list->head == NULL )
		return ;
	
	while(list->head)
	{
	 	node = list->head;
		list->head = list->head->next;
		node->next = carry;
		carry = node;
		i = 0;
		while( i < fill && stk[i] != NULL )
		{
			stk[i] = merge( &stk[i], &carry, list->data_cmp);
			carry = NULL;
			swap(&stk[i++], &carry, sizeof(list_node *) );			
		}
		swap(&stk[i], &carry, sizeof(list_node *) );
		if( i == fill )
			fill++;
	}
	
	for( i = 1; i < fill; i++ )
	{
		stk[i] = merge(&stk[i-1], &stk[i], list->data_cmp);
		stk[i-1] = NULL;
	}

	list->head = stk[fill-1];
}

boolean update_cmp(linked_list * list, int ( * data_cmp )( const void * first, const void * second) )
{
	if( data_cmp == NULL )
		return FALSE;
	list->data_cmp = data_cmp;
	return TRUE;
}

linked_list * get_linked_list( int ( * data_cmp )( const void * first, const void * second) )
{
    if( data_cmp == NULL )
        return NULL;
    
    linked_list * list = (linked_list *)malloc( sizeof(linked_list) );
    
    list->size					= 	0;
    list->head 					= 	NULL;
	
    list->data_cmp 				= 	data_cmp;
	list->update_cmp			=	update_cmp;
	list->push_front 			= 	push_front;
	list->push_back	 			= 	push_back;
	list->reverse 				= 	reverse;
	list->release_node_for_data	=	release_node_for_data;
	list->release_node_for_index=	release_node_for_index;
	list->get_node_for_data		=	get_node_for_data;
	list->select_sort			=	select_sort;
	list->merge_sort			=	merge_sort;
	
    return list;
}

void destroy_linked_list(linked_list * list)
{
    list_node * search_ptr = list->head;
    list_node * del_node = NULL;
    while( search_ptr != NULL )
    {
        del_node = search_ptr;
        search_ptr = search_ptr->next;
        free(del_node->data);
        free(del_node);
    }
    free(list);
}

/***********************************
*	linkedlist iterator
***********************************/


boolean has_next(iterator * itr)
{
	return itr->ptr != NULL;
}

list_node * get_next(iterator * itr)
{
	list_node * temp = itr->ptr;
	if( temp == NULL )
		return NULL;
	itr->ptr = itr->ptr->next;
	return temp;	
}

void reset_iterator(iterator * itr, linked_list * list)
{
	itr->ptr = list->head;	
}

iterator * get_iterator(linked_list * list)
{
	iterator * itr = ( iterator * )malloc( sizeof(iterator) );
	itr->ptr = list->head;
	itr->reset_iterator = reset_iterator;
	itr->has_next = has_next;
	itr->get_next = get_next;
	return itr;
}

void destroy_iterator(iterator *itr)
{
	free(itr);
}