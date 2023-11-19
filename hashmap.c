#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked List node
struct mapNode {

	// key is string NOT STRING
	int* key;

	// value is also string NOT STRING
	void* value;
	struct mapNode* next;
};

// like constructor
void setNode(struct mapNode* node, int* key, void* value)
{
	node->key = key;
	node->value = value;
	node->next = NULL;
	return;
};

struct hashMap {

	// Current number of elements in hashMap
	// and capacity of hashMap
	int numOfElements, capacity;

	// hold base address array of linked list
	struct mapNode** arr;
};

// like constructor
void initializeHashMap(struct hashMap* mp)
{

	// Default capacity in this case
	mp->capacity = 100;
	mp->numOfElements = 0;

	// array of size = 1
	mp->arr = (struct mapNode**)malloc(sizeof(struct mapNode*)
									* mp->capacity);
	return;
}

int hashFunction(struct hashMap* mp, int* key)
{
	int bucketIndex;
	int sum = 0, factor = 31;
	printf("hi\n");
	printf("%i", mp->capacity);
	sum = ((sum % mp->capacity)
		+ ((*key) * factor) % mp->capacity)
		% mp->capacity;
	factor = ((factor % __INT16_MAX__)
			* (31 % __INT16_MAX__))
			% __INT16_MAX__;
	bucketIndex = sum;
	return bucketIndex;
}

void insertMap(struct hashMap* mp, int* key, void* value)
{

	// Getting bucket index for the given
	// key - value pair
	int bucketIndex = hashFunction(mp, key);
	struct mapNode* newNode = (struct mapNode*)malloc(sizeof(struct mapNode));

	// Setting value of node
	setNode(newNode, key, value);

	// Bucket index is empty....no collision
	if (mp->arr[bucketIndex] == NULL) {
		mp->arr[bucketIndex] = newNode;
	}

	// Collision
	else {

		// Adding newNode at the head of
		// linked list which is present
		// at bucket index....insertion at
		// head in linked list
		newNode->next = mp->arr[bucketIndex];
		mp->arr[bucketIndex] = newNode;
	}
	return;
}

void delete (struct hashMap* mp, int* key)
{

	// Getting bucket index for the
	// given key
	int bucketIndex = hashFunction(mp, key);
	struct mapNode* prevNode = NULL;

	// Points to the head of
	// linked list present at
	// bucket index
	struct mapNode* currNode = mp->arr[bucketIndex];

	while (currNode != NULL) {

		// Key is matched at delete this
		// node from linked list
		if (*key == *(currNode->key)) {
			// Head node
			// deletion
			if (currNode == mp->arr[bucketIndex]) {
				mp->arr[bucketIndex] = currNode->next;
			}

			// Last node or middle node
			else {
				prevNode->next = currNode->next;
			}
			//free(currNode);
			break;
		}
		prevNode = currNode;
		currNode = currNode->next;
	}
	return;
}

void* search(struct hashMap* mp, int* key)
{

	// Getting the bucket index
	// for the given key
	//printf("%i\n", *key);
	printf("hi\n");
	int bucketIndex = hashFunction(mp, key);
	printf("hi\n");
	//printf("%i\n", bucketIndex);
	// Head of the linked list
	// present at bucket index
	struct mapNode* bucketHead = mp->arr[bucketIndex];
	//printf("hi\n");
	while (bucketHead != NULL) {

		// Key is found in the hashMap
		if (bucketHead->key == key) {
			return bucketHead->value;
		}
		bucketHead = bucketHead->next;
	}

	// If no key found in the hashMap
	// equal to the given key
	
	return NULL;
}
