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

#include "set_avl.h"

#include <iostream>
#include <vector>

// pair에 대한 출력 연산자 오버로딩
template <typename T>
std::ostream& operator<<(std::ostream& output_stream, const std::pair<T, T>& pair)
{
    std::cout << "(" << pair.first << ", " << pair.second << ")";
    return output_stream;
}

// vector에 대한 출력 연산자 오버로딩
template <typename T>
std::ostream& operator<<(std::ostream& output_stream, const std::vector<T>& vector)
{
    std::cout << "(";

    for (auto it = vector.begin(); it < vector.end() - 1; it++)
    {
        std::cout << *it << ", ";
    }

    std::cout << *(vector.end() - 1) << ")";

    return output_stream;
}

// 복사생성자 정의
template <typename T>
SetAVL<T>::SetAVL(const SetAVL<T>& setavl)
{
    size_ = setavl.GetSize();

    if (setavl.root_ != nullptr)
    {
        root_ = new NodeAVL<T>(setavl.root_->GetKey());
        // Deep Copy를 통해 SetAVL을 복사함
        DeepCopyForSetAVL(setavl.root_, root_);
    }
    else
    {
        root_ = nullptr;
    }
}

// 대입연산자 정의
template <typename T>
SetAVL<T>& SetAVL<T>::operator=(const SetAVL<T>& setavl)
{
    size_ = setavl.GetSize();

    if (setavl.root_ != nullptr)
    {
        root_ = new NodeAVL<T>(setavl.root_->GetKey());
        // Deep Copy를 통해 SetAVL을 복사함
        DeepCopyForSetAVL(setavl.root_, root_);
    }
    else
    {
        root_ = nullptr;
    }
}

// 소멸자 정의
template <typename T>
SetAVL<T>::~SetAVL()
{
    if (root_ != nullptr)
    {
        FreeMemoryForSetAVL(root_);
    }
}

// Set을 Deep Copy함
template <typename T>
void SetAVL<T>::DeepCopyForSetAVL(
    NodeAVL<T>* original_parent_node,
    NodeAVL<T>* copied_parent_node)
{
    if (original_parent_node->GetLeft() != nullptr)
    {
        NodeAVL<T>* node = new NodeAVL<T>(original_parent_node->GetLeft()->GetKey());
        copied_parent_node->SetLeft(node);
        DeepCopyForSetAVL(
            original_parent_node->GetLeft(), copied_parent_node->GetLeft());
    }

    if (original_parent_node->GetRight() != nullptr)
    {
        NodeAVL<T>* node = new NodeAVL<T>(original_parent_node->GetRight()->GetKey());
        copied_parent_node->SetRight(node);
        DeepCopyForSetAVL(
            original_parent_node->GetRight(), copied_parent_node->GetRight());
    }
}

// 후위순회를 통해 SetAVL에 있는 노드의 메모리를 해제시킴
template <typename T>
void SetAVL<T>::FreeMemoryForSetAVL(NodeAVL<T>* parent_node)
{
    if (parent_node->GetLeft() != nullptr)
    {
        FreeMemoryForSetAVL(parent_node->GetLeft());
    }

    if (parent_node->GetRight() != nullptr)
    {
        FreeMemoryForSetAVL(parent_node->GetRight());
    }

    delete parent_node;
}

// key를 root로 하는 subtree에서 최솟값을 갖는 node의 값과 depth를 출력
template <typename T>
void SetAVL<T>::Minimum(const T key)
{
    NodeAVL<T>* node = root_;
    // key를 root로 하는 node찾기
    while(node != nullptr)
    {
        if(key == node->GetKey())
            break;
        else if(key < node->GetKey())
            node = node->GetLeft();
        else
            node = node->GetRight();
    }

     // Set에 존재하지 않는 원소에 대한 처리
    if (node == nullptr)
    {
        std::cout << "-1, -1" << std::endl;
        return;
    }
    
    // subtree에서 최솟값을 갖는 node찾기
    while (node != nullptr && node->GetLeft() != nullptr)
    {
        node = node->GetLeft();
    }
    std::cout << node->GetKey() << " " << Find(node->GetKey()) << "\n";
}

// key를 root로 하는 subtree에서 최댓값을 갖는 node의 값과 depth를 출력
template <typename T>
void SetAVL<T>::Maximum(const T key)
{
    NodeAVL<T>* node = root_;
    // key를 root로 하는 node찾기
    while (node != nullptr)
    {
        if (key == node->GetKey())
            break;
        else if (key < node->GetKey())
            node = node->GetLeft();
        else
            node = node->GetRight();
    }

    // Set에 존재하지 않는 원소에 대한 처리
    if (node == nullptr)
    {
        std::cout << "-1, -1" << std::endl;
        return;
    }
    
    // subtree에서 최댓값을 갖는 node찾기
    while (node != nullptr && node->GetRight() != nullptr)
    {
        node = node->GetRight();
    }
    std::cout << node->GetKey() << " " << Find(node->GetKey()) << "\n";
}

