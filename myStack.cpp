#include<iostream>
using namespace std;

template <typename type>
class stack{
	private:
		int size;
		type *Data;
		int Top;
	public:
		stack(int n);
		~stack();
		bool isEmpty();
		bool isFull(); 
		void Push(type a);
		type Pop();
		void Clear();
		void show();
};
template<typename type>
stack<type>::stack(int n):size(n){
	Data = new type[size];
	Top = -1;
}
template<typename type>
stack<type>::~stack(){
	delete Data;
}
template<typename type>
bool stack<type>:: isEmpty(){
	if(Top == -1) return true;
	else return false; 
}
template<typename type>
bool stack<type>::isFull(){
	if(Top == size - 1) return true;
	else return false;
}
template<typename type>
void stack<type>::Push(type a){
	if(isFull()){
		cout<<"¶ÑÕ»ÂúÁË£¬Ìí¼ÓÊ§°Ü"<<endl;
	}else{
		Data[++Top] = a;
	}
}
template<typename type>
type stack<type>::Pop(){
	if(isEmpty()){
		cout<<"¶ÑÕ»¿ÕÁË£¬µ¯³öÊ§°Ü"<<endl;
	}else{
		type i = Data[Top];
		Top--;
		return i;
	}
} 
template<typename type>
void stack<type>::Clear(){
	int i;
	for(i == Top; i > -1; i--){
		Pop();
	}
	Top = -1;
}
template<typename type>
void stack<type>::show(){
	if(!isEmpty()){
		int i;
		for(i = 0; i <= Top; i++){
			cout<<Data[i]<<' ';
		}
	}else{
		cout<<"¶ÑÕ»ÊÇ¿ÕµÄ";
	}
	cout<<endl;
}
int main(int argc,char *argv[]){
	stack<int> stack1(20); 
	stack1.Push(12345);
	stack1.show();
	stack1.Pop();
	stack1.show();
	stack1.Push(12233);
	stack1.show();
	stack1.Push(8927);
	stack1.show();
	int i;
	for(i = 0; i < 20; i++){
		stack1.Push(i);
	}
	stack1.show();
	stack1.Pop();
	stack1.show(); 
	return 0;
}

