#include <iostream>
#include <string>

#include "p4.h"

using namespace std;

Person::Person()
{
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight)
{
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

PersonList::PersonList()
{
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

int PersonList::getSize()
{
    return size;
}

void PersonList::printByHeight(ostream &os)
{
    Person *curr = headHeightList;
    while (curr) {
        os << curr->first << " " << curr->last << ": height=" << curr->height << ", weight=" << curr->weight << endl;
        curr = curr->nextHeight;
    }
}

void PersonList::printByWeight(ostream &os)
{
    Person *curr = headWeightList;
    while (curr) {
        os << curr->first << " " << curr->last << ": height=" << curr->height << ", weight=" << curr->weight << endl;
        curr = curr->nextWeight;
    }
}

bool PersonList::exists(string first, string last)
{
    Person *curr = headHeightList;
    while (curr) {
        if (curr->first == first && curr->last == last) {
            return true;
        }
        curr = curr->nextHeight;
    }
    return false;
}

int PersonList::getHeight(string first, string last)
{
    Person *curr = headHeightList;
    while (curr) {
        if (curr->first == first && curr->last == last) {
            return curr->height;
        }
        curr = curr->nextHeight;
    }
    return -1;
}

int PersonList::getWeight(string first, string last)
{
    Person *curr = headWeightList;
    while (curr) {
        if (curr->first == first && curr->last == last) {
            return curr->weight;
        }
        curr = curr->nextWeight;
    }
    return -1;
}

bool PersonList::updateName(string first, string last, string newFirst, string newLast)
{
    Person *curr = headHeightList;
    while (curr) {
        if (curr->first == first && curr->last == last) {
            curr->first = newFirst;
            curr->last = newLast;
            return true;
        }
        curr = curr->nextHeight;
    }
    return false;
}

bool PersonList::add(string first, string last, int height, int weight)
{
    if (exists(first, last)) {
        return false;
    }

    Person *p = new Person(first, last, height, weight);

    // Insert into height list (descending order)
    if (headHeightList == nullptr) {
        headHeightList = p;
    } else {
        Person *curr = headHeightList;
        Person *prev = nullptr;
        bool inserted = false;

        while (curr) {
            // If p should come before curr in height list
            if (compare(p, curr) == p) {
                if (prev == nullptr) {
                    p->nextHeight = headHeightList;
                    headHeightList = p;
                } else {
                    p->nextHeight = curr;
                    prev->nextHeight = p;
                }
                inserted = true;
                break;
            }
            prev = curr;
            curr = curr->nextHeight;
        }

        if (!inserted) {
            prev->nextHeight = p;
        }
    }

    // Insert into weight list (ascending order)
    if (headWeightList == nullptr) {
        headWeightList = p;
    } else {
        Person *curr = headWeightList;
        Person *prev = nullptr;
        bool inserted = false;

        while (curr) {
            // For weight list: insert p before curr if p's weight is less,
            // or if weights are equal and p's height is less
            if (p->weight < curr->weight ||
                (p->weight == curr->weight && p->height < curr->height)) {
                if (prev == nullptr) {
                    p->nextWeight = headWeightList;
                    headWeightList = p;
                } else {
                    p->nextWeight = curr;
                    prev->nextWeight = p;
                }
                inserted = true;
                break;
            }
            prev = curr;
            curr = curr->nextWeight;
        }

        if (!inserted) {
            prev->nextWeight = p;
        }
    }

    size++;
    return true;
}

bool PersonList::remove(string first, string last)
{
    if (!exists(first, last)) {
        return false;
    }

    // Remove from height list
    Person *curr = headHeightList;
    Person *prev = nullptr;
    Person *toDelete = nullptr;

    while (curr) {
        if (curr->first == first && curr->last == last) {
            toDelete = curr;
            if (prev == nullptr) {
                headHeightList = curr->nextHeight;
            } else {
                prev->nextHeight = curr->nextHeight;
            }
            break;
        }
        prev = curr;
        curr = curr->nextHeight;
    }

    // Remove from weight list
    curr = headWeightList;
    prev = nullptr;

    while (curr) {
        if (curr->first == first && curr->last == last) {
            if (prev == nullptr) {
                headWeightList = curr->nextWeight;
            } else {
                prev->nextWeight = curr->nextWeight;
            }
            break;
        }
        prev = curr;
        curr = curr->nextWeight;
    }

    delete toDelete;
    size--;
    return true;
}

bool PersonList::updateHeight(string first, string last, int height)
{
    if (!exists(first, last)) {
        return false;
    }

    // Find the person and get their current weight
    Person *curr = headHeightList;
    int currentWeight = 0;
    while (curr) {
        if (curr->first == first && curr->last == last) {
            currentWeight = curr->weight;
            break;
        }
        curr = curr->nextHeight;
    }

    // Remove and re-add with new height
    remove(first, last);
    add(first, last, height, currentWeight);

    return true;
}

bool PersonList::updateWeight(string first, string last, int weight)
{
    if (!exists(first, last)) {
        return false;
    }

    // Find the person and get their current height
    Person *curr = headHeightList;
    int currentHeight = 0;
    while (curr) {
        if (curr->first == first && curr->last == last) {
            currentHeight = curr->height;
            break;
        }
        curr = curr->nextHeight;
    }

    // Remove and re-add with new weight
    remove(first, last);
    add(first, last, currentHeight, weight);

    return true;
}

PersonList::~PersonList()
{
    Person *curr = headHeightList;
    while (curr) {
        Person *temp = curr;
        curr = curr->nextHeight;
        delete temp;
    }
}

PersonList::PersonList(const PersonList &src)
{
    size = 0;
    headHeightList = nullptr;
    headWeightList = nullptr;

    Person *curr = src.headHeightList;
    while (curr) {
        add(curr->first, curr->last, curr->height, curr->weight);
        curr = curr->nextHeight;
    }
}

const PersonList &PersonList::operator=(const PersonList &src)
{
    if (this == &src) {
        return *this;
    }

    // Clear current list
    Person *curr = headHeightList;
    while (curr) {
        Person *temp = curr;
        curr = curr->nextHeight;
        delete temp;
    }

    size = 0;
    headHeightList = nullptr;
    headWeightList = nullptr;

    // Copy from source
    curr = src.headHeightList;
    while (curr) {
        add(curr->first, curr->last, curr->height, curr->weight);
        curr = curr->nextHeight;
    }

    return *this;
}

Person *PersonList::compare(Person *p1, Person *p2)
{
    // For height list: descending order by height, then descending by weight for ties
    if (p1->height > p2->height) {
        return p1;
    } else if (p1->height < p2->height) {
        return p2;
    } else {
        // Heights are equal, use weight as tiebreaker (heavier first)
        if (p1->weight > p2->weight) {
            return p1;
        } else {
            return p2;
        }
    }
}
