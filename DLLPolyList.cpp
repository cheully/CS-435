#include "DLLPolyList.h"

DLLPolyList::DLLPolyList() {
    this->head = NULL;
    this->tail = NULL;
}

DLLPolyList::~DLLPolyList() {
    if((head == NULL) && (tail == NULL)){
        delete this->head;
        delete this->tail;
    }

    while(head != tail){
        DLLNode *temp = head;
        head = head->getNext();
        delete temp;
    }
    delete head;
    delete tail;
}

void DLLPolyList::insertTerm(int c, int i, int j) {
    if(c == 0)
        return;

    DLLNode *node = new DLLNode(c, i, j);

    if((head == NULL) && (tail == NULL)){
        head = node;
        tail = node;
        return;
    }

    if(head == tail){
       if((head->getI() < node->getI()) || (head->getI() == node->getI() && head->getJ() < node->getJ()) ){
            node->setNext(head);
            head->setPrev(node);
            head = node;

        } else if(head->getI() == node->getI() && head->getJ() == node->getJ()){
            int newC;
            newC = head->getC() + node->getC();

            if(newC != 0){
                DLLNode *newNode = new DLLNode(newC, head->getI(), head->getJ());
                delete head, tail;
                head = newNode;
                tail = newNode;
            } else {
                delete head, tail;
                head = NULL; tail = NULL;
            }
        } else {
            head->setNext(node);
            node->setPrev(head);
            tail = node;
        }
        return;
    }

    DLLNode *tpHead = head;
    DLLNode *tpTail = tail;

    while(tpHead != tpTail){

        if(tpHead->getI() < node->getI() || (tpHead->getI() == node->getI() && tpHead->getJ() < node->getJ())){

            if(tpHead == head) {
                node->setNext(head);
                tpHead->setPrev(node);
                head = node;
                return;
            }

            node->setNext(tpHead);
            node->setPrev(tpHead->getPrev());
            tpHead->setPrev(node);
            node->getPrev()->setNext(node);

            return;

        } else if(tpHead->getI() == node->getI() && tpHead->getJ() == node->getJ()){

            int newC;
            newC = tpHead->getC() + node->getC();
            DLLNode *newNode = new DLLNode(newC, node->getI(), node->getJ());

            if(tpHead == head){
                if(newC != 0){
                    newNode->setNext(tpHead->getNext());
                    tpHead->getNext()->setPrev(newNode);
                    delete head;

                    head = newNode;

                } else {
                    delete head;
                    head = tpHead->getNext();
                }
                return;
            }

            if(newC != 0){

                newNode->setNext(tpHead->getNext());
                newNode->setPrev(tpHead->getPrev());
                newNode->getNext()->setPrev(newNode);
                newNode->getPrev()->setNext(newNode);

                delete tpHead;

            } else {

                tpHead->getNext()->setPrev(tpHead->getPrev());
                tpHead->getPrev()->setNext(tpHead->getNext());
                delete tpHead;
            }
            return;
        }

        tpHead = tpHead->getNext();
    }

    if(tpHead->getI() < node->getI() || (tpHead->getI() == node->getI() && tpHead->getJ() < node->getJ()) ){

        node->setNext(tpTail);
        node->setPrev(tpTail->getPrev());
        tpTail->setPrev(node);
        node->getPrev()->setNext(node);

    } else if(tpTail->getI() == node->getI() && tpTail->getJ() == node->getJ()){
        int newC;
        newC = tpTail->getC() + node->getC();

        if(newC != 0){
            DLLNode *newNode = new DLLNode(newC, node->getI(), node->getJ());
            newNode->setPrev(tpTail->getPrev());
            newNode->getPrev()->setNext(newNode);

            delete tail;
            tail = newNode;

        } else {
            tpTail->getPrev()->setNext(NULL);

            delete tail;
            tail = tpTail->getPrev();
        }

    } else {
        tail->setNext(node);
        node->setPrev(tail);
        tail = node;
        return;
    }

}

Position* DLLPolyList::first() {
    return head;
}

Position* DLLPolyList::last() {
    return tail;
}

Position* DLLPolyList::before(Position * p) {
    DLLNode * node = dynamic_cast<DLLNode*>(p);

    if(head == node){
        cout << "\nError: No accessible element before this point!\n";
        return node;
    }

    return node->getPrev();
}

Position* DLLPolyList::after(Position * p) {
    DLLNode * node = dynamic_cast<DLLNode*>(p);

    if(tail == node){
        cout << "\nError: No accessible element after this point!\n";
        return node;
    }

    return node->getNext();
}

bool DLLPolyList::isFirst(Position * p) {
    DLLNode * node = dynamic_cast<DLLNode*>(p);
    if(node == head)
        return true;
    else
        return false;
}

bool DLLPolyList::isLast(Position * p) {
    DLLNode * node = dynamic_cast<DLLNode*>(p);

    if(node == tail)
        return true;
    else
        return false;
}

bool DLLPolyList::isEmpty() {
    if((head == NULL) && (tail == NULL))
        return true;
    else
        return false;
}

int DLLPolyList::size() {
    if((head == NULL) && (tail == NULL))
        return 0;

    DLLNode *temp = head;
    int DLLPolyListSize = 0;

    while(temp != NULL){
        ++DLLPolyListSize;
        temp = temp->getNext();
    }
    return DLLPolyListSize;
}


