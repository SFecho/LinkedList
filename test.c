#include <stdio.h>
#include "LinkedList.h"
#include "student.h"
#include <stdlib.h>

#define _WINDOWS_

int cmp_no(const void * _f, const void * _s)
{
	student * f = (student *)_f;
	student * s = (student *)_s;
	return  f->no - s->no;
}

int cmp_age(const void * _f, const void * _s)
{
	student * f = (student *)_f;
	student * s = (student *)_s;
	return  f->age - s->age;
}


void menu()
{
	printf("1. add student's information\n");
	printf("2. delete student's information from sno\n");
	printf("3. sort student's information order by sno\n");
	printf("4. sort student's information order by age\n");
	printf("5. output student's information\n");
	printf("6. exit program\n");
}


int main(int argc, char* argv[])
{
	int option;
	
	student stu;
	
	linked_list * list = get_linked_list(cmp_no);
	iterator * itr = get_iterator(list);
	system("cls");
	while(TRUE)
	{
		menu();
		printf("please input option:");
		scanf("%d", &option);
		
		switch(option)
		{
			case 1:
				printf("please input sno:");
				scanf("%d", &stu.no);
				
				printf("please input name:");
				scanf("%s", stu.name);
				
				printf("please input age:");
				scanf("%d", &stu.age);
				
				list->push_front(list, &stu, sizeof(student) );
				
				break;
				
			case 2:
				printf("please input sno:");
				scanf("%d", &stu.no);
				if( list->update_cmp(list, cmp_no) == TRUE )
					list->release_node_for_data(list, &stu.no );
				break;	
			
			case 3:
				if( list->update_cmp(list, cmp_no) == TRUE )
					list->merge_sort(list);
				break;
				
			case 4:
				if( list->update_cmp(list, cmp_age) == TRUE )
					list->merge_sort(list);
			
				break;
			
			case 5:
				{
					list_node * cur_node = NULL;
					student * temp  = NULL;
					printf("sno\tname\tage\n");
					itr->reset_iterator(itr, list);
					while( itr->has_next(itr) == TRUE )
					{
						cur_node = itr->get_next(itr);
						temp =  (student *)( cur_node->data );
						printf("%d\t%s\t%d\n", temp->no, temp->name, temp->age);	
					}
				}
				break;
			case 6:
				destroy_linked_list(list);
				destroy_iterator(itr);
				return 1;
				break;
		}
		system("pause");
		#ifdef _WINDOWS_
		system("cls");
		#endif
		#ifdef _UNIX_
		system("clear");
		#endif
	}
}
