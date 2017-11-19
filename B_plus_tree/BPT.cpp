#include"BPT.h"

BP::BP( ) {
	head=NULL;
	first=NULL;
}

BP::~BP( ){

}

void BP::insert(int num) {
	if(head == NULL){                               //��Ϊ�ղ���ͷ���
		treeNode *p = new treeNode(num);
		head = p;
		first = p;
	}
	else{														//����Ϊ�յ����
		int i;
		treeNode *cur = head;
		while(cur->child[0].next != NULL){
			for(i=0;i<cur->child_num;++i){
				if(cur->child[i].key > num){
					break;
				}
			}
			if(i == cur->child_num){                //���뵽���һ���հ�λ��
				cur->child[cur->child_num-1].key=num;
				i=cur->child_num-1;
			}
			cur=cur->child[i].next;               // �ҵ�num�Ĳ���λ���ڵ�ǰ�ڵ��ĸ�������
		}
		
		//-----num�ŵ�Ҷ�ӽڵ�ĵڼ���λ��

		for (i = cur->child_num-1; i >=0 ; i--){
			if(num < cur->child[i].key){
				cur->child[i+1].key=cur->child[i].key;                     //����������һ����Ԫ�Լ�����num��key��������󿽱��������в������ݣ�
			}
			else{
				break;
			}
		}
		cur->child[i+1].key=num;                                              // �ҵ�����λ��
		cur->child[cur->child_num].next = NULL;
		cur->child_num = cur->child_num+1;                          //�����Ŀ+1

		//���Ҷ�ӽڵ�ؼ��ָ��������׷��ѣ��м�ؼ����ᵽ���ڵ�

		while(cur->child_num == ORDER+1){
			treeNode *node = new treeNode(num);
			int j;
			if(cur == head){
					for (i = (cur->child_num+1)/2; i < cur->child_num; i++){             //�ڵ��벿�ּ��뵽�½ڵ���
						node->child[i-(cur->child_num+1)/2].key = cur->child[i].key;
						node->child[i-(cur->child_num+1)/2].next = cur->child[i].next;
					}
					node->child_num=(ORDER+1)/2;
					node->bro=cur->bro;
					cur->bro=node;
					cur->child_num=ORDER/2+1;

					treeNode *root=new treeNode(num);
					root->bro=NULL;
					root->child_num = 2;
					root->parent = NULL;
					root->child[0].key = cur->child[cur->child_num-1].key;
					root->child[0].next = cur;
					root->child[1].key = node->child[node->child_num-1].key;
					root->child[1].next = node;
					cur->parent = root;
					node->parent = root;
					head = root;
					if (node->child[0].next!=NULL){
					for (int k = 0; k < node->child_num; k++)
					{
						node->child[k].next->parent = node;
					}
				}
			}
			else{                                     //��ǰ�ڵ㲻�Ǹ��ڵ�
					for (i = (cur->child_num+1)/2; i < cur->child_num; i++){                   //�ڵ��벿�ּ��뵽�½ڵ���
				
						node->child[i-(cur->child_num+1)/2].key = cur->child[i].key;
						node->child[i-(cur->child_num+1)/2].next=cur->child[i].next;
					}
					node->parent = cur->parent;
					node->child_num=(ORDER+1)/2;
					node->bro = cur->bro;
					cur->bro = node;
					cur->child_num=ORDER/2+1;
					for (j = cur->parent->child_num-1; j >= 0; j--)	{								//���м�ؼ����Ƶ����ڵ�
				
							if (cur->parent->child[j].key > cur->child[ORDER/2].key){
					
									cur->parent->child[j+1].key = cur->parent->child[j].key;
									cur->parent->child[j+1].next = cur->parent->child[j].next;
							}
							else
								break;
					}
					cur->parent->child[j+1].key = cur->child[ORDER/2].key;
					cur->parent->child[j+1].next = cur;
					cur->parent->child[j+2].next = node;
					cur->parent->child_num=cur->parent->child_num+1;
					if (node->child[0].next != NULL){
				
						for (i = 0; i < node->child_num; i++){
						
							node->child[i].next->parent = node;
						}
				}
				cur=cur->parent;
			}

		}
	
	}
}

