#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

template<typename T>
class Queue {
	public:
	Queue();
	~Queue();

	bool isEmpty() const;
	int size() const;

	//Enqueue: Items are added to the back of the queue
	void enqueue(const T& newItem);
	//Dequeue: Items are removed from the front of the queue
	void dequeue();
	//Get Front: Take a look at the first item
	void getFront(T& queueTop) const;
	void getItem(T& ret, int index) const;

	private:
    struct QueueNode {
        T item;
        QueueNode *next;
        };
    int _size;
    QueueNode* _headNode;
	QueueNode* _lastNode;
};

#endif // QUEUE_H_INCLUDED
