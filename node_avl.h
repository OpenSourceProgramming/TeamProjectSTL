/**************************************************
 * Copyright INHA_OSAP_004_Froyo
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * Contributors: Lee Seung-Bin
 * Latest Updated on 2023-12-15
**************************************************/

#ifndef NODE_AVL_H
#define NODE_AVL_H

#include "node.h"

// 복사 생성자, 대입 연산자 사용 방지
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
    Typename(const Typename&);             \
    void operator=(const Typename&)

template <typename T>
class NodeAVL : public Node<T>
{
public:
    NodeAVL(T key) :
        key_(key), height_(0), size_(1),
        parent_(nullptr), left_(nullptr), 
        right_(nullptr) {}
    ~NodeAVL() {}
    void SetKey(const T key) { key_ = key; }
    void SetParent(NodeAVL<T>* parent) { parent_ = parent; }
    void SetHeight(const int height) { height_ = height; }
    void SetSize(const int size) { size_ = size; }
    void SetLeft(NodeAVL<T>* left) { left_ = left; }
    void SetRight(NodeAVL<T>* right) { right_ = right; }
    T GetKey() const override final { return key_; }
    int GetHeight() const { return height_; }
    int GetSize() const { return size_; }
    NodeAVL<T>* GetParent() const { return parent_; }
    NodeAVL<T>* GetLeft() const { return left_; }
    NodeAVL<T>* GetRight() const { return right_; }
private:
    // 복사 생성자, 대입 연산자 사용 방지
    DISALLOW_COPY_AND_ASSIGN(NodeAVL<T>);

    // 해당 node의 key값
    T key_;

    // 해당 node의 child 중 height_의 최댓값 + 1 (left node일 경우 0)
    int height_;

    // 해당 node를 루트 노드로 하는 subtree의 node의 개수 (자기 자신 포함)
    int size_;

    // 부모 노드
    NodeAVL<T>* parent_;

    // Left Child 노드
    NodeAVL<T>* left_;

    // Right Child 노드
    NodeAVL<T>* right_;
};

#endif