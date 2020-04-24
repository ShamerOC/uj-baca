// Krzysztof Wydrzynski
#include <iostream>

struct LinkedList;

struct Rope {
    char a1, a2, a3;
    LinkedList* beadList;
};

struct Bead {
    int id;
    LinkedList* attachmentList;
};

struct Attachment {
    char a1, a2, a3;
    int id;
};

struct LinkedList {
    struct RopeList {
        RopeList* previous;
        Rope* rope;
        RopeList* next;
    };

    struct BeadList {
        BeadList* previous;
        Bead* bead;
        BeadList* next;
    };

    struct AttachmentList {
        AttachmentList* previous;
        Attachment* attachment;
        AttachmentList* next;
    };

    RopeList* ropeListFirstElement;
    RopeList* ropeListLastElement;

    BeadList* beadListFirstElement;
    BeadList* beadListLastElement;

    AttachmentList* attachmentListFirstElement;
    AttachmentList* attachmentListLastElement;


    LinkedList () {
        ropeListFirstElement = NULL;
        ropeListLastElement = NULL;

        beadListFirstElement = NULL;
        beadListLastElement = NULL;

        attachmentListFirstElement = NULL;
        attachmentListLastElement = NULL;
    }

    bool find (Rope* rope) {
        RopeList* element = ropeListFirstElement;
            while (element != NULL) {
                if (element->rope == rope) return true;
                element = element->next;
            }
        return false;
    }

    bool find (Bead* bead) {
        BeadList* element = beadListFirstElement;
            while (element != NULL) {
                if (element->bead == bead) return true;
                element = element->next;
            }
        return false;
    }

    bool find (Attachment* attachment) {
        AttachmentList* element = attachmentListFirstElement;
            while (element != NULL) {
                if (element->attachment == attachment) return true;
                element = element->next;
            }
        return false;
    }

    Rope* find (char a1, char a2, char a3) {
        RopeList* element = ropeListFirstElement;
            while (element != NULL) {
                if (element->rope->a1 == a1 && element->rope->a2 == a2 && element->rope->a3 == a3) return element->rope;
                element = element->next;
            }
        return NULL;
    }

    Bead* find (int id) {
        BeadList* element = beadListFirstElement;
            while (element != NULL) {
                if (element->bead->id == id) return element->bead;
                element = element->next;
            }
        return NULL;
    }

    Attachment* find (char a1, char a2, char a3, int id) {
        AttachmentList* element = attachmentListFirstElement;
            while (element != NULL) {
                if (element->attachment->a1 == a1 && element->attachment->a2 == a2 && element->attachment->a3 == a3 && element->attachment->id == id) return element->attachment;
                element = element->next;
            }
        return NULL;
    }

    RopeList* findAndReturnList (Rope* rope) {
        RopeList* element = ropeListFirstElement;
            while (element != NULL) {
                if (element->rope == rope) return element;
                element = element->next;
            }
        return NULL;
    }

    BeadList* findAndReturnList (Bead* bead) {
        BeadList* element = beadListFirstElement;
            while (element != NULL) {
                if (element->bead == bead) return element;
                element = element->next;
            }
        return NULL;
    }

    AttachmentList* findAndReturnList (Attachment* attachment) {
        AttachmentList* element = attachmentListFirstElement;
            while (element != NULL) {
                if (element->attachment == attachment) return element;
                element = element->next;
            }
        return NULL;
    }

    void removeAttachments() {
        AttachmentList* element = attachmentListFirstElement;
            while (element != NULL) {
                AttachmentList* nextElement = element->next;
                remove(element->attachment);
                element = nextElement;
            }
    }

    void removeBeads() {
        BeadList* element = beadListFirstElement;
            while (element != NULL) {
                BeadList* nextElement = element->next;
                remove(element->bead);
                element = nextElement;
            }
    }

    RopeList* considerInsertingAfter (RopeList* ropeList) {
        if (ropeListFirstElement == ropeList) return NULL;
        RopeList* element = ropeListFirstElement;
        while (element != ropeList) {
            Rope* currentRope = element->rope;
            Rope* myRope = ropeList->rope;
            if ((int)currentRope->a1 > (int)myRope->a1) return element->previous;
            else if ((int)currentRope->a1 == (int)myRope->a1 && (int)currentRope->a2 > (int)myRope->a2) {
                return element->previous;
            }
            else if ((int)currentRope->a1 == (int)myRope->a1 && (int)currentRope->a2 == (int)myRope->a2 && (int)currentRope->a3 > (int)myRope->a3) {
                return element->previous;
            }
            element = element->next;
        }
        return ropeList;
    }

