#include <queue>

#include "3rdparty/Lock.h"
#include "3rdparty/CV.h"

using namespace std;

struct Item
{
    // Let's assume we want to pass integer number
    int data;

    // Condition Variable on which we will signal,
    // when data will be retrieved
    CV cv;
};

class SyncBuf
{
public:
    SyncBuf();

    void put(int data);
    int get();

private:
    queue<Item*> m_queue;
    Lock m_lock;
    CV m_emptyCV;
};