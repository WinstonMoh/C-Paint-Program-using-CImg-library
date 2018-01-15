// QNode.h
// queue node class template

template <typename T>
class QNode
   {
      public:
               QNode();
               QNode(T);

               T data;
               QNode *next;
   };

template <typename T>
QNode<T>::QNode()
   {
      next = NULL;
   }

template <typename T>
QNode<T>::QNode(T x)
   {
      data = x;
      next = NULL;
   }