    void insertAfter (RopeList* current, RopeList* where) {
        if (current == where) {
            return;
        }
        if (where == NULL) {
            if (current == ropeListFirstElement) return;
            ropeListLastElement = current->previous;
            current->next = ropeListFirstElement;
            current->previous->next = NULL;
            current->previous = NULL;
            ropeListFirstElement->previous = current;
            if (ropeListLastElement == current) ropeListLastElement = ropeListFirstElement;
            ropeListFirstElement = current;
            return;
        }
        if (current == ropeListLastElement) {
            ropeListLastElement = where->next;
        }
        ropeListLastElement = current->previous;
        RopeList* next = where->next;
        next->previous = current;
        where->next = current;
        current->previous->next = NULL;
        current->previous = where;
        current->next = next;
    }

    BeadList* considerInsertingAfter (BeadList* beadList) {
        if (beadListFirstElement == beadList) return NULL;
        BeadList* element = beadListFirstElement;
        while (element != beadList) {
            Bead* currentBead = element->bead;
            Bead* myBead = beadList->bead;
            if (myBead->id < currentBead->id) return element->previous;
            element = element->next;
        }
        return beadList;
    }

    void insertAfter (BeadList* current, BeadList* where) {
        if (current == where) return;
        if (current == beadListFirstElement) return;
        if (where == NULL) {
            beadListLastElement = current->previous;
            current->next = beadListFirstElement;
            current->previous->next = NULL;
            current->previous = NULL;
            beadListFirstElement->previous = current;
            if (beadListLastElement == current) beadListLastElement =  beadListFirstElement;
            beadListFirstElement = current;
            return;
        }
        if (current == beadListLastElement) beadListLastElement = where->next;
        beadListLastElement = current->previous;
        BeadList* next = where->next;
        next->previous = current;
        where->next = current;
        current->previous->next = NULL;
        current->previous = where;
        current->next = next;
    }

    AttachmentList* considerInsertingAfter (AttachmentList* attachmentList) {
        if (attachmentListFirstElement == attachmentList) return NULL;
        AttachmentList* element = attachmentListFirstElement;
        while (element != attachmentList) {
            Attachment* currentAttachment = element->attachment;
            Attachment* myAttachment = attachmentList->attachment;
            if ((int)currentAttachment->a1 > (int)myAttachment->a1) return element->previous;
            else if ((int)currentAttachment->a1 == (int)myAttachment->a1 && (int)currentAttachment->a2 > (int)myAttachment->a2) return element->previous;
            else if ((int)currentAttachment->a1 == (int)myAttachment->a1 && (int)currentAttachment->a2 == (int)myAttachment->a2 && (int)currentAttachment->a3 > (int)myAttachment->a3) return element->previous;
            else if ((int)currentAttachment->a1 == (int)myAttachment->a1 && (int)currentAttachment->a2 == (int)myAttachment->a2 && (int)currentAttachment->a3 == (int)myAttachment->a3 && currentAttachment->id > myAttachment->id) return element->previous;
            element = element->next;
        }
        return attachmentList;
    }

    void insertAfter (AttachmentList* current, AttachmentList* where) {
        if (current == where) return;
        if (where == NULL) {
            if (current == attachmentListFirstElement) return;
            attachmentListLastElement = current->previous;
            current->next = attachmentListFirstElement;
            current->previous->next = NULL;
            current->previous = NULL;
            attachmentListFirstElement->previous = current;
            if (attachmentListLastElement == current) attachmentListLastElement =  attachmentListFirstElement;
            attachmentListFirstElement = current;
            return;
        }
        if (current == attachmentListLastElement) attachmentListLastElement = where->next;
        attachmentListLastElement = current->previous;
        AttachmentList* next = where->next;
        next->previous = current;
        where->next = current;
        current->previous->next = NULL;
        current->previous = where;
        current->next = next;
    }

    void add (Rope* rope) {
        if (find(rope)) return;
        RopeList* newRopeList = new RopeList;
        newRopeList->previous = ropeListLastElement;
        newRopeList->rope = rope;
        newRopeList->next = NULL;

        if (ropeListFirstElement == NULL) {
            ropeListFirstElement = newRopeList;
        }
        else {
            ropeListLastElement->next = newRopeList;
        }
        ropeListLastElement = newRopeList;
        RopeList* previous = considerInsertingAfter(newRopeList);
        insertAfter(newRopeList, previous);
    }