// 해당 key를 가지고 있는 node의 depth를 return
template <typename T>
int SetAVL<T>::Find(const T key)
{
    int depth = FindDepth(root_, key, 0);
    return depth;
}

template <typename T>
int SetAVL<T>::FindDepth(NodeAVL<T>* node, T key, int depth)
{
    if (node == nullptr)
    {
        return -1;
    }

    if (key == node->GetKey())
    {
        return depth;
    }
    else if (key < node->GetKey())
    {
        return FindDepth(node->GetLeft(), key, depth + 1);
    }
    else
    {
        return FindDepth(node->GetRight(), key, depth + 1);
    }
}

// key를 삽입하고 해당 node의 depth를 출력
template <typename T>
int SetAVL<T>::Insert(const T key)
{
    if (root_ == nullptr)
    {
        // Set에 아무런 원소도 없는 경우
        root_ = new NodeAVL<T>(key);

        // 새로 삽입한 node의 height는 0
        root_->SetHeight(0);
        size_ = 1;

        // 새로 삽입한 node의 depth 출력
        // root node의 depth는 0으로 정의
        return 0;
    }
    else
    {
        NodeAVL<T>* current_node = root_;
        NodeAVL<T>* new_node = new NodeAVL<T>(key);

        // 적절한 위치에 Node 삽입하기
        while (1)
        {
            if (key == current_node->GetKey())
            {
                // 삽입하려고 하는 원소가 이미 Set에 들어있음
                // new_node 메모리 해제
                delete new_node;
                return -1;
            }
            else if (key < current_node->GetKey())
            {
                // Left Child로 이동
                if (current_node->GetLeft() == nullptr)
                {
                    // Left Child가 없는 경우
                    // parent node 설정
                    new_node->SetParent(current_node);

                    // Left Child에 노드 삽입
                    current_node->SetLeft(new_node);

                    // 새로운 node의 height는 leaf 노드이므로 height는 0
                    new_node->SetHeight(0);

                    // Set에 들어있는 원소의 개수 1 증가
                    size_++;

                    // new_node부터 root node까지 모든 node의 height 갱신
                    UpdateHeightUntilRoot(new_node);

                    // new_node부터 root node까지 balance factor를 계산함
                    // balance factor의 절댓값이 2 이상인 경우 Restructuring을 진행
                    Restructuring(new_node);

                    // 새로 삽입한 node의 depth를 return
                    return GetDepth(new_node);
                }
                else
                {
                    // Left Child가 있는 경우
                    // Left Child로 이동
                    current_node = current_node->GetLeft();
                }
            }
            else
            {
                // Right Child로 이동
                if (current_node->GetRight() == nullptr)
                {
                    // Right Child가 없는 경우
                    // parent node 설정
                    new_node->SetParent(current_node);

                    // Right Child에 노드 삽입
                    current_node->SetRight(new_node);

                    // 새로운 node의 height는 leaf 노드이므로 height는 0
                    new_node->SetHeight(0);
                    
                    // Set에 들어있는 원소의 개수 1 증가
                    size_++;

                    // new_node부터 root node까지 모든 node의 height 갱신
                    UpdateHeightUntilRoot(new_node);

                    // new_node부터 root node까지 balance factor를 계산함
                    // balance factor의 절댓값이 2 이상인 경우 Restructuring을 진행
                    Restructuring(new_node);

                    // 새로 삽입한 node의 depth를 return
                    return GetDepth(new_node);
                }
                else
                {
                    // Right Child가 있는 경우
                    // Right Child로 이동
                    current_node = current_node->GetRight();
                }
            }
        }
    }
}

// 해당 key를 가지고 있는 node의 depth와 rank를 출력
// rank: Set에서 해당 node보다 작은 key 값을 가진 node의 개수 + 1
template <typename T>
void SetAVL<T>::Rank(const T key)
{
    NodeAVL<T>* root_node = root_;
    int rank = 1;

    RankTraversal(root_node, key, rank);
    
    int depth = Find(key);

    if (depth == -1)
        std::cout << "0\n";
    else
        std::cout << depth << " " << rank;
}

// AVL 트리 전위 순회
template <typename T>
void SetAVL<T>::RankTraversal(NodeAVL<T>* current_node, const T key, int& rank)
{
    if (current_node == nullptr)
        return;
    if (current_node->GetKey() < key)
    {
        rank++;

        if (current_node->GetLeft() != nullptr)
            RankTraversal(current_node->GetLeft(), key, rank);

        if (current_node->GetRight() != nullptr)
            RankTraversal(current_node->GetRight(), key, rank);
    }
    else
    {
        // right child는 탐색할 필요 없음
        if (current_node->GetLeft() != nullptr)
            RankTraversal(current_node->GetLeft(), key, rank);
    }
}

