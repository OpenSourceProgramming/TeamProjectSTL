// 라이선스

#include "set_avl.h"

#include <iostream>

// key를 root로 하는 subtree에서 최솟값을 갖는 node의 값과 depth를 출력
void SetAVL::Minimum(const int key)
{
    NodeAVL* n = root_;
    while(n != nullptr)
        {
            if(key == n->GetNum())
                break;
            else if(key < n->GetNum())
                n = n->GetLeft();
            else
                n = n->GetRight()
        }
    while(n && n->GetLeft() !== null)
        {
            n = n->GetLeft();
        }
    printf("key : %d, depth : %d", n->GetNum(), SetAVL::Find(key));
}

// key를 root로 하는 subtree에서 최댓값을 갖는 node의 값과 depth를 출력
void SetAVL::Maximum(const int key)
{

}

// 해당 key를 가지고 있는 node의 depth를 return
int SetAVL::Find(const int key)
{
    return 0;
}

// num을 삽입하고 해당 node의 depth를 출력
void SetAVL::Insert(const int num)
{
    
}
