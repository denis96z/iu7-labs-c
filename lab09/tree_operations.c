#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "declarations.h"
#include "tree_operations.h"
#include "io_unit.h"

int compare_sales_order_ID(const sales_order_detail_t *item1, const sales_order_detail_t *item2)
{
    return item1->sales_order_ID - item2->sales_order_ID;
}

int compare_sales_order_detail_ID(const sales_order_detail_t *item1, const sales_order_detail_t *item2)
{
    return item1->sales_order_detail_ID - item2->sales_order_detail_ID;
}

int compare_order_qty(const sales_order_detail_t *item1, const sales_order_detail_t *item2)
{
    return item1->order_qty - item2->order_qty;
}

int compare_product_ID(const sales_order_detail_t *item1, const sales_order_detail_t *item2)
{
    return item1->product_ID - item2->product_ID;
}

int compare_unit_price(const sales_order_detail_t *item1, const sales_order_detail_t *item2)
{
    if (fabs(item1->unit_price - item2->unit_price) < 1e-10)
    {
        return 0;
    }
    else if ((item1->unit_price - item2->unit_price) < 0.0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int compare_unit_price_discount(const sales_order_detail_t *item1, const sales_order_detail_t *item2)
{
    if (fabs(item1->unit_price_discount - item2->unit_price_discount) < 1e-10)
    {
        return 0;
    }
    else if ((item1->unit_price_discount - item2->unit_price_discount) < 0.0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int compare_modified_date(const sales_order_detail_t *item1, const sales_order_detail_t *item2)
{
    return strcmp(item1->modified_date, item2->modified_date);
}


tree_node_t *create_node(sales_order_detail_t *sales_order_detail)
{
    tree_node_t *tree_node = (tree_node_t*)malloc(sizeof(tree_node_t));

    if (!tree_node)
    {
        puts("MEMORY ALLOCATION ERROR!");
        return NULL;
    }

    tree_node->sales_order_detail = sales_order_detail;
    tree_node->left = NULL;
    tree_node->right = NULL;

    return tree_node;
}


int insert_node(tree_node_t *tree_node, tree_node_t **root, cmp_f_t cmp_f)
{
    tree_node_t *q;
    tree_node_t *t;

    if (!(*root))
    {
        *root = tree_node;
    }
    else
    {
        t = *root;
        q = *root;
        while (t)
        {
            if (cmp_f(tree_node->sales_order_detail, t->sales_order_detail) < 0)
            {
                q = t;
                t = t->left;
            }
            else
            {
                q = t;
                t = t->right;
            }
        }
        if (cmp_f(tree_node->sales_order_detail, q->sales_order_detail) < 0)
        {
            q->left = tree_node;
        }
        else
        {
            q->right = tree_node;
        }
    }

    return 1;
}


void prefix_search(tree_node_t *root)
{
    if (!root)
    {
        return;
    }
    prefix_search(root->left);
    printf("%d ", root->sales_order_detail->sales_order_ID);
    prefix_search(root->right);
}


void infix_search(tree_node_t *root)
{
    if (!root)
    {
        return;
    }
    printf("%d ", root->sales_order_detail->sales_order_ID);
    infix_search(root->left);
    infix_search(root->right);
}


void postfix_search(tree_node_t *root)
{
    if (!root)
    {
        return;
    }
    postfix_search(root->left);
    postfix_search(root->right);
    printf("%d ", root->sales_order_detail->sales_order_ID);
}


tree_node_t* min_item(tree_node_t *root)
{
    while (root->left)
    {
        root = root->left;
    }
    return root;
}


tree_node_t* max_item(tree_node_t *root)
{
    while (root->right)
    {
        root = root->right;
    }
    return root;
}


tree_node_t *search(tree_node_t *root, sales_order_detail_t item, cmp_f_t cmp_f)
{
    while (root)
    {
        if (cmp_f(root->sales_order_detail, &item) > 0)
        {
            root = root->left;
        }
        else if (cmp_f(root->sales_order_detail, &item) < 0)
        {
            root = root->right;
        }
        else
        {
            return root;
        }
    }
    return NULL;
}


tree_node_t *parent(tree_node_t *root, tree_node_t *node)
{
    if (root)
    {
        if ((root->left == node) || (root->right == node))
        {
            return root;
        }
        else
        {
            tree_node_t *result = parent(root->left, node);
            if (!result)
            {
                result = parent(root->right, node);
            }
            return result;
        }
    }
    return NULL;
}


void delete_node(tree_node_t *root, tree_node_t *node)
{
    if (node->left && node->right)
    {
        tree_node_t *local_max = max_item(node->left);
        node->sales_order_detail = local_max->sales_order_detail;
        delete_node(root, local_max);
        return;
    }
    else if (node->left)
    {
        tree_node_t *node_parent = parent(root, node);
        if (node == node_parent->left)
        {
            node_parent->left = node->left;
        }
        else
        {
            node_parent->right = node->left;
        }
    }
    else if (node->right)
    {
        tree_node_t *node_parent = parent(root, node);
        if (node == node_parent->right)
        {
            node_parent->right = node->right;
        }
        else
        {
            node_parent->left = node->right;
        }
    }
    else
    {
        tree_node_t *node_parent = parent(root, node);
        if (node == node_parent->left)
        {
            node_parent->left = NULL;
        }
        else
        {
            node_parent->right = NULL;
        }
    }
    free(node);
}