// 해당 key를 가지고 있는 노드를 삭제하고 해당 노드의 depth를 return
template <typename T>
int SetAVL<T>::Erase(const T key)
{
    // 삭제하려고 하는 노드
    NodeAVL<T>* erase_node = root_;

    // 삭제하려고 하는 노드를 검색
    while (1)
    {
        if (key == erase_node->GetKey())
        {
            // 삭제하려고 하는 node를 찾음
            break;
        }
        else if (key < erase_node->GetKey())
        {
            // Left Child로 이동
            if (erase_node->GetLeft() == nullptr)
            {
                // Left Child가 없는 경우
                // 삭제하려고 하는 노드를 찾지 못함
                return -1;
            }
            else
            {
                // Left Child가 있는 경우
                // Left Child로 이동
                erase_node = erase_node->GetLeft();
            }
        }
        else
        {
            // Right Child로 이동
            if (erase_node->GetRight() == nullptr)
            {
                // Right Child가 없는 경우
                // 삭제하려고 하는 노드를 찾지 못함
                return -1;
            }
            else
            {
                // Right Child가 있는 경우
                // Right Child로 이동
                erase_node = erase_node->GetRight();
            }
        }
    }

    // 삭제하려고 하는 노드의 depth를 저장
    int erase_node_depth = GetDepth(erase_node);

    if ((erase_node->GetLeft() == nullptr)
    && (erase_node->GetRight() == nullptr))
    {
        // 삭제하려고 하는 노드의 자식이 없는 경우
        EraseNodeThatHasNoChild(erase_node);
    }
    else if ((erase_node->GetLeft() != nullptr)
    && (erase_node->GetRight() != nullptr))
    {
        // 삭제하려고 하는 노드의 자식이 2개인 경우
        EraseNodeThatHasTwoChildren(erase_node);
    }
    else
    {
        // 삭제하려고 하는 노드의 자식이 1개인 경우
        EraseNodeThatHasOnlyOneChild(erase_node);
    }

    // 원소의 개수 1 감소
    size_--;

    // 삭제한 노드의 depth를 return
    return erase_node_depth;
}

// 해당 node의 height를 재설정
template <typename T>
void SetAVL<T>::UpdateHeight(NodeAVL<T>* node)
{
    // left subtree의 height
    int left_subtree_height = -1;

    // right subtree의 height
    int right_subtree_height = -1;

    if (node->GetLeft() != nullptr)
    {
        left_subtree_height = node->GetLeft()->GetHeight();
    }

    if (node->GetRight() != nullptr)
    {
        right_subtree_height = node->GetRight()->GetHeight();
    }

    if ((left_subtree_height == -1)
        && (right_subtree_height == -1))
    {
        // left subtree와 right subtree 모두 empty tree인 경우
        // parameter로 들어온 node는 leaf 노드
        // leaf 노드의 height는 0으로 정의
        node->SetHeight(0);
    }
    else
    {
        // left subtree와 right subtree 중 적어도 하나는 empty tree가 아닌 경우
        node->SetHeight(
            std::max(left_subtree_height, right_subtree_height) + 1);
    }
}

// start_node부터 root node까지 모든 node의 height 갱신
template <typename T>
void SetAVL<T>::UpdateHeightUntilRoot(NodeAVL<T>* start_node)
{
    NodeAVL<T>* current_node = start_node;

    if (current_node == nullptr)
    {
        return;
    }

    while (1)
    {
        // current_node의 height 재설정
        UpdateHeight(current_node);

        if (current_node == root_)
        {
            // current_node가 root 노드이므로 더 이상 height를 갱신할 node가 없음
            break;
        }
        else
        {
            // 부모 노드로 이동
            current_node = current_node->GetParent();
        }
    }
}

// 해당 node의 size를 재설정
template <typename T>
void SetAVL<T>::UpdateSize(NodeAVL<T>* node)
{
    int left_subtree_size = 0;
    int right_subtree_size = 0;

    if (node->GetLeft() != nullptr)
    {
        left_subtree_size = node->GetLeft()->GetSize();
    }

    if (node->GetRight() != nullptr)
    {
        right_subtree_size = node->GetRight()->GetSize();
    }

    node->SetSize(left_subtree_size + right_subtree_size + 1);
}

// start_node부터 root node까지 모든 node의 size 갱신
template <typename T>
void SetAVL<T>::UpdateSizeUntilRoot(NodeAVL<T>* start_node)
{
    NodeAVL<T>* current_node = start_node;

    if (current_node == nullptr)
    {
        return;
    }

    while (1)
    {
        // current_node의 height 재설정
        UpdateSize(current_node);

        if (current_node == root_)
        {
            // current_node가 root 노드이므로 더 이상 size를 갱신할 node가 없음
            break;
        }
        else
        {
            // 부모 노드로 이동
            current_node = current_node->GetParent();
        }
    }
}

