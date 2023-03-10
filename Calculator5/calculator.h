/**
 * @file calculator.h
 * @author 王笑同 (3210105450@zju.edu.cn)
 * @brief 2022 ~ 2023 秋冬 数据结构与算法 项目作业
 * @version 1.3
 * @date 2022-11-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * 待添加功能：基本初等函数、识别表达式错误（优化）、支持常数 e 和 π（pi）
 * 例子：
 * 输入 1：2^(1 + 3)-5*(15.23)/(1 + 2)*3-5
 * 输出 1：-65.15
 * 输入 2：1.25 + [3*(1 + 2^2)*3-43](4-2)
 * 输出 2：5.25
 * 输入 3：0.2*((-5)^2)
 * 输出 3：5
 * 输入 4：3^-1
 * 输出 4：错误：表达式不合法！
 * 输入 5：3^(-1)
 * 输出 5：0.333333
 * 输入 6：（空字符串）
 * 输出 6：（无）
 * 输入 7：+3.3*5(+2-1)^2
 * 输出 7：16.5
 * 输入 8：3-(2.5-15/6)^(8-8)
 * 输出 8：错误：0^0 无意义！
 * 输入 9：(-2)^3
 * 输出 9：-8
 * 输入 10：(-2)^3.000001
 * 输出 10：错误：不能计算负数的非整数次幂！
 * 输入 11：+2(1-3^(5.6-4.6))
 * 输出 11：-4
 * 输入 12：(1+{25/5})^([1.09)+0.91]
 * 输出 12：错误：表达式括号不匹配！
 * 输入 13：2^3^2
 * 输出 13：512
 * 输入 14：7/1-6+(0)-((9-7.5)^(1.46*(-4)/5.02)^(-5)+1.3)
 * 输出 14：-1.12672
 * 输入 15：6/4/(2^3.94/(5/((-5.87))/4))+(-9)^2
 * 输出 15：80.9792
 */

#include <iostream>
#include <cmath>
#include <string>
#include <stack>

#define _EPS 1e-6
/// @brief 判断两个双精度浮点数是否“相等”
/// @param a 浮点数 1
/// @param b 浮点数 2
/// @return 返回在误差范围内是否相等
bool realEqual (const double a, const double b) {
    return fabs (a - b) <= _EPS;
}

/// @brief 判断一个浮点数是否为整数
/// @param x 待判断的浮点数
/// @return 返回是否为浮点数
bool isInteger (const double x) {
    return realEqual (x, (double)(round (x)));
}

/// @brief 判断表达式子串 str 是否为合法子串
bool isLegal (std :: string str) { 
    bool opt = 0; // 上一字符是（1）否（0）为运算符
    for (auto i = str.begin (); i != str.end (); ++ i) {
        if (*i != '+' && *i != '-' && *i != '*' && *i != '/' &&
            *i != '(' && *i != ')' && *i != '^' && *i != '.' && (*i < '0' || *i > '9'))
            return 0;
        
        if (*i == '+' || *i == '-' || *i == '*' || *i == '/' || *i == '^')
            if (!opt)
                opt = 1;
            else
                return 0;
        else
            opt = 0;
        
        if (i == str.end () && (*i == '+' || *i == '-' || *i == '*' || *i == '/' || *i == '^'))
            return 0;
        if (i == str.begin () && (*i == '*' || *i == '/' || *i == '^'))
            return 0;
    }
    return 1;
}

/// @brief 判断表达式中的合法子串是否为数字
/// @param str 待判断的字符串
/// @return 返回是（1）否（0）为数字
bool isDigit (std :: string str) {
    bool dot = 0;
    for (auto i = str.begin(); i != str.end (); ++ i) {
        if (i != str.begin () && *i == '-')
            return 0;
        if ((i == str.begin() || i == str.end ()) && *i == '.')
            return 0;
        if (((char)*i < '0' || (char)*i > '9') && *i != '.')
            return 0;
        if (*i == '.') {
            if (dot)
                return 0;
            dot = 1;
        }
    }
    return 1;
}

/// @brief 利用快速幂计算 a^b
/// @param a 底数（实数）
/// @param b 指数（整数）
/// @return 返回 a^b 的结果
double quickPow (const double a, const int b) {
    if (b < 0)
        return 1 / quickPow (a, -1 * b);
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    
    double ret = quickPow (a, b >> 1);
    if (b & 1)
        return ret * ret * a;
    else
        return ret * ret;
}

