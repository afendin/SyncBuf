### Exercise 5.16

A synchronous buffer is one where the thread placing an item into the buffer waits until the thread retrieving the item has gotten it, and only then returns. Implement a synchronous buffer using Mesa-style locks and condition variables, with the following routines:

```c++
// Put item into the buffer and return only once the item
// has been retrieved by some thread.
SyncBuf::put(item);
// Wait until there is an item in the buffer, and then return it.
SyncBuf::get();
```

Any number of threads can concurrently call SyncBuf::get and SyncBuf::put; the module pairs off puts and gets. Each item should be returned exactly once, and there should be no unnecessary waiting. Once the item is retrieved, the thread that called put with the item should return.