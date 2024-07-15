/**************************************************
 * Copyright INHA_OSAP_004_Froyo
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * Contributors: Lee Seung-Bin, Choi Yi-Joon, Majunliang, Lee Jin-Woo
 * Latest Updated on 2023-12-07
**************************************************/

#include "set_avl.h"

#include <iostream>

// key를 root로 하는 subtree에서 최솟값을 갖는 node의 값과 depth를 출력
void SetAVL::Minimum(const int key)
{
    NodeAVL* node = root_;
    // key를 root로 하는 node찾기
    while(node != nullptr)
    {
        if(key == node->GetNum())
            break;
        else if(key < node->GetNum())
            node = node->GetLeft();
        else
            node = node->GetRight();
    }

     // Set에 존재하지 않는 원소에 대한 처리
    if(node == nullptr)
    {
        std::cout << "-1, -1" << std::endl;
        return;
    }
    
    // subtree에서 최솟값을 갖는 node찾기
    while(node != nullptr && node->GetLeft() != nullptr)
    {
        node = node->GetLeft();
    }
    std::cout << node->GetNum() << " " << Find(node->GetNum());
}

// key를 root로 하는 subtree에서 최댓값을 갖는 node의 값과 depth를 출력
void SetAVL::Maximum(const int key)
{
    NodeAVL* node = root_;
    // key를 root로 하는 node찾기
    while(node != nullptr)
    {
        if(key == node->GetNum())
            break;
        else if(key < node->GetNum())
            node = node->GetLeft();
        else
            node = node->GetRight();
    }

    // Set에 존재하지 않는 원소에 대한 처리
    if(node == nullptr)
    {
        std::cout << "-1, -1" << std::endl;
        return;
    }
    
    // subtree에서 최댓값을 갖는 node찾기
    while(node != nullptr && node->GetRight() != nullptr)
    {
        node = node->GetRight();
    }
    std::cout << node->GetNum() << " " << Find(node->GetNum());
}

// 해당 key를 가지고 있는 node의 depth를 return
int SetAVL::Find(const int key)
{
    int depth = findDepth(root_, key, 0);
    return depth;
}

int SetAVL::findDepth(NodeAVL *node, int key, int depth)
{
    if (node == nullptr)
    {
        return 0;
    }

    if (key == node->GetNum())
    {
        return depth;
    }
    else if (key < node->GetNum())
    {
        return findDepth(node->GetLeft(), key, depth + 1);
    }
    else
    {
        return findDepth(node->GetRight(), key, depth + 1);
    }
}