/// @brief 检测表达式括号是否匹配
/// @param str 待检测的表达式串
/// @return 返回匹配结果
bool checkBrackets (std :: string str) {
    std :: stack <char> s;
    while (!s.empty ())
        s.pop ();
    for (auto i = str.begin (); i != str.end (); ++ i) {
        if (*i == '(' || *i == '[' || *i == '{')
            s.push (*i);
        else {
            if (*i == ')')
                if (s.empty () || s.top () != '(')
                    return 0;
                else
                    s.pop ();
            if (*i == ']')
                if (s.empty () || s.top () != '[')
                    return 0;
                else
                    s.pop ();
            if (*i == '}')
                if (s.empty () || s.top () != '{')
                    return 0;
                else
                    s.pop ();
        }
    }
    return s.empty ();
}

/// @brief 表达式树中的结点类
class Node {
    public:
        /// @brief 存放结点类型（1——数字，2——符号）
        int type;

        /// @brief 结点数据域（结点中的数字，或符号：1——加，2——减，3——乘，4——除，5——乘方）
        double val;

        Node *lchild, *rchild;

        /// @brief 以该结点为根的子树的结果值
        double res;

        Node () {
            this -> lchild = nullptr;
            this -> rchild = nullptr;
            this -> res = 0;
        }

        /// @brief 计算以当前结点为根的子树代表的表达式结果 
        /// @return 返回是（1）否（0）计算成功
        bool calculateResult () {
            if (this -> type == 1) {
                this -> res = this -> val;
                return 1;
            }
            if (this -> lchild == nullptr || this -> rchild == nullptr) {
                std :: cerr << "意外错误：符号结点的子树有空儿子！" << std :: endl;
                return 0;
            }

            // 计算有错误则终止
            int res1 = this -> lchild -> calculateResult ();
            int res2 = this -> rchild -> calculateResult ();
            if (res1 * res2 == 0)
                return 0;

            switch ((int) this -> val) {
                case 1:
                    this -> res = this -> lchild -> res + this -> rchild -> res;
                    break;
                case 2:
                    this -> res = this -> lchild -> res - this -> rchild -> res;
                    break;
                case 3:
                    this -> res = this -> lchild -> res * this -> rchild -> res;
                    break;
                case 4:
                    if (realEqual (this -> rchild -> res, 0)) {
                        std :: cerr << "错误：除数为 0！" << std :: endl;
                        return 0;
                    }
                    this -> res = this -> lchild -> res / this -> rchild -> res;
                    break;
                case 5:
                    if (this -> lchild -> res < 0 && !isInteger (this -> rchild -> res)) {
                        std :: cerr << "错误：不能计算负数的非整数次幂！" << std :: endl;
                        return 0;
                    }
                    if (realEqual (this -> lchild -> res, 0) && realEqual (this -> rchild -> res, 0)) {
                        std :: cerr << "错误：0^0 无意义！" << std :: endl;
                        return 0;
                    }
                    if (isInteger (this -> rchild -> res)) 
                        this -> res = quickPow (this -> lchild -> res, round (this -> rchild -> res));
                    else
                        this -> res = pow (this -> lchild -> res, this -> rchild -> res);
                    break;
                default:
                    std :: cerr << "意外错误：符号结点存储了非预期符号！" << std :: endl;
                    return 0;
                    break;
            }
            return 1;
        }
};

/// @brief 表达式树类
class ExpTree {
    private:
        Node *root;

        /// @brief 将字符串 str 对应的表达式存储在以 p 为根节点的子树中
        /// @return 返回是否成功执行操作
        bool _buildTree (std :: string str, Node *p) {
            // 保证字符串首尾无括号
            while (str [0] == '(' && str [str.length () - 1] == ')' &&
                   checkBrackets (str.substr (1, str.length ()-2))) 
                str = str.substr (1, str.length () - 2);

            if (!isLegal (str) || !str.length ())
                return 0;

            if (isDigit (str)) {
                p -> type = 1;
                p -> val = std :: stod (str);
                return 1;
            }

            p -> lchild = new Node;
            p -> rchild = new Node;
            p -> type = 2;

            // 每次找到不在括号中的优先级最低的运算符，以该运算符为根节点建树
            // br 代表当前位置在几重括号中，pos1、pos2、pos3 依次代表非括号中的最后一个加减、乘除、乘方运算符的下标
            int br = 0;
            int pos1 = -1;
            int pos2 = -1;
            int pos3 = -1;
            for (int i = 0; i < str.length (); ++ i) {
                if (str [i] == '(') {
                    ++ br;
                    continue;
                } else if (str [i] == ')') {
                    -- br;
                    continue;
                }

                if (!br && (str [i] == '+' || str [i] == '-'))
                    pos1 = i;
                else if (!br && (str [i] == '*' || str [i] == '/'))
                    pos2 = i;
                else if (!br && str [i] == '^' && pos3 == -1)
                    pos3 = i;
                // 特别注意，只有乘方运算是右结合的，所以其处理和加减乘除有所不同
            }

            bool ret = 1;
            if (pos1 != -1) {
                p -> val = (str [pos1] == '+') ? 1 : 2;
                ret &= _buildTree (str.substr (0, pos1), p -> lchild);
                ret &= _buildTree (str.substr (pos1 + 1, str.length () - pos1 - 1), p -> rchild);
            } else if (pos2 != -1) {
                p -> val = (str [pos2] == '*') ? 3 : 4;
                ret &= _buildTree (str.substr (0, pos2), p -> lchild);
                ret &= _buildTree (str.substr (pos2 + 1, str.length () - pos2 - 1), p -> rchild);
            } else if (pos3 != -1) {
                p -> val = 5;
                ret &= _buildTree (str.substr (0, pos3), p -> lchild);
                ret &= _buildTree (str.substr (pos3 + 1, str.length () - pos3 - 1), p -> rchild);
            } else {
                std :: cerr << "错误：表达式不合法！" << std :: endl;
                //delete p -> lchild;
                //delete p -> rchild;
                return 0;
            }

            return ret;
        }

