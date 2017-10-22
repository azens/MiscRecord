/* cJSON Types: */
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

/* The cJSON structure: */
typedef struct cJSON {
	struct cJSON *next,*prev;	/* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
	struct cJSON *child;		/* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */

	int type;					/* The type of the item, as above. */

	char *valuestring;			/* The item's string, if type==cJSON_String */
	int valueint;				/* The item's number, if type==cJSON_Number */
	double valuedouble;			/* The item's number, if type==cJSON_Number */

	char *string;				/* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
} cJSON;
#include <stdio.h>
void print(cJSON node)
{
	printf("name:%s ",node.string);
	switch(node.type) {
	case cJSON_Number:
		printf("type:int value:%d\n",node.valueint);
		break;
	case cJSON_String:
		printf("type:string value:\"%s\"\n",node.valuestring);
		break;
	default:
		break;
	}
}
int main()
{
	cJSON root= {0,0,0,cJSON_String,"hello",0,0.0,"root"};
	print(root);
	return 0;
}