void BP::del(int num) {
	treeNode *cur=head;
	treeNode *emp;
	if (cur->child[cur->child_num-1].key < num){
		cout<<"���������ڣ�1"<<endl;
		return ;
	}
	//�ҵ�num��Ҷ�ӽڵ��λ��
	int i;
	while (cur->child[0].next != NULL){
			for (i = 0; i < cur->child_num; i++){
				if (cur->child[i].key >= num){
						break;
			}
		}
		cur=cur->child[i].next;
	}
	for ( i = 0; i < cur->child_num; i++){
			if (cur->child[i].key >= num){
				break;
			}
	}
	if (cur->child[i].key != num){
		cout<<"���������ڣ�2"<<endl;
		return ;
	}
	//ɾ��Ҷ�ӽڵ��ڵ�numֵ
	for (int j = i+1; j <  cur->child_num; j++){
		cur->child[j-1].key = cur->child[j].key;
		cur->child[j-1].next=cur->child[j].next;
	}
	cur->child_num--;
	if (head->child_num==0)
	{
		delete cur;
		head=NULL;
		first=NULL;
		return;
	}
	//��numΪ��ǰ�ڵ�����ֵ�����¸��ڵ�Ķ�Ӧ�ؼ���
	emp=cur;
	while (cur!=head){
		for (i = 0; i < cur->parent->child_num; i++){     //�ҵ���ǰ�ڵ��ڸ��ڵ��λ��i
			if (cur->parent->child[i].key>=cur->child[cur->child_num-1].key)
			{
				cur->parent->child[i].key = cur->child[cur->child_num-1].key;
				break;
			}
		}
			cur=cur->parent;
	}

	//����ǰ�ڵ�ؼ��ָ���С��Degree/2
	cur=emp;
	while(cur->child_num<=ORDER/2-1){
		if (cur==head && cur->child_num>=2){
			break;
		}
		if (cur==head && head != first && cur->child_num == 1){
			head=cur->child[0].next;
			delete cur;
			break;
		}
		if (head==first)
		{
			break;
		}
		//�ҵ���ǰ�ڵ��ڸ��ڵ��λ��
		for (i = 0; i < cur->parent->child_num; i++){
			if (cur->parent->child[i].key >= cur->child[cur->child_num-1].key){
				break;
			}
		}
		if (cur->parent->child_num-1 == i){                                                      //��û�����ֵ�
			if (cur->parent->child[i-1].next->child_num > ORDER/2){                 //�����ֵܽ裬�����ֵܿɽ�
				for (int j = cur->child_num-1; j <= 0; j--){                                     //��ǰ�ڵ�ؼ�������һλ
					cur->child[j+1].key=cur->child[j].key;
					cur->child[j+1].next = cur->child[j].next;
				}
				//��ǰ�ؼ��ֵ�һ���ؼ���Ϊ���ֵ����ؼ���
				cur->child[0].key=cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num-1].key;
				cur->child[0].next=cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num-1].next;
				//��ǰ�ڵ㳤��+1�����ֵܽڵ㳤��-1
				cur->child_num++;
				cur->parent->child[i-1].next->child_num--;
				//�ı����ֵܸ��ڵ��Ӧ�ؼ���
				cur->parent->child[i-1].key = cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num-1].key;
			}
			else//�����ֵܲ��ɽ裬�ϲ�
			{
				for (int j = 0; j < cur->child_num; j++)	{                    //�ϲ��ڵ�
			
					cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num+j].key = cur->child[j].key;
					cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num+j].next=cur->child[j].next;
				}
				cur->parent->child[i-1].next->child_num=cur->parent->child[i-1].next->child_num+cur->child_num;//���ֵܹؼ��ָ�������
				cur->parent->child[i-1].next->bro=cur->bro;//�ֵ�ָ��ı�
				//���ڵ�ؼ�������
				cur->parent->child[i-1].key=cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num-1].key;
				for (int j = i; j <cur->parent->child_num-1 ; j++){
					cur->parent->child[j].key = cur->parent->child[j+1].key;
					cur->parent->child[j].next=cur->parent->child[j+1].next;
				}
				cur->parent->child_num--;
				if (cur->child[0].next != NULL){                          //��Ҷ�ӽ��ϲ������亢�ӵ�parents�ı�		
					for (int j = 0; j < cur->child_num; j++){
						cur->child[j].next->parent = cur->parent->child[i-1].next;
					}
				}
				emp=cur;
				cur=cur->parent;
				delete emp;
			}
		}
		else//�������ֵ�
		{
			if (cur->parent->child[i+1].next->child_num>ORDER/2)//�����ֵܽ裬�����ֵܿɽ�
			{
				//��ǰ�ڵ����һ���ؼ���Ϊ���ֵ���С�ؼ���
				cur->child[cur->child_num].key = cur->parent->child[i+1].next->child[0].key;
				cur->child[cur->child_num].next = cur->parent->child[i+1].next->child[0].next;
				//���ֵܹؼ�������һλ
				for (int j = 0; j < cur->parent->child[i+1].next->child_num-1; j++)
				{
					cur->parent->child[i+1].next->child[j].key = cur->parent->child[i+1].next->child[j+1].key;
					cur->parent->child[i+1].next->child[j].next=cur->parent->child[i+1].next->child[j+1].next;
				}
				cur->parent->child[i+1].next->child_num--;
				cur->child_num++;

				//�ı䵱ǰ�ڵ�ĸ��ڵ��Ӧ�ؼ���
				cur->parent->child[i].key = cur->child[cur->child_num-1].key;
			}
			else//�����ֵܲ��ɽ裬�ϲ�
			{
				for (int j = 0; j < cur->parent->child[i+1].next->child_num; j++)//�ϲ��ڵ�
				{
					cur->child[cur->child_num+j].key = cur->parent->child[i+1].next->child[j].key;
					cur->child[cur->child_num+j].next=cur->parent->child[i+1].next->child[j].next;
				}
				cur->child_num=cur->child_num+cur->parent->child[i+1].next->child_num;//��ǰ�ڵ�ؼ��ָ�������
				cur->bro=cur->parent->child[i+1].next->bro;//�ֵ�ָ��ı�
				//���ڵ�ؼ�������
				delete cur->parent->child[i+1].next;
				cur->parent->child[i].key = cur->child[cur->child_num-1].key;
				for (int j = i+1; j <cur->parent->child_num-1 ; j++)
				{
					cur->parent->child[j].key = cur->parent->child[j+1].key;
					cur->parent->child[j].next = cur->parent->child[j+1].next;
				}
				cur->parent->child_num--;
				if (cur->child[0].next != NULL)//��Ҷ�ӽ��ϲ������亢�ӵ�parents�ı�
				{
					for (int j = 0; j < cur->child_num; j++)
					{
						cur->child[j].next->parent=cur;
					}
				}
				cur=cur->parent;
			}
		}
	}

}

void BP::display( ){

	treeNode *cur=first;
	if (cur==NULL)	{
		cout<<"B+��Ϊ�գ�"<<endl;
		return;
	}
	while (cur!=NULL)	{
		for (int i = 0; i < cur->child_num; i++){
			cout<<cur->child[i].key<<",";
		}
		cout<<"--->";
		cur=cur->bro;
	}

}

void BP::search(int n) {
	treeNode *cur=head;
	if(cur == NULL) {
		cout<<"B+��Ϊ�գ�"<<endl;
		return;
	}
	int i=0;
	while(cur != NULL){
		for(;i<cur->child_num;++i){
			if(n > cur->child[cur->child_num-1].key){
				cout<<"�����ڴ�ֵ��"<<endl;
				return;
			}
			else
				{
				cur = cur->child[i].next;
				continue;
				}
		}
		for(int i=0;i<cur->child_num;++i){
				if(n == cur->child[i].key && cur->child[i].next == NULL){
					 cout<<"�ҵ�"<<endl;
					 return;
				}
		}
	}
	cout<<"û���ҵ�"<<endl;
}