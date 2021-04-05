#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
struct CELL *tail(struct CELL *cur)
{
    while (cur->next != NULL)
        cur = cur->next;
    return cur;
}

// curの次にvalを挿入
void insert(struct CELL *cur, struct CELL *val)
{
    val->next = cur->next;
    cur->next = val;
}

// curの次の要素を削除して、削除された要素のポインタを返す
struct CELL *erase(struct CELL *cur)
{
    struct CELL *p = cur->next;
    if (p != NULL)
    {
        cur->next = p->next;
        p->next = NULL;
    }
    return p;
}

// curの次の要素から分断して、分断して新しくできたheaderのポインタを返す
struct CELL *split(struct CELL *cur)
{
    struct CELL *p = cur->next;
    struct CELL *header2 = create(0);

    cur->next = NULL;  // curを末尾要素にする
    header2->next = p; // pを先頭要素にする
    return header2;
}

// l1とl2のリストをつなげて、headerを返す
struct CELL *concat(struct CELL *l1, struct CELL *l2_header)
{
    struct CELL *p = tail(l1);
    p->next = l2_header->next;
    l2_header->next = NULL;
    free(l2_header);
    return l1;
}

// data=valであるポインタを返す. 見つからない場合はNULL
struct CELL *find(struct CELL *p, int val)
{
    p = p->next;
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
    struct CELL *insert_p;

    // 動作確認

    p = create(3);
    tail(header)->next = p;

    p = create(10);
    tail(header)->next = p;

    p = create(99);
    tail(header)->next = p;

    print_list(header); // 3 -> 10 -> 99

    insert_p = create(-10);
    insert(p, insert_p);

    insert_p = create(4);
    insert(p, insert_p);

    print_list(header); // 3 -> 10 -> 99 -> 4 -> -10

    free(erase(p));

    print_list(header); // 3 -> 10 -> 99 -> -10

    struct CELL *find_p = find(header, 99);
    if(find_p){
        printf("%d\n", find_p->data);
        printf("CELL of data=99 is found\n");
    }else{
        printf("CELL of data=99 is not found\n");
    }

    struct CELL *header2 = split(find(header,10));

    print_list(header); // 3 -> 10
    print_list(header2); // 99 -> -10

    insert_p = create(1000);
    insert(header2, insert_p);

    print_list(header2); // 1000 -> 99 -> -10

    struct CELL *new_header = concat(header, header2);

    print_list(new_header); // 3 -> 10 -> 1000 -> 99 -> -10

    // メモリの解放
    free_list(header);

    return 0;
}