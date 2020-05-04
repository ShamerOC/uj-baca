// Krzysztof Wydrzynski
int itr = 0;
int number = 0;

int addToNumber (int where, int val) {
    if (val == 0) return where;
    int xorResult = where ^ val;
    int andResult = where & val;
    andResult = andResult << 1;
    return addToNumber (xorResult, andResult);
}

void Print (int set, std::string* out) {
    if (itr == 0) {
        *out = "";
    }

    if (itr > 31) {
        itr = 0;
        return;
    }

    if (set == 0) {
        *out= "empty";
    }
    int itrReverse = 32;
    itrReverse = addToNumber(itrReverse, ~itr);

    int itrInBin = 1 << itrReverse;

    if (set & itrInBin) {
        std::stringstream stringStream;
        stringStream << *out << (itrReverse / 16) % 2 << (itrReverse / 8) % 2 << (itrReverse / 4) % 2 << (itrReverse / 2) % 2 << (itrReverse % 2) << " ";
        *out = stringStream.str();
    }
    itr = addToNumber(itr, 1);
    Print(set, out);
}

int binStrToDecInt (std::string str, int start = 0) {
    int insideItr = start;
    int partSet = 1;
    if (str.at(insideItr) == '1') {
        partSet = partSet << 16;
    }
    insideItr = addToNumber(insideItr, 1);
    if (str.at(insideItr) == '1') {
        partSet = partSet << 8;
    }
    insideItr = addToNumber(insideItr, 1);
    if (str.at(insideItr) == '1') {
        partSet = partSet << 4;
    }
    insideItr = addToNumber(insideItr, 1);
    if (str.at(insideItr) == '1') {
        partSet = partSet << 2;
    }
    insideItr = addToNumber(insideItr, 1);
    if (str.at(insideItr) == '1') {
        partSet = partSet << 1;
    }
    return partSet;
}

int howManySets (int set) {
    if (itr == 0) {
        number = 0;
    }
    if (itr >= 32) {
        itr = 0;
        return number;
    }
    int positionToCheck = 1 << itr;
    if (positionToCheck & set) {
        number = addToNumber(number, 1);
    }
    itr = addToNumber(itr, 1);
    return howManySets(set);
}

void Emplace (std::string str, int* set) {
    if (itr == 0) {
        *set = 0;
    }
    if (itr < str.length()) {
        if (str.at(itr) == ' ') {
            itr = addToNumber(itr, 1);
        } else {
            int partSet = binStrToDecInt(str, itr);
            itr = addToNumber(itr, 5);
            *set = *set | partSet;
        }
        Emplace(str, set);
    } else {
        itr = 0;
    }
}

void Insert (std::string str, int* set) {
    if (itr < str.length()) {
        if (str.at(itr) == ' ') {
            itr = addToNumber(itr, 1);
        } else {
            int partSet = binStrToDecInt(str, itr);
            itr = addToNumber(itr, 5);
            *set = *set | partSet;
        }
        Insert(str, set);
    } else {
        itr = 0;
    }
}

void Erase (std::string str, int* set) {
    if (itr < str.length()) {
        if (str.at(itr) == ' ') {
            itr = addToNumber(itr, 1);
        } else {
            int partSet = binStrToDecInt(str, itr);
            itr = addToNumber(itr, 5);
            int partSetReverse = ~partSet;
            *set = *set & partSetReverse;
        }
        Erase(str, set);
    } else {
        itr = 0;
    }
}

int whichSetIsBigger (int set1, int set2) {
    if (itr > 31) {
        itr = 0;
        return 2;
    }
    int itrReversed = 32;
    itrReversed = addToNumber(itrReversed, ~itr);
    int check = 1 << itrReversed;
    if ((set1 & check ) && !(set2 & check)) {
        itr = 0;
        return 0;
    }
    if (!(set1 & check) && (set2 & check)) {
        itr = 0;
        return 1;
    }
    itr = addToNumber(itr, 1);
    return whichSetIsBigger(set1, set2);
}

bool Emptiness (int set) {
    if (set == 0) {
        return true;
    }
    return false;
}

bool Nonempty (int set) {
    if (set != 0) {
        return true;
    }
    return false;
}

bool Member (std::string str, int set) {
    int partSet = binStrToDecInt(str);

    if (set & partSet) {
        return true;
    }
    return false;
}

bool Disjoint (int set1, int set2) {
    int set1Reverse = ~set1;
    if ((set1Reverse & set2) == set2) {
        return true;
    }
    return false;
}

bool Conjunctive (int set1, int set2) {
    if (Disjoint(set1, set2)) {
        return false;
    }
    return true;
}

bool Equality (int set1, int set2) {
    return (set1 == set2);
}

bool Inclusion (int set1, int set2) {
    return ((set1 | set2) == set2);
}

void Union (int set1, int set2, int* set3) {
    *set3 = set1 | set2;
}

void Intersection (int set1, int set2, int* set3) {
    *set3 = set1 & set2;
}

void Symmetric (int set1, int set2, int* set3) {
    *set3 = set1 ^ set2;
}

void Difference (int set1, int set2, int* set3) {
    int set2Reverse = ~set2;
    *set3 = set1 & set2Reverse;
}

void Complement (int set1, int* set2) {
    *set2 = ~set1;
}

bool LessThen (int set1, int set2) {
    if (howManySets(set1) != howManySets(set2)) {
        return howManySets(set1) < howManySets(set2);
    }
    if (whichSetIsBigger(set1, set2) == 1) return true;
    return false;
    if (whichSetIsBigger(set1, set2) == 0) return false;
    if (whichSetIsBigger(set1, set2) == 2) return false;
}

bool LessEqual (int set1, int set2) {
    if (howManySets(set1) != howManySets(set2)) {
        return howManySets(set1) < howManySets(set2);
    }
    if (whichSetIsBigger(set1, set2) == 0) return false;
    return true;
    if (whichSetIsBigger(set1, set2) == 1) return true;
    if (whichSetIsBigger(set1, set2) == 2) return true;
}

bool GreatThen (int set1, int set2) {
    if (howManySets(set1) != howManySets(set2)) {
        return howManySets(set1) > howManySets(set2);
    }
    if (whichSetIsBigger(set1, set2) == 0) return true;
    return false;
    if (whichSetIsBigger(set1, set2) == 1) return false;
    if (whichSetIsBigger(set1, set2) == 2) return false;
}

bool GreatEqual (int set1, int set2) {
    if (howManySets(set1) != howManySets(set2)) {
        return howManySets(set1) > howManySets(set2);
    }
    if (whichSetIsBigger(set1, set2) == 1) return false;
    return true;
    if (whichSetIsBigger(set1, set2) == 0) return true;
    if (whichSetIsBigger(set1, set2) == 2) return true;
}