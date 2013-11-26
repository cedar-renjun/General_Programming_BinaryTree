//******************************************************************************
//!
//! \file    BinaryTree.c
//! \brief   Genernal Binary Tree Implement
//!          You can use uniform Binary Tree API to manager different type of data
//!          element.
//! \version V1.0
//! \author  cedar
//! \date    2013-11-26
//! \email   xuesong5825718@gmail.com
//! \note    Only recursive algorithm is supported in current version.
//! 
//! \bug    
//!          -# Destory/Delete API can not set node pointer to NULL.
//! 
//! \todo
//!          -# Implement Stack Algorithm.
//!          -# Add Usage Example
//!
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
//******************************************************************************

#include "BinaryTree.h"

#ifdef   USE_DYNAMIC_MEMORY
#include <stdio.h>
#include <stdlib.h>
#endif

//! \internal
//! \brief The mask of append mode parameters.
#define INSERT_MODE_MASK         (INSERT_POS_LEFT  | INSERT_POS_RIGHT)

//**************************************************************************************
//!                     ASSERT MACRO
//**************************************************************************************
#ifndef ASSERT

#ifdef  NDEBUG
#define ASSERT(x)
#else
#define ASSERT(x) do {while(!(x));} while(0)
#endif

#endif  // ASSERT

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
TreeNode_t* Tree_NodeCreate(void)
{
    //! Allocate memory for tree node.
    TreeNode_t* pNode = (TreeNode_t *)malloc(sizeof(TreeNode_t));
    if(NULL == pNode)
    {
        return (NULL);
    }

    //! Initialize the node field.
    Tree_NodeInit(pNode);

    return (pNode);
}

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
TreeErrorCode_t Tree_NodeDestory(TreeNode_t **ppNode)
{
    TreeNode_t* pNode       = NULL;           //!< Pointer of Node
    TreeErrorCode_t ErrCode = ERR_FAILURE;    //!< Error Code

    //! Check mode parameter.
    ASSERT(NULL != ppNode);

    pNode   = *ppNode;

    //! Delete Tree Node
    ErrCode = Tree_NodeDelete(pNode);
    if(ERR_SUCCESS != ErrCode)
    {
        return (ErrCode);
    }

    //! Release Node From Tree Successfully, Now release node resource.
    free(pNode);
    *ppNode = NULL;

    return (ERR_SUCCESS);
}

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
TreeErrorCode_t Tree_SubTreeDelete_Dynamic(TreeNode_t** ppNode)
{
    TreeNode_t * pNode = NULL;

    //! Check input parameter
    ASSERT(NULL != ppNode);
    pNode = *ppNode;

    //! Check input parameter.
    if(NULL == pNode)
    {
        return  ERR_FAILURE;
    }

    Tree_SubTreeDelete_Dynamic(&pNode->left);
    Tree_SubTreeDelete_Dynamic(&pNode->right);

    //! \bug Can not set node value to NULL
    Tree_NodeDestory(ppNode);

    return (ERR_SUCCESS);
}

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
void Tree_NodeInit(TreeNode_t* pNode)
{
    //! Check input parameter
    ASSERT(NULL != pNode);

    pNode->parent = NULL;   //!< Init parent pointer field.
    pNode->left   = NULL;   //!< Init left child pointer field.
    pNode->right  = NULL;   //!< Init right child pointer field.
    pNode->data   = NULL;   //!< Init data pointer field.
}

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
TreeErrorCode_t Tree_NodeDelete(TreeNode_t* pNode)
{
    //! Check input parameter
    ASSERT(NULL != pNode);

    //! Check left/right child node, This function only delete leaf node.
    if(NULL != pNode->left || NULL != pNode->right)
    {
        return (ERR_FAILURE);
    }

    //! If node has parent node, then break the link between them.
    if(NULL != pNode->parent)
    {
        TreeNode_t * pParent = pNode->parent;

        //! Update parent's child pointer.
        if(pParent->left == pNode)
        {
            pParent->left = NULL;
        }

        if(pParent->right == pNode)
        {
            pParent->right = NULL;
        }
    }

    //! Reset Node Field.
    Tree_NodeInit(pNode);

    return (ERR_SUCCESS);
}

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
TreeErrorCode_t Tree_SubTreeDelete_Static(TreeNode_t** ppNode)
{
    TreeNode_t * pNode = NULL;

    //! Check input parameter
    ASSERT(NULL != ppNode);
    pNode = *ppNode;

    //! Check input parameter.
    if(NULL == pNode)
    {
        return  ERR_FAILURE;
    }

    Tree_SubTreeDelete_Static(&pNode->left);
    Tree_SubTreeDelete_Static(&pNode->right);

    Tree_NodeDelete(pNode);

    //! \bug Can not set node value to NULL
    *ppNode = NULL;

    return (ERR_SUCCESS);
}


