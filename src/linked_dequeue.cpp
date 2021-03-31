#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedDequeue::Enqueue(Element e) {
  // TODO: напишите здесь свой код ...
    if(size_ == 0){
        front_ = new DoublyNode(e, nullptr, nullptr);
        back_ = front_;
    }else {
        back_->next = new DoublyNode(e, back_, nullptr);
        back_ = back_->next;
    }
    size_++;
}

void LinkedDequeue::EnqueueFront(Element e) {
    if(size_ == 0){
        front_ = new DoublyNode(e, nullptr, nullptr);
        back_ = front_;
    }else {
        front_->previous = new DoublyNode(e, nullptr, front_);
        front_ = front_->previous;
    }
    size_++;
}

void LinkedDequeue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }
    DoublyNode *d = front_;

    if (size_ == 1) {
        delete d;
        front_ = nullptr;
        back_ = nullptr;
    } else {

        front_ = front_->next;
        front_->previous = nullptr;
        delete d;
    }
    size_--;
}

void LinkedDequeue::DequeueBack() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }
    DoublyNode *dn = back_;
    if(size_ == 1){
        delete dn;
        front_ = nullptr;
        back_ = nullptr;
    }else {
        back_ = back_->previous;
        back_->next = nullptr;
        delete dn;
    }
    size_--;
}

void LinkedDequeue::Clear() {
    while (size_ != 0) {
        Dequeue();
    }
    delete front_;
    front_ = nullptr;
    delete back_;
    back_ = nullptr;
}

// === РЕАЛИЗОВАНО ===

LinkedDequeue::~LinkedDequeue() {
  Clear();
}

std::optional<Element> LinkedDequeue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedDequeue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedDequeue::IsEmpty() const {
  return size_ == 0;
}

int LinkedDequeue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis
