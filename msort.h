#include "product.h"
#include "review.h"

#ifndef MSORT_H
#define MSORT_H

#include <iostream>
#include <string>
#include <vector>


struct comp {
    bool operator()(const int left, const int right) 
    { 
      return left > right; 
    }
 };

struct productName {
    bool operator()(const Product* left, const Product* right) 
    { 
      return left->getName() < right->getName(); 
    }
 };

struct averageRating {
    bool operator()(const Product* left, const Product* right) 
    { 
      return left->getAverageRating() > right->getAverageRating(); 
    }
 };

 struct reviewDate {
    bool operator()(const Review* left, const Review* right) 
    { 
      return left->date < right->date; 
    }
 };

 struct prodRecommend {
    bool operator()(const std::pair<string, double> left, const std::pair<string, double> right) {
        if (left.second == right.second) {
            return left.first <right.first;
        }
        return left.second > right.second;
    } 
 };

template <class T, class Comparator>
void mergeHelper(std::vector<T> &myArray, int s1, int j1, int s2, int j2, Comparator comp) {
    std::vector<T> a(myArray);
    int index = s1;
    while(s1 <= j1 && s2 <= j2) 
    {
        if (comp(a[s1], a[s2])) 
        {
            myArray[index++] = a[s1++];
        } 
        else 
        {
            myArray[index++] = a[s2++];
        }
    }
    while(s1 <= j1) 
    {
        myArray[index++] = a[s1++];
    }
    while(s2 <= j2) 
    {
        myArray[index++] = a[s2++];
    }
}


template <class T, class Comparator>
void mergeSortHelper(std::vector<T> &myArray, int index1, int index2, Comparator comp) {
    if (index1 >= index2) 
    {
        return;
    }
    int midIndex = (index1+index2) / 2;
    mergeSortHelper(myArray, index1, midIndex, comp);
    mergeSortHelper(myArray, midIndex+1, index2, comp);

    mergeHelper(myArray, index1, midIndex, midIndex+1, index2, comp);
}


template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, Comparator comp) {
    mergeSortHelper(myArray, 0, myArray.size() - 1, comp);
}


#endif