This repository is my solutions for leetcode.

## Build & Run
The project use cmake to build. For example, the first question in leetcode is "two sum", and the source file in this repository is 1_two_sum.cpp and the make target in CMakeLists.txt is 1_two_sum. To build it, I recommend you to make a build directory to save indirect files and executable files.

```
mkdir build
cd build
cmake ..
make 1_two_sum
./1_two_sum
```

So do other solutions. If you want to build all solutions, just run

```
make
```

or

```
make -j 4
```

to build with 4 threads.

All solutions is written under iso c++11 standard, and it can be compiled correctly in any compiler supporting c++11, for example, gcc>=4.8, and clang>=3.3.

## Develop in IDE

Many IDE support projects management with cmake, such as visual studio and CLion. CLion's support for c++ and cmake is obviously greater than other c++ IDE including visual studio. So I will show you how to use CLion to develop this project.

Download this project, and open the folder with CLion. If there is no "Open this folder with CLion", just start CLion and click "Open or Import", then select the directory where you save the project. After clicking "Ok", the project is open in CLion. In general, CLion will generate Makefile in cmake-build-debug automatically, and you can find all build target after clicking "Select Run/Debug Configuration" in toolbar, as is shown as the following figure.

![targets](https://github.com/w-jin/leetcode/blob/master/images/targets.png)

Select a target and run, CLion will build and run it. If you want to add a new c++ source file, just add it and reload cmake cache, as is shown as the following figure.

![new_file](https://github.com/w-jin/leetcode/blob/master/images/new_file.png)

## Headers

In some questions, we must define linked list and binary tree to run Solution codes, for example, question 2 "Add Two Numbers" use linked list to save any length of numbers, and question 99 "Recover Binary Search Tree" need you to operate a binary tree. Linked list and binary tree are implemented in header files "include/list.hpp" and "include/tree.hpp", respectively. There is ne need to link any libraries or compile with other source files when use the two header file. Just include it and use classes and functions defined in them.

There is an insteresting function in "include/tree.hpp" -- print a binary tree. The function "PrintBinaryTree" will print a tree as natural as possible. For example, a binary tree is shown as the following figure.

![binarytree](https://github.com/w-jin/leetcode/blob/master/images/binarytree.png)

Use these codes to create, display and destory it:

```cpp
TreeNode *root = CreateTree({1, 2, 3, 0, 4, 5, 6, 0, 7});
PrintBinaryTree(root);
DestoryTree(root);
```

the "PrintBinaryTree" will print:

![printbinarytree](https://github.com/w-jin/leetcode/blob/master/images/printbinarytree.png)

The function will help debug the solution related to binary tree.

## Future

I have completed just few solutions for leetcode questions. All my solutions have been updating to this repository. I will keep updating as frequently as possible untill there is no new question in leetcode.