// 해당 node의 (left subtree의 height) - (right subtree의 height)의 값을 return
template <typename T>
int SetAVL<T>::GetBalanceFactor(NodeAVL<T>* node)
{
    int left_subtree_height = -1;
    int right_subtree_height = -1;

    if (node->GetLeft() != nullptr)
    {
        left_subtree_height = node->GetLeft()->GetHeight();
    }

    if (node->GetRight() != nullptr)
    {
        right_subtree_height = node->GetRight()->GetHeight();
    }

    return left_subtree_height - right_subtree_height;
}

// 해당 node의 depth를 return
template <typename T>
int SetAVL<T>::GetDepth(NodeAVL<T>* node)
{
    // root node의 depth를 0으로 정의
    int depth = 0;
    NodeAVL<T>* current_node = node;

    while (1)
    {
        if (current_node == root_)
        {
            return depth;
        }
        else
        {
            current_node = current_node->GetParent();
            depth++;
        }
    }
}

// new_node부터 root node까지 balance factor를 계산함
// balance factor의 절댓값이 2 이상인 경우 Restructuring을 진행
template <typename T>
void SetAVL<T>::Restructuring(NodeAVL<T>* new_node)
{
    NodeAVL<T>* current_node = new_node;
    NodeAVL<T>* parent_node = new_node->GetParent();
    NodeAVL<T>* grand_parent_node = parent_node->GetParent();

    if (grand_parent_node == nullptr)
    {
        // grand parent node가 null일 경우 restructuring을 진행할 필요 없음
        return;
    }
    else
    {
        while (1)
        {
            int balance_factor = GetBalanceFactor(grand_parent_node);

            if (std::abs(balance_factor) <= 1)
            {
                // balance_factor의 절댓값이 1 이하인 경우 
                // restructuring을 진행할 필요 없음

                if (grand_parent_node == root_)
                {
                    break;
                }
                else
                {
                    // current_node, parent_node, grand_parent_node 모두 자신의 부모 노드로 이동
                    current_node = parent_node;
                    parent_node = grand_parent_node;
                    grand_parent_node = grand_parent_node->GetParent();
                }
            }
            else
            {
                // balance_factor의 절댓값이 2 이상인 경우 
                // restructuring이 필요함
            
                if (grand_parent_node->GetLeft() == parent_node)
                {
                    if (parent_node->GetLeft() == current_node)
                    {
                        /*
                             z
                            /
                           y
                          /
                         x
                        */
                        RestructuringForLeftLeftCase(
                            current_node, parent_node, grand_parent_node);
                    }
                    else
                    {
                        /*
                            z
                           /
                          y
                           \
                            x
                        */
                        RestructuringForLeftRightCase(
                            current_node, parent_node, grand_parent_node);
                    }
                }
                else
                {
                    if (parent_node->GetLeft() == current_node)
                    {
                        /*
                          z
                           \
                            y
                           /
                          x
                        */
                        RestructuringForRightLeftCase(
                            current_node, parent_node, grand_parent_node);
                    }
                    else
                    {
                        /*
                          z
                           \
                            y
                             \
                              x
                        */
                        RestructuringForRightRightCase(
                            current_node, parent_node, grand_parent_node);
                    }
                }
            }
        }
    }
}

// Left Left Case에 대하여 restructuring 진행
template <typename T>
void SetAVL<T>::RestructuringForLeftLeftCase(
    NodeAVL<T>* current_node, 
    NodeAVL<T>* parent_node,
    NodeAVL<T>* grand_parent_node)
{
    /*
         z
        /
       y
      /
     x
    */
    
    // grand_parent_node의 부모 노드(grand_grand_parent_node)가 있는지 확인
    if (grand_parent_node->GetParent() != nullptr)
    {
        // grand_parent_node의 부모 노드가 있을 경우

        if (grand_parent_node->GetParent()->GetLeft() == grand_parent_node)
        {
            // grand_parent_node가 grand_grand_parent_node의 left child인 경우
            // grand_grand_parent_node의 left child를 parent_node로 설정
            grand_parent_node->GetParent()->SetLeft(parent_node);
        }
        else
        {
            // grand_parent_node가 grand_grand_parent_node의 right child인 경우
            // grand_grand_parent_node의 right child를 parent_node로 설정
            grand_parent_node->GetParent()->SetRight(parent_node);
        }
    }
    else
    {
        // grand_parent_node는 root 노드
        // restructuring에 의해 parent_node가 root 노드가 됨
        root_ = parent_node;
    }

    NodeAVL<T>* subtree_t3_root = parent_node->GetRight();
    NodeAVL<T>* subtree_t4_root = grand_parent_node->GetRight();

    // current_node의 경우 parent, left, right node 모두 변함 없음

    // parent_node의 parent, right node 재설정
    // parent_node의 left node는 변함 없음
    parent_node->SetRight(grand_parent_node);
    parent_node->SetParent(grand_parent_node->GetParent());

    // grand_parent_node의 parent, left, right node 재설정
    // grand_parent_node의 right node는 변함 없음
    grand_parent_node->SetParent(parent_node);
    grand_parent_node->SetLeft(subtree_t3_root);

    // subtree_t3_root의 parent 재설정
    if (subtree_t3_root != nullptr)
    {
        subtree_t3_root->SetParent(grand_parent_node);
    }

    // current_node, parent_node, grand_parent_node에 대한 size 재설정
    // current_node의 경우 size의 변화가 없음
    int subtree_t3_root_size = 0;
    int subtree_t4_root_size = 0;

    if (subtree_t3_root != nullptr)
    {
        subtree_t3_root_size = subtree_t3_root->GetSize();
    }

    if (subtree_t4_root != nullptr)
    {
        subtree_t4_root_size = subtree_t4_root->GetSize();
    }

    grand_parent_node->SetSize(subtree_t3_root_size + subtree_t4_root_size + 1);
    parent_node->SetSize(current_node->GetSize() + grand_parent_node->GetSize() + 1);

    // grand_parent_node부터 root까지 height 재설정
    UpdateHeightUntilRoot(grand_parent_node);
}

