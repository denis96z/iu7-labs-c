#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H

int compare_sales_order_ID(const sales_order_detail_t *item1, const sales_order_detail_t *item2);
int compare_sales_order_detail_ID(const sales_order_detail_t *item1, const sales_order_detail_t *item2);
int compare_order_qty(const sales_order_detail_t *item1, const sales_order_detail_t *item2);
int compare_product_ID(const sales_order_detail_t *item1, const sales_order_detail_t *item2);
int compare_unit_price(const sales_order_detail_t *item1, const sales_order_detail_t *item2);
int compare_unit_price_discount(const sales_order_detail_t *item1, const sales_order_detail_t *item2);
int compare_modified_date(const sales_order_detail_t *item1, const sales_order_detail_t *item2);

tree_node_t *create_node(sales_order_detail_t *sales_order_detail);
int insert_node(tree_node_t *tree_node, tree_node_t **root, cmp_f_t cmp_f);

void prefix_search(tree_node_t *root);
void infix_search(tree_node_t *root);
void postfix_search(tree_node_t *root);


tree_node_t* min_item(tree_node_t *root);
tree_node_t* max_item(tree_node_t *root);

tree_node_t *parent(tree_node_t *root, tree_node_t *node);

tree_node_t *search(tree_node_t *root, sales_order_detail_t item, cmp_f_t cmp_f);
void delete_node(tree_node_t *root, tree_node_t *node);

#endif // TREE_OPERATIONS_H
