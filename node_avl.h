/**************************************************
 * Copyright INHA_OSAP_004_Froyo
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * Contributors: Lee Seung-Bin
 * Latest Updated on 2023-11-23
**************************************************/

#ifndef NODE_AVL_H
#define NODE_AVL_H

#include "node.h"

// 복사 생성자, 대입 연산자 사용 방지
#define DISALLOW_COPY_AND_ASSIGN(Typename) \
    Typename(const Typename&);             \
    void operator=(const Typename&)

class NodeAVL : public Node
{
public:
    NodeAVL(int num) : 
        num_(num), height_(0),
        parent_(nullptr), left_(nullptr), 
        right_(nullptr) {}
    ~NodeAVL() {}
    void SetParent(NodeAVL* parent) { parent_ = parent; }
    void SetHeight(const int height) { height_ = height; }
    void SetLeft(NodeAVL* left) { left_ = left; }
    void SetRight(NodeAVL* right) { right_ = right; }
    int GetNum() const override final { return num_; }
    int GetHeight() const { return height_; }
    NodeAVL* GetParent() const { return parent_; }
    NodeAVL* GetLeft() const { return left_; }
    NodeAVL* GetRight() const { return right_; }
private:
    // 복사 생성자, 대입 연산자 사용 방지
    DISALLOW_COPY_AND_ASSIGN(NodeAVL);

    // 해당 node의 key값
    int num_;

    // 해당 node의 child 중 height_의 최댓값 + 1 (left node일 경우 0)
    int height_;

    // 부모 노드
    NodeAVL* parent_;

    // Left Child 노드
    NodeAVL* left_;

    // Right Child 노드
    NodeAVL* right_;
};

#endif