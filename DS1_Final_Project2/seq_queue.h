//
// Created by Kevin on 2022/4/11.
//

#ifndef DS1FINALPROJECT2_SEQ_QUEUE_H
#define DS1FINALPROJECT2_SEQ_QUEUE_H

template<typename ElemType>
class SeqQueue{
protected:
    int front, rear;
    int maxSize;
    ElemType *elems;

public:
    explicit SeqQueue(int size = 100000);					 // 构造函数
    virtual ~SeqQueue();								 // 析构函数
    int GetLength() const;								 // 求队列长度
    bool IsEmpty() const;								 // 判断队列是否为空
    void Clear();										 // 将队列清空
    void Traverse(void (*Visit)(const ElemType &)) const;// 遍历队列
    bool DelQueue(ElemType &e);					     // 出队操作
    bool GetHead(ElemType &e) const;				     // 取队头操作
    bool EnQueue(ElemType e);				     // 入队操作
    SeqQueue(const SeqQueue<ElemType> &q);			 // 复制构造函数
    SeqQueue<ElemType> &operator =(const SeqQueue<ElemType> &q);// 赋值语句重载
};

template<typename ElemType>
void Write(const ElemType &e)
// 操作结果: 显示数据元素
{
    std::cout << e ;
}

template<typename ElemType>
SeqQueue<ElemType>::SeqQueue(int size){
    maxSize = size;
    elems = new ElemType[maxSize];
    rear = front = 0;
}

template<typename ElemType>
SeqQueue<ElemType>::~SeqQueue(){
    delete[] elems;
}

template<typename ElemType>
int SeqQueue<ElemType>::GetLength() const {
    //返回队列长度
    return (rear + maxSize - front) % maxSize;
}

template<class ElemType>
bool SeqQueue<ElemType>::IsEmpty() const{
    return front == rear;
}

template<class ElemType>
void SeqQueue<ElemType>::Clear(){
    rear = front = 0;
}

template <class ElemType>
void SeqQueue<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：依次对队列的每个元素调用函数(*visit)
{
    for (int i = front; i != rear; i = (i + 1) % maxSize)
        (*Visit)(elems[i]);
}

template<class ElemType>
bool SeqQueue<ElemType>::DelQueue(ElemType &e){
    if (! IsEmpty()){
        e=elems[front];
        front = (front + 1) % maxSize;
        return true;
    }
    else
        return false;
}

template<class ElemType>
bool SeqQueue<ElemType>::GetHead(ElemType &e) const{
    if(! IsEmpty()){
        e=elems[front];
        return true;
    }
    else
        return false;
}

template<class ElemType>
bool SeqQueue<ElemType>::EnQueue(const ElemType e){
    if ( (rear + 1) % maxSize == front )
        return false;
    else{
        elems[rear] = e;
        rear = (rear + 1) % maxSize;
        return true;
    }
}

template<class ElemType>   //复制构造函数
SeqQueue<ElemType>::SeqQueue(const SeqQueue<ElemType> &q){
    maxSize = q.maxSize;
    elems = new ElemType[maxSize];
    front = q.front;
    rear = q.rear;
    for(int i = front; i != rear; i=(i+1) % maxSize)
        elems[i]=q.elems[i];
}

template<typename ElemType>
SeqQueue<ElemType> &SeqQueue<ElemType>::operator=(const SeqQueue<ElemType> &q){
    if(&q != this){
        maxSize = q.maxSize;
        elems = new ElemType[maxSize];
        front = q.front;
        rear = q.rear;
        for (int i = front; i != rear; i = (i + 1) % maxSize)
            elems[i] = q.elems[i];
    }
    return *this;
}
#endif //DS1FINALPROJECT2_SEQ_QUEUE_H
