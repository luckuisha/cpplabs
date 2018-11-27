#include <galaxy-explorer/AsteroidList.hpp>


AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
	this->data = new Asteroid(a);
}

AsteroidListItem::~AsteroidListItem() {
    delete data;//Ali
}

AsteroidList::AsteroidList()
{
  //  head.setNext(nullptr);
    /**
	 * Creates an empty list
	 */
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
    const AsteroidListItem * ptr = src.head.getNext();
    AsteroidListItem * last = nullptr;
    AsteroidListItem * nptr = nullptr;
    while (ptr != nullptr)
    {
        nptr = new AsteroidListItem(ptr->getData());
        if (last == nullptr)
            head.setNext(nptr);
        else last->setNext(nptr);
        ptr = ptr->getNext();
        last=nptr;
        if (ptr == nullptr)
            last->setNext(nullptr);
    }
    
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
    
    /**
	 * Creates an independent copy of `src`. This means that there is NO shared data or pointers.
	 * The functions in this class are listed in a suggested order of implementation,
	 * except for this one and the destructor (because you should put all your constructors together).
	 */
    
    
}

AsteroidList::~AsteroidList() {
    this->clear();
//    AsteroidListItem * ptr = head.getNext();
//    AsteroidListItem * optr;
//    while (ptr != nullptr)
//    {
//        optr = ptr;
//        ptr = ptr -> getNext();
//        delete optr;
//    }
//    head.setNext(nullptr);

    /**
	 * Frees all memory associated with this list
	 * The functions in this class are listed in a suggested order of implementation,
	 * except for this one and the copy constructor (because you should put all your constructors together).
	 */
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
}

void AsteroidList::pushFront(Asteroid e) {
        AsteroidListItem * nptr = head.getNext();
        head.setNext(new AsteroidListItem(e));
        head.getNext()->setNext(nptr);
    /**
	 * Add an asteroid at the beginning of this list
	 */
}

Asteroid& AsteroidList::front() {
        
    if (head.getNext() != nullptr)
        return head.getNext()->getData();
    else
        return *(Asteroid*)nullptr;
        /**
	 * Return a reference to the first asteroid
	 * This function may have ANY BEHAVIOUR if this list is empty
	 */
}

const Asteroid& AsteroidList::front() const {
    if (head.getNext() != nullptr)
        return head.getNext()->getData();
    else
        return *(const Asteroid*)nullptr;
}

bool AsteroidList::isEmpty() const {
    if (head.getNext()== nullptr)
	return true;
    return false;
}

int AsteroidList::size() const {
    int cnt=0;
    const AsteroidListItem * ptr = head.getNext();
    while (ptr != nullptr)
    {
        ptr = ptr->getNext();
        cnt++;
    }
	return cnt;
}

AsteroidListItem* AsteroidList::beforeBegin() {
//    if (head.getNext() == nullptr)
//	return nullptr;
//    return nullptr;
    return &head;
        /**
	 * Return an item corresponding to the position immediately before the first asteroid.
	 * If this list is empty, a value equal to `beforeEnd()` must be returned.
	 * If this list is in a valid state, this function must always succeed.
	 */
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
//    if (head.getNext() == nullptr)
//	return nullptr;
//    return nullptr;
    return &head;
}

AsteroidListItem* AsteroidList::begin() {
    if (head.getNext() == nullptr)
        return nullptr;
    return head.getNext();
        /**
	 * Return an item corresponding to the first asteroid.
	 * If this list is empty, a value equal to `end()` must be returned.
	 * If this list is in a valid state, this function must always succeed.
	 */
}

const AsteroidListItem* AsteroidList::begin() const {
    if (head.getNext() == nullptr)
        return nullptr;
    return head.getNext();
     
}

