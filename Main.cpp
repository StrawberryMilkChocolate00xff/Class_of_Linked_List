#include <stdio.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define MAKE struct s_Data
#define ERROR_PRINT_MLL printf("[ERROR]TRY TO MAKE THE LINKED LIST ERROR\n")				//����ʧ����
#define ERROR_PRINT_TL printf("[ERROR]THE SEARCH NUMBER OF THE BLOCKS IS TOO LOOG\n")		//����鳤��̫����

struct s_Data {
	uchar str_Datas[128];	//���������
	MAKE *p_NextBlock;		//��һ�����ͷ��ַ
};

class c_LinkedList {
public:

	/*
	���ܣ�����һ����������ʱ�׳��쳣�����Ҵ�ӡ
	������
	1��n_Temp_Blocks		����ȷ����������
	ע�⣺
	1�����쳣Ϊ���ͣ�int����ֵΪ1ʱ��ʾ����ʧ�ܣ������������ɾ��
	*/
	c_LinkedList(uint n_Temp_Blocks);

	/*
	���ܣ������������е�һ�����������һ���飬����ʱ�׳��쳣�����Ҵ�ӡ
	ע�⣺
	1�����쳣Ϊ���Σ�int����ֵΪ1ʱ��ʾ����ʧ�ܣ����ᴴ����
	2�������ɹ������������ӵĿ�ĵ�ַ��
	3������ʧ�ܣ�����NULL
	���أ�
	1������NULL����ʾ��ӿ�ʧ��
	2���������ӵĿ��ͷ��ַ����ʾ��ӿ�ɹ�
	3����������ͷ��ַ����ʾ�������������������
	*/
	MAKE *f_AddBlock(uint n_Location_Block);

	/*
	���ܣ������������е�һ�������һ����ɾ��������ʱ���׳��쳣�����Ҵ�ӡ
	ע�⣺
	1�����쳣Ϊ���ͣ�int����ֵΪ1ʱ��ʾɾ��ʧ��
	���أ�
	1������NULL����ֹҰָ����ͷź����ã�����ʾɾ���ɹ�
	2����������ͷ��ַ����ʾ����̫��
	*/
	MAKE *f_DelBlock(uint n_Location_Block);

	/*
	���ܣ�Ĭ�ϣ�����ӡ������һ��������ݣ������Զ�������Ҫ�Ĺ���
	*/
	virtual uint vf_UseForYourSelf(uint n_Location_Block);
private:
	uint n_Blocks;				//��������ĸ���
	MAKE *p_FirstBlock;			//�����ͷ��ַ
	MAKE *p_Temp_Head;			//�ڶԿ���в���ʱ��һ������ָ����ͷ��ַ��ָ��
	MAKE *p_Temp_NextBlock;		//�ڶԿ���в���ʱ��һ������ָ����һ�����ͷ��ַ��ָ��
	MAKE *p_Temp_All;			//�ڶԿ���в���ʱ��һ��������ʱʹ�õ�ָ�루һ���������ӻ���ɾ���飩
};

