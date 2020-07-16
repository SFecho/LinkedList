#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define _INTEL_GNU_C_

#define TRUE    (char)1
#define FALSE   (char)0

typedef unsigned char boolean;

typedef struct _list_node list_node;

typedef struct _iterator iterator;

typedef struct _linked_list linked_list;

struct _list_node
{
    void * data;
    list_node * next;
};


struct _linked_list
{
    size_t size;
    list_node * head;
	
    int		( * data_cmp	)				( const void * first, const void * second );
	boolean	( * release_node_for_data)		( linked_list * list, void * data );
	boolean	( * release_node_for_index)		( linked_list * list, int index );
	boolean ( *push_front	)				( linked_list * list, void *data, size_t data_size );
	boolean ( *push_back 	)				( linked_list * list, void *data, size_t data_size );
	list_node * const ( * get_node_for_data)(linked_list * list, void * data);
	list_node * const ( *get_node_for_index)(linked_list * list, int index);
	void 	( *select_sort	)				(linked_list * list);
	void 	( *merge_sort )					(linked_list * list);
	boolean ( *reverse )					(linked_list * list);
	boolean ( * update_cmp)					(linked_list * list, int ( * data_cmp )( const void * first, const void * second) );
};

struct _iterator
{
	list_node * ptr;
	list_node * (* get_next) (iterator * itr);
	boolean  (* has_next) (iterator * itr);
	void (* reset_iterator) (iterator * itr, linked_list * list);
};


/*******************************************************
*   @author Simon Fu
*   @param  function pointer of data comparator
*   @return linked_list *
*   get a manager of linked_list
********************************************************/
linked_list * get_linked_list( int ( * data_cmp )( const void * first, const void * second) );

void destroy_linked_list(linked_list * list);

iterator * get_iterator(linked_list * list);

void destroy_iterator(iterator *itr);

#endif