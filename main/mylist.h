#ifndef MYLIST_H
#define MYLIST_H

#include <arduino.h>
#include <limits.h>

#define NORESULT UINT_MAX

template<class listtype>
class mylist
{
    public:
        mylist(const size_t default_size = 1);

        // content control
        bool add(const listtype);
        void pop_back();
        listtype begin() { return _size>0?container[0]:NULL; };
        listtype end() { return _size>0?container[_size-1]:NULL; };
        listtype get(uint16_t);
        listtype& operator[] (size_t i) { return *(container+i); };
        const listtype& operator[] (size_t i) const { return *(container+i); };
        void erase(uint16_t);
        void clear();

        // sort and search
        void sort(int (*)(const void*,const void*));
        bool mergeSort(int (*)(const void*,const void*));
        uint16_t contain(const listtype);

        // get info
        uint16_t size();
        uint16_t max_size();
        size_t length(uint16_t);

    protected:
    private:
        uint16_t _size;
        uint16_t capacity;
        //int _sort_by;
        bool sorted;
        listtype *container;
        bool increaseCapacity();
        bool _mergeSort(const int,const int);
        bool merge(const int,const int,const int);
        int (*_compare)(const void*,const void*);
};

// ==================================================

template<class listtype>
mylist<listtype>::mylist(const size_t default_size)
{
    _size = 0;
    capacity = 1;
    //_sort_by = 0;
    sorted = false;
    if(default_size==0) container = NULL;
    container = (listtype *)malloc(default_size*sizeof(listtype));
}

template<class listtype>
bool mylist<listtype>::add(const listtype value)
{
    if(_size == capacity)
    {
        if(!increaseCapacity()){ return false; }
    }
    container[_size] = value;
    _size++;
    sorted = false;
}

template<class listtype>
void mylist<listtype>::pop_back()
{
    _size--;
}

template<class listtype>
void mylist<listtype>::erase(uint16_t number)
{
    if(number>=_size) return ;
    container[number] = "";
    sorted = false;
}

template<class listtype>
void mylist<listtype>::clear()
{
    free(container);
    container = NULL;
    capacity = 0;
    _size = 0;
}

template<class listtype>
listtype mylist<listtype>::get(uint16_t number)
{
    return container[number];
}

template<class listtype>
uint16_t mylist<listtype>::size()
{
    return _size;
}

template<class listtype>
uint16_t mylist<listtype>::max_size()
{
    return capacity;
}

template<class listtype>
uint16_t mylist<listtype>::contain(const listtype target)
{
    if(sorted)
    {
        for(uint16_t i,l=0,r=_size-1,_i;l!=r;)
        {
            i = (l+r)/2;
            _i = (*_compare)(container[i],target);
            if(_i==0) return i;
            else _i<0 ? (l = i-1):(r = i+1);
        }
    }
    else
    {
        for(uint16_t i=0;i<_size;i++)
        {
            if((*_compare)(container[i],target)==0) return i;
        }
    }
    return NORESULT;
}

template<class listtype>
void mylist<listtype>::sort(int (*cmpfun)(const void*,const void*))
{
    qsort(container,_size,sizeof(listtype),cmpfun);
}

template<class listtype>
bool mylist<listtype>::mergeSort(int (*cmpfun)(const void*,const void*))
{
    _compare = cmpfun;
    if(!_mergeSort(0,_size-1)) return false;
    sorted = true;
    return true;
}

/**********************************
 * Private method
 * include sort, about capacity
 **********************************/

template<class listtype>
bool mylist<listtype>::increaseCapacity()
{
    capacity++;
    listtype *temp = (listtype *)realloc(container, capacity*sizeof(listtype));
    if(temp == NULL) return false;
    container = temp;
    return true;
}

#define MALLOC(p,s) \
    if(!((p)=(listtype*)malloc(s))) { \
        return false; \
    }

template<class listtype>
bool mylist<listtype>::_mergeSort(const int front,const int rear)
{
    if(front<rear)         //base case check
    {
        int q = (front+rear)/2;                     //divide
        if(!_mergeSort(front,q))    return false;  //left
        if(!_mergeSort(q+1  ,rear)) return false;  //right
        //Serial.println(F("merge"));
        if(!merge(front,q,rear))    return false;
    }
    return true;
}

template<class listtype>
bool mylist<listtype>::merge(const int front,const int q,const int rear)
{
    int left_length=q-front+1,right_length=rear-q;
    listtype *left,*right;
    MALLOC(left,(left_length)*sizeof(listtype));MALLOC(right,(right_length)*sizeof(listtype));
    for(int i=0;i<left_length ;i++) left[i]  = container[front+i];
    for(int i=0;i<right_length;i++) right[i] = container[q+i+1];
    for(int i=0,j=0,k=front;k<=rear;k++)
    {
        if(j==right_length || i!=left_length && _compare((void*)(left+i),(void*)(right+j))<0)
        {
            container[k] = left[i++];
        }
        else
        {
            container[k] = right[j++];
        }
    }

    free(left);free(right);
    return true;
}

#undef MALLOC(p,s)

#endif // MYLIST_H
