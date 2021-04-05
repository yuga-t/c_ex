#include <stdio.h>
#include <stdlib.h>

struct CELL
{
    int data;
    struct CELL *next;
};

// 要素の生成
struct CELL *create(int data)
{
    struct CELL *p = (struct CELL *)malloc(sizeof(struct CELL));
    p->next = NULL;
    p->data = data;
    return p;
};

// リスト末尾のポインタを返す
struct CELL *get_tail(struct CELL *pos)
{
    while (pos->next != NULL)
        pos = pos->next;
    return pos;
}

// (n-1)番目の次にCELLを挿入
void insert(struct CELL *startCell, struct CELL *insertCell, int n)
{
    struct CELL *p = startCell;
    for (int i = 1; i < n; i++)
        p = p->next;

    insertCell->next = p->next;
    p->next = insertCell;
}

// n番目のCELLを削除
void erase(struct CELL *startCell, int n)
{
    struct CELL *p = startCell;
    for (int i = 1; i < n; i++)
        p = p->next;

    struct CELL *p0 = p->next;
    p->next = p0->next;
    p0->next = NULL;
    free(p0);
}

// メモリの解放
void free_list(struct CELL *p)
{
    struct CELL *p2;
    while (p != NULL)
    {
        p2 = p->next;
        free(p);
        p = p2;
    }
}

// リストの出力
void print_list(struct CELL *p)
{
    p = p->next;
    printf("リスト : ");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(void)
{
    struct CELL *header = create(0);
    struct CELL *p;

    // 動作確認

    p = create(3);
    get_tail(header)->next = p;

    p = create(10);
    get_tail(header)->next = p;

    p = create(99);
    get_tail(header)->next = p;

    print_list(header); // 3 -> 10 -> 99

    p = create(-8);
    insert(header, p, 2);

    print_list(header); // 3 -> -8 -> 10 -> 99

    erase(header, 3);

    print_list(header); // 3 -> -8 -> 99

    //メモリ解放
    free_list(header);
}