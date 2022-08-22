#include <stdio.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define MAKE struct s_Data
#define ERROR_PRINT_MLL printf("[ERROR]TRY TO MAKE THE LINKED LIST ERROR\n")				//创建失败用
#define ERROR_PRINT_TL printf("[ERROR]THE SEARCH NUMBER OF THE BLOCKS IS TOO LOOG\n")		//输入块长度太长用

struct s_Data {
	uchar str_Datas[128];	//保存的数据
	MAKE *p_NextBlock;		//下一个块的头地址
};

class c_LinkedList {
public:

	/*
	功能：创建一个链表，错误时抛出异常，并且打印
	参数：
	1）n_Temp_Blocks		用于确定创建个数
	注意：
	1）当异常为整型（int）且值为1时表示创建失败，创建的链表会删除
	*/
	c_LinkedList(uint n_Temp_Blocks);

	/*
	功能：在现有链表中的一个块后面增加一个块，错误时抛出异常，并且打印
	注意：
	1）当异常为整形（int）且值为1时表示增加失败，不会创建块
	2）创建成功，返回新增加的块的地址，
	3）创建失败，返回NULL
	返回：
	1）返回NULL，表示添加块失败
	2）返回增加的块的头地址，表示添加块成功
	3）返回链表头地址，表示输入参数大于了链表长度
	*/
	MAKE *f_AddBlock(uint n_Location_Block);

	/*
	功能：在现有链表中的一个块的下一个块删除，错误时会抛出异常，并且打印
	注意：
	1）当异常为整型（int）且值为1时表示删除失败
	返回：
	1）返回NULL（防止野指针和释放后重用），表示删除成功
	2）返回链表头地址，表示输入太长
	*/
	MAKE *f_DelBlock(uint n_Location_Block);

	/*
	功能（默认）：打印链表中一个块的内容，可以自定义你想要的功能
	*/
	virtual uint vf_UseForYourSelf(uint n_Location_Block);
private:
	uint n_Blocks;				//创建链表的个数
	MAKE *p_FirstBlock;			//链表的头地址
	MAKE *p_Temp_Head;			//在对块进行操作时，一般用于指向块的头地址的指针
	MAKE *p_Temp_NextBlock;		//在对块进行操作时，一般用于指向下一个块的头地址的指针
	MAKE *p_Temp_All;			//在对块进行操作时，一般用于临时使用的指针（一般用于增加或者删除块）
};

c_LinkedList::c_LinkedList(uint n_Temp_Blocks) {
	//将传入的数据保存
	n_Blocks = n_Temp_Blocks;

	//创建第一个块
	p_FirstBlock = new MAKE;
	if (NULL == p_FirstBlock) {
		//初始化失败
		//抛出异常
		throw(1);
		//打印错误
		ERROR_PRINT_MLL;

		//数据复原，防止野指针或者释放后重用漏洞
		n_Blocks = 0;
		p_FirstBlock = NULL;
		p_Temp_Head = NULL;
		p_Temp_NextBlock = NULL;
		return;
	}

	//开始创建链表
	//数据准备
	uint n_Loops = 0;		//用于循环的数
	uint n_SaveLoops = 0;	//用于记录循环的数
	p_Temp_Head = p_FirstBlock;

	//开始构建
	for (n_Loops; n_Loops < n_Blocks; n_Loops++, n_SaveLoops++) {
		p_Temp_NextBlock = new MAKE;
		if (NULL == p_Temp_NextBlock) {
			//创建失败
			//抛出异常
			throw(1);
			ERROR_PRINT_MLL;

			//删除已经创建的块

			//将Head指针指向头
			p_Temp_Head = p_FirstBlock;
			//将循环数归零
			n_Loops = 0;
			for (n_Loops; n_Loops < n_SaveLoops; n_Loops++) {
				p_Temp_NextBlock = p_Temp_Head->p_NextBlock;
				delete p_Temp_Head;
				p_Temp_Head = p_Temp_NextBlock;
			}

			//数据复原，防止野指针或者释放后重用漏洞
			n_Blocks = 0;
			p_FirstBlock = NULL;
			p_Temp_Head = NULL;
			p_Temp_NextBlock = NULL;

			//删除完毕
			return;
		}
		p_Temp_Head->p_NextBlock = p_Temp_NextBlock;
		p_Temp_Head = p_Temp_NextBlock;
	}

	//创建完毕
	p_Temp_Head = NULL;
	p_Temp_NextBlock = NULL;

	printf("[OK]COMPELTELY MAKE THE LINKED LIST\n");
	return;
}

