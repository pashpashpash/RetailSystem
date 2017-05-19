// #ifndef HEAP_H
// #define HEAP_H

// #include <vector>
// #include <functional>
// #include <utility>
// #include <algorithm>
// #include <stdexcept>
// #include <unordered_map>
// template <
//          typename T,
//          typename TComparator = std::less<T>,
//          typename PComparator = std::less<double>,
//          typename Hasher = std::hash<T> >
// class Heap
// {
// public:
//     /// Constructs an m-ary heap. M should be >= 2
//     Heap(int m = 2,
//          const PComparator& c = PComparator(),
//          const Hasher& hash = Hasher(),
//          const TComparator& tcomp = TComparator()  );

//     /// Destructor as needed
//     ~Heap();

//     /// Adds an item with the provided priority
//     void push(double pri, const T& item);

//     /// returns the element at the top of the heap
//     ///  max (if max-heap) or min (if min-heap)
//     T const & top() const;

//     /// Removes the top element
//     void pop();
//     /// returns true if the heap is empty
//     bool empty() const;

//     /// decreaseKey reduces the current priority of
//     /// item to newpri, moving it up in the heap
//     /// as appropriate.
//     void decreaseKey(double newpri, const T& item);

// private:
//     /// Add whatever helper functions you need below
//     void bubble(int index);
//     void trickle(int index);




//     // These should be all the data members you need.
//     std::vector< std::pair<double, T> > store_;
//     int m_;
//     PComparator c_;
//     std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

// };

// // Complete
// template <typename T, typename TComparator, typename PComparator, typename Hasher >
// Heap<T,TComparator,PComparator,Hasher>::Heap(
//     int m,
//     const PComparator& c,
//     const Hasher& hash,
//     const TComparator& tcomp ) :

//     store_(),
//     m_(m),
//     c_(c),
//     keyToLocation_(100, hash, tcomp)

// {

// }

// // Complete
// template <typename T, typename TComparator, typename PComparator, typename Hasher >
// Heap<T,TComparator,PComparator,Hasher>::~Heap()
// {

// }

// //---------------PUSH/BUBBLE-----------------
// template <typename T, typename TComparator, typename PComparator, typename Hasher >
// void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
// {
//     //implement this
//   store_.push_back(std::make_pair(priority, item));
  
//   keyToLocation_.insert(std::make_pair(item, store_.size() -1));
//   bubble(store_.size()-1); 

// }

// template <typename T, typename TComparator, typename PComparator, typename Hasher >
// void Heap<T,TComparator, PComparator, Hasher>::bubble(int index)
// {
//   if(index == 0)
//   {
//     return;
//   }
//   int parent = floor((index-1)/m_);
//   while(parent >= 0 && c_(store_[index].first, store_[parent].first))
//   {
//     iter_swap(store_.begin() + parent, store_.begin()+index);
//     keyToLocation_[store_[index].second] = parent;
//     keyToLocation_[store_[parent].second] = index;
//     index = parent;
//     floor(parent = (index-1)/m_);
//   }
// }
// //---------------PUSH/BUBBLE------------------


// template <typename T, typename TComparator, typename PComparator, typename Hasher >
// void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
// {
//     int index = keyToLocation_[item];
//     if(store_[index].first > priority)
//     {
//         store_[index].first = priority;
//         bubble(index); 
//     }
//     /// decreaseKey reduces the current priority of
//     /// item to newpri, moving it up in the heap
//     /// as appropriate.



// }

// template <typename T, typename TComparator, typename PComparator, typename Hasher >
// T const & Heap<T,TComparator,PComparator,Hasher>::top() const
// {
//     // Here we use exceptions to handle the case of trying
//     // to access the top element of an empty heap
//     if(empty()) {
//         throw std::logic_error("can't top an empty heap");
//     }

//     return store_.at(0).second;

// }

