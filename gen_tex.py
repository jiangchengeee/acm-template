import os

# 输出的 tex 文件名
OUTPUT_TEX = "template.tex"

# ==========================================
# LaTeX 头部配置
# ==========================================
TEX_HEAD = r"""% !TEX program = xelatex
\documentclass[11pt,a4paper]{ctexart}
\usepackage{geometry}
\geometry{left=2.5cm, right=2.5cm, top=3cm, bottom=3cm}
\usepackage{listings}
\usepackage{xcolor}
\usepackage{hyperref}
\usepackage{fancyhdr}
\usepackage{graphicx}
\usepackage{tikz} 
\usepackage{linegoal}
\usepackage{calligra} 
\usepackage{amsmath}
\usepackage{amssymb}

\hypersetup{colorlinks=true, linkcolor=black, urlcolor=blue}
\setcounter{tocdepth}{2}
\pagestyle{fancy}
\fancyhf{}
\fancyhead[L]{算法竞赛核心模板库}
\fancyhead[R]{\thepage}
\setlength{\headheight}{15pt}

\lstset{
    language=C++,
    basicstyle=\ttfamily\small,
    keywordstyle=\color{blue}\bfseries,
    commentstyle=\color[rgb]{0,0.6,0},
    stringstyle=\color[rgb]{0.58,0,0.82},
    numbers=left,
    numberstyle=\tiny\color{gray},
    breaklines=true,
    frame=single,
    tabsize=4,
    showstringspaces=false,
    extendedchars=false,
}

\begin{document}

\begin{titlepage}
    \centering
    \vspace*{2cm} 

    \begin{tikzpicture}
        \node [circle, minimum size=6.5cm, path picture={
            \node at (path picture bounding box.center){
                \includegraphics[width=7cm]{cover.png}
            };
        }] {};
    \end{tikzpicture}

    \vspace{2cm} 

    {\huge \textbf{\kaishu 算法竞赛核心模板库} \par}
    \vspace{0.5cm}
    {\color{gray!60} \rule{0.6\textwidth}{0.5pt} \vspace{2pt} \par}
    {\color{gray!60} \rule{0.6\textwidth}{0.5pt} \par}

    \vspace{2cm} 
    {\Large \hspace{-1cm} {\calligra \huge Jiangcheneee} \hspace{1cm} \Large \fangsong 华中农业大学 \par}
    \vspace{0.8cm} 
    {\color{gray!60} \rule{2cm}{0.5pt} \par}
    \vspace{0.8cm} 
    {\large \the\year 年 \the\month 月 \the\day 日 \par}
    \vfill 
\end{titlepage}

\thispagestyle{empty}
\newpage
\tableofcontents
\newpage

\section*{使用说明}
\addcontentsline{toc}{section}{使用说明}

\paragraph{编译与验证}
\begin{itemize}
  \item 编译命令：\texttt{g++ -O2 -std=c++20 -o a a.cpp}；全部板子都在 GCC 15 上单独编译验证过，
        并且带样例的板子都用暴力程序对拍过。
  \item 每个板子末尾的注释块就是样例：「输入」若干行，紧跟若干行以 \texttt{//} 开头的期望输出。
        这些输出全部是程序真实跑出来的，不是手写的，可以直接拿来手算核对。
\end{itemize}

\paragraph{哪些板子能直接跑}
\begin{itemize}
  \item 自带 \texttt{main} 的板子：复制出来就能编译运行、自带读入输出格式。
  \item 下面这些是「片段」，没有 \texttt{main}，依赖启动文件里的 \texttt{up/down}、\texttt{N}、\texttt{mod}
        以及 \texttt{\#define int long long}，使用时贴在「一键启动模板」后面：
        \textbf{stl 库全部 12 个}，计算几何/极角排序，树论/倍增，数据结构/01trie、dsu、莫队、树状数组、
        线段树（区间max），数学/exgcd、欧拉筛、线性求逆元（前缀积法），图论/dij、欧拉路径，杂项/int128、modint。
  \item 标题带「推导笔记」的是数学推导（LaTeX 排版），不是代码，比赛时用来现场回忆结论。
\end{itemize}

\paragraph{几个容易写挂的地方}
\begin{itemize}
  \item \texttt{\#define int long long} 之后，需要 32 位的地方要显式写 \texttt{int32\_t}
        （例如 01trie、前缀线性基的数组），否则内存直接翻倍。
  \item 取模答案出现负数，多半是最后少了一句 \texttt{((x \% mod) + mod) \% mod}（树链剖分那页踩过）。
  \item 多组数据的板子要把 \texttt{cin >> t} 打开；单组数据必须注释掉，否则会多吃掉一行输入。
\end{itemize}
"""

