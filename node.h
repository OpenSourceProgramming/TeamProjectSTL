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

#ifndef NODE_H
#define NODE_H

// Node의 경우 Abstract Class로 정의 (pure virtual function 이용)
class Node
{
public:
    virtual ~Node() {}
    virtual int GetNum() const = 0;
};

#endif