#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>

#include <vector>
#include <cstddef>
#include <utility>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below

    std::vector<T> items_;
    int m_;
    PComparator comp_;




};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : m_(m), comp_(c)
{
  if(m < 2) {
    throw std::invalid_argument("Heap must have at least two children");
  }
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return items_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return items_.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  items_.push_back(item);
  size_t current = items_.size() - 1;

  while(current > 0) {
    size_t parent = (current - 1) / m_;

    if(comp_(items_[current], items_[parent])) {
      std::swap(items_[current], items_[parent]);
      current = parent;
    }
    else {
      break;
    }
  }
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Cannot access top of an empty heap");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return items_[0];



}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Cannot pop an empty heap");

  }
  items_[0] = items_.back();
  items_.pop_back();

  if(empty()) {
    return;
  }

  size_t current = 0;

  while(true) {
    size_t firstChild = current * m_ + 1;

    if(firstChild >= items_.size()) {
      break;
    }

    size_t bestChild = firstChild;

    for(int i = 1; i < m_; ++i) {
      size_t child = firstChild + i;

      if(child >= items_.size()) {
        break;
      }

      if(comp_(items_[child], items_[bestChild])) {
        bestChild = child;
      }
    }

    if(comp_(items_[bestChild], items_[current])) {
      std::swap(items_[current], items_[bestChild]);
      current = bestChild;
    }
    else {
      break;
    }
  }



}



#endif

