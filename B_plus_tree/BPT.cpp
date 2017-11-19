#include"BPT.h"

BP::BP( ) {
	head=NULL;
	first=NULL;
}

BP::~BP( ){

}

void BP::insert(int num) {
	if(head == NULL){                               //树为空插入头结点
		treeNode *p = new treeNode(num);
		head = p;
		first = p;
	}
	else{														//树不为空的情况
		int i;
		treeNode *cur = head;
		while(cur->child[0].next != NULL){
			for(i=0;i<cur->child_num;++i){
				if(cur->child[i].key > num){
					break;
				}
			}
			if(i == cur->child_num){                //插入到最后一个空白位置
				cur->child[cur->child_num-1].key=num;
				i=cur->child_num-1;
			}
			cur=cur->child[i].next;               // 找到num的插入位置在当前节点哪个孩子里
		}
		
		//-----num放到叶子节点的第几个位置

		for (i = cur->child_num-1; i >=0 ; i--){
			if(num < cur->child[i].key){
				cur->child[i+1].key=cur->child[i].key;                     //将结点中最后一个单元以及大于num的key的索引向后拷贝（数组中插入数据）
			}
			else{
				break;
			}
		}
		cur->child[i+1].key=num;                                              // 找到插入位置
		cur->child[cur->child_num].next = NULL;
		cur->child_num = cur->child_num+1;                          //结点数目+1

		//如果叶子节点关键字个数超过阶分裂，中间关键字提到父节点

		while(cur->child_num == ORDER+1){
			treeNode *node = new treeNode(num);
			int j;
			if(cur == head){
					for (i = (cur->child_num+1)/2; i < cur->child_num; i++){             //节点后半部分加入到新节点里
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
			else{                                     //当前节点不是根节点
					for (i = (cur->child_num+1)/2; i < cur->child_num; i++){                   //节点后半部分加入到新节点里
				
						node->child[i-(cur->child_num+1)/2].key = cur->child[i].key;
						node->child[i-(cur->child_num+1)/2].next=cur->child[i].next;
					}
					node->parent = cur->parent;
					node->child_num=(ORDER+1)/2;
					node->bro = cur->bro;
					cur->bro = node;
					cur->child_num=ORDER/2+1;
					for (j = cur->parent->child_num-1; j >= 0; j--)	{								//把中间关键字移到父节点
				
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
		cout<<"该数不存在！1"<<endl;
		return ;
	}
	//找到num在叶子节点的位置
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
		cout<<"该数不存在！2"<<endl;
		return ;
	}
	//删除叶子节点内的num值
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
	//若num为当前节点的最大值，更新父节点的对应关键字
	emp=cur;
	while (cur!=head){
		for (i = 0; i < cur->parent->child_num; i++){     //找到当前节点在父节点的位置i
			if (cur->parent->child[i].key>=cur->child[cur->child_num-1].key)
			{
				cur->parent->child[i].key = cur->child[cur->child_num-1].key;
				break;
			}
		}
			cur=cur->parent;
	}

	//若当前节点关键字个数小于Degree/2
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
		//找到当前节点在父节点的位置
		for (i = 0; i < cur->parent->child_num; i++){
			if (cur->parent->child[i].key >= cur->child[cur->child_num-1].key){
				break;
			}
		}
		if (cur->parent->child_num-1 == i){                                                      //若没有右兄弟
			if (cur->parent->child[i-1].next->child_num > ORDER/2){                 //从左兄弟借，若左兄弟可借
				for (int j = cur->child_num-1; j <= 0; j--){                                     //当前节点关键字右移一位
					cur->child[j+1].key=cur->child[j].key;
					cur->child[j+1].next = cur->child[j].next;
				}
				//当前关键字第一个关键字为左兄弟最大关键字
				cur->child[0].key=cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num-1].key;
				cur->child[0].next=cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num-1].next;
				//当前节点长度+1，左兄弟节点长度-1
				cur->child_num++;
				cur->parent->child[i-1].next->child_num--;
				//改变左兄弟父节点对应关键字
				cur->parent->child[i-1].key = cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num-1].key;
			}
			else//若左兄弟不可借，合并
			{
				for (int j = 0; j < cur->child_num; j++)	{                    //合并节点
			
					cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num+j].key = cur->child[j].key;
					cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num+j].next=cur->child[j].next;
				}
				cur->parent->child[i-1].next->child_num=cur->parent->child[i-1].next->child_num+cur->child_num;//左兄弟关键字个数更新
				cur->parent->child[i-1].next->bro=cur->bro;//兄弟指针改变
				//父节点关键字左移
				cur->parent->child[i-1].key=cur->parent->child[i-1].next->child[cur->parent->child[i-1].next->child_num-1].key;
				for (int j = i; j <cur->parent->child_num-1 ; j++){
					cur->parent->child[j].key = cur->parent->child[j+1].key;
					cur->parent->child[j].next=cur->parent->child[j+1].next;
				}
				cur->parent->child_num--;
				if (cur->child[0].next != NULL){                          //非叶子结点合并，将其孩子的parents改变		
					for (int j = 0; j < cur->child_num; j++){
						cur->child[j].next->parent = cur->parent->child[i-1].next;
					}
				}
				emp=cur;
				cur=cur->parent;
				delete emp;
			}
		}
		else//若有右兄弟
		{
			if (cur->parent->child[i+1].next->child_num>ORDER/2)//从右兄弟借，若右兄弟可借
			{
				//当前节点最后一个关键字为右兄弟最小关键字
				cur->child[cur->child_num].key = cur->parent->child[i+1].next->child[0].key;
				cur->child[cur->child_num].next = cur->parent->child[i+1].next->child[0].next;
				//右兄弟关键字左移一位
				for (int j = 0; j < cur->parent->child[i+1].next->child_num-1; j++)
				{
					cur->parent->child[i+1].next->child[j].key = cur->parent->child[i+1].next->child[j+1].key;
					cur->parent->child[i+1].next->child[j].next=cur->parent->child[i+1].next->child[j+1].next;
				}
				cur->parent->child[i+1].next->child_num--;
				cur->child_num++;

				//改变当前节点的父节点对应关键字
				cur->parent->child[i].key = cur->child[cur->child_num-1].key;
			}
			else//若右兄弟不可借，合并
			{
				for (int j = 0; j < cur->parent->child[i+1].next->child_num; j++)//合并节点
				{
					cur->child[cur->child_num+j].key = cur->parent->child[i+1].next->child[j].key;
					cur->child[cur->child_num+j].next=cur->parent->child[i+1].next->child[j].next;
				}
				cur->child_num=cur->child_num+cur->parent->child[i+1].next->child_num;//当前节点关键字个数更新
				cur->bro=cur->parent->child[i+1].next->bro;//兄弟指针改变
				//父节点关键字左移
				delete cur->parent->child[i+1].next;
				cur->parent->child[i].key = cur->child[cur->child_num-1].key;
				for (int j = i+1; j <cur->parent->child_num-1 ; j++)
				{
					cur->parent->child[j].key = cur->parent->child[j+1].key;
					cur->parent->child[j].next = cur->parent->child[j+1].next;
				}
				cur->parent->child_num--;
				if (cur->child[0].next != NULL)//非叶子结点合并，将其孩子的parents改变
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
		cout<<"B+树为空！"<<endl;
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
		cout<<"B+树为空！"<<endl;
		return;
	}
	int i=0;
	while(cur != NULL){
		for(;i<cur->child_num;++i){
			if(n > cur->child[cur->child_num-1].key){
				cout<<"不存在此值！"<<endl;
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
					 cout<<"找到"<<endl;
					 return;
				}
		}
	}
	cout<<"没有找到"<<endl;
}