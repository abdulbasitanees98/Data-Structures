/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 4
*/
using namespace std;

enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
enum LocationStatus { OCCUPIED, EMPTY, DELETED };

class HashTable
{
private:
    int* table;
    LocationStatus* status;
    int hashTableSize;
    CollisionStrategy strategy;
    int curSize;
public:
    HashTable( const int tableSize, const CollisionStrategy option );
    ~HashTable();
    bool insert( const int item );
    bool remove( const int item );
    bool search( const int item, int& numProbes );
    void display();
    void analyze( int& numSuccProbes, int& numUnsuccProbes );
    double getLoadFactor();
};
int hash2Func(int num);