// Left Right Case에 대하여 restructuring 진행
template <typename T>
void SetAVL<T>::RestructuringForLeftRightCase(
    NodeAVL<T>* current_node,
    NodeAVL<T>* parent_node,
    NodeAVL<T>* grand_parent_node)
{
    /*
         z
        /
       y
        \
         x
    */

    // grand_parent_node의 부모 노드(grand_grand_parent_node)가 있는지 확인
    if (grand_parent_node->GetParent() != nullptr)
    {
        // grand_parent_node의 부모 노드가 있을 경우

        if (grand_parent_node->GetParent()->GetLeft() == grand_parent_node)
        {
            // grand_parent_node가 grand_grand_parent_node의 left child인 경우
            // grand_grand_parent_node의 left child를 current_node로 설정
            grand_parent_node->GetParent()->SetLeft(current_node);
        }
        else
        {
            grand_parent_node->GetParent()->SetRight(current_node);
        }
    }
    else
    {
        root_ = current_node;
    }

    NodeAVL<T>* subtree_t1_root = parent_node->GetLeft();
    NodeAVL<T>* subtree_t2_root = current_node->GetLeft();
    NodeAVL<T>* subtree_t3_root = current_node->GetRight();
    NodeAVL<T>* subtree_t4_root = grand_parent_node->GetRight();

    // current_node의 parent, left, right node 재설정
    current_node->SetParent(grand_parent_node->GetParent());
    current_node->SetLeft(parent_node);
    current_node->SetRight(grand_parent_node);

    // parent_node의 parent, left, right node 재설정
    // parent_node의 left node는 변함 없음
    parent_node->SetParent(current_node);
    parent_node->SetRight(subtree_t2_root);

    // subtree_t2_root의 parent 재설정
    if (subtree_t2_root != nullptr)
    {
        subtree_t2_root->SetParent(parent_node);
    }

    // grand_parent_node의 parent, left, right node 재설정
    // grand_parent_node의 right node는 변함 없음
    grand_parent_node->SetParent(current_node);
    grand_parent_node->SetLeft(subtree_t3_root);

    // subtree_t3_root의 parent 재설정
    if (subtree_t3_root != nullptr)
    {
        subtree_t3_root->SetParent(grand_parent_node);
    }

    // parent_node, grand_parent_node의 height 재설정
    UpdateHeight(parent_node);
    UpdateHeight(grand_parent_node);

    // current_node부터 root까지 height 재설정
    UpdateHeightUntilRoot(current_node);

    // current_node, parent_node, grand_parent_node에 대한 size 재설정
    int subtree_t1_root_size = 0;
    int subtree_t2_root_size = 0;
    int subtree_t3_root_size = 0;
    int subtree_t4_root_size = 0;

    if (subtree_t1_root != nullptr)
    {
        subtree_t1_root_size = subtree_t1_root->GetSize();
    }

    if (subtree_t2_root != nullptr)
    {
        subtree_t2_root_size = subtree_t2_root->GetSize();
    }

    if (subtree_t3_root != nullptr)
    {
        subtree_t3_root_size = subtree_t3_root->GetSize();
    }

    if (subtree_t4_root != nullptr)
    {
        subtree_t4_root_size = subtree_t4_root->GetSize();
    }

    grand_parent_node->SetSize(subtree_t3_root_size + subtree_t4_root_size + 1);
    parent_node->SetSize(subtree_t1_root_size + subtree_t2_root_size + 1);
    current_node->SetSize(parent_node->GetSize() + grand_parent_node->GetSize() + 1);
}