        /// @brief 将表达式树的子树设为空树
        /// @param p 子树的根节点
        void makeEmpty (Node *p) {
            if (p -> lchild != nullptr)
                makeEmpty (p -> lchild);
            if (p -> rchild != nullptr)
                makeEmpty (p -> rchild);
            delete p;
        }

    public:
        ExpTree () {
            this -> root = new Node;
        }
        ~ExpTree () {
            makeEmpty (root);
        }

        /// @brief 判断树是否为空
        bool isEmpty () {
            return root == nullptr;
        }

        /// @brief 将中缀表达式存储到表达式树中
        /// @param str 表达式字符串
        /// @param ret 表达式的计算结果；若出错则置为 -1
        /// @return 返回表达式是（1）否（0）计算成功
        bool getResult (std :: string str, double *ret) {
            // 删除多余空格
            std :: string _tmp;
            _tmp.clear ();
            for (auto i = str.begin (); i != str.end (); ++ i)
                if (*i != ' ')
                    _tmp += *i;
            str = _tmp;

            // 检测表达式中括号是否匹配
            if (!checkBrackets (str)) {
                std :: cerr << "错误：表达式括号不匹配！" << std :: endl;
                *ret = -1;
                return 0;
            }
            
            // 将表达式串中的中括号和大括号改为小括号
            for (int i = 0; i < str.length (); ++ i)
                if (str [i] == '[' || str [i] == '{')
                    str [i] = '(';
                else if (str [i] == ']' || str [i] == '}')
                    str [i] = ')';

            if (!isLegal (str)) {
                std :: cerr << "错误：表达式不合法！" << std :: endl;
                *ret = -1;
                return 0;
            }

            // 处理输入的负数：若出现“-”号，且其前面的字符不是右括号，也不是数字，则在其前面补充"0"
            for (int i = 0; i < str.length (); ++ i) {
                if (str [i] == '-') {
                    if (!i) {
                        str = "0" + str;
                        ++ i;
                    } else if ((str [i - 1] != ')') && ((str [i - 1] < '0') || (str [i - 1] > '9'))) {
                        str = str.substr (0, i) + "0" + str.substr (i, str.length () - i);
                        ++ i;
                    }
                }
            }

            // 处理丧心病狂在正数前面加上“+”号的情形，与处理负号同理
            for (int i = 0; i < str.length (); ++ i) {
                if (str [i] == '+') {
                    if (!i) {
                        str = "0" + str;
                        ++ i;
                    } else if ((str [i - 1] != ')') && ((str [i - 1] < '0') || (str [i - 1] > '9'))) {
                        str = str.substr (0, i) + "0" + str.substr (i, str.length () - i);
                        ++ i;
                    }
                }
            }

            // 处理括号间省略的乘号和数字与左括号间省略的乘号
            for (int i = 0; i < str.length (); ++ i)
                if (i > 0 && str [i] == '(' && str [i - 1] == ')') {
                    str = str.substr (0, i) + "*" + str.substr (i, str.length () - i);
                    ++ i;
                }
            for (int i = 0; i < str.length (); ++ i)
                if (i > 0 && str [i] == '(' && str [i - 1] >= '0' && str [i - 1] <= '9') {
                    str = str.substr (0, i) + "*" + str.substr (i, str.length () - i);
                    ++ i;
                }

            bool status = _buildTree (str, this -> root);
            if (!status) {
                std :: cerr << "错误：表达式不合法！" << std :: endl;
                *ret = -1;
                return 0;
            }
            
            if (this -> root -> calculateResult ()) {
                *ret = this -> root -> res;
                return 1;
            } else {
                *ret = -1;
                return 0;
            }
        }
};