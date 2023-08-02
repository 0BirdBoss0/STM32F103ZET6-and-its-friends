#ifndef __COMBO_H
#define __COMBO_H

// 创建一个字典，多个数组（key）可以对应多个LED (value)。

// 把按键输入录入数组，切换模式按键除外。一块按键划分为单控区，一块划分为学习区？
void Combo_RecordInputArray(void);


// 检测当前按键输入是否与存在于当前字典。
// 如果有则return 1， 没有return 0；
void Combo_CheckArray(int array[3]); 


void Combo_PutIntoDict(int array[3]); 



// 在操作模式下：
单控按键可以直接操控设备，比如说最上面两排按键可以操控对应的LED，
多对一按键则可以设置对应关系，操作模式和设置模式的切换由单控按键之一控制。
在设置对应关系后，多个按键遵循顺序按下可以触发对应功能，如反转某LED



// 在设置模式下：
// 按下单控按键选择需要调整控制的方式的功能，或者说选择要编辑的value。

然后系统调用Combo_RecordInputArray()函数，开始记录，
至少一个，至多三个元素，合并成一个数组












// 方案2

把KeyNum改成二维数组，最后return这个二维数组出去，这样也许就可以实现同时按下按键


#endif // __COM