#include <iostream>
#include <vector>
#include <cstdio>

/// @brief 一个一般的结点基类模板
/// @tparam DT 结点中存放元素的数据类型
template <typename DT>
class Node {
	public:
		/// @brief 与某结点相邻的结点的地址表
		std :: vector <Node*> neighbor;

		/// @brief 结点中存放的数据
		DT data;

		Node () {
			neighbor.clear ();
		}
		~Node () {
			neighbor.clear ();
		}
};

/// @brief 由结点基类模板派生出的二叉树结点类模板
/// @tparam DT 树中存放元素的数据类型
template <typename DT>
class BinaryTreeNode : public Node <DT> {
	public:
		BinaryTreeNode () {
			this -> neighbor.clear ();
		}
		~BinaryTreeNode () {
			this -> neighbor.clear ();
		}
	// 在树中，用 neighbor[0] 存放其父亲结点的地址（若为根节点则指向空指针），分别用 neighbor[1] 和 neighbor[2] 指代左右子结点
};

/// @brief 二叉树类模板，基类
/// @tparam DT 树中存放元素的数据类型
template <typename DT>
class BinaryTree {
	private:
		/// @brief 树的根节点
		BinaryTreeNode <DT> root;
	public:	
		/// @brief 二叉树构造函数，添加根节点的 neighbor[0] 并设置为空指针
		BinaryTree () {
			root.neighbor.push_back (nullptr);
		}

		/// @brief 向树中结点添加左儿子
		/// @param p 待添加儿子的结点
		/// @param val 儿子中存放的数据
		void insertLeftChild (const BinaryTreeNode <DT> &p, const DT &val) {
			// 若左儿子已存在，则报错
			if (p.neighbor.size () > 0) {
				std :: cerr << "Error: Terminated due to duplicate insertion!";
				exit (0);
			}

			BinaryTreeNode <DT> *lchild = new BinaryTreeNode <DT>;
			lchild.data -> val;
			lchild -> neighbor.push_back (&p);

			p.neighbor.push_back (lchild);
		}

		/// @brief 向树中结点添加左儿子
		/// @param p 待添加儿子的结点
		/// @param val 儿子中存放的数据
		void insertLeftChild (BinaryTreeNode <DT> &&p, DT &&val) {
			// 若左儿子已存在，则报错
			if (p.neighbor.size () > 0) {
				std :: cerr << "Error: Terminated due to duplicate insertion!";
				exit (0);

			BinaryTreeNode <DT> *lchild = new BinaryTreeNode <DT>;
			lchild.data -> val;
			lchild -> neighbor.push_back (&std :: move (p));

			p.neighbor.push_back (lchild);
		}

		/// @brief 向树中结点添加右儿子
		/// @param p 待添加儿子的结点
		/// @param val 儿子中存放的数据
		void insertRightChild (const BinaryTreeNode <DT> &p, const DT &val) {

		}

		/// @brief 向树中结点添加右儿子
		/// @param p 待添加儿子的结点
		/// @param val 儿子中存放的数据
		void insertRightChild (BinaryTreeNode <DT> &&p, DT &&val) {
			
		}

		/// @brief 前序遍历树并输出元素
		void preorderTraversal () {

		}

		/// @brief 中序遍历树并输出元素
		void inorderTraversal () {

		}
		/// @brief 后序遍历树并输出元素
		void postorderTraversal () {

		}
};

/// @brief 平衡树派生类
/// @tparam DT 树中存放元素的数据类型
template <typename DT>
class AVLTree : private BinaryTree <DT> {;
	public:
		/// @brief 在平衡树中插入结点
		/// @param x 待插入结点的值
		void insert (const DT &x) {

		}

		/// @brief 在平衡树中插入结点
		/// @param x 待插入结点的值
		void insert (DT &&x) {

		}

		/// @brief 删除树中指定值的结点
		/// @param x 要删除的值
		void remove (const DT &x) {

		}

		/// @brief 删除树中指定值的结点
		/// @param x 要删除的值
		void remove (DT &&x) {

		}

		/// @brief 判断树是否为空树
		/// @return 树是（1）否（0）为空树
		bool isEmpty () {

		}

		/// @brief 将平衡树设置为空树
		void makeEmpty () {

		}

		/// @brief 升序输出平衡二叉树中的所有元素
		void printTree () {

		}
	private:
		/// @brief 平衡二叉树的旋转操作
		/// @param x 待平衡的结点
		void rotate (BinaryTreeNode <DT> x) {

		}
};