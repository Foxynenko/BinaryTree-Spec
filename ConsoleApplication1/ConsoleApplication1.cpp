#include <iostream>
#include <sstream>
#include <string>

// Визначення вузла бінарного дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    // Серіалізація дерева в рядок
    std::string serialize(TreeNode* root) {
        std::ostringstream out;
        serializeHelper(root, out);
        return out.str();
    }

    // Десеріалізація рядка в дерево
    TreeNode* deserialize(const std::string& data) {
        std::istringstream in(data);
        return deserializeHelper(in);
    }

private:
    // Рекурсивна допоміжна функція для серіалізації
    void serializeHelper(TreeNode* node, std::ostringstream& out) {
        if (node) {
            out << node->val << ' ';
            serializeHelper(node->left, out);
            serializeHelper(node->right, out);
        }
        else {
            out << "# "; // Позначення відсутності вузла
        }
    }

    // Рекурсивна допоміжна функція для десеріалізації
    TreeNode* deserializeHelper(std::istringstream& in) {
        std::string token;
        in >> token;

        if (token == "#") {
            return nullptr; // Відсутній вузол
        }
        else {
            int val = std::stoi(token);
            TreeNode* node = new TreeNode(val);
            node->left = deserializeHelper(in);
            node->right = deserializeHelper(in);
            return node;
        }
    }
};

int main() {
    // Приклад використання
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    Codec codec;
    std::string serialized = codec.serialize(root);
    std::cout << "Serialized: " << serialized << std::endl;

    TreeNode* deserialized = codec.deserialize(serialized);
    std::cout << "Deserialized: " << codec.serialize(deserialized) << std::endl;

    // Звільнення пам'яті (необхідно вручну відповідально звільнити пам'ять)
    // Рекурсивно видаліть вузли дерева

    return 0;
}