c_LinkedList::c_LinkedList(uint n_Temp_Blocks) {
	//����������ݱ���
	n_Blocks = n_Temp_Blocks;

	//������һ����
	p_FirstBlock = new MAKE;
	if (NULL == p_FirstBlock) {
		//��ʼ��ʧ��
		//�׳��쳣
		throw(1);
		//��ӡ����
		ERROR_PRINT_MLL;

		//���ݸ�ԭ����ֹҰָ������ͷź�����©��
		n_Blocks = 0;
		p_FirstBlock = NULL;
		p_Temp_Head = NULL;
		p_Temp_NextBlock = NULL;
		return;
	}

	//��ʼ��������
	//����׼��
	uint n_Loops = 0;		//����ѭ������
	uint n_SaveLoops = 0;	//���ڼ�¼ѭ������
	p_Temp_Head = p_FirstBlock;

	//��ʼ����
	for (n_Loops; n_Loops < n_Blocks; n_Loops++, n_SaveLoops++) {
		p_Temp_NextBlock = new MAKE;
		if (NULL == p_Temp_NextBlock) {
			//����ʧ��
			//�׳��쳣
			throw(1);
			ERROR_PRINT_MLL;

			//ɾ���Ѿ������Ŀ�

			//��Headָ��ָ��ͷ
			p_Temp_Head = p_FirstBlock;
			//��ѭ��������
			n_Loops = 0;
			for (n_Loops; n_Loops < n_SaveLoops; n_Loops++) {
				p_Temp_NextBlock = p_Temp_Head->p_NextBlock;
				delete p_Temp_Head;
				p_Temp_Head = p_Temp_NextBlock;
			}

			//���ݸ�ԭ����ֹҰָ������ͷź�����©��
			n_Blocks = 0;
			p_FirstBlock = NULL;
			p_Temp_Head = NULL;
			p_Temp_NextBlock = NULL;

			//ɾ�����
			return;
		}
		p_Temp_Head->p_NextBlock = p_Temp_NextBlock;
		p_Temp_Head = p_Temp_NextBlock;
	}

	//�������
	p_Temp_Head = NULL;
	p_Temp_NextBlock = NULL;

	printf("[OK]COMPELTELY MAKE THE LINKED LIST\n");
	return;
}

MAKE *c_LinkedList::f_AddBlock(uint n_Location_Block) {
	if (n_Location_Block > n_Blocks) {
		//����̫����
		ERROR_PRINT_TL;
		return p_FirstBlock;
	}

	//���ݳ�ʼ��
	uint n_Loops = 0;
	p_Temp_Head = p_FirstBlock;

	//Ѱ�ҵ����λ��
	for (n_Loops; n_Loops < n_Location_Block; n_Loops++) {
		p_Temp_NextBlock = p_Temp_Head->p_NextBlock;
		p_Temp_Head = p_Temp_NextBlock;
	}

	//��ʼ����һ����
	//����ԭ���ڶ������ͷ��ַ
	p_Temp_All = p_Temp_Head->p_NextBlock;

	//���ڶ�ָ��ָ���µĿ�
	p_Temp_NextBlock = new MAKE;
	if (NULL == p_Temp_NextBlock) {
		throw(1);

		ERROR_PRINT_MLL;
		return NULL;
	}

	//��ԭ��һ�����ָ���ַ��Ϊ�µĵ�ַ
	p_Temp_Head->p_NextBlock = p_Temp_NextBlock;
	
	//���µĿ��ָ���ַ��Ϊ�����ԭ���ַ
	p_Temp_NextBlock->p_NextBlock = p_Temp_All;

	//��ָ�븴ԭ
	p_Temp_All = NULL;
	p_Temp_Head = NULL;
	p_Temp_NextBlock = NULL;

	return p_Temp_NextBlock;
}

MAKE *c_LinkedList::f_DelBlock(uint n_Location_Block) {
	if (n_Location_Block >= n_Blocks) {
		//����̫����
		ERROR_PRINT_TL;
		return p_FirstBlock;
	}

	//ѭ����
	uint n_Loops = 0;
	p_Temp_Head = p_FirstBlock;

	//Ѱ�ҵ����λ��
	for (n_Loops; n_Loops < n_Location_Block; n_Loops++) {
		p_Temp_NextBlock = p_Temp_Head->p_NextBlock;
		p_Temp_Head = p_Temp_NextBlock;
	}

	//�ڶ�ָ��ָ��ɾ���Ŀ�
	p_Temp_NextBlock = p_Temp_Head->p_NextBlock;
	
	//����ָ��ָ��ɾ���Ŀ�
	p_Temp_All = p_Temp_NextBlock->p_NextBlock;

	//ɾ����
	delete p_Temp_NextBlock;

	//����������
	p_Temp_Head->p_NextBlock = p_Temp_All;

	return NULL;
}

 uint c_LinkedList::vf_UseForYourSelf(uint n_Location_Block) {
	 uint n_Loops = 0;
	 //Ѱ�ҵ����λ��
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
	//���Դ���
	c_LinkedList *Test = new c_LinkedList(10);
	Test->f_AddBlock(2);
	Test->f_DelBlock(30);

	Test->vf_UseForYourSelf(2);
	return 0;
}