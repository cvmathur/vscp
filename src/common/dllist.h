///////////////////////////////////////////////////////////////////////////////
// dllist.h
//
//  Copyright (C) 2000-2016 Ake Hedman, Grodans Paradis AB, akhe@grodansparadis.com 
//
// This software is placed into
// the public domain and may be used for any purpose.  However, this
// notice must not be changed or removed and no warranty is either
// expressed or implied by its publication or distribution.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef H_DLLIST_H
#define H_DLLIST_H

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#ifdef __cplusplus
extern "C" {
#endif


    /*!
      A base class to derive from for object storage
     */

    struct dllnode {
        /*!
          String key used for alphanumeric sort
         */
        char *pstrKey;

        /*!
          Numeric key used for numeric sort
         */
        unsigned long *pKey;

        /*!
          Sort key (can be used if no other key is abailabe ). pKey should
          be pointing to this key if used.
         */
        unsigned long Key;

        /*!
          A pointer to the embedded node object
         */
        void *pObject;

        /*!
          A long that can be used in any way a user likes.
         */
        unsigned long obid;

        /*!
          Pointer to the next node
         */
        struct dllnode *pNext;


        /*!
          Pointer to the previous node
         */
        struct dllnode *pPrev;

    };

    /*!
        Methods to handle a node for the double linked list
     */

    /*!
        Sorttypes for the list
     */

    //enum _sorttype { SORT_NONE = 0, SORT_STRING, SORT_NUMERIC };

#define SORT_NONE           0
#define SORT_STRING         1
#define SORT_NUMERIC        2

    struct DoubleLinkedList {
        /*!
          Sort order
          ==========

          0 - not sorted.
          1 - sort on string key.
          2 - sort on numeric key.
     
          Note that items can be retrived in accending/decending order by 
          retriving them from the head or from the tail of the list.
         */
        unsigned char nSortOrder;

        /*!
          Pointer to the head of the linked list
         */
        struct dllnode *pHead;

        /*!
          Pointer to the tail of the linked list
         */
        struct dllnode *pTail;

        /*!
          Number of elements in list
         */
        unsigned long nCount;

    };


    /*!
      Initialize the double linked list
     */
    void dll_init(struct DoubleLinkedList *, unsigned char);

    /*!
      Add a node to the front of the linked list.
     */
    BOOL dll_addNodeHead(struct DoubleLinkedList *, struct dllnode *);


    /*!
      Add a node to the end of the linked list.
     */
    BOOL dll_addNodeTail(struct DoubleLinkedList *, struct dllnode *);


    /*!
      Add a node before another node
     */
    BOOL dll_addNodeBefore(struct DoubleLinkedList *pdll,
        struct dllnode *pNode,
        struct dllnode *pInsertNode);

    /*!
      Add a node after another node.
     */
    BOOL dll_addNodeAfter(struct DoubleLinkedList *pdll,
        struct dllnode *pNode,
        struct dllnode *pInsertNode);


    /*!
      Add a node sorted by the current sort order 
     */
    BOOL dll_addNode(struct DoubleLinkedList *, struct dllnode *);

    /*!
      Remove all nodes form the linked list.
     */
    BOOL dll_removeAllNodes(struct DoubleLinkedList *);

    /*!
      Get node from its numerical key
   
      @param Numerical key for node.
      @return Found Object
      @return NULL if no match found.
     */
    struct dllnode * dll_findNodeFromID(struct DoubleLinkedList *, unsigned long);

    /*!
      Get node from its string key
   
      @param String key for node.
      @return Found Object
      @return NULL if no match found.
     */
    struct dllnode * dll_findNodeFromString(struct DoubleLinkedList *, char *);

    /*!
      Insert a node and an object between two other nodes 
     */
    BOOL dll_insertNode(struct DoubleLinkedList *pdll,
        struct dllnode *pNode1,
        struct dllnode *pNode2);

    /*!
      Remove a node from the double linked list
     */
    BOOL dll_removeNode(struct DoubleLinkedList *pdll,
        struct dllnode *pNode);

    /*!
      Get the node count for the list
     */
    unsigned long dll_getNodeCount(struct DoubleLinkedList *pdll);



#ifdef __cplusplus
}
#endif

#endif // H_DDLIST_H
