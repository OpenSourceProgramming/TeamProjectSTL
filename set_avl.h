/**************************************************
 * Copyright INHA_OSAP_004_Froyo
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * Contributors: Lee Seung-Bin
 * Latest Updated on 2023-12-06
**************************************************/

#ifndef SET_AVL_H
#define SET_AVL_H

#include "node_avl.h"
#include "set.h"

class SetAVL : public Set
{
public:
    SetAVL() : size_(0), root_(nullptr) {}
    // SetAVL(const SetAVL& setavl);
    // SetAVL& operator=(const SetAVL& setavl);
    ~SetAVL() {}

    // Basic 기능
    // key를 root로 하는 subtree에서 최솟값을 갖는 node의 값과 depth를 출력
    void Minimum(const int key) override final;

    // key를 root로 하는 subtree에서 최댓값을 갖는 node의 값과 depth를 출력
    void Maximum(const int key) override final;

    // Set이 비어있으면 1, 그렇지 않으면 0을 return
    bool IsEmpty() const override final { return size_ == 0; }

    // Set에 들어있는 원소의 개수 return
    int GetSize() const override final { return size_; }

    // 해당 key를 가지고 있는 node의 depth를 return
    int Find(const int key) override final;

    // num을 삽입하고 해당 node의 depth를 출력
    int Insert(const int num) override final;

    // Advanced 기능
    // 해당 key를 가지고 있는 node의 depth와 rank를 출력
    // rank: Set에서 해당 node보다 작은 key 값을 가진 node의 개수 + 1
    // void GetRank(const int num) override final;

    // 해당 key를 가지고 있는 node의 depth를 출력하고 해당 노드를 삭제
    // void Erase(const int num) override final;
private:
    // Set에 들어있는 원소의 개수
    int size_;

    // Set의 root node
    NodeAVL* root_;

    // 해당 node의 height를 재설정
    void UpdateHeight(NodeAVL* node);

    // start_node부터 root node까지 모든 node의 height 갱신
    void UpdateHeightUntilRoot(NodeAVL* start_node);

    // 해당 node의 (left subtree의 height) - (right subtree의 height)의 값을 return
    int GetBalanceFactor(NodeAVL* node);

    // 해당 node의 depth를 return
    int getDepth(NodeAVL* node);

    // key값을 가지고 있는 해당 node의 depth를 return
    int findDepth(NodeAVL *node, int key, int depth);

    // new_node부터 root node까지 balance factor를 계산함
    // balance factor의 절댓값이 2 이상인 경우 Restructuring을 진행
    void Restructuring(NodeAVL* new_node);

    // Left Left Case에 대하여 restructuring 진행
    void RestructuringForLeftLeftCase(
        NodeAVL* current_node,
        NodeAVL* parent_node,
        NodeAVL* grand_parent_node);

    // Left Right Case에 대하여 restructuring 진행
    void RestructuringForLeftRightCase(
        NodeAVL* current_node,
        NodeAVL* parent_node,
        NodeAVL* grand_parent_node);

    // Right Left Case에 대하여 restructuring 진행
    void RestructuringForRightLeftCase(
        NodeAVL* current_node,
        NodeAVL* parent_node,
        NodeAVL* grand_parent_node);

    // Right Right Case에 대하여 restructuring 진행
    void RestructuringForRightRightCase(
        NodeAVL* current_node,
        NodeAVL* parent_node,
        NodeAVL* grand_parent_node);
};

#endif