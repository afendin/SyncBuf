#include "SyncBuf.h"

SyncBuf::SyncBuf()
{

}

void SyncBuf::put(int data)
{
    m_lock.acquire();

    // For our data we create a container with corresponding
    // condition variable to be notified when our data
    // is retrieved by other thread
    Item *item = new Item;
    item->data = data;

    // We push our item in the actual buffer
    m_queue.push(item);

    // Singal just in case some thread is waiting for data
    m_emptyCV.signal();

    // Wait for other thread to retrieve our data
    item->cv.wait(&m_lock);

    // After we received a signal, our data is no longer needed
    delete item;

    m_lock.release();
}

int SyncBuf::get()
{
    m_lock.acquire();

    // If buffer is empty wait for someone to
    // put something in it
    while (m_queue.empty()){
        m_emptyCV.wait(&m_lock);
    }

    // Get first item from buffer
    Item *item = m_queue.front();

    // Read data
    int data = item->data;

    // Remove entry from buffer and signal to producer thread
    // that its data successfully retrieved
    m_queue.pop();
    item->cv.signal();

    m_lock.release();

    // Return data to the caller thread
    return data;
}