// num을 삽입하고 해당 node의 depth를 출력
int SetAVL::Insert(const int num)
{
    if (root_ == nullptr)
    {
        // Set에 아무런 원소도 없는 경우
        root_ = new NodeAVL(num);

        // 새로 삽입한 node의 height는 0
        root_->SetHeight(0);
        size_ = 1;

        // 새로 삽입한 node의 depth 출력
        // root node의 depth는 0으로 정의
        return 0;
    }
    else
    {
        NodeAVL* current_node = root_;
        NodeAVL* new_node = new NodeAVL(num);

        // 적절한 위치에 Node 삽입하기
        while (1)
        {
            if (num == current_node->GetNum())
            {
                // 삽입하려고 하는 원소가 이미 Set에 들어있음
                // new_node 메모리 해제
                delete new_node;
                return -1;
            }
            else if (num < current_node->GetNum())
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
                    return getDepth(new_node);
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
                    return getDepth(new_node);
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
void SetAVL::Rank(const int num)
{
    NodeAVL* root_node = root_;
    int key = num;
    int rank = 1;

    RankTraversal(root_node, key, rank);
    
    int depth = Find(num);

    if (depth == -1)
        std::cout << "0\n";
    else
        std::cout << depth << " " << rank;
}

// AVL 트리 전위 순회
void SetAVL::RankTraversal(NodeAVL* current_node, const int key, int& rank)
{
    if (current_node == nullptr)
        return;
    if (current_node->GetNum() < key)
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
int SetAVL::Erase(const int num)
{
    // 삭제하려고 하는 노드
    NodeAVL* erase_node = root_;

    // 삭제하려고 하는 노드를 검색
    while (1)
    {
        if (num == erase_node->GetNum())
        {
            // 삭제하려고 하는 node를 찾음
            break;
        }
        else if (num < erase_node->GetNum())
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
    int erase_node_depth = getDepth(erase_node);

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

// 해당 node의 height를 재설정`
void SetAVL::UpdateHeight(NodeAVL* node)
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
void SetAVL::UpdateHeightUntilRoot(NodeAVL* start_node)
{
    NodeAVL* current_node = start_node;
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

// 해당 node의 (left subtree의 height) - (right subtree의 height)의 값을 return
int SetAVL::GetBalanceFactor(NodeAVL* node)
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
int SetAVL::getDepth(NodeAVL* node)
{
    // root node의 depth를 0으로 정의
    int depth = 0;
    NodeAVL* current_node = node;

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
void SetAVL::Restructuring(NodeAVL* new_node)
{
    NodeAVL* current_node = new_node;
    NodeAVL* parent_node = new_node->GetParent();
    NodeAVL* grand_parent_node = parent_node->GetParent();

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
void SetAVL::RestructuringForLeftLeftCase(
    NodeAVL* current_node, 
    NodeAVL* parent_node,
    NodeAVL* grand_parent_node)
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

    NodeAVL* subtree_t3_root = parent_node->GetRight();

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

    // grand_parent_node부터 root까지 height 재설정
    UpdateHeightUntilRoot(grand_parent_node);
}

// Left Right Case에 대하여 restructuring 진행
void SetAVL::RestructuringForLeftRightCase(
    NodeAVL* current_node,
    NodeAVL* parent_node,
    NodeAVL* grand_parent_node)
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

    NodeAVL* subtree_t2_root = current_node->GetLeft();
    NodeAVL* subtree_t3_root = current_node->GetRight();

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
}

// Right Left Case에 대하여 restructuring 진행
void SetAVL::RestructuringForRightLeftCase(
    NodeAVL* current_node,
    NodeAVL* parent_node,
    NodeAVL* grand_parent_node)
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

    NodeAVL* subtree_t2_root = current_node->GetLeft();
    NodeAVL* subtree_t3_root = current_node->GetRight();

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
}

// Right Right Case에 대하여 restructuring 진행
void SetAVL::RestructuringForRightRightCase(
    NodeAVL* current_node,
    NodeAVL* parent_node,
    NodeAVL* grand_parent_node)
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

    NodeAVL* subtree_t2_root = parent_node->GetLeft();

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
}

// node를 삭제 (node의 자식이 없는 경우)
void SetAVL::EraseNodeThatHasNoChild(NodeAVL* node)
{
    delete node;
}

// node를 삭제 (node의 자식이 1개만 있는 경우)
void SetAVL::EraseNodeThatHasOnlyOneChild(NodeAVL* node)
{
    if (node->GetLeft() != nullptr)
    {
        NodeAVL* child_of_node = node->GetLeft();
        NodeAVL* parent_of_node = node->GetParent();
        if (parent_of_node == nullptr)
            _root = child_of_node;
        else
        {
            if (parent_of_node->GetNum() > child_of_node->GetNum())
            {
                parent_of_node->SetLeft(child_of_node);
                child_of_node->SetParent(parent_of_node);
            }
            else
            {
                parent_of_node->SetRight(child_of_node);
                child_of_node->SetParent(parent_of_node);
            } 
        }
        delete node;
        UpdateHeightUntilRoot(parent_of_node);
        RestructuringForErase(parent_of_node);
    }
    else
    {
        NodeAVL* child_of_node = node->GetRight();
        NodeAVL* parent_of_node = node->GetParent();
        if (parent_of_node == nullptr)
            _root = child_of_node;
        else
        {
            if (parent_of_node->GetNum() > child_of_node->GetNum())
            {
            parent_of_node->SetLeft(child_of_node);
            child_of_node->SetParent(parent_of_node);
            }
            else
            {
                parent_of_node->SetRight(child_of_node);
                child_of_node->SetParent(parent_of_node);
            } 
        }
            
        delete node;
        UpdateHeightUntilRoot(parent_of_node);
        RestructuringForErase(child_of_node->GetParent());
    }
}

// node를 삭제 (node의 자식이 2개 있는 경우)
void SetAVL::EraseNodeThatHasTwoChildren(NodeAVL* node)
{
    NodeAVL* successor = FindSuccessor(node);

    // successor의 부모 노드 저장
    NodeAVL* parent_of_successor = successor->GetParent();

    // node에 있는 key 값을 successor에 있는 key값으로 대체
    node->SetNum(successor->GetNum());

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

    // 필요에 따라 Restructuring을 진행
    RestructuringForErase(parent_of_successor);
}

// node의 successor를 찾음
NodeAVL* SetAVL::FindSuccessor(NodeAVL* node)
{
    if (node->GetRight() == nullptr)
    {
        // node의 right child가 없을 경우 successor는 존재하지 않음
        return nullptr;
    }
    else
    {
        NodeAVL* successor = node->GetRight();

        // node의 right subtree에 있는 노드 중 key 값이 최소인 노드를 찾아서 return함
        while (successor->GetLeft() != nullptr)
        {
            successor = successor->GetLeft();
        }

        return successor;
    }
}

// Erase 기능을 수행할 때 필요에 따라 Restructuring을 진행함
void SetAVL::RestructuringForErase(NodeAVL* node)
{
    // root node까지 balance factor를 계산함
    // balance factor의 절댓값이 2 이상인 경우 Restructuring을 진행

    NodeAVL* grand_parent_node = node;

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
                NodeAVL* parent_node = nullptr;
                NodeAVL* child_node = nullptr;

                if (balance_factor_of_grand_parent_node >= 2)
                {
                    // grand_parent_node의 left subtree의 height가 더 높음
                    parent_node = grand_parent_node->GetLeft();
                }
                else
                {
                    // grand_parent_node의 right subtree의 height가 더 높음
                    parent_node = grand_parent_node->GetRight();
                }

                int balance_factor_of_parent_node = GetBalanceFactor(parent_node);

                if (balance_factor_of_parent_node > 0)
                {
                    // parent_node의 left subtree의 height가 더 높음
                    child_node = parent_node->GetLeft();

                    if (grand_parent_node->GetLeft() == parent_node)
                    {
                        // Restructuring 진행
                        RestructuringForLeftLeftCase(
                            child_node, parent_node, grand_parent_node);

                        // grand_parent_node 재설정
                        grand_parent_node = parent_node->GetParent();
                    }
                    else
                    {
                        // Restructuring 진행
                        RestructuringForRightLeftCase(
                            child_node, parent_node, grand_parent_node);

                        // grand_parent_node 재설정
                        grand_parent_node = child_node->GetParent();
                    }
                }
                else if (balance_factor_of_parent_node < 0)
                {
                    // parent_node의 right subtree의 height가 더 높음
                    child_node = parent_node->GetRight();

                    if (grand_parent_node->GetLeft() == parent_node)
                    {
                        // Restructuring 진행
                        RestructuringForLeftRightCase(
                            child_node, parent_node, grand_parent_node);

                        // grand_parent_node 재설정
                        grand_parent_node = child_node->GetParent();
                    }
                    else
                    {
                        // Restructuring 진행
                        RestructuringForRightRightCase(
                            child_node, parent_node, grand_parent_node);

                        // grand_parent_node 재설정
                        grand_parent_node = parent_node->GetParent();
                    }
                }
                else
                {
                    // parent_node의 left subtree와 right subtree의 높이가 같음
                    // 연산의 수가 더 적은 single rotation을 이용하여 수행할 수 있도록 child_node를 선택함
                    if (grand_parent_node->GetLeft() == parent_node)
                    {
                        child_node = parent_node->GetLeft();

                        // Restructuring 진행
                        RestructuringForLeftLeftCase(
                            child_node, parent_node, grand_parent_node);

                        // grand_parent_node 재설정
                        grand_parent_node = parent_node->GetParent();
                    }
                    else
                    {
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