AsteroidListItem* AsteroidList::beforeEnd() {
    if (head.getNext() == nullptr)
        return &head;
    AsteroidListItem * ptr = head.getNext();
    AsteroidListItem * last = head.getNext();
    while (ptr != nullptr)
    {
        last = ptr;
        ptr = ptr -> getNext();
    }
        
    return last; 
        
        /**
	 * Return an item corresponding to the position of the last asteroid.
	 * If this list is empty, a value equal to `beforeBegin()` must be returned.
	 * If this list is in a valid state, this function must always succeed.
	 */
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    if (head.getNext() == nullptr)
        return &head;
    const AsteroidListItem * ptr = head.getNext();
    const AsteroidListItem * last = head.getNext();
    while (ptr != nullptr)
    {
        last = ptr;
        ptr = ptr -> getNext();
    }
        
    return last; 
        
}

AsteroidListItem* AsteroidList::end() {
//    if (head.getNext() == nullptr)
//        return nullptr;
//    AsteroidListItem * ptr = head.getNext();
//    while (ptr != nullptr)
//    {
//        ptr = ptr -> getNext();
//    }
//        
//    return ptr; 
    return nullptr;
        /**
	 * Return an item corresponding to the position immediately after the last asteroid.
	 * If this list is empty, a value equal to `begin()` must be returned.
	 * If this list is in a valid state, this function must always succeed.
	 */
}

const AsteroidListItem* AsteroidList::end() const {
//    if (head.getNext() == nullptr)
//        return nullptr;
//    const AsteroidListItem * ptr = head.getNext();
//    while (ptr != nullptr)
//    {
//        ptr = ptr -> getNext();
//    }
//        
//    return ptr; 
    return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem * ptr = head.getNext();
    AsteroidListItem * nptr = head.getNext();
    ptr = prev;
    nptr = prev->getNext();
    prev->setNext(new AsteroidListItem(e));
    ptr = prev->getNext();
    ptr->setNext(nptr);
    return ptr;
        /**
	 * Add a single asteroid to this list, in the position immediately after `prev`.
	 * returns the item that was inserted
	 */
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    AsteroidListItem * last = head.getNext();
    const AsteroidListItem * other = others.head.getNext();
    if (other == nullptr)
        return prev;
    
    last = prev->getNext();
    while (other != nullptr)
    {
        prev->setNext(new AsteroidListItem(other->getData()));
        other = other->getNext();
        prev = prev->getNext();
    }
    prev->setNext(last);
    return prev;

        /**
	 * Add independent copies of the entities in `others` to this list, placed immediately after `insertion_point`,
	 * in the same order as `others`.
	 * Returns the last item that was inserted, or `insertion_point' if `others' is empty.
	 */
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    AsteroidListItem * ptr = head.getNext();
    AsteroidListItem * temp = head.getNext();
    prev = temp;
    temp = temp->getNext();
    if (temp == nullptr) return end();
    ptr = temp->getNext();
    delete temp;
    prev->setNext(ptr);
    if (ptr == nullptr)
        return end();
    return ptr;
        /**
	 * Given a position in this list, delete the following asteroid.
	 * Returns the list item that followed the erased item, or end() if there wasn't one.
	 * This function may have ANY BEHAVIOUR if there is no asteroid after `prev`.
	 */
}

void AsteroidList::clear() {
    AsteroidListItem * ptr = head.getNext();
    AsteroidListItem * optr;
    while (ptr != nullptr)
    {
        optr = ptr;
        ptr = ptr -> getNext();
        delete optr;
    }
    head.setNext(nullptr);
    return;
    /**
	 * Make this list empty, free all nodes.
	 */
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
     this->clear();
//    AsteroidListItem * ptr = head.getNext();
//    AsteroidListItem * optr;
//    while (ptr != nullptr)
//    {
//        optr = ptr;
//        ptr = ptr -> getNext();
//        delete optr;
//    }
    const AsteroidListItem * cptr = src.head.getNext();
    AsteroidListItem * last = nullptr;
    AsteroidListItem * nptr = nullptr;
    while (cptr != nullptr)
    {
        nptr = new AsteroidListItem(cptr->getData());
        if (last == nullptr)
            head.setNext(nptr);
        else last->setNext(nptr);
        cptr = cptr->getNext();
        last=nptr;
    }
    return (*this);
        /**
	 * Makes this list an independent copy of `src`. This means that there is NO shared data or pointers.
	 */
}
