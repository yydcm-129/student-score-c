/* 动态学生成绩管理
 * 功能：输入人数 -> malloc 申请结构体数组 -> 录入 -> 算总分/平均分
 *       -> 按总分排序 -> 统计及格人数 -> 打印 -> free 释放
 */
#include <stdio.h>
#include <stdlib.h>

#define COURSE_NUM 3
#define PASS_LINE 60

typedef struct {
    char   id[16];
    char   name[32];
    int    score[COURSE_NUM];
    int    total;
    double average;
} Student;

/* 计算一个学生的总分与平均分 */
void calc_student(Student *s)
{
    int i;

    s->total = 0;
    for (i = 0; i < COURSE_NUM; i++)
        s->total += s->score[i];
    s->average = (double)s->total / COURSE_NUM;
}

/* 计算全部学生 */
void calc_all(Student *arr, int n)
{
    int i;

    for (i = 0; i < n; i++)
        calc_student(&arr[i]);
}

/* 按总分从高到低排序（冒泡，直接交换结构体） */
void sort_by_total(Student *arr, int n)
{
    int i, j;
    Student tmp;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (arr[j].total < arr[j + 1].total) {
                tmp        = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

/* 统计及格人数：三门成绩都不低于 PASS_LINE */
int count_pass(const Student *arr, int n)
{
    int i, k, count = 0;

    for (i = 0; i < n; i++) {
        for (k = 0; k < COURSE_NUM; k++)
            if (arr[i].score[k] < PASS_LINE)
                break;
        if (k == COURSE_NUM)
            count++;
    }
    return count;
}

/* 按当前顺序打印（中文宽度不定，用标签式排版，避免错位） */
void print_all(const Student *arr, int n)
{
    int i, k;

    printf("\n===== 成绩单（按总分从高到低）=====\n");
    for (i = 0; i < n; i++) {
        printf("%d. %s(%s)  成绩:", i + 1, arr[i].name, arr[i].id);
        for (k = 0; k < COURSE_NUM; k++)
            printf(" %d", arr[i].score[k]);
        printf("  总分:%d  平均分:%.2f\n", arr[i].total, arr[i].average);
    }
}

/* 申请内存并录入数据，失败返回 NULL */
Student *input_students(int n)
{
    int      i;
    Student *arr = (Student *)malloc(sizeof(Student) * n);

    if (arr == NULL)
        return NULL;

    for (i = 0; i < n; i++) {
        printf("第 %d 个学生（学号 姓名 成绩1 成绩2 成绩3）：", i + 1);
        if (scanf("%15s %31s %d %d %d",
                  arr[i].id, arr[i].name,
                  &arr[i].score[0], &arr[i].score[1], &arr[i].score[2]) != 5) {
            printf("输入格式错误，已退出。\n");
            free(arr);
            return NULL;
        }
    }
    return arr;
}

int main(void)
{
    int      n;
    Student *arr;

    printf("请输入学生人数：");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("人数无效，程序退出。\n");
        return 1;
    }

    arr = input_students(n);
    if (arr == NULL) {
        printf("内存申请失败或输入被中断。\n");
        return 1;
    }

    calc_all(arr, n);
    sort_by_total(arr, n);
    print_all(arr, n);
    printf("\n三门均及格人数：%d / %d\n", count_pass(arr, n), n);

    free(arr);
    arr = NULL;
    return 0;
}
