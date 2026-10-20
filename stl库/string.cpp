#include <bits/stdc++.h>
using namespace std;

// ==========================================
// 1. 基础 I/O
// ==========================================
void string_io_traps() {
	string s;
	// 基础读取，遇空格或换行停止
	// cin >> s; 
	
	// cin >> 与 getline 混用
	int n;
	// cin >> n; 
	// 读入数字后再用 getline 读下一行：
	// getline(cin, s); 
	// 结果 s 为空串：cin 不读走数字后面的换行符 '\n'。
	
	// 使用 getline 前先取走缓冲区中残留的换行符：
	/*
	cin >> n;
	string dummy; 
	getline(cin, dummy); // 取走上一行的换行符
	// 或者用：cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, s);     // 读取含空格的一整行
	*/
}

// ==========================================
// 2. 增删改与截取
// ==========================================
void string_modifiers() {
	string s = "Hello";
	
	// 尾部拼接，复杂度 O(L)
	s += " World";     
	s.push_back('!');  // 尾部追加单字符
	s.pop_back();      // 尾部删除单字符 (C++11)
	
	// substr 的第二个参数是长度，不是结束下标。
	// 从下标 6 开始取长度 5 的子串，结果为 "World"
	string sub1 = s.substr(6, 5); 
	
	// 省略第二个参数时取到末尾
	string sub2 = s.substr(6); 
	
	// 翻转字符串
	reverse(s.begin(), s.end()); 
}

// ==========================================
// 3. 查找与替换
// ==========================================
void string_find() {
	string s = "apple pen apple";
	
	// 正向查找：返回起始下标，找不到返回 string::npos
	size_t pos1 = s.find("apple"); 
	if (pos1 != string::npos) {
		// pos1 = 0
	}
	
	// 逆向查找，返回最后一次出现的位置
	size_t pos2 = s.rfind("apple"); // pos2 = 10
	
	// 从指定位置开始查找，跳过第一个 apple
	size_t pos3 = s.find("apple", 1); // pos3 = 10
	
	// 将从下标 0 开始长度 5 的子串替换为 "orange"
	s.replace(0, 5, "orange"); // "orange pen apple"
}

// ==========================================
// 4. 类型转换
// ==========================================
void string_conversions() {
	// 1. 数字转字符串 (C++11)
	int a = 123;
	double d = 3.14;
	string s1 = to_string(a); // "123"
	string s2 = to_string(d); // "3.140000"
	
	// 2. 字符串转数字
	string num_str = "10086";
	string ll_str = "10000000000000000";
	
	int num1 = stoi(num_str);      // string 转 int
	long long num2 = stoll(ll_str);// string 转 long long
	double num3 = stod("3.14");    // string 转 double
}

// ==========================================
// 5. Stringstream 分割输入
// ==========================================
// 一行由空格分隔的若干单词或数字，个数未知，且可能有连续多个空格。
// 放入 stringstream 后当作 cin 使用。

void stringstream_magic() {
	string line = "  apple   123  banana  456   ";
	stringstream ss(line);
	
	string word;
	// 自动跳过连续空格
	while (ss >> word) {
		// 依次输出: "apple", "123", "banana", "456"
		cout << word << endl; 
	}
	
	// 也可用于类型转换
	string data = "10 20 30";
	stringstream ss2(data);
	int x;
	int sum = 0;
	while (ss2 >> x) {
		sum += x; 
	}
}
