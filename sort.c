#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 16  //配列のサイズ
#define MAX_ELEMENTS 100  //マージソートに使う作業用配列のサイズ
int b[MAX_ELEMENTS];  //作業用配列

// 重複しないランダムな配列を生成
void makeRandomArray(int random[]){
    int stock[N];
    for(int i=0;i<N;i++) stock[i] = i+1;
    int top = N;
    srand((unsigned int)time(NULL));
    for(int i=0; i<N; i++){
        int index = rand() % (top-i);
        random[i] = stock[index];
        for(int j=index; j<top-i; j++){
        stock[j] = stock[j+1];
        }
    }
}

// シェルソート
void shell_sort(int random[]){
    int a[N];
    for(int i=0; i<N; i++){
        a[i] = random[i];
    }

    int h, i, j, t;
    for(h=1; h<N/9; h=h*3+1);
    for(; h>0; h/=3){
        for(i=h; i<N; i++){
            j = i;
            while(j>=h && a[j-h]>a[j]){
                t = a[j];
                a[j] = a[j-h];
                a[j-h] = t;
                j -= h;
            }
        }
    }

    printf("シェルソート後 : ");
    for(int i=0;i<N;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

// 分割する、枢軸を返す
int partition(int a[], int l, int r){
    int i, j, pivot, t;

    i = l-1;
    j = r;

    // 枢軸
    pivot = a[r];
    // 大小の振り分け
    while(1){
        while(a[++i]<pivot);
        while(i<--j && pivot<a[j]);
        if(i >= j) break;
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    t = a[i];
    a[i] = a[r];
    a[r] = t;
    
    return i;
}

// クイックソート
void quick_sort_1(int a[], int l, int r){
    int v, i;

    if(l >= r) return;

    v = partition(a, l, r);  //分割する、枢軸を返す
    quick_sort_1(a, l, v-1);  //左部分をソート
    quick_sort_1(a, v+1, r);  //右部分をソート

}

// クイックソート
void quick_sort(int random[]){
    // 配列のコピー
    int a[N];
    for(int i=0; i<N; i++){
        a[i] = random[i];
    }

    quick_sort_1(a, 0, N-1);

    // 整列後の配列の確認
    printf("クイックソート後 : ");
    for(int i=0;i<N;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

// マージソート
void merge_sort_1(int a[], int low, int high){
    int mid, i, j, k;

    if(low >= high) return;

    // 分割する
    mid = (low+high)/2;

    merge_sort_1(a, low, mid);  //左部分をソート
    merge_sort_1(a, mid+1, high);  //右部分をソート

    // マージする
    for(i=low; i<=mid; i++) b[i] = a[i];
    for(i=mid+1, j=high; i<=high; i++, j--) b[i] = a[j];

    i = low;
    j = high;
    for(k=low; k<=high; k++){
        if(b[i]<=b[j]) a[k] = b[i++];
        else a[k] = b[j--];
    }

}

// マージソート
void merge_sort(int random[]){
    // 配列のコピー
    int a[N];
    for(int i=0; i<N; i++){
        a[i] = random[i];
    }

    merge_sort_1(a, 0, N-1);

    // 整列後の配列の確認
    printf("マージソート後 : ");
    for(int i=0; i<N; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}


int main(void){
    int random[N];
    makeRandomArray(random);

    printf("整列前 : ");
    for(int i=0;i<N;i++){
        printf("%d ",random[i]);
    }
    printf("\n");

    shell_sort(random);

    quick_sort(random);

    merge_sort(random);
}