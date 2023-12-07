// 라이선스

#include "set_avl.h"

#include <iostream>

// key를 root로 하는 subtree에서 최솟값을 갖는 node의 값과 depth를 출력
void SetAVL::Minimum(const int key)
{

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
    // subtree에서 최댓값을 갖는 node찾기
    while(node != nullptr && node->GetRight() != nullptr)
    {
        node = node->GetRight();
    }
    std::cout << "key : " << node->GetNum() << ", depth : " << Find(key);
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

// 해당 node의 height를 재설정
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