// Right Left Case에 대하여 restructuring 진행
template <typename T>
void SetAVL<T>::RestructuringForRightLeftCase(
    NodeAVL<T>* current_node,
    NodeAVL<T>* parent_node,
    NodeAVL<T>* grand_parent_node)
{
    /*
      z
       \
        y
       /
      x
    */

    // grand_parent_node의 부모 노드(grand_grand_parent_node)가 있는지 확인
    if (grand_parent_node->GetParent() != nullptr)
    {
        // grand_parent_node의 부모 노드가 있을 경우

        if (grand_parent_node->GetParent()->GetLeft() == grand_parent_node)
        {
            // grand_parent_node가 grand_grand_parent_node의 left child인 경우
            // grand_grand_parent_node의 left child를 current_node로 설정
            grand_parent_node->GetParent()->SetLeft(current_node);
        }
        else
        {
            // grand_parent_node가 grand_grand_parent_node의 right child인 경우
            // grand_grand_parent_node의 right child를 current_node로 설정
            grand_parent_node->GetParent()->SetRight(current_node);
        }
    }
    else
    {
        // grand_parent_node는 root 노드
        // restructuring에 의해 current_node가 root 노드가 됨
        root_ = current_node;
    }

    NodeAVL<T>* subtree_t1_root = grand_parent_node->GetLeft();
    NodeAVL<T>* subtree_t2_root = current_node->GetLeft();
    NodeAVL<T>* subtree_t3_root = current_node->GetRight();
    NodeAVL<T>* subtree_t4_root = parent_node->GetRight();

    // current_node의 parent, left, right node 재설정
    current_node->SetParent(grand_parent_node->GetParent());
    current_node->SetLeft(grand_parent_node);
    current_node->SetRight(parent_node);

    // parent_node의 parent, left, right node 재설정
    // parent_node의 right node는 변함 없음
    parent_node->SetParent(current_node);
    parent_node->SetLeft(subtree_t3_root);

    // subtree_t3_root의 parent 재설정
    if (subtree_t3_root != nullptr)
    {
        subtree_t3_root->SetParent(parent_node);
    }

    // grand_parent_node의 parent, left, right node 재설정
    // grand_parent_node의 left node는 변함 없음
    grand_parent_node->SetParent(current_node);
    grand_parent_node->SetRight(subtree_t2_root);

    // subtree_t2_root의 parent 재설정
    if (subtree_t2_root != nullptr)
    {
        subtree_t2_root->SetParent(grand_parent_node);
    }

    // parent_node, grand_parent_node의 height 재설정
    UpdateHeight(parent_node);
    UpdateHeight(grand_parent_node);

    // current_node부터 root까지 height 재설정
    UpdateHeightUntilRoot(current_node);

    // current_node, parent_node, grand_parent_node에 대한 size 재설정
    int subtree_t1_root_size = 0;
    int subtree_t2_root_size = 0;
    int subtree_t3_root_size = 0;
    int subtree_t4_root_size = 0;

    if (subtree_t1_root != nullptr)
    {
        subtree_t1_root_size = subtree_t1_root->GetSize();
    }

    if (subtree_t2_root != nullptr)
    {
        subtree_t2_root_size = subtree_t2_root->GetSize();
    }

    if (subtree_t3_root != nullptr)
    {
        subtree_t3_root_size = subtree_t3_root->GetSize();
    }

    if (subtree_t4_root != nullptr)
    {
        subtree_t4_root_size = subtree_t4_root->GetSize();
    }

    grand_parent_node->SetSize(subtree_t1_root_size + subtree_t2_root_size + 1);
    parent_node->SetSize(subtree_t3_root_size + subtree_t4_root_size + 1);
    current_node->SetSize(parent_node->GetSize() + grand_parent_node->GetSize() + 1);
}

