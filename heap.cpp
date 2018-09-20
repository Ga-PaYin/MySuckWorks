#include <iostream>
#define infinite 10000000
using namespace std;
class heap {
public:
int size;
int *element;
bool maxOrmin;        //判断这是最大堆还是最小堆，true为最大，false为最小
void insert(int t);
int delTop();
heap(int s,bool los,int *elements);
~heap();
int getSize();
int find(int t);
};

heap::heap(int s,bool los,int *elements) : size(s),maxOrmin(los){
        element = new int[size + 1];
        maxOrmin ? element[0] = infinite : element[0] = -infinite;//设置哨兵
        for(int i = 1; i <= size; i++) {
                element[i] = elements[i-1];
        }//首先建成一棵完全二叉树
        //从最后一个非叶节点开始，将它下沉
        int i;
        for(i = size; 2 * i > size; i--); //找到第一个非叶节点；
        for(int n = i; n > 0; n--) {
                int arr = n;
                while(arr*2 <= size) {
                        if(maxOrmin) {//最大堆
                                if(element[arr*2]>element[arr*2+1] || arr*2+1>size) {
                                        //左节点大于右节点，应该让左节点和该节点换位置
                                        if(element[arr] < element[arr*2]) {
                                                int t = element[arr];
                                                element[arr] = element[arr*2];
                                                element[arr*2] = t;
                                        }
                                        arr *= 2;
                                }else{        //右节点大于左节点，应该让右节点和该节点换位置
                                        if(element[arr]<element[arr*2+1]) {
                                                int t = element[arr];
                                                element[arr] = element[arr*2+1];
                                                element[arr*2+1] = t;
                                        }
                                        arr = arr*2 + 1;
                                }
                        }else{//最小堆
                                if(element[arr*2]<element[arr*2+1] || arr*2+1>size) {
                                        //左节点小于右节点，则应该让左节点和该节点换位置
                                        if(element[arr] > element[arr*2]) {
                                                int t = element[arr];
                                                element[arr] = element[arr*2];
                                                element[arr*2] = t;
                                        }
                                        arr *= 2;
                                }else{
                                        //右节点小于左节点，应该让右节点和该节点换位置
                                        if(element[arr] > element[arr*2+1]) {
                                                int t = element[arr];
                                                element[arr] = element[arr*2+1];
                                                element[arr*2+1] = t;
                                        }
                                        arr = arr*2 + 1;
                                }
                        }
                }
        }
}

int heap::delTop(){
        int arr = size;
        size--;
        int top = element[1];
        element[1] = element[arr];
        delete &element[arr];
        //现在最后一个节点位于堆顶，要把它下沉
        arr = 1;
        while(arr <= size) {
                if(maxOrmin) {//最大堆
                        if(element[arr*2]>element[arr*2+1] || arr*2+1>size) {
                                //左节点大于右节点，应该让左节点和该节点换位置
                                if(element[arr]<element[arr*2] && arr*2 <= size) {
                                        int t = element[arr];
                                        element[arr] = element[arr*2];
                                        element[arr*2] = t;
                                }
                                arr *= 2;
                        }else{//右节点大于左节点，应该让右节点和该节点换位置
                                if(element[arr]<element[arr*2+1]) {
                                        int t = element[arr];
                                        element[arr] = element[arr*2+1];
                                        element[arr*2+1] = t;
                                }
                                arr = arr*2 + 1;
                        }
                }else{//最小堆
                        if(element[arr*2]<element[arr*2+1]||arr*2+1>size) {
                                //左节点小于右节点，则应该让左节点和该节点换位置
                                if(element[arr] > element[arr*2] && arr*2 <= size) {
                                        int t = element[arr];
                                        element[arr] = element[arr*2];
                                        element[arr*2] = t;
                                }
                                arr *= 2;
                        }else{
                                //右节点小于左节点，应该让右节点和该节点换位置
                                if(element[arr] > element[arr*2+1]) {
                                        int t = element[arr];
                                        element[arr] = element[arr*2+1];
                                        element[arr*2+1] = t;
                                }
                                arr = arr*2 + 1;
                        }
                }
        }
        return top;
}

void heap::insert(int t){
        size++;
        int *store = element;
        int *element2 = new int[size + 1];
        for(int i = 0; i < size; i++) {
                element2[i] = element[i];
        }
        element2[size] = t;
        delete element;
        element = element2;//首先在堆尾增加一个节点；
        //然后要将节点上浮；
        int *r = &element[size];
        int arr = size;
        while(arr > 0) {
                if(maxOrmin) {//最大堆
                        if(element[arr] > element[arr/2]) {
                                int m = element[arr];
                                element[arr] = element[arr/2];
                                element[arr/2] = m;
                        }
                        arr = arr/2;
                }else{//最小堆
                        if(element[arr] < element[arr/2]) {
                                int m = element[arr];
                                element[arr] = element[arr/2];
                                element[arr/2] = m;
                        }
                        arr = arr/2;
                }
        }

}

int heap::getSize(){
        return size;
}

int heap::find(int t){
        int i;
        for(i = 1; i <= size; i++) {
                if(element[i] == t) {
                        for(int n = i; n > 0; n/=2) {
                                cout<<element[n]<<' ';
                        }
                        cout<<endl;
                        break;
                }
        }
        return i;
}
heap::~heap(){
        delete element;
}
int main(int argc, char const *argv[]) {
        int size = 10;
        int HEAP[size] = {
                3,2,5,7,5,10,3,6,1,9
        };

        heap MaxHeap(size,true,HEAP);
        MaxHeap.insert(12);
        MaxHeap.find(9);
        int t = MaxHeap.getSize();
        for(int i = 0; i < t; i++) {
                cout<<MaxHeap.delTop()<<' ';
        }
        cout<<endl<<endl;
        cout<<endl;
        heap MinHeap(size,false,HEAP);
        MinHeap.insert(11);
        MinHeap.find(9);
        t = MinHeap.getSize();
        for(int i = 0; i < t; i++) {
                cout<<MinHeap.delTop()<<' ';
        }
        cout<<endl<<endl;
        return 0;
}
