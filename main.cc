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

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;

    for (int i = 0; i < T; i++)
    {
        int Q;
        std::cin >> Q;

        SetAVL<int> set;

        for (int j = 0; j < Q; j++)
        {
            std::string cmd;
            std::cin >> cmd;

            if (cmd == "minimum")
            {
                int x;
                std::cin >> x;

                set.Minimum(x);
            }
            else if (cmd == "maximum")
            {
                int x;
                std::cin >> x;

                set.Maximum(x);
            }
            else if (cmd == "empty")
            {
                if (set.IsEmpty())
                {
                    std::cout << "1\n";
                }
                else
                {
                    std::cout << "0\n";
                }
            }
            else if (cmd == "size")
            {
                std::cout << set.GetSize() << "\n";
            }
            else if (cmd == "find")
            {
                int x;
                std::cin >> x;

                int depth = set.Find(x);

                if (depth == -1)
                {
                    std::cout << "0\n";
                }
                else
                {
                    std::cout << depth << "\n";
                }
            }
            else if (cmd == "insert")
            {
                int x;
                std::cin >> x;

                std::cout << set.Insert(x) << "\n";
            }
            else if (cmd == "erase")
            {
                int x;
                std::cin >> x;

                std::cout << set.Erase(x) << "\n";
            }
            else if (cmd == "rank")
            {
                int x;
                std::cin >> x;

                set.Rank(x);
            }
        }
    }
    
    return 0;
}
