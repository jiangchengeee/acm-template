# 算法竞赛模板库

个人 ACM/ICPC 模板库。`template.pdf` 是全部代码与推导笔记的合订本，由 `gen_tex.py` 自动生成。

## 编译 PDF

```bash
python3 gen_tex.py      # 扫描目录、生成 template.tex
xelatex template.tex
xelatex template.tex    # 目录需要跑两遍
```

新增模板：把 `.cpp` / `.tex` 放进对应文件夹，重新跑 `gen_tex.py` 就会自动收录（按文件名字典序排列）。

## 目录

| 目录 | 内容 |
|---|---|
| `stl库/` | 常用 STL 容器与坑 |
| `数据结构/` | 树状数组、线段树、主席树、莫队、01-trie |
| `树论/` | 倍增求 LCA、启发式合并（dsu on tree） |
| `图论/` | 最短路、欧拉路径 |
| `数学/` | 数论、线性基、卢卡斯、莫比乌斯反演、卷积（FFT / NTT / 任意模数 NTT）、矩阵快速幂、CDQ 优化 DP、组合数恒等式 |
| `计算几何/` | 凸包、旋转卡壳、极角排序、闵可夫斯基和与皮克定理 |
| `博弈论/` | SG 函数 |
| `杂项/` | `__int128`、modint、CDQ 分治 |

带 `（推导笔记）` 后缀的 `.tex` 是配套的理论推导，会和代码一起编进 PDF。

## 使用约定

- 模板代码以 `#include <bits/stdc++.h>` + `#define int long long` + `up/down` 宏为基础风格；
- 多数 `.cpp` 自带 `solve()` 与末尾的测试样例注释，可直接提交或粘贴使用。
