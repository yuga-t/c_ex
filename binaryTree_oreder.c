#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

// ノードの定義
typedef struct node{
    int number;
    char *name;
    struct node *left, *right;
} NODE;

// 根
NODE *root;

// aよりbの方が大きい場合1を返す
int keylt(int a, int b){
    if(a<b) return 1;
    return 0;
}

// aとbが等しいなら1を返す
int keyequal(int a,int b){
    if(a==b) return 1;
    return 0;
}

// 新たなデータを追加する
NODE *insert(int key, char *insert_name){
    NODE **p, *new;
    p = &root;
    while(*p != NULL){
        if(keyequal(key, (*p)->number)){
            return NULL;
        }else if(keylt(key, (*p)->number)){
            p = &(*p)->left;
        }else{
            p = &(*p)->right;
        }
    }
    if((new = malloc(sizeof(NODE))) == NULL){
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
NODE *search(int key){
    NODE *p;
    p = root;
    while(p != NULL){
        if(keyequal(key,p->number)){
            return p;
        }
        else if(keylt(key,p->number)) p = p->left;
        else p = p->right;
    }
    return NULL;
}

// 番号がkeyに当たるデータを探索して、表示する
void search_print(int key){
    NODE *p;
    p = root;
    while(p != NULL){
        if(keyequal(key,p->number)){
            printf("番号 : %d, 名前 : %s\n",p->number,p->name);
            return;
        }
        else if(keylt(key,p->number)) p = p->left;
        else p = p->right;
    }
    return;
}

// 最小の要素を削除する
NODE *deletemin(NODE **p){
    NODE *x;
    while((*p)->left != NULL){
        p = &(*p)->left;
    }
    x = *p;
    *p =(*p)->right;
    return x;
}

// 番号がkeyであるデータを削除
int delete(int key){
    NODE **p, *x;
    p = &root;
    while(*p != NULL){
        if(keyequal(key, (*p)->number)){
            x = *p;
            if(x->left == NULL && x->right == NULL){
                *p = NULL;
            }else if(x->left == NULL){
                *p = x->right;
            }else if(x->right == NULL){
                *p = x->left;
            }else{
                *p = deletemin(&x->right);
                (*p)->right = x->right;
                (*p)->left = x->left;
            }
            free(x);
            return 1;
        }else if(keylt(key, (*p)->number)){
            p = &(*p)->left;
        }else{
            p = &(*p)->right;
        }
    }
    return 0;
}

// 行きがけ順
void preorder(NODE *p){
    if(p == NULL) return;
    printf("ノード番号 : %d, 名前 : %s  に立ち寄りました\n",p->number,p->name);
    preorder(p->left);
    preorder(p->right);
}

// 通りがけ順
void inorder(NODE *p){
    if(p == NULL) return;
    inorder(p->left);
    printf("ノード番号 : %d, 名前 : %s  に立ち寄りました\n",p->number,p->name);
    inorder(p->right);
}

// 帰りがけ順
void postorder(NODE *p){
    if(p == NULL) return;
    postorder(p->left);
    postorder(p->right);
    printf("ノード番号 : %d, 名前 : %s  に立ち寄りました\n",p->number,p->name);
}

int main(void){
    // データの追加
    insert(3,"c");
    insert(1,"a");
    insert(6,"f");
    insert(4,"d");
    insert(10,"e");

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

    printf("行きがけ順\n");
    preorder(root);

    printf("通りがけ順\n");
    inorder(root);

    printf("帰りがけ順\n");
    postorder(root);
}