    void add (Bead* bead) {
        if (find(bead)) return;
        BeadList* newBeadList = new BeadList;
        newBeadList->previous = beadListLastElement;
        newBeadList->bead = bead;
        newBeadList->next = NULL;

        if (beadListFirstElement == NULL) {
            beadListFirstElement = newBeadList;
        }
        else {
            beadListLastElement->next = newBeadList;
        }
        beadListLastElement = newBeadList;
        BeadList* previous = considerInsertingAfter(newBeadList);
        insertAfter(newBeadList, previous);
    }

    void add (Attachment* attachment) {
        if (find(attachment)) return;
        AttachmentList* newAttachmentList = new AttachmentList;
        newAttachmentList->previous = attachmentListLastElement;
        newAttachmentList->attachment = attachment;
        newAttachmentList->next = NULL;

        if (attachmentListFirstElement == NULL) {
            attachmentListFirstElement = newAttachmentList;
        }
        else {
            attachmentListLastElement->next = newAttachmentList;
        }
        attachmentListLastElement = newAttachmentList;
        AttachmentList* previous = considerInsertingAfter(newAttachmentList);
        insertAfter(newAttachmentList, previous);
    }

    void removeFromList (Bead* bead) {
        if (bead == NULL) return;
        BeadList* beadList = findAndReturnList(bead);
        if (beadList == NULL) return;
        BeadList* nextBead = beadList->next;
        BeadList* previousBead = beadList->previous;
        BeadList* element = beadListFirstElement;
        delete beadList;
        if (nextBead == NULL && previousBead == NULL) {
            beadListFirstElement = NULL;
            beadListLastElement = NULL;
            return;
        }
        if (nextBead != NULL && previousBead == NULL) {
            nextBead->previous = NULL;
            beadListFirstElement = nextBead;
            return;
        }
        if (nextBead == NULL && previousBead != NULL) {
            previousBead->next = NULL;
            beadListLastElement = previousBead;
            return;
        }
        nextBead->previous = previousBead;
        previousBead->next = nextBead;
    }

    void remove (Rope* rope) {
        if (rope == NULL) return;
        RopeList* ropeList = findAndReturnList(rope);
        if (ropeList == NULL) return;
        rope->beadList->removeBeads();
        RopeList* nextRope = ropeList->next;
        RopeList* previousRope = ropeList->previous;
        delete rope->beadList;
        delete rope;
        delete ropeList;
        if (nextRope == NULL && previousRope != NULL) {
            previousRope->next = NULL;
            ropeListLastElement = previousRope;
            return;
        }
        if (previousRope == NULL && nextRope == NULL) {
            ropeListFirstElement = NULL;
            ropeListLastElement = NULL;
            return;
        }
        if (previousRope == NULL && nextRope != NULL) {
            nextRope->previous = NULL;
            ropeListFirstElement = nextRope;
            return;
        }

        nextRope->previous = previousRope;
        previousRope->next = nextRope;
    }

    void remove (Bead* bead) {
        if (bead == NULL) return;
        BeadList* beadList = findAndReturnList(bead);
        if (beadList == NULL) return;
        bead->attachmentList->removeAttachments();
        BeadList* nextBead = beadList->next;
        BeadList* previousBead = beadList->previous;
        delete bead->attachmentList;
        delete bead;
        delete beadList;
        if (nextBead == NULL && previousBead != NULL) {
            previousBead->next = NULL;
            beadListLastElement = previousBead;
            return;
        } 
        if (previousBead == NULL && nextBead != NULL) {
            nextBead->previous = NULL;
            beadListFirstElement = nextBead;
            return;
        }
        if (previousBead == NULL && nextBead == NULL) {
            beadListFirstElement = NULL;
            beadListLastElement = NULL;
            return;
        } 
        nextBead->previous = previousBead;
        previousBead->next = nextBead;
    }

    void remove (Attachment* attachment) {
        if (attachment == NULL) return;
        AttachmentList* attachmentList = findAndReturnList(attachment);
        if (attachmentList == NULL) return;
        AttachmentList* nextAttachment = attachmentList->next;
        AttachmentList* previousAttachment = attachmentList->previous;
        delete attachmentList;
        delete attachment;
        if (nextAttachment == NULL && previousAttachment != NULL) {
            previousAttachment->next = NULL;
            attachmentListLastElement = previousAttachment;
            return;
        } 
        if (previousAttachment == NULL && nextAttachment != NULL) {
            nextAttachment->previous = NULL;
            attachmentListFirstElement = nextAttachment;
            return;
        }
        if (previousAttachment == NULL && nextAttachment == NULL) {
            attachmentListFirstElement = NULL;
            attachmentListLastElement = NULL;
            return;
        } 
        nextAttachment->previous = previousAttachment;
        previousAttachment->next = nextAttachment;
    }