MAKE *c_LinkedList::f_AddBlock(uint n_Location_Block) {
	if (n_Location_Block > n_Blocks) {
		//输入太长了
		ERROR_PRINT_TL;
		return p_FirstBlock;
	}

	//数据初始化
	uint n_Loops = 0;
	p_Temp_Head = p_FirstBlock;

	//寻找到块的位置
	for (n_Loops; n_Loops < n_Location_Block; n_Loops++) {
		p_Temp_NextBlock = p_Temp_Head->p_NextBlock;
		p_Temp_Head = p_Temp_NextBlock;
	}

	//开始增加一个块
	//缓存原本第二个块的头地址
	p_Temp_All = p_Temp_Head->p_NextBlock;

	//将第二指针指向新的块
	p_Temp_NextBlock = new MAKE;
	if (NULL == p_Temp_NextBlock) {
		throw(1);

		ERROR_PRINT_MLL;
		return NULL;
	}

	//将原第一个块的指向地址改为新的地址
	p_Temp_Head->p_NextBlock = p_Temp_NextBlock;
	
	//将新的块的指向地址改为缓存的原块地址
	p_Temp_NextBlock->p_NextBlock = p_Temp_All;

	//将指针复原
	p_Temp_All = NULL;
	p_Temp_Head = NULL;
	p_Temp_NextBlock = NULL;

	return p_Temp_NextBlock;
}

MAKE *c_LinkedList::f_DelBlock(uint n_Location_Block) {
	if (n_Location_Block >= n_Blocks) {
		//输入太长了
		ERROR_PRINT_TL;
		return p_FirstBlock;
	}

	//循环用
	uint n_Loops = 0;
	p_Temp_Head = p_FirstBlock;

	//寻找到块的位置
	for (n_Loops; n_Loops < n_Location_Block; n_Loops++) {
		p_Temp_NextBlock = p_Temp_Head->p_NextBlock;
		p_Temp_Head = p_Temp_NextBlock;
	}

	//第二指针指向被删除的块
	p_Temp_NextBlock = p_Temp_Head->p_NextBlock;
	
	//第三指针指向被删块后的块
	p_Temp_All = p_Temp_NextBlock->p_NextBlock;

	//删除块
	delete p_Temp_NextBlock;

	//将链表链接
	p_Temp_Head->p_NextBlock = p_Temp_All;

	return NULL;
}

 uint c_LinkedList::vf_UseForYourSelf(uint n_Location_Block) {
	 uint n_Loops = 0;
	 //寻找到块的位置
	 p_Temp_Head = p_FirstBlock;
	 for (n_Loops; n_Loops < n_Location_Block; n_Loops++) {
		 p_Temp_NextBlock = p_Temp_Head->p_NextBlock;
		 p_Temp_Head = p_Temp_NextBlock;
	 }

	 n_Loops = 0;
	 for (n_Loops; n_Loops < 64; n_Loops++) {
		 printf("%x ", (uchar*)p_Temp_Head->str_Datas[n_Loops]);
	 }

	 return 1;
}

int main(void) {
	//调试代码
	c_LinkedList *Test = new c_LinkedList(10);
	Test->f_AddBlock(2);
	Test->f_DelBlock(30);

	Test->vf_UseForYourSelf(2);
	return 0;
}