// Right Right Case에 대하여 restructuring 진행
template <typename T>
void SetAVL<T>::RestructuringForRightRightCase(
    NodeAVL<T>* current_node,
    NodeAVL<T>* parent_node,
    NodeAVL<T>* grand_parent_node)
{
    /*
      z
       \
        y
         \
          x
    */

    // grand_parent_node의 부모 노드(grand_grand_parent_node)가 있는지 확인
    if (grand_parent_node->GetParent() != nullptr)
    {
        // grand_parent_node의 부모 노드가 있을 경우

        if (grand_parent_node->GetParent()->GetLeft() == grand_parent_node)
        {
            // grand_parent_node가 grand_grand_parent_node의 left child인 경우
            // grand_grand_parent_node의 left child를 parent_node로 설정
            grand_parent_node->GetParent()->SetLeft(parent_node);
        }
        else
        {
            // grand_parent_node가 grand_grand_parent_node의 right child인 경우
            // grand_grand_parent_node의 right child를 parent_node로 설정
            grand_parent_node->GetParent()->SetRight(parent_node);
        }
    }
    else
    {
        // grand_parent_node는 root 노드
        // restructuring에 의해 parent_node가 root 노드가 됨
        root_ = parent_node;
    }

    NodeAVL<T>* subtree_t1_root = grand_parent_node->GetLeft();
    NodeAVL<T>* subtree_t2_root = parent_node->GetLeft();

    // current_node의 경우 parent, left, right node 모두 변함 없음

    // parent_node의 parent, left, right node 재설정
    // parent_node의 right node는 변함 없음
    parent_node->SetParent(grand_parent_node->GetParent());
    parent_node->SetLeft(grand_parent_node);

    // grand_parent_node의 parent, left, right node 재설정
    // grand_parent_node의 left node는 변함 없음
    grand_parent_node->SetParent(parent_node);
    grand_parent_node->SetRight(subtree_t2_root);

    // subtree_t2_root의 parent 재설정
    if (subtree_t2_root != nullptr)
    {
        subtree_t2_root->SetParent(grand_parent_node);
    }

    // grand_parent_node부터 root까지 height 재설정
    UpdateHeightUntilRoot(grand_parent_node);

    // current_node, parent_node, grand_parent_node에 대한 size 재설정
    // current_node의 경우 size의 변화가 없음
    int subtree_t1_root_size = 0;
    int subtree_t2_root_size = 0;

    if (subtree_t1_root != nullptr)
    {
        subtree_t1_root_size = subtree_t1_root->GetSize();
    }

    if (subtree_t2_root != nullptr)
    {
        subtree_t2_root_size = subtree_t2_root->GetSize();
    }

    grand_parent_node->SetSize(subtree_t1_root_size + subtree_t2_root_size + 1);
    parent_node->SetSize(current_node->GetSize() + grand_parent_node->GetSize() + 1);
}

// node를 삭제 (node의 자식이 없는 경우)
template <typename T>
void SetAVL<T>::EraseNodeThatHasNoChild(NodeAVL<T>* node)
{
    NodeAVL<T>* parent_of_node = node->GetParent();
      
    // 해당 노드를 삭제함
    if (parent_of_node != nullptr)
    {
        if (parent_of_node->GetLeft() == node)
        {
            parent_of_node->SetLeft(nullptr);
        }
        else
        {
            parent_of_node->SetRight(nullptr);
        }
    }
    else
    {
        // 현재 Set에 원소가 없음
        root_ = nullptr;
    }

    // 삭제하려고 하는 노드에 대한 메모리 해제
    delete node;

    // parent_of_erase_node부터 루트 노드까지 height 갱신
    UpdateHeightUntilRoot(parent_of_node);

    // parent_of_node부터 root node까지 모든 node의 size 갱신
    UpdateSizeUntilRoot(parent_of_node);

    // 필요에 따라 Restructuring 진행
    RestructuringForErase(parent_of_node);
}

// node를 삭제 (node의 자식이 1개만 있는 경우)
template <typename T>
void SetAVL<T>::EraseNodeThatHasOnlyOneChild(NodeAVL<T>* node)
{
    NodeAVL<T>* parent_of_node = node->GetParent();

    if (node->GetLeft() != nullptr)
    {
        NodeAVL<T>* child_of_node = node->GetLeft();
        
        if (parent_of_node == nullptr)
        {
            // 삭제하려고 하는 노드는 루트 노드
            // AVL Tree이므로 이러한 경우는 노드의 개수가 2개인 경우 밖에 존재하지 않음
            // 루트 노드는 삭제하려고 하는 노드의 left child가 됨
            root_ = child_of_node;
        }
        else
        {
            if (parent_of_node->GetKey() > child_of_node->GetKey())
            {
                parent_of_node->SetLeft(child_of_node);
            }
            else
            {
                parent_of_node->SetRight(child_of_node);
            } 
        }

        child_of_node->SetParent(parent_of_node);
    }
    else
    {
        NodeAVL<T>* child_of_node = node->GetRight();
        
        if (parent_of_node == nullptr)
        {
            // 삭제하려고 하는 노드는 루트 노드
            // AVL Tree이므로 이러한 경우는 노드의 개수가 2개인 경우 밖에 존재하지 않음
            // 루트 노드는 삭제하려고 하는 노드의 right child가 됨
            root_ = child_of_node;
        }
        else
        {
            if (parent_of_node->GetKey() > child_of_node->GetKey())
            {
                parent_of_node->SetLeft(child_of_node);
            }
            else
            {
                parent_of_node->SetRight(child_of_node);
            } 
        }

        child_of_node->SetParent(parent_of_node);
    }

    // parent_of_erase_node부터 루트 노드까지 height 갱신
    UpdateHeightUntilRoot(parent_of_node);

    // parent_of_node부터 root node까지 모든 node의 size 갱신
    UpdateSizeUntilRoot(parent_of_node);

    // 필요에 따라 Restructuring 진행
    RestructuringForErase(parent_of_node);

    delete node;
}