TEX_TAIL = r"""
\end{document}
"""

def escape_tex(text):
    """处理 LaTeX 中的特殊字符，防止编译报错"""
    return text.replace("_", r"\_").replace("&", r"\&")

def generate_tex():
    with open(OUTPUT_TEX, "w", encoding="utf-8") as f:
        # 1. 写入头部信息
        f.write(TEX_HEAD)
        
        # ==========================================
        # 规则 1：强行把根目录的 启动文件 置顶
        # ==========================================
        startup_file = "启动文件.cpp"
        if os.path.exists(startup_file):
            f.write(f"\\section{{一键启动模板}}\n")
            f.write(f"\\subsection{{{escape_tex('启动文件')}}}\n")
            f.write(f"\\lstinputlisting{{\"{startup_file}\"}}\n\n")

        # 获取当前目录下的所有项
        base_dir = "."
        items = os.listdir(base_dir)
        
        # 筛选出真实的文件夹（排除隐藏文件夹和普通文件）
        folders = [d for d in items if os.path.isdir(os.path.join(base_dir, d)) and not d.startswith('.')]
        
        # ==========================================
        # 规则 2：正常排序，并把“杂项”踢到最后
        # ==========================================
        has_misc = False
        if "杂项" in folders:
            folders.remove("杂项")
            has_misc = True
            
        folders.sort() # 剩余文件夹按拼音字母排序
        
        if has_misc:
            folders.append("杂项") # 把杂项塞回列表末尾
            
        # 2. 遍历每个文件夹
        for folder in folders:
            f.write(f"\\section{{{escape_tex(folder)}}}\n")
            
            folder_path = os.path.join(base_dir, folder)
            
            # 【终极进化】：同时抓取 .cpp, .md 和 .tex 文件
            files = [file for file in os.listdir(folder_path) if file.endswith((".cpp", ".md", ".tex"))]
            files.sort() # 文件夹里的代码文件也按拼音排序
            
            for file in files:
                # 用 os.path.splitext 安全地分离文件名和后缀
                title, ext = os.path.splitext(file)
                safe_title = escape_tex(title)
                f.write(f"\\subsection{{{safe_title}}}\n")
                rel_path = f"{folder}/{file}"
                
                if ext == ".md":
                    # Markdown，临时取消 C++ 语法高亮原样输出
                    f.write(f"\\lstinputlisting[language=]{{\"{rel_path}\"}}\n\n")
                elif ext == ".tex":
                    # LaTeX 公式笔记，直接 \input 触发原生完美渲染
                    f.write(f"\\input{{\"{rel_path}\"}}\n\n")
                else:
                    # 默认的 C++ 算法板子
                    f.write(f"\\lstinputlisting{{\"{rel_path}\"}}\n\n")
                
        # 3. 写入尾部信息
        f.write(TEX_TAIL)

if __name__ == "__main__":
    generate_tex()
    print(f"✅ 成功生成 LaTeX 模板文件: {OUTPUT_TEX}")
    print("👉 启动文件已置顶，杂项已置底！完美支持 .cpp, .md 和 .tex 混合编译！")