    void remove (AttachmentList* attachmentList) {
        if (attachmentList == NULL) return;
        AttachmentList* nextAttachment = attachmentList->next;
        AttachmentList* previousAttachment = attachmentList->previous;
        delete attachmentList;
        if (nextAttachment == NULL && previousAttachment != NULL) {
            previousAttachment->next = NULL;
            attachmentListLastElement = previousAttachment;
            return;
        }
        if (previousAttachment == NULL && nextAttachment != NULL) {
            nextAttachment->previous = NULL;
            attachmentListFirstElement = nextAttachment;
            return;
        }
        if (previousAttachment == NULL && nextAttachment == NULL) {
            attachmentListFirstElement = NULL;
            attachmentListLastElement = NULL;
            return;
        }
        nextAttachment->previous = previousAttachment;
        previousAttachment->next = nextAttachment;
    }

    void removeAttachmentFromAll (int id, char a1, char a2, char a3) {
            RopeList* ropeListElement = ropeListFirstElement;
            while (ropeListElement != NULL) {
                BeadList* beadListElement = ropeListElement->rope->beadList->beadListFirstElement;
                while (beadListElement != NULL) {
                    AttachmentList* attachmentListElement = beadListElement->bead->attachmentList->attachmentListFirstElement;
                    while (attachmentListElement != NULL) {
                        Attachment* checkElement = attachmentListElement->attachment;
                        if (attachmentListElement->attachment->a1 == a1 && attachmentListElement->attachment->a2 == a2 && attachmentListElement->attachment->a3 == a3 && attachmentListElement->attachment->id == id) {
                            beadListElement->bead->attachmentList->remove(attachmentListElement);
                        }
                        attachmentListElement = attachmentListElement->next;
                    }
                    beadListElement = beadListElement->next;
                }
                ropeListElement = ropeListElement->next;
            }
    }

    void removeAllAttachmentsFromRope (Rope* rope) {
        BeadList* beadListElement = rope->beadList->beadListFirstElement;
        while (beadListElement != NULL) {
            removeAttachmentFromAll(beadListElement->bead->id, rope->a1, rope->a2, rope->a3);
            beadListElement = beadListElement->next;
        }
    }

    void changeStringInAttachmentsWithId (int id, char a1, char a2, char a3, char a1New, char a2New, char a3New) {
        RopeList* ropeListElement = ropeListFirstElement;
        while (ropeListElement != NULL) {
            BeadList* beadListElement = ropeListElement->rope->beadList->beadListFirstElement;
            while (beadListElement != NULL) {
                AttachmentList* attachmentListElement = beadListElement->bead->attachmentList->attachmentListFirstElement;
                while (attachmentListElement != NULL) {
                    Attachment* checkElement = attachmentListElement->attachment;
                    if (attachmentListElement->attachment->a1 == a1 && attachmentListElement->attachment->a2 == a2 && attachmentListElement->attachment->a3 == a3 && attachmentListElement->attachment->id == id) {
                        attachmentListElement->attachment-> a1 = a1New;
                        attachmentListElement->attachment-> a2 = a2New;
                        attachmentListElement->attachment-> a3 = a3New;
                    }
                    attachmentListElement = attachmentListElement->next;
                }
                beadListElement = beadListElement->next;
            }
            ropeListElement = ropeListElement->next;
        }
    }

    void print (char chr) {
        if (chr == 'r') {
            RopeList* element = ropeListFirstElement;
            while (element != NULL) {
                std::cout << element->rope->a1 << element->rope->a2 << element->rope->a3;
                std::cout << '\n';
                if (element->rope->beadList != NULL) {
                    element->rope->beadList->print('b');
                }
                element = element->next;
            }
        } else if (chr == 'b') {
            BeadList* element = beadListFirstElement;
            while (element != NULL) {
                std::cout << element->bead->id;
                if (element->bead->attachmentList != NULL) {
                    element->bead->attachmentList->print('b');
                }
                element->bead->attachmentList->print('a');
                std::cout << '\n';
                element = element->next;
            }
        } else if (chr == 'a') {
            AttachmentList* element = attachmentListFirstElement;
            while (element != NULL) {
                std::cout << " " << element->attachment->a1 << element->attachment->a2 << element->attachment->a3 << " " << element->attachment->id;
                element = element->next;
            }
        }
    }

    void freeAllRopes() {
        RopeList* ropeElement = ropeListFirstElement;
        while (ropeElement != NULL) {
            RopeList* ropeElementNext = ropeElement->next;
            remove(ropeElement->rope);
            ropeElement = ropeElementNext;
        }
    }
};

