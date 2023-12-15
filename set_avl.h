/**************************************************
 * Copyright INHA_OSAP_004_Froyo
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * Contributors: Lee Seung-Bin, Choi Yi-Joon, Majunliang, Lee Jin-Woo
 * Latest Updated on 2023-12-15
**************************************************/

#ifndef SET_AVL_H
#define SET_AVL_H

#include "node_avl.h"
#include "set.h"

template <typename T>
class SetAVL : public Set<T>
{
public:
    SetAVL() : size_(0), root_(nullptr) {}
    SetAVL(const SetAVL& setavl);
    SetAVL& operator=(const SetAVL& setavl);
    ~SetAVL();

    // Basic 기능
    // key를 root로 하는 subtree에서 최솟값을 갖는 node의 값과 depth를 출력
    void Minimum(const T key) override final;

    // key를 root로 하는 subtree에서 최댓값을 갖는 node의 값과 depth를 출력
    void Maximum(const T key) override final;

    // Set이 비어있으면 1, 그렇지 않으면 0을 return
    bool IsEmpty() const override final { return size_ == 0; }

    // Set에 들어있는 원소의 개수 return
    int GetSize() const override final { return size_; }

    // 해당 key를 가지고 있는 node의 depth를 return
    int Find(const T key) override final;

    // key를 삽입하고 해당 node의 depth를 출력
    int Insert(const T key) override final;

    // Advanced 기능
    // 해당 key를 가지고 있는 node의 depth와 rank를 출력
    // rank: Set에서 해당 node보다 작은 key 값을 가진 node의 개수 + 1
    void Rank(const T key) override final;

    // 해당 key를 가지고 있는 노드를 삭제하고 해당 노드의 depth를 return
    int Erase(const T key) override final;
private:
    // Set에 들어있는 원소의 개수
    int size_;

    // Set의 root node
    NodeAVL<T>* root_;

    // Set을 Deep Copy함
    void DeepCopyForSetAVL(
        NodeAVL<T>* original_parent_node,
        NodeAVL<T>* copied_parent_node);

    // 후위순회를 통해 SetAVL에 있는 노드의 메모리를 해제시킴
    void FreeMemoryForSetAVL(NodeAVL<T>* parent_node);

    // 해당 node의 height를 재설정
    void UpdateHeight(NodeAVL<T>* node);

    // start_node부터 root node까지 모든 node의 height 갱신
    void UpdateHeightUntilRoot(NodeAVL<T>* start_node);

    // 해당 node의 size를 재설정
    void UpdateSize(NodeAVL<T>* node);

    // start_node부터 root node까지 모든 node의 size 갱신
    void UpdateSizeUntilRoot(NodeAVL<T>* start_node);

    // 해당 node의 (left subtree의 height) - (right subtree의 height)의 값을 return
    int GetBalanceFactor(NodeAVL<T>* node);

    // 해당 node의 depth를 return
    int GetDepth(NodeAVL<T>* node);

    // key값을 가지고 있는 해당 node의 depth를 return
    int FindDepth(NodeAVL<T> *node, T key, int depth);

    // new_node부터 root node까지 balance factor를 계산함
    // balance factor의 절댓값이 2 이상인 경우 Restructuring을 진행
    void Restructuring(NodeAVL<T>* new_node);

    // Left Left Case에 대하여 restructuring 진행
    void RestructuringForLeftLeftCase(
        NodeAVL<T>* current_node,
        NodeAVL<T>* parent_node,
        NodeAVL<T>* grand_parent_node);

    // Left Right Case에 대하여 restructuring 진행
    void RestructuringForLeftRightCase(
        NodeAVL<T>* current_node,
        NodeAVL<T>* parent_node,
        NodeAVL<T>* grand_parent_node);

    // Right Left Case에 대하여 restructuring 진행
    void RestructuringForRightLeftCase(
        NodeAVL<T>* current_node,
        NodeAVL<T>* parent_node,
        NodeAVL<T>* grand_parent_node);

    // Right Right Case에 대하여 restructuring 진행
    void RestructuringForRightRightCase(
        NodeAVL<T>* current_node,
        NodeAVL<T>* parent_node,
        NodeAVL<T>* grand_parent_node);

    // node를 삭제 (node의 자식이 없는 경우)
    void EraseNodeThatHasNoChild(NodeAVL<T>* node);

    // node를 삭제 (node의 자식이 1개만 있는 경우)
    void EraseNodeThatHasOnlyOneChild(NodeAVL<T>* node);

    // node를 삭제 (node의 자식이 2개 있는 경우)
    void EraseNodeThatHasTwoChildren(NodeAVL<T>* node);

    // node의 successor를 찾음
    NodeAVL<T>* FindSuccessor(NodeAVL<T>* node);

    // Erase 기능을 수행할 때 필요에 따라 Restructuring을 진행함
    void RestructuringForErase(NodeAVL<T>* node);

    // AVL 트리 전위 순회
    void RankTraversal(NodeAVL<T>* current_node, const T key, int& rank);
};

#include "set_avl.hpp"

#endif