// node를 삭제 (node의 자식이 2개 있는 경우)
template <typename T>
void SetAVL<T>::EraseNodeThatHasTwoChildren(NodeAVL<T>* node)
{
    NodeAVL<T>* successor = FindSuccessor(node);

    // successor의 부모 노드 저장
    NodeAVL<T>* parent_of_successor = successor->GetParent();

    // node에 있는 key 값을 successor에 있는 key값으로 대체
    node->SetKey(successor->GetKey());

    // successor를 삭제
    // successor의 parent 노드가 없는 경우는 존재하지 않음
    // successor의 parent 노드와 successor의 right child를 연결함
    if (parent_of_successor->GetLeft() == successor)
    {
        parent_of_successor->SetLeft(successor->GetRight());
    }
    else
    {
        parent_of_successor->SetRight(successor->GetRight());
    }

    if (successor->GetRight() != nullptr)
    {
        successor->GetRight()->SetParent(parent_of_successor);
    }
    
    delete successor;

    // parent_of_successor부터 루트 노드까지 height 갱신
    UpdateHeightUntilRoot(parent_of_successor);

    // parent_of_successor부터 root node까지 모든 node의 size 갱신
    UpdateSizeUntilRoot(parent_of_successor);

    // 필요에 따라 Restructuring을 진행
    RestructuringForErase(parent_of_successor);
}

// node의 successor를 찾음
template <typename T>
NodeAVL<T>* SetAVL<T>::FindSuccessor(NodeAVL<T>* node)
{
    if (node->GetRight() == nullptr)
    {
        // node의 right child가 없을 경우 successor는 존재하지 않음
        return nullptr;
    }
    else
    {
        NodeAVL<T>* successor = node->GetRight();

        // node의 right subtree에 있는 노드 중 key 값이 최소인 노드를 찾아서 return함
        while (successor->GetLeft() != nullptr)
        {
            successor = successor->GetLeft();
        }

        return successor;
    }
}

// Erase 기능을 수행할 때 필요에 따라 Restructuring을 진행함
template <typename T>
void SetAVL<T>::RestructuringForErase(NodeAVL<T>* node)
{
    // root node까지 balance factor를 계산함
    // balance factor의 절댓값이 2 이상인 경우 Restructuring을 진행

    NodeAVL<T>* grand_parent_node = node;

    while (1)
    {
        if (grand_parent_node == nullptr)
        {
            break;
        }
        else
        {
            int balance_factor_of_grand_parent_node = GetBalanceFactor(grand_parent_node);

            if (std::abs(balance_factor_of_grand_parent_node) >= 2)
            {
                // Restructuring 필요
                NodeAVL<T>* parent_node = nullptr;
                NodeAVL<T>* child_node = nullptr;

                if (balance_factor_of_grand_parent_node >= 2)
                {
                    // grand_parent_node의 left subtree의 height가 더 높음
                    parent_node = grand_parent_node->GetLeft();

                    int balance_factor_of_parent_node = GetBalanceFactor(parent_node);

                    if (balance_factor_of_parent_node >= 0)
                    {
                        // parent_node의 left subtree의 height가 더 높음
                        child_node = parent_node->GetLeft();

                        // Restructuring 진행
                        RestructuringForLeftLeftCase(
                            child_node, parent_node, grand_parent_node);

                        // grand_parent_node 재설정
                        grand_parent_node = parent_node->GetParent();
                    }
                    else
                    {
                        // parent_node의 right subtree의 height가 더 높음
                        child_node = parent_node->GetRight();

                        // Restructuring 진행
                        RestructuringForLeftRightCase(
                            child_node, parent_node, grand_parent_node);

                        // grand_parent_node 재설정
                        grand_parent_node = child_node->GetParent();
                    }
                }
                else
                {
                    // grand_parent_node의 right subtree의 height가 더 높음
                    parent_node = grand_parent_node->GetRight();

                    int balance_factor_of_parent_node = GetBalanceFactor(parent_node);

                    if (balance_factor_of_parent_node > 0)
                    {
                        // parent_node의 left subtree의 height가 더 높음
                        child_node = parent_node->GetLeft();

                        // Restructuring 진행
                        RestructuringForRightLeftCase(
                            child_node, parent_node, grand_parent_node);

                        // grand_parent_node 재설정
                        grand_parent_node = child_node->GetParent();
                    }
                    else
                    {
                        // parent_node의 right subtree의 height가 더 높음
                        child_node = parent_node->GetRight();

                        // Restructuring 진행
                        RestructuringForRightRightCase(
                            child_node, parent_node, grand_parent_node);

                        // grand_parent_node 재설정
                        grand_parent_node = parent_node->GetParent();
                    }
                }
            }
            else
            {
                grand_parent_node = grand_parent_node->GetParent();
            }
        }
    }
}
