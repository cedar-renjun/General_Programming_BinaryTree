//****************************************************************************************
//!
//! \file    BinaryTree.h
//! \brief   Genernal Binary Tree Model Interface.
//!          You can use uniform Binary Tree API to manager different type of data
//!          element.
//! \version V1.0
//! \author  cedar
//! \date    2013-11-26
//! \email   xuesong5825718@gmail.com
//!
//! \note    Only recursive algorithm is supported in current version.
//! 
//! \bug    
//!          -# Destory/Delete API can not set node pointer to NULL.
//! 
//! \todo
//!          -# Implement Stack Algorithm.
//!          -# Add Usage Example   
//! \license
//!
//! Copyright (c) 2013 Cedar MIT License
//!
//! Permission is hereby granted, free of charge, to any person obtaining a copy
//! of this software and associated documentation files (the "Software"), to deal
//! in the Software without restriction, including without limitation the rights to
//! use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
//! the Software, and to permit persons to whom the Software is furnished to do so,
//! subject to the following conditions:
//!
//! The above copyright notice and this permission notice shall be included in all
//! copies or substantial portions of the Software.
//!
//! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//! IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//! FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//! AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//! LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//! OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//! IN THE SOFTWARE.
///
//****************************************************************************************

#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__

#ifdef __cplusplus
extern "C"
{
#endif

//****************************************************************************************
//!                           CONFIGURE MACRO
//****************************************************************************************

//! Use dynamic allocate function ?
//! If your platform support malloc/free function, then you can use the following
//! functions by uncomment <USE_DYNAMIC_MEMORY> macro.
//! - \ref Tree_NodeCreate
//! - \ref Tree_NodeDestory
//! - \ref Tree_SubTreeDelete_Dynamic
//!
//! \note Default: Allocate function is DISABLED.
//#define USE_DYNAMIC_MEMORY

//! Select Tree algorithm implement type.
//! Binary Tree algorithm can be implemented with two different method:
//! -# Recursive
//! -# Stack
//!
//! \note
//!      - Can only select one at one time.
//!      - Only Recursive algorithm is supported in current version.
//!
#define USE_RECURSIVE_ALGORITHM
//#define USE_STACK_ALGORITHM

//****************************************************************************************
//!                           PUBLIC DATA INTERFACE
//****************************************************************************************

//! \brief  Tree Node typedef
typedef struct TreeNode
{
    struct TreeNode* parent; //!< Parent node.
    struct TreeNode* left  ; //!< Left node.
    struct TreeNode* right ; //!< Right node.
    void*            data  ; //!< User defined data.
}TreeNode_t;

//! Function Return Value.
typedef enum TreeErrorCode
{
    ERR_SUCCESS         ,   //!< Operate Success
    ERR_FAILURE         ,   //!< Operate Failure
    ERR_INVALID_POINTER ,   //!< Invalid pointer
    ERR_MEM             ,   //!< Failure to alloc memory
    ERR_WRONG_PARAM     ,   //!< Input parameters are invalid
    ERR_NODE_EXIST      ,   //!< Node is existing, use for Tree_NodeAppend
} TreeErrorCode_t;

//! \brief Use's Callback function which can be used in tree traverse algorithm.
//! \param Context is Context of execute environment. typical, you can use it
//!        to store the address of data, avoid to use global variable.
//! \param Data is Tree Node data pointer.
typedef int (*TreeCallBackFun_t)(void* Context, void* Data);

//! \brief Append Position: Left child.
//! \note  This macro can be used as input parameter of \ref Tree_NodeAppend.
#define INSERT_POS_LEFT        ((int)0x01)

//! \brief Append Position: Right child.
//! \note  This macro can be used as input parameter of \ref Tree_NodeAppend.
#define INSERT_POS_RIGHT       ((int)0x00)

//****************************************************************************************
//!                           PUBLIC API
//****************************************************************************************

#ifdef USE_DYNAMIC_MEMORY
//****************************************************************************************
//
//! \brief  Create tree node in dynamic method.
//! \retval the address of new node or NULL if memory allocate failure.
//!
//! \note   
//!         -# Please check the valid of return address.
//!         -# MUST uncomment <USE_DYNAMIC_MEMORY> macro in order to use this function.
//!         -# Dynamic API can not be used mix with static API.
//
//****************************************************************************************
extern TreeNode_t* Tree_NodeCreate(void);

//****************************************************************************************
//
//! \brief  Destory tree node in dynamic method.
//!
//! \param  [in] ppNode is the address of tree node pointer.
//! \retval \ref ERR_FAILURE if successed, otherwise return \ref ERR_SUCCESS.
//!
//! \note   
//!         -# MUST uncomment <USE_DYNAMIC_MEMORY> macro in order to use this function.
//!         -# Dynamic API can not be used mix with static API.
//
//****************************************************************************************
extern TreeErrorCode_t Tree_NodeDestory(TreeNode_t **ppNode);

//****************************************************************************************
//
//! \brief  Destory subtree in dynamic method.
//!
//! \param  [in] ppNode is the address of tree node pointer. typical it's the root of a tree.
//! \retval \ref ERR_FAILURE if successed, otherwise return \ref ERR_SUCCESS.
//!
//! \note   
//!         -# MUST uncomment <USE_DYNAMIC_MEMORY> macro in order to use this function.
//!         -# Dynamic API can not be used mix with static API.
//
//****************************************************************************************  
extern TreeErrorCode_t Tree_SubTreeDelete_Dynamic(TreeNode_t** ppNode);

#endif // USE_DYNAMIC_MEMORY

//****************************************************************************************
//
//! \brief  Init existing tree node.
//!
//! \param  [in] pNode is the address of tree node.
//! \retval the address of new node or NULL if memory allocate failure.
//!
//! \note   
//!         -# You must create an tree node by hand before call this function.
//!         -# Dynamic API can not be used mix with static API.
//
//****************************************************************************************
extern void Tree_NodeInit(TreeNode_t* pNode);

//****************************************************************************************
//
//! \brief  Destory tree node in static method.
//!
//! \param  [in] pNode is the address of tree node.
//! \retval \ref ERR_FAILURE if successed, otherwise return \ref ERR_SUCCESS.
//!
//! \note   
//!         -# Dynamic API can not be used mix with static API.
//
//**************************************************************************************** 
extern TreeErrorCode_t Tree_NodeDelete(TreeNode_t* pNode);

//****************************************************************************************
//
//! \brief  Destory subtree in static method.
//!
//! \param  [in] ppNode is the address of tree node pointer. typical it's the root of a tree.
//! \retval \ref ERR_FAILURE if successed, otherwise return \ref ERR_SUCCESS.
//!
//! \note   
//!         -# Dynamic API can not be used mix with static API.
//
//****************************************************************************************
extern TreeErrorCode_t Tree_SubTreeDelete_Static(TreeNode_t** ppNode);


//****************************************************************************************
//! \brief  Get the depth of tree.
//!
//! \param  [in] pNode is the root of tree.
//! \retval the depth of tree checked, it should >= 1, return zero indicates pNode is
//!         an invalid node.
//****************************************************************************************
extern int Tree_DepthGet(TreeNode_t* pNode);

//****************************************************************************************
//! \brief  Set Node value.
//!
//! \param  [in] pNode is the target tree node.
//! \param  [in] Value is the address of data.
//! \retval \ref ERR_SUCCESS if set node value successfully, \ref ERR_INVALID_POINTER
//!         if input parameters contain invalid pointer.
//!
//! \note   The tree node just store the pointer of data, so, we can use this tree
//!         to store any type of data. <General Programming Method>, Here is a code
//!         snippet for you.
//! \code
//!
//! typedef struct STUDENT
//! {
//!     char*   name;
//!     uint8_t age;
//!     uint8_t sex;
//!     uint8_t class;
//! }STUDENT;
//!
//! STUDENT Class_1[20];
//! ...
//!
//! Tree_NodeValueSet(Node[0], (void*)&Class_1[0]);
//!
//! \endcode
//
//****************************************************************************************
extern TreeErrorCode_t Tree_NodeValueSet(TreeNode_t* pNode, void* Value);

//****************************************************************************************
//! \brief  Get Node value.
//!
//! \param  [in] pNode is the target tree node.
//! \retval the address of data that stored in tree node.
//!
//! \note   The tree node just store the pointer of data, so, we can use this tree
//!         to store any type of data. <General Programming Method>, Here is a code
//!         snippet for you.
//! \code
//!
//! typedef struct STUDENT
//! {
//!     char*   name;
//!     uint8_t age;
//!     uint8_t sex;
//!     uint8_t class;
//! }STUDENT;
//!
//! STUDENT Class_1[20];
//! STUDENT* pStudent = NULL;
//! ...
//!
//! pStudent = (STUDENT*) Tree_NodeValueGet(Node[0]);
//!
//! \endcode
//****************************************************************************************
extern void* Tree_NodeValueGet(TreeNode_t* pNode);

//****************************************************************************************
//! \brief  Append an node.
//! This function append an new node to an existing node.
//!
//! \param  [in] pNode is the address of exising node, new node will be
//!         inserted behind it.
//! \param  [in] pNewNode is the address of node that want to insert.
//! \param  [in] Mode control insert point of node.
//!              the parameter can be one of the following value:
//!              - \ref INSERT_POS_LEFT  New node will be appended to left child.
//!              - \ref INSERT_POS_RIGHT New node will be appended to right child.
//!              .
//! \retval \ref ERR_SUCCESS if insert successfully, \ref ERR_INVALID_POINTER if
//!         input parameters contain invalid pointer, \ref ERR_NODE_EXIST if the
//!         child node is not empty, \ref ERR_WRONG_PARAM if Mode parameter is
//!         wrong.
//! \note   This function is designed for tree end node.
//****************************************************************************************
extern TreeErrorCode_t Tree_NodeAppend(TreeNode_t* pNode, TreeNode_t* pNewNode, int Mode);

//****************************************************************************************
//! \brief  Foreach Tree Node.
//! This function visit all tree node in pre-order algorithm.
//!
//! \param  [in] pNode is the root of tree that want to traver.
//! \param  [in] pFun is the user's callback which can do something with every node data
//!              of the tree.
//! \param  [in] Ctx is tree context environment, just for call back function.
//!
//! \retval \ref ERR_SUCCESS if operate successfully, \ref ERR_INVALID_POINTER if
//!         input parameters contain invalid pointer.
//****************************************************************************************
extern TreeErrorCode_t Tree_TravesePreOrder(TreeNode_t* pNode, TreeCallBackFun_t pFun, void* Ctx);

//****************************************************************************************
//! \brief  Foreach Tree Node.
//! This function visit all tree node in in-order algorithm.
//!
//! \param  [in] pNode is the root of tree that want to traver.
//! \param  [in] pFun is the user's callback which can do something with every node data
//!              of the tree.
//! \param  [in] Ctx is tree context environment, just for call back function.
//!
//! \retval \ref ERR_SUCCESS if operate successfully, \ref ERR_INVALID_POINTER if
//!         input parameters contain invalid pointer.
//****************************************************************************************
extern TreeErrorCode_t Tree_TraveseInOrder(TreeNode_t* pNode, TreeCallBackFun_t pFun, void* Ctx);

//****************************************************************************************
//! \brief  Foreach Tree Node.
//! This function visit all tree node in post-order algorithm.
//!
//! \param  [in] pNode is the root of tree that want to traver.
//! \param  [in] pFun is the user's callback which can do something with every node data
//!              of the tree.
//! \param  [in] Ctx is tree context environment, just for call back function.
//!
//! \retval \ref ERR_SUCCESS if operate successfully, \ref ERR_INVALID_POINTER if
//!         input parameters contain invalid pointer.
//****************************************************************************************
extern TreeErrorCode_t Tree_TravesePostOrder(TreeNode_t* pNode, TreeCallBackFun_t pFun, void* Ctx);

#ifdef __cplusplus
}
#endif

#endif // __BINARYTREE_H__
