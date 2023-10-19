#pragma once

#include <memory>

namespace NBinTree {

// Класс TNode наследуем от std::enable_shared_from_this чтобы иметь возможность приводить this к shared_ptr или weak_ptr.
template <typename T>
class TNode : public std::enable_shared_from_this<TNode<T>>{
public:
    using TNodePtr = std::shared_ptr<TNode<T>>;
    using TNodeConstPtr = std::shared_ptr<const TNode<T>>;
    // Используется для приведения к weak_ptr.
    using TNodeWeakPtr = std::weak_ptr<TNode<T>>;
    using TNodeConstWeakPtr = std::weak_ptr<const TNode<T>>;


    bool HasLeft() const {
        return Left;
    }

    bool HasRight() const {
        return Right;
    }

    bool HasParent() const {
        return Parent;
    }

    T& GetValue() {
        return Value;
    }

    const T& GetValue() const {
        return Value;
    }

    TNodePtr GetLeft() {
        return Left;
    }

    TNodeConstPtr GetLeft() const {
        return Left;
    }

    TNodePtr GetRight() {
        return Right;
    }

    TNodeConstPtr GetRight() const {
        return Right;
    }

    // Для получения доступа к родителю проверяем не удалён ли объект и в случае когда он не удалён возвращаем сильную ссылку полученую из слабой при помощи lock(). 
    TNodePtr GetParent() {
        if (Parent.expired())
            return nullptr;
        else
            return Parent.lock();
    }

    // Для получения доступа к родителю проверяем не удалён ли объект и в случае когда он не удалён возвращаем сильную ссылку полученую из слабой при помощи lock(). 
    TNodeConstPtr GetParent() const {
        if (Parent.expired())
            return nullptr;
        else
            return Parent.lock();
    }

    static TNodePtr CreateLeaf(T value) {
        return std::make_shared<TNode>(TNode(value));
    }

    // Вместо TNode* используем shared_ptr ссысли TNodePtr.
    static TNodePtr Fork(T value, TNodePtr left, TNodePtr right) {
        TNodePtr ptr = std::make_shared<TNode>(TNode(value, left, right));
        SetParent(ptr->GetLeft(), ptr);
        SetParent(ptr->GetRight(), ptr);
        return ptr;
    }

    // Меняем тип ссылки на родителя с shared_ptr на weak_ptr.
    TNodePtr ReplaceLeft(TNodePtr left) {
        SetParent(left, this->weak_from_this());
        SetParent(Left, TNodeWeakPtr());
        std::swap(left, Left);
        return left;
    }

    // Меняем тип ссылки на родителя с shared_ptr на weak_ptr.
    TNodePtr ReplaceRight(TNodePtr right) {
        SetParent(right, this->weak_from_this());
        SetParent(Right, TNodeWeakPtr());
        std::swap(right, Right);
        return right;
    }

    TNodePtr ReplaceRightWithLeaf(T value) {
        return ReplaceRight(CreateLeaf(value));
    }

    TNodePtr ReplaceLeftWithLeaf(T value) {
        return ReplaceLeft(CreateLeaf(value));
    }

    TNodePtr RemoveLeft() {
        return ReplaceLeft(nullptr);
    }

    TNodePtr RemoveRight() {
        return ReplaceRight(nullptr);
    }

private:
    T Value;
    TNodePtr Left = nullptr;
    TNodePtr Right = nullptr;
    // Ссылку на родителя храним в виде weak_ptr чтобы избежать циклических ссылок, но все еще иметь возможность проверить, существует ли объект. 
    TNodeWeakPtr Parent = TNodeWeakPtr();

    TNode(T value)
        : Value(value)
    {
    }

    TNode(T value, TNodePtr left, TNodePtr right)
        : Value(value)
        , Left(left ? left->shared_from_this() : TNodePtr{nullptr})
        , Right(right ? right->shared_from_this() : TNodePtr{nullptr})
    {
    }

    static void SetParent(TNodePtr node, TNodeWeakPtr parent) {
        if (node) {
            node->Parent = parent;
        }
    }
};

} // namespace NBinTree