// //---------------POP/TRICKLE------------------
// template <typename T, typename TComparator, typename PComparator, typename Hasher >
// void Heap<T,TComparator,PComparator,Hasher>::pop()
// {
//     if(empty()) {
//         throw std::logic_error("can't pop an empty heap");
//     }

//     // iter_swap(store_.begin(), store_.end()-1);
//     // keyToLocation_[store_[0].second] = store_.size()-1;
//     // keyToLocation_[store_[store_.size()-1].second] = 0;
//     // store_.pop_back();
//     // keyToLocation_.erase(store_[store_.size()-1].second);
//     // trickle(0);


//     // cout << store_[0].second << " Simval:" << store_[0].first << endl;
//     // std::pair<double, std::string> node = store_.front();
//     // store_[0] = store_.back();
    
//     // store_.pop_back();
//     // trickle(0);

//     //typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it = keyToLocation_.find(node.second);
//     // cout << "Size of keytolocation = " << keyToLocation_.size() << endl;
//     // cout << store_[0].second << " Simval:" << store_[0].first << endl;
//     //keyToLocation_.erase(it);

//     store_[0] = store_.back();
//     keyToLocation_.erase(store_[store_.size()-1].second);
//     store_.pop_back();
//     trickle(0);


// }

// template <typename T, typename TComparator, typename PComparator, typename Hasher >
// void Heap<T,TComparator,PComparator,Hasher>::trickle(int index)
// {
//   int length = (int)store_.size();
//   if(index >= length)
//   {
//     return;
//   }
//   int child = m_*index+1;
//   int smallestChild = child;
//   if(length < m_)
//   {
//     for(int i = 1; i <length - 1; i++)
//     {
//         if(c_(store_[child+i].first, store_[smallestChild].first) )
//         {
//             smallestChild = child + i;
//         }
//     }
//   }
//   if (c_(store_[smallestChild].first, store_[index].first) )
//   {
//     iter_swap(store_.begin() + smallestChild, store_.begin() + index);
//     keyToLocation_[store_[index].second] = smallestChild;
//     keyToLocation_[store_[smallestChild].second] = index;
//   }
//   else
//   {
//     if(smallestChild < length)
//     {
//         for(int i = 1; i < m_; i++)
//         {
//             if(c_(store_[child+i].first, store_[smallestChild].first))
//             {
//                 smallestChild = child+i;
//             }
//         }
//     }
//     if(smallestChild < length)
//     {
//         if(c_(store_[smallestChild].first, store_[index].first))
//         {
//             iter_swap(store_.begin() + smallestChild, store_.begin() + index);
//             keyToLocation_[store_[index].second] = smallestChild;
//             keyToLocation_[store_[smallestChild].second] = index;
//             trickle(smallestChild);
//         }
//     }
//   }

//   // for(int i = m_*index + 1; i <= m_*index + m_; i++)
//   // {
//   //   if (i < store_.size())
//   //   {
//   //     if(c_(store_.at(i).first, store_.at(smallestChild).first))
//   //     {
//   //       smallestChild = i;
//   //     }
//   //   }
//   // }
//   // if(smallestChild < index)
//   // {
//   //   iter_swap(store_.begin() + index, store_.begin() + smallestChild);
//   //   keyToLocation_[store_[index].second] = smallestChild;
//   //   keyToLocation_[store_[smallestChild].second] = index;
//   //   trickle(smallestChild);
//   // }
// }
// //---------------POP/TRICKLE------------------

// /// returns true if the heap is empty
// template <typename T, typename TComparator, typename PComparator, typename Hasher >
// bool Heap<T,TComparator,PComparator,Hasher>::empty() const
// {
//     return store_.empty();
// }





// #endif


#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename TComparator = std::less<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    std::pair<double, T> const & top() const;

    /// Removes the top element
    void pop();
    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

private:
    /// Add whatever helper functions you need below
    void bubble(int index);
    void trickle(int index);




    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

