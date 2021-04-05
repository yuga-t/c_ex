#include <stdio.h>
#include <stdlib.h>

// 要素の定義
typedef struct CELL
{
    int data;
    struct CELL *prev;
    struct CELL *next;
} cell;

// 要素の生成
cell *create(int data)
{
    cell *p = (struct CELL *)malloc(sizeof(struct CELL));
    p->prev = NULL;
    p->next = NULL;
    p->data = data;
    return p;
}

// リストの末尾を返す
cell *tail(cell *header)
{
    cell *cur = header;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    return cur;
}

// curの次にnewを挿入する
void insert(cell *cur, cell *new)
{
    if(tail(cur) == cur)
    {
        new->next = NULL;
        cur->next = new;
        new->prev = cur;
    }
    else
    {
        new->next = cur->next;
        new->next->prev = new;
        cur->next = new;
        new->prev = cur;
    }
}

// curを削除
cell *erase(cell *cur)
{
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    cur->next = NULL;
    cur->prev = NULL;
    return cur;
}

// data=valのポインタを返す.なければNULLを返す
cell *find(cell *header, int val)
{
    cell *p = header->next;

    while (p != NULL)
    {
        if (p->data == val)
        {
            return p;
        }
        else
        {
            p = p->next;
        }
    }

    return p;
}

// リストを出力
void print_list(cell *header)
{
    cell *p = header->next;

    printf("双方向リスト : ");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// リストのメモリ解放
void free_list(cell *header)
{

    cell *cur = header;
    cell *cur_next;

    while (cur != NULL)
    {
        cur_next = cur->next;
        free(cur);
        cur = cur_next;
    }
}

int main(void)
{
    cell *header = create(0);
    cell *cur, *new;

    // 動作確認

    cur = create(3);
    header->next = cur;
    cur->prev = NULL; // headerには戻れない

    new = create(10);
    insert(cur, new);
    cur = cur->next;

    new = create(99);
    insert(cur, new);
    cur = cur->next;

    new = create(100);
    insert(cur, new);
    cur = cur->next;

    new = create(200);
    insert(cur, new);
    cur = cur->next;

    print_list(header); // 3 -> 10 -> 99 -> 100 -> 200

    free(erase(find(header, 10))); // data=10の要素を見つけて削除

    print_list(header); // 3 -> 99 -> 100 -> 200

    printf("戻り順 : %d %d %d %d\n", cur->data, cur->prev->data, cur->prev->prev->data, cur->prev->prev->prev->data);
    // 200 -> 100 -> 99

    free_list(header);

    return 0;
}