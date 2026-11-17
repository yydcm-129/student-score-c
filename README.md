# 动态学生成绩管理（C）

`student_score.c` —— 单文件，无第三方依赖。

## 编译运行

```bash
gcc student_score.c -o student_score
./student_score
```

Windows 下用 Dev-C++ / Code::Blocks 直接打开该文件，按 F11 编译运行即可。
如果中文显示乱码，把文件用「UTF-8」编码另存一次（VS 默认 GBK 时常见）。

## 示例

输入：

```
3
2024001 张三 78 90 66
2024002 李四 92 88 95
2024003 王五 55 70 80
```

输出：

```
请输入学生人数：3
第 1 个学生（学号 姓名 成绩1 成绩2 成绩3）：...
...

===== 成绩单（按总分从高到低）=====
1. 李四(2024002)  成绩: 92 88 95  总分:275  平均分:91.67
2. 张三(2024001)  成绩: 78 90 66  总分:234  平均分:78.00
3. 王五(2024003)  成绩: 55 70 80  总分:205  平均分:68.33

三门均及格人数：2 / 3
```

## 结构说明

| 函数 | 作用 |
| --- | --- |
| `calc_student(Student *s)` | 算一个学生的总分、平均分 |
| `calc_all(Student *arr, int n)` | 对数组里每个学生调用上面这个 |
| `sort_by_total(Student *arr, int n)` | 冒泡排序，按总分从高到低 |
| `count_pass(const Student *arr, int n)` | 三门都不低于 60 分的人数 |
| `print_all(const Student *, int)` | 打印成绩单 |
| `input_students(int n)` | malloc 申请数组并录入，失败返回 NULL |

数组由 `main` 用 `malloc` 申请，用完 `free` 释放并置 NULL；`n <= 0`、申请失败、输入格式错误都有处理。
