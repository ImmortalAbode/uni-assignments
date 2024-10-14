#ifndef SYMBOLICNAMESTABLE_H
#define SYMBOLICNAMESTABLE_H

#include <QString>

struct TreeNode {
    QString name;           // Символическое имя
    QString address;        // Адрес в шестнадцатеричной системе
    TreeNode* left;         // Левый дочерний узел
    TreeNode* right;        // Правый дочерний узел
    int height;             // Высота узла для опредления балансировки дерева

    TreeNode(const QString& n, const QString& addr) : name(n), address(addr), left(nullptr), right(nullptr), height(1) {}
};

class SymbolicNamesTable {
public:
    SymbolicNamesTable();
    ~SymbolicNamesTable();
    void insert(const QString& name, const QString& address);
    bool remove(const QString& name);
    bool find(const QString& name, QString& address) const;
    void clear();

private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, const QString& name, const QString& address);
    TreeNode* remove(TreeNode* node, const QString& name);
    TreeNode* find(TreeNode* node, const QString& name) const;
    void clear(TreeNode* node);
    int height(TreeNode* node) const;
    int getBalance(TreeNode* node) const;
    TreeNode* SmallRightRotate(TreeNode* a);
    TreeNode* BigRightRotate(TreeNode* a);
    TreeNode* SmallLeftRotate(TreeNode* a);
    TreeNode* BigLeftRotate(TreeNode* a);
};

#endif // SYMBOLICNAMESTABLE_H
