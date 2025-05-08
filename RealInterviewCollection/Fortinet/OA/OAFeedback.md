### ✅ 中文面试回答（详细版本）：

> 这次 OA 一共是四道题，整体偏算法基础，难度中等偏下，但因为必须用 C 语言编写，对我来说增加了一些挑战。
>
> 我平时更熟悉用 C++ 写算法，习惯了 STL，比如 vector、map、new/delete 等语法糖。但这次只能用纯 C，没有模板库，也要手动申请和释放内存，包括链表和二叉树的节点管理、数组分配等等，所以我在写代码时花了不少精力处理指针和 malloc/free 的细节，特别是调试边界情况。
>
> 四道题中：
>
> * 第一题是单链表中删除指定值节点，逻辑比较直接，我用双指针处理前驱节点和目标节点，很快写完；
> * 第二题是飞机入侵问题，考察贪心策略，我计算每架飞机降落所需时间后排序，然后一秒打一个，直到有飞机先落地为止，时间控制和排序逻辑都比较清晰；
> * 第三题是统计整数中 1 的个数，并输出每个 1 在从左到右的位置信息，这题细节比较多，要先计算出有效二进制位，然后高位到低位遍历判断 `1` 的位置，我也通过位运算处理，节省时间；
> * 第四题是构造 BST 并统计 `insert` 函数的递归调用次数，这题我一开始思路是没问题的，但因为需要通过全局变量来记录递归次数，且每一步都要保证内存正确释放、节点插入逻辑无误，在调试上花了些时间。最终我在接近时间结束前完成了 AC，也说明我在不熟悉语言的环境下能保持逻辑清晰、快速调整方案。
>
> 整体来说，我觉得这次题目不算特别难，更像是基础算法功底和语言适应能力的综合测试，我最终按时 AC 掉所有题，感觉挺有收获。

---

### ✅ English Version (detailed and thoughtful):

> The OA consisted of four algorithm questions, mostly focusing on basic data structures and implementation logic. I'd say the overall difficulty was moderate. However, the challenge for me was that the entire test had to be completed in C, while I’m more used to working with C++.
>
> In C++, I often rely on STL containers like `vector`, `map`, and the convenience of `new/delete`. With C, I had to manually manage memory using `malloc` and `free`, which added some mental load — especially when dealing with linked list deletion and binary search tree construction.
>
> Here's how I approached the problems:
>
> * The first problem involved deleting a node from a singly linked list. I used a two-pointer approach to track the previous and current node. This one was relatively straightforward;
> * The second problem was a greedy-style air-invaders simulation. I computed the landing time for each plane, sorted them, and simulated shooting one per second until one would land — fairly direct once I had the idea;
> * The third problem involved counting the number of `1`s in the binary representation of an integer and returning their positions (from left to right). This required calculating the number of significant bits and then checking each bit using bitwise operations. The logic wasn’t difficult, but had to be implemented carefully;
> * The fourth problem was the most time-consuming for me. It required building a binary search tree and counting how many times the recursive `insert()` function was called. I understood the idea quickly, but implementing it in C — dealing with raw pointers, memory allocation, and the global counter — took more time and debugging. I got stuck for a bit, but managed to get it working and pass all test cases near the end of the allotted time.
>
> In conclusion, although the problems weren’t particularly hard algorithmically, they were a good test of implementation skills, attention to detail, and adapting to a lower-level language. I was glad that I could complete all four problems under time pressure, even outside my usual language comfort zone.
>
