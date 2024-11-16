#include "symbolicnamestable.h"

// Конструктор
SymbolicNamesTable::SymbolicNamesTable() : root(nullptr) {}

// Деструктор
SymbolicNamesTable::~SymbolicNamesTable() {
    clear();
}
/*--------------------------------------------------------------------*
 | Доступные операции вставки, удаления, поиска и очистки АВЛ-дерева. |
 *--------------------------------------------------------------------*/
// Вставка символического имени и адреса
void SymbolicNamesTable::insert(const QString& name, const QString& address) {
    root = insert(root, name, address);
}
// Удаление символического имени
bool SymbolicNamesTable::remove(const QString& name) {
    QString address{};
    if (find(name, address)) {
        root = remove(root, name);
        return true;
    }
    return false;
}
// Поиск символического имени
bool SymbolicNamesTable::find(const QString& name, QString& address) const {
    TreeNode* node = find(root, name);
    if (node)
    {
        address = node->address;
        return true;
    }
    return false;
}
// Очистка таблицы
void SymbolicNamesTable::clear() {
    clear(root);
    root = nullptr;
}

/*----------------------------------------------------------------------------------------*
 | Вспомогательные операции вставки, удаления, поиска, очистки АВЛ-дерева и балансировки. |
 *----------------------------------------------------------------------------------------*/
// Вставка с балансировкой
TreeNode* SymbolicNamesTable::insert(TreeNode* node, const QString& name, const QString& address) {
    if (!node) {
        return new TreeNode(name, address);
    }

    if (name < node->name) {
        node->left = insert(node->left, name, address);
    } else if (name > node->name) {
        node->right = insert(node->right, name, address);
    } else {
        node->address = address; // Обновление адреса, если имя уже существует
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Балансировка дерева
    if (balance == 2 && height(node->right->left) <= height(node->right->right))
    {
        return SmallLeftRotate(node);
    }
    if (balance == 2 && height(node->right->left) > height(node->right->right))
    {
        return BigLeftRotate(node);
    }
    if (balance == -2 && height(node->left->right) <= height(node->left->left))
    {
        return SmallRightRotate(node);
    }
    if (balance == -2 && height(node->left->right) > height(node->left->left))
    {
        return BigRightRotate(node);
    }

    return node;
}
// Удаление узла с балансировкой
TreeNode* SymbolicNamesTable::remove(TreeNode* node, const QString& name) {
    if (!node) {
        return node;
    }

    if (name < node->name) {
        node->left = remove(node->left, name);
    } else if (name > node->name) {
        node->right = remove(node->right, name);
    } else {
        // Узел с одним дочерним узлом или без дочерних узлов
        if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        // Узел с двумя дочерними узлами: получить последовательный узел
        TreeNode* temp = node->right;
        while (temp->left) {
            temp = temp->left;
        }
        node->name = temp->name;
        node->address = temp->address; // Также обновляем адрес
        node->right = remove(node->right, temp->name);
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Балансировка дерева
    if (balance == 2 && height(node->right->left) <= height(node->right->right))
    {
        return SmallLeftRotate(node);
    }
    if (balance == 2 && height(node->right->left) > height(node->right->right))
    {
        return BigLeftRotate(node);
    }
    if (balance == -2 && height(node->left->right) <= height(node->left->left))
    {
        return SmallRightRotate(node);
    }
    if (balance == -2 && height(node->left->right) > height(node->left->left))
    {
        return BigRightRotate(node);
    }

    return node;
}
// Поиск узла
TreeNode* SymbolicNamesTable::find(TreeNode* node, const QString& name) const {
    if (!node || node->name == name) {
        return node;
    }

    if (name < node->name) {
        return find(node->left, name);
    }

    return find(node->right, name);
}
// Очистка узлов
void SymbolicNamesTable::clear(TreeNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
// Высота узла
int SymbolicNamesTable::height(TreeNode* node) const {
    return node ? node->height : 0;
}
// Получение баланса узла
int SymbolicNamesTable::getBalance(TreeNode* node) const {
    return node ? height(node->right) - height(node->left) : 0;
}
// Малое левое вращение
TreeNode* SymbolicNamesTable::SmallLeftRotate(TreeNode* a)
{
    TreeNode* b{a->right};
    TreeNode* C{b->left};

    a->right = C;
    b->left = a;

    a->height = 1 + std::max(height(a->left), height(a->right));
    b->height = 1 + std::max(height(b->left), height(b->right));

    return b;
}
// Большое левое вращение
TreeNode* SymbolicNamesTable::BigLeftRotate(TreeNode* a)
{
    TreeNode* b{a->right};
    TreeNode* c{b->left};
    TreeNode* M{c->left};
    TreeNode* N{c->right};

    c->left = a;
    c->right = b;
    a->right = M;
    b->left = N;

    a->height = 1 + std::max(height(a->left), height(a->right));
    b->height = 1 + std::max(height(b->left), height(b->right));
    c->height = 1 + std::max(height(c->left), height(c->right));

    return c;

}
// Малое правое вращение
TreeNode* SymbolicNamesTable::SmallRightRotate(TreeNode* a)
{
    TreeNode* b{a->left};
    TreeNode* C{b->right};

    a->left = C;
    b->right = a;

    a->height = 1 + std::max(height(a->left), height(a->right));
    b->height = 1 + std::max(height(b->left), height(b->right));

    return b;
}
// Большое правое вращение
TreeNode* SymbolicNamesTable::BigRightRotate(TreeNode* a)
{
    TreeNode* b{a->left};
    TreeNode* c{b->right};
    TreeNode* M{c->left};
    TreeNode* N{c->right};

    c->left = b;
    c->right = a;
    a->left = N;
    b->right = M;

    a->height = 1 + std::max(height(a->left), height(a->right));
    b->height = 1 + std::max(height(b->left), height(b->right));
    c->height = 1 + std::max(height(c->left), height(c->right));

    return c;
}