int main () {
    char operation;
    std::cin >> operation;

    LinkedList* ropeList = new LinkedList;

    while (operation != 'F') {
        switch (operation) {
            case 'S': {
                char a1, a2, a3;
                std::cin >> a1 >> a2 >> a3;
                if (ropeList->find(a1, a2, a3) != NULL) break;
                Rope* rope = new Rope;
                rope->a1 = a1;
                rope->a2 = a2;
                rope->a3 = a3;
                rope->beadList = new LinkedList();
                ropeList->add(rope);
                break;
            }
            case 'B': {
                int id;
                char a1, a2, a3;
                std::cin >> id;
                std::cin >> a1 >> a2 >> a3;
                Rope* rope = ropeList->find(a1, a2, a3);
                if (rope == NULL) {
                    break;
                }
                if (rope->beadList->find(id) != NULL) break;
                Bead* bead = new Bead();
                bead->id = id;
                bead->attachmentList = new LinkedList();
                rope->beadList->add(bead);
                break;
            }
            case 'L': {
                int idFrom, idTo;
                char a1From, a2From, a3From, a1To, a2To, a3To;
                std::cin >> idFrom >> a1From >> a2From >> a3From >> idTo >> a1To >> a2To >> a3To;
                Rope* ropeFrom = ropeList->find (a1From, a2From, a3From);
                Rope* ropeTo = ropeList->find (a1To, a2To, a3To);
                if (ropeFrom == NULL || ropeTo == NULL) {
                    break;
                }

                Bead* beadFrom = ropeFrom->beadList->find(idFrom);
                Bead* beadTo = ropeTo->beadList->find(idTo);
                if (beadFrom == NULL || beadTo == NULL) {
                    break;
                }

                if (beadFrom->attachmentList->find(a1To, a2To, a3To, idTo)) break;

                Attachment* attachment = new Attachment();
                attachment->a1 = a1To;
                attachment->a2 = a2To;
                attachment->a3 = a3To;
                attachment->id = idTo;

                beadFrom->attachmentList->add(attachment);
                break;
            }
            case 'U': {
                int idFrom, idTo;
                char a1From, a2From, a3From, a1To, a2To, a3To;
                std::cin >> idFrom >> a1From >> a2From >> a3From >> idTo >> a1To >> a2To >> a3To;
                Rope* ropeFrom = ropeList->find (a1From, a2From, a3From);
                Rope* ropeTo = ropeList->find (a1To, a2To, a3To);
                if (ropeFrom == NULL || ropeTo == NULL) {
                    break;
                }

                Bead* beadFrom = ropeFrom->beadList->find(idFrom);
                Bead* beadTo = ropeTo->beadList->find(idTo);
                if (beadFrom == NULL || beadTo == NULL) {
                    break;
                }

                Attachment* attachment = beadFrom->attachmentList->find(a1To, a2To, a3To, idTo);

                beadFrom->attachmentList->remove(attachment);
                break;
            }
            case 'D': {
                int id;
                char a1, a2, a3;
                std::cin >> id >> a1 >> a2 >> a3;
                Rope* rope = ropeList->find(a1, a2, a3);
                if (rope == NULL) {
                    break;
                }
                Bead* bead = rope->beadList->find(id);
                if (bead == NULL) {
                    break;
                }
                ropeList->removeAttachmentFromAll(id, a1, a2, a3);
                rope->beadList->remove(bead);
                break;
            }
            case 'M': {
                int id;
                char a1From, a2From, a3From, a1To, a2To, a3To;
                std::cin >> id >> a1From >> a2From >> a3From >> a1To >> a2To >> a3To;
                if (a1From == a1To && a2From == a2To && a3From == a3To) break;
                Rope* ropeFrom = ropeList->find(a1From, a2From, a3From);
                Rope* ropeTo = ropeList->find(a1To, a2To, a3To);
                if (ropeFrom == NULL || ropeTo == NULL) break;
                Bead* bead = ropeFrom->beadList->find(id);
                if (bead == NULL) break;
                ropeFrom->beadList->removeFromList(bead);
                ropeTo->beadList->add(bead);
                break;
            }
            case 'R': {
                char a1, a2, a3;
                std::cin >> a1 >> a2 >> a3;
                Rope* rope = ropeList->find(a1, a2, a3);
                if (rope == NULL) break;
                ropeList->removeAllAttachmentsFromRope(rope);
                ropeList->remove(rope);
                break;
            }
            case 'P': {
                ropeList->print('r');
                break;
            }
            default: {
                break;
            }
        }
        std::cin >> operation;
    }
    ropeList->freeAllRopes();
    delete ropeList;
    return 0;
}
