#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ノードの定義
typedef struct node
{
    int number;
    char *name;
    struct node *left, *right;
} NODE;

// 根
NODE *root;

// aよりbの方が大きい場合1を返す
int keylt(int a, int b)
{
    if (a < b)
        return 1;
    return 0;
}

// aとbが等しいなら1を返す
int keyequal(int a, int b)
{
    if (a == b)
        return 1;
    return 0;
}

// 新たなデータを追加する
NODE *insert(int key, char *insert_name)
{
    NODE **p, *new;
    p = &root;
    while (*p != NULL)
    {
        if (keyequal(key, (*p)->number))
        {
            return NULL;
        }
        else if (keylt(key, (*p)->number))
        {
            p = &(*p)->left;
        }
        else
        {
            p = &(*p)->right;
        }
    }
    if ((new = malloc(sizeof(NODE))) == NULL)
    {
        printf("メモリが足りません\n");
        return NULL;
    }
    new->left = NULL;
    new->right = NULL;
    new->number = key;
    new->name = insert_name;
    *p = new;
    return new;
}

// 番号がkeyに当たるデータを探索
NODE *search(int key)
{
    NODE *p;
    p = root;
    while (p != NULL)
    {
        if (keyequal(key, p->number))
        {
            return p;
        }
        else if (keylt(key, p->number))
            p = p->left;
        else
            p = p->right;
    }
    return NULL;
}

// 番号がkeyに当たるデータを探索して、表示する
void search_print(int key)
{
    NODE *p;
    p = root;
    while (p != NULL)
    {
        if (keyequal(key, p->number))
        {
            printf("番号 : %d, 名前 : %s\n", p->number, p->name);
            return;
        }
        else if (keylt(key, p->number))
            p = p->left;
        else
            p = p->right;
    }
    return;
}

// 最小の要素を削除する
NODE *deletemin(NODE **p)
{
    NODE *x;
    while ((*p)->left != NULL)
    {
        p = &(*p)->left;
    }
    x = *p;
    *p = (*p)->right;
    return x;
}

// 番号がkeyであるデータを削除
int delete (int key)
{
    NODE **p, *x;
    p = &root;
    while (*p != NULL)
    {
        if (keyequal(key, (*p)->number))
        {
            x = *p;
            if (x->left == NULL && x->right == NULL)
            {
                *p = NULL;
            }
            else if (x->left == NULL)
            {
                *p = x->right;
            }
            else if (x->right == NULL)
            {
                *p = x->left;
            }
            else
            {
                *p = deletemin(&x->right);
                (*p)->right = x->right;
                (*p)->left = x->left;
            }
            free(x);
            return 1;
        }
        else if (keylt(key, (*p)->number))
        {
            p = &(*p)->left;
        }
        else
        {
            p = &(*p)->right;
        }
    }
    return 0;
}

// xとyの大きい方を返す
int max(int x, int y)
{
    if (x > y)
        return x;
    return y;
}

// 木の高さの+1した値を返す
int get_height_plus1(NODE *p)
{
    if (p == NULL)
        return 0;
    return 1 + max(get_height_plus1(p->left), get_height_plus1(p->right));
}

// 木の高さを返す
int get_height(NODE *p)
{
    return get_height_plus1(p) - 1;
}

int main(void)
{
    // データの追加
    insert(3, "c");
    insert(1, "a");
    insert(6, "f");
    insert(4, "d");
    insert(10, "e");

    printf("データの確認\n");
    search_print(1);
    search_print(2);
    search_print(3);
    search_print(4);
    search_print(5);
    search_print(6);
    search_print(7);
    search_print(8);
    search_print(9);
    search_print(10);

    printf("木の高さ : %d\n", get_height(root));
}