//---------------PUSH/BUBBLE-----------------
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    //implement this
  store_.push_back(std::make_pair(priority, item));
  
  keyToLocation_.insert(std::make_pair(item, store_.size() -1));
  bubble(store_.size()-1); 

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator, PComparator, Hasher>::bubble(int index)
{
  if(index == 0)
  {
    return;
  }
  int parent = floor((index-1)/m_);
  while(parent >= 0 && c_(store_[index].first, store_[parent].first))
  {
    iter_swap(store_.begin() + parent, store_.begin()+index);
    keyToLocation_[store_[index].second] = parent;
    keyToLocation_[store_[parent].second] = index;
    index = parent;
    floor(parent = (index-1)/m_);
  }
}
//---------------PUSH/BUBBLE------------------


template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    int index = keyToLocation_[item];
    if(store_[index].first > priority)
    {
        store_[index].first = priority;
        bubble(index); 
    }
    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.



}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
std::pair<double, T> const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    return store_.at(0);

}

//---------------POP/TRICKLE------------------
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }

    // iter_swap(store_.begin(), store_.end()-1);
    // keyToLocation_[store_[0].second] = store_.size()-1;
    // keyToLocation_[store_[store_.size()-1].second] = 0;
    // store_.pop_back();
    // keyToLocation_.erase(store_[store_.size()-1].second);
    // trickle(0);


    // cout << store_[0].second << " Simval:" << store_[0].first << endl;
    // std::pair<double, std::string> node = store_.front();
    // store_[0] = store_.back();
    
    // store_.pop_back();
    // trickle(0);

    //typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it = keyToLocation_.find(node.second);
    // cout << "Size of keytolocation = " << keyToLocation_.size() << endl;
    // cout << store_[0].second << " Simval:" << store_[0].first << endl;
    //keyToLocation_.erase(it);

    store_[0] = store_.back();
    keyToLocation_.erase(store_[store_.size()-1].second);
    store_.pop_back();
    trickle(0);


}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickle(int index)
{
  int length = (int)store_.size();
  if(index >= length)
  {
    return;
  }
  int child = m_*index+1;
  int smallestChild = child;
  if(length < m_)
  {
    for(int i = 1; i <length - 1; i++)
    {
        if(c_(store_[child+i].first, store_[smallestChild].first) )
        {
            smallestChild = child + i;
        }
    }
  }
  if (c_(store_[smallestChild].first, store_[index].first) )
  {
    iter_swap(store_.begin() + smallestChild, store_.begin() + index);
    keyToLocation_[store_[index].second] = smallestChild;
    keyToLocation_[store_[smallestChild].second] = index;
  }
  else
  {
    if(smallestChild < length)
    {
        for(int i = 1; i < m_; i++)
        {
            if(c_(store_[child+i].first, store_[smallestChild].first))
            {
                smallestChild = child+i;
            }
        }
    }
    if(smallestChild < length)
    {
        if(c_(store_[smallestChild].first, store_[index].first))
        {
            iter_swap(store_.begin() + smallestChild, store_.begin() + index);
            keyToLocation_[store_[index].second] = smallestChild;
            keyToLocation_[store_[smallestChild].second] = index;
            trickle(smallestChild);
        }
    }
  }

  // for(int i = m_*index + 1; i <= m_*index + m_; i++)
  // {
  //   if (i < store_.size())
  //   {
  //     if(c_(store_.at(i).first, store_.at(smallestChild).first))
  //     {
  //       smallestChild = i;
  //     }
  //   }
  // }
  // if(smallestChild < index)
  // {
  //   iter_swap(store_.begin() + index, store_.begin() + smallestChild);
  //   keyToLocation_[store_[index].second] = smallestChild;
  //   keyToLocation_[store_[smallestChild].second] = index;
  //   trickle(smallestChild);
  // }
}
//---------------POP/TRICKLE------------------

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}





#endif