//****************************************************************************************
//! \brief  Get the depth of tree.
//!
//! \param  [in] pNode is the root of tree.
//! \retval the depth of tree checked, it should >= 1, return zero indicates pNode is
//!         an invalid node.
//****************************************************************************************
int Tree_DepthGet(TreeNode_t* pNode)
{
    int Deep = 0;
    if(NULL != pNode)
    {
        int LChildDeep = Tree_DepthGet(pNode->left);
        int RChildDeep = Tree_DepthGet(pNode->right);
        Deep = (LChildDeep >= RChildDeep)?(LChildDeep+1):(RChildDeep+1);
    }

    return Deep;
}

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
TreeErrorCode_t Tree_NodeValueSet(TreeNode_t* pNode, void* Value)
{
    //! Check input parameters.
    if(NULL == pNode)
    {
        return (ERR_INVALID_POINTER);
    }

    //! Fill Node value
    pNode->data = Value;

    return (ERR_SUCCESS);
}

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
void* Tree_NodeValueGet(TreeNode_t* pNode)
{
    //! Check input parameters.
    if(NULL == pNode)
    {
        return (NULL);
    }

    //! Return data field.
    return (pNode->data);
}

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
TreeErrorCode_t Tree_NodeAppend(TreeNode_t* pNode, TreeNode_t* pNewNode, int Mode)
{

    //! Check input parameters
    if(NULL == pNode || NULL == pNewNode)
    {
        return (ERR_INVALID_POINTER);
    }

    //! Check mode parameter.
    if(0 != (Mode & (~INSERT_MODE_MASK)))
    {
        return (ERR_WRONG_PARAM);
    }

    //! Append Left Node
    if((Mode & INSERT_MODE_MASK) == INSERT_POS_LEFT)
    {
        if(NULL == pNode->left)
        {
            pNode->left      = pNewNode;
            pNewNode->parent = pNode;
            return (ERR_SUCCESS);
        }
        else
        {
            return (ERR_NODE_EXIST);
        }
    }

    //! Append Right Node
    if((Mode & INSERT_MODE_MASK) == INSERT_POS_RIGHT)
    {
        if(NULL == pNode->right)
        {
            pNode->right     = pNewNode;
            pNewNode->parent = pNode;
            return (ERR_SUCCESS);
        }
        else
        {
            return (ERR_NODE_EXIST);
        }
    }

    //! Note:In normal conditions, program can not run to here.
    return (ERR_WRONG_PARAM);

}

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
TreeErrorCode_t Tree_TravesePreOrder(TreeNode_t* pNode, TreeCallBackFun_t pFun, void* Ctx)
{
    if(NULL == pNode || NULL == pFun)
    {
        return (ERR_INVALID_POINTER);
    }

    pFun(Ctx, pNode->data);
    Tree_TravesePreOrder(pNode->left, pFun, Ctx);
    Tree_TravesePreOrder(pNode->right, pFun, Ctx);

    return (ERR_SUCCESS);
}

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
TreeErrorCode_t Tree_TraveseInOrder(TreeNode_t* pNode, TreeCallBackFun_t pFun, void* Ctx)
{
    if(NULL == pNode || NULL == pFun)
    {
        return (ERR_INVALID_POINTER);
    }

    Tree_TraveseInOrder(pNode->left, pFun, Ctx);
    pFun(Ctx, pNode->data);
    Tree_TraveseInOrder(pNode->right, pFun, Ctx);

    return (ERR_SUCCESS);
}

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
TreeErrorCode_t Tree_TravesePostOrder(TreeNode_t* pNode, TreeCallBackFun_t pFun, void* Ctx)
{
    if(NULL == pNode || NULL == pFun)
    {
        return (ERR_INVALID_POINTER);
    }

    Tree_TravesePostOrder(pNode->left, pFun, Ctx);
    Tree_TravesePostOrder(pNode->right, pFun, Ctx);
    pFun(Ctx, pNode->data);

    return (ERR_SUCCESS);
}
